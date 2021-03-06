/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include "bartab.h"

#include "dcircleprogress.h"
#include "dslider.h"

BarTab::BarTab(QWidget *parent) : QFrame(parent)
{
    setStyleSheet("background-color:gray;");

    DUI::DCircleProgress *circleProgess = new DUI::DCircleProgress(this);
    circleProgess->setFixedSize(100, 100);
    circleProgess->move(50, 50);

    DUI::DSlider * slider = new DUI::DSlider(Qt::Horizontal, this);
    slider->setMinimum(0);
    slider->setMaximum(100);
    slider->setFixedWidth(100);
    slider->setFixedHeight(20);
    slider->move(50, 150);

    connect(slider, &DUI::DSlider::valueChanged, circleProgess, &DUI::DCircleProgress::setValue);
    connect(slider, &DUI::DSlider::valueChanged, [circleProgess] (const int value) {
        circleProgess->setText(QString::number(value) + "%");
    });
}

