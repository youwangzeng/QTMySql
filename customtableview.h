#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QTableView>
#include <QKeyEvent>
#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QLineEdit>
#include "customsqlquerymodel.h"
#include "globals.h"

class CustomTableView : public QTableView
{
    Q_OBJECT

public:
    explicit CustomTableView(QWidget *parent = nullptr) : QTableView(parent) {}

protected:
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
            if(!db_conn.isOpen())
                db_conn.open();
           // if (state() == QAbstractItemView::EditingState) {
                QModelIndex current = currentIndex();
                if (current.isValid()) {
//                   if (!model()->setData(current, current.data())) {
//                       qDebug() << "保存数据时出错tableview"<<current.column()<<current.row()<<current.data();
//                    }
                    int nextRow = current.row();
                    int nextColumn = current.column() + 1;
                    if (nextColumn >= model()->columnCount()) {
                        nextColumn = 0;
                        nextRow++;
                    }
                    if (nextRow < model()->rowCount()) {
                        QModelIndex id_index = model()->index(currentIndex().row(),0);
                        QModelIndex up_index = model()->index(currentIndex().row(),current.column());
                        QVariant id_value = model()->data(id_index,Qt::DisplayRole);
                        QVariant up_value = model()->data(up_index,Qt::DisplayRole);
                        qDebug()<<"列名:"<< model()->headerData(currentIndex().column(),Qt::Horizontal, Qt::DisplayRole).toString()<<"id:"<<id_value<<"更新数值:"<<up_value;
                        QString ColumnName=model()->headerData(currentIndex().column(),Qt::Horizontal, Qt::DisplayRole).toString();
                        QSqlQuery u_query(db_conn);
                        u_query.prepare(QString("UPDATE " + db_tablename + " SET %1 = :value WHERE id = :id").arg(ColumnName));
                        u_query.bindValue(":value", up_value);
                        u_query.bindValue(":id", id_value);
                        //u_query.exec();
//                        if (u_query.exec()) {
//                            qDebug() << "保存数据成功!";
//                        }else {
//                            qDebug()<<"保存数据失败！"<<u_query.lastError().text();
//                            return ;
//                        }
//                        if (this->model()) {
//                            commitData(this); // 提交编辑
//                            closePersistentEditor(currentIndex()); // 关闭编辑器
//                        }
                        //u_query.prepare(QString("select * from " + db_tablename));
                        //u_query.exec();
                        QModelIndex next = model()->index(nextRow, nextColumn);
                        if (next.isValid()) {
                            setCurrentIndex(next);
                            edit(next);
                            return;
                        }
                    }
                }
            //}
        }
        QTableView::keyPressEvent(event);
    }
};
#endif // CUSTOMTABLEVIEW_H
