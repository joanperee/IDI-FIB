#include <QPushButton>
#include <QColor>

class MyQButton : public QPushButton
{
    Q_OBJECT
public:
    MyQButton(QWidget *parent);

public slots:
    void reiniciaColor();
    void reiniciarComptador();
    QString converteixNumColor(int color);
    void jugar();
    void posaColor1();
    void posaColor2();
    void posaColor3();

signals:
    void enviaColor1(QString);
    void enviaColor2(QString);
    void enviaColor3(QString);
    void actualitzaComptador(int num_trios);

private:
    int color1;
    int color2;
    int color3;
    int num_trios;
};