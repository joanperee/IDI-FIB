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
  creaBuffersTerra();
  creaBuffersCub();
  creaBuffersEsfera();

  glm::vec3 pmin, pmax;
  pmin = glm::vec3(0, 0, 0);
  pmax = glm::vec3(30, 4, 20);

  // Paràmetres de l'escena
  centreEsc = glm::vec3((pmin + pmax) / 2.f);
  radiEsc = glm::distance(pmin, pmax) / 2.f;

  anglePatricio = 0.f;

  focusEsc = false;
  enviaPosFocus();
  timerActiu = true;
  connect(&timer, SIGNAL(timeout()), this, SLOT(slotGiraPatricio()));
}

void MyGLWidget::enviaPosFocus()
{
  if (not focusEsc)
    posFoc = glm::vec3(0, 0, 0);
  else
    posFoc = glm::vec3(View * glm::vec4(15, 10, 10, 1));
  glUniform3fv(posfocusLoc, 1, &posFoc[0]);
}

void MyGLWidget::iniCamera()
{
  angleY = 0.5;
  angleX = -0.5;
  camPlanta = false;

  zn = radiEsc;
  zf = 3 * radiEsc;

  // perspectiva 3D
  ra = float(width()) / height();
  alfa = glm::radians(30.f);
  fov = 2 * alfa;

  // ortogonal 2D
  l = -radiEsc;
  r = radiEsc;
  b = -radiEsc;
  t = radiEsc;
  vrp = centreEsc;
  obs = centreEsc + glm::vec3(0, 2 * radiEsc, 0);
  up = glm::vec3(0, 0, -1);

  projectTransform();
  viewTransform();
}

void MyGLWidget::paintGL()
{
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  //  glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer i el depth-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray(VAO_Terra);
  modelTransformTerra();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el Patricio
  glBindVertexArray(VAO_Patr);
  modelTransformPatricio();
  glDrawArrays(GL_TRIANGLES, 0, patr.faces().size() * 3);

  // Pintem els 3 arbres
  pintaArbre(glm::vec3(10, 0, 10));
  pintaArbre(glm::vec3(20, 0, 5));
  pintaArbre(glm::vec3(25, 0, 15));

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformPatricio()
{
  TG = glm::mat4(1.f);
  // Alçada 2, al punt (15, 0, 10) i mirant a +Z, es pot rotar amb Key_Up
  TG = glm::translate(TG, glm::vec3(10, 0, 10));
  TG = glm::rotate(TG, -anglePatricio, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(5, 0, 0));
  TG = glm::scale(TG, glm::vec3(2.f));
  TG = glm::scale(TG, glm::vec3(escala, escala, escala));
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform()
{
  if (!camPlanta)
  {
    View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2 * radiEsc));
    View = glm::rotate(View, -angleX, glm::vec3(1, 0, 0));
    View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, -centreEsc);
  }
  else
  {
    View = glm::lookAt(obs, vrp, up);
  }
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform()
{
  glm::mat4 Proj; // Matriu de projecció
  if (!camPlanta)
  {
    Proj = glm::perspective(fov, ra, zn, zf);
  }
  else
  {
    Proj = glm::ortho(l, r, b, t, zn, zf);
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
    anglePatricio += glm::radians(360 / 32.f);
    modelTransformPatricio();
    anglePatricio = int(anglePatricio)%32;
    emit teclaUp();
    break;
  }
  case Qt::Key_F:
  {
    focusEsc = !focusEsc;
    enviaPosFocus();
    break;
  }
  case Qt::Key_C:
  {
    camPlanta = !camPlanta;
    viewTransform();
    projectTransform();
    emit teclaC();
    break;
  }
  case Qt::Key_R:
  {
    iniEscena();
    iniCamera();
    anglePatricio = 0.f;
    modelTransformPatricio();
    break;
  }
  case Qt::Key_T:
  {
    timerActiu = !timerActiu;
    if (timerActiu)
    {
      timer.start(100);
    }
    else timer.stop();
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
  if ((DoingInteractive == ROTATE) && !camPlanta)
  {
    // Fem la rotació
    angleX -= (e->y() - yClick) * M_PI / ample;
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform();
  }

  xClick = e->x();
  yClick = e->y();

  update();
}

void MyGLWidget::canviCamera()
{
  makeCurrent();
  camPlanta = !camPlanta;
  viewTransform();
  projectTransform();
  update();
}

void MyGLWidget::giraPatricio(int gir)
{
  makeCurrent();
  anglePatricio = glm::radians(float(gir) * 11.25);
  modelTransformPatricio();
  update();
}

void MyGLWidget::slotGiraPatricio()
{
  makeCurrent();
  anglePatricio += glm::radians(360 / 32.f);
  modelTransformPatricio();
  emit teclaUp();
  update();
}
