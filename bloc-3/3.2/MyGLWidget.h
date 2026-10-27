// MyGLWidget.h
#include "BL3GLWidget.h"

class MyGLWidget : public BL3GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL3GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void iniMaterialTerra();
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void initializeGL();
    virtual void carregaShaders();

  private:
    int printOglError(const char file[], int line, const char func[]);
    int focusEscena;
    GLuint colorFocusLoc;
    GLuint posFocusLoc;
    GLuint llumAmbientLoc;
    GLuint numeroLoc;
    glm::vec3 posFocus;
    glm::vec3 colorFocus;
    glm::vec3 llumAmbient;
};
