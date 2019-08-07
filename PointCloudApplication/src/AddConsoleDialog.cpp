//
// Created by zhihui on 7/15/19.
//
//#include <include/AddConsoleDialog.h>
//#include <QDockWidget>
//
//AddConsoleDialog::AddConsoleDialog(QWidget *parent):QWidget(parent)
//{
//    createDockWindows();
//}
//
//void AddConsoleDialog::createDockWindows()
//{
//    QDockWidget *dock = new QDockWidget(tr("Console"), this);
//    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
//    customerList = new QListWidget(dock);
//    customerList->addItems(QStringList()
//                               << NamePath + DataFilesPath
//                              );
//    dock->setWidget(customerList);
//    // addDockWidget(Qt::RightDockWidgetArea, dock);
//
//}
//
//void AddConsoleDialog::showConsoleSlot(const QString &namePath, const QString &dataFilePath)
//{
//    this->NamePath = namePath;
//    this->DataFilesPath = dataFilePath;
//}