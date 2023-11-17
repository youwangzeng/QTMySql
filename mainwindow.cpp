#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globals.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui-> IPlineEdit->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->IPlineEdit->text()=="" or ui->DatabaseNamelineEdit->text()=="" or ui->UserlineEdit->text()=="" or ui->PasswordlineEdit->text()==""){
        QMessageBox::about(NULL, "提示", "\n请完善信息\t\n");
        return;
    }
    db_server=ui->IPlineEdit->text();
    db_databasename=ui->DatabaseNamelineEdit->text();
    db_userid=ui->UserlineEdit->text();
    db_password=ui->PasswordlineEdit->text();
    db_port=3306;
    Form_Main *fm=new Form_Main;
    db_conn.setHostName(db_server);  //连接本地主机
    db_conn.setPort(db_port);
    db_conn.setDatabaseName(db_databasename);
    db_conn.setUserName(db_userid);
    db_conn.setPassword(db_password);
    if (db_conn.open()){
        fm->show();
         return;
        //db_conn.close();
    }
    else {
        QMessageBox::warning(this,"错误", db_conn.lastError().text() );//打开失败,显示错误信息
        return;
    }

}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QWidget *currentFocusWidget = this->focusWidget();//QApplication::focusWidget();能够获取聚焦控件
    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    {
            if(currentFocusWidget->objectName()=="IPlineEdit"){
               ui-> DatabaseNamelineEdit->setFocus();
                return;
            }
            else if(currentFocusWidget->objectName()=="DatabaseNamelineEdit"){
               ui-> UserlineEdit->setFocus();
                return;
            }
            else if(currentFocusWidget->objectName()=="UserlineEdit"){
               ui-> PasswordlineEdit->setFocus();
                return;
            }
            else if(currentFocusWidget->objectName()=="PasswordlineEdit"){
               ui-> pushButton->setFocus();
                return;
            }
            else if(currentFocusWidget->objectName()=="pushButton"){
                MainWindow::on_pushButton_clicked();
                return;
            }
    }
    break;
    default:
            break;
    }
}

