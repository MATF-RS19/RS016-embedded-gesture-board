/********************************************************************************
** Form generated from reading UI file 'subwaysurf.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBWAYSURF_H
#define UI_SUBWAYSURF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SubwaySurf
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SubwaySurf)
    {
        if (SubwaySurf->objectName().isEmpty())
            SubwaySurf->setObjectName(QString::fromUtf8("SubwaySurf"));
        SubwaySurf->resize(800, 600);
        centralwidget = new QWidget(SubwaySurf);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        SubwaySurf->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SubwaySurf);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        SubwaySurf->setMenuBar(menubar);
        statusbar = new QStatusBar(SubwaySurf);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SubwaySurf->setStatusBar(statusbar);

        retranslateUi(SubwaySurf);

        QMetaObject::connectSlotsByName(SubwaySurf);
    } // setupUi

    void retranslateUi(QMainWindow *SubwaySurf)
    {
        SubwaySurf->setWindowTitle(QApplication::translate("SubwaySurf", "MainWindow", nullptr));
        label->setText(QApplication::translate("SubwaySurf", "Subway Surf", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SubwaySurf: public Ui_SubwaySurf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBWAYSURF_H
