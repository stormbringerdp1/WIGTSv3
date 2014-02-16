#include "MEkranoplanGL.h"
  #include "funcs.h"
  #include <QStatusBar>

#include <QOpenGLShader>
#include <QImage>

#include <math.h>
#include <locale.h>

#include <QMessageBox>
  #include <QGraphicsOpacityEffect>

//============================================================================================
MEkranoplanGL::MEkranoplanGL(QWidget *parent)
            : QGLWidget(parent), //, 0, Qt::Widget)
              PitchAngle(0.0), RollAngle(0.0)//,
//              PitchAxis(0.0, 0.0, 1.0), RollAxis(1.0, 0.0, 0.0)
{
//  PosPoint = QPoint(20,20);
//  RotationMatrix4x4.translate(0.0, 0.0, -5.0);
/*
setWindowFlags(Qt::FramelessWindowHint);  setAttribute(Qt::WA_TranslucentBackground);
setAutoFillBackground(false);
setStyleSheet(QLatin1String("background: transparent;"));
setWindowOpacity(0.5);
*/

//setAttribute(Qt::WA_TranslucentBackground,true);
/*
setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
setWindowOpacity(0.5);
bool t=testAttribute ( Qt::WA_TranslucentBackground);
qDebug()<<"transparency"<<t;
*/
/*
setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
MARGINS m;
m.cxLeftWidth = -1;
m.cxRightWidth = -1;
m.cyBottomHeight = -1;
m.cyTopHeight = -1;
DwmExtendFrameIntoClientArea((HWND)winId(), &m);
*/

//IsReadyDraw = true;
}
//--------------------------------------------------------------------------------------------
MEkranoplanGL::~MEkranoplanGL()
{
    deleteTexture(texture);
}
//--------------------------------------------------------------------------------------------
/*
void MEkranoplanGL::paintEvent(QPaintEvent* event)
{
  QGLWidget::paintEvent(event);
//--
}
*/
//--------------------------------------------------------------------------------------------
bool MEkranoplanGL::event(QEvent* event)
{
  bool b = QGLWidget::event(event); //catch different events
//--
  if(event->type() == QEvent::Polish) {//Polish is caught
    setObjectName(QStringLiteral("MEkranoplanGL"));
//    setFrameShape(QFrame::Box);
    setGeometry(QRect(0, 170, 150, 150));
//++    setGeometry(QRect(0, 0, 320, 320));
//    setGeometry(QRect(0, 0, 20, 20));
//      connect(PScrollBar, SIGNAL(valueChanged(int)), this, SLOT(SliderMoved(int)));
//QMessageBox msgBox; msgBox.setText("event->type() == QEvent::Polish");   msgBox.exec();
//    setWindowOpacity(0.5);
  }

//  if(event->type() == QEvent::Move) {
//    setGeometry(QRect(20, 20, 300, 300));
//  }
//setWindowOpacity(0.1);

  return b;
}
//--------------------------------------------------------------------------------------------
/*
void MEkranoplanGL::moveEvent(QMoveEvent* event)
{
  QGLWidget::moveEvent(event);
//--
  if(mapToParent(event->pos()) != PosPoint) {
QString s; s.sprintf("mapToParent(event->pos()).x() = %d,  mapToParent(event->pos()).y() = %d",
                      mapToParent(event->pos()).x(),       mapToParent(event->pos()).y());
QMessageBox msgBox;  msgBox.setText(s);   msgBox.exec();
    setGeometry(QRect(PosPoint, QSize(300, 300)));
msgBox.setText("2");   msgBox.exec();
  }
  else {
QString s; s.sprintf("mapToParent(event->pos()).x() = %d,  mapToParent(event->pos()).y() = %d",
                      mapToParent(event->pos()).x(),       mapToParent(event->pos()).y());
QMessageBox msgBox;  msgBox.setText(s);   msgBox.exec();
msgBox.setText("3");   msgBox.exec();
  }
}
*/
//--------------------------------------------------------------------------------------------
void MEkranoplanGL::initializeGL()
{
//-    initializeGLFunctions();
  initializeOpenGLFunctions();
//-  qglClearColor(Qt::black);
//qglClearColor(QColor(127,127,127, 127));
qglClearColor(QColor(0,0,0, 255));

/*
glEnable(GL_BLEND); glEnable(GL_ALPHA_TEST);

//glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

glBlendColor(1.0f,1.0f,1.0f, 0.0f);
glBlendFuncSeparate(1.0f,1.0f,1.0f, 0.0f);

//setWindowFlags(Qt::FramelessWindowHint);  setAttribute(Qt::WA_TranslucentBackground);

//qglClearColor(QColor(127,127,127, 127));
//setAutoFillBackground(false);
glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
setWindowOpacity(0.0);

//setOpacity(0.3);
//setStyleSheet(QLatin1String("background: transparent;"));

qglColor(overlayContext()->overlayTransparentColor());

//glClearColor(0.5f,0.5f,0.5f, 0.0f);
qglClearColor(overlayContext()->overlayTransparentColor());
//glBlendColor(0.5,0.5,0.5, 0.5);
*/

/*
setAttribute(Qt::WA_TranslucentBackground,true);
setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
setWindowOpacity(0.1);
bool t=testAttribute(Qt::WA_TranslucentBackground);
*/
/*
QLinearGradient alphaGradient(QPoint(0.0,0.0), QPoint(0.0,100.0));
alphaGradient.setColorAt(0.0, Qt::transparent);
alphaGradient.setColorAt(0.5, Qt::black);
alphaGradient.setColorAt(1.0, Qt::transparent);
QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect;
effect->setOpacity(0.5);//setOpacityMask(alphaGradient);
//setGraphicsEffect(effect);

//glColor4f(0.5f, 0.0f, 0.8f, 0.5f);
*/

//qglColor(QColor(127,127,127, 127));
//setStyleSheet("background-color: rgba(0,0,0, 0)");


  InitShaders();
  InitTextures();

  // Enable depth buffer
  glEnable(GL_DEPTH_TEST);

  // Enable back face culling
  glEnable(GL_CULL_FACE);

//-    geometries.init();
  Ekranoplan.Init();

    // Use QBasicTimer because its faster than QTimer
//-    timer.start(12, this);

//move(-300,0);

//setVisible(false);
//-------------------------------------
/*
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    QOpenGLShader *vshader = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vshader->compileSourceCode(
        "attribute highp vec4 vertex;"
        "attribute mediump vec3 normal;"
        "uniform mediump mat4 matrix;"
        "uniform lowp vec4 sourceColor;"
        "varying mediump vec4 color;"
        "void main(void)"
        "{"
        "    vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));"
        "    float angle = max(dot(normal, toLight), 0.0);"
        "    vec3 col = sourceColor.rgb;"
        "    color = vec4(col * 0.2 + col * 0.8 * angle, 1.0);"
        "    color = clamp(color, 0.0, 1.0);"
        "    gl_Position = matrix * vertex;"
        "}");

    QOpenGLShader *fshader = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fshader->compileSourceCode(
        "varying mediump vec4 color;"
        "void main(void)"
        "{"
        "    gl_FragColor = color;"
        "}");

    m_program = new QOpenGLShaderProgram(this);
    m_program->addShader(vshader);
    m_program->addShader(fshader);
    m_program->link();

    vertexAttr = m_program->attributeLocation("vertex");
    normalAttr = m_program->attributeLocation("normal");
    matrixUniform = m_program->uniformLocation("matrix");
    colorUniform = m_program->uniformLocation("sourceColor");

    m_fAngle = 0;
    createGeometry();
*/
}
//--------------------------------------------------------------------------------------------
void MEkranoplanGL::InitShaders()
{
  QMessageBox msgBox;// msgBox.setText("void MMEkranoplanGLWidget::InitShaders()\nBEGIN");   msgBox.exec();

    // Override system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    // Compile vertex shader

//-    if (!program.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl"))
  if(!ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl")) {
    close();
    msgBox.setText("void MMEkranoplanGLWidget::InitShaders()\nShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex) == FALSE");   msgBox.exec();
  }

    // Compile fragment shader
//-    if (!program.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl"))
  if(!ShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl")) {
    close();
    msgBox.setText("void MMEkranoplanGLWidget::InitShaders()\nShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment) == FALSE");   msgBox.exec();
  }

    // Link shader pipeline
//-    if (!program.link())
  if(!ShaderProgram.link()) {
    close();
    msgBox.setText("void MMEkranoplanGLWidget::InitShaders()\nShaderProgram.link() == FALSE");   msgBox.exec();
  }

    // Bind shader pipeline for use
//-    if (!program.bind())
  if(!ShaderProgram.bind()) {
    close();
    msgBox.setText("void MMEkranoplanGLWidget::InitShaders()\nShaderProgram.bind() == FALSE");   msgBox.exec();
  }

    // Restore system locale
    setlocale(LC_ALL, "");

//msgBox.setText("void MMEkranoplanGLWidget::InitShaders()\nEND");   msgBox.exec();
}
//--------------------------------------------------------------------------------------------
void MEkranoplanGL::InitTextures()
{
    // Load cube.png image
    glEnable(GL_TEXTURE_2D);
//-    texture = bindTexture(QImage(":/cube.png"));
    texture = bindTexture(QImage(":/Texture.png"));

    // Set nearest filtering mode for texture minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Set bilinear filtering mode for texture magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
//--------------------------------------------------------------------------------------------
void MEkranoplanGL::resizeGL(int w, int h)
{
//  move(20,20);
//  setGeometry(20,20, 300, 300);

    // Set OpenGL viewport to cover whole widget
    glViewport(0, 0, (GLint)w, (GLint)h);

    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 28.0;//45.0;
//    const qreal zNear = 900.0, zFar = 2100.0, fov = 40.0;//45.0;
//    const qreal zNear = 0.1, zFar = 0.2, fov = 30.0;//45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
//    projection.ortho(-1.0,1.0, -1.0,1.0, zNear,zFar);
//    projection.ortho((QRectF(5.0,5.0, 10.0,10.0));
}
//--------------------------------------------------------------------------------------------
//void MEkranoplanGL::resizeOverlayGL(int width, int height)
//{
//  resizeGL(width, height);
//}
//--------------------------------------------------------------------------------------------
void MEkranoplanGL::paintGL()
{
//setVisible(false);

//setAttribute(Qt::WA_TranslucentBackground,true);
//setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
//setWindowOpacity(0.5);
//bool t=testAttribute ( Qt::WA_TranslucentBackground);
//qDebug()<<"transparency"<<t;


//glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
//qglColor(QColor(127,127,127, 0));
//setStyleSheet("background-color: rgba(127,127,127, 0)");

    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
//    matrix.translate(0.0, 0.0, -3.0);
//    matrix.translate(0.0, 0.0, -1500.0);
    matrix.rotate(RotationQuaternion);
//  RotationMatrix4x4.translate(0.0, 0.0, -5.0);
//  RotationMatrix4x4.rotate(RotationQuaternion);

    // Set modelview-projection matrix
//-    program.setUniformValue("mvp_matrix", projection * matrix);
    ShaderProgram.setUniformValue("mvp_matrix", projection * matrix);
//    ShaderProgram.setUniformValue("mvp_matrix", projection * RotationMatrix4x4);

//  RotationMatrix4x4.translate(0.0, 0.0, 5.0);
//! [6]

    // Use texture unit 0 which contains cube.png
//-    program.setUniformValue("texture", 0);
    ShaderProgram.setUniformValue("texture", 0);

//glColor4f(1.0f, 1.0f, 1.0f, 0.5f);


  ShaderProgram.setUniformValue("rollAngle", RollAngle); // for Light


    // Draw cube geometry
//-    geometries.drawCubeGeometry(&program);
    Ekranoplan.Draw(&ShaderProgram);

//IsReadyDraw = TRUE;
}
//--------------------------------------------------------------------------------------------
/*+
void MEkranoplanGL::SlotSetPitchAngle(int value)
{
  float angle = ((float)value)/180.0*M_PI;   float dangle2 = (angle-M_PI-PitchAngle)/2.0;
  QQuaternion quaternion = QQuaternion(sin(dangle2), cos(dangle2)*PitchAxis).normalized();
  RollAxis = quaternion.rotatedVector(RollAxis);
//  RotationQuaternion = (RotationQuaternion*quaternion).normalized();
  RotationQuaternion = (quaternion*RotationQuaternion).normalized();
  PitchAngle = angle;

//if(IsReadyDraw)  {
//  IsReadyDraw = false;

  updateGL();
//}
//QMessageBox msgBox; msgBox.setText("void MEkranoplanGL::SlotSetPitchAngle(int value)");   msgBox.exec();
}
//--------------------------------------------------------------------------------------------
void MEkranoplanGL::SlotSetRollAngle(int value)
{
  float angle = ((float)value)/180.0*M_PI;   float dangle2 = (angle-M_PI-RollAngle)/2.0;
//= см. http://www.gamedev.ru/articles/?id=30129:
  QQuaternion quaternion = QQuaternion(sin(dangle2), cos(dangle2)*RollAxis).normalized();
//QVector3D axisZnew = RotationQuaternion.rotatedVector(RollAxis);
//QString s; s.sprintf("axisZnew.x() = %.3f,  axisZnew.y() = %.3f, axisZnew.z() = %.3f", axisZnew.x(), axisZnew.y(), axisZnew.z());
//GetPMainWnd()->statusBar()->showMessage(s);
  PitchAxis = quaternion.rotatedVector(PitchAxis);
//  RotationQuaternion = (RotationQuaternion*quaternion).normalized();
  RotationQuaternion = (quaternion*RotationQuaternion).normalized();
  RollAngle = angle;

//if(IsReadyDraw)  {
//  IsReadyDraw = false;

  updateGL();
//}
}
*/
//--------------------------------------------------------------------------------------------
void MEkranoplanGL::SetQuaternion(QQuaternion* pQuaternion)
{
  RotationQuaternion = pQuaternion->normalized();

  updateGL();
}
//--------------------------------------------------------------------------------------------
