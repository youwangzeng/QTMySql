#ifndef EDITQUERYMODEL_H
#define EDITQUERYMODEL_H

#include "form_main.h"
#include <QSqlQueryModel>


class editQueryModel : public QSqlQueryModel
{
public:
    editQueryModel();
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    //自定义接口函数
    //更新数据
    void refresh(const QString &sqlstr);
    //根据需求来定义修改表中的内容的接口
    bool setName(int ,QString useId, const QString &name);
};

#endif // EDITQUERYMODEL_H
