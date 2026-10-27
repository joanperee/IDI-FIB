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

    virtual void modelTransformPatricio (glm::vec3 escala, glm::vec3 posbase, float radi);
    virtual void modelTransformCub (glm::vec3 escala, glm::vec3 posbase, float radi);
    virtual void iniEscena ();
    virtual void iniCamera ();
    virtual void projectTransform ();
    virtual void viewTransform ();
    virtual void enviaPosFocus ();
    virtual void iniMaterialCub ();
    virtual void resizeGL(int w, int h);
    virtual void carregaShaders();
  
  public slots:
    void focusCam();
    void focusEsc();
    void slotPatricios(int p);
    void plataformaTimer();

  signals:
    void signalFocusCam();
    void signalFocusEsc();
    void signalPatricios(int p);

  private:
    int printOglError(const char file[], int line, const char func[]);
    bool focusCamera; // Canvi de focus càmara - escena
    bool pinta1, pinta2, pinta3;  // Decidir quin/s patricio/s es pinta/en
    bool timerEnces;  // canvi timer encès - apagat

    float anglePlataforma;  // rotació de la plataforma
    float alfa; // càlcul resize
    
    QTimer timer; // temporitzador pel gir de la plataforma
    
    glm::vec3 posFoc1, posFoc2, posFoc3;  // 3 posicions dels focus escena
    GLuint posfocus1Loc, posfocus2Loc, posfocus3Loc;  // 3 localitzadors pels focus d'escena
    GLuint focusCameraLoc;  // localitzador del booleà per saber quin model calcular al fragment shader
};
