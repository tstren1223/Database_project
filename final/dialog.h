//process the staff form
#ifndef DIALOG_H
#define DIALOG_H

//---------------main QT include-----------------
#include "QDialog"
#include "QTimer"
#include"QtDebug"
#include"QString"

//---------------main people---------------------
#include"networkserver.h"

//---------------main items----------------------
#include"tickets.h"
#include"package.h"
#include"bento.h"

//---------------UI Process----------------------
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog;}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    bool q;
    QString s;
    void showtable(QString text);
    void showerror();
private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
