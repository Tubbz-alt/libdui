#ifndef DOPTIONLIST_P_H
#define DOPTIONLIST_P_H

#include "dobject_p.h"
#include "doptionlist.h"
#include "doption.h"

#include <QList>
#include <QListWidgetItem>

DUI_BEGIN_NAMESPACE

class DOptionListPrivate : public DObjectPrivate
{
    D_DECLARE_PUBLIC(DOptionList)

public:
    DOptionListPrivate(DOptionList *q);

    void init();
    void addOption(DOption *option);
    void insertOption(int pos, DOption *option);
    void setCurrentSelected(int pos);
    void setCurrentSelected(const QString &value);

public slots:
    void _q_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

protected:
    QMap<QListWidgetItem *, DOption *> m_optionList;
};

DUI_END_NAMESPACE

#endif // DOPTIONLIST_P_H
