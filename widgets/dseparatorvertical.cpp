#include "dseparatorvertical.h"
#include "dthememanager.h"

DUI_BEGIN_NAMESPACE

DSeparatorVertical::DSeparatorVertical(QWidget *parent) : QWidget(parent)
{
    D_THEME_INIT_WIDGET(DSeparatorVertical);

    this->setFixedWidth(2);

    m_leftRec = new QWidget(this);
    m_leftRec->setObjectName("DSeparatorLeftRec");
    m_rightRec = new QWidget(this);
    m_rightRec->setObjectName("DSeparatorRightRec");

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    mainLayout->addStretch();
    mainLayout->addWidget(m_leftRec);
    mainLayout->addWidget(m_rightRec);
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}

DUI_END_NAMESPACE
