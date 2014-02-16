#include "MTelemetryTabBarChannels.h"
#include "MTelemetryTabWidgetChannels.h"
#include "MTelemetryTabChannel.h"

#include <QPainter>
#include <QList>
  #include <QMessageBox>
#include <QtGlobal>

//============================================================================================
MTelemetryTabBarChannels::MTelemetryTabBarChannels(QWidget *parent)
                        : QTabBar(parent)
{
//  setUsesScrollButtons(false);
//  setTabsClosable(true);
//  setShape(QTabBar::TriangularNorth);
//  setExpanding(true);
//  setDocumentMode(true);
  setElideMode(Qt::ElideNone);//Qt::ElideRight);

  CurrentIndex = 0;//-1;
  connect(this, SIGNAL(currentChanged(int)), SLOT(SlotCurrentChanged(int)));
  connect(this, SIGNAL(tabBarClicked(int)), SLOT(SlotTabBarClicked(int)));
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabBarChannels::SlotTabBarClicked(int clickedIndex)
{
  MTelemetryTabWidgetChannels* pTabWidgetChannels = qobject_cast<MTelemetryTabWidgetChannels*>(parent());
  Q_ASSERT(pTabWidgetChannels != NULL); // Q_CHECK_PTR(pTabWidgetChannels);

  MTelemetryTabChannel* pTabChannel = qobject_cast<MTelemetryTabChannel*>(pTabWidgetChannels->widget(clickedIndex));
  Q_ASSERT(pTabChannel != NULL); // Q_CHECK_PTR(pTabChannel);
//  bool isColorBrushFlicker;  QList<bool>* pListIsNonNormalMinValue;  QList<bool>* pListIsNonNormalMaxValue;
//  if(pTabChannel->GetIsFlicker(isColorBrushFlicker, pListIsNonNormalMinValue, pListIsNonNormalMaxValue))  pTabChannel->StopFlicker();
  if(pTabChannel->GetIsFlicker())  pTabChannel->StopFlicker();
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabBarChannels::SlotCurrentChanged(int newIndex)
{
//  if(CurrentIndex != newIndex) {
//  if(0 <= CurrentIndex) {
  setTabTextColor(CurrentIndex, QColor(0,0,0));
//  }
  setTabTextColor(newIndex, QColor(0,0,255));
  CurrentIndex = newIndex;
//  }
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabBarChannels::paintEvent(QPaintEvent* event)
{
  QTabBar::paintEvent(event);
//--
  //create a QPainter and pass a pointer to the device.
  //A paint device can be a QWidget, a QPixmap or a QImage
  QPainter painter(this);

  painter.setPen(Qt::NoPen);

  MTelemetryTabWidgetChannels* pTabWidgetChannels = qobject_cast<MTelemetryTabWidgetChannels*>(parent());
  Q_ASSERT(pTabWidgetChannels != NULL); // Q_CHECK_PTR(pTabWidget);

  MTelemetryTabChannel* pTabChannel;  //  QColor* pColorBrushTab;
  bool isColorBrushFlicker;  QList<bool>* pListIsNonNormalMinValue;  QList<bool>* pListIsNonNormalMaxValue;
  for(int i = 0; i < pTabWidgetChannels->count(); i++) {
    pTabChannel = qobject_cast<MTelemetryTabChannel*>(pTabWidgetChannels->widget(i));
    Q_ASSERT(pTabChannel != NULL); // Q_CHECK_PTR(pTabChannel);

//    if(pTabChannel->GetIsFlicker(pColorBrushTab) && pColorBrushTab != NULL) {
    if(pTabChannel->GetIsFlicker(&isColorBrushFlicker, &pListIsNonNormalMinValue, &pListIsNonNormalMaxValue)) {
      if(isColorBrushFlicker) {
        painter.setBrush(QBrush(QColor(255,0,0, 100)));
        QRect rect= tabRect(i);
        if(currentIndex() != i) {
          rect.setTopLeft(rect.topLeft()+=QPoint(1,2));
          rect.setBottomRight(rect.bottomRight()+=QPoint(-1,0));
        }
        else {
          rect.setTopLeft(rect.topLeft()+=QPoint(-1,0));
          rect.setBottomRight(rect.bottomRight()+=QPoint(1,0));
        }

//        if(!isNonNormalMaxValue) rect.setTop(rect.top()+rect.height()/2);
//        if(!isNonNormalMinValue) rect.setBottom(rect.bottom()-rect.height()/2);

        int count = pListIsNonNormalMinValue->count();
        int w = rect.width()/count;  int h = rect.height()/2;
//        QRect rectMax;   QRect rectMin;  QRect r;
        QList<QRect> listRectsFlicker;
        for(int j = 0; j < count; j++) {
          if((*pListIsNonNormalMaxValue)[j]) {
//            r = QRect(rect.left()+j*w, rect.top(), w,h);
//            if(!rectMax.isValid())  rectMax  = r;
//            else                    rectMax |= r;
            listRectsFlicker << QRect(rect.left()+j*w, rect.top(), w,h);
          }
          if((*pListIsNonNormalMinValue)[j])  {
//            r = QRect(rect.left()+j*w, rect.top()+h, w,h);
//            if(!rectMin.isValid())   rectMin  = r;
//            else                     rectMin |= r;
            listRectsFlicker << QRect(rect.left()+j*w, rect.top()+h, w,h);
          }
        }

//        QRect rectFlicker;
//        if(rectMax.isValid())  rectFlicker = rectMax;
//        if(rectMin.isValid()) {
//          if(!rectFlicker.isValid())  rectFlicker  = rectMin;
//          else                        rectFlicker |= rectMin;
//        }
//        painter.drawRect(rectFlicker);
        for(int k = 0; k < listRectsFlicker.count(); k++)  {
          painter.drawRect(listRectsFlicker[k]);
        }
      }
    }
  }
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabBarChannels::SlotUpdateTabBar()
{
  update();
}
//--------------------------------------------------------------------------------------------
