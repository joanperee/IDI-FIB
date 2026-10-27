#include "ExamGLWidget.h"
#include <QTimer>

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

  private:
    int printOglError(const char file[], int line, const char func[]);
    float alfa;
    float l, r, b, t, zn2, zf2;
    float anglePatricio;
    glm::vec3 obs;
    glm::vec3 vrp;
    glm::vec3 up;
    bool focusEsc;
    QTimer timer;
    bool timerActiu;
  
  signals:
    void teclaC();
    void teclaUp();
  
  public slots:
    void canviCamera();
    void giraPatricio(int gir); // gir està entre 0...32
    void slotGiraPatricio();
};
