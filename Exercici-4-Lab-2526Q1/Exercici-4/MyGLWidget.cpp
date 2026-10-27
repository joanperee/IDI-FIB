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
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  carregaShaders();

  creaBuffersMorty();
  creaBuffersFantasma();
  creaBuffersTerraIParets();

  iniEscena();
  iniCamera();

  angleMorty = 0.f;
  posMorty = glm::vec3(5.f, 0.f, 5.f);
  posFantasma = glm::vec3(1.f, 0.5f, 5.f);
  mortyMiraFantasma = false;

  focusEscenaApagats = false;
  focusModelApagat = false;

  iniFocus();
}

void MyGLWidget::iniFocus()
{
  modelTransformMorty();
  viewTransform();
  posFocus1 = glm::vec3(View * glm::vec4(10, 6, 0, 1));
  posFocus2 = glm::vec3(View * glm::vec4(10, 6, 10, 1));
  posFocus3 = glm::vec3(View * glm::vec4(0, 6, 0, 1));
  posFocus4 = glm::vec3(View * glm::vec4(0, 6, 10, 1));
  if (!focusEscenaApagats)
    colorFocus = glm::vec3(0.7, 0, 0.7);
  else
    colorFocus = glm::vec3(0.0, 0.0, 0.0);
  glUniform3fv(posFocus1Loc, 1, &posFocus1[0]);
  glUniform3fv(posFocus2Loc, 1, &posFocus2[0]);
  glUniform3fv(posFocus3Loc, 1, &posFocus3[0]);
  glUniform3fv(posFocus4Loc, 1, &posFocus4[0]);
  glUniform3fv(colorFocusLoc, 1, &colorFocus[0]);

  posFocusModel = glm::vec3(View * TG_morty * glm::vec4(60, -90, -7, 1));
  if (!focusModelApagat)
    colorFocusModel = glm::vec3(0.9, 0.9, 0.0);
  else
    colorFocusModel = glm::vec3(0.0, 0.0, 0.0);
  glUniform3fv(colorFocusModelLoc, 1, &colorFocusModel[0]);
  glUniform3fv(posFocusModelLoc, 1, &posFocusModel[0]);
}

void MyGLWidget::paintGL()
{
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer i el depth-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // TERRA
  glBindVertexArray(VAO_Terra);
  modelTransformTerra();
  glDrawArrays(GL_TRIANGLES, 0, 30);

  // MORTY
  glBindVertexArray(VAO_Morty);
  modelTransformMorty();
  glDrawArrays(GL_TRIANGLES, 0, morty.faces().size() * 3);

  // FANTASMA -> (ex3) Si el morty està mirant el fantasma, no es pintarà
  if (!mortyMiraFantasma)
  {
    glBindVertexArray(VAO_Fantasma);
    modelTransformFantasma();
    glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size() * 3);
  }

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformMorty()
{
  TG_morty = glm::translate(glm::mat4(1.f), glm::vec3(5, 0, 5));
  TG_morty = glm::rotate(TG_morty, glm::radians(angleMorty), glm::vec3(0.f, 1.f, 0.f));
  TG_morty = glm::rotate(TG_morty, float(glm::radians(90.0)), glm::vec3(0.f, 1.f, 0.f));
  TG_morty = glm::scale(TG_morty, glm::vec3(escalaMorty, escalaMorty, escalaMorty));
  TG_morty = glm::translate(TG_morty, -centreBaseMorty);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG_morty[0][0]);
}

void MyGLWidget::modelTransformFantasma()
{
  glm::mat4 TG;
  TG = glm::translate(glm::mat4(1.f), posFantasma);
  TG = glm::rotate(TG, float(glm::radians(90.0)), glm::vec3(0.f, 1.f, 0.f));
  TG = glm::scale(TG, glm::vec3(escalaFantasma, escalaFantasma, escalaFantasma));
  TG = glm::translate(TG, -centreBaseFantasma);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

bool MyGLWidget::mortyMiraFantasmaFunc()
{
  glm::vec3 dirMorty(sin(glm::radians(angleMorty)), 0.f, cos(glm::radians(angleMorty)));

  glm::vec3 dirFantasma = posFantasma - posMorty;

  dirMorty = glm::normalize(dirMorty);
  dirFantasma = glm::normalize(dirFantasma);

  return glm::dot(dirMorty, dirFantasma) > 0.0f;
}

void MyGLWidget::reiniciaEscena()
{
  posMorty = glm::vec3(5.f, 0.f, 5.f);
  posFantasma = glm::vec3(1.f, 0.5f, 5.f);
  angleMorty = 0.f;

  focusEscenaApagats = false;
  focusModelApagat = false;

  modelTransformMorty();
  iniFocus();
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
  bool gira = false;
  switch (event->key())
  {
  case Qt::Key_Left:
  {
    angleMorty += 45.f;
    modelTransformMorty();
    iniFocus();
    gira = true;
    break;
  }
  case Qt::Key_Right:
  {
    angleMorty -= 45.f;
    modelTransformMorty();
    iniFocus();
    gira = true;
    break;
  }
  case Qt::Key_M:
  {
    focusModelApagat = !focusModelApagat;
    iniFocus();
    break;
  }
  case Qt::Key_E:
  {
    focusEscenaApagats = !focusEscenaApagats;
    iniFocus();
    break;
  }
  default:
    LL4GLWidget::keyPressEvent(event);
    break;
  }

  if (gira)
  {
    modelTransformMorty();
    iniFocus();

    mortyMiraFantasma = mortyMiraFantasmaFunc();

    if (!mortyMiraFantasma)
    {
      glm::vec3 dir = glm::normalize(posMorty - posFantasma);
      posFantasma += 0.5f * dir;
    }

    if (glm::length(posFantasma - posMorty) <= 0.5f)
      reiniciaEscena();
  }

  update();
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs(QOpenGLShader::Fragment, this);
  QOpenGLShader vs(QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicLlumShader.frag");
  vs.compileSourceFile("shaders/basicLlumShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Obtenim identificador per a l'atribut “vertex” del vertex shader
  vertexLoc = glGetAttribLocation(program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “normal” del vertex shader
  normalLoc = glGetAttribLocation(program->programId(), "normal");
  // Obtenim identificador per a l'atribut “matamb” del vertex shader
  matambLoc = glGetAttribLocation(program->programId(), "matamb");
  // Obtenim identificador per a l'atribut “matdiff” del vertex shader
  matdiffLoc = glGetAttribLocation(program->programId(), "matdiff");
  // Obtenim identificador per a l'atribut “matspec” del vertex shader
  matspecLoc = glGetAttribLocation(program->programId(), "matspec");
  // Obtenim identificador per a l'atribut “matshin” del vertex shader
  matshinLoc = glGetAttribLocation(program->programId(), "matshin");

  // Demanem identificadors per als uniforms del vertex shader
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc = glGetUniformLocation(program->programId(), "Proj");
  viewLoc = glGetUniformLocation(program->programId(), "View");

  // Afegim els Localitzadors pels focus de l'entregable
  posFocus1Loc = glGetUniformLocation(program->programId(), "posFocus1");
  posFocus2Loc = glGetUniformLocation(program->programId(), "posFocus2");
  posFocus3Loc = glGetUniformLocation(program->programId(), "posFocus3");
  posFocus4Loc = glGetUniformLocation(program->programId(), "posFocus4");
  posFocusModelLoc = glGetUniformLocation(program->programId(), "posFocusModel");
  colorFocusLoc = glGetUniformLocation(program->programId(), "colorFocus");
  colorFocusModelLoc = glGetUniformLocation(program->programId(), "colorFocusModel");
}
