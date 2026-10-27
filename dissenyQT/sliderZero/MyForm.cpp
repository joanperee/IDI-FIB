#include "MyForm.h"
#include "ui_MyForm.h"

MyForm::MyForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyForm)
{
    ui->setupUi(this);
}

MyForm::~MyForm()
{
    delete ui;
}

