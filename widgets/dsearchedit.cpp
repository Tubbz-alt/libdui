#include "dsearchedit.h"
#include "dthememanager.h"

#include <QHBoxLayout>
#include <QSpacerItem>
#include <QPropertyAnimation>
#include <QDebug>
#include <QEvent>
#include <QResizeEvent>

DUI_USE_NAMESPACE

DSearchEdit::DSearchEdit(QWidget *parent)
    : QFrame(parent)
{
    D_THEME_INIT_WIDGET(DSearchEdit);

    m_searchBtn = new DImageButton;
    m_searchBtn->setObjectName("SearchIcon");
    m_clearBtn = new DImageButton;
    m_clearBtn->setObjectName("ClearIcon");
    m_clearBtn->hide();
    m_edt = new QLineEdit;
    m_edt->setObjectName("Edit");

    m_animation = new QPropertyAnimation(m_edt, "minimumWidth");

    m_size = QSize(m_searchBtn->sizeHint().width() + m_edt->sizeHint().width() + m_clearBtn->sizeHint().width() + 6,
                   qMax(m_searchBtn->sizeHint().height(), m_edt->sizeHint().height()));
    m_edt->setFixedWidth(0);
    m_edt->installEventFilter(this);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addStretch();
    layout->addWidget(m_searchBtn);
    layout->setAlignment(m_searchBtn, Qt::AlignCenter);
    layout->addWidget(m_edt);
    layout->setAlignment(m_edt, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(m_clearBtn);
    layout->setAlignment(m_clearBtn, Qt::AlignCenter);
    layout->setSpacing(0);
    layout->setContentsMargins(3, 0, 3, 0);

    setLayout(layout);
    setAutoFillBackground(true);

    connect(m_clearBtn, &DImageButton::clicked, m_edt, static_cast<void (QLineEdit::*)()>(&QLineEdit::setFocus));
    connect(m_clearBtn, &DImageButton::clicked, this, &DSearchEdit::clear);
    connect(m_edt, &QLineEdit::textChanged, [this] {m_clearBtn->setVisible(!m_edt->text().isEmpty());});
    connect(m_edt, &QLineEdit::textChanged, this, &DSearchEdit::textChanged, Qt::DirectConnection);
    connect(m_edt, &QLineEdit::editingFinished, this, &DSearchEdit::editingFinished, Qt::DirectConnection);
    connect(m_searchBtn, &DImageButton::clicked, this, &DSearchEdit::toEditMode);
}

DSearchEdit::~DSearchEdit()
{
    m_animation->deleteLater();
}

const QString DSearchEdit::text() const
{
    return std::move(m_edt->text());
}

void DSearchEdit::mousePressEvent(QMouseEvent *)
{
    toEditMode();
}

bool DSearchEdit::eventFilter(QObject *o, QEvent *e)
{
    if (o == m_edt && e->type() == QEvent::FocusOut && m_edt->text().isEmpty())
    {
        m_animation->stop();
        m_animation->setStartValue(m_edt->width());
        m_animation->setEndValue(0);
        m_animation->setEasingCurve(m_hideCurve);
        m_animation->start();
    }

    return QFrame::eventFilter(o, e);
}

void DSearchEdit::toEditMode()
{
    m_animation->stop();
    m_animation->setStartValue(0);
    m_animation->setEndValue(m_size.width() - m_searchBtn->width() - 6); // left + right margins = 6
    m_animation->setEasingCurve(m_showCurve);
    m_animation->start();

    m_edt->show();
    m_edt->setFocus();
}

void DSearchEdit::resizeEvent(QResizeEvent *e)
{
    m_size = e->size();
}
