//
// Created by zhihui on 6/20/19.
//

#ifndef DEMO_TWO_OPENFILEDIALOG_H
#define DEMO_TWO_OPENFILEDIALOG_H

#include <QDialog>

class QPushButton;

class QComboBox;


class OpenFileDialog : public QDialog{
    Q_OBJECT
public:
    explicit OpenFileDialog(QWidget *parent= nullptr);

    ~OpenFileDialog() override = default; // default 调用系统默认的析构函数
    /*
     * 同时应该在构造函数中加入这句话  setAttribute(Qt::WA_DeleteOnClose);    // 设置该类的对象 进行析构
     */

    Q_DISABLE_COPY(OpenFileDialog); // 禁止类的拷贝

protected:
    void closeEvent(QCloseEvent *e) override ;

    Q_SIGNALS:
    void openFileInfoSignal(QString &, bool, bool);

private Q_SLOTS:

    void confirm();

private:
    void cleanup();

private:

    // 提交按钮
    QPushButton *pbConfirm;

    // 3个下拉框
    QComboBox *fileExtensionComboBox;
    QComboBox *intensityComboBox;
    QComboBox *RGBComboBox;


private:
    // 保存用户选择的文件信息
    QString fileExtension;
    bool hasIntensity;
    bool hasRGB;
};
#endif //DEMO_TWO_OPENFILEDIALOG_H
