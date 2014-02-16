#ifndef MTELEMETRYTABCHANNEL_H
#define MTELEMETRYTABCHANNEL_H

#include "MPlot.h"

#include <QWidget>
#include <QList>
//#include <QScrollBar>
#include <QLineEdit>
#include <QTimer>

//============================================================================================
class MTelemetryTabChannel : public QWidget
{
    Q_OBJECT
public:
    explicit MTelemetryTabChannel(QWidget* parent, QList<QString>* pListParamsTelemetryChannel, int iFirstItemListParamsTelemetry);
  virtual ~MTelemetryTabChannel();

  QRect GetRectChannel() { return RectChannel; }

private:
  QList<QString>* PListParamsTelemetryChannel;
  int             IFirstItemListParamsTelemetry;
//  int             DeltaNItemListParamsTelemetry;

  QList<float*> ListPMinNormalValues;   QList<float*> ListPMaxNormalValues;

  QRect RectChannel;

  QList<QLineEdit*> ListLineEditCurrentParams;

  QList<MPlot*> ListPlots;
  QList<MPlot*> ListCorrespondingReportPlots;

  QList<QLineEdit*> ListCorrespondingInfoParams;

//  QScrollBar*   PScrollBar;

  bool   IsArduinoValues;
  float* MValues;
//  bool   IsReadyTakeValues;

//  int ICurrentParam;

  QTimer Timer;
  bool IsFlicker;            bool IsFlickerBrush;
//  bool IsNonNormalMaxValue;  bool IsNonNormalMinValue;
  QList<bool> ListIsNonNormalMaxValue;  QList<bool> ListIsNonNormalMinValue;

//  QColor ColorBrushTabFlicker;

  void UpdateTabBar();


protected:
  virtual bool event(QEvent* event);
//  virtual void paintEvent(QPaintEvent* event);

public:
  const QList<MPlot*>* GetPListPlots() { return &ListPlots; }
//  const QList<QString>* GetPListParamsTelemetryChannel() { return PListParamsTelemetryChannel; }
//  const int GetIFirstItemListParamsTelemetry() { return IFirstItemListParamsTelemetry; }

//  const QList<float*>* GetPListPMinNormalValues() { return &ListPMinNormalValues; }
//  const QList<float*>* GetPListPMaxNormalValues() { return &ListPMaxNormalValues; }

  QString* GetPNameChannel() { return &(*PListParamsTelemetryChannel)[0]; }
  QString* GetPNameParamInChannel(int j) { return &(*PListParamsTelemetryChannel)[IFirstItemListParamsTelemetry + j*3]; }

//  float* GetPMinNormalValue(int j) { return ListPMinNormalValues[j]; }
//  float* GetPMaxNormalValue(int j) { return ListPMaxNormalValues[j]; }
  QString* GetPStringMinNormalValue(int j) { return &(*PListParamsTelemetryChannel)[IFirstItemListParamsTelemetry + j*3 + 1]; }
  QString* GetPStringMaxNormalValue(int j) { return &(*PListParamsTelemetryChannel)[IFirstItemListParamsTelemetry + j*3 + 2]; }

  void AddAssignCorrespondingReportPlot(MPlot* pCorrespondingReportPlot);
  void AddAssignCorrespondingInfoParam(QLineEdit* pLineEditInfoParam);

//+  void BeginGetArduinoValues();
//+  void GetNextArduinoValue();

  bool GetIsFlicker(bool* pIsColorBrushFlicker = NULL, QList<bool>** ppListIsNonNormalMinValue = NULL, QList<bool>** ppListIsNonNormalMaxValue = NULL);
  void StopFlicker();

  void ClearPlots();


signals:
//  void SignalAddSlotTelemetryTabChannel(MTelemetryTabChannel* pTelemetryTabChannel, int countParamsInChannel,
//                                        bool isToReadValuesContinuously, bool isdArduinoValue);
  void SignalAddSlotTelemetryTabChannel(MTelemetryTabChannel* pTelemetryTabChannel, bool isdArduinoValues);
//+  void SignalGetTelemetryValue(QString* psNameChannel, QString* psInputName);
  void SignalChannelTelemetryDoneParam(qreal dt, float value, bool isNonNormal, bool isLastParamInChannel);
  void SignalUpdateTabBar();

public slots:
//+  void SlotResultGetTelemetryValue(bool isOK, float* pFloatValues, int floatReadLength);
  void SlotTimerSignal();
//  void SlotTakeTelemetryParamValue(MTelemetryTabChannel* pTelemetryTabChannel, float value);
  void SlotTakeTelemetryStrValues(MTelemetryTabChannel* pTelemetryTabChannel, const char* pCharsValues);
//  void SlotTakeTelemetryStrValues(MTelemetryTabChannel* pTelemetryTabChannel, QString* pStrValues);
//  void SlotTakeTelemetryStrValues(MTelemetryTabChannel* pTelemetryTabChannel, char* pCharsValues);

};
//============================================================================================
#endif // MTELEMETRYTABCHANNEL_H
