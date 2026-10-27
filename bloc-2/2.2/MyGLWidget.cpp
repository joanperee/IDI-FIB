// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__, __FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

MyGLWidget::~MyGLWidget()
{
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

void MyGLWidget::initializeGL()
{
    Bl2GLWidget::initializeGL();
    glEnable(GL_DEPTH_TEST);
    calculaCapsaModel();
    ini_escena();
    ini_camera();
}

void MyGLWidget::ini_escena()
{
    pmin = glm::vec3(-2.5, 0, -2.5);
    pmax = glm::vec3(2.5, 4.0, 2.5);
    centreEscena = glm::vec3(pmin + pmax)/2.f;
    radiEscena = glm::distance(pmin, pmax)/2.f;
}

void MyGLWidget::ini_camera()
{
    // Inicialització dels paràmetres de càmera
    OBS = centreEscena + glm::vec3(0, 0, 2*radiEscena); 
    VRP = centreEscena; 
    UP = glm::vec3(0, 1, 0); 

    FOV = glm::radians(60.f); 
    ra = 1.0f;                
    zNear = radiEscena;
    zFar = radiEscena*3.f;

    l = -radiEscena;
    r = radiEscena;
    t = radiEscena;
    b = -radiEscena;

    camOrto = false;

    angleX = 0.0;
    angleY = 0.0;

    // Calcular les matrius amb aquests valors
    projectTransform();
    viewTransform();
}

void MyGLWidget::calculaCapsaModel()
{
    // Càlcul capsa contenidora i valors transformacions inicials
    float minx, miny, minz, maxx, maxy, maxz;
    minx = maxx = m.vertices()[0];
    miny = maxy = m.vertices()[1];
    minz = maxz = m.vertices()[2];
    for (unsigned int i = 3; i < m.vertices().size(); i += 3)
    {
        if (m.vertices()[i + 0] < minx)
            minx = m.vertices()[i + 0];
        if (m.vertices()[i + 0] > maxx)
            maxx = m.vertices()[i + 0];
        if (m.vertices()[i + 1] < miny)
            miny = m.vertices()[i + 1];
        if (m.vertices()[i + 1] > maxy)
            maxy = m.vertices()[i + 1];
        if (m.vertices()[i + 2] < minz)
            minz = m.vertices()[i + 2];
        if (m.vertices()[i + 2] > maxz)
            maxz = m.vertices()[i + 2];
    }

    escalaModel = 4.0/(maxy - miny);
    centreBase = glm::vec3((minx + maxx)/2, miny, (minz + maxz)/2);
}

// Configuració de la càmera 3D
void MyGLWidget::projectTransform()
{
    glm::mat4 Proj = glm::mat4(1.0);
    if (not camOrto)
    {
        Proj = glm::perspective(FOV, ra, zNear, zFar);
    }
    else
    {
        Proj = glm::ortho(l, r, b, t, zNear, zFar);
    }
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}

// Configuració de l'observador
void MyGLWidget::viewTransform()
{
    glm::mat4 View = glm::mat4(1.0);
    // glm::lookAt(OBS, VRP, UP);
    
    View = glm::translate(View, glm::vec3(0, 0, -2*radiEscena));
    View = glm::rotate(View, angleX, glm::vec3(1, 0, 0));
    View = glm::rotate(View, angleY, glm::vec3(0, 1, 0));
    View = glm::translate(View, -VRP);

    glm::translate
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::paintGL()
{

    // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
    // useu els paràmetres que considereu (els que hi ha són els de per defecte)
    //  glViewport (0, 0, ample, alt);

    // Esborrem el frame-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Pintar el terra
    modelTransformTerra();
    glBindVertexArray(VAO_Terra);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Pintar el homer
    modelTransformHomer();
    glBindVertexArray(VAO_Patricio);
    // #cares*3, ja que cada cara és un triangle (3 vèrtexs)
    glDrawArrays(GL_TRIANGLES, 0, m.faces().size() * 3);

    glBindVertexArray(0);
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
    makeCurrent();
    switch (event->key())
    {
    case Qt::Key_S:
    { // escalar a més gran
        scale += 0.05;
        break;
    }
    case Qt::Key_D:
    { // escalar a més petit
        scale -= 0.05;
        break;
    }
    case Qt::Key_R:
    {
        angleRotacio += glm::radians(45.f);
        break;
    }
    case Qt::Key_O:
    {
        camOrto = not camOrto;
        projectTransform();
        viewTransform();
        break;
    }
    default:
        event->ignore();
        break;
    }
    update();
}

// Transformació Terra (no es fa res i està centrat a l'origen)
void MyGLWidget::modelTransformTerra()
{
    glm::mat4 transform(1.0f);
    transform = glm::scale(transform, glm::vec3(scale));
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

// Transformació del Homer
void MyGLWidget::modelTransformHomer()
{
    glm::mat4 transform(1.0f);
    transform = glm::rotate(transform, angleRotacio, glm::vec3(0, 1, 0));
    transform = glm::scale(transform, glm::vec3(scale));

    // Euler per visualitzar qualsevol objecte
    transform = glm::scale(transform, glm::vec3(escalaModel));
    transform = glm::translate(transform, -centreBase);

    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &transform[0][0]);
}

void MyGLWidget::carregaShaders()
{
    Bl2GLWidget::carregaShaders();
    projLoc = glGetUniformLocation(program->programId(), "proj");
    viewLoc = glGetUniformLocation(program->programId(), "view");
}

void MyGLWidget::creaBuffers()
{
    Bl2GLWidget::creaBuffers();

    // ----------------------------------------------------
    // (1) BUFFER DEL HOMER
    m.load("./models/Patricio.obj");

    // Creació del Vertex Array Object per pintar
    glGenVertexArrays(1, &VAO_Patricio);
    glBindVertexArray(VAO_Patricio);

    GLuint VBO_Patricio[2];
    glGenBuffers(2, VBO_Patricio);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[0]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * m.faces().size() * 3 * 3,
                 m.VBO_vertices(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    // Color buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Patricio[1]);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(GLfloat) * m.faces().size() * 3 * 3,
                 m.VBO_matdiff(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    // ----------------------------------------------------
    // (2) BUFFER DEL TERRA
    glm::vec3 terraVerts[6] = {
        glm::vec3(-2.5, 0.0, 2.5),
        glm::vec3(2.5, 0.0, 2.5),
        glm::vec3(-2.5, 0.0, -2.5),
        glm::vec3(-2.5, 0.0, -2.5),
        glm::vec3(2.5, 0.0, 2.5),
        glm::vec3(2.5, 0.0, -2.5)};

    glm::vec3 terraColors[6] = {
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0),
        glm::vec3(0, 1, 0)};

    glGenVertexArrays(1, &VAO_Terra);
    glBindVertexArray(VAO_Terra);

    GLuint VBO_Terra[2];
    glGenBuffers(2, VBO_Terra);

    // Buffer de vèrtexs
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(terraVerts), terraVerts, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexLoc);

    // Buffer de colors
    glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(terraColors), terraColors, GL_STATIC_DRAW);
    glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(colorLoc);

    glBindVertexArray(0);
}