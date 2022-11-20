#include "dialog.h"
#include "ui_dialog.h"
#include<QMessageBox>
#include<login.h>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)

{
    ui->setupUi(this);
    QSqlQueryModel * modal = new QSqlQueryModel();

    login sec;
    sec.connOpen();
    QSqlQuery *qry = new QSqlQuery(sec.mydb);

    qry->prepare("SELECT HospitalName,Address,Doctors,Diseases FROM Alldata");


    qry->exec();
    modal -> setQuery(*qry);
    ui->tableView->setModel(modal);
    on_pushButton_2_clicked();

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_2_clicked()
{
    ui->frame_2->show();
}

void Dialog::on_pushButton_clicked()
{
    login sec;
    QString hname,doc,dis,adr,row;
    hname=ui->lineEdithospital->text();
    doc=ui->lineEditdoc->text();
    dis=ui->lineEditdis->text();
    adr=ui->lineEditaddress->text();
    row=ui->lineEditrow->text();

    sec.connOpen();

    QSqlQuery qry;
    qry.prepare("update Alldata set Row='"+row+"',HospitalName='"+hname+"',Doctors='"+doc+"',Diseases='"+dis+"',address='"+adr+"' where Row='"+row+"'");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Update"),tr("Updated"));
        sec.connClose();

    }
    else
        QMessageBox::warning(this,tr("Error"),qry.lastError().text());

}

void Dialog::on_pushButton_3_clicked()
{
    login sec;
    QString hname,doc,dis,adr,row;
    hname=ui->lineEdithospital->text();
    doc=ui->lineEditdoc->text();
    dis=ui->lineEditdis->text();
    adr=ui->lineEditaddress->text();
    row=ui->lineEditrow->text();

    sec.connOpen();

    QSqlQuery qry;
    qry.prepare("insert into Alldata (Row,HospitalName,address,Doctors,Diseases) values ('"+row+"','"+hname+"','"+adr+"','"+doc+"','"+dis+"')");
    if(qry.exec())
    {
        QMessageBox::information(this,tr("Insert"),tr("Inserted"));
        sec.connClose();

    }
    else
        QMessageBox::warning(this,tr("Error"),qry.lastError().text());

    Dialog(parent);

}
