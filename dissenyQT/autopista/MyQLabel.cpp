#include "MyQLabel.h"
#include "globals.h"

MyQLabel::MyQLabel(QWidget *parent) :QLabel(parent) {

}

void MyQLabel::changeOpen()
{
    peatgeObert = !peatgeObert;
    if (peatgeObert)
    {
        this->setText("OBERT");
        this->setStyleSheet("background-color: green;");
    }
    else
    {
        this->setText("TANCAT");
        this->setStyleSheet("background-color: red;");
    }
}
