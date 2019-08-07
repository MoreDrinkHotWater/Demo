//
// Created by zhihui on 6/21/19.
//

#ifndef DEMO_TWO_RENDER_INCLUDE_MEASUREMENT_H_
#define DEMO_TWO_RENDER_INCLUDE_MEASUREMENT_H_

#include <osgGA/GUIEventHandler>

namespace osgViewer{
class View;
}
class Measurement : public osgGA::GUIEventHandler{
    public:
    explicit Measurement(osg::Switch *rootNode);
    ~Measurement() override ;

    bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa) override;

    void pick(const osgGA::GUIEventAdapter &ea, osgViewer::View *view);

    private:

//    void rollback();

    void cleanup();

    double  calculateDistance(const osg::Vec3d &p1, const osg::Vec3d &p2) const;

    private:
    osg::ref_ptr<osg::Switch> rootNode;
    osg::ref_ptr<osg::Switch> measurementNode;
    osg::ref_ptr<osg::Geode> measurementLineGeode;

    //
    std::vector<std::pair<size_t, osg::Vec3d>> selectedPoints;

    size_t curPointIndex;

    float x, y;
};
// 简化输出代码 第一个参数： std::ostream &os 和 ostream &operator 参数要一致 且要以第一个参数为返回值 此处即 os
// const osg::Vec3d &point 为 某种数据类型
std::ostream &operator<<(std::ostream &os, const osg::Vec3d &point);

#endif //DEMO_TWO_RENDER_INCLUDE_MEASUREMENT_H_
