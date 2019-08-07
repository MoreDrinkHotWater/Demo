//
// Created by zhihui on 3/27/19.
//

#ifndef POINTCLOUDAPPLICATION_OSGWIDGET_H
#define POINTCLOUDAPPLICATION_OSGWIDGET_H

#include <QWidget>
#include <QFileInfo>
#include <QThread>

#include <osgViewer/CompositeViewer>

#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>

#include <liblas/liblas.hpp>
#include "ProgressBarWorker.h"
#include "LineEditor.h"
#include "Measurement.h"
#include "ShowCoordinateAxis.h"
#include "NewFile.h"

class QTimer;

class QFileInfo;

class QProgressDialog;

class ProgressBarWorker;

class ClearIrrelevantPoints;

class ClearPointsEvents;

namespace osgQt {
class GraphicsWindowQt;
}

//osgViewer::CompositeViewer是一个osgViewer::View序列，包含多个osgViewer::View。
class OSGWidget : public QWidget, public osgViewer::CompositeViewer {
    Q_OBJECT
    public:
    explicit OSGWidget(QWidget *parent = nullptr);

    ~OSGWidget() override;

    public:
    void init(); //

    void reset(); //

    void readPCDataFromFile(const QFileInfo &fileInfo, bool hasIntensity, bool hasRGB, const QString &originalPCDFileName); //

    void loadVectorMap(); //

    void initTerrainManipulator(); //

    void activeLineEditor(bool isActive);

    void activeLineModification(bool isActive);

    void activeLineDeletion(bool isActive);

    void activeColorByZ(bool isActive);

    void activeColorByIntensity(bool isActive);

    void activeColorByTexture(bool isActive);

    void activeMeasurementLength(bool isActive);

    void activeShowCoordiateAxis(bool isActive);

    //
    void activeClearIrrelevantPoints(bool isActive);

    void transENU2LLH() const; // ???

    void saveVectorMap(const std::string &dirPath) const;

    void transVectorMapToJson(const std::string &dirPath) const;

    void transVectorMapToCSV(const std::string &dirPath) const;

    void transAllPointsToJSON(const std::string &dirPath) const;

    private:
    void paintEvent(QPaintEvent *) override;

    void initSceneGraph(); // 初始化一个场景

    void initCamera(); // 初始化一个 Camera（相机）：完成场景和节点树的构建

    void initEditor(); //

    void initManipulator(); //

    void initVectorMap(); //

    osgQt::GraphicsWindowQt *
    createGraphicsWindow(int x, int y, int w, int h, const std::string &name = "", bool windowDecoration = false);

    // osg::Geode ： osg中的结点之一，Geode作为叶节点，用于保存几何信息以便渲染。
    osg::ref_ptr<osg::Geode> readPCDataFromPCDFile(const QFileInfo &fileInfo, bool hasIntensity, bool hasRGB);

    osg::ref_ptr<osg::Geode> readPCDataFromTXTFile(const QFileInfo &fileInfo, bool hasIntensity, bool hasRGB);

    osg::ref_ptr<osg::Geode> readPCDataFromLASFlile(const QFileInfo &fileInfo, bool hasIntensity, bool hasRGB);

    osg::ref_ptr<osg::Geode> readPCLDataFromXYZIFile(const QFileInfo &fileInfo);

    osg::ref_ptr<osg::Geode> readPCLDataFromXYZRGBFile(const QFileInfo &fileInfo);

    osg::ref_ptr<osg::Geode> readTXTDataFromIFile(const QFileInfo &fileInfo);

    osg::ref_ptr<osg::Geode> readTXTDataFromRGBFile(const QFileInfo &fileInfo);

    osg::ref_ptr<osg::Geode> readTXTDataFromIRGBFile(const QFileInfo &fileInfo);

    osg::ref_ptr<osg::Geode> readTXTDataFromFile(const QFileInfo &fileInfo);

    osg::ref_ptr<osg::Geode> readLASDataFromIFile(const QFileInfo &fileInfo);

    osg::ref_ptr<osg::Geode> readLASDataFromRGBFile(const QFileInfo &fileInfo);

    osg::ref_ptr<osg::Geode> readLASDataFromIRGBFile(const QFileInfo &fileInfo);

    osg::ref_ptr<osg::Geode> readLASDataFromFile(const QFileInfo &fileInfo);

    osg::ref_ptr<osg::Geode> addMapPointCloud(const pcl::PointCloud<pcl::PointXYZI>::Ptr &mapPointCloud,
                                              osg::Vec3 color = osg::Vec3(1.0, 1.0, 1.0));

    osg::ref_ptr<osg::Geode> addMapPointCloud(const pcl::PointCloud<pcl::PointXYZRGB>::Ptr &mapPointCloud,
                                              osg::Vec3 color = osg::Vec3(1.0, 1.0, 1.0));

    osg::ref_ptr<osg::Geode> addMapPointCloud(const osg::ref_ptr<osg::Vec3Array> &vertices,
                                              osg::Vec3 color = osg::Vec3(1.0, 1.0, 1.0)) const;

    void colorPointCloudDataByZ(bool isActive) const;

    void colorPointCloudDataByIntensity(bool isActive) const;

    void colorPointCloudDataByTexture(bool isActive) const;

    // osg::Vec3Array 三元向量数组，继承自STL的vector类，那么我们就可以使用push_back方法来添加数组成员
    osg::ref_ptr<osg::Vec3Array> calculateColorArrayZ() const;

    osg::ref_ptr<osg::Vec3Array> calculateColorArrayIntensity() const;

    osg::ref_ptr<osg::Vec3Array> calculateColorArrayTexture() const;

    // 是否有强度信息
    bool hasDataIntensity() const;

    void drawVectorItems();

    void drawTraceItems();

    void drawPavementItems();

    void drawDrivingArrowItems();

    void drawTrafficLightsItems();

    void drawRoadLinesItems();

    void clearIrrelevantPiont(); //清楚无关点

    template<class T>
    void drawVectorItems(const std::vector<T> &objects);

    Q_SIGNALS:
    void showProgressBarSignal(const QString &progressDialogLabelText);
    void closeProgressBarSignal();

    void clearIrrelevantPointsSignal(osg::ref_ptr<osg::Switch> &rootnode, osg::ref_ptr<osgViewer::View> &mainview);

    private Q_SLOTS:

    void updateFrame();

    private:
    osg::ref_ptr<osgViewer::View> mainView;

    // Switch是一个管理类，它下面可以有很多子类，它就像是一个开关可以控制子类的显示与隐藏，而这种隐藏是不耗费内存的，
    // 与SetNodeMask对比有明显的优势，SetNodeMask事实上只是隐藏了结点，但结点仍被绘制。
    // 该类是从Node和Group派生而来，故可以被加入组结点以及asGroup等等种种方法。是一个非常常用的类。
    osg::ref_ptr<osg::Switch> rootNode;

    osg::ref_ptr<LineEditor> lineEditor;

    // 调用 Measurement 类的构造函数
    osg::ref_ptr<Measurement> measurement;

    osg::ref_ptr<ShowCoordinateAxis> showCoordinateAxis;

    osg::ref_ptr<ClearPointsEvents> clearPointsEvents;

    // 保存高程数据
    std::vector<float> dataZ;

    // 保存强度信息
    std::vector<float> dataIntensity;

    // 保存颜色信息
    std::vector<osg::Vec3> dataColor;

    // 保存所有点云的点
    osg::ref_ptr<osg::Vec3Array> allPoints;

    QTimer *updateTimer;

    QFileInfo openFileInfo;

    QString originalPCDFileName;

    QProgressDialog *progressDialog; //

    ProgressBarWorker *progressBarWorker;

    QThread progressBarThread; //

    ClearIrrelevantPoints *clearIrrelevantPoints;

    QThread clearPointThread; //
};

#endif //POINTCLOUDAPPLICATION_OSGWIDGET_H
