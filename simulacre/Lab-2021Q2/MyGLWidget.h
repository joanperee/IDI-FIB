#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);

    virtual void modelTransformPatricio ();
    virtual void enviaPosFocus ();
    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();

  public slots:
    void canviCam1();
    void canviCam2();
    void girPatricio(int g);

  signals:
    void signalCam1();
    void signalCam2();
    void signalGirPatricio(int g);

  private:
    int printOglError(const char file[], int line, const char func[]);
    float alfa; // pel càlcul del resize
    float l, r, b, t; // project transform de la càmara ortogonal
    glm::vec3 obs, vrp, up; // view transform de la càmara ortogonal
    float angleRotacioPat, radiPat;  // per implementar el gir del Patricio
    bool focusEscena; // canvi de focus càmara-escena
};
