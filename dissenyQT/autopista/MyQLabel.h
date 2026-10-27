#include <QLabel>

class MyQLabel: public QLabel
{
    Q_OBJECT
    public:
        MyQLabel (QWidget *parent);

    public slots:
        void changeOpen();
};
