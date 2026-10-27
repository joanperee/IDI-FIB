#include "MyGLWidget.h"

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
//  glViewport (0, 0, ample, alt);
  
    glClear (GL_COLOR_BUFFER_BIT);  // Esborrem el frame-buffer

    pintaParet ();
    pintaPacman ();
    pintaBoleta ();

    // Desactivem el VAO
    glBindVertexArray(0);
}

void MyGLWidget::pintaBoleta (){
    glBindVertexArray(VAO_Boleta);
    
    std::vector<std::pair<float, float>> pos = {
        {-2,-2}, {-1,-2}, {0,-2}, {1,-2}, {2,-2}, 
        {-2,-1}, {0,-1}, {2,-1}, {-2,0}, {-1,0},
        {1,0}, {2,0}, {-2,1}, {2,1}, {-2,2}, 
        {-1,2}, {0,2}, {1,2}, {2,2}
    };

    for (int i = 0; i < 19; ++i)
    {
        posX = pos[i].first;
        posY = pos[i].second;
        modelTransformBoleta (glm::vec3(posX/2.5,posY/2.5,0));
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void MyGLWidget::pintaParet (){
    glBindVertexArray(VAO_Paret);
    
    // Parets 1 i 2: escalat = alçadaFi/alçadaInit = 0.4/0.5
    // Paret 3: escalatX = 1.2/0.5

    modelTransformParet (glm::vec3(0.8,0.8,1.0), glm::vec3(-0.4,-0.4,0));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    modelTransformParet (glm::vec3(0.8,0.8,1.0), glm::vec3(0.4,-0.4,0));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    modelTransformParet (glm::vec3(2.4, 0.8, 1.0), glm::vec3(0.0,0.4,0.0));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void MyGLWidget::pintaPacman (){
    modelTransformPacman (angleRotacio);
    glBindVertexArray(VAO_Pacman);
    glDrawArrays(GL_TRIANGLES, 0, 30);
}

void MyGLWidget::modelTransformPacman (float angle){
    glm::mat4 TG (1.0f);
    TG = glm::translate(TG, glm::vec3(pcmX/2.5, pcmY/2.5, 0));
    TG = glm::rotate(TG, glm::radians(angle), glm::vec3(0,0,1));
    glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformParet (glm::vec3 escala, glm::vec3 pos){
    glm::mat4 TG (1.0f);
    
    TG = glm::translate(TG, pos);
    TG = glm::scale(TG, escala);
    TG = glm::translate(TG, glm::vec3(0.25, 0.25, 0));

    glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformBoleta (glm::vec3 pos){
    glm::mat4 TG (1.0f);
    TG = glm::translate(TG, pos);
    glUniformMatrix4fv(TGLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::resizeGL (int w, int h)
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
}

bool MyGLWidget::comprovaSiParet (int pX, int pY) {
  // Aquesta funció retorna cert si la posició (pX, pY) està ocupada per paret
  return (((pX == -1) && (pY == -1)) || // paret 1
          ((pX == 1) && (pY == -1)) ||  // paret 2
          ((pX >= -1) && (pX <= 1) && (pY == 1)));  // paret 3
}

void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
    makeCurrent();
    switch (event->key()) {

        case Qt::Key_Left: {
            if (not comprovaSiParet(pcmX - 1, pcmY) and pcmX >= -1)
            {
                pcmX -= 1; 
                angleRotacio = 0;
            }
            break;
        }
        case Qt::Key_Right: {
            if (not comprovaSiParet(pcmX + 1, pcmY) and pcmX <= 1)
            {
                pcmX += 1; 
                angleRotacio = 180;
            }                
            break;
        }
        case Qt::Key_Up: {
            if (not comprovaSiParet(pcmX, pcmY + 1) and pcmY <= 1)
            {
                pcmY += 1; 
                angleRotacio = -90;
            }
            break;
        }
        case Qt::Key_Down: {
            if (not comprovaSiParet(pcmX, pcmY - 1) and pcmY >= -1)
            {
                pcmY -= 1; 
                angleRotacio = 90;
            } 
            break;
        }
        case Qt::Key_R: {
            break;
        }
        default: event->ignore(); break;
    }
    update();
}

void MyGLWidget::creaBuffers (){
    creaBuffersParet ();
    creaBuffersBoleta ();
    creaBuffersPacman ();
}

void MyGLWidget::creaBuffersParet (){
    glm::vec3 Colors[4];
    glm::vec3 Vertices[4];
    int i=0,c=0;
    Vertices[i++] = glm::vec3(-0.5 , -0.5, 0.0);
    Vertices[i++] = glm::vec3(0.0, -0.5, 0.0);
    Vertices[i++] = glm::vec3(-0.5, 0.0, 0.0);
    Vertices[i++] = glm::vec3(0.0, 0.0, 0.0);
    Colors[c++]=COLOR_BLAU;
    Colors[c++]=COLOR_BLAU;
    Colors[c++]=COLOR_BLAU;
    Colors[c++]=COLOR_BLAU;

    // Creació del Vertex Array Object (VAO) que usarem per pintar
    glGenVertexArrays(1, &VAO_Paret);
    glBindVertexArray(VAO_Paret);

    // Creació del buffer amb les dades dels vèrtexs
    GLuint VBO[2];
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    // Creació del buffer de colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    // Desactivem el VAO
    glBindVertexArray(0);
}

void MyGLWidget::creaBuffersBoleta ()
{
    float r = 0.05;

    glm::vec3 Colors[36];
    glm::vec3 Vertices[36];
    
    for (int i=0; i<36; i++)
      Colors[i] = COLOR_BLANC;

    int i=0;

    // Sector 1
    Vertices[i++] = glm::vec3(0.0, 0.0, 0.0);
    Vertices[i++] = glm::vec3(r,  0.0, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(30.0)), r*sin(glm::radians(30.0)), 0.0);

    // Sector 2
    Vertices[i++] = glm::vec3(0.0,  0.0 , 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(30.0)), r*sin(glm::radians(30.0)), 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(60.0)), r*sin(glm::radians(60.0)), 0.0);

    // Sector 3
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(60.0)), r*sin(glm::radians(60.0)), 0.0);
    Vertices[i++] = glm::vec3(0.0, r, 0.0);

    // Sector 4
    Vertices[i++] = glm::vec3( 0.0, 0.0, 0.0);
    Vertices[i++] = glm::vec3(0.0, r, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(120.0)), r*sin(glm::radians(120.0)), 0.0);

    // Sector 5
    Vertices[i++] = glm::vec3(0.0,  0.0, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(120.0)), r*sin(glm::radians(120.0)), 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(150.0)), r*sin(glm::radians(150.0)), 0.0);

    // Sector 6
    Vertices[i++] = glm::vec3(0.0,  0.0, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(150.0)), r*sin(glm::radians(150.0)), 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(180.0)), r*sin(glm::radians(180.0)), 0.0);

    // Sector 7
    Vertices[i++] = glm::vec3(0.0,  0.0, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(180.0)), r*sin(glm::radians(180.0)), 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(210.0)), r*sin(glm::radians(210.0)), 0.0);

    // Sector 8
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0); 
    Vertices[i++] = glm::vec3(r*cos(glm::radians(210.0)), r*sin(glm::radians(210.0)), 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(240.0)), r*sin(glm::radians(240.0)), 0.0);

    // Sector 9
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0); 
    Vertices[i++] = glm::vec3(r*cos(glm::radians(240.0)), r*sin(glm::radians(240.0)), 0.0);
    Vertices[i++] = glm::vec3(0.0, -r, 0.0);

    // Sector 10
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0); 
    Vertices[i++] = glm::vec3(0.0, -r, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(300.0)), r*sin(glm::radians(300.0)), 0.0);

    // Sector 11
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0); 
    Vertices[i++] = glm::vec3(r*cos(glm::radians(300.0)), r*sin(glm::radians(300.0)), 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(330.0)), r*sin(glm::radians(330.0)), 0.0);

    // Sector 12
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0); 
    Vertices[i++] = glm::vec3(r*cos(glm::radians(330.0)), r*sin(glm::radians(330.0)), 0.0);
    Vertices[i++] = glm::vec3(r, 0.0, 0.0);


    // Creació del Vertex Array Object (VAO) que usarem per pintar
    glGenVertexArrays(1, &VAO_Boleta);
    glBindVertexArray(VAO_Boleta);

    // Creació del buffer amb les dades dels vèrtexs
    GLuint VBO[2];
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    // Creació del buffer de colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    // Desactivem el VAO
    glBindVertexArray(0);
}

void MyGLWidget::creaBuffersPacman()
{
        float r = 0.15;

    glm::vec3 Colors[30];
    glm::vec3 Vertices[30];
    
    for (int i=0; i<30; i++)
      Colors[i] = COLOR_GROC;

    int i=0;

    // Sector 1
    Vertices[i++] = glm::vec3(0.0, 0.0, 0.0);
    Vertices[i++] = glm::vec3(r,  0.0, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(30.0)), r*sin(glm::radians(30.0)), 0.0);

    // Sector 2
    Vertices[i++] = glm::vec3(0.0,  0.0 , 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(30.0)), r*sin(glm::radians(30.0)), 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(60.0)), r*sin(glm::radians(60.0)), 0.0);

    // Sector 3
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(60.0)), r*sin(glm::radians(60.0)), 0.0);
    Vertices[i++] = glm::vec3(0.0, r, 0.0);

    // Sector 4
    Vertices[i++] = glm::vec3( 0.0, 0.0, 0.0);
    Vertices[i++] = glm::vec3(0.0, r, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(120.0)), r*sin(glm::radians(120.0)), 0.0);

    // Sector 5
    Vertices[i++] = glm::vec3(0.0,  0.0, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(120.0)), r*sin(glm::radians(120.0)), 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(150.0)), r*sin(glm::radians(150.0)), 0.0);

    // Sector 6
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0); 
    Vertices[i++] = glm::vec3(r*cos(glm::radians(210.0)), r*sin(glm::radians(210.0)), 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(240.0)), r*sin(glm::radians(240.0)), 0.0);

    // Sector 7
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0); 
    Vertices[i++] = glm::vec3(r*cos(glm::radians(240.0)), r*sin(glm::radians(240.0)), 0.0);
    Vertices[i++] = glm::vec3(0.0, -r, 0.0);

    // Sector 8
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0); 
    Vertices[i++] = glm::vec3(0.0, -r, 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(300.0)), r*sin(glm::radians(300.0)), 0.0);

    // Sector 9
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0); 
    Vertices[i++] = glm::vec3(r*cos(glm::radians(300.0)), r*sin(glm::radians(300.0)), 0.0);
    Vertices[i++] = glm::vec3(r*cos(glm::radians(330.0)), r*sin(glm::radians(330.0)), 0.0);

    // Sector 10
    Vertices[i++] = glm::vec3( 0.0,  0.0, 0.0); 
    Vertices[i++] = glm::vec3(r*cos(glm::radians(330.0)), r*sin(glm::radians(330.0)), 0.0);
    Vertices[i++] = glm::vec3(r, 0.0, 0.0);


    // Creació del Vertex Array Object (VAO) que usarem per pintar
    glGenVertexArrays(1, &VAO_Pacman);
    glBindVertexArray(VAO_Pacman);

    // Creació del buffer amb les dades dels vèrtexs
    GLuint VBO[2];
    glGenBuffers(2, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
    // Activem l'atribut que farem servir per vèrtex (només el 0 en aquest cas)
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    // Creació del buffer de colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Colors), Colors, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

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
  colorLoc =  glGetAttribLocation (program->programId(), "color");
  TGLoc =  glGetUniformLocation(program->programId(), "TG");
}
