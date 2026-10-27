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

MyGLWidget::MyGLWidget(QWidget *parent) : ExamGLWidget(parent)
{
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::iniEscena()
{
  creaBuffersModels();

  // inicialitzem tots els possibles objectes (blocs de Lego) com a "buits" --> no es pinten ni tenen valors guardats més que els per defecte
  for (int i = 0; i < NUM_BRICKS; i++)
  {
    pintarBricks[i] = false;
    brickModelIndex[i] = 1;
    brickTGs[i] = glm::mat4(1);
    brickColors[i] = glm::vec3(1, 1, 1);
  }

  // inicialitzem l'objecte actual (el bloc de Lego) a editar
  currentBrickObjectIndex = 0;
  currentBrickModelIndex = 1;
  x = y = z = 0;

  // inicialitzem els colors
  red = glm::vec3(0.7, 0.0, 0.0);
  black = glm::vec3(0.0, 0.0, 0.0);
  currentColor = white;

  // Inicialitzem els paràmetres de l'escena
  glm::vec3 pmin, pmax;
  pmin = glm::vec3(-10, -1, -10);
  pmax = glm::vec3(10, 10, 10);

  centreEsc = glm::vec3((pmin + pmax) / 2.f);
  radiEsc = glm::distance(pmin, pmax) / 2.f;

  angleRotacioBrick = 0.f;
  bloc1rotat = false;
}

void MyGLWidget::iniCamera()
{
  // Inicialitzem els paràmetres de càmera amb valors arbitraris
  angleY = glm::radians(15.f);
  angleX = glm::radians(15.f);
  ra = float(width()) / height();
  fov = float(M_PI / 3.0);
  zn = radiEsc;
  zf = 3 * radiEsc;
  cam2 = false;
  l = -radiEsc;
  r = radiEsc;
  b = -radiEsc;
  t = radiEsc;
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

  // Pintem el terra = GROUND_BRICKS
  glUniform3fv(colorLoc, 1, &red[0]);
  glBindVertexArray(VAO_models[GROUND_BRICKS]);
  modelTransformGround();
  glDrawArrays(GL_TRIANGLES, 0, models[GROUND_BRICKS].faces().size() * 3);

  // Pintem el bloc de Lego actual (currentBrick) del color actual
  glUniform3fv(colorLoc, 1, &currentColor[0]);
  glBindVertexArray(VAO_models[currentBrickModelIndex]);
  modelTransformCurrentBrick();
  glDrawArrays(GL_TRIANGLES, 0, models[currentBrickModelIndex].faces().size() * 3);

  // Pintem el bloc de Lego amb línies
  glUniform3fv(colorLoc, 1, &black[0]);
  glBindVertexArray(VAO_models[currentBrickModelIndex]);
  modelTransformCurrentBrick();
  glDrawArrays(GL_LINES, 0, models[currentBrickModelIndex].faces().size() * 3);

  // Pintem tots els blocs definitius
  for (int i = 0; i < NUM_BRICKS; ++i)
  {
    if (pintarBricks[i])
    {
      glUniform3fv(colorLoc, 1, &brickColors[i][0]);
      glBindVertexArray(VAO_models[brickModelIndex[i]]);
      modelTransformBrick(brickModelIndex[i]);
      glDrawArrays(GL_TRIANGLES, 0, models[brickModelIndex[i]].faces().size() * 3);
    }
  }

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformBrick (int brickIndex)
{
  glm::mat4 TG = brickTGs[brickIndex];  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformCurrentBrick()
{
  TG = glm::mat4(float(1.0f));
  if (currentBrickModelIndex == 1 and !bloc1rotat)
    TG = glm::translate(TG, glm::vec3(0.5, 0.0, 0.0));
  if (currentBrickModelIndex == 1 and bloc1rotat)
    TG = glm::translate(TG, glm::vec3(0, 0, -0.5));
  TG = glm::translate(TG, glm::vec3(x, y, z));
  TG = glm::rotate(TG, glm::radians(angleRotacioBrick), glm::vec3(0, 1, 0));
  TG = glm::rotate(TG, glm::radians(90.f), glm::vec3(1, 0, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex], escalaModels[currentBrickModelIndex]));
  TG = glm::translate(TG, -centreCapsaModels[currentBrickModelIndex]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform()
{
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2 * radiEsc));
  View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
  View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
  View = glm::translate(View, -centreEsc);
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform()
{
  glm::mat4 Proj; // Matriu de projecció
  if (!cam2)
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
  case Qt::Key_A:
  {
    // Es mou cap a les X-
    if ((currentBrickModelIndex == 1 and x > -10) or (currentBrickModelIndex == 2 and x > -9) or (currentBrickModelIndex == 3 and x > -8))
    {
      x += -1;
      modelTransformCurrentBrick();
    }
    break;
  }
  case Qt::Key_D:
  {
    // Es mou cap a les X+
    if ((currentBrickModelIndex == 1 and x < 9) or (currentBrickModelIndex == 2 and x <= 8) or (currentBrickModelIndex == 3 and x <= 7))
    {
      x += 1;
      modelTransformCurrentBrick();
    }
    break;
  }
  case Qt::Key_W:
  {
    // Es mou cap a les Z+
    if (z < 9)
    {
      z += 1;
      modelTransformCurrentBrick();
    }
    break;
  }
  case Qt::Key_S:
  {
    // Es mou cap a les Z-
    if (z > -9)
    {
      z += -1;
      modelTransformCurrentBrick();
    }
    break;
  }
  case Qt::Key_Up:
  {
    // Es mou cap a les Y+
    if (y < 9)
    {
      y += 1;
      modelTransformCurrentBrick();
    }
    break;
  }
  case Qt::Key_Down:
  {
    if (y > 0)
    {
      y += -1;
      modelTransformCurrentBrick();
    }
    break;
  }
  case Qt::Key_Q:
  {
    angleRotacioBrick += 90.f;
    bloc1rotat = !bloc1rotat;
    modelTransformCurrentBrick();
    break;
  }
  case Qt::Key_C:
  {
    cam2 = !cam2;
    projectTransform();
    break;
  }
  case Qt::Key_M:
  {
    currentBrickModelIndex++;
    if (currentBrickModelIndex == NUM_MODELS)
      currentBrickModelIndex = 1;
    if (currentBrickModelIndex == 1) emit signal2x1();
    if (currentBrickModelIndex == 2) emit signal2x2();
    if (currentBrickModelIndex == 3) emit signal2x4();
    break;
  }
  case Qt::Key_Space:
  {
    pintarBricks[currentBrickObjectIndex] = true;
    brickColors[currentBrickObjectIndex] = currentColor;
    brickModelIndex[currentBrickObjectIndex] = currentBrickModelIndex;
    brickTGs[currentBrickObjectIndex] = TG;
    currentBrickObjectIndex++;
    break;
  }
  case Qt::Key_R:
  {
    iniEscena();
    iniCamera();
    emit signal2x1();
    emit signalRed(double(1));
    emit signalGreen(double(1));
    emit signalBlue(double(1));
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
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleX += (e->y() - yClick) * M_PI / ample;
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform();
  }

  xClick = e->x();
  yClick = e->y();

  update();
}

void MyGLWidget::model2x1()
{
  makeCurrent();
  currentBrickModelIndex = 1;
  update();
}

void MyGLWidget::model2x2()
{
  makeCurrent();
  currentBrickModelIndex = 2;
  update();
}

void MyGLWidget::model2x4()
{
  makeCurrent();
  currentBrickModelIndex = 3;
  update();
}

void MyGLWidget::slotRed(double r)
{
  makeCurrent();
  currentColor.x = r;
  update();
}

void MyGLWidget::slotGreen(double g)
{
  makeCurrent();
  currentColor.y = g;
  update();
}

void MyGLWidget::slotBlue(double b)
{
  makeCurrent();
  currentColor.z = b;
  update();
}
