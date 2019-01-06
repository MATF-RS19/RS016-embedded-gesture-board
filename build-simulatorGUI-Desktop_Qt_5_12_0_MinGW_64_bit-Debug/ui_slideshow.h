/********************************************************************************
** Form generated from reading UI file 'slideshow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDESHOW_H
#define UI_SLIDESHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SlideShow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SlideShow)
    {
        if (SlideShow->objectName().isEmpty())
            SlideShow->setObjectName(QString::fromUtf8("SlideShow"));
        SlideShow->resize(421, 419);
        centralwidget = new QWidget(SlideShow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        SlideShow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SlideShow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 421, 21));
        SlideShow->setMenuBar(menubar);
        statusbar = new QStatusBar(SlideShow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SlideShow->setStatusBar(statusbar);

        retranslateUi(SlideShow);

        QMetaObject::connectSlotsByName(SlideShow);
    } // setupUi

    void retranslateUi(QMainWindow *SlideShow)
    {
        SlideShow->setWindowTitle(QApplication::translate("SlideShow", "MainWindow", nullptr));
        label->setText(QApplication::translate("SlideShow", "SlideShow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SlideShow: public Ui_SlideShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDESHOW_H
