#include <QLCDNumber>
#include <QLabel>

class MyQLCDNumber: public QLCDNumber
{
    Q_OBJECT
    public:
        MyQLCDNumber (QWidget *parent);

    public slots:
        void increment();
        void incrementRecaptacio();
        void incrementRecaptacioPlus();

    private:
        int num;
};