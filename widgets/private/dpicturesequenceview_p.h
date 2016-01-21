#ifndef DPICTURESEQUENCEVIEW_P_H
#define DPICTURESEQUENCEVIEW_P_H

#include "dpicturesequenceview.h"
#include "dobject_p.h"

#include <QList>
#include <QGraphicsScene>
#include <QTimer>

DUI_BEGIN_NAMESPACE

class DPictureSequenceViewPrivate : public DObjectPrivate
{
    D_DECLARE_PUBLIC(DPictureSequenceView)

public:
    DPictureSequenceViewPrivate(DPictureSequenceView *q);

    void init();

    void play();
    void setPictureSequence(const QStringList &sequence);

    int speed() const;
    void setSpeed(int speed);

    bool singleShot() const;
    void setSingleShot(bool singleShot);

public slots:
    void refreshPicture();

protected:
    void addPicture(const QPixmap &pixmap);

public:
    int m_lastItemPos = 0;
    int m_speed = 0;
    bool m_singleShot = false;

    QGraphicsScene *m_scene;
    QTimer *m_refreshTimer;
    QList<QGraphicsPixmapItem *> m_pictureList;
};

DUI_END_NAMESPACE

#endif // DPICTURESEQUENCEVIEW_P_H
