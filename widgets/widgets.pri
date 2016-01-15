include(private/private.pri)
include(dialogs.pri)

HEADERS += $$PWD/dslider.h\
    $$PWD/dthememanager.h \
    $$PWD/dapplication.h \
    $$PWD/dconstants.h \
    $$PWD/dseparatorhorizontal.h \
    $$PWD/dseparatorvertical.h \
    $$PWD/dbaseline.h \
    $$PWD/dheaderline.h \
    $$PWD/dbaseexpand.h \
    $$PWD/darrowbutton.h \
    $$PWD/darrowlineexpand.h \
    $$PWD/dswitchlineexpand.h \
    $$PWD/dbuttonlist.h \
    $$PWD/dimagebutton.h \
    $$PWD/dtextbutton.h \
    $$PWD/dloadingindicator.h \
    $$PWD/dsearchedit.h \
    $$PWD/dswitchbutton.h \
    $$PWD/dsegmentedcontrol.h \
    $$PWD/dcolorpicker.h \
    $$PWD/dlineedit.h \
    $$PWD/dcombobox.h \
    $$PWD/dbuttongrid.h\
    $$PWD/dcomboboxmodel.h \
    $$PWD/dcolorcombobox.h \
    $$PWD/dfontcombobox.h \
    $$PWD/dsimplecombobox.h \
    $$PWD/dwindowmaxbutton.h \
    $$PWD/dwindowminbutton.h \
    $$PWD/dwindowclosebutton.h \
    $$PWD/dwindowrestorebutton.h \
    $$PWD/dwindowoptionbutton.h \
    $$PWD/dshortcutedit.h \
    $$PWD/dabstractcomboboxdelegate.h \
    $$PWD/dexpandgroup.h \
    $$PWD/dlabel.h \
    $$PWD/dlinkbutton.h \
    $$PWD/dcameraview.h \
    $$PWD/dscrollbar.h \
    $$PWD/dscrollarea.h \
    $$PWD/darrowrectangle.h \
    $$PWD/dcalendar.h \
    $$PWD/dgraphicsgloweffect.h \
    $$PWD/anchors.h \
    $$PWD/dbasebutton.h \
    $$PWD/dlistwidget.h \
    $$PWD/dobject.h \
    $$PWD/dboxwidget.h \
    $$PWD/dcircleprogress.h \
    $$PWD/dstackwidget.h \
    $$PWD/dcheckbox.h \
    $$PWD/dfilechooseredit.h \
    $$PWD/dpasswordedit.h \
    $$PWD/dipv4lineedit.h \
    $$PWD/dspinbox.h \
    $$PWD/doptionlist.h \
    $$PWD/doption.h \
    $$PWD/dpicturesequenceview.h

SOURCES += $$PWD/dslider.cpp \
    $$PWD/dthememanager.cpp \
    $$PWD/dapplication.cpp \
    $$PWD/dseparatorhorizontal.cpp \
    $$PWD/dseparatorvertical.cpp \
    $$PWD/dbaseline.cpp \
    $$PWD/dheaderline.cpp \
    $$PWD/dbaseexpand.cpp \
    $$PWD/darrowbutton.cpp \
    $$PWD/darrowlineexpand.cpp \
    $$PWD/dswitchlineexpand.cpp \
    $$PWD/dbuttonlist.cpp \
    $$PWD/dimagebutton.cpp \
    $$PWD/dtextbutton.cpp \
    $$PWD/dloadingindicator.cpp \
    $$PWD/dsearchedit.cpp \
    $$PWD/dswitchbutton.cpp\
    $$PWD/dsegmentedcontrol.cpp \
    $$PWD/dcolorpicker.cpp \
    $$PWD/dlineedit.cpp \
    $$PWD/dcombobox.cpp \
    $$PWD/dbuttongrid.cpp\
    $$PWD/dcomboboxmodel.cpp \
    $$PWD/dcolorcombobox.cpp \
    $$PWD/dfontcombobox.cpp \
    $$PWD/dsimplecombobox.cpp\
    $$PWD/dwindowmaxbutton.cpp \
    $$PWD/dwindowminbutton.cpp \
    $$PWD/dwindowclosebutton.cpp \
    $$PWD/dwindowrestorebutton.cpp \
    $$PWD/dwindowoptionbutton.cpp \
    $$PWD/dshortcutedit.cpp \
    $$PWD/dabstractcomboboxdelegate.cpp \
    $$PWD/dexpandgroup.cpp \
    $$PWD/dlabel.cpp \
    $$PWD/dlinkbutton.cpp \
    $$PWD/dcameraview.cpp \
    $$PWD/dscrollbar.cpp \
    $$PWD/dscrollarea.cpp \
    $$PWD/darrowrectangle.cpp \
    $$PWD/dcalendar.cpp \
    $$PWD/dgraphicsgloweffect.cpp \
    $$PWD/anchors.cpp \
    $$PWD/dbasebutton.cpp \
    $$PWD/dlistwidget.cpp \
    $$PWD/dobject.cpp \
    $$PWD/dboxwidget.cpp \
    $$PWD/dcircleprogress.cpp \
    $$PWD/dstackwidget.cpp \
    $$PWD/dcheckbox.cpp \
    $$PWD/dfilechooseredit.cpp \
    $$PWD/dpasswordedit.cpp \
    $$PWD/dipv4lineedit.cpp \
    $$PWD/dspinbox.cpp \
    $$PWD/doptionlist.cpp \
    $$PWD/doption.cpp \
    $$PWD/dpicturesequenceview.cpp

RESOURCES += \
    $$PWD/../themes/dui_theme_dark.qrc \
    $$PWD/../icons.qrc \
    $$PWD/../themes/dui_theme_light.qrc

INCLUDEPATH += $$PWD
