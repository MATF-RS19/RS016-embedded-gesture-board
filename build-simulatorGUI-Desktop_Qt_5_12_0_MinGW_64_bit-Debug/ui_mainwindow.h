/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonSlideShow;
    QPushButton *pushButtonSubwaySurf;
    QPushButton *pushButtonExit;
    QPushButton *pushButtonTetris;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(633, 384);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonSlideShow = new QPushButton(centralWidget);
        pushButtonSlideShow->setObjectName(QString::fromUtf8("pushButtonSlideShow"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButtonSlideShow->sizePolicy().hasHeightForWidth());
        pushButtonSlideShow->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButtonSlideShow->setFont(font);

        gridLayout->addWidget(pushButtonSlideShow, 3, 0, 1, 1);

        pushButtonSubwaySurf = new QPushButton(centralWidget);
        pushButtonSubwaySurf->setObjectName(QString::fromUtf8("pushButtonSubwaySurf"));
        sizePolicy1.setHeightForWidth(pushButtonSubwaySurf->sizePolicy().hasHeightForWidth());
        pushButtonSubwaySurf->setSizePolicy(sizePolicy1);
        pushButtonSubwaySurf->setFont(font);
        pushButtonSubwaySurf->setAutoFillBackground(false);
        pushButtonSubwaySurf->setAutoDefault(false);
        pushButtonSubwaySurf->setFlat(false);

        gridLayout->addWidget(pushButtonSubwaySurf, 2, 0, 1, 1);

        pushButtonExit = new QPushButton(centralWidget);
        pushButtonExit->setObjectName(QString::fromUtf8("pushButtonExit"));

        gridLayout->addWidget(pushButtonExit, 7, 0, 1, 1, Qt::AlignRight|Qt::AlignBottom);

        pushButtonTetris = new QPushButton(centralWidget);
        pushButtonTetris->setObjectName(QString::fromUtf8("pushButtonTetris"));
        pushButtonTetris->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButtonTetris->sizePolicy().hasHeightForWidth());
        pushButtonTetris->setSizePolicy(sizePolicy2);
        pushButtonTetris->setFont(font);
        pushButtonTetris->setMouseTracking(false);

        gridLayout->addWidget(pushButtonTetris, 5, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Gesture Board", nullptr));
        pushButtonSlideShow->setText(QApplication::translate("MainWindow", "SlideShow", nullptr));
        pushButtonSubwaySurf->setText(QApplication::translate("MainWindow", "SubwaySurf", nullptr));
        pushButtonExit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        pushButtonTetris->setText(QApplication::translate("MainWindow", "Tetris", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
