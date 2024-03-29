//
// Created by zhihui on 8/5/19.
//
#ifndef DEMO_TWO_CLEARIRRELEVANTPOINTS_H
#define DEMO_TWO_CLEARIRRELEVANTPOINTS_H

#include <QObject>
#include <osg/ref_ptr>
#include <osgViewer/View>
#include <include/ClearPointsEvents.h>

class ClearIrrelevantPoints : public QObject {
Q_OBJECT
public:
    explicit ClearIrrelevantPoints() = default;

    ~ClearIrrelevantPoints() override = default;

private:

    osg::ref_ptr<osgViewer::View> mainView;
    osg::ref_ptr<osg::Switch> rootNode;

public Q_SLOTS:

    void clearIrrelevantPointsSlot(osg::ref_ptr<osg::Switch> &rootnode, osg::ref_ptr<osgViewer::View> &mainview);

};

#endif //DEMO_TWO_CLEARIRRELEVANTPOINTS_H
