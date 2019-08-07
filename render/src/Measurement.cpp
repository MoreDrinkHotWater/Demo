//
// Created by zhihui on 6/21/19.
//

//
// Created by zhihui on 6/21/19.
//

#include <iostream>
#include <iomanip>

#include <osg/Geode>
#include <osg/Switch>
#include <osgViewer/View>
#include <osg/ValueObject>
#include <osg/ShapeDrawable>
#include <osgText/Text>

#include <math.h>
#include <QDebug>

#include <include/Measurement.h>
#include <include/NodeTreeSearch.h>
#include <include/NodeNames.h>
#include "../../common/include/VectorMapSingleton.h"
#include "../../common/include/Color.h"

Measurement::Measurement(osg::Switch *rootNode)
    : rootNode(rootNode),
      measurementNode(dynamic_cast<osg::Switch *>(NodeTreeSearch::findNodeWithName(rootNode, tempNodeName))),
      measurementLineGeode(nullptr),
      curPointIndex(1),
      x(0),
      y(0) {}

Measurement::~Measurement() {
    cleanup();
}

bool Measurement::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa) {
    auto *view = dynamic_cast<osgViewer::View *>(&aa);
    if (view == nullptr) {
        return false;
    }
    switch (ea.getEventType()) {

        case (osgGA::GUIEventAdapter::MOVE): {
            x = ea.getX();
            y = ea.getY();

            if (selectedPoints.empty()) {
                return false;
            }

            double w = 1.5, h = 1.5;
            osg::ref_ptr<osgUtil::PolytopeIntersector> picker = new osgUtil::PolytopeIntersector(
                osgUtil::Intersector::WINDOW, x - w, y - h, x + w, y + h);
            osgUtil::IntersectionVisitor iv(picker);
            view->getCamera()->accept(iv);

            if (picker->containsIntersections()) {
                osg::Vec3d curPoint;

                bool isIntersect = false;
                auto intersections = picker->getIntersections();
                for (const auto &intersection: intersections) {
                    auto childNode = intersection.nodePath.back();
                    if (childNode->getName() == "CloudPoints") {
                        curPoint = intersection.localIntersectionPoint;
                        isIntersect = true;
                        break;
                    }
                    if (childNode->getName() == "Sphere") {
                        childNode->getUserValue("pos", curPoint);
                        isIntersect = true;
                        break;
                    }
                }

                if (!isIntersect) {
                    return false;
                }

                osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
                vertices->push_back(std::get<1>(selectedPoints.back()));
                vertices->push_back(curPoint);

                if (measurementLineGeode == nullptr) {
                    measurementLineGeode = new osg::Geode;
                    measurementLineGeode->setName("measurementLineGeode");
                    measurementNode->addChild(measurementLineGeode);
                } else {
                    measurementLineGeode->removeDrawables(0, measurementLineGeode->getNumDrawables());
                }

                osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
                geom->setName("tempLineGeom");
                measurementLineGeode->addDrawable(geom);

                geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, vertices->size()));
                osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
                colors->push_back(osg::Vec4(1.0, 0.8, 0.6, 1.0));

                geom->setColorArray(colors.get());
                geom->setColorBinding(osg::Geometry::BIND_OVERALL);
                geom->setVertexArray(vertices.get());
            }
            return false;
        }

        case (osgGA::GUIEventAdapter::RELEASE): {
            if (x == ea.getX() && y == ea.getY()) {
                pick(ea, view);
            }
            return true;
        }
        default:return false;
    }
}

void Measurement::pick(const osgGA::GUIEventAdapter &ea, osgViewer::View *view) {
    if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON) {

        double w = 1.5, h = 1.5;
        osg::ref_ptr<osgUtil::PolytopeIntersector> picker = new osgUtil::PolytopeIntersector(
            osgUtil::Intersector::WINDOW, x - w, y - h, x + w, y + h);
        osgUtil::IntersectionVisitor iv(picker);
        view->getCamera()->accept(iv);

        if (picker->containsIntersections()) {
            osg::Vec3d localPoint;
            int localPointIndex = 0;

            // 交集： intersections
            auto intersections = picker->getIntersections();
            for (const auto &intersection : intersections) {
                auto childNode = intersection.nodePath.back();
                if (childNode->getName() == "CloudPoints") {
                    localPoint = intersection.localIntersectionPoint;
                    if (!selectedPoints.empty()) {
                        if (std::get<1>(selectedPoints.back()) == localPoint) {
                            return;
                        }
                    }
                    localPointIndex = curPointIndex++;

                    osg::ref_ptr<osg::Geode> nodeGeode = new osg::Geode;
                    nodeGeode->setName("Sphere");
                    nodeGeode->setUserValue("pos", localPoint);
                    nodeGeode->setUserValue("ID", localPointIndex);

                    osg::ref_ptr<osg::ShapeDrawable> nodeSphere = new osg::ShapeDrawable(
                        new osg::Sphere(localPoint, 0.1f));
                    nodeSphere->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
                    nodeGeode->addDrawable(nodeSphere.get());
                    measurementNode->addChild(nodeGeode.get());

                    break;
                }
                if (childNode->getName() == "Sphere") {
                    childNode->getUserValue("pos", localPoint);
                    childNode->getUserValue("ID", localPointIndex);
                    if (!selectedPoints.empty()) {
                        if (std::get<1>(selectedPoints.back()) == localPoint) {
                            return;
                        }
                    }
                    osg::ref_ptr<osg::Geode> nodeGeode = new osg::Geode;
                    nodeGeode->setName("Sphere");
                    nodeGeode->setUserValue("pos", localPoint);
                    nodeGeode->setUserValue("ID", localPointIndex);
                    osg::ref_ptr<osg::ShapeDrawable> nodeSphere = new osg::ShapeDrawable(
                        new osg::Sphere(localPoint, 0.1f));
                    nodeSphere->setColor(osg::Vec4(1.0, 1.0, 1.0, 1.0));
                    nodeGeode->addDrawable(nodeSphere.get());
                    measurementNode->addChild(nodeGeode.get());

                    break;
                }
            }
            // 所选点可能在临时的线上，localPoint是默认的0值
            if (localPointIndex == 0) {
                return;
            }
            std::cout << "------------Debug-----------------" << std::endl;
            selectedPoints.emplace_back(std::make_pair(localPointIndex, localPoint));
            if (selectedPoints.size() == 2) {
                osg::Vec3d penultimatePoint = std::get<1>(*(selectedPoints.end() - 2));
                osg::Vec3d lastPoint = std::get<1>(selectedPoints.back());

                osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
                vertices->push_back(penultimatePoint);
                vertices->push_back(lastPoint);

                osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
                colors->push_back(osg::Vec4(1.0, 0.8, 0.6, 1.0));

                osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
                geom->setName("solidLineGeom");
                geom->setVertexArray(vertices.get());
                geom->setColorArray(colors.get());
                geom->setColorBinding(osg::Geometry::BIND_OVERALL);
                geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2));

                osg::ref_ptr<osg::Geode> geode = new osg::Geode;
                geode->setName("solidLineGeode");
                geode->addDrawable(geom);

                measurementNode->addChild(geode);

                osg::ref_ptr<osg::Switch> lineTextNode =
                    dynamic_cast<osg::Switch *>(NodeTreeSearch::findNodeWithName(rootNode, lineTextNodeName));
                osg::Vec3d pos = (penultimatePoint + lastPoint) / 2;
                std::string name = "MLine_";

                osg::ref_ptr<osg::Geode> lineTextGeode = new osg::Geode;
                lineTextGeode->setName(name);

                osg::ref_ptr<osgText::Text> text = new osgText::Text;
                text->setCharacterSize(1.0);
                text->setAxisAlignment(osgText::TextBase::XY_PLANE);
                text->setPosition(pos);
                text->setText(std::to_string(calculateDistance(penultimatePoint, lastPoint)));
                text->setColor(osg::Vec4(1.0, 0.8, 0.6, 1.0));

                lineTextGeode->addDrawable(text);

                lineTextNode->addChild(lineTextGeode);

                selectedPoints.clear();
            }
        }
    }

    if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) {
        cleanup();
    }
}

double Measurement::calculateDistance(const osg::Vec3d &p1, const osg::Vec3d &p2) const {
    return (p2 - p1).length();
}

void Measurement::cleanup() {
    if (measurementLineGeode != nullptr) {
        measurementLineGeode->removeDrawables(0, measurementLineGeode->getNumDrawables());
        measurementLineGeode = nullptr;
    }
    measurementNode->removeChildren(0, measurementNode->getNumChildren());

    osg::ref_ptr<osg::Switch>
        lineTextNode = dynamic_cast<osg::Switch *>(NodeTreeSearch::findNodeWithName(rootNode, lineTextNodeName));
    osg::ref_ptr<osg::Geode> lineTextGeode;
    while ((lineTextGeode =
                dynamic_cast<osg::Geode *>(NodeTreeSearch::findNodeWithName(rootNode,
                                                                            std::string("MLine_").c_str())))
        != nullptr) {

        lineTextGeode->removeDrawables(0, lineTextGeode->getNumDrawables());
        lineTextNode->removeChild(lineTextGeode);
    }

    selectedPoints.clear();
}
