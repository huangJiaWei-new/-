/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *video;
    QPushButton *open;
    QComboBox *comboBox;
    QLabel *label;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(959, 643);
        video = new QLabel(Widget);
        video->setObjectName(QString::fromUtf8("video"));
        video->setGeometry(QRect(10, 10, 551, 371));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        video->setFont(font);
        video->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        open = new QPushButton(Widget);
        open->setObjectName(QString::fromUtf8("open"));
        open->setGeometry(QRect(670, 230, 171, 61));
        comboBox = new QComboBox(Widget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(670, 140, 171, 51));
        comboBox->setFont(font);
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(580, 140, 91, 16));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        video->setText(QString());
        open->setText(QCoreApplication::translate("Widget", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\346\221\204\345\203\217\345\244\264\350\256\276\345\244\207\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
