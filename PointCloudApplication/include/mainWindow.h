//
// Created by zhihui on 6/19/19.
//

#ifndef DEMO_TWO_MAINWINDOW_H
#define DEMO_TWO_MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>  // 文件信息获取类：可获取文件的名称，大小，创建时间等信息...
#include <QThread> // 创建多线程的接口类

#include <QListWidget>
#include <QToolBar>
#include <QList>

#include <include/Toolbar.h>

class OSGWidget;

class QTreeWidget; // 目录树组件: QTreeWidget类是创建和管理目录树结构的类。

class QAction; // Qt 使用 QAction 类作为动作，这个类就是代表了窗口的一个“动作”。

class QProgressDialog; // 进度条对话框类

class GenerateOctreeWorker; // 用于产生八叉树的类


class MainWindow : public QMainWindow
{
Q_OBJECT // 宏定义 为了使用信号槽

public:
    explicit MainWindow(QWidget *parent = nullptr); // 窗口的构造函数
    ~MainWindow() override; // 窗口的析构函数 为什么要重写？？？

private:

    void initAction(); // 初始化动作的函数

    void initMenu(); // 初始化菜单栏的函数

    void initToolBar(); // 初始化工具栏的函数

    void initStatusBar(); // 初始化状态栏的函数

    /*
     * 关于索引和需要用到动作的信号槽
     */
Q_SIGNALS: // 信号：开始产生八叉树

    void test(); // ? ? ?

    void startGenerateOctreeDataSignal(const QString &filePath, bool hasRGB);

    // void showConsoleSignal(const QString &namePath, const QString &dataFilePath);

public Q_SLOTS: // 槽：产生八叉树已完成
    void doneGernerateOctreeData();

    void newfilePathSlot(QString &NamePath, QString &DataFilesPath, QString &JsonDataPath, QString &CsvDataPath, QString &MapDataPath);


protected:
    void closeEvent(QCloseEvent *e) override; // 关闭事件的函数

private Q_SLOTS: // 所有的槽

    void openFile();

    void openFileInfoSlot(QString &fileExtension, bool hasIntensity, bool hasRGB);

    void saveFile();

    void closeCurrentFile();

    void quitApp();

    void drawLine(bool isActive);

    void modifyLine(bool isActive);

    void deleteLine(bool isActive);

    void colorByZ(bool isActive);

    void colorByIntensity(bool isActive);

    void colorByTexture(bool isActive);

    void measurementLength(bool isActive);

    void showcoordinateAxis(bool isActive);

    void cutpoint(bool isActive);

    void newfile();

    void showconsole();


private: // 创建需要用到的类 的对象 便于操作。

    OSGWidget *osgWidget;

    QTreeWidget *treeWidget;

    // 菜单、工具和状态栏
    QMenuBar *pMenuBar;
    QToolBar *pToolBar;
    QStatusBar *pStatusBar;

    // 编辑线的时候要用到的动作
    QAction *clickedEditorAction;

    QAction *clickedColorAction;

    // 对于文件的处理动作
    QAction *openFileAction, *saveFileAction, *closeCurrentFileAction, *quitAppActionAction;

    // 画线的处理动作
    QAction *drawLineAction, *modifyLineAction, *deleteLineAction;

    //测量
    QAction *measurementAction;

    //展示坐标轴的动作
    QAction *showcoordinateaxisAction;

    // 新建文件的动作
    QAction *newfileAction;

    // 剪切多余的点数据
    QAction *cutPointAction;

    // 显示控制台
    QAction *showConsoleAction;

    QAction *colorByZAction, *colorByIntensityAction, *colorByTextureAction;

    // 打开文件
    QFileInfo openFileInfo;

    // 读取文件名
    QString originalPCDFileName;

    // Open Recent Project
    QList<ToolBar*> toolBars;

    // 用户选择的文件类型
    QString fileExtension;
    bool hasIntensity;
    bool hasRGB;

    QString NamePath;

    QString DataFilesPath;

    QString JsonDataPath;

    QString CsvDataPath;

    QString MapDataPath;

    // 生成索引
    GenerateOctreeWorker *generateOctreeWorker;

    // 使用线程的时候需要显示进度
    QProgressDialog *progressDialog;

    // 多线程
    QThread generateOctreeThread;

    QDockWidget *dock;

    QListWidget *consoleList;

    QMenu *viewMenu;

public Q_SLOTS:
    void UpdateConsole(const QString &projectName, const QString &datafile, const QString &jsondata, const QString &csvdata, const QString &mapdata);

};

#endif //DEMO_TWO_MAINWINDOW_H
