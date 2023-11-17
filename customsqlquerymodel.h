#ifndef CUSTOMSQLQUERYMODEL_H
#define CUSTOMSQLQUERYMODEL_H

#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QKeyEvent>
#include "globals.h"
class CustomSqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    explicit CustomSqlQueryModel(QObject *parent = nullptr) : QSqlQueryModel(parent) {}

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override
    {
       if (!index.isValid())
            return false;
        if (role != Qt::EditRole)
            return false;
        if(!db_conn.isOpen())
            db_conn.open();
        QString columnName = this->headerData(index.column(), Qt::Horizontal).toString();
        //QVariant newValue = value;
        QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
        QVariant primaryKeyValue = data(primaryKeyIndex);
        QModelIndex newValueIndex = QSqlQueryModel::index(index.row(), index.column());
        QVariant newValue = data(newValueIndex);
        QSqlQuery query(db_conn);
        query.prepare(QString("UPDATE " + db_tablename + " SET %1 = :value WHERE id = :id").arg(columnName));
        query.bindValue(":value", newValue);
        query.bindValue(":id", primaryKeyValue);
        qDebug()<<"NEW VALUE:"<<newValue;
        if (!query.exec()) {
           qDebug() << "保存数据时出错：" << query.lastError().text();
                                              return false;
        }else {
                                              qDebug()<<"Successfully";
                                              setQuery("select * from info");
                                     return true;
        }
   }
     Qt::ItemFlags flags(const QModelIndex &index) const override;
};


#endif // CUSTOMSQLQUERYMODEL_H
