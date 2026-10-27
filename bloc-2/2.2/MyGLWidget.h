// MyGLWidget.h
#include "Bl2GLWidget.h"
#include "model.h"

class MyGLWidget : public Bl2GLWidget
{
  Q_OBJECT

public:
  MyGLWidget(QWidget *parent = 0) : Bl2GLWidget(parent) {}
  ~MyGLWidget();

  // Declarem els mètodes de la classe MyGLWidget com a virtuals pel polimorfisme
  virtual void carregaShaders();
  virtual void projectTransform();
  virtual void viewTransform();
  virtual void paintGL();
  virtual void creaBuffers();
  virtual void initializeGL();
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void modelTransformHomer();
  virtual void modelTransformTerra();
  virtual void ini_camera();
  virtual void ini_escena();
  virtual void calculaCapsaModel();

private:
  int printOglError(const char file[], int line, const char func[]);

  glm::vec3 centreEscena;
  glm::vec3 pmin, pmax;
  glm::vec3 centreBase;
  glm::vec3 OBS;
  glm::vec3 VRP;
  glm::vec3 UP;

  float radiEscena;
  float zNear;
  float zFar;
  float ra;
  float FOV;
  float l, r, b, t;
  float escalaModel;
  float angleRotacio;
  float angleX, angleY;

  bool camOrto;

  GLuint projLoc;
  GLuint viewLoc;
  GLuint VAO_Patricio;
  GLuint VAO_Terra;

  Model m;
};
