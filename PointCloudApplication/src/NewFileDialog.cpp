//
// Created by zhihui on 7/5/19.
//

#include <include/NewFileDialog.h>
#include <include/mainWindow.h>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QTextBrowser>
#include <QDialogButtonBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QMessageBox>
#include <QCoreApplication>
#include <QSettings>
#include <iostream>
#include <string>


NewFileDialog::NewFileDialog(QWidget *parent) :QDialog(parent),
                                               NamePath(),
                                               DataFilesPath(),
                                               JsonDataPath(),
                                               CsvDataPath(),
                                               MapDataPath()
{
    QFrame *line;
    QLabel *label_Input;
    QFrame *line_2;
    QLabel *label_Output;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_Name;
    QSpacerItem *horizontalSpacer_4;
    /*QLineEdit *NameEdit;
    QPushButton *NameButton;*/
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_JSONData;
    QSpacerItem *horizontalSpacer_5;
   /* QLineEdit *JsonDataEdit;
    QPushButton *JsonDataButton;*/
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_CSVData;
    QSpacerItem *horizontalSpacer_6;
    /*QLineEdit *CsvDataEdit;
    QPushButton *CsvDataButton;*/
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_MapData;
    QSpacerItem *horizontalSpacer_7;
    /*QLineEdit *MapDataEdit;
    QPushButton *MapDataButton;*/
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    //QPushButton *CancleButton;
    QSpacerItem *horizontalSpacer_3;
    //QPushButton *SubmitButton;
    QSpacerItem *horizontalSpacer_2;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_DataFiles;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_9;
    /*QLineEdit *DataFilesEdit;
    QPushButton *DataFilesButton;*/
    QLabel *label_Project;

    this->resize(360, 430);
    setAttribute(Qt::WA_DeleteOnClose);

    line = new QFrame(this);

    line->setGeometry(QRect(-10, 90, 371, 16));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    label_Input = new QLabel(this);
    label_Input->setText("Input");

    label_Input->setGeometry(QRect(10, 80, 32, 17));
    label_Input->setText("Input");
    line_2 = new QFrame(this);

    line_2->setGeometry(QRect(0, 170, 360, 16));
    line_2->setFrameShape(QFrame::HLine);
    line_2->setFrameShadow(QFrame::Sunken);
    label_Output = new QLabel(this);
    label_Output->setText("Output");

    label_Output->setGeometry(QRect(10, 160, 42, 17));
    layoutWidget = new QWidget(this);

    layoutWidget->setGeometry(QRect(30, 40, 321, 31));
    horizontalLayout = new QHBoxLayout(layoutWidget);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);

    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    label_Name = new QLabel(layoutWidget);
    label_Name->setText("Name");

    horizontalLayout->addWidget(label_Name);

    horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer_4);

    NameEdit = new QLineEdit(layoutWidget);

    NameEdit->setMinimumSize(QSize(200, 0));
    NameEdit->setMaximumSize(QSize(200, 16777215));
    NameEdit->setMaxLength(32767);

    horizontalLayout->addWidget(NameEdit);

    NameButton = new QPushButton(layoutWidget);

    NameButton->setEnabled(true);
    NameButton->setMinimumSize(QSize(20, 0));
    NameButton->setMaximumSize(QSize(20, 16777215));
    NameButton->setIconSize(QSize(16, 16));
    NameButton->setAutoDefault(false);
    NameButton->setText("...");

    connect(NameButton, &QPushButton::clicked, this, &NewFileDialog::ShowName);

    horizontalLayout->addWidget(NameButton);

    layoutWidget1 = new QWidget(this);

    layoutWidget1->setGeometry(QRect(30, 200, 321, 212));
    verticalLayout_2 = new QVBoxLayout(layoutWidget1);
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setContentsMargins(11, 11, 11, 11);

    verticalLayout_2->setContentsMargins(0, 0, 0, 0);
    verticalLayout = new QVBoxLayout();
    verticalLayout->setSpacing(6);

    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);

    label_JSONData = new QLabel(layoutWidget1);
    label_JSONData->setText("JSONData");


    horizontalLayout_2->addWidget(label_JSONData);

    horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_5);

    JsonDataEdit = new QLineEdit(layoutWidget1);

    JsonDataEdit->setMinimumSize(QSize(200, 0));
    JsonDataEdit->setMaximumSize(QSize(200, 16777215));

    horizontalLayout_2->addWidget(JsonDataEdit);

    JsonDataButton = new QPushButton(layoutWidget1);

    JsonDataButton->setMinimumSize(QSize(20, 0));
    JsonDataButton->setMaximumSize(QSize(20, 16777215));
    JsonDataButton->setText("...");

    connect(JsonDataButton, &QPushButton::clicked, this, &NewFileDialog::ShowJsonData);

    horizontalLayout_2->addWidget(JsonDataButton);


    verticalLayout->addLayout(horizontalLayout_2);

    horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setSpacing(6);

    label_CSVData = new QLabel(layoutWidget1);
    label_CSVData->setText("CSVData");


    horizontalLayout_3->addWidget(label_CSVData);

    horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer_6);

    CsvDataEdit = new QLineEdit(layoutWidget1);

    CsvDataEdit->setMinimumSize(QSize(200, 0));
    CsvDataEdit->setMaximumSize(QSize(200, 16777215));

    horizontalLayout_3->addWidget(CsvDataEdit);

    CsvDataButton = new QPushButton(layoutWidget1);

    CsvDataButton->setMinimumSize(QSize(20, 0));
    CsvDataButton->setMaximumSize(QSize(20, 16777215));
    CsvDataButton->setText("...");

    connect(CsvDataButton, &QPushButton::clicked, this, &NewFileDialog::ShowCsvData);

    horizontalLayout_3->addWidget(CsvDataButton);


    verticalLayout->addLayout(horizontalLayout_3);

    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setSpacing(6);

    label_MapData = new QLabel(layoutWidget1);
    label_MapData->setText("MapData");


    horizontalLayout_4->addWidget(label_MapData);

    horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_4->addItem(horizontalSpacer_7);

    MapDataEdit = new QLineEdit(layoutWidget1);

    MapDataEdit->setMinimumSize(QSize(200, 0));
    MapDataEdit->setMaximumSize(QSize(200, 16777215));

    horizontalLayout_4->addWidget(MapDataEdit);

    MapDataButton = new QPushButton(layoutWidget1);

    MapDataButton->setMinimumSize(QSize(20, 0));
    MapDataButton->setMaximumSize(QSize(20, 16777215));
    MapDataButton->setText("...");

    connect(MapDataButton, &QPushButton::clicked, this, &NewFileDialog::ShowMapData);

    horizontalLayout_4->addWidget(MapDataButton);


    verticalLayout->addLayout(horizontalLayout_4);


    verticalLayout_2->addLayout(verticalLayout);

    verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

    verticalLayout_2->addItem(verticalSpacer);

    horizontalLayout_5 = new QHBoxLayout();
    horizontalLayout_5->setSpacing(6);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_5->addItem(horizontalSpacer);

    CancleButton = new QPushButton(layoutWidget1);
    CancleButton->setText("Cancle");

    connect(CancleButton,&QPushButton::clicked, this, &NewFileDialog::Cancle);


    horizontalLayout_5->addWidget(CancleButton);

    horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_5->addItem(horizontalSpacer_3);

    SubmitButton = new QPushButton(layoutWidget1);
    SubmitButton->setText("Submit");

    connect(SubmitButton,&QPushButton::clicked, this, &NewFileDialog::Submit);

    horizontalLayout_5->addWidget(SubmitButton);

    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_5->addItem(horizontalSpacer_2);


    verticalLayout_2->addLayout(horizontalLayout_5);

    layoutWidget_2 = new QWidget(this);

    layoutWidget_2->setGeometry(QRect(30, 110, 321, 31));
    horizontalLayout_6 = new QHBoxLayout(layoutWidget_2);
    horizontalLayout_6->setSpacing(6);
    horizontalLayout_6->setContentsMargins(11, 11, 11, 11);

    horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
    label_DataFiles = new QLabel(layoutWidget_2);
    label_DataFiles->setText("DataFiles");


    horizontalLayout_6->addWidget(label_DataFiles);

    horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_6->addItem(horizontalSpacer_9);


    horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_6->addItem(horizontalSpacer_8);

    DataFilesEdit = new QLineEdit(layoutWidget_2);

    DataFilesEdit->setMinimumSize(QSize(200, 0));
    DataFilesEdit->setMaximumSize(QSize(200, 16777215));
    DataFilesEdit->setMaxLength(32767);

    horizontalLayout_6->addWidget(DataFilesEdit);

    horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_6->addItem(horizontalSpacer_9);

    DataFilesButton = new QPushButton(layoutWidget_2);

    DataFilesButton->setEnabled(true);
    DataFilesButton->setMinimumSize(QSize(20, 0));
    DataFilesButton->setMaximumSize(QSize(20, 16777215));
    DataFilesButton->setIconSize(QSize(16, 16));
    DataFilesButton->setAutoDefault(false);
    DataFilesButton->setText("...");

    connect(DataFilesButton,&QPushButton::clicked, this, &NewFileDialog::ShowDataFiles);

    horizontalLayout_6->addWidget(DataFilesButton);

    label_Project = new QLabel(this);
    label_Project->setText("Project");

    label_Project->setGeometry(QRect(10, 10, 54, 21));
    QWidget::setTabOrder(NameEdit, NameButton);
    QWidget::setTabOrder(NameButton, DataFilesEdit);
    QWidget::setTabOrder(DataFilesEdit, DataFilesButton);
    QWidget::setTabOrder(DataFilesButton, JsonDataEdit);
    QWidget::setTabOrder(JsonDataEdit, JsonDataButton);
    QWidget::setTabOrder(JsonDataButton, CsvDataEdit);
    QWidget::setTabOrder(CsvDataEdit, CsvDataButton);
    QWidget::setTabOrder(CsvDataButton, MapDataEdit);
    QWidget::setTabOrder(MapDataEdit, MapDataButton);
    QWidget::setTabOrder(MapDataButton, CancleButton);
    QWidget::setTabOrder(CancleButton, SubmitButton);

}


void NewFileDialog::ShowName()
{
    QString fileName =
        QFileDialog::getOpenFileName(this, "Open PointCloud", "../../PointCloudData", "PointCloud(*.pcd *.txt *.las)");

    NameEdit->setText(fileName);

    if (fileName.isEmpty()) {
        return;
    }
}

void NewFileDialog::ShowDataFiles()
{
//    QString fileName =
//        QFileDialog::getOpenFileName(this, "Open PointCloud", "../../PointCloudData", "PointCloud(*.pcd *.txt *.las)");

    QString fileName =
        QFileDialog::getExistingDirectory(this, "Open PointCloud", "../../PointCloudData");

    DataFilesEdit->setText(fileName);

    if (fileName.isEmpty()) {
        return;
    }
}

void NewFileDialog::ShowJsonData()
{
    QString fileName =
        QFileDialog::getOpenFileName(this, "Open PointCloud", "../../PointCloudData", "PointCloud(*.pcd *.txt *.las)");

    JsonDataEdit->setText(fileName);

    if (fileName.isEmpty()) {
        return;
    }
}

void NewFileDialog::ShowCsvData()
{
    QString fileName =
        QFileDialog::getOpenFileName(this, "Open PointCloud", "../../PointCloudData", "PointCloud(*.pcd *.txt *.las)");

    CsvDataEdit->setText(fileName);

    if (fileName.isEmpty()) {
        return;
    }
}

void NewFileDialog::ShowMapData()
{
    QString fileName =
        QFileDialog::getOpenFileName(this, "Open PointCloud", "../../PointCloudData", "PointCloud(*.pcd *.txt *.las)");

    MapDataEdit->setText(fileName);

    if (fileName.isEmpty()) {
        return;
    }
}

void NewFileDialog::Cancle()
{
    NameEdit->clear();
    DataFilesEdit->clear();
    JsonDataEdit->clear();
    CsvDataEdit->clear();
    MapDataEdit->clear();

    close();
}

void NewFileDialog::Submit()
{
    NamePath = NameEdit->text();

    DataFilesPath = DataFilesEdit->text();

    JsonDataPath = JsonDataEdit->text();

    CsvDataPath = CsvDataEdit->text();

    MapDataPath = MapDataEdit->text();

    if(NamePath.isEmpty())
    {
        QMessageBox::information(nullptr, "Warring", "Please input correct project Path");
    }
    if(DataFilesPath.isEmpty())
    {
        QMessageBox::information(nullptr, "Warring", "Please input correct DataFiles Path");
    }
    if(JsonDataPath.isEmpty())
    {
        QMessageBox::information(nullptr, "Warring", "Please input correct JsonData Path");
    }
    if(CsvDataPath.isEmpty())
    {
        QMessageBox::information(nullptr, "Warring", "Please input correct CsvData Path");
    }

    if(MapDataPath.isEmpty())
    {
        QMessageBox::information(nullptr, "Warring", "Please input correct MapData Path");
    }
    else
    {
        if(!NamePath.isEmpty() && !DataFilesPath.isEmpty() && !JsonDataPath.isEmpty() && !CsvDataPath.isEmpty())
        {
            emit newfilePathSignal(NamePath,DataFilesPath,JsonDataPath,CsvDataPath,MapDataPath);

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

            // 遍历ini文件 看是否冲突
            for (int i = 0; i < size; ++i) {
                NameStr = settings.value(NameValues[i]).toString();
                DataFilesPathStr = settings.value(UrlValues[i]).toString();
                if(NameStr == NamePath && DataFilesPathStr == DataFilesPath)
                {
                    flag = "The file has exists";
                }
            }
                if (flag == "The file has exists") {
                    QMessageBox::information(nullptr, "Warring", "The file has exists");
                }

                if (flag != "The file has exists")
                {
                    // 创建.ini 文件
                    all = settings.childGroups();

                    //此处只拿用一组举例，有多个可以自行加设循环
                    settings.beginGroup(all[0]);
                    //存数据前要保存成QString形式的

                    // 取分组里的 数据组数
                    keys = settings.childKeys();

                    settings.setValue(QString::fromStdString("Url_"+std::to_string(keys.length())),DataFilesPath);

                    settings.endGroup();

                    settings.beginGroup(all[1]);
                    //存数据前要保存成QString形式的

                    settings.setValue(QString::fromStdString("Name_"+std::to_string(keys.length())),NamePath);

                    settings.endGroup();

                    // 创建项目
                    QDir dir = DataFilesPath;

                    dir.mkdir(DataFilesPath);

                    if (dir.exists())
                    {
                        // dir.mkdir(DataFilesPath);
                        std::cout <<"success" <<std::endl;
                    }

                    dir.mkpath(NamePath+"/");

                    dir.cd(NamePath+"/");

                    QString jsonDataPath = JsonDataPath;

                    QString csvDataPath = CsvDataPath;

                    QString mapDataPath = MapDataPath;

                    dir.mkpath(jsonDataPath);

                    dir.mkpath(csvDataPath);

                    dir.mkpath(mapDataPath);
                }
                close();
        }
    }
}
