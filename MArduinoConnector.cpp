#include "MArduinoConnector.h"
#include "funcs.h"

  #include <QThread>
  #include <QApplication>
//#include <QMessageBox>

//============================================================================================
//==== Arduino Params - the same as in "sketch.ino": ====

const char CharTypeModeReadiness = 'R';
const char CharTypeModeTelemetry = 'T';
const char CharStopSendingData = 'S';

char CharWriteTelemetryModeOccasionally = 'o';

//= For Altitude and Speed TabChannel "H, S":
int   IndexTabChannel_HS = 5;
const char* CharsCodeAltitudeSpeed = "as2 ";

//= For Pitch and Roll TabChannel "Angles":
int   IndexTabChannel_Angles = 6;
const char* CharsCodeQuaternion = "q4 ";

//= For Temperature and Pressure TabChannel "T, P":
int   IndexTabChannel_TP = 8;
const char* CharsCodeTemperaturePressure = "tp2 ";

char CharSeparator = ' ';

//====

const char* NameDevice = "Arduino Uno";

extern QString SNameTelemetryTabChannel_HS;
extern QString SNameTelemetryTabChannel_Angles;
extern QString SNameTelemetryTabChannel_TP;

//============================================================================================
MArduinoConnector::MArduinoConnector(QObject *parent) :
    QObject(parent)
{
  PPort = NULL;

//  PStrValues = new QString();

  PStringMessage = new QString();

  IsTypeModeReadiness = false;
  IsTypeModeTelemetry = false;

  IsTakeTelemetryStrValues = false;

//  ICurrentReadinessParam = -1;
//  ICurrentTelemetryParam = -1;

//  IsToReadAllChannelsValues = false;


//  connect(this, SIGNAL(destroyed(QObject*)), SLOT(SlotDestroyed(QObject*)));

  connect(this, SIGNAL(SignalMessage(QString*)), GetPMainWnd(), SLOT(SlotMessage(QString*)));

  InitPort();
}
//--------------------------------------------------------------------------------------------
MArduinoConnector::~MArduinoConnector()
{
  if(PPort) {
    if(PPort->isOpen()) {
      SlotStopTakingData();
      PPort->clear();  PPort->close();
    }
    delete PPort;  PPort = NULL;
  }

//  delete PStrValues;  PStrValues = NULL;

//  for(int i = 0; i < ListPTelemetryChannels.count(); i++) {  delete ListPStrValues[i]; }

//  delete[] PFloatValues;  PFloatValues = NULL;
  delete PStringMessage;  PStringMessage = NULL;
}
//--------------------------------------------------------------------------------------------
/*
void MArduinoConnector::SlotDestroyed(QObject* pObj)
{
*PStringMessage = "void MArduinoConnector::SlotDestroyed(QObject* pObj)";  emit SignalMessage(PStringMessage);
  if(pObj == PPort) {
    if(PPort->isOpen()) {
      SlotStopTakingData();
      PPort->clear();  PPort->close();
    }
    delete PPort;  PPort = NULL;
  }
}
*/
//--------------------------------------------------------------------------------------------
/*
//void MArduinoConnector::AddSlotTelemetryTabChannel(MTelemetryTabChannel* pTelemetryTabChannel, int countParamsInChannel,
void MArduinoConnector::SlotAddSlotTelemetryTabChannel(MTelemetryTabChannel* pTelemetryTabChannel, int countParamsInChannel,
                                                       bool isToReadValuesContinuously, bool isdArduinoValue)
{
  disconnect(pTelemetryTabChannel, SIGNAL(SignalAddSlotTelemetryTabChannel(MTelemetryTabChannel*,int,bool,bool)),
             this,                 SLOT(SlotAddSlotTelemetryTabChannel(MTelemetryTabChannel*,int,bool,bool)));

  for(int i = 0; i < countParamsInChannel; i++) {
    ListAllPTelemetryChannels << pTelemetryTabChannel;
    ListAllIsTelemetryArduinoParams << isdArduinoValue;

    if(isToReadValuesContinuously) {
// Continuous Telemetry Params MUST BE Arduino Values!
      Q_ASSERT(isdArduinoValue);
      ListContinuousPTelemetryChannels << pTelemetryTabChannel;
//      ListContinuousIsTelemetryArduinoParams << isdArduinoParam;
    }
  }

//PStringMessage->sprintf("ListContinuousPTelemetryChannels.count() = %d\nListAllPTelemetryChannels.count() = %d",
//                         ListContinuousPTelemetryChannels.count(),      ListAllPTelemetryChannels.count());
//*PStringMessage += "\nvoid MArduinoConnector::AddSlotTelemetryTabChannel(...)\n\n";  emit SignalMessage(PStringMessage);

  connect(this,                 SIGNAL(SignalTakeTelemetryParamValue(MTelemetryTabChannel*,float)),
          pTelemetryTabChannel, SLOT(SlotTakeTelemetryParamValue(MTelemetryTabChannel*,float)));
}
*/
//--------------------------------------------------------------------------------------------
void MArduinoConnector::SlotAddSlotTelemetryTabChannel(MTelemetryTabChannel* pTelemetryTabChannel, bool isdArduinoValues)
{
  ListPTelemetryChannels << pTelemetryTabChannel;
  ListIsTelemetryArduinoValues << isdArduinoValues;

//  ListPStrValues << new QString();

//  connect(this,                 SIGNAL(SignalTakeTelemetryStrValues(MTelemetryTabChannel*,QString*)),
//          pTelemetryTabChannel, SLOT(SlotTakeTelemetryStrValues(MTelemetryTabChannel*,QString*)));
  connect(this,                 SIGNAL(SignalTakeTelemetryStrValues(MTelemetryTabChannel*,const char*)),
          pTelemetryTabChannel, SLOT(SlotTakeTelemetryStrValues(MTelemetryTabChannel*,const char*)));

  disconnect(pTelemetryTabChannel, SIGNAL(SignalAddSlotTelemetryTabChannel(MTelemetryTabChannel*,bool)),
             this,                 SLOT(SlotAddSlotTelemetryTabChannel(MTelemetryTabChannel*,bool)));

//*PStringMessage = "void MArduinoConnector::SlotAddSlotTelemetryTabChannel(...)";
//emit SignalMessage(PStringMessage);
}
//--------------------------------------------------------------------------------------------
void MArduinoConnector::InitPort()
{
qsrand(1234578);

//  QSerialPort* pSerialPort = new QSerialPort(this);
//  QString sp;
  PStringMessage->clear();

  QString portName;//("COM4");
  foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    if(info.description() == NameDevice) {
      portName = info.portName();
      *PStringMessage = info.description() + ":\n"
                      + QObject::tr("     Port: ") + info.portName() + "\n"
                      + QObject::tr("     Location: ") + info.systemLocation() + "\n"
//                      + QObject::tr("Description: ") + info.description() + "\n"
                      + QObject::tr("     Manufacturer: ") + info.manufacturer() + "\n"
                      + QObject::tr("     Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
                      + QObject::tr("     Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
                      + QObject::tr("     Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";
//QMessageBox msgBox;  msgBox.setText(sp);  msgBox.exec();
//  *PStringMessage = sp;
//      emit SignalMessage(PStringMessage);
      break;
    }
  }

  if(portName.isEmpty()) {
    *PStringMessage = NameDevice;  *PStringMessage += " is not connected.";
  }
  else {
    PPort = new QSerialPort(this);

//  connect(PPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(SlotPortError(QSerialPort::SerialPortError)));

    PPort->setPortName(portName);
    if(PPort->open(QIODevice::ReadWrite)) { // | QIODevice::Text)) { // | QIODevice::Unbuffered)) { //QIODevice::WriteOnly))  {
      PPort->setBaudRate(QSerialPort::Baud38400);//38400);
      PPort->setDataBits(QSerialPort::Data8);
      PPort->setParity(QSerialPort::NoParity);
      PPort->setStopBits(QSerialPort::OneStop);
      PPort->setFlowControl(QSerialPort::NoFlowControl); // QSerialPort::SoftwareControl

      PPort->setReadBufferSize(64);
//    PPort->clear(QSerialPort::AllDirections);

//    QMessageBox msgBox;  msgBox.setText("Port \""+portName+"\" is open");  msgBox.exec();
      *PStringMessage += "\nPort \""+portName+"\" is open.\n";

      connect(PPort, SIGNAL(readyRead()), SLOT(SlotReadyRead()));
    }
    else {
//    QMessageBox msg;  msg.setText("Port \""+portName+"\" is not open");  msg.exec();
      *PStringMessage += "\nPort \""+portName+"\" is not open.\n";

      delete PPort;  PPort = NULL;
    }
  }

  emit SignalMessage(PStringMessage);
}
//--------------------------------------------------------------------------------------------
//void MArduinoConnector::SetTypeModeReadiness()
void MArduinoConnector::SlotSetTypeModeReadiness()
{
  IsTypeModeReadiness = true;
  IsTypeModeTelemetry = false;

  if(PPort)  PPort->write(&CharTypeModeReadiness, 1);

//*PStringMessage = "void MArduinoConnector::SlotSetTypeModeReadiness()";
//  emit SignalMessage(PStringMessage);
}
//--------------------------------------------------------------------------------------------
//void MArduinoConnector::SlotTest(QString* psNameChannel, QString* psInputTestName, QString* psInputTestValue, QString* psOutputTestName)
void MArduinoConnector::SlotGetReadinessTestValue(QString* psNameChannel, QString* psInputTestName, QString* psInputTestValue, QString* psOutputTestName)
{
//  wait(5000);
//  thread()->wait(5000);

// psInputTestValue->toStdString().c_str()

QThread::sleep(2); //unsigned long secs) [static]
  emit SignalTakeReadinessTestValue(10.0);

//  moveToThread(QApplication::instance()->thread());
}
//--------------------------------------------------------------------------------------------
//void MArduinoConnector::SetTypeModeTelemetry()
void MArduinoConnector::SlotSetTypeModeTelemetry()
{
  IsTypeModeReadiness = false;
  IsTypeModeTelemetry = true;

  IsTakeTelemetryStrValues = true;

  if(PPort)  PPort->write(&CharTypeModeTelemetry, 1);
}
//--------------------------------------------------------------------------------------------
//void MArduinoConnector::SlotStopTakeTelemetryStrValues()
void MArduinoConnector::SlotStopTakingData()
{
  if(PPort)  PPort->write(&CharStopSendingData, 1);

  IsTakeTelemetryStrValues = false;

//*PStringMessage = "void MArduinoConnector::SlotStopTakeTelemetryStrValues()";
//emit SignalMessage(PStringMessage);
}
//--------------------------------------------------------------------------------------------
void MArduinoConnector::SlotGetAllTelemetryValues()
{
  if(!IsTakeTelemetryStrValues) return;

  QString strValues;  float value;  QString s;

  for(int i = 0; i < ListPTelemetryChannels.count(); i++) {

    if(ListIsTelemetryArduinoValues[i]) {

      if(PPort == NULL) {

        if(*ListPTelemetryChannels[i]->GetPNameChannel() == SNameTelemetryTabChannel_HS) {
//== Altitude and Speed:
//= "5oas2 12 28.123\n"
          Q_ASSERT(i == IndexTabChannel_HS);
          strValues.sprintf("%d",IndexTabChannel_HS);                        // "5"
          strValues += CharWriteTelemetryModeOccasionally;                   // "o"
          strValues += CharsCodeAltitudeSpeed;                               // "as2 "
          value = ((qrand()*1.0)/RAND_MAX)*100.0;   s.sprintf("%.3f",value);
          strValues += s;   strValues += CharSeparator;                      // "12 "
          value = ((qrand()*1.0)/RAND_MAX)*100.0;   s.sprintf("%.3f",value);
          strValues += s;                                                    // "28.123"
        }
        else if(*ListPTelemetryChannels[i]->GetPNameChannel() == SNameTelemetryTabChannel_Angles) {
//== Angles (Quaternion):
//= "6oq4 0.123 -4.567 8.910 11.121\n"
          Q_ASSERT(i == IndexTabChannel_Angles);
          strValues.sprintf("%d",IndexTabChannel_Angles);                    // "6"
          strValues += CharWriteTelemetryModeOccasionally;                   // "o"
          strValues += CharsCodeQuaternion;                                  // "q4 "
          value = ((qrand()*1.0)/RAND_MAX)*100.0;   s.sprintf("%.3f",value);
          strValues += s;   strValues += CharSeparator;                      // "0.123 "
          value = ((qrand()*1.0)/RAND_MAX)*100.0;   s.sprintf("%.3f",value);
          strValues += s;   strValues += CharSeparator;                      // "-4.567 "
          value = ((qrand()*1.0)/RAND_MAX)*100.0;   s.sprintf("%.3f",value);
          strValues += s;   strValues += CharSeparator;                      // "8.910 "
          value = ((qrand()*1.0)/RAND_MAX)*100.0;   s.sprintf("%.3f",value);
          strValues += s;                                                    // "11.121"
        }
        else if(*ListPTelemetryChannels[i]->GetPNameChannel() == SNameTelemetryTabChannel_TP) {
//= Temperature and Pressure:
// "8otp2 25 101850"
          Q_ASSERT(i == IndexTabChannel_TP);
          strValues.sprintf("%d",IndexTabChannel_TP);                        // "8"
          strValues += CharWriteTelemetryModeOccasionally;                   // "o"
          strValues += CharsCodeTemperaturePressure;                         // "tp2 "
          value = ((qrand()*1.0)/RAND_MAX)*100.0;   s.sprintf("%.3f",value);
          strValues += s;   strValues += CharSeparator;                      // "25 "
          value = ((qrand()*1.0)/RAND_MAX)*100.0;   s.sprintf("%.3f",value);
          strValues += s;                                                    // "101850"
        }
        else {
          *PStringMessage = "Непонятка.\n";
          *PStringMessage += "void MArduinoConnector::SlotGetAllTelemetryValues()\n";
          *PStringMessage += "Этого сообщения быть НЕ ДОЛЖНО!";
          emit SignalMessage(PStringMessage);
          return;
        }

//        *ListPStrValues[i] = strValues;
//        emit SignalTakeTelemetryStrValues(ListPTelemetryChannels[i], ListPStrValues[i]);

//        wchar_t* pWchars = new wchar_t[strValues.length()+1]; pWchars[strValues.length()] = (wchar_t)'\0';
//        strValues.toWCharArray(pWchars);
//        for(int)

        char* pCharsValues = new char[64];
        for(int j = 0; j < strValues.length(); j++) { pCharsValues[j] = strValues.toStdString().c_str()[j]; }
        pCharsValues[strValues.length()] = '\0';
        emit SignalTakeTelemetryStrValues(ListPTelemetryChannels[i], pCharsValues);
      }
    }

    else {
      value = ((qrand()*1.0)/RAND_MAX)*100.0;   s.sprintf("%.3f",value);
      strValues  = s;   strValues += CharSeparator;                      // "15.678 "
      value = ((qrand()*1.0)/RAND_MAX)*100.0;   s.sprintf("%.3f",value);
      strValues += s;                                                    // "10.185"
//      emit SignalTakeTelemetryParamValue(ListAllPTelemetryChannels[i], value);

//      *ListPStrValues[i] = strValues;
//      emit SignalTakeTelemetryStrValues(ListPTelemetryChannels[i], ListPStrValues[i]);

//      *ListPStrValues[i] = strValues;
//      emit SignalTakeTelemetryStrValues(ListPTelemetryChannels[i], ListPStrValues[i]->toStdString().c_str());

      char* pCharsValues = new char[64];
      for(int j = 0; j < strValues.length(); j++) { pCharsValues[j] = strValues.toStdString().c_str()[j]; }
      pCharsValues[strValues.length()] = '\0';
      emit SignalTakeTelemetryStrValues(ListPTelemetryChannels[i], pCharsValues);
    }

  }

  if(PPort)  PPort->write(&CharWriteTelemetryModeOccasionally, 1);
}
//--------------------------------------------------------------------------------------------
void MArduinoConnector::SlotReadyRead()
{
//return;
//*PStringMessage = "void MArduinoConnector::SlotReadyRead()";  emit SignalMessage(PStringMessage);
//  while(PPort->bytesAvailable() > 0 ) { //= 4) {
//    PPort->read((char*)&FValues, 4); //PPort->bytesAvailable());
  if(PPort->canReadLine()) {
//*PStringMessage = "PPort->canReadLine()";  emit SignalMessage(PStringMessage);
//    int count = (int)PPort->readLine(Chars, 63); //PPort->bytesAvailable());
    char* pCharsValues = new char[64];
    int count = (int)PPort->readLine(pCharsValues, 63); //PPort->bytesAvailable());
//    pCharsValues[count] = '\0';

//(*PStringMessage).sprintf("count = %d\n\n",count);
//*PStringMessage += "PPort->readLine(...)\n\n";   *PStringMessage += Chars;  emit SignalMessage(PStringMessage);
/*++
    if(Chars[0] == CharTypeModeReadiness) {
//= Switch Mode:
      IsTypeModeReadiness = true;
      IsTypeModeTelemetry = false;
    }
    else if(Chars[0] == CharTypeModeTelemetry) {
//= Switch Mode:
      IsTypeModeReadiness = false;
      IsTypeModeTelemetry = true;
//*PStringMessage = "Chars[0] == CharTypeModeTelemetry";  emit SignalMessage(PStringMessage);
    }
//= Prepare For New Packets:
    else if(Chars[0] == CharModeOccasionally) {
      ICurrentTelemetryParam = -1;
      IsToReadAllChannelsValues = true;
    }
    else if(Chars[0] == CharModeContinuously) {
      ICurrentTelemetryParam = -1;
      IsToReadAllChannelsValues = false;
    }

    else {
*/
//=Read Data:
//*PStringMessage = "//=Read Data:";  emit SignalMessage(PStringMessage);

//      StrValues = Chars;

      if(IsTypeModeTelemetry) {

//        if(!IsTakeTelemetryStrValues) return;

//== Telemetry Data:
/*++
        MTelemetryTabChannel* pTelemetryTabChannel;
        ICurrentTelemetryParam += 1;

        if(IsToReadAllChannelsValues)  {
          if(ICurrentTelemetryParam >= ListAllPTelemetryChannels.count()) {
            ICurrentTelemetryParam = 0;
            *PStringMessage = "void MArduinoConnector::SlotReadyRead():\n\n";
            *PStringMessage += "Этого Сообщения Быть НЕ ДОЛЖНО!:\n\nICurrentTelemetryParam >= ListAllPTelemetryChannels.count()";
            emit SignalMessage(PStringMessage);
          }

          pTelemetryTabChannel = ListAllPTelemetryChannels[ICurrentTelemetryParam];
        }
        else {
          if(ICurrentTelemetryParam >= ListContinuousPTelemetryChannels.count()) {
            ICurrentTelemetryParam = 0;
//            *PStringMessage = "void MArduinoConnector::SlotReadyRead():\n\n";
//            *PStringMessage += "Этого Сообщения Быть НЕ ДОЛЖНО!:\n\nICurrentTelemetryParam >= ListContinuousPTelemetryChannels.count()";
//            emit SignalMessage(PStringMessage);
          }

          pTelemetryTabChannel = ListContinuousPTelemetryChannels[ICurrentTelemetryParam];
        }
//*PStringMessage = StrValue;  emit SignalMessage(PStringMessage);
        emit SignalTakeTelemetryParamValue(pTelemetryTabChannel, StrValue.toFloat());
*/
/*+
        for(int i = 0; i < ListPTelemetryChannels.count(); i++) {
          if(ListIsTelemetryArduinoValues[i]) {
            *ListPStrValues[i] = Chars; //StrValues;
            emit SignalTakeTelemetryStrValues(ListPTelemetryChannels[i], ListPStrValues[i]);
//            emit SignalTakeTelemetryStrValues(ListPTelemetryChannels[i], Chars);

          }
        }
*/
        emit SignalTakeTelemetryStrValues(ListPTelemetryChannels[QChar(pCharsValues[0]).digitValue()], pCharsValues);
      }

      else if(IsTypeModeReadiness) {
//== Readiness Data:
      }
//+++    }
  }
}
//--------------------------------------------------------------------------------------------
/*
void MArduinoConnector::SlotGetTelemetryValue(QString* psNameChannel, QString* psInputName)
{
  bool isArduinoValue = false;
  bool isOK = false;
  int floatReadLength;

  if(*psNameChannel == "Angles") {  // yaw pitch roll
    isArduinoValue = true;
    PPort->write("A", 1); // PPort->flush();
    floatReadLength = 3;  // yaw pitch roll
  }
  else {
    isOK = true;

//QThread::sleep(1); //unsigned long secs) [static]

float value = ((qrand()*1.0)/RAND_MAX)*100.0;

PFloatValues[0] = value;  PFloatValues[1] = 0.0;  PFloatValues[2] = 0.0;
floatReadLength = 1;
  }

//float value = ((qrand()*1.0)/RAND_MAX)*100.0;
//PFloatValues[0] = value;  PFloatValues[1] = value;  PFloatValues[2] = value;
//isOK = true;

  int byteReadLength = floatReadLength*4;
//byteReadLength = 8;


//const char* pc = psNameChannel->toStdString().c_str();
//  QMessageBox msgBox;  msgBox.setText("*psNameChannel == Angles");  msgBox.exec();
//  moveToThread(QApplication::instance()->thread());

isOK = true;
int k = 0;  QString s;  int n;  char buf[128];
M1:
  if(isArduinoValue) {
//    if(PPort->waitForReadyRead(3000) && PPort->bytesAvailable() >= 4) { //int msecs) [virtual]
    if(PPort->bytesAvailable() > 0) { //int msecs) [virtual]
//    while(!PPort->waitForReadyRead(3000) && PPort->bytesAvailable() < 4) {}  //int msecs) [virtual]
//    if(PPort->waitForBytesWritten(2000)) { //int msecs) [virtual]

//      if(*psNameChannel == "Angles") { // && PPort->bytesAvailable() > 0) { //== byteReadLength) { // yaw pitch roll
//n = PPort->bytesAvailable();
k += 1;
//if(k == 2) {
//PStringMessage->sprintf("PPort->bytesAvailable() = %d", PPort->bytesAvailable());
//QMessageBox msg;  msg.setText(s);   msg.exec();
//+emit SignalMessage(PStringMessage);
//goto Ms;
//}
//        PPort->read((char*)PFloatValues, floatReadLength);
        PPort->read((char*)&PFloatValues[k], 4); //PPort->bytesAvailable());

s.sprintf("%.2f",PFloatValues[k]);
//PPort->read(buf, n);  buf[n] = '\0';  s = buf;  PFloatValues[k] = s.toFloat();
*PStringMessage = s;
//emit SignalMessage(PStringMessage);


        isOK = true;
        if(k == 2) goto Ms;
        goto M1;
//      }
    }
  }
Ms:
  emit SignalResultGetTelemetryValue(isOK, PFloatValues, floatReadLength);
}
*/
//--------------------------------------------------------------------------------------------
/*
void MReadiness::SlotArduino_ControlLED(int value)
{
if(value < 0 || value > 255) return;

//==Qt 5.1.1(x86):
//byte bytes[1]; bytes[0] = (byte)value;
//==Qt 5.2.0(x64):
uchar bytes[1]; bytes[0] = (uchar)value;

//QByteArray ba(1, bvalue);
//QString sv; sv.sprintf("%d",value);
//GetPMainWnd()->statusBar()->showMessage(sv);
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();
//PPort->write(sv.toStdString().c_str());
PPort->write((char*)bytes, 1);
}
*/
//--------------------------------------------------------------------------------------------
void MArduinoConnector::SlotPortError(QSerialPort::SerialPortError ierror)
{
  if(ierror == 0)  return;
/*
  QString s; s.sprintf("ierror = %d\n", ierror); s += PPort->errorString();
  QMessageBox msgBox;//(GetPMainWnd());
  msgBox.setText(s);
//  moveToThread(QApplication::instance()->thread());
  msgBox.exec();
*/
  PStringMessage->sprintf("ierror = %d\n\n", ierror);  *PStringMessage += PPort->errorString();
  emit SignalMessage(PStringMessage);

/*
QSerialPort::NoError	0	No error occurred.
QSerialPort::DeviceNotFoundError	1	An error occurred while attempting to open an non-existing device.
QSerialPort::PermissionError	2	An error occurred while attempting to open an already opened device by another process or a user not having enough permission and credentials to open.
QSerialPort::OpenError	3	An error occurred while attempting to open an already opened device in this object.
QSerialPort::ParityError	4	Parity error detected by the hardware while reading data.
QSerialPort::FramingError	5	Framing error detected by the hardware while reading data.
QSerialPort::BreakConditionError	6	Break condition detected by the hardware on the input line.
QSerialPort::WriteError	7	An I/O error occurred while writing the data.
QSerialPort::ReadError	8	An I/O error occurred while reading the data.
QSerialPort::ResourceError	9	An I/O error occurred when a resource becomes unavailable, e.g. when the device is unexpectedly removed from the system.
QSerialPort::UnsupportedOperationError	10	The requested device operation is not supported or prohibited by the running operating system.
QSerialPort::UnknownError	11	An unidentified error occurred.
*/
}
//--------------------------------------------------------------------------------------------
