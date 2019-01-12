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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SlideShow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QPushButton *previousButton;
    QPushButton *nextButton;
    QPushButton *rotateLButton;
    QPushButton *rotateRButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QPushButton *exitButton;
    QLabel *image;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QMainWindow *SlideShow)
    {
        if (SlideShow->objectName().isEmpty())
            SlideShow->setObjectName(QString::fromUtf8("SlideShow"));
        SlideShow->resize(1366, 768);
        SlideShow->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        centralwidget = new QWidget(SlideShow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 1366, 768));
        previousButton = new QPushButton(widget);
        previousButton->setObjectName(QString::fromUtf8("previousButton"));
        previousButton->setGeometry(QRect(630, 10, 51, 51));
        previousButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);\n"
"font: 75 20pt \"MS Shell Dlg 2\";"));
        previousButton->setAutoDefault(true);
        nextButton = new QPushButton(widget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setGeometry(QRect(700, 10, 51, 51));
        nextButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);\n"
"font: 75 20pt \"MS Shell Dlg 2\";"));
        nextButton->setAutoDefault(true);
        rotateLButton = new QPushButton(widget);
        rotateLButton->setObjectName(QString::fromUtf8("rotateLButton"));
        rotateLButton->setGeometry(QRect(250, 10, 131, 41));
        rotateLButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);\n"
"font: 9pt \"MS Shell Dlg 2\";"));
        rotateLButton->setAutoDefault(true);
        rotateRButton = new QPushButton(widget);
        rotateRButton->setObjectName(QString::fromUtf8("rotateRButton"));
        rotateRButton->setGeometry(QRect(380, 10, 141, 41));
        rotateRButton->setStyleSheet(QString::fromUtf8("font: 9pt \"MS Shell Dlg 2\";\n"
"color: rgb(0, 170, 255);"));
        rotateRButton->setAutoDefault(true);
        zoomInButton = new QPushButton(widget);
        zoomInButton->setObjectName(QString::fromUtf8("zoomInButton"));
        zoomInButton->setGeometry(QRect(830, 20, 151, 28));
        zoomInButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);\n"
"font: 9pt \"MS Shell Dlg 2\";"));
        zoomInButton->setAutoDefault(true);
        zoomOutButton = new QPushButton(widget);
        zoomOutButton->setObjectName(QString::fromUtf8("zoomOutButton"));
        zoomOutButton->setGeometry(QRect(1000, 20, 161, 28));
        zoomOutButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);\n"
"font: 9pt \"MS Shell Dlg 2\";"));
        zoomOutButton->setAutoDefault(true);
        exitButton = new QPushButton(widget);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(1250, 710, 93, 37));
        exitButton->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);\n"
"font: 14pt \"MS Shell Dlg 2\";"));
        exitButton->setAutoDefault(true);
        image = new QLabel(widget);
        image->setObjectName(QString::fromUtf8("image"));
        image->setGeometry(QRect(390, 220, 641, 431));
        image->setStyleSheet(QString::fromUtf8("border-color: rgb(0, 170, 255);\n"
"border-top-color: rgb(0, 170, 255);\n"
"border-left-color: rgb(0, 170, 255);\n"
"border-right-color: rgb(0, 170, 255);\n"
"border-bottom-color: rgb(0, 170, 255);"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(720, 60, 101, 21));
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);\n"
"font: 9pt \"MS Shell Dlg 2\";"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(610, 60, 81, 20));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 255);\n"
"font: 9pt \"MS Shell Dlg 2\";"));
        SlideShow->setCentralWidget(centralwidget);

        retranslateUi(SlideShow);

        QMetaObject::connectSlotsByName(SlideShow);
    } // setupUi

    void retranslateUi(QMainWindow *SlideShow)
    {
        SlideShow->setWindowTitle(QApplication::translate("SlideShow", "MainWindow", nullptr));
        previousButton->setText(QApplication::translate("SlideShow", "<", nullptr));
        nextButton->setText(QApplication::translate("SlideShow", ">", nullptr));
        rotateLButton->setText(QApplication::translate("SlideShow", "Rotate left", nullptr));
        rotateRButton->setText(QApplication::translate("SlideShow", "Rotate Right", nullptr));
        zoomInButton->setText(QApplication::translate("SlideShow", "Flick down to zoom in", nullptr));
        zoomOutButton->setText(QApplication::translate("SlideShow", "Flick up to zoom out", nullptr));
        exitButton->setText(QApplication::translate("SlideShow", "Exit", nullptr));
        image->setText(QApplication::translate("SlideShow", "TextLabel", nullptr));
        label->setText(QApplication::translate("SlideShow", "Swipe right", nullptr));
        label_2->setText(QApplication::translate("SlideShow", "Swipe left", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SlideShow: public Ui_SlideShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDESHOW_H
