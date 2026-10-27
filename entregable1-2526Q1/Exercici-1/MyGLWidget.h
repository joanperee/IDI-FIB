#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
  Q_OBJECT

  public:
    MyGLWidget (QWidget *parent=0);
    ~MyGLWidget ();
    
  protected:
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();

    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    // resize - Es cridat quan canvia la mida del widget
    virtual void resizeGL (int width, int height);  

    // keyPressEvent - Es cridat quan es prem una tecla
     virtual void keyPressEvent (QKeyEvent *event);

  private:
    //-------------------------------------------------
    // Funcions generals de pintat per objectes

    void pintaParet();
    void pintaPacman();
    void pintaBoleta();
    //-------------------------------------------------
    //  Creació de buffers
    void creaBuffers ();        
    void creaBuffersPacman();
    void creaBuffersBoleta();
    void creaBuffersParet();

    //-------------------------------------------------
    // Funcions de transformació pels objectes
    void modelTransformBoleta (glm::vec3 pos);
    void modelTransformPacman (float angle);
    void modelTransformParet (glm::vec3 escala, glm::vec3 pos);

    //-------------------------------------------------
    void carregaShaders ();

    bool comprovaSiParet (int pX, int pY);

    //-------------------------------------------------
    // attribute locations
    GLuint vertexLoc, colorLoc;
    // uniforms
    GLuint TGLoc;
    
    // Program
    QOpenGLShaderProgram *program;

    GLuint VAO_Pacman, VAO_Boleta, VAO_Paret;
    GLint ample, alt;
    glm::vec3 COLOR_BLANC=glm::vec3(1.0,1.0,1.0);
    glm::vec3 COLOR_BLAU=glm::vec3(48.0/255,58.0/255,158.0/255);
    glm::vec3 COLOR_GROC=glm::vec3(239.0/255,251.0/255,38.0/255);
    
    //status
    int posX, posY = 0;  // posicions enteres de la graella (de -2 a 2)
    int pcmX, pcmY = 0;   // posició (x, y) del PacMan sobre la graella
    int angleRotacio = 0; // angle de la boca del PacMan
};
