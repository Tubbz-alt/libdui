/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef DSCROLLBAR_H
#define DSCROLLBAR_H

#include <QScrollBar>

#include "libdui_global.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit DScrollBar(QWidget *parent = 0);

signals:

public slots:
};

DUI_END_NAMESPACE

#endif // DSCROLLBAR_H
