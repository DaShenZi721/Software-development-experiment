/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPlainTextEdit *FileChooseText;
    QPushButton *FileChooseBtn;
    QLabel *label_2;
    QPlainTextEdit *CompressPosText;
    QPushButton *CompressPosBtn;
    QPushButton *StartCompressBtn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(724, 545);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 50, 72, 15));
        FileChooseText = new QPlainTextEdit(centralWidget);
        FileChooseText->setObjectName(QStringLiteral("FileChooseText"));
        FileChooseText->setGeometry(QRect(130, 40, 461, 31));
        FileChooseBtn = new QPushButton(centralWidget);
        FileChooseBtn->setObjectName(QStringLiteral("FileChooseBtn"));
        FileChooseBtn->setGeometry(QRect(630, 40, 51, 28));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 120, 72, 15));
        CompressPosText = new QPlainTextEdit(centralWidget);
        CompressPosText->setObjectName(QStringLiteral("CompressPosText"));
        CompressPosText->setGeometry(QRect(130, 110, 461, 31));
        CompressPosBtn = new QPushButton(centralWidget);
        CompressPosBtn->setObjectName(QStringLiteral("CompressPosBtn"));
        CompressPosBtn->setGeometry(QRect(630, 110, 51, 28));
        StartCompressBtn = new QPushButton(centralWidget);
        StartCompressBtn->setObjectName(QStringLiteral("StartCompressBtn"));
        StartCompressBtn->setGeometry(QRect(260, 210, 93, 28));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 724, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        FileChooseBtn->setText(QApplication::translate("MainWindow", "...", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\350\247\243\345\216\213\350\207\263", nullptr));
        CompressPosBtn->setText(QApplication::translate("MainWindow", "...", nullptr));
        StartCompressBtn->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\350\247\243\345\216\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
