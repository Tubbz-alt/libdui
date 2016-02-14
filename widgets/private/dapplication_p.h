/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#ifndef DAPPLICATION_P_H
#define DAPPLICATION_P_H

#include "dobject_p.h"
#include "dapplication.h"

#include <QLocalServer>

DUI_BEGIN_NAMESPACE

class DApplicationPrivate : public DObjectPrivate
{
    D_DECLARE_PUBLIC(DApplication)

public:
    DApplicationPrivate(DApplication *q);
    ~DApplicationPrivate();

    QString theme() const;
    void setTheme(const QString & theme);

    bool setSingleInstance(const QString &key);

public:
//    int m_pidLockFD = 0;
    QLocalServer *m_socketLock = nullptr;
};

DUI_END_NAMESPACE

#endif // DAPPLICATION_P_H
