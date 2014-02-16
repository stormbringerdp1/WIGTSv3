#include "MPlot.h"
  #include "funcs.h"

#include <QPainter>
//#include <QStaticText>
  #include <QMessageBox>
  #include <QStatusBar>

//============================================================================================

extern int TimerInterval; // msec

//============================================================================================
MPlot::MPlot(QWidget* pParent, const bool isReport, const char* cYAxisLabel, float* pminYNormalValue, float* pmaxYNormalValue)
//             const qreal &xLeft, const qreal &xRight)
      : QFrame(pParent),
        IsReport(isReport), SYAxisLabel(cYAxisLabel)//, MinYNormalValue(minYNormalValue), MaxYNormalValue(maxYNormalValue)
{
  PMinYNormalValue = NULL;
  if(pminYNormalValue)  {
    PMinYNormalValue = new float;   *PMinYNormalValue = *pminYNormalValue;
  }

  PMaxYNormalValue = NULL;
  if(pmaxYNormalValue) {
    PMaxYNormalValue = new float;   *PMaxYNormalValue = *pmaxYNormalValue;
  }

//  IsReport = false;
//  IsReport = true;

  XStep = TimerInterval/1000.0; //1.0;  //  [sec]

  IxyOff = 5;
  IxyOffStroke = 3;    IxyStrokeLength = 7;  IxyArrow = 15;

  NYStroke = 11;  NXStroke = 7;

  NMaxVisibleCount = 31;

  RectCurve = QRectF(0.0,0.0,1.0,1.0);

//  if(!IsReport)  HScrollBar = 0;
//  else {         HScrollBar = 13;
  if(IsReport)  {
//      QRect rect = geometry();
    PScrollBar = new QScrollBar(this);
    PScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
//      PScrollBar->setGeometry(QRect(1, rect.height()-HScrollBar-1, rect.width()-1-1, HScrollBar));
    PScrollBar->setOrientation(Qt::Horizontal);
//    PScrollBar->setRange(0,0);
    connect(PScrollBar, SIGNAL(valueChanged(int)), this, SLOT(SliderMoved(int)));
  }

  Init();
}
//--------------------------------------------------------------------------------------------
MPlot::~MPlot()
{
  delete PMinYNormalValue;
  delete PMaxYNormalValue;
}
//--------------------------------------------------------------------------------------------
void MPlot::Init()
{
  YMinAllValue = std::numeric_limits<qreal>::max();  YMaxAllValue = std::numeric_limits<qreal>::min();
  PosSB = 0;
  if(IsReport)  PScrollBar->setRange(0,0);
}
//--------------------------------------------------------------------------------------------
bool MPlot::event(QEvent* event)
{
  bool b = QFrame::event(event); //catch different events
//--
  if(event->type() == QEvent::Polish) {//Polish is caught
    setObjectName(QStringLiteral("frame"));
    setFrameShape(QFrame::Box);

//    PosSB = 0;
    if(!IsReport)  HScrollBar = 0;
    else {         HScrollBar = 13;
      QRect rect = geometry();
//      PScrollBar = new QScrollBar(this);
//      PScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
      PScrollBar->setGeometry(QRect(1, rect.height()-HScrollBar-1, rect.width()-1-1, HScrollBar));
//      PScrollBar->setOrientation(Qt::Horizontal);
//      PScrollBar->setRange(0,0);
//      connect(PScrollBar, SIGNAL(valueChanged(int)), this, SLOT(SliderMoved(int)));
    }

  }
  return b;
}
//--------------------------------------------------------------------------------------------
void MPlot::SliderMoved(int pos)
{
//QMessageBox msgBox; msgBox.setText("void MPlot::SliderMoved(int pos)");   msgBox.exec();
//QString s; s.sprintf("%d",pos);  GetPMainWnd()->statusBar()->showMessage(s);
  PosSB = pos;
  update();
}
//--------------------------------------------------------------------------------------------
void MPlot::paintEvent(QPaintEvent* event)
{
//QMessageBox msgBox; msgBox.setText("void MPlot::paintEvent(QPaintEvent* event)");   msgBox.exec();

  QFrame::paintEvent(event);

  //create a QPainter and pass a pointer to the device.
  //A paint device can be a QWidget, a QPixmap or a QImage
  QPainter painter(this);

  Draw(painter);
/*
  //a simple line
  painter.drawLine(1,1,100,100);

  //create a black pen that has solid line
  //and the width is 2.
  QPen myPen(Qt::black, 2, Qt::SolidLine);
  painter.setPen(myPen);
  painter.drawLine(100,100,100,1);

  //draw a point
  myPen.setColor(Qt::red);
  painter.drawPoint(110,110);

  //draw a polygon
  QPolygon polygon;
  polygon << QPoint(130, 140) << QPoint(180, 170)
           << QPoint(180, 140) << QPoint(220, 110)
           << QPoint(140, 100);
   painter.drawPolygon(polygon);

   //draw an ellipse
   //The setRenderHint() call enables antialiasing, telling QPainter to use different
   //color intensities on the edges to reduce the visual distortion that normally
   //occurs when the edges of a shape are converted into pixels
   painter.setRenderHint(QPainter::Antialiasing, true);
   painter.setPen(QPen(Qt::black, 3, Qt::DashDotLine, Qt::RoundCap));
   painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));
   painter.drawEllipse(200, 80, 400, 240);
*/
}
//--------------------------------------------------------------------------------------------
void MPlot::Draw(QPainter& painter)
{
  painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
//  QFont font("Helvetica", 8);  font.setStyleStrategy(QFont::NoAntialias);
  QFont font(font());  font.setStyleStrategy(QFont::NoAntialias);
  painter.setFont(font);
//  painter.setFont(QFont("Ariel", 8, 1)); //QFont::Normal));
//  painter.setRenderHint(QPainter::Antialiasing, false);
//  painter.setRenderHint(QPainter::TextAntialiasing, true);
//  painter.setRenderHint(QPainter::SmoothPixmapTransform, false);


//====  Calc  fxMinValue, fxMaxValue, fyMinValue, fyMaxValue:  ====

//  qreal fx1, fx2, fy1, fy2;
//  GetRangeValues(fx1, fx2, fy1, fy2);
/*
  qreal fxMinValue, fxMaxValue, fyMinValue, fyMaxValue;
//  qreal fxFirstValue = 0.0;

  QList<QPointF>* pListValues = !IsReport ? &ListVisibleValues : &ListAllValues;
  int count = pListValues->count();
  if(count == 0)  { fxMinValue = 0.0;  fxMaxValue = 0.0;  fyMinValue = 0.0;  fyMaxValue = 0.0;  return; }
  else {
//    if(count == 1)  fxFirstValue = (*pListValues)[0].x();

    NItemVisibleLeft = 0;
    if(IsReport && ListAllValues.count() > NMaxVisibleCount) {
      int pos = PScrollBar->value();
      qreal gdel = RectCurve.width()/(NMaxVisibleCount-1);

//      int wAll = gdel*(ListAllValues.count()-1);

      int sbMax = gdel*(ListAllValues.count()-NMaxVisibleCount) + 0.5;
//QString s; s.sprintf("count = %d  RectCurve.width() = %.3f,  gdel = %.3f,   sbMax = %d", count, RectCurve.width(), gdel, sbMax);
//GetPMainWnd()->statusBar()->showMessage(s);
//QMessageBox msgBox; msgBox.setText(s);   msgBox.exec();
      PScrollBar->setMaximum(sbMax);
//      PScrollBar->setPageStep(gdel*NMaxVisibleCount);
      PScrollBar->setValue(pos);

if(gdel > 0.0)  NItemVisibleLeft = PosSB/gdel;// + 0.5;
    }

    QPointF fp;
    fxMinValue = std::numeric_limits<qreal>::max();  fxMaxValue = std::numeric_limits<qreal>::min();
    fyMinValue = fxMinValue;                         fyMaxValue = fxMaxValue;
    for(int i = NItemVisibleLeft; i < qMin(NItemVisibleLeft+NMaxVisibleCount, count); i++) {
      fp = (*pListValues)[i];
      if(fp.x() < fxMinValue)  fxMinValue = fp.x();
      if(fp.x() > fxMaxValue)  fxMaxValue = fp.x();
      if(fp.y() < fyMinValue)  fyMinValue = fp.y();
      if(fp.y() > fyMaxValue)  fyMaxValue = fp.y();
    }
  }

//  XMinValue = fx1;  XMaxValue = fx2;  YMinValue = fy1;  YMaxValue = fy2;


//====  Calc Offs:  ====

  QString s;  QRectF rectFLabel;   qreal gwMaxLabel = 0.0;  qreal ghMaxLabel = 0.0;

  qreal dfy = (fyMaxValue-fyMinValue)/(NYStroke-1);
  for(int i=0; i < NYStroke; i++) {
    s.sprintf("%.3g", fyMinValue + i*dfy);
    rectFLabel = painter.boundingRect(QRectF(0,0, 500,500), s, QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    gwMaxLabel = qMax(gwMaxLabel, rectFLabel.width());
    ghMaxLabel = qMax(ghMaxLabel, rectFLabel.height());
  }
  qreal gxOffAxisY = IxyOff + gwMaxLabel + IxyOffStroke + IxyStrokeLength/2.0;
  qreal gyOffAxisX = IxyOff + ghMaxLabel + IxyOffStroke + IxyStrokeLength/2.0 + HScrollBar;

  QRect rectPlot = geometry();
  qreal gy0Top = IxyOff+IxyArrow;  qreal gy0Bottom = rectPlot.height() - gyOffAxisX;
  qreal gx0Left = gxOffAxisY;      qreal gx0Right = rectPlot.width() - IxyOff - IxyArrow;

  RectCurve = QRectF(QPointF(gxOffAxisY, gy0Top), QPointF(gx0Right, gy0Bottom));
  QPointF gxy0LeftBottom(gx0Left, gy0Bottom);
  qreal gxWidth = RectCurve.width();
  qreal gyHeight = RectCurve.height();

//  painter.setClipRect(RectCurve);
//  qreal dgxValue = gxWidth/(NMaxVisibleCount-1);


  painter.drawText(QRectF(gxOffAxisY+10, IxyOff, 300,30), SYAxisLabel, QTextOption(Qt::AlignLeft | Qt::AlignTop));
  painter.drawText(QRectF(QPoint(0,0), QPoint(rectPlot.width()-1-IxyOff, gy0Bottom-5)), "T", QTextOption(Qt::AlignRight | Qt::AlignBottom));
//SXAxisLabel

//s.sprintf("count = %d  RectCurve.width() = %.3f", count, RectCurve.width());
//GetPMainWnd()->statusBar()->showMessage(s);

//====  Draw Axes, Grid:  ====

  QPen penAxis(QBrush(QColor(0,0,0)), 1, Qt::SolidLine, Qt::RoundCap);
  QPen penGrid(QBrush(QColor(89,89,89)), 0.25, Qt::SolidLine); //Qt::DotLine);

//=  Y Axis:
  QPointF pxy2(gx0Left, IxyOff);
  painter.setPen(penAxis);    painter.drawLine(gxy0LeftBottom, pxy2);
//=  Y Axis' Arrow:
  QPointF p(pxy2);  p += QPointF(-3, 10);   painter.drawLine(pxy2, p);
  p = pxy2;         p += QPointF(3, 10);    painter.drawLine(pxy2, p);
//=  Y Axis' Labels, Strokes, Grid:
  qreal gy;  qreal fy;
  qreal dgy = gyHeight/(NYStroke-1);
  qreal gx1Stroke = gx0Left - IxyStrokeLength/2.0;
  qreal gx2Stroke = gx0Left + IxyStrokeLength/2.0;
  for(int i=0; i < NYStroke; i++) {
    gy = gy0Bottom - i*dgy;
    painter.setPen(penAxis);    painter.drawLine(QPointF(gx1Stroke, gy), QPointF(gx2Stroke, gy));
    painter.setPen(penGrid);    painter.drawLine(QPointF(gx2Stroke, gy), QPointF(gx0Right, gy));

    fy = fyMinValue + i*dfy;  s.sprintf("%.3g", fy);
    painter.drawText(QRectF(IxyOff, gy-ghMaxLabel/2.0, gwMaxLabel, ghMaxLabel),
                     s, QTextOption(Qt::AlignRight | Qt::AlignVCenter));
  }

//=  X Axis:
  pxy2 = QPointF(rectPlot.width()-IxyOff , gy0Bottom);
  painter.setPen(penAxis);
  painter.drawLine(gxy0LeftBottom, pxy2);
//=  X Axis' Arrow:
  p = pxy2;  p += QPointF(-10, -3);   painter.drawLine(pxy2, p);
  p = pxy2;  p += QPointF(-10, 3);    painter.drawLine(pxy2, p);
//=  X Axis' Labels, Strokes, Grid:
  painter.setPen(penGrid);    painter.drawLine(QPointF(gx0Right, gy0Bottom), QPointF(gx0Right, gy0Top));  // <<--- Right DotLine
  qreal dfx = (fxMaxValue-fxMinValue)/(NXStroke-1);
  qreal gx;  qreal fx;
  qreal gy2Stroke = gy0Bottom - IxyStrokeLength/2.0;
  qreal gy1Stroke = gy0Bottom + IxyStrokeLength/2.0;
  qreal dgx = gxWidth/(NXStroke-1);
  int j = PosSB/dgx;
  int delLeft = (PosSB/dgx - j)*dgx;
  for(int i=0; i < NXStroke; i++) {
    gx = gx0Left - delLeft + i*dgx;
    if(gx < gx0Left)  continue;
    painter.setPen(penAxis);    painter.drawLine(QPointF(gx, gy1Stroke), QPointF(gx, gy2Stroke));
    painter.setPen(penGrid);    painter.drawLine(QPointF(gx, gy2Stroke), QPointF(gx, gy0Top));

    fx = fxMinValue + (j+i)*dfx;  s.sprintf("%.1f", fx);
//    fx = fxFirstValue + (j+i)*dfx;  s.sprintf("%.1f", fx);
    rectFLabel = painter.boundingRect(QRectF(0,0, 500,500), s, QTextOption());
    painter.drawText(QRectF(gx-rectFLabel.width()/2.0, rectPlot.height()-IxyOff-HScrollBar-rectFLabel.height(),
                            rectFLabel.width(),        rectFLabel.height()),
                     s, QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
  }


//====  Draw Curve:  ====

//  QList<QPointF>* pListValues = !IsReport ? &ListVisibleValues : &ListAllValues;
//  int count = pListValues->count();
  if(count == 0)  return;

  QPen penPoint(QBrush(QColor(0,200,60)), 6, Qt::SolidLine, Qt::RoundCap);
  QPen penLine(QBrush(QColor(0,0,250)), 1, Qt::DotLine);

  QPointF fp;
  QPointF gp1,gp2;

  qreal kx = 0.0;  qreal ky = 0.0;   qreal d;
  if((d = fxMaxValue-fxMinValue) != 0.0)  kx = RectCurve.width()/d;
  if((d = fyMaxValue-fyMinValue) != 0.0)  ky = RectCurve.height()/d;

  for(int i = 0; i < count; i++) {
//  for(int i = NItemVisibleLeft; i < qMin(NItemVisibleLeft+NMaxVisibleCount, count); i++) {
    fp = (*pListValues)[i];
gx = gx0Left - delLeft + kx*(fp.x()-fxMinValue);
if(gx < gx0Left)  continue;
    gy = gy0Top + ky*(fyMaxValue-fp.y());
    if(i == 0) { gp1 = QPointF(gx,gy);
        painter.setPen(penPoint);   painter.drawPoint(gp1);
    }
    else {   gp2 = QPointF(gx,gy);
      painter.setPen(penLine);    painter.drawLine(gp1, gp2);
      gp1 = gp2;
      painter.setPen(penPoint);   painter.drawPoint(gp2);
    }
  }
*/

//========================================================


//  painter.setPen(Qt::NoPen);
//  painter.setBrush(QBrush(QColor(255,255,255, 255)));
//  painter.drawRect(1,1,geometry().width()-2,geometry().height()-2);



  qreal fyMinValue, fyMaxValue; // fxMinValue, fxMaxValue,

  QList<QPointF>* pListValues = !IsReport ? &ListVisibleValues : &ListAllValues;

  int count = pListValues->count();
  if(count == 0)  {  fyMinValue = 0.0;  fyMaxValue = 0.0;  /*fxMinValue = 0.0;  fxMaxValue = 0.0;*/   return; }
  else {
    NItemVisibleLeft = 0;
    if(IsReport && ListAllValues.count() > NMaxVisibleCount) {
      qreal dgx = RectCurve.width()/(NMaxVisibleCount-1);
      int sbMax = dgx*(ListAllValues.count()-NMaxVisibleCount) + 0.5;
      PScrollBar->setMaximum(sbMax);
//      PScrollBar->setPageStep(gxdel*NMaxVisibleCount+0.5);
      PScrollBar->setPageStep(RectCurve.width()+0.5);
      NItemVisibleLeft = PosSB/dgx;// + 0.5;
    }

    QPointF fp;
    fyMinValue = std::numeric_limits<qreal>::max();  fyMaxValue = std::numeric_limits<qreal>::min();
    for(int i = NItemVisibleLeft; i < qMin(NItemVisibleLeft+NMaxVisibleCount, count); i++) {
      fp = (*pListValues)[i];
      if(fp.y() < fyMinValue)  fyMinValue = fp.y();
      if(fp.y() > fyMaxValue)  fyMaxValue = fp.y();
    }

    if(IsReport) {
      YMinAllValue = qMin(fyMinValue, YMinAllValue);   fyMinValue = YMinAllValue;
      YMaxAllValue = qMax(fyMaxValue, YMaxAllValue);   fyMaxValue = YMaxAllValue;
    }
  }

  qreal dfYMax = 0.0;
  if(PMaxYNormalValue) {
    if(fyMaxValue < *PMaxYNormalValue)  fyMaxValue = *PMaxYNormalValue;
    dfYMax = fyMaxValue - *PMaxYNormalValue;
  }
  qreal dfYMin = 0.0;
  if(PMinYNormalValue) {
    if(*PMinYNormalValue < fyMinValue)  fyMinValue = *PMinYNormalValue;
    dfYMin = *PMinYNormalValue - fyMinValue;
  }


//====  Calc Offs:  ====

  QString s;  QRectF rectFLabel;   qreal gwMaxLabel = 0.0;  qreal ghMaxLabel = 0.0;

  qreal dfy = (fyMaxValue-fyMinValue)/(NYStroke-1);
  for(int i = 0; i < NYStroke; i++) {
    s.sprintf("%.3g", fyMinValue + i*dfy);
    rectFLabel = painter.boundingRect(QRectF(0,0, 500,500), s, QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
    gwMaxLabel = qMax(gwMaxLabel, rectFLabel.width());
    ghMaxLabel = qMax(ghMaxLabel, rectFLabel.height());
  }
  qreal gxOffAxisY = IxyOff + gwMaxLabel + IxyOffStroke + IxyStrokeLength/2.0;
  qreal gyOffAxisX = IxyOff + ghMaxLabel + IxyOffStroke + IxyStrokeLength/2.0 + HScrollBar;

  QRect rectPlot = geometry();
  qreal gy0Top = IxyOff+IxyArrow;  qreal gy0Bottom = rectPlot.height() - gyOffAxisX;
  qreal gx0Left = gxOffAxisY;      qreal gx0Right = rectPlot.width() - IxyOff - IxyArrow;

  RectCurve = QRectF(QPointF(gxOffAxisY, gy0Top), QPointF(gx0Right, gy0Bottom));
  QPointF gxy0LeftBottom(gx0Left, gy0Bottom);
  qreal gxWidth = RectCurve.width();
  qreal gyHeight = RectCurve.height();

//  painter.setClipRect(RectCurve);
//  qreal dgxValue = gxWidth/(NMaxVisibleCount-1);

  painter.drawText(QRectF(gxOffAxisY+10, IxyOff-2, 300,30), SYAxisLabel, QTextOption(Qt::AlignLeft | Qt::AlignTop));
  painter.drawText(QRectF(QPoint(0,0), QPoint(rectPlot.width()-1-IxyOff, gy0Bottom-5)), "T", QTextOption(Qt::AlignRight | Qt::AlignBottom));


//====  Draw Axes, Grid:  ====

  QPen penAxis(QBrush(QColor(0,0,0)), 1, Qt::SolidLine, Qt::RoundCap);
  QPen penGrid(QBrush(QColor(89,89,89)), 0.25, Qt::SolidLine); //Qt::DotLine);

//=  Y Axis:
  QPointF pxy2(gx0Left, IxyOff);
  painter.setPen(penAxis);    painter.drawLine(gxy0LeftBottom, pxy2);
//=  Y Axis' Arrow:
  QPointF p(pxy2);  p += QPointF(-3, 10);   painter.drawLine(pxy2, p);
  p = pxy2;         p += QPointF(3, 10);    painter.drawLine(pxy2, p);
//=  Y Axis' Labels, Strokes, Grid:
  qreal gy;  qreal fy;
  qreal dgy = gyHeight/(NYStroke-1);
  qreal gx1Stroke = gx0Left - IxyStrokeLength/2.0;
  qreal gx2Stroke = gx0Left + IxyStrokeLength/2.0;
  for(int i = 0; i < NYStroke; i++) {
    gy = gy0Bottom - i*dgy;
    painter.setPen(penAxis);    painter.drawLine(QPointF(gx1Stroke, gy), QPointF(gx2Stroke, gy));
    painter.setPen(penGrid);    painter.drawLine(QPointF(gx2Stroke, gy), QPointF(gx0Right, gy));

    fy = fyMinValue + i*dfy;  s.sprintf("%.3g", fy);
    painter.drawText(QRectF(IxyOff, gy-ghMaxLabel/2.0, gwMaxLabel, ghMaxLabel),
                     s, QTextOption(Qt::AlignRight | Qt::AlignVCenter));
  }

//=  X Axis:
  pxy2 = QPointF(rectPlot.width()-IxyOff , gy0Bottom);
  painter.setPen(penAxis);
  painter.drawLine(gxy0LeftBottom, pxy2);
//=  X Axis' Arrow:
  p = pxy2;  p += QPointF(-10, -3);   painter.drawLine(pxy2, p);
  p = pxy2;  p += QPointF(-10, 3);    painter.drawLine(pxy2, p);
//=  X Axis' Labels, Strokes, Grid:
  painter.setPen(penGrid);    painter.drawLine(QPointF(gx0Right, gy0Bottom), QPointF(gx0Right, gy0Top));  // <<--- Right DotLine
//  qreal dfx = (fxMaxValue-fxMinValue)/(NXStroke-1);
  qreal dgx = gxWidth/(NXStroke-1);
  int j = PosSB/dgx;
  int delLeft = (-PosSB/dgx + j)*dgx;
  qreal gy2Stroke = gy0Bottom - IxyStrokeLength/2.0;
  qreal gy1Stroke = gy0Bottom + IxyStrokeLength/2.0;
  qreal dfx = (XStep*(NMaxVisibleCount-1))/(NXStroke-1);
  qreal gx;  qreal fx;
  for(int i = 0; i < NXStroke; i++) {
    gx = gx0Left + delLeft + i*dgx;
    if(gx < gx0Left)  continue;
    painter.setPen(penAxis);    painter.drawLine(QPointF(gx, gy1Stroke), QPointF(gx, gy2Stroke));
    painter.setPen(penGrid);    painter.drawLine(QPointF(gx, gy2Stroke), QPointF(gx, gy0Top));
    fx = (*pListValues)[0].x() + (j+i)*dfx;  s.sprintf("%.1f", fx);
    rectFLabel = painter.boundingRect(QRectF(0,0, 500,500), s, QTextOption());
    painter.drawText(QRectF(gx-rectFLabel.width()/2.0, rectPlot.height()-IxyOff-HScrollBar-rectFLabel.height(),
                            rectFLabel.width(),        rectFLabel.height()),
                     s, QTextOption(Qt::AlignLeft | Qt::AlignVCenter));
  }


//===  Y Normal Range:  ===

  qreal ky = 0.0;  qreal d;
  if((d = fyMaxValue-fyMinValue) != 0.0)  ky = RectCurve.height()/d;

  QPen penRange(QBrush(QColor(255,0,0)), 1, Qt::SolidLine, Qt::RoundCap);
  painter.setPen(penRange);

  qreal gyMax = 0.0;
  if(PMaxYNormalValue) {
//  if(fyMinValue <= MaxYNormalValue && MaxYNormalValue <= fyMaxValue) {
    gyMax = gy0Top + ky*(fyMaxValue - *PMaxYNormalValue);
//    painter.setPen(penRange); painter.drawLine(QPointF(gx0Left, gy), QPointF(gx0Right, gy));
    painter.drawLine(QPointF(gx0Left+1.0, gyMax), QPointF(gx0Right-1.0, gyMax));
//  }
  }
  qreal gyMin = 0.0;
  if(PMinYNormalValue) {
//  if(fyMinValue <= MinYNormalValue && MinYNormalValue <= fyMaxValue) {
    gyMin = gy0Top + ky*(fyMaxValue - *PMinYNormalValue);
//    painter.setPen(penRange); painter.drawLine(QPointF(gx0Left, gy), QPointF(gx0Right, gy));
    painter.drawLine(QPointF(gx0Left+1.0, gyMin), QPointF(gx0Right-1.0, gyMin));
//  }
  }


//====  Draw Curve:  ====

  if(count == 0)  return;

  QPen penPoint(QBrush(QColor(0,0,0)), 6, Qt::SolidLine, Qt::RoundCap); //  QColor(0,0,0) <-- here any
  QPen penLine(QBrush(QColor(0,0,250)), 1, Qt::DotLine);

  QPointF fp;
  QPointF gp1,gp2;

  dgx = gxWidth/(NMaxVisibleCount-1);
  j = PosSB/dgx;
  delLeft = (-PosSB/dgx + j)*dgx;   bool isNornalValue;
  for(int i = NItemVisibleLeft; i < qMin(NItemVisibleLeft+NMaxVisibleCount+1, count); i++) {
    gx = gx0Left + delLeft + (i-NItemVisibleLeft)*dgx;
    fp = (*pListValues)[i];

    isNornalValue = true;
    if(PMinYNormalValue) {
      if(fp.y() < *PMinYNormalValue)  isNornalValue = false;
    }
    if(PMaxYNormalValue) {
      if(*PMaxYNormalValue < fp.y())  isNornalValue = false;
    }
    if(isNornalValue)  penPoint.setBrush(QColor(0,200,60));
    else               penPoint.setBrush(QColor(200,0,60));

    gy = gy0Top + ky*(fyMaxValue-fp.y());
    if(i == NItemVisibleLeft) {  gp1 = QPointF(gx,gy);
      if(gx >= gx0Left && gx <= gx0Right)  {
        painter.setPen(penPoint);   painter.drawPoint(gp1);
      }
    }
    else {   gp2 = QPointF(gx,gy);
      painter.setPen(penLine);
      if(gp1.x() < gx0Left) {   qreal x1 = gp1.x();
        gp1.setX(gx0Left);
        gp1.setY(gp1.y()+(gx0Left-x1)*(gp2.y()-gp1.y())/(gp2.x()-x1));
      }
      if(gp2.x() > gx0Right) {   qreal x2 = gp2.x();
        gp2.setX(gx0Right);
        gp2.setY(gp1.y()+(gx0Right-gp1.x())*(gp2.y()-gp1.y())/(x2-gp1.x()));
      }
      painter.drawLine(gp1, gp2);

      gp1 = gp2;
      if(gx >= gx0Left && gx <= gx0Right)  {
        painter.setPen(penPoint);   painter.drawPoint(gp2);
      }
    }
  }

//===  Y UnNormal Ranges:  ===

  if(dfYMax > 0.0 || dfYMin > 0.0) {
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(QColor(255,100,100, 50)));
    if(dfYMax > 0.0)  painter.drawRect(QRectF(gx0Left,gy0Top, gxWidth+1.0,gyMax-gy0Top));
    if(dfYMin > 0.0)  painter.drawRect(QRectF(gx0Left-1.0,gyMin, gxWidth+2.0,gy0Bottom-gyMin));
  }
}
//--------------------------------------------------------------------------------------------
void MPlot::AddValue(const qreal& fx, const qreal& fy)
{
//QString s; s.sprintf("fx = %.3f,   fy = %.3f", fx, fy);
//GetPMainWnd()->statusBar()->showMessage(s);
//QMessageBox msgBox; msgBox.setText(s);   msgBox.exec();

  int count = ListVisibleValues.count();
  if(count >= NMaxVisibleCount) {
    ListVisibleValues.removeFirst();
//    if(IsReport) {  if(!PScrollBar->isEnabled())  PScrollBar->setEnabled(true); }
  }
  QPointF fp(fx,fy);
  ListVisibleValues << fp;
  if(IsReport) {
    ListAllValues << fp;
  }

  update();

//  if(fy < MinYNormalValue || MaxYNormalValue < fy) {
//    emit SignalNotNormalValue(this);
//  }
}
//--------------------------------------------------------------------------------------------
/*
void MPlot::AddValue(const QString& sx, const qreal& fy)
{
//QMessageBox msgBox; msgBox.setText(sx);   msgBox.exec();

  qreal fx = sx.toFloat();
  AddValue(fx, fy);
}
*/
//--------------------------------------------------------------------------------------------
void MPlot::Clear()
{
  ListVisibleValues.clear();
  if(IsReport)  ListAllValues.clear();

  Init();

  update();
}
//--------------------------------------------------------------------------------------------
