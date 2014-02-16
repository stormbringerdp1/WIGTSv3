#ifndef MTELEMETRYTABBARREPORTS_H
#define MTELEMETRYTABBARREPORTS_H

#include <QTabBar>
#include <QMouseEvent>

//============================================================================================
class MTelemetryTabBarReports : public QTabBar
{
    Q_OBJECT
public:
    explicit MTelemetryTabBarReports(QWidget *parent = 0);

private:
//  int CurrentIndex; // bool IsNewTab;

//  bool InsertDataFromFileReport(MTelemetryTabReport* pTab, const QString& pathNameFileReport);

public:
//  void CloseTab(QWidget* pTab);


protected:
  virtual void mousePressEvent(QMouseEvent* event);
//  virtual void mouseReleaseEvent(QMouseEvent* event);
//  virtual void mouseMoveEvent(QMouseEvent* event);
//  virtual bool event(QEvent* e);

signals:

public slots:
//  void SlotIndexChanged(int newIndex);

};

//============================================================================================
#endif // MTELEMETRYTABBARREPORTS_H
