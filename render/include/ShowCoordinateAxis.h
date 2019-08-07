//
// Created by zhihui on 7/2/19.
//

#ifndef DEMO_TWO_RENDER_INCLUDE_SHOWCOORDINATEAXIS_H_
#define DEMO_TWO_RENDER_INCLUDE_SHOWCOORDINATEAXIS_H_
#include <osgGA/GUIEventHandler>

namespace osgViewer{
    class View;
}

class ShowCoordinateAxis : public  osgGA::GUIEventHandler
{
    public:

    explicit ShowCoordinateAxis(osg::Switch *rootNode);
    ~ShowCoordinateAxis() override;

    bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa) override;

  //  void show();

    private:
//    void clean();

    private:
    osg::ref_ptr<osg::Switch> rootNode;
    osg::ref_ptr<osg::Switch> showcoordinateaxisNode;
//    osg::ref_ptr<osg::Geode> showcoordinateaxisGeode;
    osg::ref_ptr<osg::Node> showdemo;

//    float x,y,z;
};



#endif //DEMO_TWO_RENDER_INCLUDE_SHOWCOORDINATEAXIS_H_
