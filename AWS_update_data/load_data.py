import psycopg2
from config import config
import urllib3
import datetime
def connect():
    """ Connect to the PostgreSQL database server """
    conn = None
    try:
        # read connection parameters
        params = config()

        # connect to the PostgreSQL server
        print('Connecting to the PostgreSQL database...')
        conn = psycopg2.connect(**params)
		
        # create a cursor
        cur = conn.cursor()
        #delete the possible changed tables
        #load data

        url_data = ('https://ods.railway.gov.tw/tra-ods-web/ods/download/dataResource/railway_schedule/JSON/list')
        url_data_head='https://ods.railway.gov.tw'
        http = urllib3.PoolManager()
        r = http.request("GET",url_data) # create HTTP response object
        url_table={};
        update_table={};
        today = datetime.date.today()
        running = today;
        bool=False;
        t_stamp=""
        temp=""
        for i in r.data.split():
            
            i=i.decode('UTF-8')
            if bool==False and "<td>" in i and "</td>" not in i:
                bool=True;
                index=i.find("<td>")
                t_stamp=i[index+4:]+" "
                continue;
            if bool==True and "</td>" in i and "<td>" not in i:
                bool=False;
                index=i.find("</td>")
                t_stamp+=i[:index]
                if 'href' in i:
                    index_1=i.find('"');
                    index_2=i.find('"',index_1+1)
                    date=i[index_2+2:index_2+2+8]
                    url_table[date]=url_data_head+i[index_1+1:index_2]
                    update_table[date]=temp
                else:
                    temp=t_stamp;
                t_stamp=""
        url=""
        for i in range(1,15):
            running+= datetime.timedelta(days=1)
            str_d=running.strftime("%Y%m%d");
            cur.execute("SELECT value FROM update_table WHERE date="+str(i));
            records = cur.fetchall()
            for rows in records:
                com=rows[0].strftime("%Y-%m-%d %H:%M:%S")
                if com<update_table[str_d]:
                    print("UPDATE "+str(i));
                    cur.execute("DROP TABLE IF EXISTS data_json CASCADE; CREATE TABLE IF NOT EXISTS data_json( id serial NOT NULL PRIMARY KEY, info json NOT NULL );")
                    r = http.request("GET",url_table[str_d])
                    with open("tmp/data"+".json",'wb+') as f:
                        f.write(r.data)
                    co=('info',)
                    with open('tmp/data.json', 'r',encoding="utf-8") as f:
                        cur.copy_from(f,"data_json",null='',sep=chr(1),columns=co)
                    if i==1:
                        cur.execute("DELETE FROM needed_train_info;")
                        cur.execute("DELETE FROM train_time_info;")
                        cur.execute("DELETE FROM train_info;")
                        cur.execute("INSERT INTO train_info(tain_type,train_num,breast_feed,route,package,over_night,line_dir,train_line,dinning,foodsrv,cripple,car_class,bike,extra_train,everyday,note,note_english,update_time) ( SELECT CAST(j_record->>'Type' as CHAR(1)) as train_type,CAST(j_record->>'Train' as INTEGER) as train_num, CAST(j_record->>'BreastFeed'as CHAR(1)) as bf,CAST(j_record->>'route' as VARCHAR(1))as route,CAST(j_record->>'Package'as CHAR(1)) as pk,CAST(nullif(j_record->>'OverNightStn', '') as INTEGER) as ons,CAST(j_record->>'LineDir'as CHAR(1)) as ld,CAST(j_record->>'Line'as CHAR(1)),CAST(j_record->>'Dinning' as CHAR(1))as dinning,CAST(j_record->>'FoodSrv'as CHAR(1)) as food, CAST(j_record->>'Cripple'as CHAR(1)) as cripple,CAST(j_record->>'CarClass'as CHAR(4)) as carclass,CAST(j_record->>'Bike'as CHAR(1)) as bike,CAST(j_record->>'ExtraTrain'as CHAR(1)) as extra_t,CAST(j_record->>'Everyday'as CHAR(1)) as everyday,CAST(j_record->>'Note'as VARCHAR(20)) as note,CAST(j_record->>'NoteEng'as VARCHAR(20)) as note_eng,CAST(j_d as CHAR(19)) as update_time FROM (SELECT json_array_elements(info->'TrainInfos') as j_record FROM data_json a)as j_t,(SELECT info->>'UpdateTime' as j_d FROM data_json b)as j_date  WHERE  j_record->>'Everyday'='Y')");
                        cur.execute("INSERT INTO train_time_info ( SELECT CAST(train_num as INTEGER),CAST(j_time->>'Route' as VARCHAR(1)),CAST(j_time->>'Station' as INTEGER),CAST(j_time->>'Order' as INTEGER),CAST(j_time->>'DEPTime' as CHAR(8)),CAST(j_time->>'ARRTime' as CHAR(8)) FROM (SELECT json_array_elements(info->'TrainInfos')->>'Train' as train_num,json_array_elements(json_array_elements(info->'TrainInfos')->'TimeInfos') as j_time,json_array_elements(info->'TrainInfos')->>'Everyday' as ev FROM data_json b)as j_time WHERE ev='Y' )");
                        cur.execute("WITH train_needed AS( SELECT train_num AS t_num,breast_feed bf,foodsrv AS food,cripple AS crp,car_class AS car_code,chinese_name AS c_n,everyday,chinese_name as t_c_n,train_line as t_l FROM train_info a Join train_code b ON a.car_class=b.code ) INSERT INTO needed_train_info ( SELECT t_num,chinese_name as station_c_n,related_city as city,everyday,num_order,t_c_n,t_l,bf,food,crp,car_code,c_n,arr_time,dep_time FROM (train_needed a JOIN train_time_info b ON a.t_num=b.train_num),train_station_code_2 c WHERE c.code=station ORDER BY (t_num,num_order))");
                    cur.execute("DELETE FROM needed_train_info"+str(i)+";")
                    cur.execute("DELETE FROM train_time_info"+str(i)+";")
                    cur.execute("DELETE FROM train_info"+str(i)+";")
                    cur.execute("INSERT INTO train_info"+str(i)+"(tain_type,train_num,breast_feed,route,package,over_night,line_dir,train_line,dinning,foodsrv,cripple,car_class,bike,extra_train,everyday,note,note_english,update_time) ( SELECT CAST(j_record->>'Type' as CHAR(1)) as train_type,CAST(j_record->>'Train' as INTEGER) as train_num, CAST(j_record->>'BreastFeed'as CHAR(1)) as bf,CAST(j_record->>'route' as VARCHAR(1))as route,CAST(j_record->>'Package'as CHAR(1)) as pk,CAST(nullif(j_record->>'OverNightStn', '') as INTEGER) as ons,CAST(j_record->>'LineDir'as CHAR(1)) as ld,CAST(j_record->>'Line'as CHAR(1)),CAST(j_record->>'Dinning' as CHAR(1))as dinning,CAST(j_record->>'FoodSrv'as CHAR(1)) as food, CAST(j_record->>'Cripple'as CHAR(1)) as cripple,CAST(j_record->>'CarClass'as CHAR(4)) as carclass,CAST(j_record->>'Bike'as CHAR(1)) as bike,CAST(j_record->>'ExtraTrain'as CHAR(1)) as extra_t,CAST(j_record->>'Everyday'as CHAR(1)) as everyday,CAST(j_record->>'Note'as VARCHAR(20)) as note,CAST(j_record->>'NoteEng'as VARCHAR(20)) as note_eng,CAST(j_d as CHAR(19)) as update_time FROM (SELECT json_array_elements(info->'TrainInfos') as j_record FROM data_json a)as j_t,(SELECT info->>'UpdateTime' as j_d FROM data_json b)as j_date WHERE  j_record->>'Everyday'='N')");
                    cur.execute("INSERT INTO train_time_info"+str(i)+" ( SELECT CAST(train_num as INTEGER),CAST(j_time->>'Route' as VARCHAR(1)),CAST(j_time->>'Station' as INTEGER),CAST(j_time->>'Order' as INTEGER),CAST(j_time->>'DEPTime' as CHAR(8)),CAST(j_time->>'ARRTime' as CHAR(8)) FROM (SELECT json_array_elements(info->'TrainInfos')->>'Train' as train_num,json_array_elements(json_array_elements(info->'TrainInfos')->'TimeInfos') as j_time,json_array_elements(info->'TrainInfos')->>'Everyday' as ev FROM data_json b)as j_time WHERE ev='N' )");
                    cur.execute("WITH train_needed AS( SELECT train_num AS t_num,breast_feed bf,foodsrv AS food,cripple AS crp,car_class AS car_code,chinese_name AS c_n,everyday,chinese_name as t_c_n,train_line as t_l FROM train_info"+str(i)+" a Join train_code b ON a.car_class=b.code ) INSERT INTO needed_train_info"+str(i)+" ( SELECT t_num,chinese_name as station_c_n,related_city as city,everyday,num_order,t_c_n,t_l,bf,food,crp,car_code,c_n,arr_time,dep_time FROM (train_needed a JOIN train_time_info"+str(i)+" b ON a.t_num=b.train_num),train_station_code_2 c WHERE c.code=station ORDER BY (t_num,num_order))");
                    cur.execute("UPDATE update_table SET value='"+update_table[str_d]+"' WHERE date="+str(i));
        
        # close the communication with the PostgreSQL
        cur.close()
    except (Exception, psycopg2.DatabaseError) as error:
        print(error)
    finally:
        if conn is not None:
            conn.commit();
            conn.close()
            print('Database connection closed.')


if __name__ == '__main__':
    connect()