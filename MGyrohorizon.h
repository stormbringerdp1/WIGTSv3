#ifndef MGYROHORIZON_H
#define MGYROHORIZON_H

#include <QWidget>
  #include <QPaintEvent>
//  #include <QGenericMatrix>
//  #include <QSlider>
//#include <QGraphicsView>
//#include <QGraphicsScene>
//#include <QGraphicsProxyWidget>

#include "MEkranoplanGL.h"

//============================================================================================
class MGyrohorizon : public QWidget
{
    Q_OBJECT
public:
//    explicit MGyrohorizon(QWidget *parent = 0);
//  explicit MGyrohorizon(QWidget *parent, QSlider* pSliderPitch, QSlider* pSliderRoll);
  explicit MGyrohorizon(QWidget *parent);
  virtual ~MGyrohorizon();

protected:
  virtual void paintEvent(QPaintEvent * event);

private:

//  QGraphicsScene* PGraphicsScene;
  MEkranoplanGL* PEkranoplanGL;
//  QGraphicsProxyWidget* PEkranoplanProxyWidget;

//QSlider* PSliderPitch;
//QSlider* PSliderRoll;

  qreal Width;  qreal Height;
  qreal rRoll;

  qreal WidthHalf;
  qreal HeightHalf;  qreal AngleHeightHalf;  qreal AngleHeightHalfVisible;
  qreal HOneDegreeAngle;

  qreal MaxDim;  qreal MaxDimHalf;  qreal HeightHalfVisible;
  qreal H1;  qreal H2;


  QColor ColorSky0;            QColor ColorSky1;            QColor ColorSky2;
  QColor ColorGround0;         QColor ColorGround1;         QColor ColorGround2;
  QColor ColorPitch;           QColor ColorRoll;
  QColor ColorStaticBalance0;  QColor ColorStaticBalance1;  QColor ColorStaticTriangle;  QColor ColorStaticBalanceOutline;

//QMatrix3x3 T;

  qreal PitchAngle;
//qreal PitchAngle0;
  qreal RollAngle;
//qreal RollAngle0;
//bool  IsUpDawn;
//bool   IsSliderPitchPressed;

//bool IsReadyRedraw;

public:
  void SetPEkranoplanGL(MEkranoplanGL* pEkranoplanGL) { PEkranoplanGL = pEkranoplanGL; }
  void SetQuaternion(QQuaternion* pQuaternion);

//  void SetPitchAngle(int value);
//  void SetRollAngle(int value);
  void SetPitchRollAngles(float pitch, float roll);

signals:

public slots:
//  void SlotSetPitchAngle(int value);
//  void SlotSetRollAngle(int value);

//  void SliderPitchPressed();
//  void SliderPitchReleased();
};
//============================================================================================
#endif // MGYROHORIZON_H
