//
// Created by zhihui on 6/19/19.
//
#include <iostream>
#include <include/mainWindow.h>
#include <include/GenerateOctreeWorker.h>
#include <include/OpenFileDialog.h>
#include "../../render/include/OSGWidget.h"
#include <include/NewFileDialog.h>
#include <include/AddConsoleDialog.h>
#include <include/Toolbar.h>

#include <QApplication>
#include <QAction>
#include <QTreeWidget>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QMessageBox>
#include <QProgressDialog>
#include <QFileDialog>
#include <QDebug>
#include <QCloseEvent>
#include <QDir>

#include <QListWidget>
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          osgWidget(new OSGWidget(this)), //这里是为了把 QWidget 和 osgWidget 整合起来
        // class OSGWidget : public QWidget, public osgViewer::CompositeViewer
          treeWidget(new QTreeWidget(this)),
          pMenuBar(menuBar()),
          pToolBar(addToolBar("Tools")),
          pStatusBar(statusBar()),
          clickedEditorAction(nullptr),

          clickedColorAction(nullptr),

          openFileAction(new QAction(this)),
          saveFileAction(new QAction(this)),
          closeCurrentFileAction(new QAction(this)),
          quitAppActionAction(new QAction(this)),
          drawLineAction(new QAction(this)),
          modifyLineAction(new QAction(this)),
          deleteLineAction(new QAction(this)),

          measurementAction(new QAction(this)),

        // 初始化动作
          showcoordinateaxisAction(new QAction(this)),

          newfileAction(new QAction(this)),

          showConsoleAction(new QAction(this)),

          cutPointAction(new QAction(this)),

          colorByZAction(new QAction(this)),
          colorByIntensityAction(new QAction(this)),
          colorByTextureAction(new QAction(this)),

          dock(),
          consoleList(),
          viewMenu(),

          openFileInfo(),
          originalPCDFileName(QString()),
          fileExtension(),
          hasIntensity(false),
          hasRGB(false),
          generateOctreeWorker(new GenerateOctreeWorker()),
          progressDialog(new QProgressDialog("Reading files...",
                                             QString(),
                                             0,
                                             0,
                                             this)) {
    /*
     * file->addAction(openAction);
     * toolBar->addAction(openAction);
     * 在这里我们可以看到 为窗口添加 状态栏和工具栏时，都只传入了一个参数 openAction
       那是因为在 Qmenu 和 QToolBar 类中，已经重载好了相应的函数。
       在这里我们还可以把 openAction 当成一个容器 它里面载入了不同的数据类型
     */
    setWindowTitle(tr("HDMaps"));

    progressDialog->reset(); // 重置这个进度对话框。
    connect(this, // 信号槽： startGenerateOctreeDataSignal->generateOctreeData
            &MainWindow::startGenerateOctreeDataSignal,
            generateOctreeWorker,
            &GenerateOctreeWorker::generateOctreeData);
    connect(generateOctreeWorker, // 信号槽： doneGenerateOctreeDataSignal->doneGernerateOctreeData
            &GenerateOctreeWorker::doneGenerateOctreeDataSignal,
            this,
            &MainWindow::doneGernerateOctreeData
    );
    /*
     * 通过moveToThread将对象移动到子线程
     * moveToThread是QObject的成员函数
     * 从QObject派生一个类，将耗时的工作写在该类的槽函数中。
     * 通过信号连接派生类的槽函数，并通过信号触发槽函数。(槽函数在子线程中执行)
     */
    generateOctreeWorker->moveToThread(&generateOctreeThread);
    // connect(&generateOctreeThread, &QThread::finished, generateOctreeWorker, &QObject::deleteLater);

    initAction();
    initMenu();
    initToolBar();
    initStatusBar();

    showconsole();

    setCentralWidget(osgWidget);
    osgWidget->init();
}

MainWindow::~MainWindow() {
    generateOctreeThread.quit();
    generateOctreeThread.wait();

    delete generateOctreeWorker;
}

void MainWindow::initAction() {
    //设置菜单栏图片的链接
    openFileAction->setIcon(QIcon::fromTheme("document-open", QIcon(":/images/open.jpg")));
    openFileAction->setText("&Open..."); //？？？
    //设置快捷键
    openFileAction->setShortcut(QKeySequence::Open);
    //设置状态栏的提示信息
    openFileAction->setStatusTip("Open File");
    //信号槽：单击图片->启动open()函数
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);


    saveFileAction->setIcon(QIcon::fromTheme("document-save", QIcon(":/images/file_save.png")));
    saveFileAction->setText("&Save");
    saveFileAction->setShortcut(QKeySequence::Save);
    saveFileAction->setStatusTip("Save File");
    connect(saveFileAction, &QAction::triggered, this, &MainWindow::saveFile);

    closeCurrentFileAction->setIcon(QIcon::fromTheme("edit-delete", QIcon(":/images/file_close.png")));
    closeCurrentFileAction->setText("&CloseCurrentFile");
    closeCurrentFileAction->setShortcut(QKeySequence::Close);
    closeCurrentFileAction->setStatusTip("Close Current File");
    connect(closeCurrentFileAction, &QAction::triggered, this, &MainWindow::closeCurrentFile);

    quitAppActionAction->setIcon(QIcon::fromTheme("application-exit", QIcon(":/images/appExit.png")));
    quitAppActionAction->setText("&Quit");
    quitAppActionAction->setShortcut(QKeySequence::Quit);
    quitAppActionAction->setStatusTip("Quit");
    connect(quitAppActionAction, &QAction::triggered, this, &MainWindow::quitApp, Qt::QueuedConnection);

    drawLineAction->setIcon(QIcon(":/images/traceLine.png"));
    drawLineAction->setText("Draw Line");
    drawLineAction->setStatusTip("Draw line");
    drawLineAction->setCheckable(true);
    connect(drawLineAction, &QAction::triggered, this, &MainWindow::drawLine);

    modifyLineAction->setIcon(QIcon(":/images/modifyTraceLine.jpeg"));
    modifyLineAction->setText("Modify line");
    modifyLineAction->setStatusTip("Modify line");
    modifyLineAction->setCheckable(true);
    connect(modifyLineAction, &QAction::triggered, this, &MainWindow::modifyLine);

    deleteLineAction->setIcon(QIcon::fromTheme("edit-delete", QIcon(":/images/delete.png")));
    deleteLineAction->setText("Delete line");
    deleteLineAction->setStatusTip("Delete line");
    deleteLineAction->setCheckable(true);
    connect(deleteLineAction, &QAction::triggered, this, &MainWindow::deleteLine);

    colorByZAction->setIcon(QIcon(":/images/colorByZ.jpeg"));
    colorByZAction->setText("Color By Z");
    colorByZAction->setStatusTip("Color By Z");
    colorByZAction->setCheckable(true);
    connect(colorByZAction, &QAction::triggered, this, &MainWindow::colorByZ);

    colorByIntensityAction->setIcon(QIcon(":/images/colorByIntensity.jpeg"));
    colorByIntensityAction->setText("Color By Intensity");
    colorByIntensityAction->setStatusTip("Color By Intensity");
    colorByIntensityAction->setCheckable(true);
    connect(colorByIntensityAction, &QAction::triggered, this, &MainWindow::colorByIntensity);

    colorByTextureAction->setIcon(QIcon(":/images/colorByTexture.jpeg"));
    colorByTextureAction->setText("Color By Texture");
    colorByTextureAction->setStatusTip("Color By Texture");
    colorByTextureAction->setCheckable(true);
    connect(colorByTextureAction, &QAction::triggered, this, &MainWindow::colorByTexture);

    measurementAction->setIcon(QIcon(":/images/roadedge.png"));
    measurementAction->setText("Measurement  Length");
    measurementAction->setStatusTip("Measurement  Length");
    measurementAction->setCheckable(true);
    connect(measurementAction, &QAction::triggered, this, &MainWindow::measurementLength);

    showcoordinateaxisAction->setIcon(QIcon(":/images/open.jpg"));
    showcoordinateaxisAction->setText("show coordinate axis");
    showcoordinateaxisAction->setStatusTip("show coordinate axis");
    showcoordinateaxisAction->setCheckable(true);
    connect(showcoordinateaxisAction, &QAction::triggered, this, &MainWindow::showcoordinateAxis);

    newfileAction->setIcon(QIcon(":/images/open.jpg"));
    newfileAction->setText("new file");
    newfileAction->setStatusTip("new file");
    newfileAction->setCheckable(true);
    connect(newfileAction, &QAction::triggered, this, &MainWindow::newfile);


    cutPointAction->setIcon(QIcon(":/images/Cut.png"));
    cutPointAction->setText("cut point");
    cutPointAction->setStatusTip("cut point");
    cutPointAction->setCheckable(true);
    connect(cutPointAction, &QAction::triggered, this, &MainWindow::cutpoint);
}

void MainWindow::initMenu() {
    QMenu *menu;
    menu = new QMenu("&File", this);

    menu->addAction(openFileAction);
    menu->addSeparator(); // 菜单中的横线分隔符号

    // new 一个 类ToolBar的对象指针
    ToolBar *tb = new ToolBar("Open Rencent File", this);

    // 把对象指针 加入到 QList<ToolBar*> 中
    toolBars.append(tb);

    connect(tb, &ToolBar::SendSignal, this, &MainWindow::UpdateConsole);
    // 将工具栏添加到主窗口
    addToolBar(tb);

    // toolbarMenu方法会返回一个 menu[Test, Manage Project...] 这里的 toolBars.at(0) 即 tb
    menu->addMenu(toolBars.at(0)->toolbarMenu());

    menu->addAction(closeCurrentFileAction);
    menu->addSeparator();

    menu->addAction(saveFileAction);
    menu->addSeparator();

    menu->addAction(quitAppActionAction);
    menu->addSeparator();

    pMenuBar->addMenu(menu);

    menu = new QMenu("&Draw", this);

    menu->addActions({drawLineAction, modifyLineAction, deleteLineAction});
    menu->addSeparator();

    pMenuBar->addMenu(menu);

    menu = new QMenu("&Render", this);
    menu->addActions({colorByZAction, colorByIntensityAction, colorByTextureAction});

    pMenuBar->addMenu(menu);

    menu = new QMenu("&Measurement", this);
    menu->addActions({measurementAction});

    pMenuBar->addMenu(menu);

    menu = new QMenu("&Showcoordinateaxis", this);
    menu->addActions({showcoordinateaxisAction});

    pMenuBar->addMenu(menu);

    menu = new QMenu("&NewFile", this);
    menu->addActions({newfileAction});

    pMenuBar->addMenu(menu);

    viewMenu = new QMenu("&View", this);

    pMenuBar->addMenu(viewMenu);

}

void MainWindow::initToolBar() {
    pToolBar->addActions({openFileAction, saveFileAction, closeCurrentFileAction});
    pToolBar->addSeparator();

    pToolBar->addActions({drawLineAction, modifyLineAction, deleteLineAction});
    pToolBar->addSeparator();

    pToolBar->addActions({colorByZAction, colorByIntensityAction, colorByTextureAction});
    pToolBar->addSeparator();

    pToolBar->addActions({measurementAction});
    pToolBar->addSeparator();

    pToolBar->addActions({showcoordinateaxisAction});
    pToolBar->addSeparator();

    pToolBar->addActions({newfileAction});
    pToolBar->addSeparator();

    pToolBar->addActions({cutPointAction});


}

void MainWindow::initStatusBar() {
    pStatusBar->showMessage("Ready");
}

void MainWindow::doneGernerateOctreeData() {
    progressDialog->cancel();
}

void MainWindow::closeEvent(QCloseEvent *e) {
    // 文件未打开
    if (!openFileInfo.fileName().isEmpty()) {
        if (QMessageBox::warning(nullptr,
                                 "Close Current File",
                                 "Save file or not?",
                                 QMessageBox::Yes | QMessageBox::No,
                                 QMessageBox::Yes) == QMessageBox::Yes) {
            saveFile();
        }
    }
    e->accept();
}

void MainWindow::openFile() {
    // QMessageBox::information(this, tr("Information"), tr("Open"));
    auto *openFileDialog = new OpenFileDialog();
    connect(openFileDialog, &OpenFileDialog::openFileInfoSignal, this, &MainWindow::openFileInfoSlot);
    openFileDialog->exec();

    // 打开 ./pointCloudData 路径 格式为：*.pcd *.txt *.las 的文件
    /*
     * Open PointCloud File 为文件框的 Title
     * ./pointCloudData 为路径
     * PointCloud 为过滤器文件名
     */
    QString fileName =
            QFileDialog::getOpenFileName(this, "Open PointCloud", "../../PointCloudData",
                                         "PointCloud(*.pcd *.txt *.las)");

    if (fileName.isEmpty()) {
        return;
    }

    originalPCDFileName = QFileInfo(fileName).fileName();

    QString octreeFileName(fileName);

    if (QFileInfo(fileName).suffix() == "pcd") {
        // 创建.dataOctree隐藏文件夹用来保存八叉树索引文件
        QString octreeDir = QFileInfo(fileName).absolutePath() + "/.dataOctree";
        QDir fdir(octreeDir);
        if (!fdir.exists()) {
            fdir.mkpath(octreeDir);
        }

        QString octreeFileDir =
                QFileInfo(fileName).absolutePath() + "/.dataOctree/" + QFileInfo(fileName).fileName() + ".tree";
        QDir dir(octreeFileDir);
        qDebug() << "octreeFileDir: " << octreeFileDir;
        // 隐藏文件夹中没有该文件的索引文件，则产生一个索引文件

        if (!dir.exists()) {
            progressDialog->setWindowTitle("HDMaps");
            progressDialog->setWindowModality(Qt::ApplicationModal);
            progressDialog->setMinimumDuration(0);
            generateOctreeThread.start();
            emit startGenerateOctreeDataSignal(fileName, hasRGB);
            progressDialog->exec();
        }
        // 设置文件过滤器
        dir.setNameFilters({"*.pcd"});
        // 迭代所有的 pcd 文件
        QFileInfoList list = dir.entryInfoList();
        for (const QFileInfo &fileInfo : list) {
            octreeFileName = fileInfo.absoluteFilePath();
            qDebug() << "octreeFileName: " << octreeFileName;
            break;
        }
    }
    openFileInfo.setFile(octreeFileName);
    // 读取源文件 并把该文件加入到场景树中
    osgWidget->readPCDataFromFile(octreeFileName, hasIntensity, hasRGB, originalPCDFileName);
    // 加载容器的内容
    osgWidget->loadVectorMap();
    // 初始化操作器 例如 鼠标对场景的操作
    osgWidget->initTerrainManipulator();

}

void MainWindow::openFileInfoSlot(QString &fileExtension, bool hasIntensity, bool hasRGB) {
    this->fileExtension = fileExtension;
    this->hasIntensity = hasIntensity;
    this->hasRGB = hasRGB;
}

void MainWindow::newfilePathSlot(QString &NamePath,
                                 QString &DataFilesPath,
                                 QString &JsonDataPath,
                                 QString &CsvDataPath,
                                 QString &MapDataPath) {
    this->NamePath = NamePath;
    this->DataFilesPath = DataFilesPath;
    this->JsonDataPath = JsonDataPath;
    this->CsvDataPath = CsvDataPath;
    this->MapDataPath = MapDataPath;

    // std::cout<<this->NamePath.toStdString()<<std::endl;
}

void MainWindow::saveFile() {

    QDir dir;

    // 文件未打开
    if (openFileInfo.fileName().isEmpty()) {
        return;
    }

    QString fileName;

    // suffix 获取文件的后缀名
    if (openFileInfo.suffix() == "pcd") {
        fileName = originalPCDFileName;
    } else {
        fileName = openFileInfo.fileName();
    }

    // 创建文件夹
    QString dirName = "data/" + fileName + "/";
    if (!dir.exists(dirName)) {
        std::cout << "data directory doesn't exists, try to create it";
        // 创建磁盘路径 ： dirName
        dir.mkpath(dirName);
    }

    // cd 进入文件目录
    dir.cd(dirName);
    std::cout << "save to: " << dir.absolutePath().toStdString();
    osgWidget->saveVectorMap(dir.absolutePath().toStdString());
    osgWidget->transVectorMapToJson(dir.absolutePath().toStdString());
    osgWidget->transVectorMapToCSV(dir.absolutePath().toStdString());
}

void MainWindow::closeCurrentFile() {

}

void MainWindow::quitApp() {
    QMessageBox::information(this, tr("Information"), tr("Open"));
}

void MainWindow::drawLine(bool isActive) {
    if (isActive) {
        if (clickedEditorAction && clickedEditorAction != drawLineAction) {
            clickedEditorAction->setChecked(false);

            //  osgWidget->activeLineModification(false);
            // osgWidget->activeLineDeletion(false);
        }
        clickedEditorAction = drawLineAction;
    }
    osgWidget->activeLineEditor(isActive);
}

void MainWindow::modifyLine(bool isActive) {

}

void MainWindow::deleteLine(bool isActive) {

}

void MainWindow::colorByZ(bool isActive) {
    if (isActive) {
        if (clickedColorAction && clickedColorAction != colorByZAction) {
            clickedColorAction->setChecked(false);

            osgWidget->activeColorByIntensity(false);
            osgWidget->activeColorByTexture(false);

        }
        clickedColorAction = colorByZAction;
    }
    osgWidget->activeColorByZ(isActive);
}

void MainWindow::colorByIntensity(bool isActive) {
    //QMessageBox::information(this, tr("Information"), tr("Open"));
    if (isActive) {
        if (clickedColorAction && clickedColorAction != colorByIntensityAction) {
            clickedColorAction->setChecked(false);

            osgWidget->activeColorByZ(false);
            osgWidget->activeColorByTexture(false);

        }
        clickedColorAction = colorByIntensityAction;
    }
    osgWidget->activeColorByIntensity(isActive);
}

void MainWindow::colorByTexture(bool isActive) {
    // QMessageBox::information(this, tr("Information"), tr("Open"));
    if (isActive) {
        if (clickedColorAction && clickedColorAction != colorByTextureAction) {
            clickedColorAction->setChecked(false);
            osgWidget->activeColorByZ(false);
            osgWidget->activeColorByIntensity(false);
        }
        clickedColorAction = colorByTextureAction;
    }

    osgWidget->activeColorByTexture(isActive);
}

void MainWindow::measurementLength(bool isActive) {
    if (isActive) {
        if (clickedEditorAction && clickedEditorAction != measurementAction) {
            clickedEditorAction->setChecked(false);
        }
        clickedEditorAction = measurementAction;
    }
    osgWidget->activeMeasurementLength(isActive);
}

void MainWindow::showcoordinateAxis(bool isActive) {
    if (isActive) {
        if (clickedEditorAction && clickedEditorAction != showcoordinateaxisAction) {
            clickedEditorAction->setChecked(false);

            osgWidget->activeMeasurementLength(false);
            osgWidget->activeLineEditor(false);
            osgWidget->activeColorByIntensity(false);
            osgWidget->activeColorByZ(false);
            osgWidget->activeColorByTexture(false);
        }
        clickedEditorAction = showcoordinateaxisAction;
    }
    osgWidget->activeShowCoordiateAxis(isActive);
}

void MainWindow::cutpoint(bool isActive)
{
//    QMessageBox::information(this, tr("Information"), tr("Open"));
    if (isActive){
        if(clickedEditorAction && clickedEditorAction != cutPointAction)
        {
            clickedEditorAction->setChecked(false);

            osgWidget->activeLineEditor(false);
            osgWidget->activeColorByIntensity(false);
            osgWidget->activeColorByTexture(false);
            osgWidget->activeColorByZ(false);
            osgWidget->activeMeasurementLength(false);
            osgWidget->activeShowCoordiateAxis(false);
        }
        clickedEditorAction = cutPointAction;
    }
    osgWidget->activeClearIrrelevantPoints(isActive);
}


void MainWindow::newfile() {
    auto *newFileDialog = new NewFileDialog();
    connect(newFileDialog, &NewFileDialog::newfilePathSignal, this, &MainWindow::newfilePathSlot);
    newFileDialog->exec();

    consoleList->clear();
    consoleList->addItems(QStringList() << NamePath + ":  " + DataFilesPath);
    dock->setWidget(consoleList);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
}

void MainWindow::showconsole() {
//    auto *addConsoleDialog = new AddConsoleDialog();
//    connect(this,&MainWindow::showConsoleSignal,addConsoleDialog,&AddConsoleDialog::showConsoleSlot);
//    addConsoleDialog->show();

    dock = new QDockWidget(tr("Console"), this);
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    dock->setHidden(true);
    consoleList = new QListWidget(dock);
    consoleList->addItems(QStringList()
                                  << NamePath + DataFilesPath
    );
    dock->setWidget(consoleList);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
    viewMenu->addActions({dock->toggleViewAction()});
}

void MainWindow::UpdateConsole(const QString &projectName, const QString &datafile, const QString &jsondata, const QString &csvdata, const QString &mapdata)
{
    std::cout << "The Project name is:" << projectName.toStdString() << std::endl;

    consoleList->clear();

    consoleList->addItems(QStringList() << "Project name: " + projectName);
    consoleList->addItems(QStringList() << "DataFile: " + datafile);
    consoleList->addItems(QStringList() << "JSONData: " + jsondata);
    consoleList->addItems(QStringList() << "CSVData: " + csvdata);
    consoleList->addItems(QStringList() << "mapData: " + mapdata);

    dock->setWidget(consoleList);
    addDockWidget(Qt::BottomDockWidgetArea, dock);
}



