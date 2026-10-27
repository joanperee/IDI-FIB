// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
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

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::initializeGL() {
  
  initializeOpenGLFunctions();  

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  

  colFocusLoc = glGetUniformLocation(program->programId(),"colFocus");
  blanc = true;
  
  iniEscena ();
  inicamorto ();
  cubs = true;
  
  projectTransform();
  viewTransform();

  angleY = 0.0f;
  angle1 = 0.0f; 
  angle2 = 2.*M_PI/3.;
  angle3 = 4.*M_PI/3.;
  
}

void MyGLWidget::iniFocus() {
  colFocus = glm::vec3(1.0f,1.0f,1.0f);
  glUniform3fv(colFocusLoc,1,&colFocus[0]);
}

void MyGLWidget::inicamorto() {
  
  orto.VRP = centreEsc;
  orto.OBS = orto.VRP + 2*radiEsc * glm::vec3(0, 1, 0);
  orto.UP = glm::vec3(1, 0, 0);

  orto.left   = -radiEsc;
  orto.right  =  radiEsc;
  orto.bottom = -radiEsc;
  orto.top    =  radiEsc;
  orto.zNear  =  radiEsc;
  orto.zFar   =  3 * radiEsc;

  ExamGLWidget::iniCamera();
}

void MyGLWidget::paintGL ()   // Mètode que has de modificar
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el cub
  if (cubs) {
    glBindVertexArray(VAO_Cub);
    modelTransformCub (2.0,angle1);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    
    glBindVertexArray(VAO_Cub);
    modelTransformCub (2.5, angle2);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(VAO_Cub);
    modelTransformCub (3.0, angle3);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }

  else {
    // Pintem el Patricio
    glBindVertexArray (VAO_Patr);
    modelTransformPatricio ();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }

  glBindVertexArray(0);
}



void MyGLWidget::modelTransformCub (float escala, float angle) 
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG,angle,glm::vec3(0.0f,1.0f,0.0f));
  TG = glm::translate(TG,glm::vec3(5.0f,0.0f,0.0f));
  TG = glm::scale(TG,glm::vec3(escala,escala,escala));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio ()    // Mètode que has de modificar
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG,angleY,glm::vec3(0.0f,1.0f,0.0f));
  TG = glm::translate(TG,glm::vec3(5.0f,0.0f,0.0f));
  TG = glm::rotate(TG,glm::radians(-90.0f),glm::vec3(.0f,0.0f,0.0f));
  TG = glm::scale(TG, glm::vec3 (escala*2.0f, escala*2.0f, escala*2.0f));
  TG = glm::translate(TG, -centreBasePat);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else
  {
    glm::mat4 view = glm::lookAt(orto.OBS, orto.VRP, orto.UP);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &view[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
    glm::mat4 proj = glm::ortho(orto.left, orto.right, orto.bottom, orto.top, orto.zNear, orto.zFar);

    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &proj[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
    cubs = !cubs;
    break;
	}
  case Qt::Key_1: {
    angleY = 0.0f;
    modelTransformPatricio();
    break;
	}
  case Qt::Key_2: {
    angleY = 2.*M_PI/3.;
    modelTransformPatricio();
    break;
	}
  case Qt::Key_3: {
    angleY = 4.*M_PI/3.;
    modelTransformPatricio();
    break;
	}
  case Qt::Key_F: {
    blanc = !blanc;

    if(blanc) colFocus = glm::vec3(1.0f,1.0f,1.0f);
    else colFocus = glm::vec3(1.0f,1.0f,0.0f);

    glUniform3fv(colFocusLoc,1,&colFocus[0]);
    break;
	}
  case Qt::Key_C: {
    camPlanta = !camPlanta;
    projectTransform();
    viewTransform();
    break;
	}
  case Qt::Key_Right: {
    angle1 += 2.*M_PI/3.;
    angle2 += 2.*M_PI/3.;
    angle3 += 2.*M_PI/3.;
    angleY += 2.*M_PI/3.;
    break;
	}
  case Qt::Key_Left: {
    angle1 -= 2.*M_PI/3.;
    angle2 -= 2.*M_PI/3.;
    angle3 -= 2.*M_PI/3.;
    angleY -= 2.*M_PI/3.;
    break;
	}
  case Qt::Key_R: {
    initializeGL();
    iniFocus();
    viewTransform();
    projectTransform();
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}

