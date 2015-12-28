#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QScreen>
#include <QPainter>
#include <QWidget>
#include <QDebug>

#include "dialog_constants.h"
#include "dabstractdialog.h"
#include "private/dabstractdialogprivate_p.h"

DUI_BEGIN_NAMESPACE

DAbstractDialogPrivate::DAbstractDialogPrivate(DAbstractDialog *qq):
    DObjectPrivate(qq)
{

}

void DAbstractDialogPrivate::init()
{
    D_Q(DAbstractDialog);

    q->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    q->setAttribute(Qt::WA_TranslucentBackground);
    q->resize(DIALOG::DEFAULT_WIDTH, DIALOG::DEFAULT_HEIGHT);
    q->setMaximumWidth(getParentGeometry().width() / 1.5);
}

QRect DAbstractDialogPrivate::getParentGeometry() const
{
    D_QC(DAbstractDialog);

    if (q->parentWidget()) {
        return q->parentWidget()->window()->geometry();
    } else {
        QPoint pos = QCursor::pos();

        for (QScreen *screen : qApp->screens()) {
            if (screen->geometry().contains(pos)) {
                return screen->geometry();
            }
        }
    }

    return qApp->primaryScreen()->geometry();
}

DAbstractDialog::DAbstractDialog(QWidget *parent) :
    QDialog(parent),
    DObject(*new DAbstractDialogPrivate(this))
{
    d_func()->init();
}

QColor DAbstractDialog::backgroundColor() const
{
    D_DC(DAbstractDialog);

    return d->backgroundColor;
}

QColor DAbstractDialog::borderColor() const
{
    D_DC(DAbstractDialog);

    return d->borderColor;
}

DAbstractDialog::DisplayPostion DAbstractDialog::displayPostion() const
{
    D_DC(DAbstractDialog);

    return d->displayPostion;
}

void DAbstractDialog::moveToCenter()
{
    D_DC(DAbstractDialog);

    moveToCenterByRect(d->getParentGeometry());
}

void DAbstractDialog::moveToTopRight()
{
    D_DC(DAbstractDialog);

    moveToTopRightByRect(d->getParentGeometry());
}

void DAbstractDialog::moveToTopRightByRect(const QRect &rect)
{
    int x = rect.x() + rect.width() - width();
    move(QPoint(x, 0));
}

void DAbstractDialog::setBackgroundColor(QColor backgroundColor)
{
    D_D(DAbstractDialog);

    d->backgroundColor = backgroundColor;

    update();
}

void DAbstractDialog::setBorderColor(QColor borderColor)
{
    D_D(DAbstractDialog);

    d->borderColor = borderColor;

    update();
}

void DAbstractDialog::setDisplayPostion(DAbstractDialog::DisplayPostion displayPostion)
{
    D_D(DAbstractDialog);

    d->displayPostion = displayPostion;

    switch (displayPostion) {
    case DisplayCenter:
        moveToCenter();
        break;
    case DisplayTopRight:
        moveToTopRight();
        break;
    default:
        break;
    }
}

void DAbstractDialog::moveToCenterByRect(const QRect &rect)
{
    QRect qr = frameGeometry();
    qr.moveCenter(rect.center());
    move(qr.topLeft());
}

void DAbstractDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        D_D(DAbstractDialog);

        d->dragPosition = event->globalPos() - frameGeometry().topLeft();
        d->mousePressed = true;
    }

    QDialog::mousePressEvent(event);
}

void DAbstractDialog::mouseReleaseEvent(QMouseEvent *event)
{
    D_D(DAbstractDialog);

    d->mousePressed = false;

    QDialog::mouseReleaseEvent(event);
}

void DAbstractDialog::mouseMoveEvent(QMouseEvent *event)
{
    D_D(DAbstractDialog);

    if(d->mousePressed) {
        move(event->globalPos() - d->dragPosition);
        d->mouseMoved = true;
    }

    QDialog::mouseMoveEvent(event);
}

void DAbstractDialog::paintEvent(QPaintEvent *event)
{
    D_DC(DAbstractDialog);

    QPainter painter(this);

    painter.setPen(QPen(d->borderColor, DIALOG::BORDER_SHADOW_WIDTH));
    painter.setBrush(d->backgroundColor);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QRectF r(DIALOG::BORDER_SHADOW_WIDTH / 2.0, DIALOG::BORDER_SHADOW_WIDTH / 2.0,
            width() - DIALOG::BORDER_SHADOW_WIDTH, height() - DIALOG::BORDER_SHADOW_WIDTH);
    painter.drawRoundedRect(r, DIALOG::BORDER_SHADOW_WIDTH, DIALOG::BORDER_SHADOW_WIDTH);

    QDialog::paintEvent(event);
}

void DAbstractDialog::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);

    D_DC(DAbstractDialog);

    if(!d->mouseMoved)
        setDisplayPostion(displayPostion());

    emit sizeChanged(event->size());
}

DAbstractDialog::DAbstractDialog(DAbstractDialogPrivate &dd, QWidget *parent):
    QDialog(parent),
    DObject(dd)
{
    dd.init();
}

DUI_END_NAMESPACE
