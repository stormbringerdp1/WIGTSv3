#ifndef MTELEMETRYTABWIDGETREPORTS_H
#define MTELEMETRYTABWIDGETREPORTS_H

//#include "MTelemetryTabWidgetChannels.h"

#include "MTelemetryTabReport.h"

#include <QTabWidget>
//#include <QMouseEvent>
#include <QEvent>

//============================================================================================
class MTelemetryTabWidgetReports : public QTabWidget
{
    Q_OBJECT
public:
    explicit MTelemetryTabWidgetReports(QWidget *parent); //, MTelemetryTabWidgetChannels *pTabWidgetChannels);

private:
  int CurrentIndex; // bool IsNewTab;

//  MTelemetryTabWidgetChannels* PTabWidgetChannels;

  bool InsertDataFromFileReport(MTelemetryTabReport* pTab, const QString& pathNameFileReport);

public:
  QRect AddTabs();
  void CloseTab(QWidget* pTab);

//  MTelemetryTabWidgetChannels* GetPTabWidgetChannels() { return PTabWidgetChannels; }


protected:
//  virtual void mousePressEvent(QMouseEvent* event);
//  virtual void mouseReleaseEvent(QMouseEvent* event);
//  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual bool event(QEvent* e);
//  virtual void changeEvent(QEvent * ev);

signals:

public slots:
  void SlotIndexChanged(int newIndex);
//void setCurrentIndex(int index);
//void SlotTabBarClicked(int index);
};
//============================================================================================

#endif // MTELEMETRYTABWIDGETREPORTS_H
