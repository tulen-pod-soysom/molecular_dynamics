/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QCustomPlot *widget;
    QCustomPlot *widget_2;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *Label;
    QDoubleSpinBox *DoubleSpinBox;
    QLabel *Label_2;
    QDoubleSpinBox *DoubleSpinBox_2;
    QSpacerItem *verticalSpacer;
    QLabel *Label_3;
    QSpinBox *SpinBox_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QCustomPlot *widget_3;
    QCustomPlot *widget_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(830, 617);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QCustomPlot(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 411, 411));
        widget_2 = new QCustomPlot(centralwidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(430, 10, 391, 131));
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 430, 411, 141));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        Label = new QLabel(formLayoutWidget);
        Label->setObjectName(QString::fromUtf8("Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, Label);

        DoubleSpinBox = new QDoubleSpinBox(formLayoutWidget);
        DoubleSpinBox->setObjectName(QString::fromUtf8("DoubleSpinBox"));
        DoubleSpinBox->setMinimum(0.800000000000000);
        DoubleSpinBox->setMaximum(1.700000000000000);
        DoubleSpinBox->setSingleStep(0.010000000000000);
        DoubleSpinBox->setValue(0.900000000000000);

        formLayout->setWidget(0, QFormLayout::FieldRole, DoubleSpinBox);

        Label_2 = new QLabel(formLayoutWidget);
        Label_2->setObjectName(QString::fromUtf8("Label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Label_2);

        DoubleSpinBox_2 = new QDoubleSpinBox(formLayoutWidget);
        DoubleSpinBox_2->setObjectName(QString::fromUtf8("DoubleSpinBox_2"));
        DoubleSpinBox_2->setDecimals(3);
        DoubleSpinBox_2->setMaximum(10.000000000000000);
        DoubleSpinBox_2->setSingleStep(0.001000000000000);
        DoubleSpinBox_2->setValue(0.010000000000000);

        formLayout->setWidget(1, QFormLayout::FieldRole, DoubleSpinBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        formLayout->setItem(2, QFormLayout::FieldRole, verticalSpacer);

        Label_3 = new QLabel(formLayoutWidget);
        Label_3->setObjectName(QString::fromUtf8("Label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, Label_3);

        SpinBox_3 = new QSpinBox(formLayoutWidget);
        SpinBox_3->setObjectName(QString::fromUtf8("SpinBox_3"));
        SpinBox_3->setMinimum(1);
        SpinBox_3->setMaximum(10000);
        SpinBox_3->setSingleStep(10);
        SpinBox_3->setValue(100);

        formLayout->setWidget(3, QFormLayout::FieldRole, SpinBox_3);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(430, 430, 351, 41));
        pushButton->setCheckable(true);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(false);
        pushButton_2->setGeometry(QRect(430, 480, 171, 41));
        pushButton_2->setFlat(false);
        widget_3 = new QCustomPlot(centralwidget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(430, 150, 391, 131));
        widget_4 = new QCustomPlot(centralwidget);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(430, 290, 391, 131));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 830, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        pushButton_2->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        Label->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\270\320\276\320\264 \321\200\320\265\321\210\320\265\321\202\320\272\320\270", nullptr));
        DoubleSpinBox->setSuffix(QApplication::translate("MainWindow", " \320\276\321\202 \321\200\320\260\320\262\320\275\320\276\320\262\320\265\321\201\320\275\320\276\320\263\320\276 \321\200\320\260\321\201\321\201\321\202\320\276\321\217\320\275\320\270\321\217", nullptr));
        Label_2->setText(QApplication::translate("MainWindow", "\320\250\320\260\320\263 \320\277\320\276 \320\262\321\200\320\265\320\274\320\265\320\275\320\270", nullptr));
        DoubleSpinBox_2->setPrefix(QString());
        DoubleSpinBox_2->setSuffix(QApplication::translate("MainWindow", " \320\276\321\202 \321\205\320\260\321\200\320\260\320\272\321\202\320\265\321\200\320\275\320\276\320\263\320\276 \320\262\321\200\320\265\320\274\320\265\320\275\320\270", nullptr));
        Label_3->setText(QApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \321\201\320\270\320\274\321\203\320\273\321\217\321\206\320\270\320\270", nullptr));
        SpinBox_3->setSuffix(QApplication::translate("MainWindow", " \321\210\320\260\320\263\320\276\320\262 \320\262 \321\201\320\265\320\272\321\203\320\275\320\264\321\203", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\270\320\276\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
