
//#include <GL/glew.h>
#include "MyGLWidget.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  
  glClearColor (0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffers();
}

void MyGLWidget::paintGL ()
{
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  glViewport (0, 0, ample, alt);
  
  glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

  // OBJECTE 1 
  glBindVertexArray(VAO1);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  
  glClear(GL_COLOR_BUFFER_BIT); // esborrar el frame-buffer
  modelTransform();
  glBindVertexArray(VAO1);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::resizeGL (int w, int h)
{
  ample = w;
  alt = h;
}

void MyGLWidget::keyPressEvent(QKeyEvent *e)
{
  makeCurrent();
  float scl = 0.5;
  switch(e->key())
  {
    case Qt::Key_S:
      scl += 0.1;
      glUniform1f(varLoc, scl);
      break;
    case Qt::Key_D:
      scl -= 0.1;
      glUniform1f(varLoc, scl);
      break; 
    default: e->ignore();
  }
  update();
}

void MyGLWidget::modelTransform()
{
  glm::mat4 TG(1.0);  // Matriu de transformació identitat d'ordre 4
  TG = glm::translate(TG, glm::vec3 (-0.5, 0.5, 0.0));
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::creaBuffers ()
{
  // OBJECTE 1 (TRIANGLE GRAN)
  glm::vec3 Vertices[3];  // Tres vèrtexs amb X, Y i Z (1 triangle/s)
 
  // Triangle 1 (paret dreta)
  Vertices[0] = glm::vec3(-1.0, -1.0, 0.0);   // bottom-left
  Vertices[1] = glm::vec3( 0.0,  1.0, 0.0);   // top-middle
  Vertices[2] = glm::vec3( 1.0, -1.0, 0.0);   // bottom-right
  
  // Colors dels vèrtexs
  glm::vec3 Colors[3];
  Colors[0] = glm::vec3(1, 0, 0);   // bottom-left
  Colors[1] = glm::vec3(0, 0, 1);   // top-middle
  Colors[2] = glm::vec3(0, 1, 0);   // bottom-right

  // Creació del Vertex Array Object (VAO) que usarem per pintar
  glGenVertexArrays(1, &VAO1);
  glBindVertexArray(VAO1);

  // Creació del buffer amb les dades dels vèrtexs
  GLuint VBO1;
  glGenBuffers(1, &VBO1);
  glBindBuffer(GL_ARRAY_BUFFER, VBO1);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Creació del buffer amb les dades dels colors
  GLuint VBO2;
  glGenBuffers(1, &VBO2);
  glBindBuffer(GL_ARRAY_BUFFER, VBO2);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
  // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)	
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  // SCL variable que conté el valor que es vol per "val"
  float scl = 0.5;
  glUniform1f (varLoc, scl);

  // Desactivem el VAO
  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
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
  colorLoc = glGetAttribLocation (program->programId(), "color");
  varLoc = glGetUniformLocation (program->programId(), "val");
}
