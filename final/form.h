//process the customer form
//need clinet data to store and record
#ifndef FORM_H
#define FORM_H
#define carriageSeat_num (12)
//---------------main system include-----------------
#include "QWidget"
#include "QTimer"
#include"QtDebug"
#include"QString"
#include<time.h>
#include<stdlib.h>
#include<QImage>
#include<QPixmap>
#include<QGraphicsPixmapItem>
#include<QGraphicsScene>
#include<QHoverEvent>
#include <set>
#include <QHeaderView>
#include"dialog.h"

#include <cmath>
#include <QSqlResult>
#include <QSqlDatabase>
#include <QSqlQuery>
#include<QLineEdit>
#include "simulation.h"
#include<stdlib.h>
#include<string.h>
//---------------main people---------------------
#include"networkclient.h"

//---------------main items----------------------
#include"tickets.h"
#include"package.h"
#include"bento.h"

//---------------UI Process----------------------
QT_BEGIN_NAMESPACE
namespace Ui { class Form;}
QT_END_NAMESPACE

class Form : public QWidget
{
    Q_OBJECT

public:
    Form(QWidget *parent = nullptr);
    ~Form();
    bool q;
    NetworkClient *NC;
    int state;//for the UI should shown when different keys
    //0 for nothing 1 for reserve 3 for other services 4 for check
    Client *nowct;//for current client
    vector<Ticket> *newT;//for buying
    QString running;//for running light
    bool nost;//for no seat
    int runbegin;
    int startdo;
    int changerun;//for runlight move
    QTimer rl,ti;//for run light
    QGraphicsScene* scene,*menu;
    void setQuery(QSqlQuery *q);
    Ui::Form *ui;
    QSqlQuery *query;
    Dialog dia;
public:
      bool eventFilter(QObject *obj, QEvent *event);

      void client_table_create();

signals:
    void signal_updateTable();
    void signal_updateTable3();
    void signal_modifyTwo();
    void signal_initialFromToCity();
private slots:
    void t_run();//for runnung light
    void timer();//for time view
    void on_pushButton_clicked();
    //reserve tickets

    void on_pushButton_2_clicked();
    //modify tickets

    void on_pushButton_3_clicked();
    //other serving

    void on_pushButton_4_clicked();
    //log out

    void on_pushButton_6_clicked();
    //enter (button)

    void on_pushButton_5_clicked();
    //check

    void on_dateEdit_dateChanged(const QDate &date);


    void on_calendarWidget_selectionChanged();


    void on_comboBox_5_textActivated(const QString &arg1);
    //ticket number change

    void on_pushButton_7_clicked();
    //delete



    void on_pushButton_8_clicked();



    //void on_comboBox_8_activated(const QString &arg1);

    void on_comboBox_8_currentIndexChanged(int index);

    //void on_comboBox_9_currentIndexChanged(int index);

    //void on_comboBox_9_textActivated(const QString &arg1);


    //void on_comboBox_11_activated(const QString &arg1);

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();


    void on_comboBox_6_activated(int index);

    void on_comboBox_7_activated(int index);

    void on_pushButton_11_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_3_stateChanged(int arg1);

    void on_comboBox_activated(int index);

    void on_comboBox_2_activated(int index);

    void on_timeEdit_timeChanged(const QTime &time);

    void on_comboBox_3_activated(int index);

    void on_comboBox_9_activated(int index);

    void on_comboBox_10_activated(int index);

    void on_tableWidget_cellActivated(int row, int column);

    void on_tableWidget_2_cellActivated(int row, int column);

    void on_tableWidget_3_cellActivated(int row, int column);

    void on_comboBox_11_activated(int index);

public slots:
    void showTable();
    void slot_updateTable3();
    void slot_updateTable2();
    void slot_initialFromToCity();
private:
    QTimer showSimul;
    void _hideall();
    QTime timeDiff(QTime t1,QTime t2);
    void QTimeToInt(QTime t,int &h,int &m,int &s);
    int stringToInt(string s);
    Ticket special; //a temporary object for current chosen ticket, use in special serving
    string reserveCom1;  //for reserve tickets used, choose seat
    string reserveCom12;
    string reserveCom13;
    string reserveCom2;     //for reserve, latter part of ticket
    const int seatInCarriage;   //40 in one carriage
    int currentCarriageNumber;  //the carriage number in this train
    vector <int> carriageSeat[carriageSeat_num];
    int tempTrainNumber;    //for the train that is reversed
    vector<QString> type;
    vector<QString>train_num;
    int tempDateDiff;
    int tempCode;
    int bug;
    QDate today;
    double tempSeat;
    QString tempStart;
    bool double_state2;
    QString tempDest;
    QDate tempSelectDate;
    int destI;
    int startI;
    int modifyIndex1;
    int modifyIndex2;
    vector<int>s_o;
    vector<int>e_o;
    vector <double> discreateSeat;
    vector <int> fromIndex;
    vector <int> toIndex;
    bool clickedSearch;
    void indexToStation(const int number,int start,int end,QString &startS,QString &destS);
    void stationToIndex(const int number,int &start,int &end,QString startS,QString destS,QTime dep,QTime arr);
    void changeRowColor2(int row);
    void changeRowColor3(int row);
    int ticketNumber;
    void checkLocation();
    void checkDate();
    void checkTime();
    void checkTimeDate();
    void checkLocTime();
    void checkLocDateTime();
};
#endif // FORM_H
