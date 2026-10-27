#include "MyQLCDNumber.h"
#include "globals.h"

MyQLCDNumber::MyQLCDNumber(QWidget *parent) : QLCDNumber(parent)
{
    num = 0;
}

void MyQLCDNumber::increment()
{
    if (not peatgeObert) return;
    ++num;
    display(num);
}

void MyQLCDNumber::incrementRecaptacio()
{
    if (not peatgeObert) return;
    ++recaptacio;
    display(recaptacio);
}

void MyQLCDNumber::incrementRecaptacioPlus()
{
    if (not peatgeObert) return;
    recaptacio += 4;
    display(recaptacio);
}
