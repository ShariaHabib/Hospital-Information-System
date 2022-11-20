#include "login.h"
#include "ui_login.h"
#include<QScrollArea>
#include<QPixmap>
#include<QtSql>
#include<QDebug>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QGridLayout>
#include<QFrame>
#include<QLineEdit>
#include<QPixmap>
#include<QEvent>
#include<QString>
#include<string>
#include<qlist.h>
#include<regex>

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    ui->scrollContents->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->scrollContents->resize(ui->scrollArea->size().width(),ui->scrollArea->size().height());
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(ui->scrollContents);
    ui->scrollContents->adjustSize();

    connOpen();
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQueryModel * modal1 = new QSqlQueryModel();


    QSqlQuery *qry = new QSqlQuery(mydb);
    QSqlQuery *qry1 = new QSqlQuery(mydb);

    qry->prepare("SELECT HospitalName FROM AllData");
    qry1->prepare("SELECT address FROM AllData");

    qry->exec();
    qry1->exec();

    modal->setQuery(*qry);
    modal1->setQuery(*qry1);

    QGridLayout *lay = new QGridLayout(this);
    QPushButton *name[100];

    for(int j=0;j<=modal->rowCount()-1;j++)
     {
        QString str=modal->record(j).value(0).toString();
        QString str1=modal1->record(j).value(0).toString();

    name[j]=new QPushButton(str);
    QLabel *lab =new QLabel("Address: "+str1+"");

    QFrame *line;

    line=new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("background:gray");

    name[j]->setObjectName("btn1");
    name[j]->setStyleSheet("QPushButton#btn1{background:transparent;Text-alignn:left;font-family:montserrat;font-size:18px;color:black;}"
                           "QPushbutton#btn1:hover{color:white;Font-size:14px;}");

    lab->setStyleSheet("background:transparent;Text-alignn:center;font-family:montserrat;font-size:14px;color:red;");

    lay->addWidget(name[j]);
    lay->addWidget(lab);
    lay->addWidget(line);

    connect(name[j],SIGNAL(clicked()),this,SLOT(onnameclicked()));
    }
           ui->scrollContents->setLayout(lay);
           connClose();
           ui->frame_2->hide();
}



login::~login()
{
    delete ui;
}


QString buttonText;
int login::x=0;
QPushButton *pushbutton[1000];


void login::onnameclicked(){
  //  ui->frame_2->setGeometry(650,130,681,741);

    ui->frame_2->show();
    pushbutton[x]=new(QPushButton);
    pushbutton[x]=qobject_cast<QPushButton*>(sender());

   if(x>0)
   {
        pushbutton[x-1]->setObjectName("btn1");
       pushbutton[x-1]->setStyleSheet("QPushButton#btn1{background:transparent;Text-alignn:left;font-family:montserrat;font-size:18px;color:black;}"
                                       "QPushbutton#btn1:hover{color:white;Font-size:14px;}");
   }

    pushbutton[x]->setStyleSheet("Text-alignn:left;font-family:montserrat;font-size:18px;color:blue;");

    buttonText=pushbutton[x]->text();
    ui->label->setText(buttonText);
    ui->label->setStyleSheet("Text-alignn:left;font-family:montserrat;font-size:20px;color:black;");
    ui->label_2->setStyleSheet("Text-alignn:left;font-family:montserrat;font-size:20px;color:black;");

    connOpen();


    QSqlQuery qry;
    qry.prepare("SELECT * FROM AllData WHERE HospitalName='"+buttonText+"'");
    if(qry.exec())
    {
        while(qry.next()){
            ui->label->setWordWrap(true);
            //ui->label->adjustSize();
            ui->label->setText("Doctors : "+qry.value(5).toString());
            ui->label_2->setText("Diseases : "+qry.value(6).toString());
            x++;

            connClose();
        }
    }
}



void login::on_pushButton_clicked()//LOGINPART
{
    QString username,password;
    username=ui->lineEdit_U->text();
    password=ui->lineEdit_P->text();

    if(!connOpen())
    {
          QMessageBox::warning(this,"WARNING","Not connected");
    }

    connOpen();
    QSqlQuery qry;
    if(qry.prepare("SELECT * FROM AllData WHERE username='"+username+"' AND password='"+password+"'"))

   if(qry.exec())
     {
                int count=0;
               while(qry.next())
               {
                   count++;

               }
               if(count==1)
               {
                QMessageBox::information(this,"Successful","Login Successful");
                dialog=new Dialog();
                dialog->show();

                connClose();
               }
               else
                {
                   QMessageBox::warning(this,"Unsuccessful","Login Unsuccessful");
               }
     }
}

void login::on_pushButton_2_clicked() // Search
{
    connOpen();
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQueryModel * modal1 = new QSqlQueryModel();
    QSqlQueryModel * modal2 = new QSqlQueryModel();
    QSqlQueryModel * modal3 = new QSqlQueryModel();



     QSqlQuery *qry = new QSqlQuery(mydb);
     QSqlQuery *qry1 = new QSqlQuery(mydb);
     QSqlQuery *qry2 = new QSqlQuery(mydb);
     QSqlQuery *qry3 = new QSqlQuery(mydb);

     qry->prepare("SELECT HospitalName FROM AllData");
     qry1->prepare("SELECT address FROM AllData");
      qry2->prepare("SELECT Doctors FROM AllData");
       qry3->prepare("SELECT Diseases FROM AllData");

     qry->exec();
     qry1->exec();
     qry2->exec();
     qry3->exec();

     modal->setQuery(*qry);
     modal1->setQuery(*qry1);
     modal2->setQuery(*qry2);
 modal3->setQuery(*qry3);

     QVBoxLayout *lay=new QVBoxLayout(this);
     QString s=(ui->lineEdit->text());


int y=0;

     QPushButton *label;
     for(int j=0;j<=modal->rowCount()-1;j++)
{

         QString str=modal->record(j).value(0).toString();
         QString str1=modal1->record(j).value(0).toString();
         QString str2=modal2->record(j).value(0).toString();
         QString str3=modal3->record(j).value(0).toString();


      /// int x=QString::compare(s,str1,Qt::CaseInsensitive);






//            QStringList str2;
//             for(int j=0;j<=modal1->rowCount();j++)
//             {

//                         //QString  str;
//                 //while(qry1->next())
//               // str.append(modal->record(j).value(0).toString());
//                 //str2.append(modal1->record(j).value(0).toString());


//             int x=0;
//                 for(int i=0;i<str2.size();i++)
//                 {
//                   const QString &st = str2.at(i);
//                      if (st.contains(s))
//                        x=1;


        // if(str1.contains(s))
         if(str1.contains(s,Qt::CaseInsensitive)||str2.contains(s,Qt::CaseInsensitive)||str3.contains(s,Qt::CaseInsensitive))
{
           if(ui->scrollContents->layout()!=NULL)
           {
               QLayoutItem *item;
               while((item=ui->scrollContents->layout()->takeAt(0))!=NULL){
                   delete item->widget();
                   delete item;

               }
               delete ui->scrollContents->layout();
           }

           ui->frame_2->hide();

        label = new QPushButton(str);
        label->setObjectName(str);




          QLabel *lab = new QLabel("Adress:"+str1+"");

           QFrame *line=new QFrame;
           line->setFrameShape(QFrame::HLine);
           line->setFrameShadow(QFrame::Sunken);
           line->setStyleSheet("backgrond:white");


           label->setStyleSheet("QPushButton{background:transparent;Text-alignn:left;font-family:montserrat;font-size:20px;color:black;}"
                                "QPushbutton:hover{color:white;}");



                   lay->addWidget(label);
                   lay->addWidget(lab);
                   lay->addWidget(line);

                  connect(label,SIGNAL(clicked()),this,SLOT(onnameclicked()));

                y=1;
              }

          }
     if(y==0)
        { QMessageBox::warning(this,"Not Found","No Match Found");}

     ui->scrollContents->setLayout(lay);
//     ui->scrollArea->setWidgetResizable(true);
//  ui->scrollArea->setWidget(ui->scrollContents);
//  ui->scrollContents->adjustSize();

     ui->scrollContents->setVisible(true);
     ui->scrollContents->show();


}

void login::on_pushButton_3_clicked()
{
    {
        QLayoutItem *item;
        while((item=ui->scrollContents->layout()->takeAt(0))!=NULL){
        delete item->widget();
        delete item;

    }
    delete ui->scrollContents->layout();
    x=0;
}
    connOpen();
    QSqlQueryModel * modal = new QSqlQueryModel();
    QSqlQueryModel * modal1 = new QSqlQueryModel();


    QSqlQuery *qry = new QSqlQuery(mydb);
     QSqlQuery *qry1 = new QSqlQuery(mydb);

    qry->prepare("SELECT HospitalName FROM AllData");
    qry1->prepare("SELECT address FROM AllData");

    qry->exec();
    qry1->exec();

    modal->setQuery(*qry);
    modal1->setQuery(*qry1);

    QGridLayout *lay = new QGridLayout(this);
    QPushButton *name[100];

    for(int j=0;j<=modal->rowCount()-1;j++)
      {
        QString str=modal->record(j).value(0).toString();
        QString str1=modal1->record(j).value(0).toString();

    name[j]=new QPushButton(str);
    QLabel *lab =new QLabel("Address: "+str1+"");

    QFrame *line;

    line=new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("background:gray");

    name[j]->setObjectName("btn1");
    name[j]->setStyleSheet("QPushButton#btn1{background:transparent;Text-alignn:left;font-family:montserrat;font-size:18px;color:black;}"
                           "QPushbutton#btn1:hover{color:white;Font-size:14px;}");

    lab->setStyleSheet("background:transparent;Text-alignn:center;font-family:montserrat;font-size:14px;color:red;");

    lay->addWidget(name[j]);
    lay->addWidget(lab);
    lay->addWidget(line);

    connect(name[j],SIGNAL(clicked()),this,SLOT(onnameclicked()));
    }
           ui->scrollContents->setLayout(lay);
           connClose();
           ui->frame_2->hide();
}






