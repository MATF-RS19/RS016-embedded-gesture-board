/********************************************************************************
** Form generated from reading UI file 'spaceglider.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPACEGLIDER_H
#define UI_SPACEGLIDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpaceGlider
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_exit;
    QPushButton *pushButton_start;
    QPushButton *pushButton_pause;
    QFrame *frejm;
    QLabel *label_glider;

    void setupUi(QMainWindow *SpaceGlider)
    {
        if (SpaceGlider->objectName().isEmpty())
            SpaceGlider->setObjectName(QString::fromUtf8("SpaceGlider"));
        SpaceGlider->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SpaceGlider->sizePolicy().hasHeightForWidth());
        SpaceGlider->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(SpaceGlider);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_exit = new QPushButton(centralwidget);
        pushButton_exit->setObjectName(QString::fromUtf8("pushButton_exit"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_exit->sizePolicy().hasHeightForWidth());
        pushButton_exit->setSizePolicy(sizePolicy1);
        pushButton_exit->setAutoDefault(true);
        pushButton_exit->setFlat(true);

        gridLayout->addWidget(pushButton_exit, 2, 2, 1, 1);

        pushButton_start = new QPushButton(centralwidget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));
        sizePolicy1.setHeightForWidth(pushButton_start->sizePolicy().hasHeightForWidth());
        pushButton_start->setSizePolicy(sizePolicy1);
        pushButton_start->setAutoDefault(true);
        pushButton_start->setFlat(true);

        gridLayout->addWidget(pushButton_start, 0, 2, 1, 1, Qt::AlignRight|Qt::AlignBottom);

        pushButton_pause = new QPushButton(centralwidget);
        pushButton_pause->setObjectName(QString::fromUtf8("pushButton_pause"));
        sizePolicy1.setHeightForWidth(pushButton_pause->sizePolicy().hasHeightForWidth());
        pushButton_pause->setSizePolicy(sizePolicy1);
        pushButton_pause->setAutoDefault(true);
        pushButton_pause->setFlat(true);

        gridLayout->addWidget(pushButton_pause, 1, 2, 1, 1);

        frejm = new QFrame(centralwidget);
        frejm->setObjectName(QString::fromUtf8("frejm"));
        sizePolicy.setHeightForWidth(frejm->sizePolicy().hasHeightForWidth());
        frejm->setSizePolicy(sizePolicy);
        frejm->setFrameShape(QFrame::StyledPanel);
        frejm->setFrameShadow(QFrame::Raised);
        label_glider = new QLabel(frejm);
        label_glider->setObjectName(QString::fromUtf8("label_glider"));
        label_glider->setGeometry(QRect(2000, 2000, 50, 50));
        label_glider->setPixmap(QPixmap(QString::fromUtf8(":/resource/img/raketa.png")));
        label_glider->setScaledContents(true);

        gridLayout->addWidget(frejm, 0, 0, 3, 1);

        SpaceGlider->setCentralWidget(centralwidget);

        retranslateUi(SpaceGlider);

        QMetaObject::connectSlotsByName(SpaceGlider);
    } // setupUi

    void retranslateUi(QMainWindow *SpaceGlider)
    {
        SpaceGlider->setWindowTitle(QApplication::translate("SpaceGlider", "MainWindow", nullptr));
        pushButton_exit->setText(QApplication::translate("SpaceGlider", "Quit", nullptr));
        pushButton_start->setText(QApplication::translate("SpaceGlider", "Start", nullptr));
        pushButton_pause->setText(QApplication::translate("SpaceGlider", "Stop/Resume", nullptr));
        label_glider->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SpaceGlider: public Ui_SpaceGlider {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPACEGLIDER_H
