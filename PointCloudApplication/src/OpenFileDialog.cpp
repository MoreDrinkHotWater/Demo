//
// Created by zhihui on 6/20/19.
//

#include <include/OpenFileDialog.h>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QCloseEvent>

OpenFileDialog::OpenFileDialog(QWidget *parent) : QDialog(parent) ,fileExtension(), hasIntensity(false), hasRGB(false)
{
    setWindowTitle("OpenFileDialog");
    setFixedSize(240,200);

    // 设置该类的对象 进行析构
    setAttribute(Qt::WA_DeleteOnClose);

    pbConfirm = new QPushButton(this);
    pbConfirm->setText("Confirm");
    pbConfirm->setGeometry(QRect(160, 160, 61, 25));

    connect(pbConfirm, &QPushButton::clicked, this, &OpenFileDialog::confirm);

    auto *widget = new QWidget(this);
    widget->setGeometry(QRect(20, 20, 201, 131));

    auto *verticalLayout = new QVBoxLayout(widget);
    verticalLayout->setSpacing(6);
    verticalLayout->setContentsMargins(11, 11, 11, 11);
    verticalLayout->setContentsMargins(0, 0, 0, 0);

    /*
     * 文件
     * auto *horizontalLayout = new QHBoxLayout();
       horizontalLayout->setSpacing(6);

       auto *lFileExtension = new QLabel(widget);
       lFileExtension->setText("FileExtension");
       horizontalLayout->addWidget(lFileExtension);
     */

    auto *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setSpacing(6);

    auto *lFileExtension = new QLabel(widget);
    lFileExtension->setText("FileExtension");

    horizontalLayout->addWidget(lFileExtension);

    /*
     * 文件下拉框
     *  auto *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        horizontalLayout->addItem(horizontalSpacer);

        fileExtensionComboBox = new QComboBox(widget);
        fileExtensionComboBox->addItems({"txt", "pcd", "las"});
        fileExtensionComboBox->setCurrentIndex(-1);

        horizontalLayout->addWidget(fileExtensionComboBox);

        verticalLayout->addLayout(horizontalLayout);
     */

    auto *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer);

    fileExtensionComboBox = new QComboBox(widget);
    fileExtensionComboBox->addItems({"txt", "pcd", "las"});
    fileExtensionComboBox->setCurrentIndex(-1);

    horizontalLayout->addWidget(fileExtensionComboBox);

    verticalLayout->addLayout(horizontalLayout);

    /*
     * Intensity 强度
     */

    auto *horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setSpacing(6);

    auto *lIntensity = new QLabel(widget);
    lIntensity->setText("Intensity");

    horizontalLayout_2->addWidget(lIntensity);

    auto *horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer_2);

    intensityComboBox = new QComboBox(widget);
    intensityComboBox->addItems({"on", "off"});
    intensityComboBox->setCurrentIndex(-1);

    horizontalLayout_2->addWidget(intensityComboBox);

    verticalLayout->addLayout(horizontalLayout_2);

    /*
     * RGB
     */

    auto *horizontalLayout_3 = new QHBoxLayout();
    horizontalLayout_3->setSpacing(6);

    auto *lRGB = new QLabel(widget);
    lRGB->setText("RGB");

    horizontalLayout_3->addWidget(lRGB);

    auto *horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_3->addItem(horizontalSpacer_3);

    RGBComboBox = new QComboBox(widget);
    RGBComboBox->addItems({"on", "off"});
    RGBComboBox->setCurrentIndex(-1);

    horizontalLayout_3->addWidget(RGBComboBox);

    verticalLayout->addLayout(horizontalLayout_3);
}

void OpenFileDialog::confirm()
{
    fileExtension = fileExtensionComboBox->currentText();

    if (fileExtension.isEmpty()) {
        cleanup();
        return;
    }

    if (intensityComboBox->currentText() == "on") {
        hasIntensity = true;
    } else if (intensityComboBox->currentText() == "off") {
        hasIntensity = false;
    } else {
        cleanup();
        return;
    }

    if (RGBComboBox->currentText() == "on") {
        hasRGB = true;
    } else if (RGBComboBox->currentText() == "off") {
        hasRGB = false;
    } else {
        cleanup();
        return;
    }

    emit openFileInfoSignal(fileExtension, hasIntensity, hasRGB);

    close();
}

void OpenFileDialog::cleanup()
{
    fileExtensionComboBox ->setCurrentIndex(-1);
    intensityComboBox ->setCurrentIndex(-1);
    RGBComboBox ->setCurrentIndex(-1);

    fileExtension.clear();
    hasIntensity = false;
    hasRGB = false;
}

void OpenFileDialog::closeEvent(QCloseEvent *e)
{
    if(!fileExtension.isEmpty())
    {
        e->accept();
    }
    else
    {
        e->ignore();
    }
}