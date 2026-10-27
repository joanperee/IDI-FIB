#include "ExamGLWidget.h"
#include <QTimer>

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0);
    ~MyGLWidget();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void mouseMoveEvent (QMouseEvent *event);

    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();
    
    virtual void modelTransformCurrentBrick();

  public slots:
    
  signals:


  private:
    int printOglError(const char file[], int line, const char func[]);
    glm::vec3 red;    
    glm::vec3 black;
    glm::vec3 posBrick;
    float rotacioBrick;
};
