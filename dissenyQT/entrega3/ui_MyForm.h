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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyQButton.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLCDNumber *lcdNumber;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    MyQButton *pushButton_3;
    MyQButton *pushButton_2;
    MyQButton *pushButton;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    MyQButton *pushButton_4;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_5;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_7;
    MyQButton *pushButton_6;
    MyQButton *pushButton_5;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(795, 502);
        horizontalLayout_5 = new QHBoxLayout(MyForm);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(MyForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_4);

        lcdNumber = new QLCDNumber(MyForm);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));

        horizontalLayout_3->addWidget(lcdNumber);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(MyForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_3 = new MyQButton(MyForm);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(124, 124, 124);"));

        horizontalLayout_2->addWidget(pushButton_3);

        pushButton_2 = new MyQButton(MyForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(124, 124, 124);"));

        horizontalLayout_2->addWidget(pushButton_2);

        pushButton = new MyQButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(124, 124, 124);"));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_4 = new MyQButton(MyForm);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy1.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(pushButton_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_5 = new QLabel(MyForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_8->addWidget(label_5);


        verticalLayout->addLayout(horizontalLayout_8);

        line_2 = new QFrame(MyForm);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        pushButton_6 = new MyQButton(MyForm);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        horizontalLayout_7->addWidget(pushButton_6);

        pushButton_5 = new MyQButton(MyForm);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        horizontalLayout_7->addWidget(pushButton_5);


        verticalLayout->addLayout(horizontalLayout_7);


        horizontalLayout_5->addLayout(verticalLayout);


        retranslateUi(MyForm);
        QObject::connect(pushButton_4, SIGNAL(clicked()), pushButton_4, SLOT(jugar()));
        QObject::connect(pushButton_4, SIGNAL(enviaColor1(QString)), pushButton_3, SLOT(setStyleSheet(QString)));
        QObject::connect(pushButton_4, SIGNAL(enviaColor2(QString)), pushButton_2, SLOT(setStyleSheet(QString)));
        QObject::connect(pushButton_4, SIGNAL(enviaColor3(QString)), pushButton, SLOT(setStyleSheet(QString)));
        QObject::connect(pushButton_3, SIGNAL(clicked()), pushButton_4, SLOT(posaColor1()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), pushButton_4, SLOT(posaColor2()));
        QObject::connect(pushButton, SIGNAL(clicked()), pushButton_4, SLOT(posaColor3()));
        QObject::connect(pushButton_5, SIGNAL(clicked()), MyForm, SLOT(close()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), pushButton_3, SLOT(reiniciaColor()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), pushButton_2, SLOT(reiniciaColor()));
        QObject::connect(pushButton_6, SIGNAL(clicked()), pushButton, SLOT(reiniciaColor()));
        QObject::connect(pushButton_4, SIGNAL(actualitzaComptador(int)), lcdNumber, SLOT(display(int)));
        QObject::connect(pushButton_6, SIGNAL(clicked()), pushButton_4, SLOT(reinciarComptador()));
        QObject::connect(pushButton_4, SIGNAL(actualitzaComptador(int)), lcdNumber, SLOT(display(int)));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "Atzar", nullptr));
        label_4->setText(QCoreApplication::translate("MyForm", "Trios:", nullptr));
        label_2->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("MyForm", "&1", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MyForm", "&2", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "&3", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MyForm", "&Jugar", nullptr));
        label_5->setText(QString());
        pushButton_6->setText(QCoreApplication::translate("MyForm", "&Reiniciar", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MyForm", "&Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
