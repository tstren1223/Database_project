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
        cur.execute("SELECT t_num,max(num_order)  FROM (SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info14) as a GROUP BY t_num");
        records=cur.fetchall()
        cur.execute("ALTER TABLE seat_table DROP COLUMN code_date1;");
        for i in range(1,14):
            cur.execute("ALTER TABLE seat_table RENAME COLUMN code_date"+str(i+1)+" TO code_date"+str(i)+";")
        cur.execute("ALTER TABLE seat_table ADD COLUMN code_date14 TEXT;")
        """"
        cur.execute("CREATE TABLE IF NOT EXISTS temp(id INTEGER,id2 DOUBLE PRECISION, value TEXT, PRIMARY KEY (id,id2))");
        
        with open('tmp/seat_table.txt', 'r',encoding="utf-8") as rr:
            with open('tmp/data.txt', 'w+',encoding="utf-8") as f:
                for r in rr.readlines():
                    index_1=r.find(',');
                    index_2=r.find(',',index_1+1);
                    index_3=r.find(',',index_2+1);
                    f.write(r[:index_3]+"\n")
        
        with open('tmp/data.txt', 'r',encoding="utf-8") as f:
            cur.copy_from(f,"temp",null='',sep=",")
        """
        print("UPDATEing....");
        cur.execute("UPDATE seat_table SET code_date14=temp.value FROM temp WHERE (train_num,seat_code)=(id,id2)")              
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