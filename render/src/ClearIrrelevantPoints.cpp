//
// Created by zhihui on 8/5/19.
//
#include <iostream>

#include <QObject>
#include <QThread>

#include <include/ClearIrrelevantPoints.h>

void ClearIrrelevantPoints::clearIrrelevantPointsSlot(osg::ref_ptr<osg::Switch> &rootnode, osg::ref_ptr<osgViewer::View> &mainview) {
    this->mainView = mainview;
    this->rootNode = rootnode;

    std::cout << "ClearIrrelevantPoints thread: " << QThread::currentThreadId() << std::endl;

    std::cout << "ClearIrrelevantPoints :success" << std::endl;
    if (rootNode == nullptr) {
        std::cout << "get failed" << std::endl;
    } else {
        osg::ref_ptr<ClearPointsEvents> clearPointsEvents = new ClearPointsEvents(rootNode);
        mainView->addEventHandler(clearPointsEvents);
    }
}
