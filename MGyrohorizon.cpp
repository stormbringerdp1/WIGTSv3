#include "MGyrohorizon.h"
#include "funcs.h"

#include <QGraphicsView>
#include <QPainter>
#include <QLinearGradient>
#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QBitmap>

//  #include <QStatusBar>
//  #include <QMessageBox>

//  #include <math.h>

//============================================================================================
//void DrawText(QPainter& painter, qreal dopangle, const qreal xoff, const qreal yoff, const QString& text)
//void DrawText(QPainter& painter, const qreal xoff, const qreal yoff, const QString& text)
void DrawText(QPainter& painter, const qreal xoff, const qreal yoff, const qreal angle)
{
  QString text;  text.sprintf("%.0f",angle);
//  painter.rotate(dopangle);
  QRectF rectF = painter.boundingRect(QRectF(0.0,0.0, 500.0,500.0), text, QTextOption(Qt::AlignCenter));
//  painter.drawText(QRectF(-rectF.width()/2.0-0.5 + xoff, -rectF.height()/2.0-0.5 + yoff, rectF.width(),rectF.height()), text, QTextOption(Qt::AlignHCenter | Qt::AlignBottom));
//  painter.drawText(QRectF(-rectF.width()/2.0-0.5 + xoff, -rectF.height() + yoff, rectF.width(),rectF.height()), text, QTextOption(Qt::AlignCenter));
  painter.drawText(QRectF(-rectF.width()/2.0-0.5 + xoff, -rectF.height()/2.0-0.5 + yoff, rectF.width(),rectF.height()), text, QTextOption(Qt::AlignCenter));
}
//============================================================================================
MGyrohorizon::MGyrohorizon(QWidget *parent)//, QSlider *pSliderPitch, QSlider *pSliderRoll) :
            : QWidget(parent) //, PSliderPitch(pSliderPitch), PSliderRoll(pSliderRoll)
{
//+  PGraphicsScene = qobject_cast<QGraphicsView*>(parent)->scene();

//T.setToIdentity();

  Width = 320.0;
  Height = 320.0;
  rRoll = 125.0;

  WidthHalf = Width/2.0;
  HeightHalf = Height/2.0;  AngleHeightHalf = 40.0;   AngleHeightHalfVisible = 25.0;
  HOneDegreeAngle = HeightHalf/AngleHeightHalf;

  MaxDim = qMax(Width,Height)*qSqrt(2.0);  MaxDimHalf = MaxDim/2.0;
  HeightHalfVisible = HeightHalf/AngleHeightHalf*AngleHeightHalfVisible;

  H1 = HOneDegreeAngle*AngleHeightHalf;
  H2 = HOneDegreeAngle*(90.0-AngleHeightHalf);


  ColorSky2 = QColor(0,0,80, 255);
  ColorSky1 = QColor(0,0,100, 255);
  ColorSky0 = QColor(80,180,255, 255);
  ColorGround0 = QColor(90,170,110, 255);
  ColorGround1 = QColor(90,17,11, 255);
  ColorGround2 = QColor(0,17,11, 255);

  ColorPitch = QColor(255,255,255, 255);
  ColorRoll = QColor(255,255,255, 255);

  ColorStaticBalance0 = QColor(255,255,0, 255);
  ColorStaticBalance1 = QColor(88,88,0, 255);
  ColorStaticTriangle = QColor(255,255,0, 255);
  ColorStaticBalanceOutline = QColor(0,0,0, 255);

  PitchAngle = 0.0;
//PitchAngle0 = 0.0;
  RollAngle = 0.0;
//RollAngle0 = 0.0;
//IsUpDawn = false;
//IsSliderPitchPressed = false;

//IsReadyRedraw = true;
}
//--------------------------------------------------------------------------------------------
MGyrohorizon::~MGyrohorizon()
{
}
//--------------------------------------------------------------------------------------------
void MGyrohorizon::paintEvent(QPaintEvent * event)
{
//setStyleSheet(QLatin1String("background: transparent;"));

//  QPixmap pixmap(400,300);  pixmap.fill(Qt::white);
//  QPainter paint(&pixmap);
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);

  QLinearGradient linearGrad;
  QPointF mpointsF[5];
  qreal yh;

/*===========  First Variant  ===========

  qreal hPitchAngle = HeightHalf/AngleHeightHalf*PitchAngle;


//qreal cs = qCos(RollAngle/180.0*M_PI);   qreal acs = qAbs(cs);
//qreal hPitchAngleCos = hPitchAngle*cs;

//qreal HeightHemiSphere = Height/AngleHeight*90.0;


  painter.translate(WidthHalf,HeightHalf);

//painter.translate(0.0,-hPitchAngle);

  painter.rotate(-RollAngle);

//painter.translate(0.0,hPitchAngle);

//=====  Pitch:  =====


  painter.setPen(Qt::NoPen);

//  bool isUpDawn = false;

//-Sky:

// 0:
  yh = hPitchAngle;
  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-h1);
  linearGrad.setColorAt(0, QColor(80,180,255, 255));
  linearGrad.setColorAt(1, QColor(0,0,100, 255));
  QBrush brushSky1(linearGrad);   painter.setBrush(brushSky1);
  painter.drawRect(-MaxDimHalf,yh+0.5, MaxDim,-h1-1.0);

  yh = hPitchAngle-h1;
  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-h2);
  linearGrad.setColorAt(0, QColor(0,0,100, 255));
  linearGrad.setColorAt(1, QColor(0,0,80, 255));
  QBrush brushSky2(linearGrad);   painter.setBrush(brushSky2);
  painter.drawRect(-MaxDimHalf,yh, MaxDim,-h2-1.0);

//90
  yh = hPitchAngle-h1-h2;
  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-h2);
  linearGrad.setColorAt(0, QColor(0,0,80, 255));
  linearGrad.setColorAt(1, QColor(0,0,100, 255));
  QBrush brushSky3(linearGrad);   painter.setBrush(brushSky3);
  painter.drawRect(-MaxDimHalf,yh, MaxDim,-h2-1.0);

  yh = hPitchAngle-h1-h2-h2;
  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-h1);
  linearGrad.setColorAt(0, QColor(0,0,100, 255));
  linearGrad.setColorAt(1, QColor(80,180,255, 255));
  QBrush brushSky4(linearGrad);   painter.setBrush(brushSky4);
  painter.drawRect(-MaxDimHalf,yh+0.5, MaxDim,-h1-1.0);
//180

//-Ground:

// 0:
  yh = hPitchAngle;
  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+h1);
  linearGrad.setColorAt(0, QColor(90,170,110, 255));
  linearGrad.setColorAt(1, QColor(90,17,11, 255));
  QBrush brushGround1(linearGrad);   painter.setBrush(brushGround1);
  painter.drawRect(-MaxDimHalf,yh-0.5, MaxDim,h1+1.0);

  yh = hPitchAngle+h1;
  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+h2);
  linearGrad.setColorAt(0, QColor(90,17,11, 255));
  linearGrad.setColorAt(1, QColor(0,17,11, 255));
  QBrush brushGround2(linearGrad);   painter.setBrush(brushGround2);
  painter.drawRect(-MaxDimHalf,yh, MaxDim,h2+1.0);

//90:
  yh = hPitchAngle+h1+h2;
  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+h2);
  linearGrad.setColorAt(0, QColor(0,17,11, 255));
  linearGrad.setColorAt(1, QColor(90,17,11, 255));
  QBrush brushGround3(linearGrad);   painter.setBrush(brushGround3);
  painter.drawRect(-MaxDimHalf,yh, MaxDim,h2+1.0);

  yh = hPitchAngle+h1+h2+h2;
  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+h1);
  linearGrad.setColorAt(0, QColor(90,17,11, 255));
  linearGrad.setColorAt(1, QColor(90,170,110, 255));
  QBrush brushGround4(linearGrad);   painter.setBrush(brushGround4);
  painter.drawRect(-MaxDimHalf,yh, MaxDim,h1);
//180


//  if(isUpDawn) { PSliderRoll->setValue(RollAngle+180); }


//painter.translate(0.0,-hPitchAngle);

//painter.rotate(RollAngle);

//painter.translate(0.0,hPitchAngle);


//= Pitch Scale:


  QPen pen(QColor(255,255,255, 255));
  pen.setWidthF(1.0);
//  pen.setCapStyle(Qt::RoundCap);
//  pen.setJoinStyle(Qt::SvgMiterJoin); //Qt::RoundJoin); //Qt::BevelJoin); //Qt::MiterJoin);
  painter.setPen(pen);

//  qreal x,y;
  QVector<QLineF> lines;

//- (2)-degrees:
  qreal y;  bool isHas = false;
  for(int k = -1; k <= 1; k += 2) {
    y = hPitchAngle;
    while(y >=   2.0*(h1+h2)-2.0*HeightHalfVisible)  { y -= 2.0*(h1+h2); }
    while(y <= -(2.0*(h1+h2)-2.0*HeightHalfVisible)) { y += 2.0*(h1+h2); }
    for(int i = 1; i <= 4; i++) {
      y += -2.0*HOneDegreeAngle*k;
      if(qAbs(y) <= HeightHalfVisible) {  isHas = true;
        lines << QLineF(-8.0,y, 8.0,y);
      }
    }
  }
  if(isHas)  painter.drawLines(lines);
  lines.clear();

  pen.setWidthF(1.5);   painter.setPen(pen);

  qreal xoff, yoff;
  qreal angle;

//- 10-degrees:
  mpointsF[0].setX(-24.0);
  mpointsF[1].setX(-24.0);
  mpointsF[2].setX(24.0);
  mpointsF[3].setX(24.0);
  for(int k = -1; k <= 1; k += 2) {
    for(int i = 0; i <= 9; i++) {
      angle = 10.0*i;
      y = hPitchAngle - angle*HOneDegreeAngle*k;
      while(y >=   2.0*(h1+h2)-2.0*HeightHalfVisible)  { y -= 2.0*(h1+h2); }
      while(y <= -(2.0*(h1+h2)-2.0*HeightHalfVisible)) { y += 2.0*(h1+h2); }
      if(qAbs(y) <= HeightHalfVisible) {
        if(i == 0) {
          painter.drawLine(QLineF(-48.0,y, 48.0,y));
        }
        else if(i < 9) {
          mpointsF[0].setY(y + 5.0*k);
          mpointsF[1].setY(y);
          mpointsF[2].setY(y);
          mpointsF[3].setY(y + 5.0*k);
          painter.drawPolyline(mpointsF, 4); //int pointCount)
          DrawText(painter, -24.0-12.0+0.5, y+5.0/2.0*k, angle);
          DrawText(painter,  24.0+12.0+1.0, y+5.0/2.0*k, angle);
        }
        else {
          lines << QLineF(-36.0,y-7.0, -36.0,y+7.0);
          lines << QLineF(-36.0,y,      36.0,y);
          lines << QLineF( 36.0,y-7.0,  36.0,y+7.0);
          painter.drawLines(lines);  lines.clear();
          DrawText(painter, -36.0-12.0+1.0, y, angle);
          DrawText(painter,  36.0+12.0+1.0, y, angle);
        }
      }
    }

  }
//- (15)-degrees:
  for(int k = -1; k <= 1; k += 2) {
    y = hPitchAngle - 10.0*HOneDegreeAngle*(1.0+0.5)*k;
    while(y >=   2.0*(h1+h2)-2.0*HeightHalfVisible)  { y -= 2.0*(h1+h2); }
    while(y <= -(2.0*(h1+h2)-2.0*HeightHalfVisible)) { y += 2.0*(h1+h2); }
    if(qAbs(y) <= HeightHalfVisible)
      painter.drawLine(QLineF(-16.0,y, 16.0,y));
  }


//  QFont font(font());   // font.setStyleStrategy(QFont::NoAntialias);
//  painter.setFont(font);



//=====  Roll:  =====

//painter.rotate(-RollAngle);

  painter.setBrush(QBrush(QColor(255,255,255, 255)));

//- Triangle:
  painter.setPen(Qt::NoPen);
  mpointsF[0].setX(0.0);   mpointsF[0].setY(-rRoll);
  mpointsF[1].setX(-6.5);  mpointsF[1].setY(-rRoll - 11.258); //  11.258 = sqrt(3.0)/2.0 * 13.0
  mpointsF[2].setX(6.5);   mpointsF[2].setY(-rRoll - 11.258);
  painter.drawPolygon(mpointsF,3);

//- Arc:
  pen.setWidthF(1.5);   painter.setPen(pen);
  painter.drawArc(QRectF(-rRoll, -rRoll, 2.0*rRoll, 2.0*rRoll), 30*16, 120*16);


  qreal hs1 = 5.0;
  qreal hs2 = 12.0;  qreal ws2 = 5.0;
  qreal hs3 = 10.0;
  yoff = -rRoll - hs2 - 10.0; //  - 5.0
  angle = 0.0;

  qreal dopangle;  // QString text;

  for(int k = -1; k <= 1; k += 2) {
    xoff = ws2/2.0*k;
//- (5), (10):
    dopangle = 10.0*k;  painter.rotate(dopangle);
    for(int i = 1; i <= 2; i++) {
      painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0,-rRoll-hs1));
      painter.rotate(dopangle);
    }

//- 30, (45), 60, (75):
    dopangle = 15.0*k;  angle = 15.0;
    for(int i = 1; i <= 2; i++) {
// 30, 60:
      angle += dopangle*k;  //  text.sprintf(("%.0f"),angle);
      DrawText(painter, xoff, yoff, angle); //text);
      mpointsF[0].setX(0.0);  mpointsF[0].setY(-rRoll);
      mpointsF[1].setX(0.0);  mpointsF[1].setY(-rRoll-hs2);
      mpointsF[2].setX(ws2*k);  mpointsF[2].setY(-rRoll-hs2);
      painter.drawPolyline(mpointsF, 3);
// (45), (75):
      painter.rotate(dopangle);
      painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0,-rRoll-hs3));

      painter.rotate(dopangle);
      angle += dopangle*k;
    }

//- 90:
    xoff = 1.0;
    angle += dopangle*k;  //  text.sprintf(("%.0f"),angle);
    DrawText(painter, xoff, yoff, angle); //text);
//    painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0, -rRoll-hs2));
//    painter.drawLine(QPointF(-4.0, -rRoll-hs2), QPointF(4.0, -rRoll-hs2));
    lines << QLineF(0.0,-rRoll, 0.0,-rRoll-hs2);
    lines << QLineF(-4.0,-rRoll-hs2, 4.0,-rRoll-hs2);
    painter.drawLines(lines);  lines.clear();

//- 120, 150:
    xoff = -ws2/2.0*k;
    dopangle = 30.0*k;    painter.rotate(dopangle);
    for(int i = 1; i <= 2; i++) {
      angle += dopangle*k;  //  text.sprintf(("%.0f"),angle);
      DrawText(painter, xoff, yoff, angle); //text);
      mpointsF[0].setX(0.0);  mpointsF[0].setY(-rRoll);
      mpointsF[1].setX(0.0);  mpointsF[1].setY(-rRoll-hs2);
      mpointsF[2].setX(-ws2*k);  mpointsF[2].setY(-rRoll-hs2);
      painter.drawPolyline(mpointsF, 3);

      painter.rotate(dopangle);
    }

    if(k == -1)  painter.rotate(180.0);
  }

//- 180:
  xoff = -1.0;
  angle += dopangle;  //  text.sprintf(("%.0f"),angle);
  DrawText(painter, xoff, yoff, angle); //text);
//  painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0,-rRoll-hs2));
//  painter.drawLine(QPointF(-3.0, -rRoll-hs2+4.0), QPointF(3.0, -rRoll-hs2+4.0));
//  painter.drawLine(QPointF(-6.0, -rRoll-hs2), QPointF(6.0, -rRoll-hs2));
  lines << QLineF(0.0,-rRoll, 0.0,-rRoll-hs2);
  lines << QLineF(-3.0,-rRoll-hs2+4.0, 3.0,-rRoll-hs2+4.0);
  lines << QLineF(-6.0,-rRoll-hs2, 6.0,-rRoll-hs2);
  painter.drawLines(lines);  lines.clear();
  painter.rotate(-180.0);

//=====  Static:  =====

  painter.rotate(RollAngle);

  painter.setPen(Qt::NoPen);

//-Balance:

  pen.setColor(Qt::black);
  pen.setWidthF(0.5);   painter.setPen(pen);

  linearGrad.setStart(0.0,    -3.5+1.5);
  linearGrad.setFinalStop(0.0, 3.5);
  linearGrad.setColorAt(0, QColor(255,255,0, 255));
  linearGrad.setColorAt(1, QColor(88,88,0, 255));
  QBrush brushBalance(linearGrad);   painter.setBrush(brushBalance);

//-Left:
  mpointsF[0].setX(-48.0-1.0);           mpointsF[0].setY(0.0);
  mpointsF[1].setX(-48.0-1.0-8.0);       mpointsF[1].setY(-3.5);
  mpointsF[2].setX(-48.0-1.0-8.0-24.0);  mpointsF[2].setY(-3.5);
  mpointsF[3].setX(-48.0-1.0-8.0-24.0);  mpointsF[3].setY(3.5);
  mpointsF[4].setX(-48.0-1.0-8.0);       mpointsF[4].setY(3.5);
  painter.drawPolygon(mpointsF,5);

//-Right:
  mpointsF[0].setX(48.0+1.0);          // mpointsF[0].setY(0.0);
  mpointsF[1].setX(48.0+1.0+8.0);      // mpointsF[1].setY(-3.5);
  mpointsF[2].setX(48.0+1.0+8.0+24.0); // mpointsF[2].setY(-3.5);
  mpointsF[3].setX(48.0+1.0+8.0+24.0); // mpointsF[3].setY(3.5);
  mpointsF[4].setX(48.0+1.0+8.0);      // mpointsF[4].setY(3.5);
  painter.drawPolygon(mpointsF,5);

//-Center:
  linearGrad.setStart(0.0,    0.0);
  linearGrad.setFinalStop(0.0, 12.0+6.0);
  linearGrad.setColorAt(0, QColor(255,255,0, 255));
  linearGrad.setColorAt(1, QColor(88,88,0, 255));
  QBrush brushBalanceCenter(linearGrad);   painter.setBrush(brushBalanceCenter);
  mpointsF[0].setX(0.0);            mpointsF[0].setY(0.0);
  mpointsF[1].setX(-30.0);          mpointsF[1].setY(12.0);
  mpointsF[2].setX(0.0);            mpointsF[2].setY(6.0);
  mpointsF[3].setX(30.0);           mpointsF[3].setY(12.0);
  painter.drawPolygon(mpointsF,4);

//- Triangle:
  painter.setBrush(QBrush(QColor(255,255,0, 255)));
  mpointsF[0].setX(0.0);   mpointsF[0].setY(-rRoll);
  mpointsF[1].setX(6.5);   mpointsF[1].setY(-rRoll + 11.258); //  11.258 = sqrt(3.0)/2.0 * 13.0
  mpointsF[2].setX(-6.5);  mpointsF[2].setY(-rRoll + 11.258);
  painter.drawPolygon(mpointsF,3);
*/

//=============================

//PitchAngle = PitchAngle0;
  bool isUpDawn = false;
  while(PitchAngle < -90.0) { PitchAngle += 180.0;
//  while(PitchAngle < -90.0) { PitchAngle = -180.0 - PitchAngle;
//    PSliderPitch->setValue(PitchAngle);
    isUpDawn = !isUpDawn; //true;
//    IsUpDawn = isUpDawn;
  } //PitchAngle += 180.0; } // hPitchAngle += 2.0*(h1+h2); }
  while(PitchAngle > 90.0)  { PitchAngle -= 180.0;
//  while(PitchAngle > 90.0)  { PitchAngle = 180.0 - PitchAngle;
//    PSliderPitch->setValue(PitchAngle); // PSliderPitch->setTracking(true);
    isUpDawn = !isUpDawn; //true;
//    IsUpDawn = isUpDawn;
  } //PitchAngle -= 180.0; } // hPitchAngle -= 2.0*(h1+h2); }

//RollAngle = RollAngle0;
  if(isUpDawn) {  RollAngle += 180.0;
//    PSliderRoll->setValue(RollAngle);
  }
  while(RollAngle < -180.0) {
    RollAngle += 360.0;
//    PSliderRoll->setValue(RollAngle);
  } //PitchAngle += 180.0; } // hPitchAngle += 2.0*(h1+h2); }
  while(RollAngle > 180.0)  { RollAngle -= 360.0;
//    PSliderRoll->setValue(RollAngle);
  } //PitchAngle -= 180.0; } // hPitchAngle -= 2.0*(h1+h2); }


  qreal hPitchAngle = HeightHalf/AngleHeightHalf*PitchAngle;
  if(isUpDawn) {
//    painter.translate(0.0,-2.0*hPitchAngle);
    hPitchAngle = -hPitchAngle;
  }


//qreal cs = qCos(RollAngle/180.0*M_PI);   qreal acs = qAbs(cs);
//qreal hPitchAngleCos = hPitchAngle*cs;

//qreal HeightHemiSphere = Height/AngleHeight*90.0;


  painter.translate(WidthHalf,HeightHalf);

//  painter.translate(0.0,hPitchAngle);


  painter.rotate(-RollAngle);

//painter.translate(0.0,hPitchAngle);

//=====  Pitch:  =====


  painter.setPen(Qt::NoPen);


//-Sky:

// 0:
  yh = hPitchAngle;
//  yh = 0.0;
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(2.0*(h1+h2)-qSqrt(2.0)*h1)) { yh += 2.0*(h1+h2); }
//  while(yh >=   2.0*(h1+h2)-qSqrt(2.0)*h1)  { yh -= 2.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-H1);
  linearGrad.setColorAt(0, ColorSky0);
  linearGrad.setColorAt(1, ColorSky1);
  QBrush brushSky1(linearGrad);   painter.setBrush(brushSky1);
  painter.drawRect(-MaxDimHalf,yh+0.5, MaxDim,-H1-2.0);

//  yh = hPitchAngle-H1;
  yh -= H1;
//  yh = -h1;
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(2.0*(h1+h2)-qSqrt(2.0)*h2)) { yh += 2.0*(h1+h2); }
//  while(yh >=   2.0*(h1+h2)-qSqrt(2.0)*h2)  { yh -= 2.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-H2);
  linearGrad.setColorAt(0, ColorSky1);
  linearGrad.setColorAt(1, ColorSky2);
  QBrush brushSky2(linearGrad);   painter.setBrush(brushSky2);
  painter.drawRect(QRectF(-MaxDimHalf,yh, MaxDim,-H2-2.0));

//90
//  yh = hPitchAngle-H1-H2;
  yh -= H2;
//  yh = -h1-h2;
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(2.0*(h1+h2)-qSqrt(2.0)*h2)) { yh += 2.0*(h1+h2); }
//  while(yh >=   2.0*(h1+h2)-qSqrt(2.0)*h2)  { yh -= 2.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-H2);
  linearGrad.setColorAt(0, ColorSky2);
  linearGrad.setColorAt(1, ColorSky1);
  QBrush brushSky3(linearGrad);   painter.setBrush(brushSky3);
  painter.drawRect(QRectF(-MaxDimHalf,yh, MaxDim,-H2-2.0));

//  yh = hPitchAngle-H1-H2-H2;
  yh -= H2;
//  yh = -h1-h2-h2;
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(2.0*(h1+h2)-qSqrt(2.0)*h1)) { yh += 2.0*(h1+h2); }
//  while(yh >=   2.0*(h1+h2)-qSqrt(2.0)*h1)  { yh -= 2.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-H1);
  linearGrad.setColorAt(0, ColorSky1);
  linearGrad.setColorAt(1, ColorSky0);
  QBrush brushSky4(linearGrad);   painter.setBrush(brushSky4);
  painter.drawRect(QRectF(-MaxDimHalf,yh+0.5, MaxDim,-H1-2.0));
//180


//-Ground:

// 0:
  yh = hPitchAngle;
//  yh = 0.0;
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//  while(yh >=   2.0*(h1+h2)-qSqrt(2.0)*h1)  { yh -= 2.0*(h1+h2); }
//  while(yh <= -(2.0*(h1+h2)-qSqrt(2.0)*h1)) { yh += 2.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+H1);
  linearGrad.setColorAt(0, ColorGround0);
  linearGrad.setColorAt(1, ColorGround1);
  QBrush brushGround1(linearGrad);   painter.setBrush(brushGround1);
  painter.drawRect(QRectF(-MaxDimHalf,yh-0.5, MaxDim,H1+2.0));

//  yh = hPitchAngle+H1;
  yh += H1;
//  yh = h1;
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//  while(yh >=   2.0*(h1+h2)-qSqrt(2.0)*h2)  { yh -= 2.0*(h1+h2); }
//  while(yh <= -(2.0*(h1+h2)-qSqrt(2.0)*h2)) { yh += 2.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+H2);
  linearGrad.setColorAt(0, ColorGround1);
  linearGrad.setColorAt(1, ColorGround2);
  QBrush brushGround2(linearGrad);   painter.setBrush(brushGround2);
  painter.drawRect(QRectF(-MaxDimHalf,yh, MaxDim,H2+2.0));

//90:
//  yh = hPitchAngle+H1+H2;
  yh += H2;
//  yh = h1+h2;
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//  while(yh >=   2.0*(h1+h2)-qSqrt(2.0)*h2)  { yh -= 2.0*(h1+h2); }
//  while(yh <= -(2.0*(h1+h2)-qSqrt(2.0)*h2)) { yh += 2.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+H2);
  linearGrad.setColorAt(0, ColorGround2);
  linearGrad.setColorAt(1, ColorGround1);
  QBrush brushGround3(linearGrad);   painter.setBrush(brushGround3);
  painter.drawRect(QRectF(-MaxDimHalf,yh, MaxDim,H2+2.0));

//  yh = hPitchAngle+H1+H2+H2;
  yh += H2;
//  yh = h1+h2+h2;
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//  while(yh >=   2.0*(h1+h2)-qSqrt(2.0)*h1)  { yh -= 2.0*(h1+h2); }
//  while(yh <= -(2.0*(h1+h2)-qSqrt(2.0)*h1)) { yh += 2.0*(h1+h2); }
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+H1);
  linearGrad.setColorAt(0, ColorGround1);
  linearGrad.setColorAt(1, ColorGround0);
  QBrush brushGround4(linearGrad);   painter.setBrush(brushGround4);
  painter.drawRect(QRectF(-MaxDimHalf,yh, MaxDim,H1+2));
//180


//  painter.translate(0.0,hPitchAngle);
//
//  if(isUpDawn) {
//    painter.translate(0.0,2.0*hPitchAngle);
//    hPitchAngle = -hPitchAngle;
//  }


//  if(isUpDawn) { PSliderRoll->setValue(RollAngle+180); }


//painter.translate(0.0,-hPitchAngle);

//painter.rotate(RollAngle);

//painter.translate(0.0,hPitchAngle);


//== Pitch Scale:

  QPen pen(ColorPitch);  pen.setWidthF(1.0);
//  pen.setCapStyle(Qt::RoundCap);
//  pen.setJoinStyle(Qt::SvgMiterJoin); //Qt::RoundJoin); //Qt::BevelJoin); //Qt::MiterJoin);
  painter.setPen(pen);

//  qreal x,y;
  QVector<QLineF> lines;

//- (2)-degrees:
  qreal y;  bool isHas = false;
  for(int k = -1; k <= 1; k += 2) {
    y = hPitchAngle;
    while(y >=   2.0*(H1+H2)-2.0*HeightHalfVisible)  { y -= 2.0*(H1+H2); }
    while(y <= -(2.0*(H1+H2)-2.0*HeightHalfVisible)) { y += 2.0*(H1+H2); }
    for(int i = 1; i <= 4; i++) {
      y += -2.0*HOneDegreeAngle*k;
      if(qAbs(y) <= HeightHalfVisible) {  isHas = true;
        lines << QLineF(-8.0,y, 8.0,y);
      }
    }
  }
  if(isHas)  painter.drawLines(lines);
  lines.clear();

  pen.setWidthF(1.5);   painter.setPen(pen);

  qreal xoff, yoff;
  qreal angle;

//- 10-degrees:
  mpointsF[0].setX(-24.0);
  mpointsF[1].setX(-24.0);
  mpointsF[2].setX(24.0);
  mpointsF[3].setX(24.0);
  for(int k = -1; k <= 1; k += 2) {
    for(int i = 0; i <= 9; i++) {
      angle = 10.0*i;
      y = hPitchAngle - angle*HOneDegreeAngle*k;
      while(y >=   2.0*(H1+H2)-2.0*HeightHalfVisible)  { y -= 2.0*(H1+H2); }
      while(y <= -(2.0*(H1+H2)-2.0*HeightHalfVisible)) { y += 2.0*(H1+H2); }
      if(qAbs(y) <= HeightHalfVisible) {
        if(i == 0) {
          painter.drawLine(QLineF(-48.0,y, 48.0,y));
        }
        else if(i < 9) {
          mpointsF[0].setY(y + 5.0*k);
          mpointsF[1].setY(y);
          mpointsF[2].setY(y);
          mpointsF[3].setY(y + 5.0*k);
          painter.drawPolyline(mpointsF, 4); //int pointCount)
          DrawText(painter, -24.0-12.0+0.5, y+5.0/2.0*k, angle);
          DrawText(painter,  24.0+12.0+1.0, y+5.0/2.0*k, angle);
        }
        else {
          lines << QLineF(-36.0,y-7.0, -36.0,y+7.0);
          lines << QLineF(-36.0,y,      36.0,y);
          lines << QLineF( 36.0,y-7.0,  36.0,y+7.0);
          painter.drawLines(lines);  lines.clear();
          DrawText(painter, -36.0-12.0+1.0, y, angle);
          DrawText(painter,  36.0+12.0+1.0, y, angle);
        }
      }
    }

  }
//- (15)-degrees:
  for(int k = -1; k <= 1; k += 2) {
    y = hPitchAngle - 10.0*HOneDegreeAngle*(1.0+0.5)*k;
    while(y >=   2.0*(H1+H2)-2.0*HeightHalfVisible)  { y -= 2.0*(H1+H2); }
    while(y <= -(2.0*(H1+H2)-2.0*HeightHalfVisible)) { y += 2.0*(H1+H2); }
    if(qAbs(y) <= HeightHalfVisible)
      painter.drawLine(QLineF(-16.0,y, 16.0,y));
  }


//  QFont font(font());   // font.setStyleStrategy(QFont::NoAntialias);
//  painter.setFont(font);



//=====  Roll:  =====

//painter.rotate(-RollAngle);

  painter.setBrush(QBrush(ColorRoll));

//- Triangle:
  painter.setPen(Qt::NoPen);
  mpointsF[0].setX(0.0);   mpointsF[0].setY(-rRoll);
  mpointsF[1].setX(-6.5);  mpointsF[1].setY(-rRoll - 11.258); //  11.258 = sqrt(3.0)/2.0 * 13.0
  mpointsF[2].setX(6.5);   mpointsF[2].setY(-rRoll - 11.258);
  painter.drawPolygon(mpointsF,3);

//- Arc:
  pen.setColor(ColorRoll);  pen.setWidthF(1.5);   painter.setPen(pen);
  painter.drawArc(QRectF(-rRoll, -rRoll, 2.0*rRoll, 2.0*rRoll), 30*16, 120*16);


  qreal hs1 = 5.0;
  qreal hs2 = 12.0;  qreal ws2 = 5.0;
  qreal hs3 = 10.0;
  yoff = -rRoll - hs2 - 10.0; //  - 5.0
  angle = 0.0;

  qreal dopangle;  // QString text;

  for(int k = -1; k <= 1; k += 2) {
    xoff = ws2/2.0*k;
//- (5), (10):
    dopangle = 10.0*k;  painter.rotate(dopangle);
    for(int i = 1; i <= 2; i++) {
      painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0,-rRoll-hs1));
      painter.rotate(dopangle);
    }

//- 30, (45), 60, (75):
    dopangle = 15.0*k;  angle = 15.0;
    for(int i = 1; i <= 2; i++) {
// 30, 60:
      angle += dopangle*k;  //  text.sprintf(("%.0f"),angle);
      DrawText(painter, xoff, yoff, angle); //text);
      mpointsF[0].setX(0.0);  mpointsF[0].setY(-rRoll);
      mpointsF[1].setX(0.0);  mpointsF[1].setY(-rRoll-hs2);
      mpointsF[2].setX(ws2*k);  mpointsF[2].setY(-rRoll-hs2);
      painter.drawPolyline(mpointsF, 3);
// (45), (75):
      painter.rotate(dopangle);
      painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0,-rRoll-hs3));

      painter.rotate(dopangle);
      angle += dopangle*k;
    }

//- 90:
    xoff = 1.0;
    angle += dopangle*k;  //  text.sprintf(("%.0f"),angle);
    DrawText(painter, xoff, yoff, angle); //text);
//    painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0, -rRoll-hs2));
//    painter.drawLine(QPointF(-4.0, -rRoll-hs2), QPointF(4.0, -rRoll-hs2));
    lines << QLineF(0.0,-rRoll, 0.0,-rRoll-hs2);
    lines << QLineF(-4.0,-rRoll-hs2, 4.0,-rRoll-hs2);
    painter.drawLines(lines);  lines.clear();

//- 120, 150:
    xoff = -ws2/2.0*k;
    dopangle = 30.0*k;    painter.rotate(dopangle);
    for(int i = 1; i <= 2; i++) {
      angle += dopangle*k;  //  text.sprintf(("%.0f"),angle);
      DrawText(painter, xoff, yoff, angle); //text);
      mpointsF[0].setX(0.0);  mpointsF[0].setY(-rRoll);
      mpointsF[1].setX(0.0);  mpointsF[1].setY(-rRoll-hs2);
      mpointsF[2].setX(-ws2*k);  mpointsF[2].setY(-rRoll-hs2);
      painter.drawPolyline(mpointsF, 3);

      painter.rotate(dopangle);
    }

    if(k == -1)  painter.rotate(180.0);
  }

//- 180:
  xoff = -1.0;
  angle += dopangle;  //  text.sprintf(("%.0f"),angle);
  DrawText(painter, xoff, yoff, angle); //text);
//  painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0,-rRoll-hs2));
//  painter.drawLine(QPointF(-3.0, -rRoll-hs2+4.0), QPointF(3.0, -rRoll-hs2+4.0));
//  painter.drawLine(QPointF(-6.0, -rRoll-hs2), QPointF(6.0, -rRoll-hs2));
  lines << QLineF(0.0,-rRoll, 0.0,-rRoll-hs2);
  lines << QLineF(-3.0,-rRoll-hs2+4.0, 3.0,-rRoll-hs2+4.0);
  lines << QLineF(-6.0,-rRoll-hs2, 6.0,-rRoll-hs2);
  painter.drawLines(lines);  lines.clear();
  painter.rotate(-180.0);


//=====  Static:  =====

  painter.rotate(RollAngle);

//  painter.setPen(Qt::NoPen);

//==Balance:

  pen.setColor(ColorStaticBalanceOutline);  pen.setWidthF(0.5);   painter.setPen(pen);

  linearGrad.setStart(0.0,    -3.5+1.5);
  linearGrad.setFinalStop(0.0, 3.5);
  linearGrad.setColorAt(0, ColorStaticBalance0);
  linearGrad.setColorAt(1, ColorStaticBalance1);
  QBrush brushBalance(linearGrad);   painter.setBrush(brushBalance);

//-Left:
  mpointsF[0].setX(-48.0-1.0);           mpointsF[0].setY(0.0);
  mpointsF[1].setX(-48.0-1.0-8.0);       mpointsF[1].setY(-3.5);
  mpointsF[2].setX(-48.0-1.0-8.0-24.0);  mpointsF[2].setY(-3.5);
  mpointsF[3].setX(-48.0-1.0-8.0-24.0);  mpointsF[3].setY(3.5);
  mpointsF[4].setX(-48.0-1.0-8.0);       mpointsF[4].setY(3.5);
  painter.drawPolygon(mpointsF,5);

//-Right:
  mpointsF[0].setX(48.0+1.0);          // mpointsF[0].setY(0.0);
  mpointsF[1].setX(48.0+1.0+8.0);      // mpointsF[1].setY(-3.5);
  mpointsF[2].setX(48.0+1.0+8.0+24.0); // mpointsF[2].setY(-3.5);
  mpointsF[3].setX(48.0+1.0+8.0+24.0); // mpointsF[3].setY(3.5);
  mpointsF[4].setX(48.0+1.0+8.0);      // mpointsF[4].setY(3.5);
  painter.drawPolygon(mpointsF,5);

//-Center:
  linearGrad.setStart(0.0,    0.0);
  linearGrad.setFinalStop(0.0, 12.0+6.0);
  linearGrad.setColorAt(0, ColorStaticBalance0);
  linearGrad.setColorAt(1, ColorStaticBalance1);
  QBrush brushBalanceCenter(linearGrad);   painter.setBrush(brushBalanceCenter);
  mpointsF[0].setX(0.0);            mpointsF[0].setY(0.0);
  mpointsF[1].setX(-30.0);          mpointsF[1].setY(12.0);
  mpointsF[2].setX(0.0);            mpointsF[2].setY(6.0);
  mpointsF[3].setX(30.0);           mpointsF[3].setY(12.0);
  painter.drawPolygon(mpointsF,4);

//- Triangle:
  painter.setBrush(QBrush(ColorStaticTriangle));
  mpointsF[0].setX(0.0);   mpointsF[0].setY(-rRoll);
  mpointsF[1].setX(6.5);   mpointsF[1].setY(-rRoll + 11.258); //  11.258 = sqrt(3.0)/2.0 * 13.0
  mpointsF[2].setX(-6.5);  mpointsF[2].setY(-rRoll + 11.258);
  painter.drawPolygon(mpointsF,3);


//=============================


/*
qreal cs = qCos(RollAngle/180.0*M_PI);   qreal acs = qAbs(cs);
qreal hPitchAngleCos = hPitchAngle*cs;

//qreal HeightHemiSphere = Height/AngleHeight*90.0;


  painter.translate(WidthHalf,HeightHalf);

while(hPitchAngle <= -(2.0*(h1+h2)-h2)) { hPitchAngle += 4.0*(h1+h2); }
while(hPitchAngle >=  (2.0*(h1+h2)-h2)) { hPitchAngle -= 4.0*(h1+h2); }

//if(hPitchAngle <= -(2.0*(h1+h2))) { hPitchAngle += 2.0*(h1+h2); }
//if(hPitchAngle >=  (2.0*(h1+h2))) { hPitchAngle -= 2.0*(h1+h2); }


painter.translate(0.0,hPitchAngle);

//while(hPitchAngle <= -(4.0*(h1+h2))) { hPitchAngle += 4.0*(h1+h2); }
//while(hPitchAngle >=  (4.0*(h1+h2))) { hPitchAngle -= 4.0*(h1+h2); }


  painter.rotate(-RollAngle);

//painter.translate(0.0,hPitchAngle);

//=====  Pitch:  =====


  painter.setPen(Qt::NoPen);

//-Sky:

// 0:
//  yh = hPitchAngle;
//yh = hPitchAngleCos; //*cs;
yh = 0.0;
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
//while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//while(yh >=  (4.0*(h1+h2)-2.0*qSqrt(2.0)*h1))  { yh -= 4.0*(h1+h2); }
//yh += -hPitchAngle + hPitchAngleCos; //*cs;
//yh *= cs;
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-h1);
  linearGrad.setColorAt(0, QColor(80,180,255, 255));
  linearGrad.setColorAt(1, QColor(0,0,100, 255));
  QBrush brushSky1(linearGrad);   painter.setBrush(brushSky1);
  painter.drawRect(-MaxDimHalf,yh+0.5, MaxDim,-h1-1.0);

//  yh = hPitchAngle-h1;
//yh = hPitchAngleCos-h1; //)*cs;
yh = -h1; //)*cs;
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
//while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//while(yh >=  (4.0*(h1+h2)-2.0*qSqrt(2.0)*h2))  { yh -= 4.0*(h1+h2); }
//yh += -hPitchAngle + hPitchAngleCos; //*cs;
//yh *= cs;
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-h2);
  linearGrad.setColorAt(0, QColor(0,0,100, 255));
  linearGrad.setColorAt(1, QColor(0,0,80, 255));
  QBrush brushSky2(linearGrad);   painter.setBrush(brushSky2);
  painter.drawRect(-MaxDimHalf,yh, MaxDim,-h2-1.0);

//90
//  yh = hPitchAngle-h1-h2;
//yh = hPitchAngleCos-h1-h2; //)*cs;
yh = -h1-h2; //)*cs;
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
//while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//while(yh >=  (4.0*(h1+h2)-2.0*qSqrt(2.0)*h2))  { yh -= 4.0*(h1+h2); }
//yh += -hPitchAngle + hPitchAngleCos; //*cs;
//yh *= cs;
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-h2);
  linearGrad.setColorAt(0, QColor(0,0,80, 255));
  linearGrad.setColorAt(1, QColor(0,0,100, 255));
  QBrush brushSky3(linearGrad);   painter.setBrush(brushSky3);
  painter.drawRect(-MaxDimHalf,yh, MaxDim,-h2-1.0);

//  yh = hPitchAngle-h1-h2-h2;
//yh = hPitchAngleCos-h1-h2-h2; //)*cs;
yh = -h1-h2-h2; //)*cs;
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
//while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//while(yh >=  (4.0*(h1+h2)-2.0*qSqrt(2.0)*h1))  { yh -= 4.0*(h1+h2); }
//yh += -hPitchAngle + hPitchAngleCos; //*cs;
//yh *= cs;
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh-h1);
  linearGrad.setColorAt(0, QColor(0,0,100, 255));
  linearGrad.setColorAt(1, QColor(80,180,255, 255));
  QBrush brushSky4(linearGrad);   painter.setBrush(brushSky4);
  painter.drawRect(-MaxDimHalf,yh+0.5, MaxDim,-h1-1.0);
//180

//-Ground:

// 0:
//  yh = hPitchAngle;
//yh = hPitchAngleCos; //*cs;
yh = 0.0;//hPitchAngleCos; //*cs;
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//while(yh >=  (4.0*(h1+h2)-2.0*qSqrt(2.0)*h1))  { yh -= 4.0*(h1+h2); }
//while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//yh += -hPitchAngle + hPitchAngleCos; //*cs;
//yh *= cs;
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+h1);
  linearGrad.setColorAt(0, QColor(90,170,110, 255));
  linearGrad.setColorAt(1, QColor(90,17,11, 255));
  QBrush brushGround1(linearGrad);   painter.setBrush(brushGround1);
  painter.drawRect(-MaxDimHalf,yh-0.5, MaxDim,h1+1.0);

//  yh = hPitchAngle+h1;
//yh = hPitchAngleCos+h1; //)*cs;
yh = h1; //)*cs;
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//while(yh >=  (4.0*(h1+h2)-2.0*qSqrt(2.0)*h2))  { yh -= 4.0*(h1+h2); }
//while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//yh += -hPitchAngle + hPitchAngleCos; //*cs;
//yh *= cs;
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+h2);
  linearGrad.setColorAt(0, QColor(90,17,11, 255));
  linearGrad.setColorAt(1, QColor(0,17,11, 255));
  QBrush brushGround2(linearGrad);   painter.setBrush(brushGround2);
  painter.drawRect(-MaxDimHalf,yh, MaxDim,h2+1.0);

//90:
//  yh = hPitchAngle+h1+h2;
//yh = hPitchAngleCos+h1+h2; //)*cs;
yh = h1+h2; //)*cs;
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//while(yh >=  (4.0*(h1+h2)-2.0*qSqrt(2.0)*h2))  { yh -= 4.0*(h1+h2); }
//while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h2)) { yh += 4.0*(h1+h2); }
//yh += -hPitchAngle + hPitchAngleCos; //*cs;
//yh *= cs;
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+h2);
  linearGrad.setColorAt(0, QColor(0,17,11, 255));
  linearGrad.setColorAt(1, QColor(90,17,11, 255));
  QBrush brushGround3(linearGrad);   painter.setBrush(brushGround3);
  painter.drawRect(-MaxDimHalf,yh, MaxDim,h2+1.0);

//  yh = hPitchAngle+h1+h2+h2;
//yh = hPitchAngleCos+h1+h2+h2; //)*cs;
yh = h1+h2+h2; //)*cs;
//  while(yh >=   4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)  { yh -= 4.0*(h1+h2); }
//  while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//while(yh >=  (4.0*(h1+h2)-2.0*qSqrt(2.0)*h1))  { yh -= 4.0*(h1+h2); }
//while(yh <= -(4.0*(h1+h2)-2.0*qSqrt(2.0)*h1)) { yh += 4.0*(h1+h2); }
//yh += -hPitchAngle + hPitchAngleCos; //*cs;
//yh *= cs;
  linearGrad.setStart(0.0,     yh);
  linearGrad.setFinalStop(0.0, yh+h1);
  linearGrad.setColorAt(0, QColor(90,17,11, 255));
  linearGrad.setColorAt(1, QColor(90,170,110, 255));
  QBrush brushGround4(linearGrad);   painter.setBrush(brushGround4);
  painter.drawRect(-MaxDimHalf,yh, MaxDim,h1);
//180



//painter.translate(0.0,-hPitchAngle);

painter.rotate(RollAngle);

painter.translate(0.0,-hPitchAngle);


//= Pitch Scale:


  QPen pen(QColor(255,255,255, 255));
  pen.setWidthF(1.0);
//  pen.setCapStyle(Qt::RoundCap);
//  pen.setJoinStyle(Qt::SvgMiterJoin); //Qt::RoundJoin); //Qt::BevelJoin); //Qt::MiterJoin);
  painter.setPen(pen);

//  qreal x,y;
  QVector<QLineF> lines;

//- (2)-degrees:
  qreal y;  bool isHas = false;
  for(int k = -1; k <= 1; k += 2) {
    y = hPitchAngle;
    while(y >=   2.0*(h1+h2)-2.0*HeightHalfVisible)  { y -= 2.0*(h1+h2); }
    while(y <= -(2.0*(h1+h2)-2.0*HeightHalfVisible)) { y += 2.0*(h1+h2); }
    for(int i = 1; i <= 4; i++) {
      y += -2.0*HOneDegreeAngle*k;
      if(qAbs(y) <= HeightHalfVisible) {  isHas = true;
        lines << QLineF(-8.0,y, 8.0,y);
      }
    }
  }
  if(isHas)  painter.drawLines(lines);
  lines.clear();

  pen.setWidthF(1.5);   painter.setPen(pen);

  qreal xoff, yoff;
  qreal angle;

//- 10-degrees:
  mpointsF[0].setX(-24.0);
  mpointsF[1].setX(-24.0);
  mpointsF[2].setX(24.0);
  mpointsF[3].setX(24.0);
  for(int k = -1; k <= 1; k += 2) {
    for(int i = 0; i <= 9; i++) {
      angle = 10.0*i;
      y = hPitchAngle - angle*HOneDegreeAngle*k;
      while(y >=   2.0*(h1+h2)-2.0*HeightHalfVisible)  { y -= 2.0*(h1+h2); }
      while(y <= -(2.0*(h1+h2)-2.0*HeightHalfVisible)) { y += 2.0*(h1+h2); }
      if(qAbs(y) <= HeightHalfVisible) {
        if(i == 0) {
          painter.drawLine(QLineF(-48.0,y, 48.0,y));
        }
        else if(i < 9) {
          mpointsF[0].setY(y + 5.0*k);
          mpointsF[1].setY(y);
          mpointsF[2].setY(y);
          mpointsF[3].setY(y + 5.0*k);
          painter.drawPolyline(mpointsF, 4); //int pointCount)
          DrawText(painter, -24.0-12.0+0.5, y+5.0/2.0*k, angle);
          DrawText(painter,  24.0+12.0+1.0, y+5.0/2.0*k, angle);
        }
        else {
          lines << QLineF(-36.0,y-7.0, -36.0,y+7.0);
          lines << QLineF(-36.0,y,      36.0,y);
          lines << QLineF( 36.0,y-7.0,  36.0,y+7.0);
          painter.drawLines(lines);  lines.clear();
          DrawText(painter, -36.0-12.0+1.0, y, angle);
          DrawText(painter,  36.0+12.0+1.0, y, angle);
        }
      }
    }

  }
//- (15)-degrees:
  for(int k = -1; k <= 1; k += 2) {
    y = hPitchAngle - 10.0*HOneDegreeAngle*(1.0+0.5)*k;
    while(y >=   2.0*(h1+h2)-2.0*HeightHalfVisible)  { y -= 2.0*(h1+h2); }
    while(y <= -(2.0*(h1+h2)-2.0*HeightHalfVisible)) { y += 2.0*(h1+h2); }
    if(qAbs(y) <= HeightHalfVisible)
      painter.drawLine(QLineF(-16.0,y, 16.0,y));
  }


//  QFont font(font());   // font.setStyleStrategy(QFont::NoAntialias);
//  painter.setFont(font);



//=====  Roll:  =====

painter.rotate(-RollAngle);

  painter.setBrush(QBrush(QColor(255,255,255, 255)));

//- Triangle:
  painter.setPen(Qt::NoPen);
  mpointsF[0].setX(0.0);   mpointsF[0].setY(-rRoll);
  mpointsF[1].setX(-6.5);  mpointsF[1].setY(-rRoll - 11.258); //  11.258 = sqrt(3.0)/2.0 * 13.0
  mpointsF[2].setX(6.5);   mpointsF[2].setY(-rRoll - 11.258);
  painter.drawPolygon(mpointsF,3);

//- Arc:
  pen.setWidthF(1.5);   painter.setPen(pen);
  painter.drawArc(QRectF(-rRoll, -rRoll, 2.0*rRoll, 2.0*rRoll), 30*16, 120*16);


  qreal hs1 = 5.0;
  qreal hs2 = 12.0;  qreal ws2 = 5.0;
  qreal hs3 = 10.0;
  yoff = -rRoll - hs2 - 10.0; //  - 5.0
  angle = 0.0;

  qreal dopangle;  // QString text;

  for(int k = -1; k <= 1; k += 2) {
    xoff = ws2/2.0*k;
//- (5), (10):
    dopangle = 10.0*k;  painter.rotate(dopangle);
    for(int i = 1; i <= 2; i++) {
      painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0,-rRoll-hs1));
      painter.rotate(dopangle);
    }

//- 30, (45), 60, (75):
    dopangle = 15.0*k;  angle = 15.0;
    for(int i = 1; i <= 2; i++) {
// 30, 60:
      angle += dopangle*k;  //  text.sprintf(("%.0f"),angle);
      DrawText(painter, xoff, yoff, angle); //text);
      mpointsF[0].setX(0.0);  mpointsF[0].setY(-rRoll);
      mpointsF[1].setX(0.0);  mpointsF[1].setY(-rRoll-hs2);
      mpointsF[2].setX(ws2*k);  mpointsF[2].setY(-rRoll-hs2);
      painter.drawPolyline(mpointsF, 3);
// (45), (75):
      painter.rotate(dopangle);
      painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0,-rRoll-hs3));

      painter.rotate(dopangle);
      angle += dopangle*k;
    }

//- 90:
    xoff = 1.0;
    angle += dopangle*k;  //  text.sprintf(("%.0f"),angle);
    DrawText(painter, xoff, yoff, angle); //text);
//    painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0, -rRoll-hs2));
//    painter.drawLine(QPointF(-4.0, -rRoll-hs2), QPointF(4.0, -rRoll-hs2));
    lines << QLineF(0.0,-rRoll, 0.0,-rRoll-hs2);
    lines << QLineF(-4.0,-rRoll-hs2, 4.0,-rRoll-hs2);
    painter.drawLines(lines);  lines.clear();

//- 120, 150:
    xoff = -ws2/2.0*k;
    dopangle = 30.0*k;    painter.rotate(dopangle);
    for(int i = 1; i <= 2; i++) {
      angle += dopangle*k;  //  text.sprintf(("%.0f"),angle);
      DrawText(painter, xoff, yoff, angle); //text);
      mpointsF[0].setX(0.0);  mpointsF[0].setY(-rRoll);
      mpointsF[1].setX(0.0);  mpointsF[1].setY(-rRoll-hs2);
      mpointsF[2].setX(-ws2*k);  mpointsF[2].setY(-rRoll-hs2);
      painter.drawPolyline(mpointsF, 3);

      painter.rotate(dopangle);
    }

    if(k == -1)  painter.rotate(180.0);
  }

//- 180:
  xoff = -1.0;
  angle += dopangle;  //  text.sprintf(("%.0f"),angle);
  DrawText(painter, xoff, yoff, angle); //text);
//  painter.drawLine(QPointF(0.0,-rRoll), QPointF(0.0,-rRoll-hs2));
//  painter.drawLine(QPointF(-3.0, -rRoll-hs2+4.0), QPointF(3.0, -rRoll-hs2+4.0));
//  painter.drawLine(QPointF(-6.0, -rRoll-hs2), QPointF(6.0, -rRoll-hs2));
  lines << QLineF(0.0,-rRoll, 0.0,-rRoll-hs2);
  lines << QLineF(-3.0,-rRoll-hs2+4.0, 3.0,-rRoll-hs2+4.0);
  lines << QLineF(-6.0,-rRoll-hs2, 6.0,-rRoll-hs2);
  painter.drawLines(lines);  lines.clear();
  painter.rotate(-180.0);

//=====  Static:  =====

  painter.rotate(RollAngle);

  painter.setPen(Qt::NoPen);

//-Balance:

  pen.setColor(Qt::black);
  pen.setWidthF(0.5);   painter.setPen(pen);

  linearGrad.setStart(0.0,    -3.5+1.5);
  linearGrad.setFinalStop(0.0, 3.5);
  linearGrad.setColorAt(0, QColor(255,255,0, 255));
  linearGrad.setColorAt(1, QColor(88,88,0, 255));
  QBrush brushBalance(linearGrad);   painter.setBrush(brushBalance);

//-Left:
  mpointsF[0].setX(-48.0-1.0);           mpointsF[0].setY(0.0);
  mpointsF[1].setX(-48.0-1.0-8.0);       mpointsF[1].setY(-3.5);
  mpointsF[2].setX(-48.0-1.0-8.0-24.0);  mpointsF[2].setY(-3.5);
  mpointsF[3].setX(-48.0-1.0-8.0-24.0);  mpointsF[3].setY(3.5);
  mpointsF[4].setX(-48.0-1.0-8.0);       mpointsF[4].setY(3.5);
  painter.drawPolygon(mpointsF,5);

//-Right:
  mpointsF[0].setX(48.0+1.0);          // mpointsF[0].setY(0.0);
  mpointsF[1].setX(48.0+1.0+8.0);      // mpointsF[1].setY(-3.5);
  mpointsF[2].setX(48.0+1.0+8.0+24.0); // mpointsF[2].setY(-3.5);
  mpointsF[3].setX(48.0+1.0+8.0+24.0); // mpointsF[3].setY(3.5);
  mpointsF[4].setX(48.0+1.0+8.0);      // mpointsF[4].setY(3.5);
  painter.drawPolygon(mpointsF,5);

//-Center:
  linearGrad.setStart(0.0,    0.0);
  linearGrad.setFinalStop(0.0, 12.0+6.0);
  linearGrad.setColorAt(0, QColor(255,255,0, 255));
  linearGrad.setColorAt(1, QColor(88,88,0, 255));
  QBrush brushBalanceCenter(linearGrad);   painter.setBrush(brushBalanceCenter);
  mpointsF[0].setX(0.0);            mpointsF[0].setY(0.0);
  mpointsF[1].setX(-30.0);          mpointsF[1].setY(12.0);
  mpointsF[2].setX(0.0);            mpointsF[2].setY(6.0);
  mpointsF[3].setX(30.0);           mpointsF[3].setY(12.0);
  painter.drawPolygon(mpointsF,4);

//- Triangle:
  painter.setBrush(QBrush(QColor(255,255,0, 255)));
  mpointsF[0].setX(0.0);   mpointsF[0].setY(-rRoll);
  mpointsF[1].setX(6.5);   mpointsF[1].setY(-rRoll + 11.258); //  11.258 = sqrt(3.0)/2.0 * 13.0
  mpointsF[2].setX(-6.5);  mpointsF[2].setY(-rRoll + 11.258);
  painter.drawPolygon(mpointsF,3);
*/
//==========================

//if(!IsReadyGL) return;
//IsReadyGL = false;

//IsReadyRedraw = true;
//return;

  painter.setOpacity(0.6);

//QPixmap pixmap = PEkranoplanGL->grab();

  QPixmap pixmap = PEkranoplanGL->renderPixmap(); //80,80);//,false);
//  bool b = pixmap.save("d:\\Progs\\WIGTS\\__TT.png", "PNG");
//  painter.drawPixmap(-40,-40, pixmap);
//  bool b2 = pixmap2.save("d:\\Progs\\WIGTS\\__TT2.png", "PNG");
//  QImage image = PEkranoplanGLWidget->grabFrameBuffer();
//+  QPixmap pixmap = QPixmap::fromImage(PEkranoplanGL->grabFrameBuffer());
  pixmap.setMask(pixmap.createMaskFromColor(QColor(0,0,0, 255)));
  painter.drawPixmap(-WidthHalf+1,HeightHalf-pixmap.rect().height()-1, pixmap);
//IsReadyGL = true;
/*
//GetPMainWnd()->statusBar()->hide();
//GetPMainWnd()->statusBar()->repaint();
QString s; s.sprintf("PitchAngle0 = %.1f,  RollAngle0 = %.1f;    PitchAngle = %.1f,  RollAngle = %.1f;", PitchAngle0,RollAngle0, PitchAngle,RollAngle);
GetPMainWnd()->statusBar()->showMessage(s);
GetPMainWnd()->statusBar()->repaint();
*/
}
//--------------------------------------------------------------------------------------------
/*+
//void MGyrohorizon::SlotSetPitchAngle(int value)
void MGyrohorizon::SetPitchAngle(int value)
{
*/
/*
  qreal d = (value - PitchAngle)*M_PI/180.0;
  qreal cs = qCos(d);  qreal sn = qSin(d);
  QMatrix3x3 t;

//  qreal t11 = cs;   qreal t21 = 0.0;  qreal t31 = -sn;
//  qreal t12 = 0.0;  qreal t22 = 1.0;  qreal t32 = 0.0;
//  qreal t13 = sn;   qreal t23 = 0.0;  qreal t33 = cs;

//   X'              Y'              Z'
  t(0,0) = cs;    t(0,1) = 0.0;   t(0,2) = sn;
  t(1,0) = 0.0;   t(1,1) = 1.0;   t(1,2) = 0.0;
  t(2,0) = -sn;   t(2,1) = 0.0;   t(2,2) = cs;

  QMatrix3x3 temp(T);
  T = temp*t;


  QGenericMatrix<1,3,float> vx,vy, vxs,vys;
  vxs(0,0) = 1.0;  vxs(1,0) = 0.0;  vxs(2,0) = 0.0;
  vys(0,0) = 0.0;  vys(1,0) = 1.0;  vxs(2,0) = 0.0;

  vx = T*vxs;  vy = T*vys;

  qreal a = (-vx(1,0)*vy(0,0) + vx(0,0)*vy(1,0))/qSqrt(vx(1,0)*vx(1,0)+vx(0,0)*vx(0,0));
  if(a <= -1.0)      RollAngle = 180.0;
  else if(a >= 1.0)  RollAngle = 0.0;
  else               RollAngle = qAcos(a)*180.0/M_PI;
*/
//--
/*+
//if(value > 90)  value -= 180;
//if(value < -90)  value += 180;

//  if(PitchAngle == value)  return;
//  PitchAngle = value;
if(PitchAngle0 == value)  return;
PitchAngle0 = value;

  update();

//QString s; s.sprintf("PitchAngle0 = %.1f,  RollAngle0 = %.1f;    PitchAngle0 = %.1f,  RollAngle0 = %.1f", PitchAngle0,RollAngle0, PitchAngle,RollAngle);
//GetPMainWnd()->statusBar()->showMessage(s);
}
//--------------------------------------------------------------------------------------------
//void MGyrohorizon::SlotSetRollAngle(int value)
void MGyrohorizon::SetRollAngle(int value)
{
*/
/*
  qreal d = (value - RollAngle)*M_PI/180.0;
  qreal cs = qCos(d);  qreal sn = qSin(d);
  QMatrix3x3 t;
//   X'              Y'              Z'
  t(0,0) = 1.0;   t(0,1) = 0.0;   t(0,2) = 0.0;
  t(1,0) = 0.0;   t(1,1) = cs;    t(1,2) = -sn;
  t(2,0) = 0.0;   t(2,1) = sn;    t(2,2) = cs;

  QMatrix3x3 temp(T);
  T = temp*t;
*/
//--
/*+
//  if(RollAngle == value)  return;
//  RollAngle = value;
if(RollAngle0 == value)  return;
RollAngle0 = value;

//RollAngle = 90.0;
//QString s; s.sprintf("PitchAngle0 = %.1f,  RollAngle0 = %.1f;    PitchAngle0 = %.1f,  RollAngle0 = %.1f", PitchAngle0,RollAngle0, PitchAngle,RollAngle);
//GetPMainWnd()->statusBar()->showMessage(s);

//if(!IsSliderPitchPressed)
  update();
}
*/
//--------------------------------------------------------------------------------------------
void MGyrohorizon::SetPitchRollAngles(float pitch, float roll)
{
//  if((int)(PitchAngle0*100) != (int)(pitch*100) || (int)(RollAngle0*100) != (int)(roll*100)) {
  if((int)(PitchAngle*100) != (int)(pitch*100) || (int)(RollAngle*100) != (int)(roll*100)) {

//if(!IsReadyRedraw)  return;
//IsReadyRedraw = false;

//    PitchAngle0 = pitch;
//    RollAngle0 = roll;

    PitchAngle = pitch;
    RollAngle = roll;

    update();
  }
}
//--------------------------------------------------------------------------------------------
void MGyrohorizon::SetQuaternion(QQuaternion* pQuaternion)
{
  PEkranoplanGL->SetQuaternion(pQuaternion);
}
//--------------------------------------------------------------------------------------------
/*
void MGyrohorizon::SliderPitchPressed()
{
  IsSliderPitchPressed = true;

//QMessageBox msgBox(QMessageBox::Critical, SMessageBoxTitle, "GetPMainWnd() == NULL");   msgBox.exec();
//QMessageBox msgBox;  msgBox.setText("void MGyrohorizon::SliderPitchPressed()");  msgBox.exec();
}
//--------------------------------------------------------------------------------------------
void MGyrohorizon::SliderPitchReleased()
{
  IsSliderPitchPressed = false;
//QMessageBox msgBox;  msgBox.setText("void MGyrohorizon::SliderPitchReleased()");  msgBox.exec();
}
*/
//--------------------------------------------------------------------------------------------
