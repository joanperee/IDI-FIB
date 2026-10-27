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
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio ();
    virtual void projectTransform ();
    virtual void viewTransform ();

    //ex3
    void iniFocus();
    virtual void initializeGL();

    //ex4
    void inicamorto();
  private:
    int printOglError(const char file[], int line, const char func[]);

    //ex2
    float angleY;
    bool cubs;

    //ex3
    glm::vec3 colFocus;
    GLuint colFocusLoc;
    bool blanc;

    //ex4
    glm::vec3 VRP,OBS,UP;
    struct cam {
      glm::vec3 OBS, VRP, UP;
      float left, right, bottom, top, zNear, zFar;
    };
    cam orto;

    //ex5
    float angle1; 
    float angle2;
    float angle3;
};
