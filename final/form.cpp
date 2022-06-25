#include "form.h"
#include "ui_form.h"
const int col=6;
const int col2=11;//for special serving
const int maxDiscreateSeat=3;

QString temp_style[2];


int combo_num;
int combo2_num;
Form::Form(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Form) , seatInCarriage(40)
{

    ui->setupUi(this);
    bug=0;
    today=QDate::currentDate();
    double_state2=false;
    q=true;
    nowct=NULL;
    NC=new NetworkClient;
    ui->timeEdit_2->hide();
    //   ui->timeEdit_2->setStyleSheet("QTimeEdit::up-arrow {width: 0;} QTimeEdit::up-button {width: 0;}QTimeEdit::down-arrow {width: 0;} QTimeEdit::down-button {width: 0;}");
    //QObject::connect(&t,SIGNAL(timeout()),this,SLOT(t_changform()));
    //t.setInterval(500);
    state=0;//initial state
    clickedSearch=false;
    //process UI hide
    _hideall();
    //setting running light
    QFont f=ui->label_9->font();
    f.setPointSize(12);
    ui->label_9->setStyleSheet("background: black;color:red;font: bold;");
    for(int i=0;i<63;i++){
        ui->label_9->setText(ui->label_9->text()+" ");
    }
    ui->label_3->setText("From");
    ui->label_4->setText("To");
    running="Be Aware of Only The Special Identity Can Use Special Care Like Preggnant or Kids or Elders or Alone person, Hope You All Have A Nice Day!";
    runbegin=0;
    changerun=0;
    startdo=0;
    rl.setInterval(90);
    QObject::connect(&rl,SIGNAL(timeout()),this,SLOT(t_run()));
    QObject::connect(&ti,SIGNAL(timeout()),this,SLOT(timer()));
    ti.setInterval(1000);
    QObject::connect(this,SIGNAL(signal_updateTable()),this,SLOT(slot_updateTable2()));
    QObject::connect(this,SIGNAL(signal_updateTable3()),this,SLOT(slot_updateTable3()));
    QObject::connect(this,SIGNAL(signal_modifyTwo()),this,SLOT(on_pushButton_7_clicked()));
    QObject::connect(this,SIGNAL(signal_initialFromToCity()),this,SLOT(slot_initialFromToCity()));
    //process transparent pushbottom
    ui->pushButton->setStyleSheet("background-color: rgba(255, 255, 255, 50);font: 14px;height 31px;width: 150px");
    ui->pushButton_2->setStyleSheet("background-color: rgba(255, 255, 255, 50);font: 14px;height 31px;width: 150px");
    ui->pushButton_3->setStyleSheet("background-color: rgba(255, 255, 255, 50);font: 14px;height 31px;width: 150px");
    ui->pushButton_4->setStyleSheet("background-color: rgba(255, 255, 255, 50);font:14px;height 31px;width: 150px");
    ui->pushButton_5->setStyleSheet("background-color: rgba(255, 255, 255, 50);font:14px;height 31px;width: 150px");
    ui->pushButton_6->setStyleSheet("background-color:qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 black);height 31px;width: 150px");
    temp_style[0]=ui->pushButton->styleSheet();
    temp_style[1]=ui->pushButton_6->styleSheet();
    ui->pushButton->setAttribute(Qt::WA_Hover);
    ui->pushButton_2->setAttribute(Qt::WA_Hover);
    ui->pushButton_3->setAttribute(Qt::WA_Hover);
    ui->pushButton_4->setAttribute(Qt::WA_Hover);
    ui->pushButton_5->setAttribute(Qt::WA_Hover);
    ui->pushButton->installEventFilter(this);
    ui->pushButton_2->installEventFilter(this);
    ui->comboBox_2->setEditable(true);
    ui->comboBox_2->lineEdit()->setReadOnly(true);
    ui->comboBox_6->setEditable(true);
    ui->comboBox_6->lineEdit()->setReadOnly(true);
    ui->comboBox_7->setEditable(true);
    ui->comboBox_7->lineEdit()->setReadOnly(true);
    ui->comboBox->setEditable(true);
    ui->comboBox->lineEdit()->setReadOnly(true);
    ui->pushButton_3->installEventFilter(this);

    ui->pushButton_4->installEventFilter(this);

    ui->pushButton_5->installEventFilter(this);
    ui->pushButton_6->installEventFilter(this);
    //process picture
    QPixmap p(":/pic/train.jpg");
    if(p.isNull())
        qDebug()<<"A";
    ui->label_11->setPixmap(p);
    ui->label_11->show();
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFrameStyle(QFrame::NoFrame);
    ui->graphicsView->setStyleSheet("background: transparent");
    scene->clear();
    QPixmap gp(":/pic/pregnant.png");
    scene->addPixmap(gp);//dummy
    menu = new QGraphicsScene();
    ui->graphicsView_2->setScene(menu);
    ui->graphicsView_2->setFrameStyle(QFrame::NoFrame);
    ui->graphicsView_2->setStyleSheet("background-color: rgba(163, 148, 128,0);");//rice color
    //   ti.setInterval(200);
    // ti.start();
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setColumnHidden(11,true);
    ui->tableWidget_3->setColumnHidden(11,true);
    ui->tableWidget->setColumnHidden(5,true);
    ui->label_14->setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 #120000);");
    //   ui->comboBox_2->setEditable(true);
}
void Form::timer(){
    query->exec("SELECT CURRENT_TIMESTAMP(0) AT TIME ZONE 'AWST'");
    query->next();
    string q=query->value(0).toString().toStdString();
    int index=q.find('T');
    string a="";
    a+=q.substr(8,2);
    a+="/";
    a+=q.substr(5,2);
    a+="/";
    a+=q.substr(0,4);
    today= QDate::fromString(QString::fromStdString(a),"dd/MM/yyyy");
    ui->timeEdit_2->setTime(QTime::fromString(QString::fromStdString(q.substr(index+1,8))));
}
bool Form::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::Enter)
    {
        QPushButton* a=qobject_cast<QPushButton*>(obj);
        if(a==ui->pushButton_6){
            a->setStyleSheet("background-color:qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 black);height:31px;width:150px;border-style: outset;border-width: 2px;border-radius: 10px;border-color: beige;font: bold 14px;");

        }
        else{
            a->setStyleSheet("background-color:qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 white ,stop:1 black);height:31px;width:150px;border-style: outset;border-width: 2px;border-radius: 10px;border-color: beige;font: bold 14px;min-width: 10em;padding: 6px;");
        }
    }
    else if(event->type()==QEvent::Leave){
        QPushButton* a=qobject_cast<QPushButton*>(obj);
        if(a==ui->pushButton_6){
            a->setStyleSheet(temp_style[1]);
        }
        else
            a->setStyleSheet(temp_style[0]);
    }
    return QWidget::eventFilter(obj, event);
}

void Form::_hideall(){//except for the menu and picture
    //message
    dia.hide();
    //timer
    rl.stop();
    //label
    ui->label_2->hide();
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_9->hide();
    ui->label_10->hide();
    ui->label_15->hide();
    ui->label_16->hide();
    ui->graphicsView->hide();
    //ui->label_11->hide();for picture
    //time and combobox
    ui->calendarWidget->hide();
    ui->dateEdit->hide();
    ui->comboBox->hide();
    ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->comboBox_4->hide();
    ui->comboBox_5->hide();
    ui->spinBox_2->hide();
    ui->spinBox_3->hide();
    ui->spinBox->hide();
    ui->pushButton_6->hide();
    ui->pushButton_7->hide();
    ui->timeEdit->hide();
    //group
    ui->groupBox->hide();
    ui->radioButton->hide();
    ui->radioButton_2->hide();
    ui->tableWidget->hide();
    ui->tableWidget_2->hide();
    ui->tableWidget_3->hide();
    ui->comboBox_8->hide();
    ui->comboBox_9->hide();
    ui->comboBox_11->hide();
    ui->comboBox_10->hide();
    ui->comboBox_6->hide();
    ui->comboBox_7->hide();
    ui->pushButton_8->hide();
    ui->label_13->hide();
    ui->pushButton_10->hide();
    ui->checkBox->hide();
    ui->checkBox_2->hide();
    ui->checkBox_3->hide();
    ui->pushButton_11->hide();
    ui->pushButton_9->hide();
}

Form::~Form()
{
    delete ui;
}

void Form::setQuery(QSqlQuery *q)
{
    query=q;
}

void Form::t_run(){
    ui->label_9->hide();
    QString s;
    int size=0;
    if(startdo!=62){
        ui->label_9->hide();
        QString a=ui->label_9->text();
        for(int i=0;i<62;i++)
            a[i]=a[i+1];//move left
        a[62]=running[startdo];
        ui->label_9->setText(a);
        //        ui->label_9->setStyleSheet("background: black;color:red;font: bold;");
        if(state==3)
            ui->label_9->show();
        startdo++;
    }
    else{
        while(size!=63){
            s+=running[(runbegin+size)%running.size()];
            size++;
        }
        ui->label_9->setText(s);
        if(state==3)
            ui->label_9->show();
        runbegin++;
        runbegin%=running.size();
    }
}

void Form::on_pushButton_clicked()//reserve
{

    bug=0;

    double_state2=false;
    QTableWidgetItem *item;
    int row=ui->tableWidget->rowCount();
    //delete original item
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            item=ui->tableWidget->item(i,j);
            delete item;
        }
    }
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);


    _hideall();
    //process UI show
    //reverse tickets
    ui->label_2->hide();//tickets number
    ui->label_3->show();//start point
    ui->label_4->show();//destination
    ui->label_5->hide();//train number
    ui->label_6->hide();//seat number
    ui->label_7->show();//time and date
    ui->label_8->hide();//for the success or fail
    ui->label_9->hide();
    ui->calendarWidget->show();//for date choose
    ui->dateEdit->show();
    ui->timeEdit->show();//for time choose
    ui->comboBox->show();//start choose
    ui->comboBox->clear();
    ui->comboBox_2->show();//destination choose
    ui->comboBox_2->clear();
    ui->comboBox_3->hide();//train number choose
    ui->comboBox_3->clear();
    ui->comboBox_4->hide();//seat number choose
    ui->comboBox_4->clear();
    ui->comboBox_5->hide();//choosing ticket
    //ui->spinBox->show();//ticket number choose
    ui->spinBox->clear();
    ui->pushButton_6->hide();//enter
    ui->pushButton_7->hide();
    ui->comboBox_6->show();
    ui->comboBox_7->show();
    ui->pushButton_8->hide();//check for reserve
    state=1;

    //-------------------for the context-----------------
    ui->spinBox->setValue(1);
    ui->label_2->setText("Tickets num");
    ui->label_3->setText("From");
    ui->label_4->setText("To");
    ui->label_5->setText("Carriage num");
    ui->label_6->setText("Seat num");
    ui->label_7->setText("Time");
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    ui->calendarWidget->setEnabled(true);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setEnabled(true);
    ui->timeEdit->setTime(QTime::currentTime());
    ui->timeEdit->setEnabled(true);
    ui->pushButton_6->setText("Enter");
    //combobox
    ui->comboBox->setCurrentIndex(-1);
    ui->comboBox_2->setCurrentIndex(-1);
    ui->comboBox_3->setCurrentIndex(-1);
    ui->comboBox_4->setCurrentIndex(-1);

    ui->comboBox_3->clear();
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_6->clear();
    ui->comboBox_7->clear();

    ui->tableWidget->show();
    ui->tableWidget_2->hide();

    //show city and town in combo box
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_6->clear();
    ui->comboBox_7->clear();
    emit signal_initialFromToCity();


}

void Form::on_pushButton_2_clicked()//modify
{
    //select calendar before pressing
    ui->label_12->hide();
    bug=0;

    double_state2=false;
    QTableWidgetItem *item;
    int row=ui->tableWidget_2->rowCount();
    //delete original item
    for(int i=0;i<row;i++){
        for(int j=0;j<col2;j++){
            item=ui->tableWidget_2->item(i,j);
            delete item;
        }
    }
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);


    emit signal_updateTable();

    _hideall();
    state=2;
    //process UI hide
    ui->label_2->hide();
    ui->label_3->show();
    ui->label_4->show();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_9->hide();
    ui->calendarWidget->show();
    ui->comboBox->show();
    ui->comboBox_2->show();
    ui->comboBox_3->hide();
    ui->comboBox_4->hide();
    ui->comboBox_5->hide();
    ui->spinBox->hide();
    ui->pushButton_6->hide();
    //ui->pushButton_7->hide();
    ui->timeEdit->hide();
    ui->dateEdit->hide();
    //---------------------context------------------
    ui->label_2->setText("Tickets Code");
    ui->label_8->clear();
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();
    ui->spinBox->clear();
    ui->tableWidget_2->show();
    //ui->pushButton_7->show();
    ui->comboBox_6->show();
    ui->comboBox_7->show();
    ui->comboBox_6->setCurrentIndex(-1);
    ui->comboBox_7->setCurrentIndex(-1);
    ui->pushButton_8->hide();

    //ui->comboBox_5->setCurrentIndex(-1);

    emit signal_initialFromToCity();

    ui->label_3->setText("From");
    ui->label_4->setText("To");

}

void Form::on_pushButton_3_clicked()//other service
{
    _hideall();
    bug=0;
    state=3;
    QTableWidgetItem *item;
    int row=ui->tableWidget_3->rowCount();
    //delete original item
    for(int i=0;i<row;i++){
        for(int j=0;j<col2;j++){
            item=ui->tableWidget_3->item(i,j);
            delete item;
        }
    }
    ui->tableWidget_3->clearContents();
    ui->tableWidget_3->setRowCount(0);
    double_state2=false;
    //process UI hide
    ui->label_2->hide();
    ui->label_3->show();
    ui->label_4->show();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_9->hide();//running light
    ui->calendarWidget->hide();
    ui->comboBox->hide();
    ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->comboBox_4->hide();
    //ui->comboBox_5->show();
    ui->spinBox->hide();
    //ui->pushButton_6->hide();
    //ui->pushButton_7->hide();
    ui->timeEdit->hide();
    ui->dateEdit->hide();
    //---------------------context------------------
    ui->label_2->setText("Tickets Code");
    ui->label_8->clear();
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();
    ui->spinBox->clear();

    ui->comboBox->show();
    ui->comboBox_2->show();
    ui->comboBox_6->show();
    ui->comboBox_7->show();
    ui->comboBox_8->show();
    ui->comboBox_9->show();
    ui->pushButton_8->hide();
    ui->calendarWidget->hide();
    ui->calendarWidget->setEnabled(true);
    ui->tableWidget_3->show();
    ui->comboBox_8->hide();
    ui->comboBox_9->hide();
    ui->tableWidget_2->hide();

    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_6->clear();
    ui->comboBox_7->clear();

    emit signal_updateTable3();
    emit signal_initialFromToCity();



    ui->comboBox_5->setCurrentIndex(-1);




}

void Form::on_pushButton_4_clicked()//log out
{

    double_state2=false;
    ti.stop();
    ui->label_12->hide();
    bug=0;
    if(!q){
        nowct=NULL;
        //process UI hide
        _hideall();
        q=true;
        hide();
    }
}

void Form::on_pushButton_6_clicked()//enter
{
    if(state==1){
        ui->label_8->hide();

        double carriageNumber=ui->comboBox_3->currentText().toDouble();
        double seatNumber=ui->comboBox_4->currentText().toDouble();
        double seat=carriageNumber+(seatNumber/100.0);
        string infoMiddle=QString::number(seat).toStdString()+",";

        //process ticket code to prevent repeated code
        string com;
        int indexComma=reserveCom1.find_first_of(',');
        string subString=reserveCom1.substr(indexComma);
        com="SELECT MAX(code) FROM "+nowct->clientName;
        query->exec(QString::fromStdString(com));
        query->next();
        int totalTicket=query->value(0).toInt();
        string reserveComNew="("+QString::number(totalTicket+1).toStdString()+subString;
        reserveCom1=reserveComNew;
        com="INSERT INTO "+nowct->clientName+" VALUES "+reserveCom1+infoMiddle+reserveCom2;
        query->exec(QString::fromStdString(com));
        //qDebug()<<QString::fromStdString(com);


        //set the seat condition in mysql

        com="SELECT * FROM seat_table"+string(" WHERE train_num=")+QString::number(tempTrainNumber).toStdString()+" and seat_code="+QString::number(seat).toStdString();
        query->exec(QString::fromStdString(com));
        query->next();
        string seatCondition=query->value(tempDateDiff+2).toString().toStdString();
        for(int i=0;i<destI-startI+1;i++){
            //bitwise operation
            seatCondition [startI+i]='n';
        }

        QString com2=QString("UPDATE seat_table")+(" SET code_date")+QString::number(tempDateDiff+1)+"='"+QString::fromStdString(seatCondition)+"' WHERE train_num="+QString::number(tempTrainNumber)+" and seat_code="+QString::number(seat);
        query->exec(com2);
        qDebug()<<com2;
        //qDebug()<<QString::fromStdString(com);

        ui->label_8->setText("Success");


        //refresh the seat content in combo box
        //***********************************************


        for(int i=0;i<carriageSeat_num;i++){
            carriageSeat[i].clear();
        }
        ui->comboBox_3->clear();
        for(int i=1;i<=currentCarriageNumber;i++){
            //put carriage number into combo box
            ui->comboBox_3->addItem(QString::number(i));
        }

        com="SELECT * FROM seat_table WHERE train_num="+QString::number(tempTrainNumber).toStdString()+"ORDER BY seat_code";
        query->exec(QString::fromStdString(com));
        while (query->next()){
            //show all valid seat number
            bool valid=true;
            double currentSeatNumber=query->value(1).toDouble();    //1.01,2.01

            string seatCondition=query->value(tempDateDiff+2).toString().toStdString();
            for(int i=0;i<destI-startI+1;i++){
                //bitwise operation
                if(seatCondition [startI+i]!='y'){
                    //not a valid seat
                    valid=false;
                    //qDebug()<<currentSeatNumber<<"******************";
                    break;
                }
            }
            if(valid==true){
                //valid seat
                int latterNumber=(int)(round((currentSeatNumber-(int)currentSeatNumber)*100));
                //qDebug()<<(currentSeatNumber-(int)currentSeatNumber)*100<<"******************";

                carriageSeat[(int)currentSeatNumber-1].push_back(latterNumber);
            }
        }
        //put valid seat into combo box
        ui->comboBox_4->clear();
        for(int i=0;i<(int)carriageSeat[0].size();i++){
            ui->comboBox_4->addItem(QString::number(carriageSeat[0][i]));
        }

        ui->pushButton_5->clicked();

        //**************************************************

    }
    else if(state==2){

        ui->calendarWidget->setDisabled(false);
        //temp set the seat free
        //if fail to  modify, show fail and recover the seat

        double NewtempSeat=ui->comboBox_3->currentText().toDouble()+((ui->comboBox_4->currentText().toDouble())/100.0);
        bool success=true;
        QString com;
        int dateDiff=tempSelectDate.toJulianDay()-today.toJulianDay();
        tempDateDiff=dateDiff;



        com="SELECT * FROM seat_table WHERE train_num="+QString::number(tempTrainNumber)+"and seat_code="+QString::number(tempSeat);
        query->exec(com);
        query->next();
        string seatCondition=query->value(tempSelectDate.toJulianDay()-today.toJulianDay()+2).toString().toStdString();
        //old seat condition
        string tempSeatCondition=seatCondition;
        //temperatry store the old seat condition

        if(ticketNumber<2){
            //temperary cancel
            cout<<startI<<"QQQ"<<destI<<endl;
            for(int i=0;i<destI-startI+1;i++){
                //bitwise operation
                seatCondition[startI+i]='y';

            }
            com="UPDATE seat_table"+QString(" SET code_date")+QString::number(tempSelectDate.toJulianDay()-today.toJulianDay()+1)+"='"+QString::fromStdString(seatCondition)+"'WHERE train_num="+QString::number(tempTrainNumber)+" and seat_code="+QString::number(tempSeat);
            query->exec(com);
        }



        //check whether it is ok to modify
        com=QString("SELECT * FROM seat_table")+" WHERE seat_code="+QString::number(NewtempSeat)+" and train_num="+QString::number(tempTrainNumber);
        query->exec(com);

        query->next();
        seatCondition=query->value(ui->calendarWidget->selectedDate().toJulianDay()-today.toJulianDay()+2).toString().toStdString();
        //new seat condition
        for(int i=0;i<modifyIndex2-modifyIndex1+1;i++){
            if(seatCondition[modifyIndex1+i]!='y'){
                success=false;
                qDebug()<<"fail to modify seat";
            }
        }
        if(success==true){
            if(ticketNumber<2){
                for(int i=0;i<modifyIndex2-modifyIndex1+1;i++){
                    seatCondition[modifyIndex1+i]='n';
                }
                com="UPDATE seat_table "+QString(" SET code_date")+QString::number(ui->calendarWidget->selectedDate().toJulianDay()-today.toJulianDay()+1)+"='"+QString::fromStdString(seatCondition)+"'WHERE train_num="+QString::number(tempTrainNumber)+" and seat_code="+QString::number(NewtempSeat);
                query->exec(com);
                //update seat in database
            }
            else{
                for(int j=0;j<ticketNumber;j++){

                    com=QString::fromStdString("SELECT * FROM "+nowct->clientName+" WHERE code=")+QString::number(tempCode);
                    query->exec(com);
                    query->next();
                    for(int k=0;k<j;k++){
                        query->next();
                    }
                    QString startLoc=query->value(1).toString();
                    QString destLoc=query->value(2).toString();
                    double nowSeat=query->value(4).toDouble();
                    qDebug()<<"seat : "<<nowSeat;
                    com="SELECT * FROM seat_table WHERE train_num="+QString::number(tempTrainNumber)+"and seat_code="+QString::number(nowSeat);
                    query->exec(com);
                    query->next();

                    string seatCondition=query->value(tempDateDiff+2).toString().toStdString();
                    int index1,index2;
                    stationToIndex(tempTrainNumber,index1,index2,startLoc,destLoc,query->value(6).toTime(),query->value(7).toTime());
                    cout<<index1<<"QQQQ"<<index2<<endl;
                    for(int i=0;i<index2-index1+1;i++){
                        seatCondition[index1+i]='y';
                    }

                    com="UPDATE seat_table"+QString(" SET code_date")+QString::number(tempDateDiff+1)+"='"+QString::fromStdString(seatCondition)+"' WHERE seat_code="+QString::number(nowSeat)+"and train_num="+QString::number(tempTrainNumber);
                    query->exec(com);

                }

                for(int i=0;i<modifyIndex2-modifyIndex1+1;i++){
                    seatCondition[modifyIndex1+i]='n';
                }
                com=QString("UPDATE seat_table")+" SET code_date"+QString::number(ui->calendarWidget->selectedDate().toJulianDay()-today.toJulianDay()+1)+"='"+QString::fromStdString(seatCondition)+"' WHERE seat_code="+QString::number(NewtempSeat)+"and train_num="+QString::number(tempTrainNumber);
                query->exec(com);
                //update seat in database
            }


            //success modify, modify client's tickets in database

            qDebug()<<com;
            int modifyC=tempCode;

            com=QString::fromStdString("UPDATE "+nowct->clientName+" SET code="+QString::number(modifyC+1).toStdString()+" WHERE code="+QString::number(tempCode).toStdString()+" AND startLocation='")+tempStart+"'";
            query->exec(com);

            com=QString::fromStdString("UPDATE "+nowct->clientName+" SET startLocation='")+ui->comboBox_10->currentText()+"' WHERE code="+QString::number(modifyC+1);
            query->exec(com);
            com=QString::fromStdString("UPDATE "+nowct->clientName+" SET destination='")+ui->comboBox_11->currentText()+"' WHERE code="+QString::number(modifyC+1);
            query->exec(com);
            com=QString::fromStdString("UPDATE "+nowct->clientName+" SET seatNumber=")+QString::number(NewtempSeat)+" WHERE code="+QString::number(modifyC+1);
            query->exec(com);
            com=QString("SELECT * FROM  (SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1)+")as a WHERE t_num=")+QString::number(tempTrainNumber);
            query->exec(com);
            QTime startT;
            QTime endT;
            QDate newQDate=ui->calendarWidget->selectedDate();
            int y=newQDate.year(),m=newQDate.month(),d=newQDate.day();
            string newDate=QString::number(y).toStdString()+"-"+QString::number(m).toStdString()+"-"+QString::number(d).toStdString();
            while(query->next()){
                if(query->value(1).toString()==ui->comboBox_10->currentText()){
                    startT=query->value(13).toTime();
                }
                else if(query->value(1).toString()==ui->comboBox_11->currentText()){
                    endT=query->value(12).toTime();
                }
            }

            com=QString::fromStdString("UPDATE "+nowct->clientName+" SET startTime='")+startT.toString()+"' WHERE code="+QString::number(modifyC+1);
            query->exec(com);
            com=QString::fromStdString("UPDATE "+nowct->clientName+" SET endTime='")+endT.toString()+"' WHERE code="+QString::number(modifyC+1);
            query->exec(com);
            com=QString::fromStdString("UPDATE "+nowct->clientName+" SET calendar='"+newDate+"' WHERE code=")+QString::number(modifyC+1);
            query->exec(com);

            //qDebug()<<QString::fromStdString(com);

        }
        else{
            com=QString("UPDATE seat_table")+" SET code_date"+QString::number(tempDateDiff+1)+"="+QString::fromStdString(tempSeatCondition)+" WHERE seat_code="+QString::number(tempSeat)+" and train_num="+QString::number(tempTrainNumber);
            query->exec(com);
            ui->label_12->setText("Fail to modify\nNo complete seat for your whole route");
            ui->label_12->show();
        }


        emit signal_updateTable();
        ui->pushButton_5->clicked();

    }
    else if(state==3){

        string com="SELECT * from "+nowct->clientName;
        query->exec(QString::fromStdString(com));

        while(query->next()){
            if(query->value(0).toString().toInt()==special.getCode()){
                //focus on the ticket
                QString identity=ui->comboBox_8->currentText();
                com="UPDATE "+nowct->clientName+" SET identity='"+identity.toStdString()+ "' WHERE code="+QString::number(special.getCode()).toStdString();
                query->exec(QString::fromStdString(com));

                int meatNumber=ui->spinBox_2->value();
                com="UPDATE "+nowct->clientName+" SET meat='"+QString::number(meatNumber).toStdString()+ "' WHERE code="+QString::number(special.getCode()).toStdString();
                query->exec(QString::fromStdString(com));

                int vegetableNumber=ui->spinBox_3->value();
                com="UPDATE "+nowct->clientName+" SET vegetable='"+QString::number(vegetableNumber).toStdString()+ "' WHERE code="+QString::number(special.getCode()).toStdString();
                query->exec(QString::fromStdString(com));

                if(ui->radioButton->isChecked()){
                    com="UPDATE "+nowct->clientName+" SET special=1 WHERE code="+QString::number(special.getCode()).toStdString();
                }
                else{
                    com="UPDATE "+nowct->clientName+" SET special=0 WHERE code="+QString::number(special.getCode()).toStdString();
                }
                query->exec(QString::fromStdString(com));

                emit signal_updateTable3();
                break;
            }
        }
        ui->pushButton_5->clicked();

    }
}


void Form::on_pushButton_5_clicked()//check
{

    double_state2=false;
    bug=0;
    ui->timeEdit->show();
    ui->label_12->hide();
    QTableWidgetItem *item;
    int row=ui->tableWidget_2->rowCount();
    //delete original item
    for(int i=0;i<row;i++){
        for(int j=0;j<col2;j++){
            item=ui->tableWidget_2->item(i,j);
            delete item;
        }
    }
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);


    emit signal_updateTable();




    state=4;
    _hideall();
    //process UI hide
    ui->label_2->hide();
    ui->label_3->show();
    ui->label_4->show();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_7->hide();
    ui->label_8->hide();
    ui->label_9->hide();
    //ui->calendarWidget->hide();
    //ui->comboBox->hide();
    //ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->comboBox_4->hide();
    //ui->comboBox_5->show();
    ui->spinBox->hide();
    //ui->pushButton_6->hide();
    //ui->pushButton_7->hide();
    ui->timeEdit->hide();
    ui->dateEdit->hide();

    //---------------------context------------------
    ui->label_2->setText("Tickets Code:");
    ui->label_8->clear();
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->comboBox_5->clear();
    ui->spinBox->clear();

    ui->comboBox->show();
    ui->comboBox_2->show();
    ui->comboBox_6->show();
    ui->comboBox_7->show();
    ui->tableWidget_2->show();
    ui->calendarWidget->show();
    ui->calendarWidget->setEnabled(true);
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_6->clear();
    ui->comboBox_7->clear();
    ui->tableWidget->hide();
    ui->tableWidget_2->show();
    ui->comboBox_6->show();
    ui->comboBox_7->show();
    ui->pushButton_8->hide();
    //let user select what kind of tickets they want to check
    //similar to taiwan railway website form
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_6->clear();
    ui->comboBox_7->clear();
    emit signal_initialFromToCity();

    ui->comboBox_5->setCurrentIndex(-1);
    ui->pushButton_11->show();
    ui->checkBox->show();
    ui->checkBox_2->show();
    ui->checkBox_3->show();
    ui->timeEdit->show();
    ui->label_3->setText("From");
    ui->label_4->setText("To");
}


void Form::showTable()
{
    /*
    query->exec("select * from timeTable");
    //display timeTable(simulation)
    //need to be changed to user firendly form
    ui->textEdit->clear();
    int count=-1;
    while(query->next()){
        count++;
        QString text;
        text=query->value(0).toString()+" ";
        text+=query->value(1).toString()+" ";
        text+=query->value(2).toString()+" ";
        text+=query->value(3).toString()+" ";
        text+=query->value(4).toString()+" ";
        text+=query->value(5).toString()+" ";
        //text+=query->value(6).toString()+" ";
        text+=query->value(8).toString()+" ";

        ui->textEdit->append(text);
    }


    query->exec("select * from timeNow");
    query->next();
    ui->label_9->setText(query->value(0).toTime().toString());
    */
}

void Form::slot_updateTable3()
{
    QTableWidgetItem *item;
    int count=0;
    string com;
    com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));
    while (query->next()) {
        count++;
    }
    ui->tableWidget_3->setRowCount(count);
    query->exec(QString::fromStdString(com));
    count=0;
    while(query->next()){
        //date
        QDate d=query->value(5).toDate();
        QString td;
        td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
        item=new QTableWidgetItem;
        item->setText(td);
        ui->tableWidget_3->setItem(count,0,item);


        //train type and number
        string text=query->value(8).toString().toStdString()+query->value(3).toString().toStdString();
        item=new QTableWidgetItem;
        item->setText(QString::fromStdString(text));
        ui->tableWidget_3->setItem(count,1,item);

        //start location
        text=query->value(1).toString().toStdString();
        item=new QTableWidgetItem;
        item->setText(QString::fromStdString(text));
        ui->tableWidget_3->setItem(count,2,item);

        //destination
        text=query->value(2).toString().toStdString();
        item=new QTableWidgetItem;
        item->setText(QString::fromStdString(text));
        ui->tableWidget_3->setItem(count,3,item);

        //depart time
        text=query->value(6).toString().toStdString();
        item=new QTableWidgetItem;
        item->setText(QString::fromStdString(text));
        ui->tableWidget_3->setItem(count,4,item);

        //arrival time
        text=query->value(7).toString().toStdString();
        item=new QTableWidgetItem;
        item->setText(QString::fromStdString(text));
        ui->tableWidget_3->setItem(count,5,item);

        //seat number
        text=query->value(4).toString().toStdString();
        item=new QTableWidgetItem;
        item->setText(QString::fromStdString(text));
        ui->tableWidget_3->setItem(count,6,item);

        //meat bento
        text=query->value(9).toString().toStdString();
        item=new QTableWidgetItem;
        item->setText(QString::fromStdString(text));
        ui->tableWidget_3->setItem(count,7,item);

        //vegetable bento
        text=query->value(10).toString().toStdString();
        item=new QTableWidgetItem;
        item->setText(QString::fromStdString(text));
        ui->tableWidget_3->setItem(count,8,item);

        //special serving
        int ss=query->value(11).toInt();
        if(ss==1){
            text="Yes";
        }
        else{
            text="No";
        }
        item=new QTableWidgetItem;
        item->setText(QString::fromStdString(text));
        ui->tableWidget_3->setItem(count,9,item);


        //identity
        text=query->value(12).toString().toStdString();
        item=new QTableWidgetItem;
        item->setText(QString::fromStdString(text));
        ui->tableWidget_3->setItem(count,10,item);


        text=query->value(0).toString().toStdString();
        item=new QTableWidgetItem;
        item->setText(QString::fromStdString(text));
        ui->tableWidget_3->setItem(count,11,item);


        count++;
    }

    if(ui->tableWidget_3->rowCount()!=0){
        int pred=-1;
        int loc=ui->tableWidget_3->item(0,11)->text().toInt();
        changeRowColor3(0);
        bool colorChange=true;  //store the state of the before one
        for(int i=1;i<ui->tableWidget_3->rowCount();i++){
            pred=loc;
            loc=ui->tableWidget_3->item(i,11)->text().toInt();
            if(pred==loc){
                if(colorChange==true){
                    changeRowColor3(i);
                }
            }
            else{
                if(colorChange==true){
                    colorChange=false;
                }
                else if(colorChange==false){
                    colorChange=true;
                    changeRowColor3(i);
                }
            }

        }
    }


}

void Form::slot_updateTable2()
{
    QTableWidgetItem *item;
    int count=0;
    QString com=QString::fromStdString("SELECT * FROM "+nowct->clientName);
    query->exec(com);
    ui->tableWidget_2->setRowCount(query->size());
    cout<<query->size()<<endl;
    count=0;
    while(query->next()){
        //date
        QDate d=query->value(5).toDate();
        QString td;
        td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
        item=new QTableWidgetItem;
        item->setText(td);
        ui->tableWidget_2->setItem(count,0,item);

        //train type and number
        QString text=query->value(8).toString()+query->value(3).toString();
        item=new QTableWidgetItem;
        item->setText(text);
        ui->tableWidget_2->setItem(count,1,item);

        type.push_back(query->value(8).toString());
        train_num.push_back(query->value(3).toString());
        //start location
        text=query->value(1).toString();
        item=new QTableWidgetItem;
        item->setText(text);
        ui->tableWidget_2->setItem(count,2,item);

        //destination
        text=query->value(2).toString();
        item=new QTableWidgetItem;
        item->setText(text);
        ui->tableWidget_2->setItem(count,3,item);

        //depart time
        text=query->value(6).toString();
        item=new QTableWidgetItem;
        item->setText(text);
        ui->tableWidget_2->setItem(count,4,item);

        //arrival time
        text=query->value(7).toString();
        item=new QTableWidgetItem;
        item->setText(text);
        ui->tableWidget_2->setItem(count,5,item);

        //seat number
        text=query->value(4).toString();
        item=new QTableWidgetItem;
        item->setText(text);
        ui->tableWidget_2->setItem(count,6,item);

        //meat bento
        text=query->value(9).toString();
        item=new QTableWidgetItem;
        item->setText(text);
        ui->tableWidget_2->setItem(count,7,item);

        //vegetable bento
        text=query->value(10).toString();
        item=new QTableWidgetItem;
        item->setText(text);
        ui->tableWidget_2->setItem(count,8,item);

        //special serving
        int ss=query->value(11).toInt();
        if(ss==1){
            text="Yes";
        }
        else{
            text="No";
        }
        item=new QTableWidgetItem;
        item->setText(text);
        ui->tableWidget_2->setItem(count,9,item);


        //identity
        text=query->value(12).toString();
        item=new QTableWidgetItem;
        item->setText(text);
        ui->tableWidget_2->setItem(count,10,item);


        text=query->value(0).toString();
        item=new QTableWidgetItem;
        item->setText(text);
        ui->tableWidget_2->setItem(count,11,item);


        count++;
    }

    if(ui->tableWidget_2->rowCount()!=0){
        int pred=-1;
        int loc=ui->tableWidget_2->item(0,11)->text().toInt();
        changeRowColor2(0);
        bool colorChange=true;  //store the state of the before one
        for(int i=1;i<ui->tableWidget_2->rowCount();i++){
            pred=loc;
            loc=ui->tableWidget_2->item(i,11)->text().toInt();
            if(pred==loc){
                if(colorChange==true){
                    changeRowColor2(i);
                }
            }
            else{
                if(colorChange==true){
                    colorChange=false;
                }
                else if(colorChange==false){
                    colorChange=true;
                    changeRowColor2(i);
                }
            }

        }
    }


}

void Form::slot_initialFromToCity()
{
    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox_6->clear();
    ui->comboBox_7->clear();
    query->exec("SELECT * FROM city");
    while(query->next()){
        QString temp=query->value(0).toString();
        ui->comboBox->addItem(temp);
        ui->comboBox_2->addItem(temp);
    }
    ui->comboBox->activated(0);
    ui->comboBox_2->activated(0);
    ui->comboBox_6->activated(0);
    ui->comboBox_7->activated(0);
}

QTime Form::timeDiff(QTime t1, QTime t2)
{
    //calculate the difference of two QTime
    int h1,h2,m1,m2,s1,s2;
    QTimeToInt(t1,h1,m1,s1);
    QTimeToInt(t2,h2,m2,s2);
    int h,m,s;
    if(s2-s1<0){
        m1++;
        s=s2+60-s1;
    }
    else{
        s=s2-s1;
    }
    if(m2-m1<0){
        h1++;
        m=m2+60-m1;
    }
    else{
        m=m2-m1;
    }
    h=h2-h1;
    QTime t;
    t.setHMS(h,m,s);
    return t;
}

void Form::QTimeToInt(QTime t, int &h, int &m, int &s)
{
    //convert QTime to three integer number
    //for the purpose of calculation
    string ts=t.toString().toStdString();
    string hs=ts.substr(0,2);
    h=stringToInt(hs);
    string ms=ts.substr(3,2);
    m=stringToInt(ms);
    string ss=ts.substr(6,2);
    s=stringToInt(ss);
}

int Form::stringToInt(string s)
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

void Form::indexToStation(const int number, int start, int end, QString &startS, QString &destS)
{

    QString com="SELECT station_c_n FROM(SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1)+")as a WHERE t_num="+QString::number(number);
    query->exec(com);
    int i=0;
    while(query->next()){
        if(i==start)
            startS=query->value(0).toString();
        if(end==start)
            destS=query->value(0).toString();
    }
}

void Form::stationToIndex(const int number, int &start, int &end, QString startS, QString destS,QTime dep,QTime arr)
{
    QString com="SELECT * FROM (SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1)+")as a WHERE t_num="+QString::number(number);
    query->exec(com);
    int count=0;
    while(query->next()){
        if(query->value(1).toString()==startS && query->value(13).toTime()==dep){
            start=count;
        }
        else if(query->value(1).toString()==destS&& query->value(12).toTime()==arr){
            end=count;
        }
        count++;
    }
}

void Form::changeRowColor2(int row)
{
    for(int i=0;i<col2;i++){
        QTableWidgetItem *item;
        item=ui->tableWidget_2->item(row,i);
        item->setBackground(QColor(220,220,220));
    }
}

void Form::changeRowColor3(int row)
{
    for(int i=0;i<col2;i++){
        QTableWidgetItem *item;
        item=ui->tableWidget_3->item(row,i);
        item->setBackground(QColor(220,220,220));
    }
}
void Form::client_table_create(){
    string data=" (code SERIAL,startLocation varchar(20),destination varchar(20),trainNumber INTEGER, seatNumber DOUBLE PRECISION,calendar DATE,startTime TIME,endTime TIME,trainType VARCHAR(20),meat VARCHAR(10), vegetable VARCHAR(10), special SMALLINT,identity VARCHAR(40),PRIMARY KEY (code))";
    QString com=QString::fromStdString("CREATE TABLE IF NOT EXISTS "+nowct->clientName+data);
    query->exec(com);
}

void Form::on_dateEdit_dateChanged(const QDate &date)
{
    ui->calendarWidget->setSelectedDate(date);
    ui->pushButton_8->clicked();
}

void Form::on_calendarWidget_selectionChanged()
{
    ui->dateEdit->setDate(ui->calendarWidget->selectedDate());
    ui->pushButton_8->clicked();
}

void Form::on_comboBox_5_textActivated(const QString &arg1)
{
    if(state==4){//check
        vector<Ticket>* a=nowct->gettickets();
        Ticket b;//choose now ticket
        for(int i=0;i<(int)a->size();i++){
            if((*a)[i].getCode()==arg1.toInt()){
                b=(*a)[i];
                break;
            }
        }
        //------------------UI Show----------------
        ui->label_2->show();//train code
        ui->label_3->show();//start point
        ui->label_4->show();//destination
        ui->label_5->show();//train number
        ui->label_6->show();//seat number
        ui->label_7->show();//time and date
        ui->label_8->show();//for the success or fail
        ui->label_9->hide();
        ui->calendarWidget->show();//for date choose
        ui->calendarWidget->setSelectedDate(QDate::currentDate());
        ui->dateEdit->show();
        ui->timeEdit->show();//for time choose
        //-------------------------context--------------------
        ui->label_2->setText("Ticket Code");
        ui->label_3->setText("From          "+(b.getStart()));
        ui->label_4->setText("TO            "+(b.getDest()));
        ui->label_5->setText("Train num     "+QString::number(b.getTrainNumber()));
        ui->label_6->setText("Seat num      "+QString::number(b.getSeatNumber()));
        ui->label_7->setText("Time          ");
        ui->calendarWidget->setSelectedDate(b.getTrainDate());
        ui->calendarWidget->setEnabled(false);
        ui->dateEdit->setDate(b.getTrainDate());
        ui->dateEdit->setEnabled(false);
        ui->timeEdit->setTime(b.getstartTime());
        ui->timeEdit->setEnabled(false);
    }
    else if(state==3){//other service

    }
    else if(state==2){//modify

    }

}

void Form::on_pushButton_7_clicked()
{
    int ticketNumber=0;
    string com="SELECT * FROM "+nowct->clientName+" WHERE code="+QString::number(tempCode).toStdString();
    query->exec(QString::fromStdString(com));
    ticketNumber=query->size();

    if(ticketNumber==1){
        com="DELETE FROM "+nowct->clientName+" WHERE code="+QString::number(tempCode).toStdString();
        query->exec(QString::fromStdString(com));

        com=string("SELECT * FROM seat_table")+" WHERE seat_code="+QString::number(tempSeat).toStdString()+"and train_num="+QString::number(tempTrainNumber).toStdString();
        query->exec(QString::fromStdString(com));
        query->next();
        string seatCondition=query->value(tempDateDiff+2).toString().toStdString();
        for(int i=0;i<destI-startI+1;i++){
            //bitwise operation
            seatCondition[startI+i]='y';

        }
        QString com2=QString("UPDATE seat_table")+" SET code_date"+QString::number(tempDateDiff+1)+"='"+QString::fromStdString(seatCondition)+"' WHERE seat_code="+QString::number(tempSeat)+" and train_num="+QString::number(tempTrainNumber);
        query->exec(com2);


    }
    else{
        qDebug()<<"number : "<<ticketNumber;
        for(int j=0;j<ticketNumber;j++){
            //qDebug()<<j;
            com="SELECT * FROM "+nowct->clientName+" WHERE code="+QString::number(tempCode).toStdString();
            query->exec(QString::fromStdString(com));
            query->next();
            for(int k=0;k<j;k++){
                query->next();
            }
            QString startLoc=query->value(1).toString();
            QString destLoc=query->value(2).toString();
            double nowSeat=query->value(4).toDouble();
            qDebug()<<"seat : "<<nowSeat;
            com=string("SELECT * FROM seat_table")+" WHERE seat_code="+QString::number(nowSeat).toStdString()+"and train_num="+QString::number(tempTrainNumber).toStdString();
            query->exec(QString::fromStdString(com));
            query->next();
            qDebug()<<"2212";
            string seatCondition=query->value(tempDateDiff+2).toString().toStdString();
            int index1,index2;
            stationToIndex(tempTrainNumber,index1,index2,startLoc,destLoc,query->value(6).toTime(),query->value(7).toTime());
            for(int i=0;i<index2-index1+1;i++){
                seatCondition[index1+i]='y';
            }
            com=string("SELECT * FROM seat_table")+ "WHERE seat_code="+QString::number(tempDateDiff+1).toStdString()+"and train_num="+QString::number(tempTrainNumber).toStdString();
            query->exec(QString::fromStdString(com));

        }
        com="DELETE FROM "+nowct->clientName+" WHERE code="+QString::number(tempCode).toStdString();
        query->exec(QString::fromStdString(com));


    }
    ui->pushButton_2->click();
}

QString change_time(QString o,int hrs,int minutes,int secs=0){
    if(o.size()!=8||o[2]!=':'||o[5]!=':')
        return o;
    string oo=o.toStdString();
    int get_hr=(oo[0]-'0')*10+(oo[1]-'0');
    int get_mi=(oo[3]-'0')*10+(oo[4]-'0');
    int get_se=(oo[6]-'0')*10+(oo[7]-'0');
    get_hr+=hrs;
    get_mi+=minutes;
    get_se+=secs;
    if(get_se>=60){
        get_mi+=get_se/60;
        get_se%=60;
    }
    if(get_mi>=60){
        get_hr+=get_mi/60;
        get_mi%=60;
    }
    if(get_hr>=24){
        get_hr%=24;
    }
    if(get_se<0){
        get_se+=60;
        get_mi-=1;
    }
    if(get_mi<0){
        get_mi+=60;
        get_hr-=1;
    }
    if(get_hr<0){
        get_hr+=24;
    }
    oo[0]=get_hr/10+'0';
    oo[1]=get_hr%10+'0';
    oo[3]=get_mi/10+'0';
    oo[4]=get_mi%10+'0';
    oo[6]=get_se/10+'0';
    oo[7]=get_se%10+'0';
    return QString::fromStdString(oo);
}

void Form::on_pushButton_8_clicked()
{


    //search button

    if(state==1){
        //search (for reverse)
        //search buttom
        //search by start locationand destination
        if((ui->comboBox_2->currentText()==ui->comboBox->currentText())&&(ui->comboBox_6->currentText()==ui->comboBox_7->currentText())){
            if(!bug){
                bug++;
            }
            else{
                //dia.s="Cannot set from and to the same place!";
                //dia.showerror();
                //dia.show();
            }
        }
        else{
            QDate selectDate=ui->calendarWidget->selectedDate();
            int dateDiff=selectDate.toJulianDay()-today.toJulianDay();
            tempDateDiff=dateDiff;
            if(dateDiff<0 || dateDiff>13){
                //ui->label_12->setText("You can only buy the tickets in two weeks");
                //ui->label_12->show();
                dia.s="You can only buy the tickets in two weeks";
                dia.showerror();
                dia.show();
                ui->tableWidget->setRowCount(0);
                return;
            }
            QString station1=ui->comboBox_6->currentText();
            QString station2=ui->comboBox_7->currentText();
            //all train number that can be searched
            qDebug()<<dateDiff;
            QString ask=ui->timeEdit->time().toString();
            QString com="SELECT DISTINCT t_nn,s_s,s_e,d_t,a_t,t_c_n,t_l,s_o,e_o FROM get_train('"+change_time(ask,0,-30)+"','"+change_time(ask,0,30)+"','"+station1+"','"+station2+"')"+" ,needed_train_info a WHERE t_nn=t_num";
            QString com2="SELECT DISTINCT t_nn,s_s,s_e,d_t,a_t,t_c_n,t_l,s_o,e_o FROM get_train2('"+change_time(ask,0,-30)+"','"+change_time(ask,0,30)+"','"+station1+"','"+station2+"')"+" ,needed_train_info"+QString::number(dateDiff+1)+" a WHERE t_nn=t_num";

            if(dateDiff==0){
                com+=" and d_t>'"+ui->timeEdit_2->time().toString()+"'";
                com2+=" and d_t>'"+ui->timeEdit_2->time().toString()+"'";
            }

            int row=ui->tableWidget->rowCount();
            QTableWidgetItem *item;
            //delete original item
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    item=ui->tableWidget->item(i,j);
                    delete item;
                }
            }
            //print data to table
            com+=" UNION "+com2;
            qDebug()<<com;
            query->exec(com);
            ui->tableWidget->clearContents();
            ui->tableWidget->setRowCount(query->size());
            int i=0;
            s_o.clear();
            e_o.clear();
            train_num.clear();
            type.clear();
            while(query->next()){
                item=new QTableWidgetItem;
                item->setText(query->value(3).toString());
                ui->tableWidget->setItem(i,0,item);
                //depart time
                item=new QTableWidgetItem;
                item->setText(query->value(4).toString());
                ui->tableWidget->setItem(i,1,item);
                //arrival time

                item=new QTableWidgetItem;
                QTime t;
                t=timeDiff(QTime::fromString(query->value(3).toString()),QTime::fromString(query->value(4).toString()));
                item->setText(t.toString());
                ui->tableWidget->setItem(i,2,item);
                //tour time

                item=new QTableWidgetItem;
                QString s=query->value(5).toString()+query->value(0).toString();
                item->setText(s);
                ui->tableWidget->setItem(i,3,item);
                //train type ans train number

                s=query->value(6).toString();
                if(s=="0"){
                    s="不經過山海線";
                }else if(s=="1"){
                    s="山線";
                }else if(s=="2"){
                    s="海線";
                }else if(s=="3"){
                    s="成追";
                }else if(s=="4"){
                    s="山海";
                }

                item=new QTableWidgetItem;
                item->setText(s);
                ui->tableWidget->setItem(i,4,item);
                //passing through

                item=new QTableWidgetItem;
                item->setText("BUY!");
                ui->tableWidget->setItem(i,5,item);
                //s_o and e_o
                s_o.push_back(query->value(7).toInt());
                e_o.push_back(query->value(8).toInt());
                //train_t
                train_num.push_back(query->value(0).toString());
                type.push_back(query->value(5).toString());
                //print buy text
                i++;
            }
        }
    }
    if(state==4 || state==2){
        if(state==2){
            ui->comboBox_7->show();
        }

        if((state==4 && !ui->checkBox->isChecked() && !ui->checkBox_2->isChecked() && !ui->checkBox_3->isChecked()) || state==2){
            //search (for check)
            QTableWidgetItem *item;
            int row=ui->tableWidget_2->rowCount();
            //delete original item
            for(int i=0;i<row;i++){
                for(int j=0;j<col2;j++){
                    item=ui->tableWidget_2->item(i,j);
                    delete item;
                }
            }
            ui->tableWidget_2->clearContents();

            QString startLocation=ui->comboBox_6->currentText();
            QString endLocation=ui->comboBox_7->currentText();
            QDate day=ui->calendarWidget->selectedDate();
            int dateDiff=day.toJulianDay()-today.toJulianDay();
            tempDateDiff=dateDiff;
            string com="SELECT * FROM "+nowct->clientName;
            query->exec(QString::fromStdString(com));

            vector <int> code;
            //the vector store the code of tickets that match the user request
            while(query->next()){
                if(query->value(1).toString()==startLocation){
                    if(query->value(2).toString()==endLocation){
                        if(query->value(5).toDate()==day){
                            //find the corresponding tickets
                            if(dateDiff==0){
                                if(query->value(7).toTime()<ui->timeEdit_2->time()){
                                    continue;
                                }
                                qDebug()<<query->value(7).toString()<<"AA"<<ui->timeEdit_2->time().toString();
                            }
                            code.push_back(query->value(0).toInt());
                        }
                    }
                }
            }
            vector <int> duplicatedCode;
            set <int> uniqueDuplicate;
            com="SELECT * FROM "+nowct->clientName;
            query->exec(QString::fromStdString(com));
            int pred=0;
            int loc=0;
            query->next();
            pred=query->value(0).toInt();
            while(query->next()){
                loc=query->value(0).toInt();
                if(loc==pred){
                    duplicatedCode.push_back(loc);
                    uniqueDuplicate.insert(loc);
                }
                pred=loc;
            }

            set <int> fitCode;
            for(set<int>::iterator itr=uniqueDuplicate.begin();itr!=uniqueDuplicate.end();itr++){
                QString command="SELECT * FROM ";
                command+=QString::fromStdString(nowct->clientName);
                command+=" WHERE code="+QString::number(*itr);
                query->exec(command);
                query->next();
                QString startL,destL;
                startL=query->value(1).toString();
                QDate dd=query->value(5).toDate();
                while(query->next()){
                    destL=query->value(2).toString();
                }
                if(startL==startLocation && destL==endLocation && dd==ui->calendarWidget->selectedDate()){
                    fitCode.insert(*itr);
                }
            }



            ui->tableWidget_2->setRowCount(code.size()+duplicatedCode.size()+uniqueDuplicate.size());
            int count=0;
            //print the tickets data into table
            train_num.clear();
            type.clear();
            for(int i=0;i<(int)code.size();i++){
                QString command="SELECT * FROM ";
                command+=QString::fromStdString(nowct->clientName);
                command+=" WHERE code="+QString::number(code[i]);
                query->exec(command);
                while(query->next()){
                    //date
                    QDate d=query->value(5).toDate();
                    QString td;
                    td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
                    item=new QTableWidgetItem;
                    item->setText(td);
                    ui->tableWidget_2->setItem(count,0,item);


                    //set type and number
                    item=new QTableWidgetItem;
                    QString text=query->value(8).toString();
                    text+=query->value(3).toString();
                    train_num.push_back(query->value(3).toString());
                    type.push_back(query->value(8).toString());

                    item->setText(text);
                    ui->tableWidget_2->setItem(count,1,item);

                    //set start location
                    item=new QTableWidgetItem;
                    item->setText(query->value(1).toString());
                    ui->tableWidget_2->setItem(count,2,item);

                    //set end location
                    item=new QTableWidgetItem;
                    item->setText(query->value(2).toString());
                    ui->tableWidget_2->setItem(count,3,item);

                    //set start time
                    item=new QTableWidgetItem;
                    item->setText(query->value(6).toString());
                    ui->tableWidget_2->setItem(count,4,item);

                    //set end time
                    item=new QTableWidgetItem;
                    item->setText(query->value(7).toString());
                    ui->tableWidget_2->setItem(count,5,item);

                    //set seat number
                    item=new QTableWidgetItem;
                    item->setText(query->value(4).toString());
                    ui->tableWidget_2->setItem(count,6,item);

                    //set meat bento
                    item=new QTableWidgetItem;
                    item->setText(query->value(9).toString());
                    ui->tableWidget_2->setItem(count,7,item);

                    //set vegetable bento
                    item=new QTableWidgetItem;
                    item->setText(query->value(10).toString());
                    ui->tableWidget_2->setItem(count,8,item);

                    //set special serving
                    int ss=query->value(11).toInt();
                    QString extraServing;
                    if(ss==1){
                        extraServing="Yes";
                    }
                    else{
                        extraServing="No";
                    }
                    item=new QTableWidgetItem;
                    item->setText(extraServing);
                    ui->tableWidget_2->setItem(count,9,item);

                    //set identity
                    item=new QTableWidgetItem;
                    item->setText(query->value(12).toString());
                    ui->tableWidget_2->setItem(count,10,item);

                    //code
                    item=new QTableWidgetItem;
                    item->setText(query->value(0).toString());
                    ui->tableWidget_2->setItem(count,11,item);

                    count++;
                }




            }

            int ii=0;
            for(set<int>::iterator itr=fitCode.begin();itr!=fitCode.end();itr++){
                QString command="SELECT * FROM ";
                command+=QString::fromStdString(nowct->clientName);
                command+=" WHERE code="+QString::number(*itr);
                query->exec(command);
                while(query->next()){
                    //date
                    QDate d=query->value(5).toDate();
                    QString td;
                    td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
                    item=new QTableWidgetItem;
                    item->setText(td);
                    ui->tableWidget_2->setItem(code.size()+ii,0,item);


                    //set type and number
                    item=new QTableWidgetItem;
                    QString text=query->value(8).toString();
                    text+=query->value(3).toString();
                    item->setText(text);
                    ui->tableWidget_2->setItem(code.size()+ii,1,item);

                    //set start location
                    item=new QTableWidgetItem;
                    item->setText(query->value(1).toString());
                    ui->tableWidget_2->setItem(code.size()+ii,2,item);

                    //set end location
                    item=new QTableWidgetItem;
                    item->setText(query->value(2).toString());
                    ui->tableWidget_2->setItem(code.size()+ii,3,item);

                    //set start time
                    item=new QTableWidgetItem;
                    item->setText(query->value(6).toString());
                    ui->tableWidget_2->setItem(code.size()+ii,4,item);

                    //set end time
                    item=new QTableWidgetItem;
                    item->setText(query->value(7).toString());
                    ui->tableWidget_2->setItem(code.size()+ii,5,item);

                    //set seat number
                    item=new QTableWidgetItem;
                    item->setText(query->value(4).toString());
                    ui->tableWidget_2->setItem(code.size()+ii,6,item);

                    //set meat bento
                    item=new QTableWidgetItem;
                    item->setText(query->value(9).toString());
                    ui->tableWidget_2->setItem(code.size()+ii,7,item);

                    //set vegetable bento
                    item=new QTableWidgetItem;
                    item->setText(query->value(10).toString());
                    ui->tableWidget_2->setItem(code.size()+ii,8,item);

                    //set special serving
                    int ss=query->value(11).toInt();
                    QString extraServing;
                    if(ss==1){
                        extraServing="Yes";
                    }
                    else{
                        extraServing="No";
                    }
                    item=new QTableWidgetItem;
                    item->setText(extraServing);
                    ui->tableWidget_2->setItem(code.size()+ii,9,item);

                    //set identity
                    item=new QTableWidgetItem;
                    item->setText(query->value(12).toString());
                    ui->tableWidget_2->setItem(code.size()+ii,10,item);

                    //code
                    item=new QTableWidgetItem;
                    item->setText(query->value(0).toString());
                    ui->tableWidget_2->setItem(code.size()+ii,11,item);

                    ii++;
                }
            }

            ui->tableWidget_2->setRowCount(count+ii);

            if(ui->tableWidget_2->rowCount()!=0){
                pred=-1;
                loc=ui->tableWidget_2->item(0,11)->text().toInt();
                changeRowColor2(0);
                bool colorChange=true;  //store the state of the before one
                for(int i=1;i<ui->tableWidget_2->rowCount();i++){
                    pred=loc;
                    loc=ui->tableWidget_2->item(i,11)->text().toInt();
                    if(pred==loc){
                        if(colorChange==true){
                            changeRowColor2(i);
                        }
                    }
                    else{
                        if(colorChange==true){
                            colorChange=false;
                        }
                        else if(colorChange==false){
                            colorChange=true;
                            changeRowColor2(i);
                        }
                    }

                }
            }


        }
        else if(ui->checkBox->isChecked() && !ui->checkBox_2->isChecked() && !ui->checkBox_3->isChecked()){
            checkLocation();
        }
        else if(!ui->checkBox->isChecked() && ui->checkBox_2->isChecked() && !ui->checkBox_3->isChecked()){
            checkDate();
        }
        else if(!ui->checkBox->isChecked() && !ui->checkBox_2->isChecked() && ui->checkBox_3->isChecked()){
            checkTime();
        }
        else if(!ui->checkBox->isChecked() && ui->checkBox_2->isChecked() && ui->checkBox_3->isChecked()){
            checkTimeDate();
        }
        else if(ui->checkBox->isChecked() && !ui->checkBox_2->isChecked() && ui->checkBox_3->isChecked()){
            checkLocTime();
        }
        else if(ui->checkBox->isChecked() && ui->checkBox_2->isChecked() && ui->checkBox_3->isChecked()){
            checkLocDateTime();
        }

    }
    if(state==3){
        //search (for other serving)
        QTableWidgetItem *item;
        int row=ui->tableWidget_3->rowCount();
        //delete original item
        for(int i=0;i<row;i++){
            for(int j=0;j<col2;j++){
                item=ui->tableWidget_3->item(i,j);
                delete item;
            }
        }
        ui->tableWidget_3->clearContents();
        QString startLocation;
        QString endLocation;
        QDate day;
        //if(clickedSearch==true){
        //ckick search
        //need to follow combobox
        startLocation=ui->comboBox_6->currentText();
        endLocation=ui->comboBox_7->currentText();
        day=ui->calendarWidget->selectedDate();
        //}
        /*else{
            //directly double clicked
            QString startLocation=QString::fromStdString(tempStart);
            QString endLocation=QString::fromStdString(tempDest);
            day=tempSelectDate;

        }*/
        clickedSearch=true;

        string com="SELECT * FROM "+nowct->clientName;
        query->exec(QString::fromStdString(com));

        vector <int> code;
        //the vector store the code of tickets that match the user request
        while(query->next()){
            if(query->value(1).toString()==startLocation){
                if(query->value(2).toString()==endLocation){
                    if(query->value(5).toDate()==day){
                        //find the corresponding tickets
                        code.push_back(query->value(0).toInt());
                    }
                }
            }
        }



        vector <int> duplicatedCode;
        set <int> uniqueDuplicate;
        com="SELECT * FROM "+nowct->clientName;
        query->exec(QString::fromStdString(com));
        int pred=0;
        int loc=0;
        query->next();
        pred=query->value(0).toInt();
        while(query->next()){
            loc=query->value(0).toInt();
            if(loc==pred){
                duplicatedCode.push_back(loc);
                uniqueDuplicate.insert(loc);
            }
            pred=loc;
        }


        set <int> fitCode;
        for(set<int>::iterator itr=uniqueDuplicate.begin();itr!=uniqueDuplicate.end();itr++){
            QString command="SELECT * FROM ";
            command+=QString::fromStdString(nowct->clientName);
            command+=" WHERE code="+QString::number(*itr);
            query->exec(command);
            query->next();
            string startL,destL;
            startL=query->value(1).toString().toStdString();
            while(query->next()){
                destL=query->value(2).toString().toStdString();
            }
            if(startL==startLocation.toStdString() && destL==endLocation.toStdString()){
                fitCode.insert(*itr);

            }
        }



        ui->tableWidget_3->setRowCount(code.size()+duplicatedCode.size()+uniqueDuplicate.size());




        //ui->tableWidget_3->setRowCount(code.size());

        //print the tickets data into table
        train_num.clear();
        type.clear();
        for(int i=0;i<(int)code.size();i++){
            QString command="SELECT * FROM ";
            command+=QString::fromStdString(nowct->clientName);
            command+=" WHERE code="+QString::number(code[i]);
            query->exec(command);
            query->next();

            //date
            item=new QTableWidgetItem;
            QString text=query->value(5).toString();
            item->setText(text);
            ui->tableWidget_3->setItem(i,0,item);

            //set type and number
            item=new QTableWidgetItem;
            text=query->value(8).toString();
            text+=query->value(3).toString();
            item->setText(text);
            ui->tableWidget_3->setItem(i,1,item);
            type.push_back(query->value(8).toString());
            train_num.push_back(query->value(3).toString());

            //set start location
            item=new QTableWidgetItem;
            item->setText(startLocation);
            ui->tableWidget_3->setItem(i,2,item);

            //set end location
            item=new QTableWidgetItem;
            item->setText(endLocation);
            ui->tableWidget_3->setItem(i,3,item);

            //set start time
            item=new QTableWidgetItem;
            item->setText(query->value(6).toString());
            ui->tableWidget_3->setItem(i,4,item);

            //set end time
            item=new QTableWidgetItem;
            item->setText(query->value(7).toString());
            ui->tableWidget_3->setItem(i,5,item);

            //set seat number
            item=new QTableWidgetItem;
            item->setText(query->value(4).toString());
            ui->tableWidget_3->setItem(i,6,item);

            //set bento meat
            item=new QTableWidgetItem;
            item->setText(query->value(9).toString());
            ui->tableWidget_3->setItem(i,7,item);

            //set bento vegetable
            item=new QTableWidgetItem;
            item->setText(query->value(10).toString());
            ui->tableWidget_3->setItem(i,8,item);

            //set special care
            item=new QTableWidgetItem;
            int special=query->value(11).toInt();
            QString temp="No";
            if(special==1){
                temp="Yes";
            }
            else if(special==0){
                temp="No";
            }
            item->setText(temp);
            ui->tableWidget_3->setItem(i,9,item);

            //set identity
            item=new QTableWidgetItem;
            item->setText(query->value(12).toString());
            ui->tableWidget_3->setItem(i,10,item);

            //code
            item=new QTableWidgetItem;
            item->setText(query->value(0).toString());
            ui->tableWidget_3->setItem(i,11,item);

        }


        int ii=0;
        for(set<int>::iterator itr=fitCode.begin();itr!=fitCode.end();itr++){
            QString command="SELECT * FROM ";
            command+=QString::fromStdString(nowct->clientName);
            command+=" WHERE code="+QString::number(*itr);
            query->exec(command);
            while(query->next()){
                //date
                QDate d=query->value(5).toDate();
                QString td;
                td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
                item=new QTableWidgetItem;
                item->setText(td);
                ui->tableWidget_3->setItem(code.size()+ii,0,item);


                //set type and number
                item=new QTableWidgetItem;
                QString text=query->value(8).toString();
                text+=query->value(3).toString();
                item->setText(text);
                ui->tableWidget_3->setItem(code.size()+ii,1,item);
                type.push_back(query->value(8).toString());
                train_num.push_back(query->value(3).toString());
                //set start location
                item=new QTableWidgetItem;
                item->setText(query->value(1).toString());
                ui->tableWidget_3->setItem(code.size()+ii,2,item);

                //set end location
                item=new QTableWidgetItem;
                item->setText(query->value(2).toString());
                ui->tableWidget_3->setItem(code.size()+ii,3,item);

                //set start time
                item=new QTableWidgetItem;
                item->setText(query->value(6).toString());
                ui->tableWidget_3->setItem(code.size()+ii,4,item);

                //set end time
                item=new QTableWidgetItem;
                item->setText(query->value(7).toString());
                ui->tableWidget_3->setItem(code.size()+ii,5,item);

                //set seat number
                item=new QTableWidgetItem;
                item->setText(query->value(4).toString());
                ui->tableWidget_3->setItem(code.size()+ii,6,item);

                //set meat bento
                item=new QTableWidgetItem;
                item->setText(query->value(9).toString());
                ui->tableWidget_3->setItem(code.size()+ii,7,item);

                //set vegetable bento
                item=new QTableWidgetItem;
                item->setText(query->value(10).toString());
                ui->tableWidget_3->setItem(code.size()+ii,8,item);

                //set special serving
                int ss=query->value(11).toInt();
                QString extraServing;
                if(ss==1){
                    extraServing="Yes";
                }
                else{
                    extraServing="No";
                }
                item=new QTableWidgetItem;
                item->setText(extraServing);
                ui->tableWidget_3->setItem(code.size()+ii,9,item);

                //set identity
                item=new QTableWidgetItem;
                item->setText(query->value(12).toString());
                ui->tableWidget_3->setItem(code.size()+ii,10,item);

                //code
                item=new QTableWidgetItem;
                item->setText(query->value(0).toString());
                ui->tableWidget_3->setItem(code.size()+ii,11,item);

                ii++;
            }
        }
        ui->tableWidget_3->setRowCount(code.size()+ii);

        if(ui->tableWidget_3->rowCount()!=0){
            pred=-1;
            qDebug()<<"66";
            qDebug()<<ui->tableWidget_3->item(0,10)->text();
            loc=ui->tableWidget_3->item(0,11)->text().toInt();
            qDebug()<<"99";
            changeRowColor3(0);
            bool colorChange=true;  //store the state of the before one
            for(int i=1;i<ui->tableWidget_3->rowCount();i++){
                pred=loc;
                loc=ui->tableWidget_3->item(i,11)->text().toInt();
                if(pred==loc){
                    if(colorChange==true){
                        changeRowColor3(i);
                    }
                }
                else{
                    if(colorChange==true){
                        colorChange=false;
                    }
                    else if(colorChange==false){
                        colorChange=true;
                        changeRowColor3(i);
                    }
                }

            }
        }
    }

}




void Form::on_comboBox_8_currentIndexChanged(int index)
{
    if(state==3){
        QString com2=QString("SELECT DISTINCT bf,food,crp FROM(SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1)+")as a WHERE t_num=")+QString::number(tempTrainNumber);
        qDebug()<<com2;
        query->exec(com2);
        query->next();
        bool pre=(query->value(0).toString()=="Y"?true:false);
        bool bento=(query->value(1).toString()=="Y"?true:false);
        bool eld=(query->value(2).toString()=="Y"?true:false);
        rl.stop();
        ui->label_7->hide();
        ui->pushButton_6->hide();
        ui->graphicsView->hide();
        ui->label_9->hide();

        ui->groupBox->hide();
        ui->radioButton->hide();
        ui->radioButton_2->hide();
        if(index==0){
            ui->label_10->hide();
            ui->spinBox_2->hide();
            ui->spinBox_3->hide();
            ui->comboBox_9->clear();
            if(bento)
                ui->comboBox_9->addItem("Bento");
            ui->comboBox_9->setCurrentIndex(-1);
        }
        else{

            ui->label_10->hide();
            ui->spinBox_2->hide();
            ui->spinBox_3->hide();
            ui->comboBox_9->clear();
            if((ui->comboBox_8->currentText()!="Pregnant"&&ui->comboBox_8->currentText()!="Elder")||(ui->comboBox_8->currentText()=="Pregnant"&&pre)||(ui->comboBox_8->currentText()=="Elder"&&eld))
            ui->comboBox_9->addItem("Special Care");

            if(bento)
            ui->comboBox_9->addItem("Bento");
            ui->comboBox_9->setCurrentIndex(-1);
        }
    }
}





void Form::on_pushButton_9_clicked()
{
    ui->calendarWidget->setDisabled(true);
    ui->comboBox_3->show();
    ui->comboBox_4->show();
    ui->label_5->show();
    ui->label_6->show();



    string com;


    com="SELECT * FROM(SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1).toStdString()+")as a WHERE t_num="+QString::number(tempTrainNumber).toStdString()+" ORDER BY num_order";
    qDebug()<<QString::fromStdString(com);
    query->exec(QString::fromStdString(com));
    QString startStop=ui->comboBox_10->currentText();
    QString destStop=ui->comboBox_11->currentText();

    //new ticket start and destination index
    int startIndex=-1;
    int destIndex=-1;
    int count=0;
    while(query->next()){
        if(query->value(1).toString()==startStop){
            startIndex=count;
            modifyIndex1=count;
            count++;
            continue;
        }
        if(query->value(1).toString()==destStop){
            destIndex=count;
            modifyIndex2=destIndex;
            break;
        }
        count++;
    }
    if(startIndex==-1 || destIndex==-1){
        qDebug()<<"ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        qDebug()<<"line 2638";
    }


    com="SELECT * FROM (SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1).toStdString()+")as a WHERE t_num="+QString::number(tempTrainNumber).toStdString()+" ORDER BY num_order";
    query->exec(QString::fromStdString(com));

    count=0;
    while(query->next()){
        if(query->value(1).toString()==tempStart){
            startIndex=count;
            startI=count;
            count++;
            continue;
        }
        if(query->value(1).toString()==tempDest){
            destIndex=count;
            destI=count;
            break;
        }
        count++;
    }






    for(int i=0;i<carriageSeat_num;i++){
        carriageSeat[i].clear();
    }


    ui->comboBox_3->clear();
    for(int i=0;i<currentCarriageNumber;i++){
        //put carriage number into combo box
        ui->comboBox_3->addItem(QString::number(i+1));
    }



    com="SELECT * FROM seat_table WHERE train_num="+QString::number(tempTrainNumber).toStdString()+" and seat_code="+QString::number(tempSeat).toStdString();
    query->exec(QString::fromStdString(com));
    query->next();
    string seatCondition=query->value(tempSelectDate.toJulianDay()-today.toJulianDay()+2).toString().toStdString();
    //old seat condition
    string tempSeatCondition=seatCondition;
    //temperatry store the old seat condition


    if(ticketNumber<2){
        //temperary cancel
        for(int i=0;i<destI-startI+1;i++){
            //bitwise operation
            seatCondition[startI+i]='y';
        }
        //qDebug()<<startI<<destI;
        QString com2=QString("UPDATE seat_table")+" SET code_date"+QString::number(tempSelectDate.toJulianDay()-today.toJulianDay()+1)+"='"+QString::fromStdString(seatCondition)+"' WHERE seat="+QString::number(tempSeat)+" and train_num="+QString::number(tempTrainNumber);
        query->exec(com2);
    }

    com="SELECT * FROM (SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1).toStdString()+")as a WHERE t_num="+QString::number(tempTrainNumber).toStdString()+" ORDER BY num_order";
    query->exec(QString::fromStdString(com));
    while(query->next()){
        if(query->value(1).toString()==ui->comboBox_10->currentText()){
            startIndex=query->value(4).toInt()-1;
            continue;
        }
        if(query->value(1).toString()==ui->comboBox_11->currentText()){
            destIndex=query->value(4).toInt()-1;
            break;
        }
    }

    com="SELECT * FROM seat_table WHERE train_num="+QString::number(tempTrainNumber).toStdString()+"ORDER BY seat_code";
    query->exec(QString::fromStdString(com));
    while (query->next()){
        //show all valid seat number
        bool valid=true;
        double currentSeatNumber=query->value(1).toDouble();    //1.01,2.01

        seatCondition=query->value(ui->calendarWidget->selectedDate().toJulianDay()-today.toJulianDay()+2).toString().toStdString();
        for(int i=0;i<destIndex-startIndex+1;i++){
            //bitwise operation
            if(seatCondition[startIndex+i]!='y'){
                //not a valid seat
                valid=false;
                //qDebug()<<currentCarriageNumber<<"..............."<<00;
                break;
            }
        }
        if(valid==true){
            //valid seat
            int latterNumber=(int)(round((currentSeatNumber-(int)currentSeatNumber)*100));
            //qDebug()<<(currentSeatNumber-(int)currentSeatNumber)*100<<"******************";

            carriageSeat[(int)currentSeatNumber-1].push_back(latterNumber);
        }
    }
    //put valid seat into combo box
    ui->comboBox_4->clear();
    for(int i=0;i<(int)carriageSeat[0].size();i++){
        ui->comboBox_4->addItem(QString::number(carriageSeat[0][i]));
    }


    if(ticketNumber<2){
        //re reserve the ticket
        QString com2=QString("UPDATE seat_table")+" SET code_date"+QString::number(tempDateDiff+1)+"="+QString::fromStdString(tempSeatCondition)+" WHERE seat="+QString::number(tempSeat)+" and train_num="+QString::number(tempTrainNumber);
        query->exec(com2);
    }


}

void Form::on_pushButton_10_clicked()
{
    string infoMiddle=QString::number(discreateSeat[0]).toStdString()+",";
    string com;
    com="INSERT INTO "+nowct->clientName+" VALUES "+reserveCom1+infoMiddle+reserveCom2;
    qDebug()<<QString::fromStdString(com);
    query->exec(QString::fromStdString(com));
    com="SELECT * FROM seat_table WHERE train_num="+QString::number(tempTrainNumber).toStdString()+" and seat_code="+QString::number(discreateSeat[0]).toStdString();
    query->exec(QString::fromStdString(com));
    query->next();
    string seatCondition=query->value(tempDateDiff+2).toString().toStdString();
    for(int i=fromIndex[0];i<=toIndex[0];i++){
        seatCondition=seatCondition [i]='n';
    }
    QString com2="UPDATE seat_table  SET code_date"+QString::number(tempDateDiff+1)+"='"+QString::fromStdString(seatCondition)+"' WHERE train_num="+QString::number(tempTrainNumber)+" and  seat_code="+QString::number(discreateSeat[0]);
    query->exec(com2);

    if(discreateSeat.size()>=2){
        string infoMiddle=QString::number(discreateSeat[1]).toStdString()+",";
        string com;
        com="INSERT INTO "+nowct->clientName+" VALUES "+reserveCom12+infoMiddle+reserveCom2;
        qDebug()<<QString::fromStdString(com);
        query->exec(QString::fromStdString(com));
        com="SELECT * FROM seat_table WHERE train_num="+QString::number(tempTrainNumber).toStdString()+" and seat_code="+QString::number(discreateSeat[1]).toStdString();
        query->exec(QString::fromStdString(com));
        query->next();
        seatCondition=query->value(tempDateDiff+2).toString().toStdString();
        for(int i=fromIndex[1];i<=toIndex[1];i++){
            seatCondition=seatCondition [i]='n';
        }
        com2="UPDATE seat_table  SET code_date"+QString::number(tempDateDiff+1)+"='"+QString::fromStdString(seatCondition)+"' WHERE train_num="+QString::number(tempTrainNumber)+" and  seat_code="+QString::number(discreateSeat[1]);
        query->exec(com2);
        if(discreateSeat.size()>=3){
            string infoMiddle=QString::number(discreateSeat[2]).toStdString()+",";
            string com;
            com="INSERT INTO "+nowct->clientName+" VALUES "+reserveCom13+infoMiddle+reserveCom2;
            qDebug()<<QString::fromStdString(com);
            query->exec(QString::fromStdString(com));
            com="SELECT * FROM seat_table WHERE train_num="+QString::number(tempTrainNumber).toStdString()+" and seat_code="+QString::number(discreateSeat[2]).toStdString();
            query->exec(QString::fromStdString(com));
            query->next();
            seatCondition=query->value(tempDateDiff+2).toString().toStdString();
            for(int i=fromIndex[2];i<=toIndex[2];i++){
                seatCondition [i]='n';
            }
            qDebug()<<"3964";
            com2="UPDATE seat_table  SET code_date"+QString::number(tempDateDiff+1)+"='"+QString::fromStdString(seatCondition)+"' WHERE train_num="+QString::number(tempTrainNumber)+" and  seat_code="+QString::number(discreateSeat[2]);
            query->exec(com2);
        }
    }
    ui->pushButton_10->hide();
    ui->label_13->hide();
    ui->comboBox_3->show();
    ui->comboBox_4->show();
    ui->pushButton_6->show();
    ui->label_5->show();
    ui->label_6->show();
}




void Form::on_comboBox_6_activated(int index)
{
    QColor c=(ui->comboBox_6->itemData(index)).value<QColor>();
    if(c==Qt::red){

        ui->comboBox_6->findChild<QLineEdit*>()->setStyleSheet("color: red;");
    }
    else{
        ui->comboBox_6->findChild<QLineEdit*>()->setStyleSheet("color: black;");
    }
    index=-1;
    if(ui->comboBox->currentText()==ui->comboBox_2->currentText()){
        for(int i=0;i<ui->comboBox_6->count();i++){
            if(ui->comboBox_6->itemText(i)==ui->comboBox_7->currentText())
                index=i;
            if(ui->comboBox_7->findText(ui->comboBox_6->itemText(i))==-1){
                ui->comboBox_7->addItem(ui->comboBox_6->itemText(i));
            }
        }
        for(int i=0;i<ui->comboBox_7->count();i++)
            if(ui->comboBox_7->itemText(i)==ui->comboBox_6->currentText()){
                ui->comboBox_7->removeItem(i);
            }
        if(index!=-1){
            ui->comboBox_6->removeItem(index);
            QString com="SELECT DISTINCT chinese_name FROM train_station_code_2 WHERE related_city='"+ui->comboBox->currentText()+(QString)"'";
            query->exec(com);
            while(query->next()){
                if(query->value(0).toString()==ui->comboBox_7->currentText())
                    continue;
                if(ui->comboBox_6->findText(query->value(0).toString())==-1)
                    ui->comboBox_6->addItem(query->value(0).toString());
            }
        }



        ui->pushButton_8->clicked();
    }

    if(state==4|| state==3){
        ui->pushButton_8->click();
    }
}

void Form::on_comboBox_7_activated(int index)
{
    QColor c=(ui->comboBox_7->itemData(index)).value<QColor>();
    if(c==Qt::red){

        ui->comboBox_7->findChild<QLineEdit*>()->setStyleSheet("color: red;");
    }
    else{
        ui->comboBox_7->findChild<QLineEdit*>()->setStyleSheet("color: black;");
    }
    index=-1;
    if(ui->comboBox->currentText()==ui->comboBox_2->currentText()){
        for(int i=0;i<ui->comboBox_7->count();i++){
            if(ui->comboBox_7->itemText(i)==ui->comboBox_6->currentText()){
                index=i;
            }
            if(ui->comboBox_6->findText(ui->comboBox_7->itemText(i))==-1){
                ui->comboBox_6->addItem(ui->comboBox_7->itemText(i));
            }
        }
        for(int i=0;i<ui->comboBox_6->count();i++)
            if(ui->comboBox_6->itemText(i)==ui->comboBox_7->currentText()){
                ui->comboBox_6->removeItem(i);
            }
        if(index!=-1){
            ui->comboBox_7->removeItem(index);
            QString com="SELECT DISTINCT chinese_name FROM train_station_code_2 WHERE related_city='"+ui->comboBox->currentText()+(QString)"'";
            query->exec(com);

            ui->pushButton_8->clicked();
            while(query->next()){
                if(query->value(0).toString()==ui->comboBox_6->currentText())
                    continue;
                if(ui->comboBox_7->findText(query->value(0).toString())==-1)
                    ui->comboBox_7->addItem(query->value(0).toString());
            }
        }



        ui->pushButton_8->clicked();
    }
    if(state==4|| state==3){
        ui->pushButton_8->click();
    }
}

void Form::on_pushButton_11_clicked()
{
    emit signal_updateTable();
}

void Form::checkLocation()
{

    ui->tableWidget_2->clearContents();
    QString startLocation=ui->comboBox_6->currentText();
    QString endLocation=ui->comboBox_7->currentText();
    string com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));

    vector <int> code;
    //the vector store the code of tickets that match the user request
    while(query->next()){
        if(query->value(1).toString()==startLocation){
            if(query->value(2).toString()==endLocation){
                //find the corresponding tickets
                code.push_back(query->value(0).toInt());
            }
        }
    }

    vector <int> duplicatedCode;
    set <int> uniqueDuplicate;
    com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));
    int pred=0;
    int loc=0;
    query->next();
    pred=query->value(0).toInt();
    while(query->next()){
        loc=query->value(0).toInt();
        if(loc==pred){
            duplicatedCode.push_back(loc);
            uniqueDuplicate.insert(loc);
        }
        pred=loc;
    }


    set <int> fitCode;
    for(set<int>::iterator itr=uniqueDuplicate.begin();itr!=uniqueDuplicate.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        query->next();
        QString startL,destL;
        startL=query->value(1).toString();
        while(query->next()){
            destL=query->value(2).toString();
        }
        if(startL==startLocation && destL==endLocation){
            fitCode.insert(*itr);
        }
    }

    ui->tableWidget_2->setRowCount(code.size()+duplicatedCode.size()+uniqueDuplicate.size());


    int count=0;

    QTableWidgetItem *item;
    for(int i=0;i<(int)code.size();i++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(code[i]);
        query->exec(command);
        while(query->next()){
            //date
            QDate d=query->value(5).toDate();
            QString td;
            td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
            item=new QTableWidgetItem;
            item->setText(td);
            ui->tableWidget_2->setItem(count,0,item);


            //set type and number
            item=new QTableWidgetItem;
            QString text=query->value(8).toString();
            text+=query->value(3).toString();
            item->setText(text);
            ui->tableWidget_2->setItem(count,1,item);

            //set start location
            item=new QTableWidgetItem;
            item->setText(query->value(1).toString());
            ui->tableWidget_2->setItem(count,2,item);

            //set end location
            item=new QTableWidgetItem;
            item->setText(query->value(2).toString());
            ui->tableWidget_2->setItem(count,3,item);

            //set start time
            item=new QTableWidgetItem;
            item->setText(query->value(6).toString());
            ui->tableWidget_2->setItem(count,4,item);

            //set end time
            item=new QTableWidgetItem;
            item->setText(query->value(7).toString());
            ui->tableWidget_2->setItem(count,5,item);

            //set seat number
            item=new QTableWidgetItem;
            item->setText(query->value(4).toString());
            ui->tableWidget_2->setItem(count,6,item);

            //set meat bento
            item=new QTableWidgetItem;
            item->setText(query->value(9).toString());
            ui->tableWidget_2->setItem(count,7,item);

            //set vegetable bento
            item=new QTableWidgetItem;
            item->setText(query->value(10).toString());
            ui->tableWidget_2->setItem(count,8,item);

            //set special serving
            int ss=query->value(11).toInt();
            QString extraServing;
            if(ss==1){
                extraServing="Yes";
            }
            else{
                extraServing="No";
            }
            item=new QTableWidgetItem;
            item->setText(extraServing);
            ui->tableWidget_2->setItem(count,9,item);

            //set identity
            item=new QTableWidgetItem;
            item->setText(query->value(12).toString());
            ui->tableWidget_2->setItem(count,10,item);

            //code
            item=new QTableWidgetItem;
            item->setText(query->value(0).toString());
            ui->tableWidget_2->setItem(count,11,item);

            count++;
        }



    }

    int ii=0;
    for(set<int>::iterator itr=fitCode.begin();itr!=fitCode.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        while(query->next()){
            //date
            QDate d=query->value(5).toDate();
            QString td;
            td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
            item=new QTableWidgetItem;
            item->setText(td);
            ui->tableWidget_2->setItem(code.size()+ii,0,item);


            //set type and number
            item=new QTableWidgetItem;
            QString text=query->value(8).toString();
            text+=query->value(3).toString();
            item->setText(text);
            ui->tableWidget_2->setItem(code.size()+ii,1,item);

            //set start location
            item=new QTableWidgetItem;
            item->setText(query->value(1).toString());
            ui->tableWidget_2->setItem(code.size()+ii,2,item);

            //set end location
            item=new QTableWidgetItem;
            item->setText(query->value(2).toString());
            ui->tableWidget_2->setItem(code.size()+ii,3,item);

            //set start time
            item=new QTableWidgetItem;
            item->setText(query->value(6).toString());
            ui->tableWidget_2->setItem(code.size()+ii,4,item);

            //set end time
            item=new QTableWidgetItem;
            item->setText(query->value(7).toString());
            ui->tableWidget_2->setItem(code.size()+ii,5,item);

            //set seat number
            item=new QTableWidgetItem;
            item->setText(query->value(4).toString());
            ui->tableWidget_2->setItem(code.size()+ii,6,item);

            //set meat bento
            item=new QTableWidgetItem;
            item->setText(query->value(9).toString());
            ui->tableWidget_2->setItem(code.size()+ii,7,item);

            //set vegetable bento
            item=new QTableWidgetItem;
            item->setText(query->value(10).toString());
            ui->tableWidget_2->setItem(code.size()+ii,8,item);

            //set special serving
            int ss=query->value(11).toInt();
            QString extraServing;
            if(ss==1){
                extraServing="Yes";
            }
            else{
                extraServing="No";
            }
            item=new QTableWidgetItem;
            item->setText(extraServing);
            ui->tableWidget_2->setItem(code.size()+ii,9,item);

            //set identity
            item=new QTableWidgetItem;
            item->setText(query->value(12).toString());
            ui->tableWidget_2->setItem(code.size()+ii,10,item);

            //code
            item=new QTableWidgetItem;
            item->setText(query->value(0).toString());
            ui->tableWidget_2->setItem(code.size()+ii,11,item);

            ii++;
        }
    }

    ui->tableWidget_2->setRowCount(count+ii);

    if(ui->tableWidget_2->rowCount()!=0){
        pred=-1;
        loc=ui->tableWidget_2->item(0,11)->text().toInt();
        changeRowColor2(0);
        bool colorChange=true;  //store the state of the before one
        for(int i=1;i<ui->tableWidget_2->rowCount();i++){
            pred=loc;
            loc=ui->tableWidget_2->item(i,11)->text().toInt();
            if(pred==loc){
                if(colorChange==true){
                    changeRowColor2(i);
                }
            }
            else{
                if(colorChange==true){
                    colorChange=false;
                }
                else if(colorChange==false){
                    colorChange=true;
                    changeRowColor2(i);
                }
            }

        }
    }

}

void Form::checkDate()
{
    QTableWidgetItem *item;
    int row=ui->tableWidget_2->rowCount();
    //delete original item
    for(int i=0;i<row;i++){
        for(int j=0;j<col2;j++){
            item=ui->tableWidget_2->item(i,j);
            delete item;
        }
    }
    ui->tableWidget_2->clearContents();
    QDate day=ui->calendarWidget->selectedDate();
    string com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));

    vector <int> code;
    //the vector store the code of tickets that match the user request
    while(query->next()){
        //if(query->value(1).toString()==startLocation){
        //if(query->value(2).toString()==endLocation){
        if(query->value(5).toDate()==day){
            //find the corresponding tickets
            code.push_back(query->value(0).toInt());
        }
        //}
        //}
    }

    vector <int> duplicatedCode;
    set <int> uniqueDuplicate;
    com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));
    int pred=0;
    int loc=0;
    query->next();
    pred=query->value(0).toInt();
    while(query->next()){
        loc=query->value(0).toInt();
        if(loc==pred){
            duplicatedCode.push_back(loc);
            uniqueDuplicate.insert(loc);
        }
        pred=loc;
    }


    set <int> fitCode;
    for(set<int>::iterator itr=uniqueDuplicate.begin();itr!=uniqueDuplicate.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        query->next();
        QString startL,destL;
        startL=query->value(1).toString();
        QDate dd=query->value(5).toDate();
        while(query->next()){
            destL=query->value(2).toString();
        }
        if(dd==ui->calendarWidget->selectedDate()){
            fitCode.insert(*itr);
        }
    }



    ui->tableWidget_2->setRowCount(code.size()+duplicatedCode.size()+uniqueDuplicate.size());

    set <int> setCode;
    for(int k=0;k<(int)code.size();k++){
        setCode.insert(code[k]);
    }

    int count=0;
    //print the tickets data into table
    for(set<int>::iterator itr=setCode.begin();itr!=setCode.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        while(query->next()){
            //i++;
            //date
            QDate d=query->value(5).toDate();
            QString td;
            td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
            item=new QTableWidgetItem;
            item->setText(td);
            ui->tableWidget_2->setItem(count,0,item);


            //set type and number
            item=new QTableWidgetItem;
            QString text=query->value(8).toString();
            text+=query->value(3).toString();
            item->setText(text);
            ui->tableWidget_2->setItem(count,1,item);

            //set start location
            item=new QTableWidgetItem;
            item->setText(query->value(1).toString());
            ui->tableWidget_2->setItem(count,2,item);

            //set end location
            item=new QTableWidgetItem;
            item->setText(query->value(2).toString());
            ui->tableWidget_2->setItem(count,3,item);

            //set start time
            item=new QTableWidgetItem;
            item->setText(query->value(6).toString());
            ui->tableWidget_2->setItem(count,4,item);

            //set end time
            item=new QTableWidgetItem;
            item->setText(query->value(7).toString());
            ui->tableWidget_2->setItem(count,5,item);

            //set seat number
            item=new QTableWidgetItem;
            item->setText(query->value(4).toString());
            ui->tableWidget_2->setItem(count,6,item);

            //set meat bento
            item=new QTableWidgetItem;
            item->setText(query->value(9).toString());
            ui->tableWidget_2->setItem(count,7,item);

            //set vegetable bento
            item=new QTableWidgetItem;
            item->setText(query->value(10).toString());
            ui->tableWidget_2->setItem(count,8,item);

            //set special serving
            int ss=query->value(11).toInt();
            QString extraServing;
            if(ss==1){
                extraServing="Yes";
            }
            else{
                extraServing="No";
            }
            item=new QTableWidgetItem;
            item->setText(extraServing);
            ui->tableWidget_2->setItem(count,9,item);

            //set identity
            item=new QTableWidgetItem;
            item->setText(query->value(12).toString());
            ui->tableWidget_2->setItem(count,10,item);

            //code
            item=new QTableWidgetItem;
            item->setText(query->value(0).toString());
            ui->tableWidget_2->setItem(count,11,item);


            count++;
        }



    }

    ui->tableWidget_2->setRowCount(code.size());

    if(ui->tableWidget_2->rowCount()!=0){
        pred=-1;
        loc=ui->tableWidget_2->item(0,11)->text().toInt();
        changeRowColor2(0);
        bool colorChange=true;  //store the state of the before one
        for(int i=1;i<ui->tableWidget_2->rowCount();i++){
            pred=loc;
            loc=ui->tableWidget_2->item(i,11)->text().toInt();
            if(pred==loc){
                if(colorChange==true){
                    changeRowColor2(i);
                }
            }
            else{
                if(colorChange==true){
                    colorChange=false;
                }
                else if(colorChange==false){
                    colorChange=true;
                    changeRowColor2(i);
                }
            }

        }
    }

}

void Form::checkTime()
{
    QTableWidgetItem *item;
    int row=ui->tableWidget_2->rowCount();
    //delete original item
    for(int i=0;i<row;i++){
        for(int j=0;j<col2;j++){
            item=ui->tableWidget_2->item(i,j);
            delete item;
        }
    }
    ui->tableWidget_2->clearContents();

    //QString startLocation=ui->comboBox_6->currentText();
    //QString endLocation=ui->comboBox_7->currentText();
    string com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));

    vector <int> code;
    //the vector store the code of tickets that match the user request
    while(query->next()){
        //if(query->value(1).toString()==startLocation){
        //if(query->value(2).toString()==endLocation){
        QTime tt=query->value(6).toTime();
        QTime selectTime=ui->timeEdit->time();

        if(tt.hour() > selectTime.hour()){
            //latter is larger
            QTime temp=tt;
            tt=selectTime;
            selectTime=temp;
        }
        else if((tt.minute() > selectTime.minute()) && tt.hour() == selectTime.hour()){
            //latter is larger
            QTime temp=tt;
            tt=selectTime;
            selectTime=temp;
        }

        QTime td=timeDiff(tt,selectTime);

        int tdint=60*td.hour()+td.minute();
        qDebug()<<tt;
        qDebug()<<selectTime;
        qDebug()<<td;
        qDebug()<<tdint;
        if(abs(tdint) <=60){
            //find the corresponding tickets
            code.push_back(query->value(0).toInt());
        }
        //}
        //}
    }

    vector <int> duplicatedCode;
    set <int> uniqueDuplicate;
    com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));
    int pred=0;
    int loc=0;
    query->next();
    pred=query->value(0).toInt();
    while(query->next()){
        loc=query->value(0).toInt();
        if(loc==pred){
            duplicatedCode.push_back(loc);
            uniqueDuplicate.insert(loc);
        }
        pred=loc;
    }


    set <int> fitCode;
    for(set<int>::iterator itr=uniqueDuplicate.begin();itr!=uniqueDuplicate.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        query->next();
        QString startL,destL;
        startL=query->value(1).toString();
        while(query->next()){
            destL=query->value(2).toString();
        }
        //if(query->value(1).toString()==startLocation){
        //if(query->value(2).toString()==endLocation){
        command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        query->next();

        QTime tt=query->value(6).toTime();
        QTime selectTime=ui->timeEdit->time();

        if(tt.hour() > selectTime.hour()){
            //latter is larger
            QTime temp=tt;
            tt=selectTime;
            selectTime=temp;
        }
        else if((tt.minute() > selectTime.minute()) && tt.hour() == selectTime.hour()){
            //latter is larger
            QTime temp=tt;
            tt=selectTime;
            selectTime=temp;
        }

        QTime td=timeDiff(tt,selectTime);

        int tdint=60*td.hour()+td.minute();
        /*qDebug()<<tt;
        qDebug()<<selectTime;
        qDebug()<<td;
        qDebug()<<tdint;*/
        if(abs(tdint) <= 60){
            //find the corresponding tickets
            fitCode.insert(query->value(0).toInt());
        }
    }

    set <int> setCode;
    for(int k=0;k<(int)code.size();k++){
        setCode.insert(code[k]);
    }

    ui->tableWidget_2->setRowCount(code.size()+duplicatedCode.size()+uniqueDuplicate.size());

    int count=0;
    //print the tickets data into table
    for(set<int>::iterator itr=setCode.begin();itr!=setCode.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        while(query->next()){
            //i++;
            //date
            QDate d=query->value(5).toDate();
            QString td;
            td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
            item=new QTableWidgetItem;
            item->setText(td);
            ui->tableWidget_2->setItem(count,0,item);


            //set type and number
            item=new QTableWidgetItem;
            QString text=query->value(8).toString();
            text+=query->value(3).toString();
            item->setText(text);
            ui->tableWidget_2->setItem(count,1,item);

            //set start location
            item=new QTableWidgetItem;
            item->setText(query->value(1).toString());
            ui->tableWidget_2->setItem(count,2,item);

            //set end location
            item=new QTableWidgetItem;
            item->setText(query->value(2).toString());
            ui->tableWidget_2->setItem(count,3,item);

            //set start time
            item=new QTableWidgetItem;
            item->setText(query->value(6).toString());
            ui->tableWidget_2->setItem(count,4,item);

            //set end time
            item=new QTableWidgetItem;
            item->setText(query->value(7).toString());
            ui->tableWidget_2->setItem(count,5,item);

            //set seat number
            item=new QTableWidgetItem;
            item->setText(query->value(4).toString());
            ui->tableWidget_2->setItem(count,6,item);

            //set meat bento
            item=new QTableWidgetItem;
            item->setText(query->value(9).toString());
            ui->tableWidget_2->setItem(count,7,item);

            //set vegetable bento
            item=new QTableWidgetItem;
            item->setText(query->value(10).toString());
            ui->tableWidget_2->setItem(count,8,item);

            //set special serving
            int ss=query->value(11).toInt();
            QString extraServing;
            if(ss==1){
                extraServing="Yes";
            }
            else{
                extraServing="No";
            }
            item=new QTableWidgetItem;
            item->setText(extraServing);
            ui->tableWidget_2->setItem(count,9,item);

            //set identity
            item=new QTableWidgetItem;
            item->setText(query->value(12).toString());
            ui->tableWidget_2->setItem(count,10,item);

            //code
            item=new QTableWidgetItem;
            item->setText(query->value(0).toString());
            ui->tableWidget_2->setItem(count,11,item);


            count++;
        }



    }

    ui->tableWidget_2->setRowCount(code.size());

    if(ui->tableWidget_2->rowCount()!=0){
        loc=ui->tableWidget_2->item(0,11)->text().toInt();
        changeRowColor2(0);
        bool colorChange=true;  //store the state of the before one
        for(int i=1;i<ui->tableWidget_2->rowCount();i++){
            pred=loc;
            loc=ui->tableWidget_2->item(i,11)->text().toInt();
            if(pred==loc){
                if(colorChange==true){
                    changeRowColor2(i);
                }
            }
            else{
                if(colorChange==true){
                    colorChange=false;
                }
                else if(colorChange==false){
                    colorChange=true;
                    changeRowColor2(i);
                }
            }

        }
    }

}

void Form::checkTimeDate()
{
    QTableWidgetItem *item;
    int row=ui->tableWidget_2->rowCount();
    //delete original item
    for(int i=0;i<row;i++){
        for(int j=0;j<col2;j++){
            item=ui->tableWidget_2->item(i,j);
            delete item;
        }
    }
    ui->tableWidget_2->clearContents();

    //QString startLocation=ui->comboBox_6->currentText();
    //QString endLocation=ui->comboBox_7->currentText();
    QDate day=ui->calendarWidget->selectedDate();
    string com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));

    vector <int> code;
    //the vector store the code of tickets that match the user request
    while(query->next()){
        //if(query->value(1).toString()==startLocation){
        //if(query->value(2).toString()==endLocation){
        QTime tt=query->value(6).toTime();
        QTime selectTime=ui->timeEdit->time();

        if(tt.hour() > selectTime.hour()){
            //latter is larger
            QTime temp=tt;
            tt=selectTime;
            selectTime=temp;
        }
        else if((tt.minute() > selectTime.minute()) && tt.hour() == selectTime.hour()){
            //latter is larger
            QTime temp=tt;
            tt=selectTime;
            selectTime=temp;
        }

        QTime td=timeDiff(tt,selectTime);

        int tdint=60*td.hour()+td.minute();
        /*qDebug()<<tt;
        qDebug()<<selectTime;
        qDebug()<<td;
        qDebug()<<tdint;*/
        if(abs(tdint) <=60){
            //find the corresponding tickets
            if(day==query->value(5).toDate())
                code.push_back(query->value(0).toInt());
        }
        //}
        //}
    }

    vector <int> duplicatedCode;
    set <int> uniqueDuplicate;
    com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));
    int pred=0;
    int loc=0;
    query->next();
    pred=query->value(0).toInt();
    while(query->next()){
        loc=query->value(0).toInt();
        if(loc==pred){
            duplicatedCode.push_back(loc);
            uniqueDuplicate.insert(loc);
        }
        pred=loc;
    }


    set <int> fitCode;
    for(set<int>::iterator itr=uniqueDuplicate.begin();itr!=uniqueDuplicate.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        query->next();
        QString startL,destL;
        startL=query->value(1).toString();
        QDate dd=query->value(5).toDate();
        while(query->next()){
            destL=query->value(2).toString();
        }
        command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        query->next();
        if(dd==ui->calendarWidget->selectedDate()){

            QTime tt=query->value(6).toTime();
            QTime selectTime=ui->timeEdit->time();

            if(tt.hour() > selectTime.hour()){
                //latter is larger
                QTime temp=tt;
                tt=selectTime;
                selectTime=temp;
            }
            else if((tt.minute() > selectTime.minute()) && tt.hour() == selectTime.hour()){
                //latter is larger
                QTime temp=tt;
                tt=selectTime;
                selectTime=temp;
            }

            QTime td=timeDiff(tt,selectTime);

            int tdint=60*td.hour()+td.minute();
            /*qDebug()<<tt;
            qDebug()<<selectTime;
            qDebug()<<td;
            qDebug()<<tdint;*/
            if(abs(tdint) <=60){
                //find the corresponding tickets
                if(day==query->value(5).toDate())
                    fitCode.insert(*itr);
            }
            //}
            //}

        }
    }



    ui->tableWidget_2->setRowCount(code.size()+duplicatedCode.size()+uniqueDuplicate.size());

    set <int> setCode;
    for(int k=0;k<(int)code.size();k++){
        setCode.insert(code[k]);
    }


    int count=0;
    //print the tickets data into table
    for(set<int>::iterator itr=setCode.begin();itr!=setCode.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        while(query->next()){
            //i++;
            //date
            QDate d=query->value(5).toDate();
            QString td;
            td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
            item=new QTableWidgetItem;
            item->setText(td);
            ui->tableWidget_2->setItem(count,0,item);


            //set type and number
            item=new QTableWidgetItem;
            QString text=query->value(8).toString();
            text+=query->value(3).toString();
            item->setText(text);
            ui->tableWidget_2->setItem(count,1,item);

            //set start location
            item=new QTableWidgetItem;
            item->setText(query->value(1).toString());
            ui->tableWidget_2->setItem(count,2,item);

            //set end location
            item=new QTableWidgetItem;
            item->setText(query->value(2).toString());
            ui->tableWidget_2->setItem(count,3,item);

            //set start time
            item=new QTableWidgetItem;
            item->setText(query->value(6).toString());
            ui->tableWidget_2->setItem(count,4,item);

            //set end time
            item=new QTableWidgetItem;
            item->setText(query->value(7).toString());
            ui->tableWidget_2->setItem(count,5,item);

            //set seat number
            item=new QTableWidgetItem;
            item->setText(query->value(4).toString());
            ui->tableWidget_2->setItem(count,6,item);

            //set meat bento
            item=new QTableWidgetItem;
            item->setText(query->value(9).toString());
            ui->tableWidget_2->setItem(count,7,item);

            //set vegetable bento
            item=new QTableWidgetItem;
            item->setText(query->value(10).toString());
            ui->tableWidget_2->setItem(count,8,item);

            //set special serving
            int ss=query->value(11).toInt();
            QString extraServing;
            if(ss==1){
                extraServing="Yes";
            }
            else{
                extraServing="No";
            }
            item=new QTableWidgetItem;
            item->setText(extraServing);
            ui->tableWidget_2->setItem(count,9,item);

            //set identity
            item=new QTableWidgetItem;
            item->setText(query->value(12).toString());
            ui->tableWidget_2->setItem(count,10,item);

            //code
            item=new QTableWidgetItem;
            item->setText(query->value(0).toString());
            ui->tableWidget_2->setItem(count,11,item);


            count++;
        }



    }

    ui->tableWidget_2->setRowCount(code.size());

    if(ui->tableWidget_2->rowCount()!=0){
        loc=ui->tableWidget_2->item(0,11)->text().toInt();
        changeRowColor2(0);
        bool colorChange=true;  //store the state of the before one
        for(int i=1;i<ui->tableWidget_2->rowCount();i++){
            pred=loc;
            loc=ui->tableWidget_2->item(i,11)->text().toInt();
            if(pred==loc){
                if(colorChange==true){
                    changeRowColor2(i);
                }
            }
            else{
                if(colorChange==true){
                    colorChange=false;
                }
                else if(colorChange==false){
                    colorChange=true;
                    changeRowColor2(i);
                }
            }

        }
    }
}

void Form::checkLocTime()
{
    //search (for check)
    QTableWidgetItem *item;
    int row=ui->tableWidget_2->rowCount();
    //delete original item
    for(int i=0;i<row;i++){
        for(int j=0;j<col2;j++){
            item=ui->tableWidget_2->item(i,j);
            delete item;
        }
    }
    ui->tableWidget_2->clearContents();

    QString startLocation=ui->comboBox_6->currentText();
    QString endLocation=ui->comboBox_7->currentText();
    string com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));

    vector <int> code;
    //the vector store the code of tickets that match the user request
    while(query->next()){
        if(query->value(1).toString()==startLocation){
            if(query->value(2).toString()==endLocation){
                //if(query->value(1).toString()==startLocation){
                //if(query->value(2).toString()==endLocation){
                QTime tt=query->value(6).toTime();
                QTime selectTime=ui->timeEdit->time();

                if(tt.hour() > selectTime.hour()){
                    //latter is larger
                    QTime temp=tt;
                    tt=selectTime;
                    selectTime=temp;
                }
                else if((tt.minute() > selectTime.minute()) && tt.hour() == selectTime.hour()){
                    //latter is larger
                    QTime temp=tt;
                    tt=selectTime;
                    selectTime=temp;
                }

                QTime td=timeDiff(tt,selectTime);

                int tdint=60*td.hour()+td.minute();
                /*qDebug()<<tt;
                qDebug()<<selectTime;
                qDebug()<<td;
                qDebug()<<tdint;*/
                if(abs(tdint) < 480){
                    //find the corresponding tickets

                    code.push_back(query->value(0).toInt());
                }
                //}
                //}
            }
        }
    }

    vector <int> duplicatedCode;
    set <int> uniqueDuplicate;
    com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));
    int pred=0;
    int loc=0;
    query->next();
    pred=query->value(0).toInt();
    while(query->next()){
        loc=query->value(0).toInt();
        if(loc==pred){
            duplicatedCode.push_back(loc);
            uniqueDuplicate.insert(loc);
        }
        pred=loc;
    }


    set <int> fitCode;
    for(set<int>::iterator itr=uniqueDuplicate.begin();itr!=uniqueDuplicate.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        query->next();
        QString startL,destL;
        startL=query->value(1).toString();
        QDate dd=query->value(5).toDate();
        while(query->next()){
            destL=query->value(2).toString();
        }
        command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        query->next();
        if(startL==startLocation && destL==endLocation){
            QTime tt=query->value(6).toTime();
            QTime selectTime=ui->timeEdit->time();

            if(tt.hour() > selectTime.hour()){
                //latter is larger
                QTime temp=tt;
                tt=selectTime;
                selectTime=temp;
            }
            else if((tt.minute() > selectTime.minute()) && tt.hour() == selectTime.hour()){
                //latter is larger
                QTime temp=tt;
                tt=selectTime;
                selectTime=temp;
            }

            QTime td=timeDiff(tt,selectTime);

            int tdint=60*td.hour()+td.minute();
            /*qDebug()<<tt;
            qDebug()<<selectTime;
            qDebug()<<td;
            qDebug()<<tdint;*/
            if(abs(tdint) <=60){
                //find the corresponding tickets
                fitCode.insert(*itr);
            }


        }
    }



    ui->tableWidget_2->setRowCount(code.size()+duplicatedCode.size()+uniqueDuplicate.size());

    int count=0;
    //print the tickets data into table
    for(int i=0;i<(int)code.size();i++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(code[i]);
        query->exec(command);
        while(query->next()){
            //date
            QDate d=query->value(5).toDate();
            QString td;
            td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
            item=new QTableWidgetItem;
            item->setText(td);
            ui->tableWidget_2->setItem(count,0,item);


            //set type and number
            item=new QTableWidgetItem;
            QString text=query->value(8).toString();
            text+=query->value(3).toString();
            item->setText(text);
            ui->tableWidget_2->setItem(count,1,item);

            //set start location
            item=new QTableWidgetItem;
            item->setText(query->value(1).toString());
            ui->tableWidget_2->setItem(count,2,item);

            //set end location
            item=new QTableWidgetItem;
            item->setText(query->value(2).toString());
            ui->tableWidget_2->setItem(count,3,item);

            //set start time
            item=new QTableWidgetItem;
            item->setText(query->value(6).toString());
            ui->tableWidget_2->setItem(count,4,item);

            //set end time
            item=new QTableWidgetItem;
            item->setText(query->value(7).toString());
            ui->tableWidget_2->setItem(count,5,item);

            //set seat number
            item=new QTableWidgetItem;
            item->setText(query->value(4).toString());
            ui->tableWidget_2->setItem(count,6,item);

            //set meat bento
            item=new QTableWidgetItem;
            item->setText(query->value(9).toString());
            ui->tableWidget_2->setItem(count,7,item);

            //set vegetable bento
            item=new QTableWidgetItem;
            item->setText(query->value(10).toString());
            ui->tableWidget_2->setItem(count,8,item);

            //set special serving
            int ss=query->value(11).toInt();
            QString extraServing;
            if(ss==1){
                extraServing="Yes";
            }
            else{
                extraServing="No";
            }
            item=new QTableWidgetItem;
            item->setText(extraServing);
            ui->tableWidget_2->setItem(count,9,item);

            //set identity
            item=new QTableWidgetItem;
            item->setText(query->value(12).toString());
            ui->tableWidget_2->setItem(count,10,item);

            //code
            item=new QTableWidgetItem;
            item->setText(query->value(0).toString());
            ui->tableWidget_2->setItem(count,11,item);

            count++;
        }




    }

    int ii=0;
    for(set<int>::iterator itr=fitCode.begin();itr!=fitCode.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        while(query->next()){
            //date
            QDate d=query->value(5).toDate();
            QString td;
            td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
            item=new QTableWidgetItem;
            item->setText(td);
            ui->tableWidget_2->setItem(code.size()+ii,0,item);


            //set type and number
            item=new QTableWidgetItem;
            QString text=query->value(8).toString();
            text+=query->value(3).toString();
            item->setText(text);
            ui->tableWidget_2->setItem(code.size()+ii,1,item);

            //set start location
            item=new QTableWidgetItem;
            item->setText(query->value(1).toString());
            ui->tableWidget_2->setItem(code.size()+ii,2,item);

            //set end location
            item=new QTableWidgetItem;
            item->setText(query->value(2).toString());
            ui->tableWidget_2->setItem(code.size()+ii,3,item);

            //set start time
            item=new QTableWidgetItem;
            item->setText(query->value(6).toString());
            ui->tableWidget_2->setItem(code.size()+ii,4,item);

            //set end time
            item=new QTableWidgetItem;
            item->setText(query->value(7).toString());
            ui->tableWidget_2->setItem(code.size()+ii,5,item);

            //set seat number
            item=new QTableWidgetItem;
            item->setText(query->value(4).toString());
            ui->tableWidget_2->setItem(code.size()+ii,6,item);

            //set meat bento
            item=new QTableWidgetItem;
            item->setText(query->value(9).toString());
            ui->tableWidget_2->setItem(code.size()+ii,7,item);

            //set vegetable bento
            item=new QTableWidgetItem;
            item->setText(query->value(10).toString());
            ui->tableWidget_2->setItem(code.size()+ii,8,item);

            //set special serving
            int ss=query->value(11).toInt();
            QString extraServing;
            if(ss==1){
                extraServing="Yes";
            }
            else{
                extraServing="No";
            }
            item=new QTableWidgetItem;
            item->setText(extraServing);
            ui->tableWidget_2->setItem(code.size()+ii,9,item);

            //set identity
            item=new QTableWidgetItem;
            item->setText(query->value(12).toString());
            ui->tableWidget_2->setItem(code.size()+ii,10,item);

            //code
            item=new QTableWidgetItem;
            item->setText(query->value(0).toString());
            ui->tableWidget_2->setItem(code.size()+ii,11,item);

            ii++;
        }
    }

    ui->tableWidget_2->setRowCount(count+ii);

    if(ui->tableWidget_2->rowCount()!=0){
        pred=-1;
        loc=ui->tableWidget_2->item(0,11)->text().toInt();
        changeRowColor2(0);
        bool colorChange=true;  //store the state of the before one
        for(int i=1;i<ui->tableWidget_2->rowCount();i++){
            pred=loc;
            loc=ui->tableWidget_2->item(i,11)->text().toInt();
            if(pred==loc){
                if(colorChange==true){
                    changeRowColor2(i);
                }
            }
            else{
                if(colorChange==true){
                    colorChange=false;
                }
                else if(colorChange==false){
                    colorChange=true;
                    changeRowColor2(i);
                }
            }

        }
    }
}

void Form::checkLocDateTime()
{
    //search (for check)
    QTableWidgetItem *item;
    int row=ui->tableWidget_2->rowCount();
    //delete original item
    for(int i=0;i<row;i++){
        for(int j=0;j<col2;j++){
            item=ui->tableWidget_2->item(i,j);
            delete item;
        }
    }
    ui->tableWidget_2->clearContents();

    QString startLocation=ui->comboBox_6->currentText();
    QString endLocation=ui->comboBox_7->currentText();
    QDate day=ui->calendarWidget->selectedDate();
    string com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));

    vector <int> code;
    //the vector store the code of tickets that match the user request
    while(query->next()){
        if(query->value(1).toString()==startLocation){
            if(query->value(2).toString()==endLocation){
                //if(query->value(1).toString()==startLocation){
                //if(query->value(2).toString()==endLocation){
                QTime tt=query->value(6).toTime();
                QTime selectTime=ui->timeEdit->time();

                if(tt.hour() > selectTime.hour()){
                    //latter is larger
                    QTime temp=tt;
                    tt=selectTime;
                    selectTime=temp;
                }
                else if((tt.minute() > selectTime.minute()) && tt.hour() == selectTime.hour()){
                    //latter is larger
                    QTime temp=tt;
                    tt=selectTime;
                    selectTime=temp;
                }

                QTime td=timeDiff(tt,selectTime);

                int tdint=60*td.hour()+td.minute();
                if(abs(tdint) <=60){
                    //find the corresponding tickets
                    if(day==query->value(5)){
                        code.push_back(query->value(0).toInt());
                    }
                }
            }
        }
    }

    vector <int> duplicatedCode;
    set <int> uniqueDuplicate;
    com="SELECT * FROM "+nowct->clientName;
    query->exec(QString::fromStdString(com));
    int pred=0;
    int loc=0;
    query->next();
    pred=query->value(0).toInt();
    while(query->next()){
        loc=query->value(0).toInt();
        if(loc==pred){
            duplicatedCode.push_back(loc);
            uniqueDuplicate.insert(loc);
        }
        pred=loc;
    }


    set <int> fitCode;
    for(set<int>::iterator itr=uniqueDuplicate.begin();itr!=uniqueDuplicate.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        query->next();
        QString startL,destL;
        startL=query->value(1).toString();
        while(query->next()){
            destL=query->value(2).toString();
        }
        command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        query->next();
        if(startL==startLocation && destL==endLocation){
            QTime tt=query->value(6).toTime();
            QTime selectTime=ui->timeEdit->time();

            if(tt.hour() > selectTime.hour()){
                //latter is larger
                QTime temp=tt;
                tt=selectTime;
                selectTime=temp;
            }
            else if((tt.minute() > selectTime.minute()) && tt.hour() == selectTime.hour()){
                //latter is larger
                QTime temp=tt;
                tt=selectTime;
                selectTime=temp;
            }

            QTime td=timeDiff(tt,selectTime);

            int tdint=60*td.hour()+td.minute();

            if(abs(tdint) <=60){
                //find the corresponding tickets
                if(day==query->value(5).toDate()){
                    fitCode.insert(*itr);
                }

            }
        }
    }



    ui->tableWidget_2->setRowCount(code.size()+duplicatedCode.size()+uniqueDuplicate.size());

    int count=0;
    //print the tickets data into table
    for(int i=0;i<(int)code.size();i++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(code[i]);
        query->exec(command);
        while(query->next()){
            //date
            QDate d=query->value(5).toDate();
            QString td;
            td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
            item=new QTableWidgetItem;
            item->setText(td);
            ui->tableWidget_2->setItem(count,0,item);


            //set type and number
            item=new QTableWidgetItem;
            QString text=query->value(8).toString();
            text+=query->value(3).toString();
            item->setText(text);
            ui->tableWidget_2->setItem(count,1,item);

            //set start location
            item=new QTableWidgetItem;
            item->setText(query->value(1).toString());
            ui->tableWidget_2->setItem(count,2,item);

            //set end location
            item=new QTableWidgetItem;
            item->setText(query->value(2).toString());
            ui->tableWidget_2->setItem(count,3,item);

            //set start time
            item=new QTableWidgetItem;
            item->setText(query->value(6).toString());
            ui->tableWidget_2->setItem(count,4,item);

            //set end time
            item=new QTableWidgetItem;
            item->setText(query->value(7).toString());
            ui->tableWidget_2->setItem(count,5,item);

            //set seat number
            item=new QTableWidgetItem;
            item->setText(query->value(4).toString());
            ui->tableWidget_2->setItem(count,6,item);

            //set meat bento
            item=new QTableWidgetItem;
            item->setText(query->value(9).toString());
            ui->tableWidget_2->setItem(count,7,item);

            //set vegetable bento
            item=new QTableWidgetItem;
            item->setText(query->value(10).toString());
            ui->tableWidget_2->setItem(count,8,item);

            //set special serving
            int ss=query->value(11).toInt();
            QString extraServing;
            if(ss==1){
                extraServing="Yes";
            }
            else{
                extraServing="No";
            }
            item=new QTableWidgetItem;
            item->setText(extraServing);
            ui->tableWidget_2->setItem(count,9,item);

            //set identity
            item=new QTableWidgetItem;
            item->setText(query->value(12).toString());
            ui->tableWidget_2->setItem(count,10,item);

            //code
            item=new QTableWidgetItem;
            item->setText(query->value(0).toString());
            ui->tableWidget_2->setItem(count,11,item);

            count++;

        }



    }

    int ii=0;
    for(set<int>::iterator itr=fitCode.begin();itr!=fitCode.end();itr++){
        QString command="SELECT * FROM ";
        command+=QString::fromStdString(nowct->clientName);
        command+=" WHERE code="+QString::number(*itr);
        query->exec(command);
        while(query->next()){
            //date
            QDate d=query->value(5).toDate();
            QString td;
            td=QString::number(d.year())+"-"+QString::number(d.month())+"-"+QString::number(d.day());
            item=new QTableWidgetItem;
            item->setText(td);
            ui->tableWidget_2->setItem(code.size()+ii,0,item);


            //set type and number
            item=new QTableWidgetItem;
            QString text=query->value(8).toString();
            text+=query->value(3).toString();
            item->setText(text);
            ui->tableWidget_2->setItem(code.size()+ii,1,item);

            //set start location
            item=new QTableWidgetItem;
            item->setText(query->value(1).toString());
            ui->tableWidget_2->setItem(code.size()+ii,2,item);

            //set end location
            item=new QTableWidgetItem;
            item->setText(query->value(2).toString());
            ui->tableWidget_2->setItem(code.size()+ii,3,item);

            //set start time
            item=new QTableWidgetItem;
            item->setText(query->value(6).toString());
            ui->tableWidget_2->setItem(code.size()+ii,4,item);

            //set end time
            item=new QTableWidgetItem;
            item->setText(query->value(7).toString());
            ui->tableWidget_2->setItem(code.size()+ii,5,item);

            //set seat number
            item=new QTableWidgetItem;
            item->setText(query->value(4).toString());
            ui->tableWidget_2->setItem(code.size()+ii,6,item);

            //set meat bento
            item=new QTableWidgetItem;
            item->setText(query->value(9).toString());
            ui->tableWidget_2->setItem(code.size()+ii,7,item);

            //set vegetable bento
            item=new QTableWidgetItem;
            item->setText(query->value(10).toString());
            ui->tableWidget_2->setItem(code.size()+ii,8,item);

            //set special serving
            int ss=query->value(11).toInt();
            QString extraServing;
            if(ss==1){
                extraServing="Yes";
            }
            else{
                extraServing="No";
            }
            item=new QTableWidgetItem;
            item->setText(extraServing);
            ui->tableWidget_2->setItem(code.size()+ii,9,item);

            //set identity
            item=new QTableWidgetItem;
            item->setText(query->value(12).toString());
            ui->tableWidget_2->setItem(code.size()+ii,10,item);

            //code
            item=new QTableWidgetItem;
            item->setText(query->value(0).toString());
            ui->tableWidget_2->setItem(code.size()+ii,11,item);

            ii++;
        }
    }

    ui->tableWidget_2->setRowCount(count+ii);

    if(ui->tableWidget_2->rowCount()!=0){
        pred=-1;
        loc=ui->tableWidget_2->item(0,11)->text().toInt();
        changeRowColor2(0);
        bool colorChange=true;  //store the state of the before one
        for(int i=1;i<ui->tableWidget_2->rowCount();i++){
            pred=loc;
            loc=ui->tableWidget_2->item(i,11)->text().toInt();
            if(pred==loc){
                if(colorChange==true){
                    changeRowColor2(i);
                }
            }
            else{
                if(colorChange==true){
                    colorChange=false;
                }
                else if(colorChange==false){
                    colorChange=true;
                    changeRowColor2(i);
                }
            }

        }
    }
}


void Form::on_checkBox_stateChanged(int arg1)
{
    ui->pushButton_8->clicked();
}

void Form::on_checkBox_2_stateChanged(int arg1)
{
    ui->pushButton_8->clicked();
}

void Form::on_checkBox_3_stateChanged(int arg1)
{
    ui->pushButton_8->clicked();
}



void Form::on_comboBox_activated(int index)
{
    if(!double_state2&&(state==1 || state==4||state==2||state==3)){
        ui->comboBox_6->clear();
        query->exec((QString)("SELECT DISTINCT chinese_name FROM train_station_code_2 WHERE related_city='")+ui->comboBox->currentText()+(QString)"'");

        while(query->next()){
            if(query->value(0).toString()==ui->comboBox_7->currentText())
                continue;
            ui->comboBox_6->addItem(query->value(0).toString());
        }
        ui->pushButton_8->clicked();


    }
    else if(double_state2){
        QString com="SELECT station_c_n,min(num_order) from (SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1)+")as a GROUP BY (t_num,city,station_c_n) HAVING t_num="+QString::number(tempTrainNumber)+ "and city='"+ui->comboBox->currentText()+"'ORDER BY (min(num_order)) " ;
        QString com3="SELECT city,min(num_order) from (SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1)+")as a GROUP BY (t_num,CITY) HAVING t_num="+QString::number(tempTrainNumber)+"ORDER BY (min(num_order)) ";
        qDebug()<<com;
        ui->comboBox_10->clear();
        if(ui->comboBox_2->currentText()==ui->comboBox->currentText()){
            query->exec(com);
            while(query->next()){
                ui->comboBox_10->addItem(query->value(0).toString());
            }
        }
        else{
            query->exec(com3);
            bool allowed=false;
            int count=0;
            bool clear=false;
            while(query->next()){
                if(query->value(0).toString()==ui->comboBox->currentText()){
                    allowed=true;
                }
                if(!allowed&&ui->comboBox_2->findText(query->value(0).toString())!=-1){
                    if(!clear&&ui->comboBox_2->findText(query->value(0).toString())==0){
                        clear=true;
                    }
                    ui->comboBox_2->removeItem(ui->comboBox_2->findText(query->value(0).toString()));


                }
                else if(allowed&&ui->comboBox_2->findText(query->value(0).toString())==-1){
                    ui->comboBox_2->insertItem(count,query->value(0).toString());
                    count++;
                }
            }
            query->exec(com);
            while(query->next()){
                ui->comboBox_10->addItem(query->value(0).toString());
            }
            if(clear){
                ui->comboBox_2->activated(0);
            }
        }
        ui->comboBox_10->activated(0);
    }
}


void Form::on_comboBox_2_activated(int index)
{
    if(!double_state2&&(state==1 || state==4||state==2||state==3)){
        //reserve or check
        //to (city)
        //when the combo box that display city is changed
        //the corresponding town will also changed
        query->exec(((QString)("SELECT DISTINCT chinese_name FROM train_station_code_2 WHERE related_city='")+ui->comboBox->currentText()+(QString)"'"));
        ui->comboBox_7->clear();
        while(query->next()){
            if(query->value(0).toString()==ui->comboBox_6->currentText())
                continue;
            ui->comboBox_7->addItem(query->value(0).toString());
        }
        ui->pushButton_8->clicked();


    }
    else if(double_state2){
        QString com="SELECT station_c_n,min(num_order) from (SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1)+")as a GROUP BY (t_num,city,station_c_n) HAVING t_num="+QString::number(tempTrainNumber)+ "and city='"+ui->comboBox_2->currentText()+"'ORDER BY (min(num_order)) " ;
               query->exec(com);
        ui->comboBox_11->clear();
        if(ui->comboBox_2->currentText()==ui->comboBox->currentText()){
            bool allowed=false;
            while(query->next()){
                if(query->value(0).toString()==ui->comboBox_10->currentText()){
                    allowed=true;
                    continue;
                }
                if(allowed&&ui->comboBox_11->findText(query->value(0).toString())==-1)
                    ui->comboBox_11->addItem(query->value(0).toString());
                else if(!allowed&&ui->comboBox_11->findText(query->value(0).toString())!=-1)
                    ui->comboBox_11->removeItem(ui->comboBox_11->findText(query->value(0).toString()));
            }
        }
        else{
            while(query->next()&&ui->comboBox_11->findText(query->value(0).toString())==-1){
                ui->comboBox_11->addItem(query->value(0).toString());
            }
        }
        ui->comboBox_11->activated(0);
        return;
    }
}


void Form::on_timeEdit_timeChanged(const QTime &time)
{
    ui->pushButton_8->clicked();
}


void Form::on_comboBox_3_activated(int index)
{
    QString com="SELECT * FROM  (SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1)+")as a WHERE t_num="+QString::number(tempTrainNumber)+"ORDER BY seat_code";
    query->exec(com);
    if(!query->next()){
        return;
    }
    ui->comboBox_4->clear();
    int carriageNumber=ui->comboBox_3->currentText().toInt();
    //put the valid with the corresponding carriage into combo box
    for(int i=0;i<(int)carriageSeat[carriageNumber-1].size();i++){
        ui->comboBox_4->addItem(QString::number(carriageSeat[carriageNumber-1][i]));
    }
}


void Form::on_comboBox_9_activated(int index)
{
    if(state==3){
        ui->pushButton_6->show();
        if(ui->comboBox_9->currentText()=="Special Care"){
            ui->label_7->show();
            ui->label_9->show();
            ui->label_10->hide();
            ui->spinBox_2->hide();
            ui->spinBox_3->hide();
            ui->label_7->setText("Care Content");
            ui->graphicsView->show();
            ui->groupBox->show();
            ui->radioButton->show();
            ui->radioButton_2->show();
            rl.start();

            if(ui->comboBox_8->currentText()=="Pregnant"){
                scene->clear();
                QPixmap gp(":/pic/pregnant.png");
                scene->addPixmap(gp);
                if(running!="Comfortable Sofa Will Be Your Best Partner When You Want To Snnze In A Long Travel! Give It A Try And Enjoy The Wonderful Experience On The Train!"){
                    running="Comfortable Sofa Will Be Your Best Partner When You Want To Snnze In A Long Travel! Give It A Try And Enjoy The Wonderful Experience On The Train!";
                    runbegin=0;
                    changerun=0;
                    startdo=0;
                }
            }
            else if(ui->comboBox_8->currentText()=="Kid"){
                scene->clear();
                QPixmap gp(":/pic/kid.png");
                scene->addPixmap(gp);
                if(running!="Play With Robot~We Provide Your Kids A Lot Of Toys To Deplete Their Unlimited Energy! Do Your Kids Like LEGO? Let's Play ~"){
                    running="Play With Robot~We Provide Your Kids A Lot Of Toys To Deplete Their Unlimited Energy! Do Your Kids Like LEGO? Let's Play ~";
                    runbegin=0;
                    changerun=0;
                    startdo=0;
                }
            }
            else if(ui->comboBox_8->currentText()=="Elder"){
                scene->clear();
                QPixmap gp(":/pic/elder.png");
                scene->addPixmap(gp);
                if(running!="We All Will Give You A Hand! Just Ensure This Serving Then We Will Send Some Specilist Foucing on Tacking Care for you!"){
                    running="We All Will Give You A Hand! Just Ensure This Serving Then We Will Send Some Specilist Foucing on Tacking Care for you!";
                    runbegin=0;
                    changerun=0;
                    startdo=0;
                }
            }
            else if(ui->comboBox_8->currentText()=="Alone"){
                scene->clear();
                QPixmap gp(":/pic/alone.png");
                scene->addPixmap(gp);
                if(running!="Don't Be Cring~ If You Reserving Alone And Need Some Help,We Always Here! We Can Support You With A Small Doll That Can Accompany With You!"){
                    running="Don't Be Cring~ If You Reserving Alone And Need Some Help,We Always Here! We Can Support You With A Small Doll That Can Accompany With You!";
                    runbegin=0;
                    changerun=0;
                    startdo=0;
                }
            }
        }
        else if(ui->comboBox_9->currentText()=="Bento"){
            ui->label_7->show();
            rl.stop();
            ui->label_9->hide();
            ui->label_10->show();
            ui->spinBox_2->show();
            ui->spinBox_3->show();
            ui->graphicsView->hide();
            ui->groupBox->hide();
            ui->radioButton->hide();
            ui->radioButton_2->hide();
            //Bento a1=b.getBento();

            ui->spinBox_2->setValue(QString::fromStdString(special.getBento().getMeat()).toInt());
            ui->spinBox_3->setValue(QString::fromStdString(special.getBento().getVeg()).toInt());
            ui->label_7->setText("meat");
            ui->label_10->setText("vegetable");
        }
    }
}


void Form::on_comboBox_10_activated(int index)
{
    index=-1;
    QString com="SELECT station_c_n,min(num_order) FROM (SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1)+")as a GROUP BY (t_num,city,station_c_n) HAVING t_num="+QString::number(tempTrainNumber)+ "and city='"+ui->comboBox_2->currentText()+"'"+"ORDER BY (min(num_order)) " ;
    QString com3=QString::fromStdString("SELECT city,min(num_order) from(SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1).toStdString()+")as a GROUP BY (t_num,CITY) HAVING t_num="+QString::number(tempTrainNumber).toStdString()+"ORDER BY (min(num_order)) ");

    if(ui->comboBox_2->currentText()==ui->comboBox->currentText()){
        query->exec(com);
        int count=0;
        bool allowed=false;
        bool check=false;
        while(query->next()){
            if(!allowed&&ui->comboBox_11->findText(query->value(0).toString())!=-1){
                ui->comboBox_11->removeItem(ui->comboBox_11->findText(query->value(0).toString()));
            }
            else if(allowed&&ui->comboBox_11->findText(query->value(0).toString())==-1){
                ui->comboBox_11->insertItem(count,query->value(0).toString());
                count++;
                check=true;
            }

            if(query->value(0)==ui->comboBox_10->currentText())
                allowed=true;
        }
        if(check){
            ui->comboBox_11->activated(0);
        }
    }
    if((index=ui->comboBox_10->findText(tempStart))!=-1){
        ui->comboBox_10->removeItem(index);
    }

}

void Form::on_tableWidget_cellActivated(int row, int column)
{
    if(ui->tableWidget->item(row,column)->data(QVariant::Color)==QColor(Qt::red)){
        return ;
    }
    ui->comboBox_3->show();
    ui->comboBox_4->show();
    ui->pushButton_6->show();
    ui->label_13->hide();
    ui->pushButton_10->hide();
    ui->label_5->show();
    ui->label_6->show();



    QTableWidgetItem *item;
    //srand(time(NULL));
    //for(int i=0;i<ui->spinBox->text().toInt();i++){
    Ticket a;
    Bento b;
    a.setbento(b);
    a.setCode(-1);
    ticketNumber++;
    //code
    //ticket code is sequence, not random
    //prevent repeated code

    a.setStart(ui->comboBox_6->currentText());
    //start location
    a.setDest(ui->comboBox_7->currentText());
    //destnation

    //get train number
    string temp;
    temp=train_num[row].toStdString();
    a.setTrainNumber(stoi(temp));
    tempTrainNumber=stoi(temp);
    //get train number

    //add seat number to combo box

    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    //user can choose seat
    QDate selectDate=ui->calendarWidget->selectedDate();
    int dateDiff=selectDate.toJulianDay()-today.toJulianDay();
    tempDateDiff=dateDiff;
    if(dateDiff<0 || dateDiff>13){
        //ui->label_12->setText("You can only buy the tickets in two weeks");
        //ui->label_12->show();
        dia.s="You can only buy the tickets in two weeks";
        dia.showerror();
        dia.show();
        ui->tableWidget->setRowCount(0);
        return;
    }
    ui->label_12->hide();
    int carriageNumber=carriageSeat_num;
    currentCarriageNumber=carriageNumber;
    for(int i=1;i<=carriageNumber;i++){
        //put carriage number into combo box
        ui->comboBox_3->addItem(QString::number(i));
    }

    //set seat detail
    int startIndex=startI=s_o[row]-1;
    int destIndex=destI=e_o[row]-1;

    for(int i=0;i<carriageSeat_num;i++){
        carriageSeat[i].clear();
    }
    QString com=QString("SELECT * FROM seat_table WHERE train_num=")+QString::fromStdString(temp)+"ORDER BY seat_code";
    query->exec(com);
    while (query->next()){
        //show all valid seat number
        bool valid=true;
        double currentSeatNumber=query->value(1).toDouble();    //1.01,2.01

        string seatCondition=query->value(dateDiff+2).toString().toStdString();
        for(int i=0;i<destIndex-startIndex+1;i++){
            //bitwise operation
            if(seatCondition[startIndex+i]=='n'){
                //not a valid seat
                valid=false;
                //qDebug()<<currentSeatNumber<<"******************";
                break;
            }
        }
        if(valid==true){
            //valid seat
            int latterNumber=(int)(round((currentSeatNumber-(int)currentSeatNumber)*100));
            //qDebug()<<(currentSeatNumber-(int)currentSeatNumber)*100<<"******************";

            carriageSeat[(int)currentSeatNumber-1].push_back(latterNumber);
        }
    }
    //put valid seat into combo box
    ui->comboBox_4->clear();
    bool noSeat=true;
    for(int i=0;i<carriageSeat_num;i++)
        if(carriageSeat[i].size()!=0){
            noSeat=false;
            break;
        }
    if((int)carriageSeat[0].size()==0){
        ui->comboBox_3->addItem(QString::number(0));
        ui->comboBox_4->addItem(QString::number(0));
    }else{
        for(int i=0;i<(int)carriageSeat[0].size();i++){
            ui->comboBox_4->addItem(QString::number(carriageSeat[0][i]));
        }
    }

    bool success=true;
    discreateSeat.clear();
    fromIndex.clear();
    toIndex.clear();
    if(noSeat==true){
        ui->label_13->show();
        //search discreate seat
        com=QString("SELECT * FROM seat_table WHERE t_num=")+QString::number(tempTrainNumber);
        query->exec(com);
        int walkStation=0;
        fromIndex.push_back(startIndex);
        while(startIndex+walkStation < destIndex){
            if(query->next()==NULL){
                //no valid discreate seat
                qDebug()<<"1583";
                success=false;
                break;
            }
            string seatCondition=query->value(dateDiff+2).toString().toStdString();
            if(seatCondition[startIndex+walkStation]=='y'){
                while(seatCondition[startIndex+walkStation]=='y'){
                    walkStation++;
                    if(startIndex+walkStation >= destIndex){
                        toIndex.push_back(destIndex);
                        //successful
                        break;
                    }

                }
                discreateSeat.push_back(query->value(1).toDouble());
                qDebug()<<"dis "<<query->value(1).toDouble();
                fromIndex.push_back(startIndex+walkStation);
                toIndex.push_back(startIndex+walkStation);
                qDebug()<<"index : "<<startIndex+walkStation;
                query->exec(com);
            }

            if(discreateSeat.size() > maxDiscreateSeat){
                //no more than 3 discreate tickets
                success=false;
                qDebug()<<discreateSeat.size();
                break;
            }

        }

        if(success==true){
            QString text="Discreate seat : \n";
            for(int i=0;i<(int)discreateSeat.size();i++){
                QString ss,ds;
                indexToStation(tempTrainNumber,fromIndex[i],toIndex[i],ss,ds);
                text=text+ss+" to "+ds+" : ";
                text=text+QString::number(discreateSeat[i])+" \n";
            }
            ui->label_13->show();
            ui->label_13->setText(text);
            ui->pushButton_10->show();
            ui->comboBox_3->hide();
            ui->comboBox_4->hide();
            ui->pushButton_6->hide();
            ui->label_5->hide();
            ui->label_6->hide();
            nost=true;
        }
        else{
            ui->label_13->setText("NO SEAT");
            ui->label_13->show();
            ui->comboBox_3->hide();
            ui->comboBox_4->hide();
            ui->pushButton_6->hide();
            ui->label_5->hide();
            ui->label_6->hide();
            nost=false;
        }
    }


    a.setTrainType(type[row]);
    //train type
    a.setSeatNumber(ui->comboBox_4->currentText().toDouble());
    //get seat number
    a.setTrainDate(ui->calendarWidget->selectedDate());
    //get depart date(calendar)

    item=ui->tableWidget->item(row,0);
    QString ss=item->text();
    QTime st=QTime::fromString(ss);
    a.setstartTime(st);
    //get depart time

    item=ui->tableWidget->item(row,1);
    ss=item->text();
    st=QTime::fromString(ss);
    a.setArriveTime(st);
    //arrive time


    QString info="("+QString::number(a.getCode())+",";
    info+="'"+(a.getStart())+"',";
    info+="'"+(a.getDest())+"',";
    info+=QString::number(a.getTrainNumber())+",";

    reserveCom1=info.toStdString();

    if(success==true && noSeat==true){
        if(discreateSeat.size()>=1){
            info="("+QString::number(a.getCode())+",";
            QString startS;
            QString destS;
            indexToStation(a.getTrainNumber(),fromIndex[0],toIndex[0],startS,destS);
            info+="'"+(startS)+"',";
            info+="'"+(destS)+"',";
            info+=QString::number(a.getTrainNumber())+",";
            reserveCom1=info.toStdString();
            if(discreateSeat.size()>=2){
                info="("+QString::number(a.getCode())+",";
                indexToStation(a.getTrainNumber(),fromIndex[1],toIndex[1],startS,destS);
                info+="'"+(startS)+"',";
                info+="'"+(destS)+"',";
                info+=QString::number(a.getTrainNumber())+",";
                reserveCom12=info.toStdString();
                if(discreateSeat.size()>=3){
                    info="("+QString::number(a.getCode())+",";
                    indexToStation(a.getTrainNumber(),fromIndex[2],toIndex[2],startS,destS);
                    info+="'"+(startS)+"',";
                    info+="'"+(destS)+"',";
                    info+=QString::number(a.getTrainNumber())+",";
                    reserveCom13=info.toStdString();
                }
            }

        }
    }


    QString info2;
    //info+=QString::number(a.getSeatNumber())+",";
    int y,m,d;
    a.getTrainDate().getDate(&y,&m,&d);
    //qDebug()<<a.getTrainDate();
    QString day="'"+QString::number(y)+"-"+QString::number(m)+"-"+QString::number(d)+"'";
    info2=day+",";
    info2+="'"+a.getstartTime().toString()+"',";
    info2+=+"'"+a.getArrivalTime().toString()+"',";
    info2+="'"+a.getTrainType()+"',";
    info2+="'0','0',0,'normal')";

    reserveCom2=info2.toStdString();

    for(int j=0;j<ui->tableWidget->rowCount();j++){
        ui->tableWidget->cellDoubleClicked(j,0);

        if(j==row)
            for(int i=0;i<ui->tableWidget->columnCount();i++){
                ui->tableWidget->item(j,i)->setBackground(QBrush(Qt::green));
            }
        else{
            for(int i=0;i<ui->tableWidget->columnCount();i++){
                ui->tableWidget->item(j,i)->setBackground(QBrush(Qt::white));
            }
        }

    }
    //com="INSERT INTO "+clientName+" VALUES "+info.toStdString();
    //qDebug()<<QString::fromStdString(reserveCom1)<<QString::fromStdString(reserveCom2);
    //query->exec(QString::fromStdString(com));

    //add ticket for specific client
}


void Form::on_tableWidget_2_cellActivated(int row, int column)
{
    if(state==2){
        double_state2=true;
        ui->pushButton_7->show();
        ui->comboBox_10->show();
        ui->comboBox_11->show();
        ui->comboBox->show();
        ui->comboBox_2->show();
        ui->pushButton_9->show();
        ui->comboBox_6->hide();
        ui->comboBox_7->hide();
        QTableWidgetItem *item;

        QDate tableDate;
        QString type;
        int number;
        QString startStop;
        QString endStop;
        QTime departTime;
        QTime endTime;
        double seatNumber;
        string bentom;
        string bentov;
        int specialServing;
        string identity;
        QDate day;



        //get train type
        type=Form::type[row];

        //get train number
        number=Form::train_num[row].toInt();
        tempTrainNumber=number;

        item=ui->tableWidget_2->item(row,0);
        string processDate=item->text().toStdString();
        int y,m,d;
        int ind=0;
        int pred=0;
        ind=processDate.find_first_of("-",ind);
        y=stoi(processDate.substr(pred,ind-pred));
        pred=ind+1;
        ind++;

        ind=processDate.find_first_of("-",ind);
        m=stoi(processDate.substr(pred,ind-pred));
        pred=ind+1;

        d=stoi(processDate.substr(pred));

        tableDate.setDate(y,m,d);
        qDebug()<<tableDate;
        tempSelectDate=tableDate;
        int dateDiff=tableDate.toJulianDay()-today.toJulianDay();
        tempDateDiff=dateDiff;
        QString com3=QString::fromStdString("SELECT city,min(num_order) from (SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info")+QString::number(dateDiff+1);
        QString tail=QString::fromStdString(") as a GROUP BY (t_num,CITY) HAVING t_num="+QString::number(number).toStdString()+"ORDER BY (min(num_order)) ");
        qDebug()<<"DIFF:"<<dateDiff;
        if(dateDiff==0){
            com3+=" ) as a WHERE dep_time>'"+ui->timeEdit_2->time().toString()+"'";
        }
        com3+=tail;
        qDebug()<<com3;
        query->exec(com3);
        ui->comboBox->clear();
        ui->comboBox_2->clear();
        while(query->next()){
            ui->comboBox->addItem(query->value(0).toString());
            ui->comboBox_2->addItem(query->value(0).toString());
            if(ui->comboBox->count()==1){
                combo_num=query->value(1).toInt();
            }
            if(ui->comboBox_2->count()==1)
                combo2_num=query->value(1).toInt();
        }

        //get start stop
        item=ui->tableWidget_2->item(row,2);
        startStop=item->text();
        tempStart=startStop;

        //get destination
        item=ui->tableWidget_2->item(row,3);
        endStop=item->text();
        tempDest=endStop;

        tempDateDiff=dateDiff;
        ui->comboBox->activated(0);
        ui->comboBox_2->activated(0);
        //get depart time
        item=ui->tableWidget_2->item(row,4);
        departTime=QTime::fromString(item->text());

        //get arrival time
        item=ui->tableWidget_2->item(row,5);
        endTime=QTime::fromString(item->text());

        //get seat number
        item=ui->tableWidget_2->item(row,6);
        seatNumber=item->text().toDouble();
        tempSeat=seatNumber;





        string com;

        currentCarriageNumber=carriageSeat_num;


        QString com2=QString::fromStdString("SELECT * FROM "+nowct->clientName)+" WHERE startlocation='"+startStop+"' and destination='"+endStop+"' and trainnumber="+QString::number(number)+" and traintype='"+type+"'";
        query->exec(com2);
        qDebug()<<com2;


        bool notfound=true;
        while(query->next()){

            if(query->value(4).toDouble()==seatNumber){
                if(query->value(5).toDate()==tableDate){
                    //find
                    notfound=false;
                    tempCode=query->value(0).toInt();
                    com="SELECT * FROM(SELECT* FROM needed_train_info UNION SELECT* FROM needed_train_info"+QString::number(tempDateDiff+1).toStdString()+")as a WHERE t_num="+QString::number(number).toStdString()+" ORDER BY num_order";
                    query->exec(QString::fromStdString(com));
                    int startIndex=-1;
                    int destIndex=-1;
                    while(query->next()){
                        if(query->value(1).toString()==startStop&&query->value(13).toTime()==departTime){
                            startIndex=query->value(4).toInt()-1;
                            continue;
                        }
                        if(query->value(1).toString()==endStop&&query->value(12).toTime()==endTime){
                            destIndex=query->value(4).toInt()-1;
                            break;
                        }
                    }
                    startI=startIndex;
                    destI=destIndex;
                    if(startIndex==-1 || destIndex==-1){
                        qDebug()<<"ERROR!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
                        qDebug()<<"line 2046";
                    }
                    tempDateDiff=tableDate.toJulianDay()-today.toJulianDay();
                    tempSeat=seatNumber;

                    //let user to modify start and destination
                    ui->pushButton_6->show();
                    ui->comboBox_10->show();
                    ui->comboBox_11->show();
                    ui->comboBox_6->hide();
                    ui->comboBox_7->hide();
                    break;
                }
            }
        }

        if(notfound){
            qDebug()<<"Error!!!!!!!!!!!!!!!!!!!!!!";
            qDebug()<<"2091";
        }



        //to see whether the code have two tickets
        com="SELECT * FROM "+nowct->clientName+" WHERE code="+QString::number(tempCode).toStdString();
        query->exec(QString::fromStdString(com));
        ticketNumber=query->size();


        for(int i=0;i<ui->tableWidget_2->rowCount();i++){
            for(int j=0;j<ui->tableWidget_2->columnCount();j++){
                item=ui->tableWidget_2->item(i,j);
                item->setBackground(QColor(255,255,255));
            }
        }
        int loc;
        if(ui->tableWidget_2->rowCount()!=0){
            pred=-1;
            loc=ui->tableWidget_2->item(0,11)->text().toInt();
            changeRowColor2(0);
            bool colorChange=true;  //store the state of the before one
            for(int i=1;i<ui->tableWidget_2->rowCount();i++){
                pred=loc;
                loc=ui->tableWidget_2->item(i,11)->text().toInt();
                if(pred==loc){
                    if(colorChange==true){
                        changeRowColor2(i);
                    }
                }
                else{
                    if(colorChange==true){
                        colorChange=false;
                    }
                    else if(colorChange==false){
                        colorChange=true;
                        changeRowColor2(i);
                    }
                }

            }
        }

        item=ui->tableWidget_2->item(row,11);
        int tc=item->text().toInt();
        for(int j=0;j<ui->tableWidget_2->rowCount();j++){
            item=ui->tableWidget_2->item(j,11);
            int currentCode=item->text().toInt();
            if(currentCode==tc){
                for(int k=0;k<ui->tableWidget_2->columnCount();k++){
                    item=ui->tableWidget_2->item(j,k);
                    item->setBackground(QColor(0,255,0));
                }
            }

        }

    }
    else if(state==4){
        QTableWidgetItem *item;

        for(int i=0;i<ui->tableWidget_2->rowCount();i++){
            for(int j=0;j<ui->tableWidget_2->columnCount();j++){
                item=ui->tableWidget_2->item(i,j);
                item->setBackground(QColor(255,255,255));
            }
        }
        int loc,pred;
        if(ui->tableWidget_2->rowCount()!=0){
            pred=-1;
            loc=ui->tableWidget_2->item(0,11)->text().toInt();
            changeRowColor2(0);
            bool colorChange=true;  //store the state of the before one
            for(int i=1;i<ui->tableWidget_2->rowCount();i++){
                pred=loc;
                loc=ui->tableWidget_2->item(i,11)->text().toInt();
                if(pred==loc){
                    if(colorChange==true){
                        changeRowColor2(i);
                    }
                }
                else{
                    if(colorChange==true){
                        colorChange=false;
                    }
                    else if(colorChange==false){
                        colorChange=true;
                        changeRowColor2(i);
                    }
                }

            }
        }

        item=ui->tableWidget_2->item(row,11);
        int tc=item->text().toInt();
        for(int j=0;j<ui->tableWidget_2->rowCount();j++){
            item=ui->tableWidget_2->item(j,11);
            int currentCode=item->text().toInt();
            if(currentCode==tc){
                for(int k=0;k<ui->tableWidget_2->columnCount();k++){
                    item=ui->tableWidget_2->item(j,k);
                    qDebug()<<QString::number(j)<<QString::number(k);
                    item->setBackground(QColor(0,255,0));
                }
            }

        }
        QString text;
        item=ui->tableWidget_2->item(row,11);
        int tempc=item->text().toInt();
        QString com=QString::fromStdString("SELECT * FROM "+nowct->clientName+" WHERE code=")+QString::number(tempc);
        query->exec(com);
        query->next();
        text="Date : "+query->value(5).toString()+"\n";
        text=text+"Type and number : "+query->value(8).toString()+query->value(3).toString()+"\n";
        com=QString::fromStdString("SELECT * FROM "+nowct->clientName+" WHERE code=")+QString::number(tempc);
        query->exec(com);
        while(query->next()){
            text=text+"Start Location : "+query->value(1).toString()+"\n";
            text=text+"Destination : "+query->value(2).toString()+"\n";
            text=text+"Seat number : "+query->value(4).toString()+"\n";
        }
        com=QString::fromStdString("SELECT * FROM "+nowct->clientName+" WHERE code=")+QString::number(tempc);
        query->exec(com);
        query->next();
        text=text+"Start time : "+query->value(6).toString()+"\n";
        text=text+"End time : "+query->value(7).toString()+"\n";
        text=text+"meat bento : "+query->value(9).toString()+"\n";
        text=text+"vegetable bento : "+query->value(10).toString()+"\n";
        int ss=query->value(11).toInt();
        if(ss==1){
            text=text+"Special serving : Yes\n";
        }
        else{
            text=text+"Special serving : No\n";
        }
        text=text+"Identity : "+query->value(12).toString();



        dia.showtable(text);
        dia.show();
    }
}


void Form::on_tableWidget_3_cellActivated(int row, int column)
{

    clickedSearch=false;
    //press the ticket row
    //check the matched tickets
    //for other serving
    QTableWidgetItem *item;

    QDate tableDate;
    QString type;
    int number;
    QString startStop;
    QString endStop;
    QTime departTime;
    QTime endTime;
    double seatNumber;
    string bentom;
    string bentov;
    int specialServing;
    string identity;
    QDate day;



    //get train type
    string row1Item;

    number=train_num[row].toInt();
    type=Form::type[row];
    tempTrainNumber=number;


    //get start stop
    item=ui->tableWidget_3->item(row,2);
    startStop=item->text();
    tempStart=startStop;

    //get destination
    item=ui->tableWidget_3->item(row,3);
    endStop=item->text();
    tempDest=endStop;

    //get depart time
    item=ui->tableWidget_3->item(row,4);
    departTime=QTime::fromString(item->text());

    //get arrival time
    item=ui->tableWidget_3->item(row,5);
    endTime=QTime::fromString(item->text());

    //get seat number
    item=ui->tableWidget_3->item(row,6);
    seatNumber=item->text().toDouble();

    //get bento meat
    item=ui->tableWidget_3->item(row,7);
    bentom=item->text().toStdString();

    //get bento vegetable
    item=ui->tableWidget_3->item(row,8);
    bentov=item->text().toStdString();

    //get special serving
    item=ui->tableWidget_3->item(row,9);
    string temp=item->text().toStdString();
    if(temp=="YES"){
        specialServing=1;
    }
    else{
        specialServing=0;
    }

    //get identity
    item=ui->tableWidget_3->item(row,10);
    identity=item->text().toStdString();


    //get date
    //day=ui->calendarWidget->selectedDate();

    item=ui->tableWidget_3->item(row,0);
    string processDate=item->text().toStdString();
    int y,m,d;
    int ind=0;
    int pred=0;

    ind=processDate.find_first_of("-",ind);
    y=stoi(processDate.substr(pred,ind-pred));
    pred=ind+1;
    ind++;

    ind=processDate.find_first_of("-",ind);
    m=stoi(processDate.substr(pred,ind-pred));
    pred=ind+1;



    d=stoi(processDate.substr(pred));



    tableDate.setDate(y,m,d);
    qDebug()<<tableDate;
    tempSelectDate=tableDate;




    string com;
    QString com2=QString::fromStdString("SELECT * FROM "+nowct->clientName)+" WHERE startlocation='"+startStop+"' and destination='"+endStop+"' and trainnumber="+QString::number(number)+" and traintype='"+type+"'";
    query->exec(com2);
    bool notfound=true;
    while(query->next()){
        qDebug()<<query->value(5);
        if(query->value(6).toTime()==departTime){
            if(query->value(7).toTime()==endTime){
                if(query->value(4).toDouble()==seatNumber){
                    if(query->value(5).toDate()==tableDate){
                        //find
                        notfound=false;
                        special.setCode(query->value(0).toInt());
                        Bento temp;
                        temp.setMeat(query->value(9).toString().toStdString());
                        temp.setVeg(query->value(10).toString().toStdString());
                        special.setbento(temp);
                        break;
                    }
                }
            }
        }

    }
    if(notfound){
        qDebug()<<"Error!!!!!";
        qDebug()<<"2217";
    }

    ui->label_2->hide();//train code
    ui->label_3->show();//identity normal,pregnant,kid,elder,alone
    ui->label_4->show();//serving item->1.special care(normalcannot)
    //2.bento
    ui->label_5->hide();//1.care:content:vency sofa,small chair,supporting,big dolls 2.total bento number
    ui->label_6->hide();//photo showing
    ui->label_7->show();//1.care:running content to show some advice 2.bento:for type number!
    ui->label_8->show();//for the success or fail
    ui->label_9->hide();
    ui->label_15->show();
    ui->label_16->show();
    ui->calendarWidget->hide();//for date choose
    ui->dateEdit->hide();
    ui->timeEdit->hide();//for time choose
    ui->comboBox->show();//to //choose for identity
    //ui->comboBox->clear();
    ui->comboBox_2->show();//to //choose for serving item
    //ui->comboBox_2->clear();
    ui->comboBox_3->hide();//train number choose
    ui->comboBox_3->clear();
    ui->comboBox_4->hide();//seat number choose
    ui->comboBox_4->clear();
    ui->pushButton_6->hide();//enter
    ui->pushButton_7->hide();//delete
    //-------------------------context--------------------
    ui->label_2->setText("Tickets Code");
    ui->label_3->setText("From");
    ui->label_4->setText("To");
    ui->label_15->setText("Identity");
    ui->label_16->setText("Serving item");
    //      ui->label_5->setText("Train num");
    //      ui->label_6->setText("Seat num");
    ui->label_7->setText("");
    //ui->calendarWidget->setSelectedDate(b.getTrainDate());
    ui->calendarWidget->setEnabled(true);
    //ui->dateEdit->setDate(b.getTrainDate());
    ui->dateEdit->setEnabled(true);
    //ui->timeEdit->setTime(b.getstartTime());
    ui->timeEdit->setEnabled(true);
    //combobox
    ui->comboBox_8->show();
    ui->comboBox_9->show();

    //       ui->comboBox->addItem(QString::fromStdString(b.getStart()));
    ui->comboBox_8->clear();

    ui->comboBox_8->addItem("Normal");
    ui->comboBox_8->addItem("Pregnant");
    ui->comboBox_8->addItem("Kid");
    ui->comboBox_8->addItem("Elder");
    ui->comboBox_8->addItem("Alone");
    ui->radioButton->setText("YES");
    ui->radioButton_2->setText("NO");//qDebug()<<"****************************";
    QString text="SELECT * FROM "+QString::fromStdString(nowct->clientName)+" WHERE code="+QString::number(special.getCode());
    query->exec(text);
    query->next();
    //qDebug()<<text;
    int s=query->value(11).toString().toInt();
    if(s){
        ui->radioButton->click();
    }
    else
        ui->radioButton_2->click();

    /*
    for(int j=0;j<ui->tableWidget_3->rowCount();j++){
        if(j==row)
            for(int i=0;i<ui->tableWidget_3->columnCount();i++){
                 ui->tableWidget_3->item(j,i)->setBackground(QBrush(Qt::green));
            }
        else{
            for(int i=0;i<ui->tableWidget_3->columnCount();i++){
                 ui->tableWidget_3->item(j,i)->setBackground(QBrush(Qt::white));
            }
        }
}*/
    for(int i=0;i<ui->tableWidget_3->rowCount();i++){
        for(int j=0;j<ui->tableWidget_3->columnCount();j++){
            item=ui->tableWidget_3->item(i,j);
            item->setBackground(QColor(255,255,255));
        }
    }
    int loc;
    if(ui->tableWidget_3->rowCount()!=0){
        pred=-1;
        loc=ui->tableWidget_3->item(0,11)->text().toInt();
        changeRowColor3(0);
        bool colorChange=true;  //store the state of the before one
        for(int i=1;i<ui->tableWidget_3->rowCount();i++){
            pred=loc;
            loc=ui->tableWidget_3->item(i,11)->text().toInt();
            if(pred==loc){
                if(colorChange==true){
                    changeRowColor3(i);
                }
            }
            else{
                if(colorChange==true){
                    colorChange=false;
                }
                else if(colorChange==false){
                    colorChange=true;
                    changeRowColor3(i);
                }
            }

        }
    }

    item=ui->tableWidget_3->item(row,11);
    int tc=item->text().toInt();
    for(int j=0;j<ui->tableWidget_3->rowCount();j++){
        item=ui->tableWidget_3->item(j,11);
        int currentCode=item->text().toInt();
        if(currentCode==tc){
            for(int k=0;k<ui->tableWidget_3->columnCount();k++){
                item=ui->tableWidget_3->item(j,k);
                qDebug()<<QString::number(j)<<QString::number(k);
                item->setBackground(QColor(0,255,0));
            }
        }

    }
}


void Form::on_comboBox_11_activated(int index)
{
    index=-1;
    if((index=ui->comboBox_11->findText(tempDest))!=-1){
        ui->comboBox_11->removeItem(index);
    }
}

