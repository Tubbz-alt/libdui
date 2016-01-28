#include <QDebug>
#include <QScrollBar>
#include <QApplication>
#include <QWheelEvent>

#include "dthememanager.h"
#include "dscrollbar.h"
#include "dflowlistview.h"
#include "private/dflowlistview_p.h"
#include "dflowlayout.h"

DUI_BEGIN_NAMESPACE

class DFlowListItemCreator
{
public:
    explicit DFlowListItemCreator();
    ~DFlowListItemCreator();

    QWidget *creatWidget(const QStyleOptionViewItem &option, const QModelIndex &index);
    void destroyWidget(QWidget *widget);
    void setWidgetData(QWidget *widget, const QModelIndex &index);
    void clear();

protected:
    QList<QWidget*> widgetList;
    QList<QWidget*> bufferList;

    DFlowListView *view;

private:
    friend class DFlowListView;
    friend class DFlowListViewPrivate;
};

DVariantListModel::DVariantListModel(QObject *parent) :
    QAbstractListModel(parent)
{

}

int DVariantListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return dataList.count();
}

QVariant DVariantListModel::data(const QModelIndex &index, int role) const
{
    Q_UNUSED(role);

    return dataList.value(index.row());
}

bool DVariantListModel::setData(const QModelIndex &index,
                                 const QVariant &value, int role)
{
    if (index.row() >= 0 && index.row() < dataList.size()) {
        dataList.replace(index.row(), value);
        Q_EMIT dataChanged(index, index, QVector<int>() << role);

        return true;
    }

    return false;
}

bool DVariantListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (count < 1 || row < 0 || row > rowCount(parent))
        return false;

    beginInsertRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        dataList.insert(row, QVariant());

    endInsertRows();

    return true;
}

bool DVariantListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (count <= 0 || row < 0 || (row + count) > rowCount(parent))
        return false;

    beginRemoveRows(QModelIndex(), row, row + count - 1);

    for (int r = 0; r < count; ++r)
        dataList.removeAt(row);

    endRemoveRows();

    return true;
}

DFlowListItemCreator::DFlowListItemCreator()
{

}

DFlowListItemCreator::~DFlowListItemCreator()
{
    clear();
}

QWidget *DFlowListItemCreator::creatWidget(const QStyleOptionViewItem &option,
                                               const QModelIndex &index)
{
    QWidget *widget = 0;

    if(bufferList.isEmpty()) {
        widget = view->itemDelegate()->createEditor(view->viewport(), option, index);

        if(!widget)
            return 0;
    } else {
        widget = bufferList.takeFirst();
        setWidgetData(widget, index);
    }

    widgetList << widget;

    return widget;
}

void DFlowListItemCreator::destroyWidget(QWidget *widget)
{
    if(!widget)
        return;

    widgetList.removeOne(widget);

    widget->hide();
    widget->setParent(0);

    bufferList << widget;
}

void DFlowListItemCreator::setWidgetData(QWidget *widget, const QModelIndex &index)
{
    view->itemDelegate()->setEditorData(widget, index);
}

void DFlowListItemCreator::clear()
{
    widgetList << bufferList;

    while(!widgetList.isEmpty()) {
        QWidget *widget = widgetList.takeAt(0);

        widget->deleteLater();
    }

    bufferList.clear();
}

DFlowListItemDelegate::DFlowListItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

DFlowListViewPrivate::DFlowListViewPrivate(DFlowListView *qq) :
    DListViewPrivate(qq)
{

}

DFlowListViewPrivate::~DFlowListViewPrivate()
{
    if(creator)
        delete creator;
}

void DFlowListViewPrivate::init()
{
    D_Q(DFlowListView);

    creator = new DFlowListItemCreator;
    creator->view = q;

    q->setFlow(QListView::LeftToRight);
    q->setWrapping(true);
    q->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    q->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    q->connect(q->verticalScrollBar(), SIGNAL(valueChanged(int)),
               q, SLOT(_q_updateIndexWidget()));
    q->connect(q->horizontalScrollBar(), SIGNAL(valueChanged(int)),
               q, SLOT(_q_updateIndexWidget()));
}

void DFlowListViewPrivate::onRowsInserted(const QModelIndex &parent,
                                             int first, int last)
{
    Q_UNUSED(parent);
    Q_ASSERT(creator);
    D_Q(DFlowListView);

    for(int i = first; i <= last; ++i) {
        const QModelIndex &index = q->model()->index(i, 0, parent);

        QWidget *widget = q->indexWidget(index);

        if(widget) {
            creator->setWidgetData(widget, index);
        }
    }
}

void DFlowListViewPrivate::onRowsAboutToBeRemoved(const QModelIndex &parent,
                                            int first, int last)
{
    Q_UNUSED(parent);
    Q_ASSERT(creator);
    D_Q(DFlowListView);

    int rowCount = q->model()->rowCount(parent);

    for(int i = rowCount + last - first - 1; i < rowCount; ++i) {
        creator->destroyWidget(q->getWidget(i));
    }
}

void DFlowListViewPrivate::onDataChanged(const QModelIndex &topLeft,
                                            const QModelIndex &bottomRight,
                                            const QVector<int> &roles)
{
    Q_UNUSED(roles);
    Q_ASSERT(creator);
    D_Q(DFlowListView);

    for(int i = topLeft.row(); i <= bottomRight.row(); ++i) {
        const QModelIndex &index = q->model()->index(i, 0, q->rootIndex());

        creator->setWidgetData(q->indexWidget(index), index);
    }
}

void DFlowListViewPrivate::_q_updateIndexWidget()
{
    D_Q(DFlowListView);

    QScrollBar *vbar = q->verticalScrollBar();
    QScrollBar *hbar = q->horizontalScrollBar();

    if((vbar->maximum() <= vbar->minimum())
            && (hbar->maximum() <= hbar->minimum()))
        return;

    QRect rect = q->viewport()->geometry();

    if(q->verticalScrollMode() == QAbstractItemView::ScrollPerPixel)
        rect.moveTop(vbar->value() + rect.top());

    if(q->horizontalScrollMode() == QAbstractItemView::ScrollPerPixel)
        rect.moveLeft(hbar->value() + rect.left());

    const QList<int> indexList = indexToWidgetMap.keys();

    for(int i : indexList) {
        const QModelIndex &index = q->model()->index(i, 0, q->rootIndex());
        const QRect &rect = q->visualRect(index);
        QWidget *widget = q->indexWidget(index);

        if(q->isActiveRect(rect)) {
            widget->setVisible(q->isVisualRect(rect));
        } else {
            creator->destroyWidget(widget);
            q->setIndexWidget(index, 0);
        }
    }
}

void DFlowListViewPrivate::_q_onItemPaint(const QStyleOptionViewItem &option,
                                          const QModelIndex &index)
{
    D_Q(DFlowListView);

    if(q->isActiveRect(option.rect)) {
        QWidget *widget = q->indexWidget(index);

        if(!widget) {
            widget = creator->creatWidget(option, index);
            q->setIndexWidget(index, widget);
        }

        if(q->isVisualRect(option.rect) && widget) {
            QRect rect = widget->rect();

            rect.moveCenter(option.rect.center());
            widget->move(rect.topLeft());
            creator->setWidgetData(widget, index);
        }
    }
}

DFlowListView::DFlowListView(QWidget *parent) :
    DListView(*new DFlowListViewPrivate(this), parent)
{
    d_func()->init();
}

void DFlowListView::setRootIndex(const QModelIndex &index)
{
    D_D(DFlowListView);

    if(!index.isValid())
        return;

    int count = model()->rowCount(index);
    const QList<int> &indexList = d->indexToWidgetMap.keys();

    for(int i : indexList) {
        if(i > count)
            d->creator->destroyWidget(d->indexToWidgetMap.take(i));
    }

    DListView::setRootIndex(index);
}

DFlowListItemDelegate *DFlowListView::itemDelegate() const
{
    return qobject_cast<DFlowListItemDelegate*>(DListView::itemDelegate());
}

void DFlowListView::setItemDelegate(DFlowListItemDelegate *delegate)
{
    DFlowListItemDelegate *old_delegate = itemDelegate();

    disconnect(old_delegate, SIGNAL(itemPaint(QStyleOptionViewItem,QModelIndex)),
               this, SLOT(_q_onItemPaint(QStyleOptionViewItem,QModelIndex)));

    DListView::setItemDelegate(delegate);

    connect(delegate, SIGNAL(itemPaint(QStyleOptionViewItem,QModelIndex)),
            this, SLOT(_q_onItemPaint(QStyleOptionViewItem,QModelIndex)));
}

QWidget *DFlowListView::getWidget(int index) const
{
    D_DC(DFlowListView);

    return d->indexToWidgetMap.value(index);
}

QVariant DFlowListView::getItemData(int index) const
{
    return model()->data(model()->index(index, 0, rootIndex()));
}

QModelIndex DFlowListView::getIndexByWidget(const QWidget *widget) const
{
    D_DC(DFlowListView);

    int index = d->indexToWidgetMap.key(const_cast<QWidget*>(widget), -1);

    return model()->index(index, 0, rootIndex());
}

bool DFlowListView::isActiveRect(const QRect &rect) const
{
    D_DC(DFlowListView);

    QRect area = viewport()->geometry();
    const int &cacheBuffer = d->cacheBuffer;

    area.adjust(-cacheBuffer, -cacheBuffer, cacheBuffer, cacheBuffer);

    return area.intersects(rect);
}

bool DFlowListView::isVisualRect(const QRect &rect) const
{
    D_DC(DFlowListView);

    QRect area = viewport()->geometry();

    return area.intersects(rect);
}

int DFlowListView::cacheBuffer() const
{
    return d_func()->cacheBuffer;
}

int DFlowListView::count() const
{
    return model()->rowCount();
}

void DFlowListView::setIndexWidget(const QModelIndex &index, QWidget *widget)
{
    D_D(DFlowListView);

    int row = index.row();

    if(widget) {
        widget->setParent(viewport());
        widget->show();
        d->indexToWidgetMap[row] = widget;
    } else {
        d->indexToWidgetMap.remove(row);
    }
}

bool DFlowListView::addItem(const QVariant &data)
{
    return insertItem(count(), data);
}

bool DFlowListView::addItems(const QVariantList &datas)
{
    return insertItems(count(), datas);
}

bool DFlowListView::insertItem(int index, const QVariant &data)
{
    if(!model()->insertRow(index))
        return false;

    return model()->setData(model()->index(index, 0, rootIndex()), data);
}

bool DFlowListView::insertItems(int index, const QVariantList &datas)
{
    if(!model()->insertRows(index, datas.count()))
        return false;

    for(int i = 0; i < datas.count(); ++i)
        model()->setData(model()->index(index + i, 0, rootIndex()), datas.at(i));

    return true;
}

bool DFlowListView::removeItem(int index)
{
    return model()->removeRow(index);
}

bool DFlowListView::removeItems(int index, int count)
{
    return model()->removeRows(index, count);
}

void DFlowListView::clear()
{
    D_D(DFlowListView);

    if(d->creator)
        d->creator->clear();
}

void DFlowListView::setCacheBuffer(int cacheBuffer)
{
    D_D(DFlowListView);

    if (d->cacheBuffer == cacheBuffer)
        return;

    d->cacheBuffer = cacheBuffer;
    emit cacheBufferChanged(cacheBuffer);
}

void DFlowListView::resizeEvent(QResizeEvent *size)
{
    QListView::resizeEvent(size);

    d_func()->_q_updateIndexWidget();
}

void DFlowListView::dataChanged(const QModelIndex &topLeft,
                                const QModelIndex &bottomRight,
                                const QVector<int> &roles)
{
    DListView::dataChanged(topLeft, bottomRight, roles);
    d_func()->onDataChanged(topLeft, bottomRight, roles);
}

void DFlowListView::rowsInserted(const QModelIndex &parent, int start, int end)
{
    DListView::rowsInserted(parent, start, end);
    d_func()->onRowsInserted(parent, start, end);
}

void DFlowListView::rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end)
{
    DListView::rowsAboutToBeRemoved(parent, start, end);
    d_func()->onRowsAboutToBeRemoved(parent, start, end);
}

#include "moc_dflowlistview.cpp"

DUI_END_NAMESPACE