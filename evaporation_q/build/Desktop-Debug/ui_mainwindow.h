/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.14
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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QCustomPlot *widget_2;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *Label;
    QDoubleSpinBox *DoubleSpinBox;
    QLabel *Label_2;
    QDoubleSpinBox *DoubleSpinBox_2;
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
        widget = new QWidget(centralwidget);
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

        formLayout->setWidget(0, QFormLayout::FieldRole, DoubleSpinBox);

        Label_2 = new QLabel(formLayoutWidget);
        Label_2->setObjectName(QString::fromUtf8("Label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Label_2);

        DoubleSpinBox_2 = new QDoubleSpinBox(formLayoutWidget);
        DoubleSpinBox_2->setObjectName(QString::fromUtf8("DoubleSpinBox_2"));

        formLayout->setWidget(1, QFormLayout::FieldRole, DoubleSpinBox_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(430, 430, 351, 41));
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
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Label->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\270\320\276\320\264 \321\200\320\265\321\210\320\265\321\202\320\272\320\270", nullptr));
        Label_2->setText(QCoreApplication::translate("MainWindow", "\320\250\320\260\320\263 \320\277\320\276 \320\262\321\200\320\265\320\274\320\265\320\275\320\270", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\276\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
