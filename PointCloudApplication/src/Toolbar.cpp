//
// Created by zhihui on 7/23/19.
//
#include <include/Toolbar.h>

#include <QMainWindow>
#include <QMenu>
#include <QMessageBox>
#include <QCoreApplication>
#include <QSettings>
#include <QDomElement>
#include <QTreeWidget>

#include <stdlib.h>
#include <iostream>

#include <include/mainWindow.h>
#include <QDockWidget>
#include <QListWidget>
#include <QMainWindow>


ToolBar::ToolBar(const QString &title, QWidget *parent)

        : QToolBar(parent)
{
//    TestAction = new QAction(this);
//    TestAction->setText(tr("Test"));
//    connect(TestAction, &QAction::triggered, this, &ToolBar::Test);
//
//    ManageAction = new QAction(this);
//    ManageAction->setText(tr("Manage Projects..."));
//    connect(ManageAction, &QAction::triggered, this, &ToolBar::Manage);
//
//    menu = new QMenu(title, this);
//
//    menu->addAction(TestAction);
//    menu->addAction(ManageAction);

    readIniFile();

    // std::cout<<"ProjoctNameStr.size(): "<<ProjoctNameStr.size()<<std::endl;

    menu = new QMenu(title, this);

    for (int i = 0; i < ProjoctNameStr.size(); ++i) {

        TestActionGroup = new QActionGroup(this);

        auto *action = new QAction(this);

        TestActionGroup->addAction(action);

        action->setText(ProjoctNameStr.at(i));

        menu->addAction(action);

        //connect(TestActionGroup, &QAction::triggered, this, &ToolBar::Test);

        // 为了获得点击的项目名 这里我们采用这种的写法 传一个 action 过去
        connect(TestActionGroup, SIGNAL(triggered(QAction*)), this, SLOT(Test(QAction*)));

        connect(action, &QAction::triggered, this, &ToolBar::SendData);
    }

    ManageAction = new QAction(this);
    ManageAction->setText(tr("Manage Projects..."));
    connect(ManageAction, &QAction::triggered, this, &ToolBar::Manage);

    menu->addAction(ManageAction);
}

void ToolBar::readIniFile()
{
    QString filePath;
    filePath = QCoreApplication::applicationDirPath();
    filePath += "/Application/test.ini";

    QSettings settings(filePath, QSettings::IniFormat);

    /*
    * 取组 和 keys
    */
    QStringList all = settings.childGroups();

    settings.beginGroup(all[1]);

    // 取分组里的 数据组数
    QStringList keys = settings.childKeys();

    QStringList NameValues;

    for(auto &key:keys)
    {
        NameValues.append("Project/"+key);
    }

    settings.endGroup();

    settings.beginGroup(all[0]);
    // 取分组里的 数据组数
    QStringList Url_keys = settings.childKeys();

    QStringList UrlValues;

    for(auto &key:Url_keys)
    {
        UrlValues.append("DataFilesPath/"+key);
    }

    settings.endGroup();

    int size = NameValues.size();

    QString NameStr,DataFilesPathStr,flag;

    for (int i = 0; i < size; ++i) {
        NameStr = settings.value(NameValues[i]).toString();
        DataFilesPathStr = settings.value(UrlValues[i]).toString();

        ProjoctNameStr.append(NameStr);

        map.insert(NameStr,DataFilesPathStr);
    }

//    for (auto &temp:map) {
//        std::cout<<"map: "<<temp.toStdString()<<std::endl;
//    }

}

void ToolBar::Test(QAction *action)
{


    QString Text = action->text();

    QString DataFilesPath;

    for (auto &temp:map) {
        QMap<QString,QString>::iterator it = map.find(Text);
        DataFilesPath = it.value();
        break;
    }

    std::cout<<"map.key: "<<Text.toStdString()<<std::endl;
    std::cout<<"map.value: "<<DataFilesPath.toStdString()<<std::endl;

    // 如果有项目被打开了， 则先关闭该项目， 再加载用户点击的项目，并且修改ini文件的次序。

    readXmlFile(DataFilesPath);

    // 如果没有项目被打开， 则直接加载用户点击的项目，并且修改ini文件的次序。

}

void ToolBar::readXmlFile(QString &DataFilesPath)
{
    QFile file(DataFilesPath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(nullptr, "Title", "Cannot read filr %1",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }

    QString errorStr;
    int errorLine,errorColumn;

    QDomDocument doc;
    if (!doc.setContent(&file, false, &errorStr, &errorLine,
                        &errorColumn)) {
        QMessageBox::critical(nullptr, tr("Error"),
                              tr("Parse error at line %1, column %2: %3")
                                      .arg(errorLine).arg(errorColumn).arg(errorStr));
        return;
    }

    QDomElement root = doc.documentElement();

    ProjectName =  root.attribute("name");


    std::cout<<"root.tagName: "<<root.tagName().toStdString()<<std::endl;
    std::cout<<"root.attribute(\"name\"): "<<root.attribute("name").toStdString()<<std::endl;
    std::cout<<"root.attribute(\"exists\"): "<<root.attribute("exists").toStdString()<<std::endl;

    if(root.tagName() != "project")
    {
        QMessageBox::critical(nullptr, tr("Error"),
                              tr("Not a project file"));
        return;
    }

    parseProjectElement(root);
    file.close();
}

// 普通函数
void ToolBar::parseProjectElement(const QDomElement &element)
{
    QDomElement directory = element.firstChildElement();
    if (!directory.isNull() && directory.toElement().tagName() == "directory") {
            parseDirectoryElement(directory);
    }
}

void ToolBar::parseDirectoryElement(const QDomElement &element)
{
    QDomElement dataFiles = element.firstChildElement();

    DataFile = dataFiles.attribute("dir");

    std::cout<<"dir: "<<dataFiles.attribute("dir").toStdString()<<std::endl;
    std::cout<<"num: "<<dataFiles.attribute("num").toStdString()<<std::endl;
    QDomElement MD5 = dataFiles.firstChildElement();
    while(!MD5.isNull())
    {
        if (MD5.toElement().tagName() == "MD5") {
            std::cout<<"MD5: "<<MD5.attribute("MD5").toStdString()<<std::endl;
            std::cout<<"fileName: "<<MD5.attribute("fileName").toStdString()<<std::endl;
        }
        MD5 = MD5.nextSiblingElement();
    }
    parseMetaDataElement(dataFiles);
}


void ToolBar::parseMetaDataElement(const QDomElement &element)
{
    QDomElement metaData = element.nextSiblingElement();
    std::cout<<"dir: "<<metaData.attribute("dir").toStdString()<<std::endl;
    parseGroundCSVDataElement(metaData);
}

void ToolBar::parseGroundCSVDataElement(const QDomElement &element)
{
    QDomElement groundCSVData = element.nextSiblingElement();
    std::cout<<"dir: "<<groundCSVData.attribute("dir").toStdString()<<std::endl;
    parseJSONDataElement(groundCSVData);
}

void ToolBar::parseJSONDataElement(const QDomElement &element)
{
    QDomElement JsonData = element.nextSiblingElement();

    JSONData = JsonData.attribute("dir");

    std::cout<<"dir: "<<JsonData.attribute("dir").toStdString()<<std::endl;
    parseCSVDataElement(JsonData);
}

void ToolBar::parseCSVDataElement(const QDomElement &element)
{
    QDomElement CsvData = element.nextSiblingElement();
    CSVData = CsvData.attribute("dir");
    std::cout<<"dir: "<<CsvData.attribute("dir").toStdString()<<std::endl;
    parseMapDataElement(CsvData);
}

void ToolBar::parseMapDataElement(const QDomElement &element)
{
    QDomElement MapData = element.nextSiblingElement();
    mapData = MapData.attribute("dir");
    std::cout<<"dir: "<<MapData.attribute("dir").toStdString()<<std::endl;
}

void ToolBar::Manage()
{
    QMessageBox::information(nullptr, "Title", "Manage",
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

void ToolBar::SendData()
{
    emit SendSignal(ProjectName, DataFile, JSONData, CSVData, mapData);
}
