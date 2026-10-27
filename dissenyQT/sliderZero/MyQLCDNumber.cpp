#include "MyQLCDNumber.h"

MyQLCDNumber::MyQLCDNumber(QWidget *parent) :QLCDNumber(parent) {

}

void MyQLCDNumber::setZero()
{
    display(0);
}
