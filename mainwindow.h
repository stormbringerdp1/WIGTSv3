#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "MReadiness.h"
#include "MTelemetry.h"
#include "MArduinoConnector.h"

#include <QMainWindow>
//#include <QGraphicsScene>
//#include <QGraphicsView>
#include <QList>
#include <QString>
#include <QThread>

  #include <QTimer>

//============================================================================================

namespace Ui {
class MainWindow;
}

//============================================================================================
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
//--
private:
/*++++
  QSplitter* PMainSplitter;
  QList<int> ListMainSplitterSizes;

  QGraphicsScene*       PSceneEkranoplan;
  QGraphicsView*        PViewEkranoplan;
  QGraphicsEllipseItem* PTestSpot;
*/
  MReadiness*           PReadiness;
  MTelemetry*           PTelemetry;

  QList<QString>        ListNamesEngines;
  QList<QString>        ListNamesSensors;
  QList<QString>        ListNamesServoMotors;

//  QList<QString>        ListTextTestChannels;
  QList<QList<QString>> ListParamsReadinessChannels;  int IFirstItemListParamsReadiness;  int DeltaNItemListParamsReadiness;
  QList<QList<QString>> ListParamsTelemetryChannels;  int IFirstItemListParamsTelemetry;//  int DeltaNItemListParamsTelemetry;
                                                      int ILongeronsTelemetryChannel;
  QList<QList<QString>> ListParamsTelemetryStates;    int IFirstItemListParamsStates;

  QTimer Timer;
  qint64 TimeStartTelemetry;

  void CreateArduinoConnector();  void DeleteArduinoConnector();
  void InitLists();
//  void SwitchSplitterFromTo(QWidget* pWidgetFrom, QWidget* pWidgetTo);
  void SwitchSplitterTo(QWidget* pWidget);


  MArduinoConnector* PArduinoConnector;
  QThread            ThreadArduinoConnector;

public:

  void Init();

  QList<QString>* GetPListNamesEngines() { return &ListNamesEngines; }
  QList<QString>* GetPListNamesSensors() { return &ListNamesSensors; }
  QList<QString>* GetPListNamesServoMotors() { return &ListNamesServoMotors; }

//  QList<QString>*        GetPListTextTestChannels() { return &ListTextTestChannels; }
  QList<QList<QString>>* GetPListParamsReadinessChannels() { return &ListParamsReadinessChannels; }
  const int GetIFirstItemListParamsReadiness() { return IFirstItemListParamsReadiness; }
  const int GetDeltaNItemListParamsReadiness() { return DeltaNItemListParamsReadiness; }

  QList<QList<QString>>* GetPListParamsTelemetryChannels() { return &ListParamsTelemetryChannels; }
  const int GetIFirstItemListParamsTelemetry() { return IFirstItemListParamsTelemetry; }
//  int GetDeltaNItemListParamsTelemetry() { return DeltaNItemListParamsTelemetry; }
  const int GetILongeronsTelemetryChannel() { return ILongeronsTelemetryChannel; }

  QList<QList<QString>>* GetPListParamsTelemetryStates() { return &ListParamsTelemetryStates; }
  const int GetIFirstItemListParamsStates() { return IFirstItemListParamsStates; }

//  QGraphicsScene* GetPSceneEkranoplan() { return PSceneEkranoplan; }


//  QThread* GetPThreadArduino() { return &ThreadArduino; }
  MArduinoConnector* GetPArduinoConnector() { return PArduinoConnector; }
//  void CreateArduinoObject(const QObject* pSenderReceiver, const char* signalThis, const char* slotArduino,
//                                                           const char* signalArduino, const char* slotThis);
//  void DestroyArduinoObject();

  MTelemetry* GetPTelemetry() { return PTelemetry; }

  QTimer& GetTimer() { return Timer; }

  void  SetTimeStartTelemetry(const qint64 timeStartTelemetry) { TimeStartTelemetry = timeStartTelemetry; }
  const qint64 GetTimeStartTelemetry()                          { return TimeStartTelemetry; }


protected:
  virtual bool event(QEvent* event);
//  virtual bool winEvent(MSG *message, long *result);
//  virtual void contextMenuEvent(QContextMenuEvent * event);

public:

signals:

public slots:
  void SlotMessage(QString* pStr);
  void SlotSwitchToReadiness();
  void SlotSwitchToTelemetry();
};
//============================================================================================
#endif // MAINWINDOW_H
