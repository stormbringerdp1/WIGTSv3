#ifndef MREADINESS_H
#define MREADINESS_H

#include "MReadinessTestChannel.h"
#include <QSplitter>
#include <QList>
#include <QPushButton>
#include <QString>
#include <QListWidget>
//  #include <QtSerialPort/QtSerialPort>

class MainWindow;
//============================================================================================

class MReadiness : public QSplitter
{
    Q_OBJECT
public:
    explicit MReadiness(QWidget *parent = 0);
  virtual ~MReadiness();

private:
  QString SMessageBoxTitle;

  QList<MReadinessTestChannel*> ListReadinessTestChannels;
  QPushButton* PPushButtonStart;

  QListWidget* PListWidgetEngines;
  QListWidget* PListWidgetSensors;
  QListWidget* PListWidgetServoMotors;
  QPushButton* PPushButtonTelemetry;

//QSerialPort* PPort;

  bool BResultTests;
  int  ITestChannel;


//  MainWindow* GetPMainWnd();

  QRect FillReadinessTest(QWidget* pScrollAreaTestContents);
//  QRect AddReadinessTestChannel(QWidget* pParent, const int yTopChannel,// const char* namePixmapFileChannel,
//                                QList<QString>* pListParamsChannel);
  QRect FillReadinessStart(QWidget* pScrollAreaStartContents);
//  void AddReadinessStartListItem(QListWidget* pListWidget, QList<QString>* pListNamesDevice);
  void CreateListWidget(const char* nameList, QListWidget*& pListWidget, QWidget* pParent, QRect rectList, QList<QString>* pListNames);

  QListWidgetItem* GetListWidgetItem(QString nameItem);
  QListWidgetItem* GetListWidgetItem(QListWidget* pListWidget, QString nameItem);

  void StartNextTestChannel();

public:
  void Init();

signals:
  void SignalSetTypeModeReadiness();

public slots:
  void SlotStart();
//void SlotPortError(QSerialPort::SerialPortError ierror);
//void SlotArduino_ControlLED(int value);
  void SlotResultTestChannel(bool bResult);
};
//============================================================================================
#endif // MREADINESS_H
