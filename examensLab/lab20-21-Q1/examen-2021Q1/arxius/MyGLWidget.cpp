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

void MyGLWidget::initializeGL()
{
  ExamGLWidget::initializeGL();

  pintaPatricio = false;
  posIniPatricio = glm::vec3(5.0, 0.0, 0.0);
  posPatricio = 1;
  focusGroc = false;
  enviaColFocus();
  angle1 = 0.0;
  angle2 = 2.*M_PI/3.;
  angle3 = 4.*M_PI/3.;
  VRP = centreEsc;
  OBS = VRP + 2*radiEsc*glm::vec3(0.0, 1.0, 0.0);
  UP = glm::vec3(1.0, 0.0, 0.0);
  l = -radiEsc;
  r = radiEsc;
  b = -radiEsc;
  t = radiEsc;
  zn = radiEsc;
  zf = 3*radiEsc;
}

void MyGLWidget::paintGL() // Mètode que has de modificar
{
  // Esborrem el frame-buffer i el depth-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray(VAO_Terra);
  modelTransformTerra();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  if (pintaPatricio)
  {
    glBindVertexArray(VAO_Patr);
    modelTransformPatricio();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size() * 3);
  }
  else
  {
    // Cub 1
    glBindVertexArray(VAO_Cub);
    modelTransformCub(2.0, angle1);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Cub 2
    glBindVertexArray(VAO_Cub);
    modelTransformCub(2.5, angle2);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Cub 3
    glBindVertexArray(VAO_Cub);
    modelTransformCub(3.0, angle3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformPatricio() // Mètode que has de modificar
{
  TG = glm::mat4(1.f);

  if (posPatricio == 1) TG = glm::translate(TG, glm::vec3(5.0, 0.0, 0.0));
  else if (posPatricio == 2) TG = glm::translate(TG, glm::vec3(5.0 * cos(4.f * M_PI / 3.f), 0.0, 5.0 * sin(4.f * M_PI / 3.f)));
  else TG = glm::translate(TG, glm::vec3(5.0 * cos(2.f * M_PI / 3.f), 0.0, 5.0 * sin(2.f * M_PI / 3.f)));
  
  TG = glm::rotate(TG, glm::radians(-90.f), glm::vec3(0.0, 1.0, 0.0)); // +Z a Y (app)
  TG = glm::scale(TG, glm::vec3(escala*3, escala*3, escala*3));              // ja té alçada 2 (igual que el cub 1)
  TG = glm::translate(TG, -centreBasePat);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformCub(float escala, float angle)
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, angle, glm::vec3(0.0, 1.0, 0.0));
  TG = glm::translate(TG, glm::vec3(5.0, 0.0, 0.0));
  TG = glm::scale(TG, glm::vec3(escala/0.5, escala/0.5, escala/0.5));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::enviaColFocus()
{
  if (focusGroc) colFoc = glm::vec3(1, 1, 0);
  else colFoc = glm::vec3(1, 1, 1);
  glUniform3fv (colfocusLoc, 1, &colFoc[0]);
}

void MyGLWidget::viewTransform() // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else
  {
    View = glm::lookAt(OBS, VRP, UP);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
    glm::mat4 Proj = glm::ortho(l, r, b, t, zn, zf);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::mousePressEvent (QMouseEvent *e)
{
  if (!camPlanta)
  {
    xClick = e->x();
    yClick = e->y();

    if (e->button() & Qt::LeftButton &&
        ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
    {
      DoingInteractive = ROTATE;
    }
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
  makeCurrent();
  switch (event->key())
  {
  case Qt::Key_V:
  {
    pintaPatricio = !pintaPatricio;
    break;
  }
  case Qt::Key_1:
  {
    if (pintaPatricio)
    {
      posPatricio = 1;
      modelTransformPatricio();
    }    
    break;
  }
  case Qt::Key_2:
  {
    if (pintaPatricio)
    {
      posPatricio = 2;
      modelTransformPatricio();
    }    
    break;
  }
  case Qt::Key_3:
  {
    if (pintaPatricio)
    {
      posPatricio = 3;
      modelTransformPatricio();
    }    
    break;
  }
  case Qt::Key_F:
  {
    focusGroc = !focusGroc;
    enviaColFocus();
    break;
  }
  case Qt::Key_C:
  {
    camPlanta = !camPlanta;
    viewTransform();
    projectTransform();
    break;
  }
  case Qt::Key_Right:
  {
    angle += 2.*M_PI/3;
    break;
  }
  case Qt::Key_Left:
  {       
    angle += 2.*M_PI/3;
    break;
  }
  case Qt::Key_R:
  {
    initializeGL();
    break;
  }
  default:
    ExamGLWidget::keyPressEvent(event);
    break;
  }
  update();
}
