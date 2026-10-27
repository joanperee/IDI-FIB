#include "MyQButton.h"

MyQButton::MyQButton(QWidget *parent) : QPushButton(parent)
{
    color1 = -1;
    color2 = -1;
    color3 = -1;
    num_trios = 0;
}

void MyQButton::reiniciaColor()
{
    this->setStyleSheet("background-color:rgb(124,124,124);");
}

void MyQButton::reiniciarComptador()
{
    color1 = color2 = color3 = -1;
    num_trios = 0;
    emit actualitzaComptador(num_trios);
}

QString MyQButton::converteixNumColor(int color)
{
    QString style;
    switch (color)
    {
    case 0:
        style = "background-color: rgb(255, 0, 0);";
        break;
    case 1:
        style = "background-color: rgb(255, 255, 0);";
        break;
    case 2:
        style = "background-color: rgb(0, 255, 0);";
        break;
    case 3:
        style = "background-color: rgb(0, 0, 255);";
        break;
    default:
        break;
    }
    return style;
}

void MyQButton::jugar()
{
    color1 = rand() % 4;
    color2 = rand() % 4;
    color3 = rand() % 4;

    emit enviaColor1(converteixNumColor(color1));
    emit enviaColor2(converteixNumColor(color2));
    emit enviaColor3(converteixNumColor(color3));

    if (color1 == color2 and color2 == color3)
    {
        ++num_trios;
        emit actualitzaComptador(num_trios);
    }
}

void MyQButton::posaColor1()
{
    color1 = rand() % 4;

    emit enviaColor1(converteixNumColor(color1));

    if (color1 == color2 and color2 == color3)
    {
        num_trios++;
        emit actualitzaComptador(num_trios);
    }
}

void MyQButton::posaColor2()
{
    color2 = rand() % 4;

    emit enviaColor2(converteixNumColor(color2));

    if (color1 == color2 and color2 == color3)
    {
        num_trios++;
        emit actualitzaComptador(num_trios);
    }
}

void MyQButton::posaColor3()
{
    color3 = rand() % 4;

    emit enviaColor3(converteixNumColor(color3));

    if (color1 == color2 and color2 == color3)
    {
        num_trios++;
        emit actualitzaComptador(num_trios);
    }
}
