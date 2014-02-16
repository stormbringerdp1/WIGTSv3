#ifndef MTELEMETRYTABWIDGETCHANNELS_H
#define MTELEMETRYTABWIDGETCHANNELS_H

#include <QTabWidget>
#include <QList>
#include <QEvent>

//============================================================================================
class MTelemetryTabWidgetChannels : public QTabWidget
{
    Q_OBJECT
public:
    explicit MTelemetryTabWidgetChannels(QWidget *parent, QList<QList<QString>>* pListParamsTelemetryChannels,
                                                          int iFirstItemListParamsTelemetry);

  QList<QList<QString>>* PListParamsTelemetryChannels;
  int IFirstItemListParamsTelemetry;

  QRect AddTabs();

protected:
//  virtual void mousePressEvent(QMouseEvent* event);
//  virtual void mouseReleaseEvent(QMouseEvent* event);
//  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual bool event(QEvent* e);

signals:

public slots:

};
//============================================================================================

#endif // MTELEMETRYTABWIDGETCHANNELS_H
