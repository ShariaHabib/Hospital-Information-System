#ifndef LOGIN_H
#define LOGIN_H
#include<dialog.h>
#include <QMainWindow>
#include<QtSql>
#include<QSqlDatabase>
#include<QDebug>
#include<QFileInfo>


QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QMainWindow
{
    Q_OBJECT
public slots:
    void onnameclicked();
public:
    static int x;
     QSqlDatabase mydb;

     void connClose(){
         mydb.close();
         mydb.removeDatabase(QSqlDatabase::defaultConnection);
     }

     bool connOpen()
     { QString path = QDir(QCoreApplication::applicationDirPath()).filePath("database.db");
         mydb=QSqlDatabase::addDatabase("QSQLITE");
         mydb.setDatabaseName(path);

         if(!mydb.open())
         {
             qDebug()<<("Not opened");
         return false;
         }
         else
             {
             qDebug()<<("CONNECTED");
             return true;
         }
     }
public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::login *ui;
    Dialog *dialog;

};
#endif // LOGIN_H
