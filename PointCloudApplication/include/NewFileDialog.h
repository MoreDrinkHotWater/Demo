//
// Created by zhihui on 7/5/19.
//

#ifndef DEMO_TWO_POINTCLOUDAPPLICATION_INCLUDE_NEWFILEDIALOG_H_
#define DEMO_TWO_POINTCLOUDAPPLICATION_INCLUDE_NEWFILEDIALOG_H_

#include <QDialog>
#include <QLineEdit>
#include <QDebug>

class QPushButton;

class NewFileDialog : public QDialog {

    Q_OBJECT

    public:

    explicit NewFileDialog(QWidget *parent = nullptr);
    ~NewFileDialog() override = default;

    private Q_SLOTS:

    void Cancle();

    void Submit();

    void ShowName();

    void ShowDataFiles();

    void ShowJsonData();

    void ShowCsvData();

    void ShowMapData();

//    protected:
//    void closeEvent(QCloseEvent *e) override;

   Q_SIGNALS:
    void newfilePathSignal(QString &, QString &, QString &, QString &, QString &);

    private:
    QString NamePath;

    QString DataFilesPath;

    QString JsonDataPath;

    QString CsvDataPath;

    QString MapDataPath;

    private:

    QLineEdit *NameEdit;
    QPushButton *NameButton;

    QLineEdit *DataFilesEdit;
    QPushButton *DataFilesButton;

    QLineEdit *JsonDataEdit;
    QPushButton *JsonDataButton;

    QLineEdit *CsvDataEdit;
    QPushButton *CsvDataButton;

    QLineEdit *MapDataEdit;
    QPushButton *MapDataButton;

    QPushButton *SubmitButton;

    QPushButton *CancleButton;

};

#endif //DEMO_TWO_POINTCLOUDAPPLICATION_INCLUDE_NEWFILEDIALOG_H_
