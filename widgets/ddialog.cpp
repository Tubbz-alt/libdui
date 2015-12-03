#include <QPushButton>
#include <QLabel>
#include <QButtonGroup>
#include <QDebug>
#include <QCloseEvent>
#include <QApplication>
#include <QSpacerItem>
#include <QDesktopWidget>
#include <QScreen>

#include "private/ddialog_p.h"

#include "dialog_constants.h"
#include "ddialog.h"
#include "dthememanager.h"
#include "dboxwidget.h"

DUI_BEGIN_NAMESPACE

DDialogPrivate::DDialogPrivate(DDialog *qq) :
    DAbstractDialogPrivate(qq)
{

}

void DDialogPrivate::init()
{
    D_Q(DDialog);

    boxWidget = new DVBoxWidget;
    buttonLayout = new QHBoxLayout;

    buttonLayout->setMargin(0);
    buttonLayout->setSpacing(0);
    buttonLayout->setContentsMargins(DIALOG::BUTTON_LAYOUT_LEFT_MARGIN,
                                     DIALOG::BUTTON_LAYOUT_TOP_MARGIN,
                                     DIALOG::BUTTON_LAYOUT_RIGHT_MARGIN,
                                     DIALOG::BUTTON_LAYOUT_BOTTOM_MARGIN);

    closeButton = new QPushButton(q);

    closeButton->setObjectName("CloseButton");
    closeButton->setFixedSize(DIALOG::CLOSE_BUTTON_WIDTH, DIALOG::CLOSE_BUTTON_WIDTH);
    closeButton->setAttribute(Qt::WA_NoMousePropagation);

    iconLabel = new QLabel;
    iconLabel->hide();

    messageLabel = new QLabel;
    messageLabel->setObjectName("MessageLabel");
    messageLabel->hide();

    titleLabel = new QLabel;
    titleLabel->setObjectName("TitleLabel");
    titleLabel->hide();

    QVBoxLayout *layout_message = new QVBoxLayout;

    layout_message->setMargin(0);
    layout_message->setSpacing(0);
    layout_message->addWidget(titleLabel);
    layout_message->addWidget(messageLabel);
    layout_message->addStretch();

    iconLayout = new QHBoxLayout;

    iconLayout->setContentsMargins(DIALOG::ICON_LAYOUT_LEFT_MARGIN,
                                   DIALOG::ICON_LAYOUT_TOP_MARGIN,
                                   DIALOG::ICON_LAYOUT_RIGHT_MARGIN,
                                   DIALOG::ICON_LAYOUT_BOTTOM_MARGIN);
    iconLayout->addWidget(iconLabel);
    iconLayout->addLayout(layout_message);
    iconLayout->addStretch();

    spacerWidget = new QWidget;
    spacerWidget->setFixedHeight(0);

    boxWidget->layout()->addWidget(closeButton, 0, Qt::AlignRight);
    boxWidget->layout()->addLayout(iconLayout);
    boxWidget->layout()->addWidget(spacerWidget);
    boxWidget->layout()->addLayout(buttonLayout);

    QObject::connect(closeButton, SIGNAL(clicked()), q, SLOT(close()));
    QObject::connect(boxWidget, SIGNAL(sizeChanged(QSize)), q, SLOT(_q_updateSize()));

    boxWidget->setParent(q);
}

const QScreen *DDialogPrivate::getScreen() const
{
    D_QC(DDialog);

    const QScreen *screen = qApp->screens()[qApp->desktop()->screenNumber(q)];

    if(screen)
        return screen;

    screen = qApp->screens()[qApp->desktop()->screenNumber(QCursor::pos())];

    return screen;
}

void DDialogPrivate::_q_onButtonClicked()
{
    D_Q(DDialog);

    QAbstractButton *button = qobject_cast<QAbstractButton*>(q->sender());

    if(button) {
        clickedButtonIndex = buttonList.indexOf(button);
        q->buttonClicked(clickedButtonIndex, button->text());

        if(onButtonClickedClose)
            q->done(clickedButtonIndex);
    }
}

void DDialogPrivate::_q_updateSize()
{
    D_Q(DDialog);

    int boxWidget_height = boxWidget->sizeHint().height()- spacerWidget->height();

    if(boxWidget_height < DIALOG::DEFAULT_HEIGHT) {
        if(boxWidget->sizeHint().height() < DIALOG::DEFAULT_HEIGHT) {
            spacerWidget->setFixedHeight(DIALOG::DEFAULT_HEIGHT - boxWidget_height);
            spacerWidget->show();
        }
    } else {
        spacerWidget->setFixedHeight(0);
        spacerWidget->hide();
    }

    q->resize(boxWidget->sizeHint());
}

void DDialogPrivate::_q_updateLabelMaxWidth()
{
    if(!targetScreen)
        return;

    D_Q(DDialog);

    int labelMaxWidth = targetScreen->geometry().width() / 2;
    QFontMetrics fm = titleLabel->fontMetrics();

    if (fm.width(title) > labelMaxWidth){
        int label_old_width = titleLabel->sizeHint().width();
        QString text = fm.elidedText(title, Qt::ElideRight, labelMaxWidth);

        titleLabel->setText(text);
        boxWidget->setFixedWidth(boxWidget->width() - label_old_width + titleLabel->sizeHint().width());
    }

    fm = messageLabel->fontMetrics();

    if (fm.width(message) > labelMaxWidth){
        int label_old_width = messageLabel->sizeHint().width();
        QString text = fm.elidedText(message, Qt::ElideRight, labelMaxWidth);

        messageLabel->setText(text);
        boxWidget->setFixedWidth(boxWidget->width() - label_old_width + messageLabel->sizeHint().width());
    }
}

DDialog::DDialog(QWidget *parent) :
    DAbstractDialog(*new DDialogPrivate(this), parent)
{
    D_THEME_INIT_WIDGET(dialogs/DDialog);

    d_func()->init();
}

DDialog::DDialog(const QString &title, const QString &message, QWidget *parent) :
    DAbstractDialog(*new DDialogPrivate(this), parent)
{
    D_THEME_INIT_WIDGET(dialogs/DDialog);

    d_func()->init();

    setTitle(title);
    setMessage(message);
}

int DDialog::getButtonIndexByText(const QString &text) const
{
    D_DC(DDialog);

    int i = -1;

    for(const QAbstractButton *button : getButtons()) {
        ++i;

        if(button->text() == text)
            return i;
    }

    return i;
}

int DDialog::buttonCount() const
{
    D_DC(DDialog);

    return d->buttonList.count();
}

int DDialog::contentCount() const
{
    D_DC(DDialog);

    return d->contentList.count();
}

QList<QAbstractButton*> DDialog::getButtons() const
{
    D_DC(DDialog);

    return d->buttonList;
}

QList<QWidget *> DDialog::getContents() const
{
    D_DC(DDialog);

    return d->contentList;
}

QAbstractButton *DDialog::getButton(int index) const
{
    D_DC(DDialog);

    return d->buttonList.at(index);
}

QWidget *DDialog::getContent(int index) const
{
    D_DC(DDialog);

    return d->contentList.at(index);
}

QString DDialog::title() const
{
    D_DC(DDialog);

    return d->title;
}

QString DDialog::message() const
{
    D_DC(DDialog);

    return d->message;
}

QIcon DDialog::icon() const
{
    D_DC(DDialog);

    return d->icon;
}

QPixmap DDialog::iconPixmap() const
{
    D_DC(DDialog);

    return *d->iconLabel->pixmap();
}

Qt::TextFormat DDialog::textFormat() const
{
    D_DC(DDialog);

    return d->textFormat;
}

bool DDialog::onButtonClickedClose() const
{
    D_DC(DDialog);

    return d->onButtonClickedClose;
}

void DDialog::setFixedWidth(int width)
{
    D_D(DDialog);

    d->boxWidget->setFixedWidth(width);
}

void DDialog::setFixedHeight(int height)
{
    D_D(DDialog);

    d->boxWidget->setFixedHeight(height);
}

void DDialog::setFixedSize(const QSize &size)
{
    D_D(DDialog);

    d->boxWidget->setFixedSize(size);
}

int DDialog::addButton(const QString &text)
{
    int index = buttonCount();

    insertButton(index, text);

    return index;
}

int DDialog::addButtons(const QStringList &text)
{
    int index = buttonCount();

    insertButtons(index, text);

    return index;
}

void DDialog::insertButton(int index, const QString &text)
{
    QPushButton *button = new QPushButton(text);

    button->setObjectName("ActionButton");
    button->setAttribute(Qt::WA_NoMousePropagation);
    button->setFixedHeight(DIALOG::BUTTON_HEIGHT);

    insertButton(index, button);
}

void DDialog::insertButton(int index, QAbstractButton *button)
{
    D_D(DDialog);

    QLabel* label = new QLabel;
    label->setObjectName("VLine");
    label->setFixedWidth(1);
    label->hide();

    if(index > 0 && index >= buttonCount()) {
        QLabel *label = qobject_cast<QLabel*>(d->buttonLayout->itemAt(d->buttonLayout->count() - 1)->widget());
        if(label)
            label->show();
    }

    d->buttonLayout->insertWidget(index * 2, button);
    d->buttonList << button;
    d->buttonLayout->insertWidget(index * 2 + 1, label);

    connect(button, SIGNAL(clicked(bool)), this, SLOT(_q_onButtonClicked()));
}

void DDialog::insertButtons(int index, const QStringList &text)
{
    for(int i = 0; i < text.count(); ++i) {
        insertButton(index + i, text[i]);
    }
}

void DDialog::removeButton(int index)
{
    D_D(DDialog);

    QLabel *label = qobject_cast<QLabel*>(d->buttonLayout->itemAt(index * 2 + 1)->widget());
    QAbstractButton * button = qobject_cast<QAbstractButton*>(d->buttonLayout->itemAt(index * 2)->widget());

    if(label) {
        d->buttonLayout->removeWidget(label);
        label->deleteLater();
    }

    if(button) {
        d->buttonLayout->removeWidget(button);
        button->deleteLater();
    }

    if(index > 0 && index == buttonCount() - 1) {
        QLabel *label = qobject_cast<QLabel*>(d->buttonLayout->itemAt(d->buttonLayout->count() - 1)->widget());

        if(label)
            label->hide();
    }

    d->buttonList.removeAt(index);
}

void DDialog::removeButton(QAbstractButton *button)
{
    removeButton(getButtons().indexOf(button));
}

void DDialog::removeButtonByText(const QString &text)
{
    int index = getButtonIndexByText(text);

    if(index >= 0)
        removeButton(index);
}

void DDialog::clearButtons()
{
    D_D(DDialog);

    d->buttonList.clear();

    while(d->buttonLayout->count()) {
        QLayoutItem *item = d->buttonLayout->takeAt(0);

        item->widget()->deleteLater();
        delete item;
    }
}

int DDialog::addContent(QWidget *widget)
{
    D_DC(DDialog);

    int index = d->contentList.count();

    insertContent(index, widget);

    return index;
}

void DDialog::insertContent(int index, QWidget *widget)
{
    D_D(DDialog);

    d->boxWidget->layout()->insertWidget(index + DIALOG::CONTENT_INSERT_OFFSET,
                                         widget, 0, Qt::AlignHCenter);
    d->contentList << widget;
}

void DDialog::removeContent(QWidget *widget, bool isDelete)
{
    D_D(DDialog);

    d->boxWidget->layout()->removeWidget(widget);

    if(isDelete)
        widget->deleteLater();

    d->contentList.removeOne(widget);
}

void DDialog::clearContents(bool isDelete)
{
    D_D(DDialog);

    while(d->boxWidget->layout()->count() >  + DIALOG::CONTENT_INSERT_OFFSET + 1) {
        d->boxWidget->layout()->removeItem(d->boxWidget->layout()->itemAt(DIALOG::CONTENT_INSERT_OFFSET));
    }

    if(isDelete) {
        qDeleteAll(d->contentList);
    }

    d->contentList.clear();
}

void DDialog::setButtonText(int index, const QString &text)
{
    QAbstractButton *button = getButton(index);

    button->setText(text);
}

void DDialog::setButtonIcon(int index, const QIcon &icon)
{
    QAbstractButton *button = getButton(index);

    button->setIcon(icon);
}

void DDialog::setTitle(const QString &title)
{
    D_D(DDialog);

    if (d->title == title)
        return;

    d->title = title;
    d->titleLabel->setText(title);
    d->titleLabel->setHidden(title.isEmpty());
    d->_q_updateLabelMaxWidth();

    emit titleChanged(title);
}

void DDialog::setMessage(const QString &message)
{
    D_D(DDialog);

    if (d->message == message)
        return;

    d->message = message;
    d->messageLabel->setText(message);
    d->messageLabel->setHidden(message.isEmpty());
    d->_q_updateLabelMaxWidth();

    emit messageChanged(message);
}

void DDialog::setIcon(const QIcon &icon)
{
    D_D(DDialog);

    d->icon = icon;

    if(!icon.isNull())
        setIconPixmap(icon.pixmap(icon.availableSizes().first()));
}

void DDialog::setIconPixmap(const QPixmap &iconPixmap)
{
    D_D(DDialog);

    d->iconLabel->setPixmap(iconPixmap);
    if(iconPixmap.isNull()) {
        d->iconLabel->hide();
        d->iconLayout->setSpacing(0);
    } else {
        d->iconLayout->setSpacing(DIALOG::ICON_LAYOUT_SPACING);
        d->iconLabel->show();
    }
}

void DDialog::setTextFormat(Qt::TextFormat textFormat)
{
    D_D(DDialog);

    if (d->textFormat == textFormat)
        return;

    d->textFormat = textFormat;
    d->titleLabel->setTextFormat(textFormat);
    d->messageLabel->setTextFormat(textFormat);

    emit textFormatChanged(textFormat);
}

void DDialog::setOnButtonClickedClose(bool onButtonClickedClose)
{
    D_D(DDialog);

    d->onButtonClickedClose = onButtonClickedClose;
}

int DDialog::exec()
{
    D_D(DDialog);

    d->clickedButtonIndex = -1;

    int code = DAbstractDialog::exec();

    return d->clickedButtonIndex >= 0 ? d->clickedButtonIndex : code;
}

DDialog::DDialog(DDialogPrivate &dd, QWidget *parent) :
    DAbstractDialog(dd, parent)
{
    D_THEME_INIT_WIDGET(dialogs/DDialog);

    d_func()->init();
}

void DDialog::closeEvent(QCloseEvent *event)
{
    emit aboutToClose();
    done(-1);
    DAbstractDialog::closeEvent(event);
    emit closed();
}

void DDialog::showEvent(QShowEvent *event)
{
    D_D(DDialog);

    disconnect(d->targetScreen, SIGNAL(geometryChanged(QRect)), this, SLOT(_q_updateLabelMaxWidth()));
    d->targetScreen = d->getScreen();
    connect(d->targetScreen, SIGNAL(geometryChanged(QRect)), this, SLOT(_q_updateLabelMaxWidth()));

    d->_q_updateLabelMaxWidth();

    DAbstractDialog::showEvent(event);
}

DUI_END_NAMESPACE

#include "moc_ddialog.cpp"
