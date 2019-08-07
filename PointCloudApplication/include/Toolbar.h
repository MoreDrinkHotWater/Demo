//
// Created by zhihui on 7/23/19.
//

#ifndef DEMO_TWO_TOOLBAR_H
#define DEMO_TWO_TOOLBAR_H
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QActionGroup>
#include <QList>
#include <QDomElement>

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit ToolBar(const QString &title, QWidget *parent);

    QMenu *toolbarMenu() const { return menu; }

private slots:

    void Test(QAction *action);
    static void Manage();


public slots:
    void SendData();

private:

    QMenu *menu;

    QActionGroup *TestActionGroup;

    QAction *ManageAction;

    QList<QString> ProjoctNameStr;

    QMap<QString,QString> map;

    void readIniFile();

    void readXmlFile(QString &DataFilesPath);

private:
    QString ProjectName;
    QString DataFile;
    QString JSONData;
    QString CSVData;
    QString mapData;

    void parseProjectElement(const QDomElement &element);
    void parseDirectoryElement(const QDomElement &element);
    void parseMetaDataElement(const QDomElement &element);
    void parseGroundCSVDataElement(const QDomElement &element);
    void parseJSONDataElement(const QDomElement &element);
    void parseCSVDataElement(const QDomElement &element);
    void parseMapDataElement(const QDomElement &element);

Q_SIGNALS:
    void SendSignal(const QString &projectName, const QString &datafile, const QString &jsondata, const QString &csvdata, const QString &mapdata);
};

#endif //DEMO_TWO_TOOLBAR_H
