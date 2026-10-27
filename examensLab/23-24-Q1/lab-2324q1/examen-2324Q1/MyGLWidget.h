#include "ExamGLWidget.h"

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
    virtual void modelTransformBrick(int i);

  public slots:
    void model2x1();
    void model2x2();
    void model2x4();
    void slotRed(double r);
    void slotGreen(double g);
    void slotBlue(double b);
    
  signals:
    void signal2x1();
    void signal2x2();
    void signal2x4();
    void signalRed(double val);
    void signalGreen(double val);
    void signalBlue(double val);

  private:
    int printOglError(const char file[], int line, const char func[]);
    glm::vec3 red, black;
    float x, y, z;
    float angleRotacioBrick;
    bool bloc1rotat;
    bool cam2;
    float l, r, b, t;
    glm::mat4 TG;
};
