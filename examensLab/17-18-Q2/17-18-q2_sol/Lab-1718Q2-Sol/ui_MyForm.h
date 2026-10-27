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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
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
    QCheckBox *checkBox;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(819, 726);
        horizontalLayout = new QHBoxLayout(MyForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new MyGLWidget(MyForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        checkBox = new QCheckBox(MyForm);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        verticalLayout->addWidget(checkBox);

        radioButton_4 = new QRadioButton(MyForm);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));

        verticalLayout->addWidget(radioButton_4);

        radioButton_3 = new QRadioButton(MyForm);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));

        verticalLayout->addWidget(radioButton_3);

        radioButton_2 = new QRadioButton(MyForm);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout->addWidget(radioButton_2);

        radioButton = new QRadioButton(MyForm);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout->addWidget(radioButton);

        radioButton_5 = new QRadioButton(MyForm);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setChecked(true);

        verticalLayout->addWidget(radioButton_5);

        pushButton_2 = new QPushButton(MyForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

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
        QObject::connect(radioButton_4, SIGNAL(clicked(bool)), widget, SLOT(show1(bool)));
        QObject::connect(radioButton_3, SIGNAL(clicked(bool)), widget, SLOT(show2(bool)));
        QObject::connect(radioButton_2, SIGNAL(clicked(bool)), widget, SLOT(show3(bool)));
        QObject::connect(radioButton, SIGNAL(clicked(bool)), widget, SLOT(show4(bool)));
        QObject::connect(radioButton_5, SIGNAL(clicked()), widget, SLOT(showAll()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), radioButton_5, SLOT(click()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), widget, SLOT(reset()));
        QObject::connect(checkBox, SIGNAL(clicked(bool)), widget, SLOT(tipusCam(bool)));
        QObject::connect(pushButton_2, SIGNAL(clicked(bool)), checkBox, SLOT(setChecked(bool)));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "Form", nullptr));
        checkBox->setText(QCoreApplication::translate("MyForm", "CamPat", nullptr));
        radioButton_4->setText(QCoreApplication::translate("MyForm", "Pat1", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MyForm", "Pat2", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MyForm", "Pat3", nullptr));
        radioButton->setText(QCoreApplication::translate("MyForm", "Pat4", nullptr));
        radioButton_5->setText(QCoreApplication::translate("MyForm", "Tots", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MyForm", "Reset", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "&Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
