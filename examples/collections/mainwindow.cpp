/**
 * Copyright (C) 2015 Deepin Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 **/

#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>

#include "dslider.h"
#include "dthememanager.h"
#include "libdui_global.h"
#include "dswitchbutton.h"
#include "segmentedcontrol.h"
#include "dcolorpicker.h"

#include "mainwindow.h"
#include "buttonlisttab.h"
#include "buttongridtab.h"
#include "imagebuttongridtab.h"
#include "cameraform.h"
#include "graphicseffecttab.h"
#include "flowwidgetlisttab.h"

DUI_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    DThemeManager * themeManager = DThemeManager::instance();

    initTabWidget();

    QVBoxLayout * mainLayout = new QVBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_mainTab);

    QHBoxLayout * styleLayout = new QHBoxLayout();
    QPushButton *darkButton = new QPushButton("Dark",this);
    QPushButton *lightBUtton = new QPushButton("Light",this);
    connect(darkButton, &QPushButton::clicked, [=]{
        themeManager->setTheme("dark");
    });
    connect(lightBUtton, &QPushButton::clicked, [=]{
        themeManager->setTheme("light");
    });
    styleLayout->addWidget(darkButton);
    styleLayout->addWidget(lightBUtton);
    styleLayout->addStretch();

    mainLayout->addLayout(styleLayout);

    this->setLayout(mainLayout);
}

void MainWindow::initTabWidget()
{
    m_mainTab = new QTabWidget(this);

    ComboBoxTab * comboBoxTab = new ComboBoxTab(this);

    LineTab * lineTab = new LineTab(this);

    BarTab * barTab = new BarTab(this);

    ButtonTab * buttonTab = new ButtonTab(this);

    InputTab * inputTab = new InputTab(this);

    SliderTab * sliderTab = new SliderTab(this);

    IndicatorTab * indicatorTab = new IndicatorTab(this);

    ButtonListTab* buttonListGroupTab = new ButtonListTab(this);

    ButtonGridTab* buttonGridTab = new ButtonGridTab(this);

    ImageButtonGridTab* imageButtonGridTab = new ImageButtonGridTab(this);

    Segmentedcontrol *segmentedControl = new Segmentedcontrol(this);

    WidgetsTab *widgetsTab = new WidgetsTab(this);

    DColorPicker *picker = new DColorPicker(1, this);

    CameraForm *cameraform = new CameraForm(this);

    GraphicsEffectTab *effectTab = new GraphicsEffectTab;

    m_mainTab->addTab(effectTab, "GraphicsEffect");
    m_mainTab->addTab(comboBoxTab, "ComboBox");
    m_mainTab->addTab(indicatorTab, "Indicator");
    m_mainTab->addTab(lineTab,"Line");
    m_mainTab->addTab(barTab,"Bar");
    m_mainTab->addTab(buttonTab,"Button");
    m_mainTab->addTab(inputTab,"Input");
    m_mainTab->addTab(sliderTab,"Slider");

    m_mainTab->addTab(buttonListGroupTab, "ButtonList");
    m_mainTab->addTab(imageButtonGridTab, "imageButtonGrid");
    m_mainTab->addTab(buttonGridTab, "ButtonGrid");
    m_mainTab->addTab(segmentedControl, "Segmented Control");
    m_mainTab->addTab(widgetsTab, "Widgets");
    m_mainTab->addTab(picker, "Color Picker");
    m_mainTab->addTab(cameraform, "Camera View");
    m_mainTab->addTab(new FlowWidgetListTab, "Layout Tab");

    m_mainTab->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{

}
