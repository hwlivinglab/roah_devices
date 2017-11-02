/********************************************************************************
** Form generated from reading UI file 'devices_control.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICES_CONTROL_H
#define UI_DEVICES_CONTROL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DevicesControl
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *bell_warn;
    QLabel *label_2;
    QLabel *bell_time;
    QPushButton *bell_ring;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *switch_2;
    QLabel *switch_3;
    QLabel *label_4;
    QLabel *label_3;
    QLabel *switch_1;
    QPushButton *switch_1_toggle;
    QPushButton *switch_2_toggle;
    QPushButton *switch_3_toggle;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *dimmer;
    QSlider *dimmer_in;
    QGroupBox *groupBox_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *blinds;
    QSlider *blinds_in;

    void setupUi(QWidget *DevicesControl)
    {
        if (DevicesControl->objectName().isEmpty())
            DevicesControl->setObjectName(QString::fromUtf8("DevicesControl"));
        DevicesControl->resize(600, 400);
        verticalLayout = new QVBoxLayout(DevicesControl);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(DevicesControl);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        bell_warn = new QLabel(groupBox);
        bell_warn->setObjectName(QString::fromUtf8("bell_warn"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(bell_warn->sizePolicy().hasHeightForWidth());
        bell_warn->setSizePolicy(sizePolicy);
        bell_warn->setMinimumSize(QSize(32, 32));
        bell_warn->setMaximumSize(QSize(32, 32));
        bell_warn->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(bell_warn);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_2);

        bell_time = new QLabel(groupBox);
        bell_time->setObjectName(QString::fromUtf8("bell_time"));

        horizontalLayout->addWidget(bell_time);

        bell_ring = new QPushButton(groupBox);
        bell_ring->setObjectName(QString::fromUtf8("bell_ring"));

        horizontalLayout->addWidget(bell_ring);

        horizontalLayout->setStretch(2, 1);

        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(DevicesControl);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        switch_2 = new QLabel(groupBox_2);
        switch_2->setObjectName(QString::fromUtf8("switch_2"));

        gridLayout->addWidget(switch_2, 1, 1, 1, 1);

        switch_3 = new QLabel(groupBox_2);
        switch_3->setObjectName(QString::fromUtf8("switch_3"));

        gridLayout->addWidget(switch_3, 2, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        switch_1 = new QLabel(groupBox_2);
        switch_1->setObjectName(QString::fromUtf8("switch_1"));

        gridLayout->addWidget(switch_1, 0, 1, 1, 1);

        switch_1_toggle = new QPushButton(groupBox_2);
        switch_1_toggle->setObjectName(QString::fromUtf8("switch_1_toggle"));

        gridLayout->addWidget(switch_1_toggle, 0, 2, 1, 1);

        switch_2_toggle = new QPushButton(groupBox_2);
        switch_2_toggle->setObjectName(QString::fromUtf8("switch_2_toggle"));

        gridLayout->addWidget(switch_2_toggle, 1, 2, 1, 1);

        switch_3_toggle = new QPushButton(groupBox_2);
        switch_3_toggle->setObjectName(QString::fromUtf8("switch_3_toggle"));

        gridLayout->addWidget(switch_3_toggle, 2, 2, 1, 1);

        gridLayout->setColumnStretch(1, 1);

        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(DevicesControl);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_3);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        dimmer = new QLabel(groupBox_3);
        dimmer->setObjectName(QString::fromUtf8("dimmer"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dimmer->sizePolicy().hasHeightForWidth());
        dimmer->setSizePolicy(sizePolicy1);
        dimmer->setMinimumSize(QSize(50, 0));
        dimmer->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(dimmer);

        dimmer_in = new QSlider(groupBox_3);
        dimmer_in->setObjectName(QString::fromUtf8("dimmer_in"));
        dimmer_in->setMaximum(100);
        dimmer_in->setValue(0);
        dimmer_in->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(dimmer_in);


        verticalLayout->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(DevicesControl);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_4);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        blinds = new QLabel(groupBox_4);
        blinds->setObjectName(QString::fromUtf8("blinds"));
        sizePolicy1.setHeightForWidth(blinds->sizePolicy().hasHeightForWidth());
        blinds->setSizePolicy(sizePolicy1);
        blinds->setMinimumSize(QSize(50, 0));
        blinds->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(blinds);

        blinds_in = new QSlider(groupBox_4);
        blinds_in->setObjectName(QString::fromUtf8("blinds_in"));
        blinds_in->setMaximum(100);
        blinds_in->setValue(0);
        blinds_in->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(blinds_in);


        verticalLayout->addWidget(groupBox_4);


        retranslateUi(DevicesControl);

        QMetaObject::connectSlotsByName(DevicesControl);
    } // setupUi

    void retranslateUi(QWidget *DevicesControl)
    {
        DevicesControl->setWindowTitle(QApplication::translate("DevicesControl", "Devices Control", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DevicesControl", "Bell", 0, QApplication::UnicodeUTF8));
        bell_warn->setText(QString());
        label_2->setText(QApplication::translate("DevicesControl", "Last Ring: ", 0, QApplication::UnicodeUTF8));
        bell_time->setText(QApplication::translate("DevicesControl", "--", 0, QApplication::UnicodeUTF8));
        bell_ring->setText(QApplication::translate("DevicesControl", "Ring", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("DevicesControl", "Switches", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DevicesControl", "Switch 1: ", 0, QApplication::UnicodeUTF8));
        switch_2->setText(QApplication::translate("DevicesControl", "--", 0, QApplication::UnicodeUTF8));
        switch_3->setText(QApplication::translate("DevicesControl", "--", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("DevicesControl", "Switch 3: ", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DevicesControl", "Switch 2: ", 0, QApplication::UnicodeUTF8));
        switch_1->setText(QApplication::translate("DevicesControl", "--", 0, QApplication::UnicodeUTF8));
        switch_1_toggle->setText(QApplication::translate("DevicesControl", "Toggle", 0, QApplication::UnicodeUTF8));
        switch_2_toggle->setText(QApplication::translate("DevicesControl", "Toggle", 0, QApplication::UnicodeUTF8));
        switch_3_toggle->setText(QApplication::translate("DevicesControl", "Toggle", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("DevicesControl", "Dimmer", 0, QApplication::UnicodeUTF8));
        dimmer->setText(QApplication::translate("DevicesControl", "-- %", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("DevicesControl", "Blinds", 0, QApplication::UnicodeUTF8));
        blinds->setText(QApplication::translate("DevicesControl", "-- %", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DevicesControl: public Ui_DevicesControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICES_CONTROL_H
