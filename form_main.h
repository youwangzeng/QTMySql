#ifndef FORM_MAIN_H
#define FORM_MAIN_H

#include "mainwindow.h"
#include "editquerymodel.h"
#include "customsqlquerymodel.h"
#include "customtableview.h"
#include <QWidget>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <qDebug>
#include <QList>
#include <QVBoxLayout>
namespace Ui {
class Form_Main;
}

class Form_Main : public QWidget
{
    Q_OBJECT

public:
    explicit Form_Main(QWidget *parent = nullptr);
    ~Form_Main();

private slots:
    void on_ShowDBpushButton_clicked();
//    void on_ShowTBpushButton_clicked();
//    void on_ShowDatapushButton_clicked();
    void on_ClearpushButton_clicked();
    void ClearInfo(void);
    void on_DatabaseNamecomboBox_currentTextChanged(const QString &arg1);
    void on_TableNamecomboBox_currentTextChanged(const QString &arg1);
    void on_ShowDTpushButton_clicked();
    //void keyPressEvent(QKeyEvent *);

private:
    Ui::Form_Main *ui;
    QSqlTableModel *myModel;
    QSqlQueryModel *model;
    CustomSqlQueryModel *c_model;
    QSqlQuery query();
    CustomTableView *ctableview;
};
#endif // FORM_MAIN_H
