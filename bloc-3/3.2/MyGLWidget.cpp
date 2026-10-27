// MyGLWidget.cpp

// TIPUS DE FOCUS (3.2)
// - càmara: posFocus
// - escena: view*posFocus
// - model: TG*view*posFocus
// Això es calcula a posFocusSCO = view*posFocus

#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__, __FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

void MyGLWidget::initializeGL()
{
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  creaBuffersPatricio();
  creaBuffersTerraIParet();

  iniEscena();
  iniCamera();

  posFocus = glm::vec3(1, 1, 1);
  colorFocus = glm::vec3(0.8, 0.1, 0.1);
  llumAmbient = glm::vec3(0.2, 0.2, 0.2);
  glUniform3fv(posFocusLoc, 1, &posFocus[0]);
  glUniform3fv(colorFocusLoc, 1, &colorFocus[0]);
  glUniform3fv(llumAmbientLoc, 1, &llumAmbient[0]);

  focusEscena = 1;
}

void MyGLWidget::iniMaterialTerra()
{
  // Donem valors al material del terra
  amb = glm::vec3(0.0, 0.0, 0.2); // color
  diff = glm::vec3(0.0, 0, 0.8);  // color diff > amb
  spec = glm::vec3(1, 1, 1);      // brillo
  shin = 100;                     // mida de la taca (com més alt el valor més petita)
}

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

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform();
  }

  xClick = e->x();
  yClick = e->y();

  update();
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
  makeCurrent();
  switch (event->key())
  {
  case Qt::Key_K: // moure focus +X
    posFocus.x -= 0.2f;
    glUniform3fv(posFocusLoc, 1, &posFocus[0]);
    break;
  case Qt::Key_L: // moure focus -X
    posFocus.x += 0.2f;
    glUniform3fv(posFocusLoc, 1, &posFocus[0]);
    break;
  case Qt::Key_F: // focus escena 1 - focus camara 0
    focusEscena = !focusEscena;
    glUniform1i(numeroLoc, focusEscena);
    break;
  default:
    BL3GLWidget::keyPressEvent(event);
    break;
  }
  update();
}

void MyGLWidget::carregaShaders()
{
  BL3GLWidget::carregaShaders();
  posFocusLoc = glGetUniformLocation(program->programId(), "posFocus");
  colorFocusLoc = glGetUniformLocation(program->programId(), "colorFocus");
  numeroLoc = glGetUniformLocation(program->programId(), "focusEscena");
}
