#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__, __FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

MyGLWidget::MyGLWidget(QWidget *parent = 0) : LL2GLWidget(parent)
{
  connect(&timer, SIGNAL(timeout()), this, SLOT(girarRoda())); // per al moviment de la roda
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

void MyGLWidget::iniEscena()
{
  LL2GLWidget::iniEscena();

  // Paràmetres moviment roda
  angleRoda = 0;
  velocitatRoda = 0.25;

  // Paràmetres capsa contenidora de l'escena
  glm::vec3 pmin, pmax;
  pmin = glm::vec3(-23, -23, -3);
  pmax = glm::vec3(23, 23, 3);
  radiEsc = glm::distance(pmin, pmax) / 2.f;
  centreEsc = glm::vec3(pmin + pmax) / 2.f;

  // Moviment del fantasma
  // Si el valor és 0 està al mig, si és 1 està a la dreta i si és -1 està a l'esquerra
  // Actualitzarem el valor segons convengui per implementar el moviment amb les tecles
  rodaActual = 0;
}

void MyGLWidget::iniCamera()
{
  // Inclinacions inicials
  factorAngleX = glm::radians(45.f);
  factorAngleY = glm::radians(0.f);

  // Paràmetres de la càmara perspectiva (3D)
  FOV = glm::radians(60.f);
  ra = 1.f;
  znear = radiEsc;
  zfar = radiEsc * 3.f;
  cam2 = false;

  timer.start(16);  
  // inicio el timer del moviment aquí perquè després
  // crido la funció al premer la tecla "R"

  viewTransform();
}

void MyGLWidget::paintGL()
{
  // descomentar per canviar paràmetres
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Roda - La roda té 72 cubs, un cub cada 5 graus
  // Creem 3 rodes per formar el mapa amb els cubs
  glBindVertexArray(VAO_Cub);
  for (int i = 0; i < 360; i += 5)
  {
    modelTransformCub(alcades[0][i / 5], float(i), 20.0f, -2.0f);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  glBindVertexArray(VAO_Cub);
  for (int i = 0; i < 360; i += 5)
  {
    modelTransformCub(alcades[1][i / 5], float(i), 20.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  glBindVertexArray(VAO_Cub);
  for (int i = 0; i < 360; i += 5)
  {
    modelTransformCub(alcades[2][i / 5], float(i), 20.0f, 2.0f);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  // Fantasma
  glBindVertexArray(VAO_Fantasma);
  modelTransformFantasma();
  glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size() * 3);

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformFantasma()
{
  glm::mat4 TG(1.f);

  TG = glm::translate(TG, glm::vec3(0, 0, 2*rodaActual)); // ex5
  TG = glm::translate(TG, glm::vec3(0, 21, 0));                                   // (0, 0, 0) a (0, 21, 0)
  TG = glm::scale(TG, glm::vec3(2 / 10.f, 2 / 10.f, 2 / 10.f));                   // alçada final = 2
  TG = glm::rotate(TG, glm::radians(90.f), glm::vec3(0, 1, 0));                   // rotem en sentit antihorari 90º (+Z a +X)
  TG = glm::scale(TG, glm::vec3(escalaFantasma, escalaFantasma, escalaFantasma)); // escala inicial (alçada 10)
  TG = glm::translate(TG, -centreBaseFantasma);                                   // porta al punt (0, 0, 0)

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformCub(float alcada, float angle, float radi, float z)
{
  glm::mat4 TG = glm::mat4(1.f);                                           // Matriu de transformació
  TG = glm::rotate(TG, glm::radians(angleRoda), glm::vec3(0.f, 0.f, 1.f)); // rotate cada 16 ms
  TG = glm::rotate(TG, float(glm::radians(angle)), glm::vec3(0.f, 0.f, 1.f));
  TG = glm::translate(TG, glm::vec3(0, radi, z));
  TG = glm::scale(TG, glm::vec3(2, glm::max(0.1f, alcada) * 0.5, 1.8));
  TG = glm::translate(TG, -glm::vec3(0.5, 0, 0.5));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform()
{
  glm::mat4 Proj(1.0f);

  if (not cam2)
  {
    Proj = glm::perspective(FOV, ra, znear, zfar); // Calculem els paràmetres de la càmara a iniCamera
  }
  else
  {
    Proj = glm::perspective(FOV, ra, float(0.1), float(4*radiEsc)); // Paràmetres znear/zfar canvien arbitràriament
  }
  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform()
{
  // Matriu de posició i orientació de l'observador

  glm::mat4 View(1.0f);

  if (not cam2) // Ho fem amb angles d'Euler
  {
    
    View = glm::translate(View, glm::vec3(0, 0, -2*radiEsc)); // allunyem l'observador
    View = glm::rotate(View, factorAngleX, glm::vec3(1, 0, 0)); // rotar vertical 45º
    View = glm::rotate(View, factorAngleY, glm::vec3(0, 1, 0)); // rotar horitzontal 0º
    View = glm::translate(View, -centreEsc);                    // portar Escena al (0, 0, 0)
  }
  else  // La càmara2 està activa i configurada amb lookAt
  {
    View = glm::lookAt(glm::vec3(-5, 25, 0), glm::vec3(0, 23, 0), glm::vec3(0, 1, 0));
  }

  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  if (not cam2) // Ens assegurem que el moviment de ratolí només afecta amb la cam1 activa
  {
    makeCurrent();

    // Afegim la traducció "moure ratolí" -> pixels -> rotació de l'aplicació
    if (DoingInteractive == ROTATE)
    {
      int deltaX = e->x() - xClick;
      int deltaY = e->y() - yClick;

      factorAngleX += deltaY / float(alt) * 2 * M_PI;
      factorAngleY += deltaX / float(ample) * 2 * M_PI;

      viewTransform();
    }

    xClick = e->x();
    yClick = e->y();

    update();
  }
  
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
  makeCurrent();
  switch (event->key())
  {
  case Qt::Key_Left:
  {
    // El fantasma fa un salt a l'esquerra si pot
    if (rodaActual != -1)
    {
      rodaActual -= 1;
    }
    break;
  }
  case Qt::Key_Right:
  {
    // El fantasma fa un salt a la dreta si pot
    if (rodaActual != 1)
    {
      rodaActual += 1;
    }
    break;
  }
  case Qt::Key_C:
  {
    // Canvi de càmara
    cam2 = not cam2;
    viewTransform();
    projectTransform();
    break;
  }
  case Qt::Key_A:
  {
    // Atura les rodes
    timer.stop();
    break;
  }
  case Qt::Key_E:
  {
    // Engega les rodes
    timer.start(16);
    break;
  }
  case Qt::Key_R:
  {
    // Reinicia l'escena
    iniCamera();
    iniEscena();
    break;
  }
  default:
    event->ignore();
    break;
  }
  update();
}

void MyGLWidget::girarRoda()
{
  makeCurrent();
  // ex3: cada timeout (16 ms) s'executa angleRoda += velocitatRoda (0.25)
  angleRoda += velocitatRoda;
  // s'ha de modificar la funció que pinta les rodes afegint el rotate(angleRoda)
  update();
}
