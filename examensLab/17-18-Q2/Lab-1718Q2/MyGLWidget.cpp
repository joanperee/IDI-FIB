#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus); // per rebre events de teclat
  xClick = yClick = 0;
  DoingInteractive = NONE;
}

MyGLWidget::~MyGLWidget()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  glEnable(GL_DEPTH_TEST);
  carregaShaders();
  createBuffersModel();
  createBuffersTerra();

  iniEscena();
  iniCamera();
}

void MyGLWidget::iniEscena()
{
  glm::vec3 pmin, pmax;
  pmin = glm::vec3(-10, 0, -10);
  pmax = glm::vec3(10, 8, 10);
  radiEsc = glm::distance(pmin, pmax)/2.f;
  centreEsc = glm::vec3((pmin.x + pmax.x)/2.f, (pmin.y + pmax.y)/2.f, (pmin.z + pmax.z)/2.f);
}

void MyGLWidget::iniCamera()
{
  angleY = M_PI / 4.0;
  angleX = 0;
  ra = 1.0;
  alfa = glm::radians(30.f);
  fov = 2*alfa;
  zn = radiEsc;
  zf = 3*radiEsc;
  projectTransform();
  viewTransform();
}

void MyGLWidget::paintGL()
{
  // Esborrem el frame-buffer i el depth-buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Activem el VAO per a pintar el terra
  glBindVertexArray(VAO_Terra);

  modelTransformIdent();
  // pintem terra
  glDrawArrays(GL_TRIANGLES, 0, 6);

  // Patricio1
  glBindVertexArray(VAO_Model);
  modelTransformModel(2.0, glm::vec3(8, 0, 8), -120.f);
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size() * 3);

  // Patricio2
  glBindVertexArray(VAO_Model);
  modelTransformModel(4.0, glm::vec3(-8, 0, 8), 120.f);
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size() * 3);

  // Patricio3
  glBindVertexArray(VAO_Model);
  modelTransformModel(6.0, glm::vec3(8, 0, -8), -45.f);
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size() * 3);

  // Patricio4
  glBindVertexArray (VAO_Model);
  modelTransformModel(8.0, glm::vec3(-8, 0, -8),45.f);
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);

  glBindVertexArray(0);
}

void MyGLWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);
}

void MyGLWidget::modelTransformModel(float escala, glm::vec3 pos, float angleRotacioIni)
{
  glm::mat4 TG(1.f); // Matriu de transformació
  TG = glm::translate(TG, pos);
  TG = glm::rotate(TG, glm::radians(angleRotacioIni), glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(escala));
  TG = glm::scale(TG, glm::vec3(escalaModel, escalaModel, escalaModel));
  TG = glm::translate(TG, -centreBaseModel);

  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformIdent()
{
  glm::mat4 TG(1.f); // Matriu de transformació
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform()
{
  glm::mat4 Proj; // Matriu de projecció
  Proj = glm::perspective(fov, ra, zn, zf);

  glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform()
{
  glm::mat4 View; // Matriu de posició i orientació
  View = glm::translate(glm::mat4(1.f), glm::vec3(0, 0, -2 * radiEsc));
  View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
  View = glm::rotate(View, -angleY, glm::vec3(0, 1, 0));
  View = glm::translate(View, -centreEsc);

  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::calculaCapsaModel(Model &p, float &escala, glm::vec3 &centreBase)
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = p.vertices()[0];
  miny = maxy = p.vertices()[1];
  minz = maxz = p.vertices()[2];
  for (unsigned int i = 3; i < p.vertices().size(); i += 3)
  {
    if (p.vertices()[i + 0] < minx)
      minx = p.vertices()[i + 0];
    if (p.vertices()[i + 0] > maxx)
      maxx = p.vertices()[i + 0];
    if (p.vertices()[i + 1] < miny)
      miny = p.vertices()[i + 1];
    if (p.vertices()[i + 1] > maxy)
      maxy = p.vertices()[i + 1];
    if (p.vertices()[i + 2] < minz)
      minz = p.vertices()[i + 2];
    if (p.vertices()[i + 2] > maxz)
      maxz = p.vertices()[i + 2];
  }
  escala = 1.0 / (maxy - miny);
  centreBase[0] = (minx + maxx) / 2.0;
  centreBase[1] = miny;
  centreBase[2] = (minz + maxz) / 2.0;
}

void MyGLWidget::createBuffersModel()
{
  // Carreguem el model de l'OBJ - Atenció! Abans de crear els buffers!
  m.load("../../../../models/cow.obj");

  // Calculem la capsa contenidora del model
  calculaCapsaModel(m, escalaModel, centreBaseModel);

  // Creació del Vertex Array Object del Model
  glGenVertexArrays(1, &VAO_Model);
  glBindVertexArray(VAO_Model);

  // Creació dels buffers del model patr
  GLuint VBO_Model[6];
  // Buffer de posicions
  glGenBuffers(6, VBO_Model);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Model[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_vertices(), GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // Buffer de normals
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Model[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_normals(), GL_STATIC_DRAW);

  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Model[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_matamb(), GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Model[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_matdiff(), GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Model[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_matspec(), GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Model[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3, m.VBO_matshin(), GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::createBuffersTerra()
{
  // Dades del terra
  // VBO amb la posició dels vèrtexs
  glm::vec3 posterra[6] = {
      glm::vec3(-10.0, 0.0, -10.0),
      glm::vec3(-10.0, 0.0, 10.0),
      glm::vec3(10.0, 0.0, -10.0),
      glm::vec3(10.0, 0.0, -10.0),
      glm::vec3(-10.0, 0.0, 10.0),
      glm::vec3(10.0, 0.0, 10.0)};

  // VBO amb la normal de cada vèrtex
  glm::vec3 normt(0, 1, 0);
  glm::vec3 normterra[6] = {
      normt, normt, normt, normt, normt, normt};

  // Definim el material del terra
  glm::vec3 amb(0.0, 0.1, 0);
  glm::vec3 diff(0.0, 0.6, 0.0);
  glm::vec3 spec(1.0, 1.0, 1.0);
  float shin = 2;

  // Fem que aquest material afecti a tots els vèrtexs per igual
  glm::vec3 matambterra[6] = {
      amb, amb, amb, amb, amb, amb};
  glm::vec3 matdiffterra[6] = {
      diff, diff, diff, diff, diff, diff};
  glm::vec3 matspecterra[6] = {
      spec, spec, spec, spec, spec, spec};
  float matshinterra[6] = {
      shin, shin, shin, shin, shin, shin};

  // Creació del Vertex Array Object del terra
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra[6];
  glGenBuffers(6, VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posterra), posterra, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(normterra), normterra, GL_STATIC_DRAW);

  // Activem l'atribut normalLoc
  glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(normalLoc);

  // En lloc del color, ara passem tots els paràmetres dels materials
  // Buffer de component ambient
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matambterra), matambterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matambLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matambLoc);

  // Buffer de component difusa
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matdiffterra), matdiffterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matdiffLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matdiffLoc);

  // Buffer de component especular
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matspecterra), matspecterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matspecLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matspecLoc);

  // Buffer de component shininness
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(matshinterra), matshinterra, GL_STATIC_DRAW);

  glVertexAttribPointer(matshinLoc, 1, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(matshinLoc);

  glBindVertexArray(0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs(QOpenGLShader::Fragment, this);
  QOpenGLShader vs(QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/fragshad.frag");
  vs.compileSourceFile("shaders/vertshad.vert");
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
  projLoc = glGetUniformLocation(program->programId(), "proj");
  viewLoc = glGetUniformLocation(program->programId(), "view");
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
  makeCurrent();
  switch (event->key())
  {
  case Qt::Key_H:
  { // help de l'aplicació
    std::cout << std::endl
              << "Ajuda: Tecles actives a l'aplicació" << std::endl;
    std::cout << "   H: Mostra aquest mateix help." << std::endl;
    break;
  }
  default:
    event->ignore();
    break;
  }
  update();
}

void MyGLWidget::mousePressEvent(QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      !(e->modifiers() & (Qt::ShiftModifier | Qt::AltModifier | Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *)
{
  DoingInteractive = NONE;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleX += (e->y() - yClick) * M_PI / 180.0;
    angleY += (e->x() - xClick) * M_PI / 180.0;
    viewTransform();
  }

  xClick = e->x();
  yClick = e->y();

  update();
}
