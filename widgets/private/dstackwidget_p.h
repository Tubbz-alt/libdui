/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef DSTACKWIDGET_P_H
#define DSTACKWIDGET_P_H

#include "libdui_global.h"
#include "dobject_p.h"
#include "dstackwidget.h"

class QStackedLayout;

DUI_BEGIN_NAMESPACE

class DAbstractStackWidgetTransitionPrivate : public DObjectPrivate
{
    DAbstractStackWidgetTransitionPrivate(DAbstractStackWidgetTransition *qq);
    ~DAbstractStackWidgetTransitionPrivate();

    QVariantAnimation *animation;
    DAbstractStackWidgetTransition::TransitionInfo info;

    void init();

    D_DECLARE_PUBLIC(DAbstractStackWidgetTransition)
};

class DStackWidgetPrivate : public DObjectPrivate
{
    DStackWidgetPrivate(DStackWidget *qq);
    ~DStackWidgetPrivate();

    int currentIndex;
    QWidget *currentWidget;
    QList<QWidget*> widgetList;
    QList<QWidget*> trashWidgetList;
    DAbstractStackWidgetTransition* transition;

    void init();
    void setCurrentIndex(int index);

    D_DECLARE_PUBLIC(DStackWidget)
};

DUI_END_NAMESPACE

#endif // DSTACKWIDGET_P

