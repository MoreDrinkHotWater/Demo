//
// Created by zhihui on 6/20/19.
//

#ifndef DEMO_TWO_GENERATEOCTREEWORKER_H
#define DEMO_TWO_GENERATEOCTREEWORKER_H

#include <QObject>

class GenerateOctreeWorker : public QObject{
    Q_OBJECT

public:
    explicit GenerateOctreeWorker(QObject *parent= nullptr);
    ~GenerateOctreeWorker() override = default;

public Q_SLOTS:
    void generateOctreeData(const QString &filePath, bool hasRGB);
Q_SIGNALS:
    void doneGenerateOctreeDataSignal();
};



#endif //DEMO_TWO_GENERATEOCTREEWORKER_H
