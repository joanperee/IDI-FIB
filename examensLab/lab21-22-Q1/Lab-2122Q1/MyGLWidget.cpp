// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__, __FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[])
{
  GLenum glErr;
  int retCode = 0;

  glErr = glGetError();
  const char *error = 0;
  switch (glErr)
  {
  case 0x0500:
    error = "GL_INVALID_ENUM";
    break;
  case 0x501:
    error = "GL_INVALID_VALUE";
    break;
  case 0x502:
    error = "GL_INVALID_OPERATION";
    break;
  case 0x503:
    error = "GL_STACK_OVERFLOW";
    break;
  case 0x504:
    error = "GL_STACK_UNDERFLOW";
    break;
  case 0x505:
    error = "GL_OUT_OF_MEMORY";
    break;
  default:
    error = "unknown error!";
  }
  if (glErr != GL_NO_ERROR)
  {
    printf("glError in file %s @ line %d: %s function: %s\n",
           file, line, error, func);
    retCode = 1;
  }
  return retCode;
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::iniEscena()
{
  creaBuffersPatricio();
  creaBuffersAvio();
  creaBuffersHangar();
  creaBuffersTerra();

  // Càlculs intermitjos
  glm::vec3 pmin, pmax;
  pmin = glm::vec3(0.0, 0.0, 0.0);
  pmax = glm::vec3(30.0, 2.5, 24);

  // Paràmetres de l'escena
  centreEsc = glm::vec3(15.0, 1.25, 12.0);
  radiEsc = glm::distance(pmin, pmax) / 2.f;
}

void MyGLWidget::iniMaterialTerra()
{
  // Donem valors al material del terra
  amb = glm::vec3(0.0, 0.2, 0.2);  // color
  diff = glm::vec3(0.0, 0.7, 0.7); // color + 0.5
  spec = glm::vec3(1, 1, 1);       // brillo
  shin = 500;
}

void MyGLWidget::enviaPosFocus()
{
  if (not focusModel)
  {
    posFoc = glm::vec3(0, 0, 0);
    glUniform3fv(posfocusLoc, 1, &posFoc[0]);
  }
  else
  {
    glm::vec3 cuaAvio = glm::vec3((capsaAvioMax.x + capsaAvioMin.x)/2.f,
                                  (capsaAvioMax.y + capsaAvioMin.y)/2.f,
                                  capsaAvioMin.z);  
    posFoc = glm::vec3(View * TGAvio * glm::vec4(cuaAvio, 1));
    glUniform3fv(posfocusLoc, 1, &posFoc[0]);
  }
  // línia per focus escena
  // posFoc = glm::vec3(View * glm::vec4(0, 0, 0, 1));
}

void MyGLWidget::iniCamera()
{
  angleY = 0.5;
  angleX = -0.5;
  camera2 = false;
  alfa = glm::radians(30.f);
  ra = float(width()) / height();
  fov = 2.f * alfa; // 60º pq dist(OBS, VRP) és 2*radiEsc
  zn = radiEsc;
  zf = 3 * radiEsc;

  OBS = glm::vec3(15, 3, 12);
  VRP = glm::vec3(15 - 1, 3, 12);
  UP = glm::vec3(0, 1, 0);
  fov2 = glm::radians(90.f);
  zn2 = 0.1f;
  zf2 = 30.f;

  alturaAvio = 0.f;

  focusModel = false;

  projectTransform();
  viewTransform();
}

void MyGLWidget::paintGL()
{
  ExamGLWidget::paintGL();
}

void MyGLWidget::modelTransformPatricio()
{
  glm::mat4 TG(1.f);

  TG = glm::translate(TG, glm::vec3(15, 0, 12));
  TG = glm::scale(TG, glm::vec3(2.0 / 1.0));
  TG = glm::rotate(TG, glm::radians(-90.f), glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(escalaPat, escalaPat, escalaPat));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformAvio()
{
  TGAvio = glm::mat4(1.f);

  TGAvio = glm::translate(TGAvio, glm::vec3(25 - 10, alturaAvio, 12));
  TGAvio = glm::rotate(TGAvio, glm::radians(angleAvio), glm::vec3(0, 1, 0));
  TGAvio = glm::translate(TGAvio, glm::vec3(10, 0, 0)); // radi de rotació
  TGAvio = glm::scale(TGAvio, glm::vec3(1.5 / 1.0));
  TGAvio = glm::scale(TGAvio, glm::vec3(escalaAvio, escalaAvio, escalaAvio));
  TGAvio = glm::translate(TGAvio, -centreBaseAvio);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TGAvio[0][0]);
}

void MyGLWidget::viewTransform()
{
  if (!camera2)
  {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2 * radiEsc));
    View = glm::rotate(View, -angleX, glm::vec3(1, 0, 0));
    View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, glm::vec3(-centreEsc)); // portem l'esc al (0,0,0)
  }
  else
  {
    View = glm::mat4(1.0f);
    View = glm::lookAt(OBS, VRP, UP);
  }
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform()
{
  glm::mat4 Proj;
  if (!camera2)
  {
    Proj = glm::perspective(fov, ra, zn, zf);
  }
  else
  {
    Proj = glm::perspective(fov2, ra, zn2, zf2);
  }
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
  makeCurrent();
  switch (event->key())
  {
  case Qt::Key_Up:
  {
    if (alturaAvio < 5)
    {
      alturaAvio += 1.f;
    }
    modelTransformAvio();
    emit signalAltura(alturaAvio);
    break;
  }
  case Qt::Key_Down:
  {
    if (alturaAvio > 0)
    {
      alturaAvio -= 1.f;
    }
    modelTransformAvio();
    emit signalAltura(alturaAvio);
    break;
  }
  case Qt::Key_Right:
  {
    angleAvio -= 360 / 32.f;
    modelTransformAvio();
    break;
  }
  case Qt::Key_F:
  {
    focusModel = !focusModel;
    enviaPosFocus();
    break;
  }
  case Qt::Key_C:
  {
    camera2 = !camera2;
    viewTransform();
    projectTransform();
    emit teclaC();
    break;
  }
  case Qt::Key_R:
  {
    iniCamera();
    iniEscena();
    angleAvio = 0.f;
    modelTransformAvio();
    emit signalAltura(alturaAvio);
    emit teclaC();
    break;
  }
  default:
    ExamGLWidget::keyPressEvent(event);
    break;
  }
  update();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  if ((DoingInteractive == ROTATE) && !camera2)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    angleX += (e->y() - yClick) * M_PI / ample;
    viewTransform();
  }

  xClick = e->x();
  yClick = e->y();

  update();
}

void MyGLWidget::canviCamera()
{
  makeCurrent();
  camera2 = !camera2;
  viewTransform();
  projectTransform();
  update();
}

void MyGLWidget::canviAltura(int h)
{
  makeCurrent();
  alturaAvio = h;
  modelTransformAvio();
  update();
}
