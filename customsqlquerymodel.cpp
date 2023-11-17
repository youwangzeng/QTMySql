//customsqlquerymodel.cpp
#include "customsqlquerymodel.h"

//CustomSqlQueryModel::CustomSqlQueryModel(const QString &tn,QObject *parent) : QSqlQueryModel(parent),tablename(tn)
//{
//}

//Qt::ItemFlags CustomSqlQueryModel::flags(const QModelIndex &index) const
//{
//    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
//    flags |= Qt::ItemIsEditable; // 添加可编辑标志
//    return flags;
//}

//bool CustomSqlQueryModel::setData(const QModelIndex &index, const QVariant &value, int role)
//{
//    if (!index.isValid())
//        return false;

//    if (role != Qt::EditRole)
//        return false;

//    // 设置数据到模型
//    bool result = true;

//    if (result) {
//         qDebug()<<265;
//        // 保存数据到数据库
//        QString columnName = headerData(index.column(), Qt::Horizontal, Qt::DisplayRole).toString();
//        QVariant newValue = value;
//        // 获取编辑的行的主键值
//        QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
//        QVariant primaryKeyValue = data(primaryKeyIndex);
//        QSqlRecord record = this->record(index.row());
//        QString primaryKey = record.fieldName(0);
//        //QString primaryKeyValue = record.value(primaryKey).toString();
//        QSqlQuery query;
//        query.prepare(QString("UPDATE " + tablename + " SET %1 = :value WHERE id = :id").arg(columnName));
//        query.bindValue(":value", newValue);
//        query.bindValue(":id", primaryKeyValue);
//        qDebug()<<columnName<< newValue << primaryKeyValue;
//        if (!query.exec()) {
//            qDebug() << "保存数据时出错model：" << query.lastError().text();
//                                                  result = false;
//        }
//        setQuery("select * from " + tablename);
//    }

//    return result;

//    if (index.isValid() && role == Qt::EditRole) {
//        // 获取编辑的列名和对应的值
//        QString columnName = headerData(index.column(), Qt::Horizontal, Qt::DisplayRole).toString();
//        QVariant newValue = value;
//        // 获取编辑的行的主键值
//        QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
//        QVariant primaryKeyValue = data(primaryKeyIndex);
//        // 执行更新操作
//        QSqlQuery query;
//        query.prepare(QString("UPDATE " + tablename + " SET %1 = :value WHERE id = :id").arg(columnName));
//        query.bindValue(":value", newValue);
//        query.bindValue(":id", primaryKeyValue);
//        if (query.exec()) {
//            // 更新成功后，通知视图刷新数据
//            //dataChanged(index, index);
//           setQuery("select * from " + tablename);
//            return true;
//        } else {
//            // 更新失败，处理错误情况
//            qDebug()<<2222222<<query.lastError().text();
//      return false;
//        }
//    }


//}
Qt::ItemFlags CustomSqlQueryModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.isValid())
        flags |= Qt::ItemIsEditable;
    return flags;
}

