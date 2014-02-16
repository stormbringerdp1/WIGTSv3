#ifndef MARDUINOCONNECTOR_H
#define MARDUINOCONNECTOR_H

#include "MTelemetryTabChannel.h"

#include <QObject>
#include <QList>
#include <QString>
#include <QtSerialPort/QtSerialPort>

//============================================================================================
class MArduinoConnector : public QObject
{
    Q_OBJECT
public:
    explicit MArduinoConnector(QObject *parent = 0);
  virtual ~MArduinoConnector();

private:

  QList<MTelemetryTabChannel*>  ListPTelemetryChannels;
  QList<bool>                   ListIsTelemetryArduinoValues;

//  QList<MTelemetryTabChannel*>  ListContinuousPTelemetryChannels;


  QSerialPort* PPort;

//  float* PFloatValues;
  QString* PStringMessage;

  bool IsTypeModeReadiness;
  bool IsTypeModeTelemetry;

  bool IsTakeTelemetryStrValues;

//  int ICurrentReadinessParam;
//  int ICurrentTelemetryParam;

//  bool IsToReadAllChannelsValues;

//  char     Chars[64];
//  QString  StrValues;
//  QList<QString*> ListPStrValues;

  void InitPort();

public:
//  void SetTypeModeReadiness();
//  void SetTypeModeTelemetry();

//  void AddSlotTelemetryTabChannel(MTelemetryTabChannel* pTelemetryTabChannel, int countParamsInChannel,
//                                  bool isToReadValuesContinuously, bool isdArduinoValue);

signals:
  void SignalMessage(QString* pStr);
//  void SignalResultTest(float result);
  void SignalTakeReadinessTestValue(float result);
//+  void SignalResultGetTelemetryValue(bool isOK, float* pFloatValues, int floatReadLength);
//  void SignalTakeTelemetryParamValue(MTelemetryTabChannel* pTelemetryTabChannel, float value);
//  void SignalTakeTelemetryStrValues(MTelemetryTabChannel* pTelemetryTabChannel, QString* pStrValues);
  void SignalTakeTelemetryStrValues(MTelemetryTabChannel* pTelemetryTabChannel, const char* pCharsValues);

public slots:
  void SlotPortError(QSerialPort::SerialPortError ierror);
//  void SlotAddSlotTelemetryTabChannel(MTelemetryTabChannel* pTelemetryTabChannel, int countParamsInChannel,
//                                      bool isToReadValuesContinuously, bool isdArduinoValue);
  void SlotAddSlotTelemetryTabChannel(MTelemetryTabChannel* pTelemetryTabChannel, bool isdArduinoValues);

  void SlotSetTypeModeReadiness();
  void SlotSetTypeModeTelemetry();

//  void SlotStopTakeTelemetryStrValues();
  void SlotStopTakingData();

//+  void SlotGetTelemetryValue(QString* psNameChannel, QString* psInputName);
//void SlotTest(QString* psNameChannel, QString* psInputTestName, QString* psInputTestValue, QString* psOutputTestName);
  void SlotGetReadinessTestValue(QString* psNameChannel, QString* psInputTestName, QString* psInputTestValue, QString* psOutputTestName);
  void SlotGetAllTelemetryValues();

  void SlotReadyRead();

//  void SlotDestroyed(QObject* pObj);
};
//============================================================================================

#endif // MARDUINOCONNECTOR_H
