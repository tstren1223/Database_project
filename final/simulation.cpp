#include "simulation.h"
#include <time.h>
#include <string>
#include <string.h>
using namespace std;


Simulation::Simulation()
{

}

Simulation::~Simulation()
{
    int h,m,s;
    QTimeToInt(now,h,m,s);
    string updateTime=to_string(h)+":"+to_string(m)+":"+to_string(s);
    string com="UPDATE timeNow SET now='"+updateTime+"'";
    query->exec(QString::fromStdString(com));
}

void Simulation::simul(QSqlQuery *query)
{
    srand(time(NULL));
    int parameter=5;
    string com;
    for(int i=0;i<(int)timeTable.size();i++){
        string temp=to_string(timeTable[i].getTrainNumber());
        com="SELECT * FROM timeTable"+temp;
        query->exec(QString::fromStdString(com));
        query->next();
        if(now < query->value(1).toTime()){
            //the train have not start
            continue;
        }
        else {
            if(timeTable[i].getTerminal()==false){
                //id the train having start, start it
                timeTable[i].setMoving(true);
            }

        }
        if(timeTable[i].getMoving()==false){
            //the train arrive its terminal
            continue;
        }
        string t=now.toString().toStdString();
        t=t.substr(0,2);
        int tint=stringToInt(t);
        //get hour part of now
        if(tint==7 || tint==8){
            parameter=8;
            //in the morning, the probability of delay is higher
        }
        else if(tint==12){
            parameter=15;
            //at 12, the probability of delay is lower
        }
        else if(tint==17 || tint==18 || tint==19){
            parameter=6;
            //at 17 18 19, the probalility is the highest
        }
        if(rand()%parameter==0){
            //5% to dalay
            int delayTime=rand()%2;
            //at most delay 2 mins one time


            string delayTimes=to_string(delayTime);
            com="UPDATE timeTable SET delay=delay+"+delayTimes+" WHERE trainNumber="+temp;
            query->exec(QString::fromStdString(com));
            //update the data in database(timeTable), which is the most general table

            com="select * from timeTable WHERE trainNumber="+temp;
            query->exec(QString::fromStdString(com));
            query->next();
            int h,m,s;
            QTimeToInt(query->value(6).toTime(),h,m,s);
            m=m+delayTime;
            if(m>60){
                m=m%60;
                h++;
            }
            string updateTime=to_string(h)+":"+to_string(m)+":"+to_string(s);
            com="UPDATE timeTable SET realArriveTime= '"+updateTime+"' WHERE trainNumber="+temp;
            query->exec(QString::fromStdString(com));

            //update data in database(timetable+trainNumber),which is data of specific train

            timeTable[i].setRealArrivalTime(query->value(6).toTime());


            com="UPDATE timeTable"+temp+" SET delay=delay+"+delayTimes;
            query->exec(QString::fromStdString(com));

        }
        com="SELECT * from timeTable WHERE trainNumber="+temp;
        query->exec(QString::fromStdString(com));
        query->next();
        int isDelay=stringToInt(query->value(8).toString().toStdString());
        if(isDelay>0){
            //check whether the train is delay
            if(rand()%3==2){
                //determine whether the train cover the delay time
                int cover=rand()%isDelay;
                //the cover time will not exceed its delay time
                if(cover>0){
                    //the condition that the train cover
                    com="UPDATE timeTable SET delay=delay-"+to_string(cover)+" WHERE trainNumber="+temp;
                    query->exec(QString::fromStdString(com));
                    com="SELECT * from timeTable WHERE trainNumber="+temp;
                    query->exec(QString::fromStdString(com));
                    query->next();

                    int h,m,s;
                    QTimeToInt(query->value(6).toTime(),h,m,s);
                    //get realArrive time
                    m=m-cover;
                    if(m<0){
                        m=60+m;
                        h--;
                    }

                    string updateTime=to_string(h)+":"+to_string(m)+":"+to_string(s);
                    com="UPDATE timeTable SET realArriveTime= '"+updateTime+"' WHERE trainNumber="+temp;
                    query->exec(QString::fromStdString(com));

                    com="UPDATE timeTable"+temp+" SET delay=delay-"+to_string(cover);
                    query->exec(QString::fromStdString(com));
                }
            }
        }

        changeStop(query,temp,i);

    }

}

void Simulation::setQuery(QSqlQuery *q)
{
    query=q;
}

void Simulation::setTrain(Train t)
{
    timeTable.push_back(t);
}

void Simulation::setNow(QTime t)
{
    now=t;
}

QTime Simulation::getNow()
{
    return now;
}

void Simulation::changeStop(QSqlQuery *query,string number,int i)
{
    //the aim of this function is to check whether we need to change the stop and nextStop in database
    string com;
    com="SELECT * from timeTable WHERE trainNumber="+number;
    query->exec(QString::fromStdString(com));
    query->next();
    QTime t1=query->value(6).toTime();
    //get the realArrive time
    if(t1<now){
        //need to change the current station
        int count=0;
        timeTable[i].setPassStation(timeTable[i].getPassStation()+1);
        //having pass one more station
        qDebug()<<timeTable[i].getStationNumber() - timeTable[i].getPassStation();
        if(timeTable[i].getStationNumber() - timeTable[i].getPassStation() == 1){
            //there are only one left station to go
            timeTable[i].setTerminal(true);
        }
        if(timeTable[i].getStationNumber() - timeTable[i].getPassStation() <=0){
            //the station arrive its terminal station
            //stop to simulate
            timeTable[i].setMoving(false);
            com="UPDATE timeTable SET nextStop='terminal' WHERE trainNumber="+number;
            query->exec(QString::fromStdString(com));
            com="UPDATE timeTable SET thisStop='terminal' WHERE trainNumber="+number;
            query->exec(QString::fromStdString(com));
            com="UPDATE timeTable SET arriveTime='00:00:00' WHERE trainNumber="+number;
            query->exec(QString::fromStdString(com));
            com="UPDATE timeTable SET realArriveTime='00:00:00' WHERE trainNumber="+number;
            query->exec(QString::fromStdString(com));
            //com="UPDATE timeTable SET delay=0 WHERE trainNumber="+number;
            //query->exec(QString::fromStdString(com));
            return;

        }




        string stop1="",stop2="";
        string ts1="",ts2="";
        com="SELECT * from timeTable"+number;
        query->exec(QString::fromStdString(com));
        query->next();
        count=0;
        while(query->next()){
            count++;
            QTime temp=query->value(1).toTime();
            //arriveTime
            int delay=query->value(2).toInt();
            //delay time
            addDelay(temp,delay);
            //combine the two data to get realArriveTime
            if(now < temp){
                stop2=query->value(0).toString().toStdString();
                //get next stop
                QTime t1=query->value(1).toTime();
                ts1=t1.toString().toStdString();
                addDelay(t1,delay);
                ts2=t1.toString().toStdString();
                //get the real time that will arrive the next stop
                break;
            }
        }
        com="SELECT * from timeTable"+number;
        query->exec(QString::fromStdString(com));
        query->next();
        for(int i=0;i<count-1;i++){
            query->next();
            //get this stop
        }
        stop1=query->value(0).toString().toStdString();

        com="UPDATE timeTable SET thisStop='"+stop1+"' WHERE trainNumber="+number;
        query->exec(QString::fromStdString(com));
        com="UPDATE timeTable SET nextStop='"+stop2+"' WHERE trainNumber="+number;
        query->exec(QString::fromStdString(com));

        com="UPDATE timeTable SET arriveTime='"+ts1+"' WHERE trainNumber="+number;
        query->exec(QString::fromStdString(com));
        com="UPDATE timeTable SET realArriveTime='"+ts2+"' WHERE trainNumber="+number;
        query->exec(QString::fromStdString(com));

        //update the data thisStop and nextStop in database



    }
}

void Simulation::QTimeToInt(QTime t, int &h, int &m, int &s)
{
    //convert QTime to three integer number
    string ts=t.toString().toStdString();
    string hs=ts.substr(0,2);
    h=stringToInt(hs);
    string ms=ts.substr(3,2);
    m=stringToInt(ms);
    string ss=ts.substr(6,2);
    s=stringToInt(ss);
}

void Simulation::addDelay(QTime &t, int delay)
{
    //add time and delay
    int h,m,s;
    QTimeToInt(t,h,m,s);
    m=m+delay;
    if(m>=60){
        m=m%60;
        h++;
    }
    t.setHMS(h,m,s);
}

vector<Train> Simulation::getTimeTable()
{
    return timeTable;
}

void Simulation::initialize()
{
    //load the cariage number
    for(int i=0;i<(int)timeTable.size();i++){
        string ns=to_string(timeTable[i].getTrainNumber());
        string com="SELECT * FROM timeTable"+ns;
        query->exec(QString::fromStdString(com));
        int count=0;
        while(query->next()){
            count++;
        }
        timeTable[i].setStationNumber(count);

        qDebug()<<count;
    }


}


int Simulation::stringToInt(string s)
{
    //convert string to int
    int temp=0;
    int index=1;
    for(int i=s.length()-1;i>=0;i--){
        int t=s[i]-48;
        t*=index;
        temp+=t;
        index*=10;
    }
    return temp;
}

