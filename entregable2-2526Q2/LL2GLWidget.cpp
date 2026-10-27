#include "LL2GLWidget.h"

#include <iostream>

LL2GLWidget::LL2GLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  xClick = yClick = 0;
  DoingInteractive = NONE;
}

LL2GLWidget::~LL2GLWidget ()
{
  if (program != NULL)
    delete program;
}

void LL2GLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  
  glEnable(GL_DEPTH_TEST);
  
  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersFantasma();
  creaBuffersCub();
  iniEscena();
  iniCamera();
}

void LL2GLWidget::iniEscena()
{
  // Paràmetres de l'escena - arbitraris
  radiEscena = 25;
}

void LL2GLWidget::iniCamera()
{
  viewTransform();
}

void LL2GLWidget::paintGL ()
{
  // descomentar per canviar paràmetres
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Roda - La roda té 72 cubs, un cub cada 5 graus
  glBindVertexArray (VAO_Cub);
  for (int i = 0; i < 360; i += 5)
  {
    modelTransformCub (alcades[1][i/5],float(i),20.0f,0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  
  // Fantasma
  glBindVertexArray (VAO_Fantasma);
  modelTransformFantasma ();
  glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size()*3);

  glBindVertexArray (0);
}

void LL2GLWidget::modelTransformFantasma ()
{
  glm::mat4 TG(1.f);
  TG = glm::scale(TG, glm::vec3 (escalaFantasma, escalaFantasma, escalaFantasma));
  TG = glm::translate(TG, -centreBaseFantasma);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL2GLWidget::modelTransformCub (float alcada, float angle, float radi, float z)
{
  glm::mat4 TG = glm::mat4(1.f);  // Matriu de transformació
  TG = glm::rotate(TG, float(glm::radians(angle)),glm::vec3(0.f, 0.f, 1.f));
  TG = glm::translate(TG, glm::vec3(0,radi,z));
  TG = glm::scale(TG, glm::vec3(2, glm::max(0.1f,alcada)*0.5, 1.8));
  TG = glm::translate(TG, -glm::vec3(0.5,0,0.5));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void LL2GLWidget::projectTransform ()
{
  glm::mat4 Proj(1.0f);
  Proj = glm::perspective (float(M_PI/3.0), 1.0f, 3.0f, 70.0f);
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void LL2GLWidget::viewTransform ()
{
  // Matriu de posició i orientació de l'observador
  glm::mat4 View(1.0f);
  View = glm::lookAt (glm::vec3(10,10,50), glm::vec3(10,10,0), glm::vec3(0,1,0));
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void LL2GLWidget::resizeGL (int w, int h) 
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
  ra = float(ample)/float(alt);
  factorAngleY = M_PI / ample;
  factorAngleX = M_PI / alt;
  projectTransform();
}

void LL2GLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    default: event->ignore(); break;
  }
  update();
}

void LL2GLWidget::mousePressEvent (QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
}

void LL2GLWidget::mouseReleaseEvent( QMouseEvent *)
{
  DoingInteractive = NONE;
}

void LL2GLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();

  xClick = e->x();
  yClick = e->y();

  update ();
}

void LL2GLWidget::creaBuffersCub ()
{
  // Vèrtexs del cub
  glm::vec3 vertexs[8] = {
       /* 0*/ glm::vec3( 0.0, 0.0, 0.0),  /* 1*/ glm::vec3( 1.0, 0.0, 0.0),
       /* 2*/ glm::vec3( 0.0, 1.0, 0.0),  /* 3*/ glm::vec3( 1.0, 1.0, 0.0),
       /* 4*/ glm::vec3( 0.0, 0.0, 1.0),  /* 5*/ glm::vec3( 1.0, 0.0, 1.0),
       /* 6*/ glm::vec3( 0.0, 1.0, 1.0),  /* 7*/ glm::vec3( 1.0, 1.0, 1.0)
  };

  // VBO amb la posició dels vèrtexs
  glm::vec3 poscub[36] = {  // 12 triangles
       vertexs[0], vertexs[2], vertexs[1],
       vertexs[1], vertexs[2], vertexs[3],
       vertexs[5], vertexs[1], vertexs[7],
       vertexs[1], vertexs[3], vertexs[7],
       vertexs[2], vertexs[6], vertexs[3],
       vertexs[3], vertexs[6], vertexs[7],
       vertexs[0], vertexs[4], vertexs[6],
       vertexs[0], vertexs[6], vertexs[2],
       vertexs[0], vertexs[1], vertexs[4],
       vertexs[1], vertexs[5], vertexs[4],
       vertexs[4], vertexs[5], vertexs[6],
       vertexs[5], vertexs[7], vertexs[6]
  };

  // Colors del cub
  glm::vec3 cols[6] = {
       /* 0*/ glm::vec3( 1.0, 0.0, 0.0),  /* 1*/ glm::vec3( 0.0, 1.0, 0.0),
       /* 2*/ glm::vec3( 0.0, 0.0, 1.0),  /* 3*/ glm::vec3( 1.0, 1.0, 0.0),
       /* 4*/ glm::vec3( 0.0, 1.0, 1.0),  /* 5*/ glm::vec3( 1.0, 0.0, 1.0)
  };

  glm::vec3 colorscub[36];
  int i=0;
  for (int c=0; c<6; c++)
    for (int v=0; v<6; v++)
      colorscub[i++] = cols[c]*glm::vec3(0.7);

// Creació del Vertex Array Object del cub
  glGenVertexArrays(1, &VAO_Cub);
  glBindVertexArray(VAO_Cub);

  GLuint VBO_Cub[2];
  glGenBuffers(2, VBO_Cub);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(poscub), poscub, GL_STATIC_DRAW);

  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Cub[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colorscub), colorscub, GL_STATIC_DRAW);

  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

  glBindVertexArray(0);
}

void LL2GLWidget::calculaCapsaModelFantasma ()
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = fantasma.vertices()[0];
  miny = maxy = fantasma.vertices()[1];
  minz = maxz = fantasma.vertices()[2];
  for (unsigned int i = 3; i < fantasma.vertices().size(); i+=3)
  {
    if (fantasma.vertices()[i+0] < minx)
      minx = fantasma.vertices()[i+0];
    if (fantasma.vertices()[i+0] > maxx)
      maxx = fantasma.vertices()[i+0];
    if (fantasma.vertices()[i+1] < miny)
      miny = fantasma.vertices()[i+1];
    if (fantasma.vertices()[i+1] > maxy)
      maxy = fantasma.vertices()[i+1];
    if (fantasma.vertices()[i+2] < minz)
      minz = fantasma.vertices()[i+2];
    if (fantasma.vertices()[i+2] > maxz)
      maxz = fantasma.vertices()[i+2];
  }
  escalaFantasma = 10.0/(maxx-minx);
  
  centreBaseFantasma[0] = (minx+maxx)/2.0; 
  centreBaseFantasma[1] = miny; 
  centreBaseFantasma[2] = (minz+maxz)/2.0;
}

void LL2GLWidget::creaBuffersFantasma ()
{
  // Càrrega dels models
  fantasma.load("./models/Fantasma.obj");

  // Calculem la capsa contenidora del model
  calculaCapsaModelFantasma ();
  // Creació del Vertex Array Object del Fantasma
  glGenVertexArrays(1, &VAO_Fantasma);
  glBindVertexArray(VAO_Fantasma);

  GLuint VBO_Fantasma[2];
  glGenBuffers(2, VBO_Fantasma);

  // geometria
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Fantasma[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*fantasma.faces().size()*3*3,     
               fantasma.VBO_vertices(), GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // color
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Fantasma[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*fantasma.faces().size()*3*3,
               fantasma.VBO_matdiff(), GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);  
  
  glBindVertexArray (0);
}

void LL2GLWidget::carregaShaders()
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

  // Identificador per als  atributs
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  colorLoc = glGetAttribLocation (program->programId(), "color");

  // Identificadors dels uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc  = glGetUniformLocation (program->programId(), "Proj");
  viewLoc  = glGetUniformLocation (program->programId(), "View");
}

