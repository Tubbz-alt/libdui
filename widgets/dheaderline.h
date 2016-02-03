/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef DHEADERLINE_H
#define DHEADERLINE_H

#include <QWidget>
#include <QLabel>

#include "libdui_global.h"
#include "dbaseline.h"

DUI_BEGIN_NAMESPACE

class LIBDUISHARED_EXPORT DHeaderLine : public DBaseLine
{
    Q_OBJECT
public:
    explicit DHeaderLine(QWidget *parent = 0);
    void setTitle(const QString &title);
    void setContent(QWidget *content);

private:
    void setLeftContent(QWidget *content);
    void setRightContent(QWidget *content);

private:
    QLabel *m_titleLabel = NULL;
};

DUI_END_NAMESPACE

#endif // DHEADERLINE_H
