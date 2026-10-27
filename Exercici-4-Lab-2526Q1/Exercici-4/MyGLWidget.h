// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget
{
  Q_OBJECT

public:
  MyGLWidget(QWidget *parent = 0) : LL4GLWidget(parent) {}
  ~MyGLWidget();

protected:
  virtual void mouseMoveEvent(QMouseEvent *e);
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void initializeGL();
  virtual void paintGL();
  virtual void modelTransformMorty();
  virtual void modelTransformFantasma();
  virtual void iniFocus();
  virtual void carregaShaders();
  virtual bool mortyMiraFantasmaFunc();
  virtual void reiniciaEscena();

private:
  int printOglError(const char file[], int line, const char func[]);
  float angleMorty;
  GLuint posFocus1Loc, posFocus2Loc, posFocus3Loc, posFocus4Loc;
  GLuint posFocusModelLoc;
  GLuint colorFocusLoc, colorFocusModelLoc;
  glm::vec3 posFocus1, posFocus2, posFocus3, posFocus4;
  glm::vec3 colorFocus;
  glm::vec3 posFocusModel, colorFocusModel;
  bool focusModelApagat, focusEscenaApagats;
  glm::vec3 posMorty;
  glm::vec3 posFantasma;
  bool mortyMiraFantasma;
};
