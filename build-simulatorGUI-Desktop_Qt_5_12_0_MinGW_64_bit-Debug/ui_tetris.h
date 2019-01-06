/********************************************************************************
** Form generated from reading UI file 'tetris.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TETRIS_H
#define UI_TETRIS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tetris
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Tetris)
    {
        if (Tetris->objectName().isEmpty())
            Tetris->setObjectName(QString::fromUtf8("Tetris"));
        Tetris->resize(621, 438);
        centralwidget = new QWidget(Tetris);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        Tetris->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Tetris);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 621, 21));
        Tetris->setMenuBar(menubar);
        statusbar = new QStatusBar(Tetris);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Tetris->setStatusBar(statusbar);

        retranslateUi(Tetris);

        QMetaObject::connectSlotsByName(Tetris);
    } // setupUi

    void retranslateUi(QMainWindow *Tetris)
    {
        Tetris->setWindowTitle(QApplication::translate("Tetris", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("Tetris", "TETRIS", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tetris: public Ui_Tetris {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TETRIS_H
