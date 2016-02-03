/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "dabstractcomboboxdelegate.h"

DAbstractComboBoxDelegate::DAbstractComboBoxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void DAbstractComboBoxDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    //TODO, need to find anther way to get current index
    DUI::DComboBox *cb = static_cast<DUI::DComboBox *>(this->parent());
    if (cb){
        QModelIndex currentIndex = index.model()->index(cb->currentIndex(),0,QModelIndex());
        if (index == currentIndex){
            QPixmap pixmap((cb->hoverIndex()  != currentIndex) ? cb->normalTickImg() : cb->hoverTickImg());
            QRect rect = option.rect;
            rect.setX(DUI::TEXT_LEFT_MARGIN);
            rect.setY(rect.y() + (rect.height() - pixmap.height()) / 2);//draw in vertical center
            rect.setSize(pixmap.size());
            painter->drawPixmap(rect, pixmap);
        }
    }
}

void DAbstractComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    editor->setGeometry(option.rect);
}
