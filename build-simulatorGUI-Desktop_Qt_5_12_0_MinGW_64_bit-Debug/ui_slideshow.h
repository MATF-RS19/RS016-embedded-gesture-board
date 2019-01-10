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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SlideShow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QLabel *image;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QPushButton *rotateLButton;
    QPushButton *rotateRButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QPushButton *exitButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SlideShow)
    {
        if (SlideShow->objectName().isEmpty())
            SlideShow->setObjectName(QString::fromUtf8("SlideShow"));
        SlideShow->resize(903, 577);
        SlideShow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        centralwidget = new QWidget(SlideShow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        image = new QLabel(widget);
        image->setObjectName(QString::fromUtf8("image"));
        image->setGeometry(QRect(200, 100, 500, 333));
        previousButton = new QPushButton(widget);
        previousButton->setObjectName(QString::fromUtf8("previousButton"));
        previousButton->setGeometry(QRect(310, 10, 51, 51));
        previousButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);\n"
"font: 75 20pt \"MS Shell Dlg 2\";"));
        nextButton = new QPushButton(widget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setGeometry(QRect(380, 10, 51, 51));
        nextButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);\n"
"font: 75 20pt \"MS Shell Dlg 2\";"));
        rotateLButton = new QPushButton(widget);
        rotateLButton->setObjectName(QString::fromUtf8("rotateLButton"));
        rotateLButton->setGeometry(QRect(100, 20, 93, 28));
        rotateLButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);"));
        rotateRButton = new QPushButton(widget);
        rotateRButton->setObjectName(QString::fromUtf8("rotateRButton"));
        rotateRButton->setGeometry(QRect(200, 20, 93, 28));
        rotateRButton->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(0, 170, 255);"));
        zoomInButton = new QPushButton(widget);
        zoomInButton->setObjectName(QString::fromUtf8("zoomInButton"));
        zoomInButton->setGeometry(QRect(520, 20, 93, 28));
        zoomInButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);"));
        zoomOutButton = new QPushButton(widget);
        zoomOutButton->setObjectName(QString::fromUtf8("zoomOutButton"));
        zoomOutButton->setGeometry(QRect(630, 20, 93, 28));
        zoomOutButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);"));
        exitButton = new QPushButton(widget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(822, 0, 61, 28));
        exitButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);"));

        verticalLayout->addWidget(widget);

        SlideShow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SlideShow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 903, 26));
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
        image->setText(QApplication::translate("SlideShow", "TextLabel", nullptr));
        previousButton->setText(QApplication::translate("SlideShow", "<", nullptr));
        nextButton->setText(QApplication::translate("SlideShow", ">", nullptr));
        rotateLButton->setText(QApplication::translate("SlideShow", "Rotate left", nullptr));
        rotateRButton->setText(QApplication::translate("SlideShow", "Rotate Right", nullptr));
        zoomInButton->setText(QApplication::translate("SlideShow", "Zoom in", nullptr));
        zoomOutButton->setText(QApplication::translate("SlideShow", "Zoom out", nullptr));
        exitButton->setText(QApplication::translate("SlideShow", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SlideShow: public Ui_SlideShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDESHOW_H
