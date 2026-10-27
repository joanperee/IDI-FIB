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

    // funcions afegides
    virtual void initializeGL ();
    virtual void enviaColFocus ();
    virtual void mousePressEvent (QMouseEvent *e);

  private:
    int printOglError(const char file[], int line, const char func[]);
    
    // atributs afegits
    bool pintaPatricio; // pintem patricio o els cubs?
    bool focusGroc; // usem el focus blanc o groc?
    
    glm::vec3 posIniPatricio; // serà (5, 0, 0) com diu l'enunciat
    glm::vec3 OBS;  //  
    glm::vec3 VRP;
    glm::vec3 UP;
    
    int posPatricio;
    
    float angleY;
    float angle1, angle2, angle3;    
    float l, r, b, t, zn, zf;
};
