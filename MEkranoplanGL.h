#ifndef MEKRANOPLANGLWIDGET_H
#define MEKRANOPLANGLWIDGET_H

//#include <QWidget>
#include <QGLWidget>
#include <QEvent>
#include <QMoveEvent>
//-#include <QGLFunctions>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>
#include <QVector2D>
#include <QVector3D>
#include <QQuaternion>
//#include <QBasicTimer>
//-#include <QGLShaderProgram>

#include "MEkranoplan.h"

//-class GeometryEngine;
//class MEkranoplan;

//============================================================================================
class MEkranoplanGL : public QGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MEkranoplanGL(QWidget *parent = 0);
  virtual ~MEkranoplanGL();


protected:
  virtual bool event(QEvent* event);
//  virtual void moveEvent(QMoveEvent* event);

  virtual void initializeGL();
  virtual void resizeGL(int w, int h);
  virtual void paintGL();

//  virtual void paintEvent(QPaintEvent* event);

protected:
//-    void initShaders();
//-    void initTextures();
  void InitShaders();
  void InitTextures();

private:

//bool IsReadyDraw;

//  QPoint  PosPoint;
  float PitchAngle;     float RollAngle;
//  QVector3D PitchAxis;  QVector3D RollAxis;

//    QBasicTimer timer;
//-    QGLShaderProgram program;
  QOpenGLShaderProgram ShaderProgram;
//-    GeometryEngine geometries;
  MEkranoplan Ekranoplan;

    GLuint texture;

    QMatrix4x4 projection;
//    QVector2D mousePressPosition;
//-    QVector3D rotationAxis;
//    QVector3D RotationAxis;
//    qreal angularSpeed;
//-    QQuaternion rotation;
    QQuaternion RotationQuaternion;
  QMatrix4x4 RotationMatrix4x4;

public:
  void SetQuaternion(QQuaternion* pQuaternion);

signals:

public slots:
//  void SlotSetPitchAngle(int value);
//  void SlotSetRollAngle(int value);
};
//============================================================================================
#endif // MEKRANOPLANGLWIDGET_H
