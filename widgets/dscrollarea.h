/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef DSCROLLAREA_H
#define DSCROLLAREA_H

#include <QScrollArea>

#include "libdui_global.h"
#include "dobject.h"

DUI_BEGIN_NAMESPACE

class DScrollBar;
class DScrollAreaPrivate;
class LIBDUISHARED_EXPORT DScrollArea : public QScrollArea, public DObject
{
    Q_OBJECT

    Q_PROPERTY(bool autoHideScrollBar READ autoHideScrollBar WRITE setAutoHideScrollBar NOTIFY autoHideScrollBarChanged)

public:
    explicit DScrollArea(QWidget *parent = 0);

    bool autoHideScrollBar() const;

public slots:
    void setAutoHideScrollBar(bool autoHideScrollBar);

signals:
    void autoHideScrollBarChanged(bool autoHideScrollBar);

private slots:
    void hideScrollBar(QScrollBar *bar);
    void showScrollBar(QScrollBar *bar);

protected:
    DScrollArea(DScrollAreaPrivate &dd, QWidget *parent = 0);

private:
    D_DECLARE_PRIVATE(DScrollArea)
};

DUI_END_NAMESPACE

#endif // DSCROLLAREA_H
