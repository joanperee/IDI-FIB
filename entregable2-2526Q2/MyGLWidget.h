#include "LL2GLWidget.h"

#include <vector>

#include <QTimer>

class MyGLWidget : public LL2GLWidget
{
  Q_OBJECT

public:
  MyGLWidget(QWidget *parent);
  ~MyGLWidget();

protected:
  virtual void keyPressEvent(QKeyEvent *event);
  virtual void iniEscena();
  virtual void iniCamera();
  virtual void paintGL();
  virtual void projectTransform();
  virtual void viewTransform();
  virtual void modelTransformFantasma();
  virtual void mouseMoveEvent(QMouseEvent *e);
  virtual void modelTransformCub(float, float, float, float);

  // per al moviment automàtic
  QTimer timer;

  // per moure la roda
  float angleRoda;
  float velocitatRoda;
  bool girant;

public slots:
  void girarRoda();

private:
  int printOglError(const char file[], int line, const char func[]);

  // Aquí tots els atributs privats que necessitis
  glm::vec3 centreEsc;
  float FOV, ra, znear, zfar;
  int radiEsc; 
  int rodaActual;
  bool cam2;
};
