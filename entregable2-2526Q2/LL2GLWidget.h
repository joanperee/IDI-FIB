#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "model.h"


class LL2GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core 
{
  Q_OBJECT

  public:
    LL2GLWidget (QWidget *parent=0);
    ~LL2GLWidget ();

  protected:
    // initializeGL - Aqui incluim les inicialitzacions del context gràfic.
    virtual void initializeGL ( );
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );
    // resizeGL - És cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);
    // keyPressEvent - És cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    // mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event
    // corresponent de ratolí
    virtual void mousePressEvent (QMouseEvent *event);
    virtual void mouseReleaseEvent (QMouseEvent *event);
    virtual void mouseMoveEvent (QMouseEvent *event);

    // iniEscena - Aqui incluim les inicialitzacions de l'escena
    virtual void iniEscena ();
    // iniCamera - Aqui incluim les inicialitzacions de la camera
    virtual void iniCamera ();    
    
    // viewTransform i projecTransform - Es fan servir per construir i enviar als shader les matrius de càmera (View i Projection respectivament).
    virtual void viewTransform ();
    virtual void projectTransform ();
    
    virtual void modelTransformCub (float alcada, float angle, float radi, float z);
    virtual void modelTransformFantasma ();

    void calculaCapsaModelFantasma ();

    // creaBuffersCub - Inicialitzem el VAO i els VBO d'un model fet a mà que representa un cub
    void creaBuffersCub ();
    // creaBuffersModels - Carreguem els fitxers obj i fem la inicialització dels diferents VAOS i VBOs
    void creaBuffersFantasma ();

    // carregaShaders - Carreguem els shaders, els compilem i els linkem. També busquem els uniform locations que fem servir.
    void carregaShaders ();
    
    // attribute locations
    GLuint vertexLoc, colorLoc;

    // uniform locations
    GLuint transLoc, viewLoc, projLoc;

    // VAO names
    GLuint VAO_Fantasma, VAO_Cub;

    // Program
    QOpenGLShaderProgram *program;

    // Viewport
    GLint ample, alt;

    // Mouse interaction
    typedef  enum {NONE, ROTATE} InteractiveAction;
    InteractiveAction DoingInteractive;
    int xClick, yClick;
    float factorAngleX, factorAngleY;

    // Model, capsa contenidora i escala
    Model fantasma;
    glm::vec3 centreBaseFantasma;
    float escalaFantasma;        

    // Internal vars
    float radiEscena;
    float ra=1;

    // configuració alçades cubs per rodes
    int alcades[3][72] = {
{0,0,0,4,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,2,4,4,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,3,3,0,0,3,0,0,0,0,0,0,4,4,4,0,0,0,0,0,4,0},
		{0,0,3,0,0,0,0,0,4,5,5,0,0,0,3,3,4,0,0,0,0,4,3,5,0,0,0,0,0,0,0,0,0,2,3,4,0,0,6,4,5,0,0,0,0,0,0,6,5,4,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,4,4,0,0,0,0},
		{0,0,0,0,0,5,0,0,0,0,0,0,0,5,0,0,0,0,0,4,4,4,0,0,4,0,0,2,3,4,0,0,0,0,0,0,0,5,0,0,4,4,4,0,4,4,4,5,0,0,0,0,4,5,5,0,6,5,0,0,5,5,5,0,4,0,0,0,5,5,0,0}
	     };
};

