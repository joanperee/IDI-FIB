/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QHBoxLayout *horizontalLayout;
    MyGLWidget *widget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_2;
    QFrame *line;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;
    QDoubleSpinBox *doubleSpinBox_2;
    QDoubleSpinBox *doubleSpinBox_3;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(933, 726);
        horizontalLayout = new QHBoxLayout(MyForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new MyGLWidget(MyForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(50, 50));

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_2 = new QLabel(MyForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        radioButton = new QRadioButton(MyForm);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setChecked(true);

        verticalLayout->addWidget(radioButton);

        radioButton_3 = new QRadioButton(MyForm);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout->addWidget(radioButton_3);

        radioButton_2 = new QRadioButton(MyForm);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        line = new QFrame(MyForm);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        label = new QLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        doubleSpinBox = new QDoubleSpinBox(MyForm);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setMaximum(1.000000000000000);
        doubleSpinBox->setSingleStep(0.100000000000000);
        doubleSpinBox->setValue(1.000000000000000);

        verticalLayout->addWidget(doubleSpinBox);

        doubleSpinBox_2 = new QDoubleSpinBox(MyForm);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));
        doubleSpinBox_2->setMaximum(1.000000000000000);
        doubleSpinBox_2->setSingleStep(0.100000000000000);
        doubleSpinBox_2->setValue(1.000000000000000);

        verticalLayout->addWidget(doubleSpinBox_2);

        doubleSpinBox_3 = new QDoubleSpinBox(MyForm);
        doubleSpinBox_3->setObjectName(QString::fromUtf8("doubleSpinBox_3"));
        doubleSpinBox_3->setMaximum(1.000000000000000);
        doubleSpinBox_3->setSingleStep(0.100000000000000);
        doubleSpinBox_3->setValue(1.000000000000000);

        verticalLayout->addWidget(doubleSpinBox_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(MyForm);
        QObject::connect(pushButton, SIGNAL(clicked()), MyForm, SLOT(close()));
        QObject::connect(widget, SIGNAL(signal2x1()), radioButton, SLOT(click()));
        QObject::connect(widget, SIGNAL(signal2x2()), radioButton_3, SLOT(click()));
        QObject::connect(widget, SIGNAL(signal2x4()), radioButton_2, SLOT(click()));
        QObject::connect(radioButton, SIGNAL(clicked()), widget, SLOT(model2x1()));
        QObject::connect(radioButton_3, SIGNAL(clicked()), widget, SLOT(model2x2()));
        QObject::connect(radioButton_2, SIGNAL(clicked()), widget, SLOT(model2x4()));
        QObject::connect(widget, SIGNAL(signalRed(double)), doubleSpinBox, SLOT(setValue(double)));
        QObject::connect(widget, SIGNAL(signalGreen(double)), doubleSpinBox_2, SLOT(setValue(double)));
        QObject::connect(widget, SIGNAL(signalBlue(double)), doubleSpinBox_3, SLOT(setValue(double)));
        QObject::connect(doubleSpinBox, SIGNAL(valueChanged(double)), widget, SLOT(slotRed(double)));
        QObject::connect(doubleSpinBox_2, SIGNAL(valueChanged(double)), widget, SLOT(slotGreen(double)));
        QObject::connect(doubleSpinBox_3, SIGNAL(valueChanged(double)), widget, SLOT(slotBlue(double)));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "IDI-Lab", nullptr));
        label_2->setText(QCoreApplication::translate("MyForm", "Canviar bloc:", nullptr));
        radioButton->setText(QCoreApplication::translate("MyForm", "Model 2x1", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MyForm", "Model 2x2", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MyForm", "Model 2x4", nullptr));
        label->setText(QCoreApplication::translate("MyForm", "Color RGB:", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "&Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
