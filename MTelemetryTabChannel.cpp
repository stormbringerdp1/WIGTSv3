#include "MTelemetryTabChannel.h"
//#include "MTelemetryTabWidgetChannels.h"
//#include "MTelemetryTabBarChannels.h"
#include "MArduinoConnector.h"
#include "funcs.h"
//#include "constants.h"

#include <QTabWidget>
#include <QTabBar>
#include <QtGlobal>
#include <QDateTime>
#include <QMessageBox>

//===
extern char CharWriteTelemetryModeOccasionally; // = 'o';

//= For Altitude and Speed TabChannel "H, S":
extern int   IndexTabChannel_HS; // = 5;
extern const char* CharsCodeAltitudeSpeed; // = "as2 ";

//= For Pitch and Roll TabChannel "Angles":
extern int   IndexTabChannel_Angles; // = 6;
extern const char* CharsCodeQuaternion; // = "q4 ";

//= For Temperature and Pressure TabChannel "T, P":
extern int   IndexTabChannel_TP; // = 8;
extern const char* CharsCodeTemperaturePressure; // = "tp2 ";

extern char CharSeparator; // = ' ';
//===

extern QString SNameTelemetryTabChannel_HS;
extern QString SNameTelemetryTabChannel_Angles;
extern QString SNameTelemetryTabChannel_TP;

//============================================================================================
//bool GetTempValues(QString* pStrValues, const char* charsCodeValues, const int nvalues, float* tempValues)
//bool GetTempValues(const char* pCharsValues, const char* charsCodeValues, const int nvalues, float* tempValues)
void GetTempValues(const char* pCharsValues, const char* charsCodeValues, const int* pnvalues, float* tempValues)
{
//QTextStream* pStream = GetPMainWnd()->GetPTelemetry()->GetPStreamFileReport();

//*pStream << *pStrValues;  *pStream << " : "; *pStream << "\"";  *pStream << charsValues; *pStream << "\"";  *pStream << "\n";

  QString* pStrValues = new QString(pCharsValues);

//  int pos1 = 0;  int pos2;
  int* ppos1 = new int;   *ppos1 = 0;
  int* ppos2 = new int;

  if(charsCodeValues) {
    *ppos1 = pStrValues->indexOf(charsCodeValues); // "6oq4 0.123 -4.567 8.910 11.121"  or  "-0.123 4.567"  or  ...
//    if(pos1 < 0) { delete pStrValues;  return false;  }
    Q_ASSERT(*ppos1 >= 0);

    *ppos2 = pStrValues->indexOf(CharSeparator, *ppos1);
    int* pn = new int;  *pn = pStrValues->at(*ppos2 - 1).digitValue();
    Q_ASSERT(*pn == *pnvalues);
    delete pn;
//if(n != nvalues) {
//  QString s; s.sprintf("n = %d,  nvalues = %d\n\n", n,nvalues);  s += *pStrValues;
//  QMessageBox msg;  msg.setText(s);  msg.exec();
//}
    *ppos1 = *ppos2 + 1;
  }

  int* pi = new int;  *pi = -1;
  while(*ppos1 < pStrValues->length()) {  *pi += 1;
    *ppos2 = pStrValues->indexOf(CharSeparator, *ppos1);
    if(*ppos2 < 0)  *ppos2 = pStrValues->length();
    tempValues[*pi] = pStrValues->mid(*ppos1, *ppos2 - *ppos1).toFloat();
    *ppos1 = *ppos2 + 1;
  }

  Q_ASSERT(*pi + 1 == *pnvalues);

  delete pi;
  delete ppos1;  delete  ppos2;
  delete pStrValues;


//if(i+1 != nvalues) {
//  QString s; s.sprintf("i+1 = %d,  nvalues = %d\n\n", i+1,nvalues);  s += *pStrValues;
//  QMessageBox msg;  msg.setText(s);  msg.exec();
//}
//  return true;
}
//--------------------------------------------------------------------------------------------
void GetYawPitchRoll(float* ypr, float* q)
//void FreeSixIMU::getYawPitchRoll(float * ypr) {
{
/*++++
//  float q[4]; // quaternion
  float gx, gy, gz; // estimated gravity direction
//  getQ(q);

  gx = 2.0*(q[1]*q[3]-q[0]*q[2]);
  gy = 2.0*(q[0]*q[1]+q[2]*q[3]);
  gz = q[0]*q[0]-q[1]*q[1]-q[2]*q[2]+q[3]*q[3];

  ypr[0] = atan2(2.0*q[1]*q[2]-2.0*q[0]*q[3], 2.0*q[0]*q[0]+2.0*q[1]*q[1]-1.0)*180.0/M_PI;
  ypr[1] = atan(gx/sqrt(gy*gy+gz*gz))*180.0/M_PI;
  ypr[2] = atan(gy/sqrt(gx*gx+gz*gz))*180.0/M_PI;
*/
//---
  q[2] = -q[2];

//=Yaw:
  ypr[0] = atan2(-2.0*(q[1]*q[2]-q[0]*q[3]), 2.0*(q[1]*q[1]+q[0]*q[0])-1.0)*180.0/M_PI;

//=Roll:
  float qx = -2.0*(q[2]*q[3]-q[1]*q[0]);
  float qy = 2.0*(q[3]*q[3]+q[0]*q[0])-1.0;
  float q2 = atan2(qx, qy);
  ypr[2] = q2*180.0/M_PI;

//=Pitch:
  float q1 = 2.0*(q[1]*q[3]+q[2]*q[0]);
  if((45.0 <= ypr[2] && ypr[2] <= 135.0) || (-135.0 <= ypr[2] && ypr[2] <= -45.0)) {
    ypr[1] = atan2(q1, qx/sin(q2));
  }
  else {
    ypr[1] = atan2(q1, qy/cos(q2));
  }
  ypr[1] = ypr[1]*180.0/M_PI;

//---
  q[2] = -q[2];
  q[1] = -q[1];
}
//============================================================================================
MTelemetryTabChannel::MTelemetryTabChannel(QWidget* parent, QList<QString>* pListParamsTelemetryChannel, int iFirstItemListParamsTelemetry)
                    : QWidget(parent),
                      PListParamsTelemetryChannel(pListParamsTelemetryChannel), IFirstItemListParamsTelemetry(iFirstItemListParamsTelemetry)
{
//  MTelemetryTabWidgetChannels* pTabWidgetChannels = qobject_cast<MTelemetryTabWidgetChannels*>(parent);
//  Q_ASSERT(pTabWidgetChannels != NULL); // Q_CHECK_PTR(pTabWidgetChannels);
//  MTelemetryTabBarChannels* pTabBarChannels = qobject_cast<MTelemetryTabBarChannels*>(pTabWidgetChannels->tabBar());
//  Q_ASSERT(pTabBarChannels != NULL); // Q_CHECK_PTR(pTabBarChannels);

//float** PMMinValues = new float*[];

  QTabWidget* pTabWidget = qobject_cast<QTabWidget*>(parent);
  Q_ASSERT(pTabWidget != NULL); // Q_CHECK_PTR(pTabWidgetChannels);
//  QTabBar* pTabBar = qobject_cast<QTabBar*>(pTabWidget->tabBar());
  QTabBar* pTabBar = pTabWidget->tabBar();
  Q_ASSERT(pTabBar != NULL); // Q_CHECK_PTR(pTabBarChannels);

  MPlot* pPlot;    QString s;
  int yTopName = pTabBar->rect().height();// + 10;
  QRect rectPlot(10,yTopName+6, 321,321);
  int xLeftName = rectPlot.left() + rectPlot.width()/2 - 30;

//  IFirstItemListParamsTelemetry = GetPMainWnd()->GetIFirstItemListParamsTelemetry();
//  DeltaNItemListParamsTelemetry = GetPMainWnd()->GetDeltaNItemListParamsTelemetry();

//  ICurrentParam = 0;

  for(int i = IFirstItemListParamsTelemetry; i < PListParamsTelemetryChannel->count(); i += 3) { //DeltaNItemListParamsTelemetry) {
/*
    pLineEditNameParam = new QLineEdit(parent);
    pLineEditNameParam->setObjectName(QStringLiteral("LineEditNameParam"));
//    rect = QRect(xLeftName, yTopName, 100, 20);
    pLineEditNameParam->setGeometry(QRect(xLeftName, yTopName, 300, 20));
    pLineEditNameParam->setFrame(false);
    pLineEditNameParam->setReadOnly(true);
    pLineEditNameParam->setStyleSheet(QLatin1String("background: transparent;"));
    pLineEditNameParam->setAlignment(Qt::AlignCenter);
    s = "Current Value of ";  s = (*PListParamsChannel)[i];
    pLineEditNameParam->setText(s);
*/
    xLeftName += rectPlot.width()+10;
/*+
    float minValue = (*PListParamsTelemetryChannel)[i+1].toFloat();   ListMinNormalValues << minValue;
    float maxValue = (*PListParamsTelemetryChannel)[i+2].toFloat();   ListMaxNormalValues << maxValue;
//    pPlot = new MPlot(this, false, (*PListParamsTelemetryChannel)[i].toStdString().c_str());//,0.0, 10.0);
    pPlot = new MPlot(this, false, (*PListParamsTelemetryChannel)[i].toStdString().c_str(), minValue, maxValue);
*/
    float* pminValue = NULL;
    if((*PListParamsTelemetryChannel)[i+1] != "N/A") {
      pminValue = new float;   *pminValue = (*PListParamsTelemetryChannel)[i+1].toFloat();
    }
    ListPMinNormalValues << pminValue;

    float* pmaxValue = NULL;
    if((*PListParamsTelemetryChannel)[i+2] != "N/A") {
      pmaxValue = new float;  *pmaxValue = (*PListParamsTelemetryChannel)[i+2].toFloat();
    }
    ListPMaxNormalValues << pmaxValue;

    pPlot = new MPlot(this, false, (*PListParamsTelemetryChannel)[i].toStdString().c_str(), pminValue, pmaxValue);
    pPlot->setGeometry(rectPlot);

//    connect(this, SIGNAL(SignalNotNormalValue()), pTabBar, SLOT(SlotNotNormalValue()));

    ListPlots << pPlot;
    RectChannel |= rectPlot;

    if(i == 1)  RectChannel = rectPlot;
    else        RectChannel |= rectPlot;

    rectPlot.translate(rectPlot.width()+10,0);
  }
//  RectChannel.setRight(RectChannel.right()+15);


  IsFlicker = false;   IsFlickerBrush = false;
//  IsNonNormalMaxValue = false;  IsNonNormalMinValue = false;
//  ColorBrushTabFlicker = QColor(255,0,0, 100);
  for(int i = 0; i < ListPlots.count(); i++) {
    ListIsNonNormalMaxValue << false;
    ListIsNonNormalMinValue << false;
  }

  MValues = new float[ListPlots.count()];

//  IsReadyTakeValues = true;

//--
/*
  bool isToReadValuesContinuously = false;    bool isdArduinoValue = false;

//====  Changing the values of:  ====
//   "isToReadValuesContinuously"  or  "isdArduinoValue"  --->>  Change contents of the corresponding file "sketch.ino" sections:
//   "Continuously Sent Data:"  and  "Occasionally Sent Data:"

  if(*GetPNameChannel() == SNameTelemetryTabChannel_Angles) {
    isToReadValuesContinuously = true;   isdArduinoValue = true;
//QMessageBox msg; msg.setText(SNameTelemetryTabChannel_Angles);  msg.exec();
  }

//  GetPMainWnd()->GetPArduinoConnector()->AddSlotTelemetryTabChannel(this, ListPlots.count(), isToReadValuesContinuously, isdArduinoValue);
  connect(this,                                  SIGNAL(SignalAddSlotTelemetryTabChannel(MTelemetryTabChannel*,int,bool,bool)),
          GetPMainWnd()->GetPArduinoConnector(), SLOT(SlotAddSlotTelemetryTabChannel(MTelemetryTabChannel*,int,bool,bool)));
  emit SignalAddSlotTelemetryTabChannel(this, ListPlots.count(), isToReadValuesContinuously, isdArduinoValue);
*/


  IsArduinoValues = false;

  if(*GetPNameChannel() == SNameTelemetryTabChannel_HS ||
     *GetPNameChannel() == SNameTelemetryTabChannel_Angles ||
     *GetPNameChannel() == SNameTelemetryTabChannel_TP) {
//====  Adding "*GetPNameChannel() == SNameTelemetryTabChannel_..."  --->>  Change contents of:
//  1) the corresponding file "sketch.ino" sections:  "Continuously Sent Data:"  and  "Occasionally Sent Data:")
//  2) void MArduinoConnector::SlotGetAllTelemetryValues():  after  "if(PPort == NULL)"

    IsArduinoValues = true;

//QMessageBox msg; msg.setText(SNameTelemetryTabChannel_Angles);  msg.exec();
  }

  connect(this,                                  SIGNAL(SignalAddSlotTelemetryTabChannel(MTelemetryTabChannel*,bool)),
          GetPMainWnd()->GetPArduinoConnector(), SLOT(SlotAddSlotTelemetryTabChannel(MTelemetryTabChannel*,bool)));
  emit SignalAddSlotTelemetryTabChannel(this, IsArduinoValues);

  connect(&Timer, SIGNAL(timeout()), this, SLOT(SlotTimerSignal()));
}
//--------------------------------------------------------------------------------------------
MTelemetryTabChannel::~MTelemetryTabChannel()
{
  for(int i = 0; i < ListPMinNormalValues.count(); i++) { delete ListPMinNormalValues[i]; }
  for(int i = 0; i < ListPMaxNormalValues.count(); i++) { delete ListPMaxNormalValues[i]; }

  delete[] MValues;  MValues = NULL;
}
//--------------------------------------------------------------------------------------------
bool MTelemetryTabChannel::event(QEvent* event)
{
  bool b = QWidget::event(event); //catch different events
//--
  if(event->type() == QEvent::Polish) {//Polish is caught

    int xLeftName = 20;   QLineEdit* pLineEditCurrentParam;

    for(int i = 0; i < ListPlots.count(); i++) {

/*
      pLineEditNameParam = new QLineEdit(ListPlots[i]->parentWidget());
//      pLineEditNameParam->setObjectName(QStringLiteral("LineEditNameParam"));
      pLineEditNameParam->setGeometry(QRect(xLeftName, 15, 300, 20));
      pLineEditNameParam->setFrame(false);
      pLineEditNameParam->setReadOnly(true);
      pLineEditNameParam->setStyleSheet(QLatin1String("background: transparent;"));
      pLineEditNameParam->setAlignment(Qt::AlignLeft);//Center);
      pLineEditNameParam->setText("Current Value of "
                                  + *GetPNameParamInChannel(i) //(*PListParamsTelemetryChannel)[IFirstItemListParamsTelemetry + i*3] //DeltaNItemListParamsTelemetry]
                                  + ":");
      pLineEditCurrentParam = new QLineEdit(ListPlots[i]->parentWidget());
//      pLineEditCurrentParam->setObjectName(QStringLiteral("LineEditNameParam"));
      pLineEditCurrentParam->setGeometry(QRect(xLeftName+245, 15, 50, 20));
      pLineEditCurrentParam->setFrame(false);
      pLineEditCurrentParam->setReadOnly(true);
      pLineEditCurrentParam->setStyleSheet(QLatin1String("background: transparent;"));
      pLineEditCurrentParam->setAlignment(Qt::AlignRight);//Center);
*/
      pLineEditCurrentParam = CreateLineEditCurrentValue(ListPlots[i]->parentWidget(),
                                                         QRect(xLeftName,10, 300,20),
                                                         "Current Value of " + *GetPNameParamInChannel(i) + ":",
                                                         QRect(xLeftName+245,10, 50,20));
      ListLineEditCurrentParams << pLineEditCurrentParam;

      xLeftName += 330;
    }

/*
    setObjectName(QStringLiteral("TelemetryTabChannel")); //tab"));

    MPlot* pPlot;  QRect rect(20,120, 321,321);
    for(int i = 0; i < PListParamsChannel->count(); i++) {
      pPlot = new MPlot(this, false, (*PListParamsChannel)[i], "t (sec)", 0.0, 10.0); // Plot moves to the left
      pPlot->setGeometry(rect);
      ListPlots << pPlot;
      if(i ==0)  RectChannel = rect;
      else       RectChannel |= rect;
      rect.translate(rect.width()+10,0);
    }

//    pPlot = new MPlot(this, true, "YAxisLabel", "XAxisLabel", 0.0, 10.0); // Plot does not move
//    pPlot->setGeometry(QRect(360, 120, 321, 321));
//    ListPlots << pPlot;


//    QRect rect = pPlot->geometry();
//    PScrollBar = new QScrollBar(this);
//    PScrollBar->setObjectName(QStringLiteral("horizontalScrollBar"));
//    PScrollBar->setGeometry(QRect(rect.left(), rect.bottom()+1, rect.width(), 16));
//    PScrollBar->setOrientation(Qt::Horizontal);

*/
  }
  return b;
}
//--------------------------------------------------------------------------------------------
/*
void MTelemetryTabChannel::paintEvent(QPaintEvent* event)
{
  QWidget::paintEvent(event);
  return;
}
*/
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::AddAssignCorrespondingReportPlot(MPlot* pCorrespondingReportPlot)
{
  ListCorrespondingReportPlots << pCorrespondingReportPlot;
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::AddAssignCorrespondingInfoParam(QLineEdit* pLineEditInfoParam)
{
  ListCorrespondingInfoParams << pLineEditInfoParam;
}
//--------------------------------------------------------------------------------------------
/*+
void MTelemetryTabChannel::BeginGetArduinoValues()
{
  ICurrentParam = -1;

//  GetPMainWnd()->CreateArduinoObject(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), SLOT(SlotGetTelemetryValue(QString*,QString*)),
//                                           SIGNAL(SignalResultGetTelemetryValue(bool,float*,int)), SLOT(SlotResultGetTelemetryValue(bool,float*,int)));
  connect(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), GetPMainWnd()->GetPArduinoObject(), SLOT(SlotGetTelemetryValue(QString*,QString*)));
  connect(GetPMainWnd()->GetPArduinoObject(), SIGNAL(SignalResultGetTelemetryValue(bool,float*,int)), this, SLOT(SlotResultGetTelemetryValue(bool,float*,int)));
  GetNextArduinoValue();
}
*/
//--------------------------------------------------------------------------------------------
/*+
void MTelemetryTabChannel::GetNextArduinoValue()
{
  ICurrentParam += 1;
*/
/*
  if(ICurrentParam < ListPlots.count()) {
    emit SignalGetTelemetryValue(&(*PListParamsChannel)[0], &(*PListParamsChannel)[ICurrentParam+1]);
  }
  else {
//    GetPMainWnd()->DestroyArduinoObject();
    if(!disconnect(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), GetPMainWnd()->GetPArduino(), SLOT(SlotGetTelemetryValue(QString*,QString*)))) {
      QMessageBox msgBox(QMessageBox::Warning, "void MTelemetryTabChannel::GetNextArduinoValue()",
                         "Problem::\n\ndisconnect(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), GetPMainWnd()->GetPArduino(), SLOT(SlotGetTelemetryValue(QString*,QString*))) == false");
      msgBox.exec();
    }
    if(!disconnect(GetPMainWnd()->GetPArduino(), SIGNAL(SignalResultGetTelemetryValue(bool,float*,int)), this, SLOT(SlotResultGetTelemetryValue(bool,float*,int)))) {
      QMessageBox msgBox(QMessageBox::Warning, "void MTelemetryTabChannel::GetNextArduinoValue()",
                         "Problem::\n\ndisconnect(GetPMainWnd()->GetPArduino(), SIGNAL(SignalResultGetTelemetryValue(bool,float*,int)), this, SLOT(SlotResultGetTelemetryValue(bool,float*,int))) == false");
      msgBox.exec();
    }
    emit SignalChannelTelemetryDoneParam(true);
  }
*/
/*+

  emit SignalGetTelemetryValue(GetPNameChannel(),//&(*PListParamsTelemetryChannel)[0],
                               GetPNameParamInChannel(ICurrentParam)); //&(*PListParamsTelemetryChannel)[IFirstItemListParamsTelemetry + ICurrentParam*3]); //DeltaNItemListParamsTelemetry]);
}
*/
//--------------------------------------------------------------------------------------------
//+void MTelemetryTabChannel::SlotResultGetTelemetryValue(bool isOK, float* pFloatValues, int floatReadLength)
//void MTelemetryTabChannel::SlotTakeTelemetryParamValue(MTelemetryTabChannel* pTelemetryTabChannel, float value)
//void MTelemetryTabChannel::SlotTakeTelemetryStrValues(MTelemetryTabChannel* pTelemetryTabChannel, QString* pStrValues)
void MTelemetryTabChannel::SlotTakeTelemetryStrValues(MTelemetryTabChannel* pTelemetryTabChannel, const char* pCharsValues)
{
  if(pTelemetryTabChannel != this)  return;

//  if(!IsReadyTakeValues)  { delete[] pCharsValues;  return; }
//  IsReadyTakeValues = false;

//QMessageBox msg;  msg.setText("void MTelemetryTabChannel::SlotTakeTelemetryParamValue(...)");  msg.exec();

//  float* mValues = new float[2];

  if(IsArduinoValues) {

    if(*GetPNameChannel() == SNameTelemetryTabChannel_HS) {
//= Altitude and Speed:
// "5oas2 12 28.123"

//      if(pCharsValues[1] != CharWriteTelemetryModeOccasionally)  {
//        delete[] pCharsValues;  IsReadyTakeValues = true;  // delete[] mValues;
//        return;
//      }
      Q_ASSERT(QChar(pCharsValues[0]).digitValue() == IndexTabChannel_HS);
      Q_ASSERT(pCharsValues[1] == CharWriteTelemetryModeOccasionally);

      int nvalues = 2;
//      float* altitudeSpeed = new float[nvalues];

      GetTempValues(pCharsValues, CharsCodeAltitudeSpeed, &nvalues, MValues);
//      if(!GetTempValues(pCharsValues, CharsCodeAltitudeSpeed, 2, MValues))  {
//        delete[] pCharsValues;  IsReadyTakeValues = true;  // delete[] mValues;
//        return;
//      }

//      mValues[0] = altitudeSpeed[0];  //  Altitude for ICurrentParam == 0
//      mValues[1] = altitudeSpeed[1];  //  Speed  for ICurrentParam == 1

//      delete[] altitudeSpeed;
    }
    else if(*GetPNameChannel() == SNameTelemetryTabChannel_Angles) {
//= Angles (Quaternion):
// "6oq4 0.123 -4.567 8.910 11.121"  or  "6q4 0.123 -4.567 8.910 11.121"

      Q_ASSERT(QChar(pCharsValues[0]).digitValue() == IndexTabChannel_Angles);

      int* pnvalues = new int;  *pnvalues = 4;
      float* quaternion = new float[*pnvalues];

      GetTempValues(pCharsValues, CharsCodeQuaternion, pnvalues, quaternion);
      delete pnvalues;
//      if(!GetTempValues(pCharsValues, CharsCodeQuaternion, nvalues, quaternion))  {
//        delete[] pCharsValues;  delete[] quaternion;  IsReadyTakeValues = true;
//        return;
//      }

      float* yawPitchRoll = new float[3];
      GetYawPitchRoll(yawPitchRoll, quaternion);

      float* mValues = new float[2];
      mValues[0] = yawPitchRoll[1];  // Pitch for ICurrentParam == 0
      mValues[1] = yawPitchRoll[2];  // Roll  for ICurrentParam == 1
//      mValues[0] = yawPitchRoll[2];  // Pitch for ICurrentParam == 0
//      mValues[1] = -yawPitchRoll[1];  // Roll  for ICurrentParam == 1
      delete[] yawPitchRoll;

//      GetPMainWnd()->GetPTelemetry()->SetPitchAngle(MValues[0]);
//      GetPMainWnd()->GetPTelemetry()->SetRollAngle(MValues[1]);
      GetPMainWnd()->GetPTelemetry()->GetPGyrohorizon()->SetPitchRollAngles(mValues[0], mValues[1]);

      QQuaternion* pQuaternion = new QQuaternion(quaternion[0], quaternion[1],quaternion[3],quaternion[2]);

      delete[] quaternion;
      GetPMainWnd()->GetPTelemetry()->GetPGyrohorizon()->SetQuaternion(pQuaternion);
      delete[] pQuaternion;
//      QCoreApplication::postEvent(GetPMainWnd()->GetPTelemetry()->GetPGyrohorizon(), new QPaintEvent(QRect(0,0, 320,320)));//, int priority = Qt::NormalEventPriority) [static]

//      if(pStrValues->at(1) != CharWriteTelemetryModeOccasionally)  return;
      if(pCharsValues[1] != CharWriteTelemetryModeOccasionally)  {
        delete[] pCharsValues;  delete[] mValues; // IsReadyTakeValues = true;
        return;
      }
      MValues[0] = mValues[0];
      MValues[1] = mValues[1];
      delete[] mValues;

    }
    else if(*GetPNameChannel() == SNameTelemetryTabChannel_TP) {
//= Temperature and Pressure:
// "8otp2 25 101850"

      Q_ASSERT(QChar(pCharsValues[0]).digitValue() == IndexTabChannel_TP);
      Q_ASSERT(pCharsValues[1] == CharWriteTelemetryModeOccasionally);

//      if(pStrValues->at(1) != CharWriteTelemetryModeOccasionally)  return;
//      if(pCharsValues[1] != CharWriteTelemetryModeOccasionally)  {
//        delete[] pCharsValues;  IsReadyTakeValues = true;  // delete[] mValues;
//        return;
//      }

      int nvalues = 2;
//      float* temperaturePressure = new float[nvalues];

      GetTempValues(pCharsValues, CharsCodeTemperaturePressure, &nvalues, MValues);
//      if(!GetTempValues(pCharsValues, CharsCodeTemperaturePressure, 2, MValues))  {
//        delete[] pCharsValues;  IsReadyTakeValues = true;  // delete[] mValues;
//        return;
//       }

//      mValues[0] = temperaturePressure[0];  // Temperature for ICurrentParam == 0
//      mValues[1] = temperaturePressure[1];  // Pressure for ICurrentParam == 1

//      delete[] temperaturePressure;
    }
    else {
      QMessageBox msg(QMessageBox::Critical, "void MTelemetryTabChannel::SlotTakeTelemetryParamStrValues", "Unknown CharsCode");  msg.exec();
      delete[] pCharsValues; // IsReadyTakeValues = true;  // delete[] mValues;
      return;
    }
//    if(pStrValues->at(0) != CharWriteTelemetryModeOccasionally)  return;

  }
  else {
// "-0.123 4.567"
    int nvalues = 2;
    GetTempValues(pCharsValues, NULL, &nvalues, MValues);
//    if(!GetTempValues(pCharsValues, NULL, 2, MValues))  {
//      delete[] pCharsValues;  IsReadyTakeValues = true;  // delete[] mValues;
//      return;
//    }
  }

  delete[] pCharsValues;

//--------------

  qreal dt = (QDateTime::currentDateTime().toMSecsSinceEpoch()-GetPMainWnd()->GetTimeStartTelemetry())/1000.0;

  float value;  QString s;
  bool isNonNormal;  bool isLastParamInChannel;

  for(int iCurrentParam = 0; iCurrentParam < ListPlots.count(); iCurrentParam++) {

    value = MValues[iCurrentParam];
/*+
int k = 0;
float value = pFloatValues[k];

M0:
if(*GetPNameChannel() == "Angles") {
//QMessageBox msgBox(QMessageBox::Warning, "void MTelemetryTabChannel::SlotResultGetTelemetryValue(bool isOK, float* pFloatValues, int floatReadLength)",
//                   "if(*GetPNameChannel() == Angles");
 k += 1;
 value = pFloatValues[k]; //  // yaw pitch roll
// if(k == 1)  GetPMainWnd()->GetPTelemetry()->GetPEkranoplanGL()->SlotSetPitchAngle(value);
// if(k == 2)  GetPMainWnd()->GetPTelemetry()->GetPEkranoplanGL()->SlotSetRollAngle(value);
// if(k == 1)  GetPMainWnd()->GetPTelemetry()->SetPitchAngle(value);
 if(k == 2)  GetPMainWnd()->GetPTelemetry()->SetPitchRollAngles(pFloatValues[1], pFloatValues[2]);
}
*/
    s.sprintf("%.1f",value);
    ListLineEditCurrentParams[iCurrentParam]->setText(s);

    if(iCurrentParam < ListCorrespondingInfoParams.count()) {
      ListCorrespondingInfoParams[iCurrentParam]->setText(s);
    }
    else if(ListCorrespondingInfoParams.count() != 0) {
      QMessageBox msgBox(QMessageBox::Critical, "void MTelemetryTabChannel::SlotResultGetTelemetryValue(bool isOK, float* pFloatValues, int floatReadLength)",
                       "Problem::\n\nICurrentParam < ListCorrespondingInfoParams.count()\n\nДоделать Программу");
      msgBox.exec();
    }

    ListPlots[iCurrentParam]->AddValue(dt, value);
    Q_ASSERT(iCurrentParam < ListCorrespondingReportPlots.count());
    ListCorrespondingReportPlots[iCurrentParam]->AddValue(dt, value);

    isNonNormal = false;
/*
  if(value < *ListPMinNormalValues[ICurrentParam] || *ListPMaxNormalValues[ICurrentParam] < value) {
    isNonNormal = true;
    if(value < *ListPMinNormalValues[ICurrentParam])  ListIsNonNormalMinValue.replace(ICurrentParam, true);
    else                                              ListIsNonNormalMaxValue.replace(ICurrentParam, true);
*/
    if(ListPMinNormalValues[iCurrentParam]) {
      if(value < *ListPMinNormalValues[iCurrentParam]) {
        isNonNormal = true;
        ListIsNonNormalMinValue.replace(iCurrentParam, true);
      }
    }
    if(ListPMaxNormalValues[iCurrentParam]) {
      if(*ListPMaxNormalValues[iCurrentParam] < value)  {
        isNonNormal = true;
        ListIsNonNormalMaxValue.replace(iCurrentParam, true);
      }
    }
    if(isNonNormal) {
      if(!Timer.isActive()) {
        IsFlicker = true;  IsFlickerBrush = true; // !IsFlickerBrush;
       Timer.start(500); // int msec
        UpdateTabBar();
      }
    }

//  GetNextArduinoValue();
//  ICurrentParam += 1;

    if(iCurrentParam < ListPlots.count()-1)  isLastParamInChannel = false;
    else {                                   isLastParamInChannel = true;
/*++
//    GetPMainWnd()->DestroyArduinoObject();
    if(!disconnect(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), GetPMainWnd()->GetPArduinoObject(), SLOT(SlotGetTelemetryValue(QString*,QString*)))) {
      QMessageBox msgBox(QMessageBox::Warning, "void MTelemetryTabChannel::SlotResultGetTelemetryValue(bool isOK, float value)",
                         "Problem::\n\ndisconnect(this, SIGNAL(SignalGetTelemetryValue(QString*,QString*)), GetPMainWnd()->GetPArduino(), SLOT(SlotGetTelemetryValue(QString*,QString*))) == false");
      msgBox.exec();
    }
    if(!disconnect(GetPMainWnd()->GetPArduinoObject(), SIGNAL(SignalResultGetTelemetryValue(bool,float*,int)), this, SLOT(SlotResultGetTelemetryValue(bool,float*,int)))) {
      QMessageBox msgBox(QMessageBox::Warning, "void MTelemetryTabChannel::SlotResultGetTelemetryValue(bool isOK, float value)",
                         "Problem::\n\ndisconnect(GetPMainWnd()->GetPArduino(), SIGNAL(SignalResultGetTelemetryValue(bool,float*,int)), this, SLOT(SlotResultGetTelemetryValue(bool,float*,int))) == false");
      msgBox.exec();
    }
*/
    }

    emit SignalChannelTelemetryDoneParam(dt, value, isNonNormal, isLastParamInChannel);
  }

//  delete[] mValues;
//  IsReadyTakeValues = true;

//  ICurrentParam += 1;
//  if(ICurrentParam >= ListPlots.count())  ICurrentParam = 0;

/*+
if(*GetPNameChannel() == "Angles" && k == 1) {
  ICurrentParam += 1;
  goto M0;
}
*/
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::SlotTimerSignal()
{
  IsFlickerBrush = !IsFlickerBrush;
  UpdateTabBar();
}
//--------------------------------------------------------------------------------------------
//bool MTelemetryTabChannel::GetIsFlicker(bool& isColorBrushFlicker, bool& isNonNormalMinValue, bool& isNonNormalMaxValue)
bool MTelemetryTabChannel::GetIsFlicker(bool* pIsColorBrushFlicker/* = NULL*/, QList<bool>** ppListIsNonNormalMinValue/* = NULL*/, QList<bool>** ppListIsNonNormalMaxValue/* = NULL*/)
{
  if(IsFlicker) {
    if(pIsColorBrushFlicker) {
      if(IsFlickerBrush)  *pIsColorBrushFlicker = true; //&ColorBrushTabFlicker;
      else                *pIsColorBrushFlicker = false; //NULL;
    }
//    isNonNormalMinValue = IsNonNormalMinValue;  isNonNormalMaxValue = IsNonNormalMaxValue;
    if(ppListIsNonNormalMinValue) *ppListIsNonNormalMinValue = &ListIsNonNormalMinValue;
    if(ppListIsNonNormalMaxValue) *ppListIsNonNormalMaxValue = &ListIsNonNormalMaxValue;
  }
  return IsFlicker;
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::StopFlicker()
{
  IsFlicker = false;   IsFlickerBrush = false;
//  IsNonNormalMaxValue = false;  IsNonNormalMinValue = false;
  for(int i = 0; i < ListPlots.count(); i++) {
    ListIsNonNormalMaxValue.replace(i, false);
    ListIsNonNormalMinValue.replace(i, false);
  }

  if(Timer.isActive())  Timer.stop();
  UpdateTabBar();
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::UpdateTabBar()
{
  emit SignalUpdateTabBar();
//return;
//  MTelemetryTabWidgetChannels* pTabWidget = qobject_cast<MTelemetryTabWidgetChannels*>(parentWidget());
//  MTelemetryTabWidgetChannels* pTabWidget = qobject_cast<MTelemetryTabWidgetChannels*>(parentWidget());
//  MTelemetryTabWidgetChannels* pTabWidget = (MTelemetryTabWidgetChannels*)parentWidget();
//if(pTabWidget == NULL)   {
//  QMessageBox msgBox; msgBox.setText("void MTelemetryTabChannel::UpdateTabBar()");  msgBox.exec();
//}
//  Q_CHECK_PTR(pTabWidget);

//  pTabWidget->tabBar()->update();
//  MTelemetryTabBarChannels* pTabBar = qobject_cast<MTelemetryTabBarChannels*>(pTabWidget->tabBar());
//  MTelemetryTabBarChannels* pTabBar = (MTelemetryTabBarChannels*)pTabWidget->tabBar();
//  Q_CHECK_PTR(pTabBar);
//  pTabBar->update();
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabChannel::ClearPlots()
{
  StopFlicker();

  for(int i = 0; i < ListPlots.count(); i++)                    { ListPlots[i]->Clear(); }
  for(int i = 0; i < ListCorrespondingReportPlots.count(); i++) { ListCorrespondingReportPlots[i]->Clear(); }
}
//--------------------------------------------------------------------------------------------
