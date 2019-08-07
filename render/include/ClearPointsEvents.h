//
// Created by zhihui on 8/6/19.
//

#ifndef DEMO_TWO_CLEARPOINTSEVENTS_H
#define DEMO_TWO_CLEARPOINTSEVENTS_H

#include <osgGA/GUIEventHandler>
#include "NodeTreeSearch.h"
#include <include/NodeNames.h>
#include <osg/Switch>
#include <osgViewer/View>
#include <osgDB/ReadFile>

namespace osgViewer{
    class View;
}
class ClearPointsEvents : public osgGA::GUIEventHandler{
public:
    explicit ClearPointsEvents(osg::Switch *rootNode);

    ~ClearPointsEvents() override = default;

    bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa) override;

     // void pick(const osgGA::GUIEventAdapter &ea, osgViewer::View *view);

private:
    osg::ref_ptr<osg::Switch> rootNode;
    osg::ref_ptr<osg::Switch> clearpointseventsNode;
    osg::ref_ptr<osg::Node> showdemo;
};
#endif //DEMO_TWO_CLEARPOINTSEVENTS_H
