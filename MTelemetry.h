#ifndef MTELEMETRY_H
#define MTELEMETRY_H

#include "MTelemetryTabWidgetChannels.h"
//#include "MTelemetryTabWidgetStates.h"
#include "MTelemetryTabWidgetReports.h"
#include "MTelemetryTabChannel.h"
//#include "MTelemetryTabReport.h"
#include "MEkranoplanGL.h"
#include "MGyrohorizon.h"

#include <QSplitter>
#include <QTabWidget>
#include <QPushButton>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
//  #include <QSlider>

class MainWindow;
//============================================================================================

class MTelemetry : public QSplitter
{
    Q_OBJECT
public:
    explicit MTelemetry(QWidget *parent = 0);
  virtual ~MTelemetry();

private:
  QString SMessageBoxTitle;

//  QWidget* PScrollAreaGyrohorizonContents;

  MGyrohorizon* PGyrohorizon;

//  QTabWidget* PTabWidgetChannels;   int CurrentIndexTabChannel;
//  QTabWidget* PTabWidgetStates;
  MTelemetryTabWidgetChannels* PTabWidgetChannels;
//  MTelemetryTabWidgetStates*   PTabWidgetStates;
  MTelemetryTabWidgetChannels* PTabWidgetStates;
  MTelemetryTabWidgetReports*  PTabWidgetReports;

//  QList<MPlot*> ListTabPlots;

//  MEkranoplanGL* PEkranoplanGL;
//  MGyrohorizon*  PGyrohorizon;

  bool IsTelemetryStarted;
//  qint64 TimeStartTelemetry;
  int  CountAllTelemetryChannels;
  bool IsReadyNextCycle;
  int  ICurrentAllChannel;
//  bool IsMechanicalChannels;
/*+
  bool IsReadyNextChannel;
  bool IsReadyNextChannelParam;
*/
  MEkranoplanGL* PEkranoplanGL;
  QPushButton* PPushButtonStartTelemetry;
  QPushButton* PPushButtonStopTelemetry;

  QPushButton* PPushButtonReadiness;

//  void Init();

  QRect FillTelemetryGyrohorizon(QWidget* pScrollAreaGyrohorizonContents);
  QRect FillTelemetryChannels(QWidget* pScrollAreaChannelsContents);
  QRect FillTelemetryStates(QWidget* pScrollAreaStatesContents);
  QRect FillTelemetryReports(QWidget* pScrollAreaReportsContents);

  QRect AddInfoPanel(QWidget* pScrollAreaGyrohorizonContents);
  void  AssignCorrespondingChannelInfoParam(QString& sInfoParam, QLineEdit* pLineEditInfoParam);

  void SwitchActiveTabWidgetFromTo(QTabWidget* pTabWidgetFrom, QTabWidget* pTabWidgetTo);

  QString      NameFileReport;
  QFile*       PFileReport;
  QTextStream* PStreamFileReport;
  QList<int> ListLengthAllParams;
  int        IWritingParam;
  int        NAllWritingParams;

  void PrepareFileReport(QDateTime& currentDataTime);
  void WriteFileReportValue(qreal dt, float value, bool isNonNormal, bool isLastParamInChannel);
  void CloseFileReport();


//QSlider* pSliderPitch;
//QSlider* pSliderRoll;

public:
  void Init();

  void ActivateTabWidgetStates();
  void ActivateTabWidgetReports();

  MGyrohorizon* GetPGyrohorizon() { return PGyrohorizon; }

//  void DoTelemetry();

  MTelemetryTabChannel* GetCurrentPTabChannel(int iCurrentAllChannel);

  MTelemetryTabWidgetChannels* GetPTabWidgetChannels() { return PTabWidgetChannels; }
  MTelemetryTabWidgetChannels* GetPTabWidgetStates()   { return PTabWidgetStates;   }

//  MEkranoplanGL* GetPEkranoplanGL() { return PEkranoplanGL; }

//void SetPitchAngle(float pitch);
//void SetRollAngle(float roll);

//  void SetPitchRollAngles(float pitch, float roll);

//  QRect FillTabReport(MTelemetryTabReport* pTabReport, int countParamsTelemetryChannels, QList<QString>& listNamesChannels,
//                      QList<int>& listCountPlotsInChannels, QList<QList<QString>>& listNameParamsInChannels,
//                      bool isAssignCorrespondingReportPlot);
  const QString* GetCurrentPNameFileReport() { return &NameFileReport; }

//QTextStream* GetPStreamFileReport() { return PStreamFileReport; }


signals:
  void SignalSetTypeModeTelemetry();
  void SignalGetAllTelemetryValues();

//  void SignalStopTakeTelemetryStrValues();
  void SignalStopTakingData();

//++  void SignalSetPitchAngle(int pitch);
//++  void SignalSetRollAngle(int roll);

public slots:
//  void SlotIndexTabChannelsChanged(int newIndex);
  void SlotStartTelemetry();
  void SlotStopTelemetry();
  void SlotTimerSignal();
  void SlotChannelTelemetryDoneParam(qreal dt, float value, bool isNonNormal, bool isLastParamInChannel);
};
//============================================================================================
#endif // MTELEMETRY_H
