#include "editquerymodel.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
editQueryModel::editQueryModel()
{

}

bool editQueryModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // 1. 判断是否有效的列
    if(index.column() < 0 || index.column() > this->columnCount())
        return false;
    // 2. 获取列所对应的id
    QModelIndex prinmaryIndex = QSqlQueryModel::index(index.row(), 0);
    QString id = this->data(prinmaryIndex).toString();  // 获取字段表中的id值
    // 在修改行之前，将数据清除，把整个model清空
    this->clear();
    bool flag;
    // 3.根据需求来修改所对应的列
   // if(index.column() == 2)
   // {
        flag = setName(index.column(),id, value.toString());
   // }
    //刷新数据
    QString s="select * from info";
    refresh(s);
    return flag;
}

Qt::ItemFlags editQueryModel::flags(const QModelIndex &index) const
{
    // 1. 获取当前单位格的编辑状态
    Qt::ItemFlags flag = QSqlQueryModel::flags(index);
    // 2.给现有的标志增加一个可编辑的标志
   // if(index.column() == 2)
        flag = flag | Qt::ItemIsEditable; //给它设置一个可编辑的状态
    return flag;
}

void editQueryModel::refresh(const QString &sqlstr)
{
    //相当于将数据库的数据查询出来，转换成一个model
    setQuery(sqlstr);

}

bool editQueryModel::setName(int Cindex,QString useId, const QString &value)
{
    qDebug()<<Cindex;
    //相当于一个刷新的操作
    QSqlQuery query;
    QString cName;
    switch (Cindex) {
    case 1:
        cName="引种年月";
        break;
    case 2:
        cName="品种";
        break;
    case 3:
        cName="祖代引种";
        break;
    default:
        break;
    }
       qDebug() << cName;
    QString sqlstr="update info set " + cName + " = " + value + " where id = " + useId;
    query.exec(sqlstr);
//    query.prepare("update info set " + cName + " = " + value + " where id = " + useId); // ?表示占位符
//    query.addBindValue(value);
//    query.addBindValue(useId);

        qDebug()<<sqlstr;

    return query.exec();
}

