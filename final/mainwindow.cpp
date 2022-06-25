#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <string>
#include <QString>
#include <algorithm>
#include <fstream>
#include <set>
using namespace std;


#define inter 1000
//1s per mins
#define simulaTime 1500

QString create_one(int n){
    QString ans="";
    for(int i=0;i<n;i++)
        ans+="y";
    return ans;
}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->hide();//account
    ui->label_2->hide();//password
    ui->lineEdit->hide();//input account
    ui->lineEdit_2->hide();//input password
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->pushButton->hide();//enter
    ui->pushButton_4->hide();//for show bottom
    ui->pushButton->setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 #120000);");
    ui->pushButton_2->setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 #120000);");
    ui->pushButton_3->setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 #120000);");
    ui->pushButton_4->setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 #120000);");
    ui->pushButton->setAttribute(Qt::WA_Hover);
    ui->pushButton_2->setAttribute(Qt::WA_Hover);
    ui->pushButton_3->setAttribute(Qt::WA_Hover);
    ui->pushButton_4->setAttribute(Qt::WA_Hover);
    ui->pushButton->installEventFilter(this);
    ui->pushButton_2->installEventFilter(this);
    ui->pushButton_3->installEventFilter(this);
    ui->pushButton_4->installEventFilter(this);

    ui->label->setStyleSheet("color:qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 black);font:bold 9pt;");
    ui->label_2->setStyleSheet("color:qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 black);font:bold 9pt;");
    ui->label_3->setStyleSheet("color:qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 black);font:bold 15pt;");
    state=0;
    QObject::connect(&tshow,SIGNAL(timeout()),this,SLOT(t_changeform()));
    tshow.setInterval(300);
    ui->label_5->setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 #120000);");

    QObject::connect(&tshow,SIGNAL(timeout()),this,SLOT(t_changeform()));
    tshow.setInterval(300);


    QSqlDatabase database;
    database =QSqlDatabase::addDatabase ("QPSQL");
    database .setHostName ("");
    database .setDatabaseName ("") ;// schema name
    database .setUserName ("");
    database .setPassword ("");// your password
    database .setPort (5432);
    bool ok =database .open();
    if (ok){
        qDebug ()<<"Successful connect";
    }
    else{
        qDebug ()<<"Error: Cannot connect!!!";
    }
    query = new QSqlQuery (database);
    QSqlQuery query2(database);
    fo.setQuery(query);

    s.setQuery(query);

    //query->exec("select * from timeNow");
    //query->next();
    //QTime tempNow=query->value(0).toTime();
    //s.setNow(tempNow);
    /*
    query ->exec("select * from timeTable");
    while(query->next()){
        //read data from database
        Train temp;
        temp.setType(query->value(0).toString().toStdString());
        temp.setTrainNumber(query->value(1).toInt());
        temp.setPassThrough(query->value(2).toString().toStdString());
        temp.setCurrentLocation(query->value(3).toString().toStdString());
        temp.setNextStop(query->value(4).toString().toStdString());
        temp.setArrivalTime(query->value(5).toTime());
        temp.setRealArrivalTime(query->value(6).toTime());
        temp.setCarriageNumber(query->value(7).toInt());
        temp.setDelayTime(query->value(8).toInt());
        for(int i=0;i<temp.getCarriageNumber();i++){
            temp.setCarriagePeople(i,0);
            //add 0 people to carriage i
        }
        temp.setPassStation(0);
        temp.setTerminal(false);
        temp.setMoving(false);
        s.setTrain(temp);
        //add a train to s

    }*/
    //s.initialize();
    //simul.setInterval(simulaTime);
    //simul.start();
    //simulate erery 1.5s


    /*QString com4="DELETE FROM seat_table";
    query->exec(com4);
    QString com="SELECT t_num,max(num_order)  FROM needed_train_info GROUP BY t_num";
    fstream ooo("C:\\Users\\tstre\\Downloads\\final\\seat_table.txt",fstream::out);
    if(!ooo.is_open())
        cerr<<"ERROR open!";
    query->exec(com);
    while(query->next()){
        for(int i=1;i<=12;i++){
            for(int j=1;j<=80;j++){
                QString com3=query->value(0).toString()+","+QString::number(i)+(j>=10?QString("."):QString(".0"))+QString::number(j);
                QString one=create_one(query->value(1).toInt());
                for(int k=0;k<14;k++){
                    com3+=","+one;
                }
                //com3+=")";
                //query2.exec(com3);
                ooo<<com3.toStdString()<<endl;
            }
        }
    }

    qDebug()<<"END";*/
    oneMin.setInterval(inter);
    oneMin.start();
    //pass one minute in QT every 1s


    //QObject::connect(&showForm,SIGNAL(timeout()),&fo,SLOT(showTable()));
    showForm.setInterval(1000);
    showForm.start();
    ui->pushButton_2->click();
    state=1;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Enter)
    {
        QPushButton* a=qobject_cast<QPushButton*>(obj);
        a->setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:0.2 #121300,step:0.5 #F12312,step:1 #120000);border-style: outset;border-width: 2px;border-radius: 5px;border-color: #ffeecc;font: bold;");

    }
    else if(event->type()==QEvent::Leave){
        QPushButton* a=qobject_cast<QPushButton*>(obj);
        //       a->setStyleSheet("");
        a->setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 #120000);");
    }
    return QWidget::eventFilter(obj, event);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::t_changeform(){
    if(fo.q&&tshow.interval()==300){
        show();
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
        tshow.stop();
    }
    else if(tshow.interval()==1000){
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
        tshow.stop();
    }
}
void MainWindow::on_pushButton_clicked()//enter
{
    if(state==1){
        //log in
        string ac,pas;
        ac=ui->lineEdit->text().toStdString();
        pas=ui->lineEdit_2->text().toStdString();
        Client a(ac,pas);
        int ab=2;
        if(fo.NC->login(a,ab,fo.nowct,query)){
            if(fo.q){
                hide();
                fo.client_table_create();
                fo.q=false;
                fo.show();
                fo.state=0;
                fo.ti.start();
                tshow.stop();
                tshow.setInterval(300);
                tshow.start();
            }
        }
        else{
            QFont f=ui->label_4->font();
            f.setPointSize(20);
            //if(ab==1)
                //ui->label_4->setText("Wrong Password!");
            //else if(ab==2)
            ui->label_4->setText("Wrong account or password!");

        }
    }
    else if(state==2){
        //register
        string ac,pas;
        ac=ui->lineEdit->text().toStdString();
        pas=ui->lineEdit_2->text().toStdString();
        Client a(ac,pas);
        if(!fo.NC->exist(a,query)){
            ui->label_4->setText("Successful!");
            fo.NC->newClient(a,query);
        }
        else{
            ui->label_4->setText("Exist the same account!");
        }
    }
}


void MainWindow::on_pushButton_2_clicked()//log in
{
    ui->label->show();
    ui->label_2->show();
    ui->pushButton_4->show();
    ui->pushButton_2->hide();
    ui->pushButton_3->show();
    ui->lineEdit->show();
    ui->lineEdit->clear();
    ui->lineEdit_2->show();
    ui->lineEdit_2->clear();
    ui->pushButton->show();
    ui->label_4->setText("");
    state=1;
    QFont f=ui->label_3->font();
    f.setPointSize(20);
    ui->label_3->setText("LOG IN");
}

void MainWindow::on_pushButton_3_clicked()//register
{
    state=2;
    ui->pushButton_3->hide();
    ui->pushButton_2->show();
    ui->label->show();
    ui->label_2->show();
    ui->pushButton_4->show();
    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->pushButton->show();
    ui->label_4->setText("");
    QFont f=ui->label_3->font();
    f.setPointSize(20);

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->label_3->setText("REGISTER");


}

void MainWindow::on_pushButton_4_clicked()//show
{
    tshow.stop();
    tshow.setInterval(1000);
    tshow.start();
    ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
}

void MainWindow::changeTable()
{
    //call simulation function
    //s.simul(query);
}




void MainWindow::on_lineEdit_2_returnPressed()
{
    ui->pushButton->click();
}


