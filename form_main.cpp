#include "form_main.h"
#include "ui_form_main.h"
#include "globals.h"

Form_Main::Form_Main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form_Main)

{
    ui->setupUi(this);
    //model= new QSqlQueryModel(ui->tableView);
    myModel=new QSqlTableModel(this);
    c_model=new CustomSqlQueryModel(this);
    ctableview= new CustomTableView(this);
    ui->verticalLayout_3->addWidget(ctableview);

}

Form_Main::~Form_Main()
{
    delete ui;
}

void Form_Main::on_ShowDBpushButton_clicked()
{
    if(!db_conn.isOpen())
        db_conn.open();
    ui->DatabaseNamecomboBox->clear();
    ui->TableNamecomboBox->clear();
    QSqlQuery query;
    query.exec("show databases;");
    while(query.next())
    {
        ui->DatabaseNamecomboBox->addItem(query.value(0).toString());
    }
    db_conn.close();
}

//void Form_Main::on_ShowTBpushButton_clicked()
//{
//    if(ui->DatabaseNamecomboBox->currentText().isEmpty()){
//        QMessageBox::about(this,"提示","数据库不能为空\t");
//            return;
//    }

//    ui->TableNamecomboBox->clear();

//    QSqlQuery query(MainWindow::db);
//    query.exec("use " + ui->DatabaseNamecomboBox->currentText());
//    query.exec("show tables;");
//    while(query.next())
//    {
//        ui->TableNamecomboBox->addItem(query.value(0).toString());
//    }
//}

//void Form_Main::on_ShowDatapushButton_clicked()
//{    if(ui->TableNamecomboBox->currentText().isEmpty()){
//        QMessageBox::about(this,"提示","数据表不能为空\t");
//        return;
//    }
//    model->clear();
//    myModel->clear();
//    model->setQuery("select * from " + ui->TableNamecomboBox->currentText());
//    ui->tableView->setModel(model);

//    //基本视图信息；
//    myModel = new QSqlTableModel(this);
//    myModel->setTable(ui->TableNamecomboBox->currentText());
//    myModel->select();  //加载数据
//    //数据网格信息加载
//    ui->tableView->setModel(myModel);
//}

void Form_Main::on_ClearpushButton_clicked()
{
    Form_Main::ClearInfo();
}

void Form_Main::ClearInfo()
{
    ui->DatabaseNamecomboBox->clear();
    ui->TableNamecomboBox->clear();
    c_model->clear();
    //model->clear();
    //myModel->clear();
}

void Form_Main::on_DatabaseNamecomboBox_currentTextChanged(const QString &arg1)
{
    if(ui->DatabaseNamecomboBox->currentText().isEmpty()){
            return;
    }
    db_conn.setDatabaseName(ui->DatabaseNamecomboBox->currentText());
    if(!db_conn.isOpen())
            db_conn.open();
    QSqlQuery query(db_conn);
    query.exec("use " + arg1);
    query.exec("show tables;");
    ui->TableNamecomboBox->clear();
    while(query.next())
    {
        ui->TableNamecomboBox->addItem(query.value(0).toString());
    }
    db_conn.close();
}

void Form_Main::on_TableNamecomboBox_currentTextChanged(const QString &arg1)
{
    if(ui->TableNamecomboBox->currentText().isEmpty()){
        return;
    }
    db_tablename=ui->TableNamecomboBox->currentText();
    if(!db_conn.isOpen())
        db_conn.open();
    c_model->clear();
        c_model->setQuery("select * from " + db_tablename);
        ctableview->setModel(c_model);
        db_conn.close();
}

void Form_Main::on_ShowDTpushButton_clicked()
{
        db_tablename="info";
    if(!(db_conn.open()))
        db_conn.open();
    c_model->setQuery("select * from " + db_tablename);
    ctableview->setModel(c_model);
}

//void Form_Main::keyPressEvent(QKeyEvent *event)
//{
//    QWidget *currentFocusWidget = this->focusWidget();
//    qDebug()<<currentFocusWidget->objectName();
//    if(ui->tableView->model()!=nullptr){
//    QItemSelectionModel* selectionModel = ui->tableView->selectionModel();
//    if (selectionModel->hasSelection()) {
//        QModelIndexList selectedIndexes = selectionModel->selectedIndexes();
//        if (!selectedIndexes.isEmpty()) {
//            QModelIndex selectedIndex = selectedIndexes.first();
//            int selectedRow = selectedIndex.row();
//            int selectedColumn = selectedIndex.column();
//            //处理获取到的行号和列号
//            qDebug()<<"行："<<selectedRow<<" 列："<<selectedColumn;
//            QModelIndex index = ui->tableView->model()->index(selectedRow, selectedColumn+1);
//            ui->tableView->setCurrentIndex(index);
//        }
//    }
//    }
//    if(currentFocusWidget->objectName()=="tableView"){
//    //qDebug()<< ui->tableView->selectionModel()->currentIndex().column();
//    switch (event->key()) {
//    case Qt::Key_Return:
//    case Qt::Key_Enter:
//        qDebug()<<"回车键事件";
//        break;
//    default:
//        break;
//    }}
//}

