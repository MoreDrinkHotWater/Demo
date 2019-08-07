//
// Created by zhihui on 8/6/19.
//

#include <include/ClearPointsEvents.h>
#include <include/NodeTreeSearch.h>
#include <include/NodeNames.h>
#include <osg/Switch>
#include <osgViewer/View>
#include <osgDB/ReadFile>

ClearPointsEvents::ClearPointsEvents(osg::Switch *rootNode):
        rootNode(rootNode),
        clearpointseventsNode(dynamic_cast<osg::Switch *>(NodeTreeSearch::findNodeWithName(rootNode, clearpointseventsNodeName))),
        showdemo (osgDB::readNodeFile("/home/zhihui/library/OpenSceneGraph-OpenSceneGraph-3.2/data/cow.osg")){

        }

bool ClearPointsEvents::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
    auto *view = dynamic_cast<osgViewer::View *>(&aa);
    if (view == nullptr) {
        return false;
    }
    static int n = 1;
    switch (ea.getEventType())
    {
        case osgGA::GUIEventAdapter::KEYDOWN:
        {

            if (showdemo == nullptr) {
                std::cout << "readNodeFile:nullptr" << std::endl;
                return false;
            }
            if (ea.getKey() == 'j')
            {
                std::cout<<"success"<<std::endl;
                clearpointseventsNode->addChild(showdemo);
            }
            if(ea.getKey() == 'k')
            {
                std::cout<<"failed"<<std::endl;
                if (n == 1) {
                    rootNode->setAllChildrenOff();
                    std::cout << "n(=1): " << n << std::endl;
                    n = 0;
                    return true;
                }
                if (n == 0) {
                    rootNode->setAllChildrenOn();
                    std::cout << "n(=0): " << n << std::endl;
                    n = 1;
                    return true;
                }
            }
        }
    }
}
