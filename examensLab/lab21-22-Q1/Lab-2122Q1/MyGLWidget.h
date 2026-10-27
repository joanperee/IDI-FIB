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
    virtual void modelTransformAvio ();
    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();
    virtual void enviaPosFocus ();
    virtual void iniMaterialTerra ();
  
  public slots:
    void canviCamera();
    void canviAltura(int h);
  
  signals:
    void teclaC();
    void signalAltura(int h);
  
  private:
    int printOglError(const char file[], int line, const char func[]);  
    
    float alfa;
    float fov2;
    float zn2;
    float zf2;
    float alturaAvio;
    float angleAvio;

    glm::vec3 OBS;
    glm::vec3 VRP;
    glm::vec3 UP;

    bool focusModel;
};
