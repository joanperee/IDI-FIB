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
  creaBuffersCub();
  creaBuffersTerra();

  glm::vec3 pmin, pmax;
  pmin = glm::vec3(0, 0, 0);
  pmax = glm::vec3(30, 7, 20);

  // Paràmetres de l'escena
  centreEsc = glm::vec3((pmin + pmax) / 2.f);
  radiEsc = glm::distance(pmin, pmax) / 2.f;

  // inicialitzem llum
  enviaPosFocus();

  // inicialitzacions variables afegides
  pinta1 = pinta2 = pinta3 = true;
  anglePlataforma = 0.f;
  timerEnces = false;
  connect(&timer, SIGNAL(timeout()), this, SLOT(plataformaTimer()));
}

void MyGLWidget::iniMaterialCub()
{
  // Donem valors al material del cub
  amb = glm::vec3(0.0, 0.0, 0.2);
  diff = glm::vec3(0.0, 0.0, 0.6);
  spec = glm::vec3(1, 1, 1);
  shin = 500;
}

void MyGLWidget::enviaPosFocus()
{
  if (focusCamera)
  {
    posFoc = glm::vec3(0, 0, 0);
    glUniform3fv(posfocusLoc, 1, &posFoc[0]);
    glUniform1i(focusCameraLoc, focusCamera);
  }
  else 
  {
    posFoc1 = glm::vec3(View * glm::vec4(5, 8, 20, 1));
    posFoc2 = glm::vec3(View * glm::vec4(15, 8, 20, 1));
    posFoc3 = glm::vec3(View * glm::vec4(25, 8, 20, 1));
    glUniform3fv(posfocus1Loc, 1, &posFoc1[0]);
    glUniform3fv(posfocus2Loc, 1, &posFoc2[0]);
    glUniform3fv(posfocus3Loc, 1, &posFoc3[0]);
    glUniform1i(focusCameraLoc, focusCamera);
  }
}

void MyGLWidget::iniCamera()
{
  angleX = -0.5;
  angleY = 0.0;
  ra = float(width()) / height();
  alfa = glm::radians(30.f);
  fov = 2 * alfa;
  zn = radiEsc;
  zf = 3 * radiEsc;
  focusCamera = true;
  projectTransform();
  viewTransform();
}

void MyGLWidget::resizeGL(int w, int h)
{
#ifdef __APPLE__
  // Aquest codi és necessari únicament per a MACs amb pantalla retina.
  GLint vp[4];
  glGetIntegerv(GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif

  ra = float(ample) / float(alt);
  if (ra < 1.0)
  {
    float alfaNew = atan(tan(alfa) / ra);
    fov = 2 * alfaNew;
  }
  projectTransform();
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

  // Pintem el Patricio que ha quedat 1r
  if (pinta1)
  {
    glBindVertexArray(VAO_Patr);
    modelTransformPatricio(glm::vec3(4.0 / 1.0), glm::vec3(15, 4, 10), 0.0);
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size() * 3);
  }

  // Pintem el Patricio que ha quedat 2n
  if (pinta2)
  {
    glBindVertexArray(VAO_Patr);
    modelTransformPatricio(glm::vec3(5.0 / 1.0), glm::vec3(10, 3, 10), -5.0);
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size() * 3);
  }

  // Pintem el Patricio que ha quedat 3r
  if (pinta3)
  {
    glBindVertexArray(VAO_Patr);
    modelTransformPatricio(glm::vec3(6.0 / 1.0), glm::vec3(20, 2, 10), 5.0);
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size() * 3);
  }

  // Pintem la plataforma que està al centre del terra (15, 0, 10);
  glBindVertexArray(VAO_Cub);
  modelTransformCub(glm::vec3(20.0 / 0.5, 1.0 / 0.5, 10.0 / 0.5), glm::vec3(15, 0, 10), 0.0);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Pintem el podi del 1r
  glBindVertexArray(VAO_Cub);
  modelTransformCub(glm::vec3(5.0 / 0.5, 3.0 / 0.5, 5.0 / 0.5), glm::vec3(15, 1, 10), 0.0);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Pintem el podi del 2n
  glBindVertexArray(VAO_Cub);
  modelTransformCub(glm::vec3(5.0 / 0.5, 2.0 / 0.5, 5.0 / 0.5), glm::vec3(10, 1, 10), -5.0);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Pintem el podi del 3r
  glBindVertexArray(VAO_Cub);
  modelTransformCub(glm::vec3(5.0 / 0.5, 1.0 / 0.5, 5.0 / 0.5), glm::vec3(20, 1, 10), 5.0);
  glDrawArrays(GL_TRIANGLES, 0, 36);

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformPatricio(glm::vec3 escala, glm::vec3 posbase, float radi)
{
  glm::mat4 TG(1.f);
  TG = glm::translate(TG, glm::vec3(posbase.x - radi, posbase.y, posbase.z));
  TG = glm::rotate(TG, anglePlataforma, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(radi, 0, 0));

  TG = glm::scale(TG, glm::vec3(escala));
  TG = glm::scale(TG, glm::vec3(escalaPat, escalaPat, escalaPat));
  TG = glm::translate(TG, -centreBasePat);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformCub(glm::vec3 escala, glm::vec3 posbase, float radi)
{
  glm::mat4 TG = glm::mat4(1.f);
  TG = glm::translate(TG, glm::vec3(posbase.x - radi, posbase.y, posbase.z));
  TG = glm::rotate(TG, anglePlataforma, glm::vec3(0, 1, 0));
  TG = glm::translate(TG, glm::vec3(radi, 0, 0));

  TG = glm::scale(TG, glm::vec3(escala));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform()
{
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2 * radiEsc));
  View = glm::rotate(View, -angleX, glm::vec3(1, 0, 0));
  View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
  View = glm::translate(View, -centreEsc);

  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform()
{
  glm::mat4 Proj; // Matriu de projecció
  Proj = glm::perspective(fov, ra, zn, zf);

  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
  makeCurrent();
  switch (event->key())
  {
  case Qt::Key_Up:
  {
    if (!pinta1 and !pinta2 and !pinta3)
    {
      pinta3 = true;
      emit signalPatricios(1);
    }
    else if (pinta3 and !pinta2 and !pinta1)
    {
      pinta2 = true;
      emit signalPatricios(2);
    }
    else
    {
      pinta1 = true;
      emit signalPatricios(3);
    }
    break;
  }
  case Qt::Key_Down:
  {
    if (pinta1 and pinta2 and pinta3)
    {
      pinta1 = false;
      emit signalPatricios(2);
    }
    else if (pinta2 and pinta3)
    {
      pinta2 = false;
      emit signalPatricios(1);
    }
    else
    {
      emit signalPatricios(0);
      pinta3 = false;
    }
    break;
  }
  case Qt::Key_Left:
  {
    anglePlataforma -= glm::radians(30.f);
    break;
  }
  case Qt::Key_Right:
  {
    anglePlataforma += glm::radians(30.f);
    break;
  }
  case Qt::Key_F:
  {
    focusCamera = !focusCamera;
    enviaPosFocus();
    if (focusCamera)
      emit signalFocusCam();
    else
      emit signalFocusEsc();
    break;
  }
  case Qt::Key_R:
  {
    iniEscena();
    iniCamera();
    emit signalFocusCam();
    emit signalPatricios(3);
    timer.stop();
    break;
  }
  case Qt::Key_T:
  {
    timerEnces = !timerEnces;
    if (timerEnces) timer.start(90);
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
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleX -= (e->y() - yClick) * M_PI / alt;
    angleY += (e->x() - xClick) * M_PI / alt;
    viewTransform();
  }

  xClick = e->x();
  yClick = e->y();

  update();
}

void MyGLWidget::focusCam()
{
  makeCurrent();
  focusCamera = true;
  enviaPosFocus();
  update();
}

void MyGLWidget::focusEsc()
{
  makeCurrent();
  focusCamera = false;
  enviaPosFocus();
  update();
}

void MyGLWidget::slotPatricios(int p)
{
  makeCurrent();
  if (p == 3)
    pinta1 = pinta2 = pinta3 = true;
  else if (p == 2)
    pinta2 = pinta3 = true;
  else
    pinta3 = true;
  update();
}

void MyGLWidget::plataformaTimer()
{
  makeCurrent();
  anglePlataforma += glm::radians(30.f);
  update();
}

void MyGLWidget::carregaShaders() 
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("./shaders/basicLlumShader.frag");
  vs.compileSourceFile("./shaders/basicLlumShader.vert");
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
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  // Obtenim identificador per a l'atribut “normal” del vertex shader
  normalLoc = glGetAttribLocation (program->programId(), "normal");
  // Obtenim identificador per a l'atribut “matamb” del vertex shader
  matambLoc = glGetAttribLocation (program->programId(), "matamb");
  // Obtenim identificador per a l'atribut “matdiff” del vertex shader
  matdiffLoc = glGetAttribLocation (program->programId(), "matdiff");
  // Obtenim identificador per a l'atribut “matspec” del vertex shader
  matspecLoc = glGetAttribLocation (program->programId(), "matspec");
  // Obtenim identificador per a l'atribut “matshin” del vertex shader
  matshinLoc = glGetAttribLocation (program->programId(), "matshin");

  // Demanem identificadors per als uniforms dels shaders
  transLoc = glGetUniformLocation (program->programId(), "TG");
  projLoc = glGetUniformLocation (program->programId(), "proj");
  viewLoc = glGetUniformLocation (program->programId(), "view");
  posfocusLoc = glGetUniformLocation (program->programId(), "posFocus");
  posfocus1Loc = glGetUniformLocation (program->programId(), "posFocus1");
  posfocus2Loc = glGetUniformLocation (program->programId(), "posFocus2");
  posfocus3Loc = glGetUniformLocation (program->programId(), "posFocus3");  
  focusCameraLoc = glGetUniformLocation (program->programId(), "focusCamera");
}