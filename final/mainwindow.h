//process the log in form
//need clinet list to check for true log in
//need server list for server log
//date:11/23--->customer complete
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//---------------main QT include-----------------
#include <QMainWindow>
#include"QtDebug"
#include"form.h"
#include"dialog.h"
#include"networkclient.h"
#include"networkserver.h"
#include <QMainWindow>
#include <QSqlResult>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTimer>
#include "simulation.h"
#include"QtDebug"
#include"form.h"
#include"dialog.h"
#include "train.h"


//---------------main systems-------------------
#include"networkclient.h"
#include"networkserver.h"

//---------------UI Process----------------------
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlQuery *query;
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void on_pushButton_clicked();
    void t_changeform();//for check whether need to call back mainwindowns
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();


 //   void on_lineEdit_2_textEdited(const QString &arg1);

    void on_pushButton_4_clicked();


    void on_lineEdit_2_returnPressed();

    void changeTable();



private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
    QTimer simul;
    QTimer oneMin;
    QTimer showForm;
    Simulation s;


    QTimer tshow;//timer for show
    Form fo;
    int state;//for log or register 0 for nothing 1 for log 2 for register 3 for sucess 4 for fail
};
#endif // MAINWINDOW_H
