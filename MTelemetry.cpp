#include "MTelemetry.h"
//#include "MEkranoplanGL.h"
//#include "MGyrohorizon.h"
//#include "MTelemetryTabChannel.h"
#include "funcs.h"
//#include "constants.h"

#include <QApplication>
//#include <QCoreApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include <QScrollArea>
#include <QtGlobal>

//  #include <QSlider>
//  #include <QGraphicsProxyWidget>

//============================================================================================

int TimerInterval = 1000; // msec
const char* ReportFileVersion = "WIGTS Report Ver. 1.0";

//============================================================================================

MTelemetry::MTelemetry(QWidget *parent) :
//  QSplitter(Qt::Vertical, parent)
  QSplitter(Qt::Horizontal, parent)
{
  SMessageBoxTitle = QCoreApplication::instance()->applicationName()+":  Telemetry";

  CountAllTelemetryChannels = 0;

  PFileReport = NULL;
  PStreamFileReport = NULL;

//  Init();
  IsTelemetryStarted = false;
}
//--------------------------------------------------------------------------------------------
MTelemetry::~MTelemetry()
{
  CloseFileReport();
}
//--------------------------------------------------------------------------------------------
void MTelemetry::Init()
{
//===####  I: Left (Gyrohorizon + Params):  ####===

  QScrollArea* pScrollAreaGyrohorizon = new QScrollArea(this);//pSplitterTelemetry);
//  pScrollAreaGyrohorizon->setObjectName(QStringLiteral("ScrollAreaGyrohorizon"));
//  pScrollAreaTabs->setGeometry(QRect(40, 70, 611, 111));
  pScrollAreaGyrohorizon->setWidgetResizable(true);

  QWidget* pScrollAreaGyrohorizonContents = new QWidget(this);//pSplitterTelemetry);
//  PScrollAreaGyrohorizonContents = new QWidget(this);//pSplitterTelemetry);
//  pScrollAreaGyrohorizonContents->setObjectName(QStringLiteral("ScrollAreaGyrohorizonContents"));
//  pScrollAreaTabsContents->setGeometry(QRect(0, 0, 609, 109));
//  pScrollAreaTabsContents->setMinimumSize(609,109);

  QRect rectInfo = FillTelemetryGyrohorizon(pScrollAreaGyrohorizonContents);
//  pScrollAreaGyrohorizonContents->setMinimumSize(rectInfo.right()+3,rectInfo.bottom()+3);
  pScrollAreaGyrohorizon->setWidget(pScrollAreaGyrohorizonContents);


//  pScrollAreaGyrohorizon->setGeometry(QRect(0, 0, 411, 511));
//  pScrollAreaGyrohorizon->setMinimumSize(rect.right()+3,rect.bottom()+3);



//++  addWidget(pScrollAreaGyrohorizon);


//===####  II: 1) Right (Channels):  ####===

  QSplitter* pSplitterTelemetry = new QSplitter(Qt::Vertical, this);//pSplitter);
//++  addWidget(pSplitterTelemetry);

  QList<int> list;  list << 97 << 200;    setSizes(list);   list.clear();


//===  1) TelemetryChannels:

  QScrollArea* pScrollAreaChannels = new QScrollArea(pSplitterTelemetry);
//  pScrollAreaChannels->setObjectName(QStringLiteral("ScrollAreaTabs"));
//  pScrollAreaChannels->setGeometry(QRect(0, 0, 1000, 1000));
  pScrollAreaChannels->setWidgetResizable(true);
//pScrollAreaChannels->setMinimumSize(700,10);


//pScrollAreaChannels->setMinimumSize(100,100);


  QWidget* pScrollAreaChannelsContents = new QWidget(pSplitterTelemetry);
//  pScrollAreaChannelsContents->setObjectName(QStringLiteral("ScrollAreaTabsContents"));
//  pScrollAreaChannelsContents->setGeometry(QRect(0, 0, 10, 10));
//  pScrollAreaChannelsContents->setMinimumSize(100,100);

  QRect rect = FillTelemetryChannels(pScrollAreaChannelsContents);
  PTabWidgetChannels->setGeometry(rect);

  pScrollAreaChannels->setWidget(pScrollAreaChannelsContents);
  pScrollAreaChannelsContents->setMinimumSize(rect.right()+5,rect.bottom()+5);


//==  2) TelemetryStates + TelemetryReports:

  QScrollArea* pScrollAreaStatesReports = new QScrollArea(pSplitterTelemetry);
//  pScrollAreaStatesReports->setObjectName(QStringLiteral("ScrollAreaStatesReports"));
//  pScrollAreaState->setGeometry(QRect(40, 70, 611, 111));
  pScrollAreaStatesReports->setWidgetResizable(true);

  QWidget* pScrollAreaStatesReportsContents = new QWidget(pSplitterTelemetry);
//  PTabWidgetStates = new MTelemetryTabWidgetStates(pScrollAreaState, PTabWidgetChannels);
//  MTelemetryTabWidgetStates* pScrollAreaStateContents = PTabWidgetStates;
//  pScrollAreaStatesReportsContents->setObjectName(QStringLiteral("ScrollAreaStatesReportsContents"));
//  pScrollAreaStateContents->setGeometry(QRect(0, 0, 609, 109));
//  pScrollAreaStateContents->setMinimumSize(609,109);

//= a) TelemetryStates:
  rect = FillTelemetryStates(pScrollAreaStatesReportsContents);

//= b) TelemetryReports:
  rect |= FillTelemetryReports(pScrollAreaStatesReportsContents);
//msgBox.setText("rect |= FillTelemetryReports(pScrollAreaStatesReportsContents);");   msgBox.exec();

  PTabWidgetStates->setGeometry(rect);

  rect.moveTo(0,PTabWidgetStates->tabBar()->geometry().height()-10);
  rect.setBottom(rect.bottom()-1);
//  rect.setBottom(rect.bottom()+10);
  PTabWidgetReports->setGeometry(rect);

//  PTabWidgetReports->tabBar()->setShape(QTabBar::RoundedSouth);
  PTabWidgetReports->setTabPosition(QTabWidget::South);
  PTabWidgetReports->tabBar()->setShape(QTabBar::RoundedSouth);


//  pScrollAreaStateContents->setMinimumSize(rect.right()+3,rect.bottom()+3);
  pScrollAreaStatesReportsContents->setMinimumSize(rect.right(),rect.bottom()+3);
  pScrollAreaStatesReports->setWidget(pScrollAreaStatesReportsContents);


  for(int i = 0; i < CountAllTelemetryChannels; i++) {
    connect(GetCurrentPTabChannel(i), SIGNAL(SignalChannelTelemetryDoneParam(qreal,float,bool,bool)), this, SLOT(SlotChannelTelemetryDoneParam(qreal,float,bool,bool)));
  }
//==

  rectInfo |= AddInfoPanel(pScrollAreaGyrohorizonContents);

//- Button "START":
  PPushButtonStartTelemetry = new QPushButton(pScrollAreaGyrohorizonContents);
//  PPushButtonStart->setObjectName(QStringLiteral("PushButton"));
  rect.setRect(rectInfo.left()+20,rectInfo.bottom()+40, 60,20);
  PPushButtonStartTelemetry->setGeometry(rect);
//  PPushButtonStart->setAutoDefault(true);
//  PPushButtonStart->setDefault(true);
  PPushButtonStartTelemetry->setText(QApplication::translate("MainWindow", "START", 0));
//PPushButtonStart->setFlat(false);
  PPushButtonStartTelemetry->setEnabled(true);
  connect(PPushButtonStartTelemetry, SIGNAL(clicked()), this, SLOT(SlotStartTelemetry()));
  rectInfo |= rect;

//- Button "STOP":
  PPushButtonStopTelemetry = new QPushButton(pScrollAreaGyrohorizonContents);
//  PPushButtonStart->setObjectName(QStringLiteral("PushButton"));
  rect.setRect(rect.left()+240,rect.top(), 60,20);
  PPushButtonStopTelemetry->setGeometry(rect);
//  PPushButtonStart->setAutoDefault(true);
//  PPushButtonStart->setDefault(true);
  PPushButtonStopTelemetry->setText(QApplication::translate("MainWindow", "STOP", 0));
//PPushButtonStop->setFlat(false);
  PPushButtonStopTelemetry->setEnabled(false);
  connect(PPushButtonStopTelemetry, SIGNAL(clicked()), this, SLOT(SlotStopTelemetry()));
  rectInfo |= rect;

//- Button "Readiness":
//  PPushButtonReadiness = new QPushButton(pScrollAreaStatesReports);//pScrollAreaStateContents);
  PPushButtonReadiness = new QPushButton(pScrollAreaGyrohorizonContents);//pScrollAreaStateContents);
  rect.setRect(rect.left(),rect.top()+60, 60,30);
//  PPushButtonReadiness->setObjectName(QStringLiteral("PushButton"));
  PPushButtonReadiness->setGeometry(rect); //QRect(685, 110, 60, 30));
  PPushButtonReadiness->setAutoDefault(true);
//  PPushButtonReadiness->setDefault(true);
  PPushButtonReadiness->setText(QApplication::translate("MainWindow", "Readiness", 0));
//  PPushButtonReadiness->setText("Readiness");
  connect(PPushButtonReadiness, SIGNAL(clicked()), GetPMainWnd(), SLOT(SlotSwitchToReadiness()));
  rectInfo |= rect;

//-
  pScrollAreaGyrohorizonContents->setMinimumSize(rectInfo.right()+3,rectInfo.bottom()+3);
//  pScrollAreaGyrohorizon->setWidget(pScrollAreaGyrohorizonContents);
//==

  ActivateTabWidgetStates();

//=====

//+  pSplitterTelemetry->addWidget(pScrollAreaChannels);
//+  pSplitterTelemetry->addWidget(pScrollAreaStatesReports);

  list << 490 << 510;    pSplitterTelemetry->setSizes(list);  list.clear();


//=====
//  StartTelemetry();
//  IsTelemetryStarted = false;
}
//--------------------------------------------------------------------------------------------
QRect MTelemetry::FillTelemetryGyrohorizon(QWidget* pScrollAreaGyrohorizonContents)
{
//      QGraphicsScene* pSceneGyrohorizon = new QGraphicsScene(20.0, 20.0, 325.0, 325.0, pTab);
  QGraphicsScene* pSceneGyrohorizon = new QGraphicsScene(pScrollAreaGyrohorizonContents);//pTab);
  QGraphicsView* pViewGyrohorizon = new QGraphicsView(pSceneGyrohorizon, pScrollAreaGyrohorizonContents);//pTab);
  QRect rect(15,15, 320,320);
  pViewGyrohorizon->setGeometry(rect);

//=================
/*+
//QSlider* pSliderPitch = new QSlider(pScrollAreaGyrohorizonContents);//pTab);
pSliderPitch = new QSlider(pScrollAreaGyrohorizonContents);//pTab);
//pSliderPitch->setObjectName(QStringLiteral("verticalSlider"));
pSliderPitch->setOrientation(Qt::Vertical);
pSliderPitch->setGeometry(QRect(360, 450, 16, 360));
pSliderPitch->setMinimum(-360); //1080);
pSliderPitch->setMaximum(360); //1080);
pSliderPitch->setSingleStep(1);
pSliderPitch->setPageStep(36);
pSliderPitch->setValue(0);
pSliderPitch->setTickPosition(QSlider::TicksAbove);
//connect(pSliderPitch, SIGNAL(valueChanged(int)), PEkranoplanGLWidget, SLOT(SetPitchAngle(int)));
//connect(pSliderPitch, SIGNAL(valueChanged(int)), PGyrohorizon, SLOT(SetPitchAngle(int)));

//QSlider* pSliderRoll = new QSlider(pScrollAreaGyrohorizonContents);//pTab);
pSliderRoll = new QSlider(pScrollAreaGyrohorizonContents);//pTab);
//pSliderRoll->setObjectName(QStringLiteral("horizontalSlider"));
pSliderRoll->setOrientation(Qt::Horizontal);
pSliderRoll->setGeometry(QRect(10, 820, 360, 16));
pSliderRoll->setMinimum(-360);
pSliderRoll->setMaximum(360);
pSliderRoll->setSingleStep(1);
pSliderRoll->setPageStep(36);
pSliderRoll->setValue(0);
pSliderRoll->setTickPosition(QSlider::TicksAbove);
//connect(pSliderRoll, SIGNAL(valueChanged(int)), PEkranoplanGLWidget, SLOT(SetRollAngle(int)));
//connect(pSliderRoll, SIGNAL(valueChanged(int)), PGyrohorizon, SLOT(SetRollAngle(int)));
*/
//=================

//      PEkranoplanGLWidget = new MEkranoplanGLWidget(pViewGyrohorizon); // !


//      PGyrohorizon = new MGyrohorizon(pViewGyrohorizon, PEkranoplanGLWidget, pSliderPitch, pSliderRoll);
//+      PGyrohorizon = new MGyrohorizon(pViewGyrohorizon, pSliderPitch, pSliderRoll);
//+      PGyrohorizon->setGeometry(0,0, 320,320);

//MGyrohorizon* PGyrohorizon = new MGyrohorizon(pScrollAreaGyrohorizonContents, pSliderPitch, pSliderRoll);

//  PGyrohorizon = new MGyrohorizon(pScrollAreaGyrohorizonContents, pSliderPitch, pSliderRoll);
  PGyrohorizon = new MGyrohorizon(pScrollAreaGyrohorizonContents);
  PGyrohorizon->setGeometry(rect);//15,15, 320,320);

//PGyrohorizon->setStyleSheet(QLatin1String("background: transparent;"));
//+      QGraphicsProxyWidget* pw = pSceneGyrohorizon->addWidget(PGyrohorizon);
//      pw->setRotation(10.0);
//pw->setOpacity(0.3);

//pViewGyrohorizon->rotate(30.0);

//      QGraphicsView* pViewGyrohorizonStatic = new QGraphicsView(pSceneGyrohorizon, pTab);
//      pViewGyrohorizonStatic->setGeometry(20,20, 321,321);

//pViewGyrohorizonStatic->rotate(30.0);

//  pViewGyrohorizon->setViewport(PEkranoplanGLWidget); // !

//PEkranoplanGLWidget = new MEkranoplanGLWidget(pViewGyrohorizon); // !
//      PEkranoplanGLWidget->setParent(pViewGyrohorizon);
//      QGraphicsProxyWidget* pw1 = pSceneGyrohorizon->addWidget(PEkranoplanGLWidget);


//  MEkranoplanGL* PEkranoplanGL = new MEkranoplanGL(pViewGyrohorizon); // !
  PEkranoplanGL = new MEkranoplanGL(pViewGyrohorizon); // !
//      PEkranoplanGL = new MEkranoplanGL(PGyrohorizon); // !
//      PEkranoplanGL = new MEkranoplanGL(pSceneGyrohorizon); // !
//      PEkranoplanGL = new MEkranoplanGL(0); // !
//      PEkranoplanGL->setWindowOpacity(0.0);
//PEkranoplanGL->setStyleSheet(QLatin1String("background: transparent;"));

//PEkranoplanGLWidget->hide();
//PEkranoplanGLWidget->setVisible(false);

//+      QGraphicsProxyWidget* pw1 = pSceneGyrohorizon->addWidget(PEkranoplanGLWidget);
//  pViewGyrohorizon->setViewport(PEkranoplanGLWidget); // !
//pw1->setOpacity(0.3);

//QGraphicsProxyWidget* pw = pSceneGyrohorizon->addWidget(PGyrohorizon);

  PGyrohorizon->SetPEkranoplanGL(PEkranoplanGL);

//=================
/*+
connect(pSliderPitch, SIGNAL(valueChanged(int)), PGyrohorizon, SLOT(SlotSetPitchAngle(int)));
connect(pSliderPitch, SIGNAL(valueChanged(int)), PEkranoplanGL, SLOT(SlotSetPitchAngle(int)));
//connect(pSliderPitch, SIGNAL(sliderPressed()),  PGyrohorizon, SLOT(SliderPitchPressed()));
//connect(pSliderPitch, SIGNAL(sliderReleased()), PGyrohorizon, SLOT(SliderPitchReleased()));


connect(pSliderRoll, SIGNAL(valueChanged(int)), PGyrohorizon, SLOT(SlotSetRollAngle(int)));
connect(pSliderRoll, SIGNAL(valueChanged(int)), PEkranoplanGL, SLOT(SlotSetRollAngle(int)));
*/
//=================

//=================
//+connect(this, SIGNAL(SignalSetPitchAngle(int)), PGyrohorizon, SLOT(SlotSetPitchAngle(int)));
//+connect(this, SIGNAL(SignalSetPitchAngle(int)), PEkranoplanGL, SLOT(SlotSetPitchAngle(int)));

//connect(pSliderPitch, SIGNAL(sliderPressed()),  PGyrohorizon, SLOT(SliderPitchPressed()));
//connect(pSliderPitch, SIGNAL(sliderReleased()), PGyrohorizon, SLOT(SliderPitchReleased()));


//+connect(this, SIGNAL(SignalSetRollAngle(int)), PGyrohorizon, SLOT(SlotSetRollAngle(int)));
//+connect(this, SIGNAL(SignalSetRollAngle(int)), PEkranoplanGL, SLOT(SlotSetRollAngle(int)));
//=================

  return QRect(0,0, PGyrohorizon->geometry().right()+12,PGyrohorizon->geometry().bottom());
}
//--------------------------------------------------------------------------------------------
/*+
void MTelemetry::SetPitchAngle(float pitch)
{
//pSliderPitch->setSliderPosition(pitch);
int ipitch = (int)pitch;
//+++  emit SignalSetPitchAngle(ipitch);
  PGyrohorizon->SetPitchAngle(ipitch);
}
//............................................................................................
void MTelemetry::SetRollAngle(float roll)
{
//pSliderRoll->setSliderPosition(roll);
int iroll = (int)roll;
//+++  emit SignalSetRollAngle(iroll);
  PGyrohorizon->SetRollAngle(iroll);
}
*/
//--------------------------------------------------------------------------------------------
/*
void MTelemetry::SetPitchRollAngles(float pitch, float roll)
{
  PGyrohorizon->SetPitchRollAngles(pitch, roll);
}
*/
//--------------------------------------------------------------------------------------------
QRect MTelemetry::FillTelemetryChannels(QWidget* pScrollAreaChannelsContents)
{
//  CurrentIndexTabChannel = -1;
//  QRect rectTelemetryChannels;  QRect rect;
//  PTabWidgetChannels = new QTabWidget(pScrollAreaChannelsContents);

  PTabWidgetChannels = new MTelemetryTabWidgetChannels(pScrollAreaChannelsContents,
                                                       GetPMainWnd()->GetPListParamsTelemetryChannels(),
                                                       GetPMainWnd()->GetIFirstItemListParamsTelemetry());
//  PTabWidgetChannels->setObjectName(QStringLiteral("PTabWidgetChannels"));

  QRect rectTelemetryChannels = PTabWidgetChannels->AddTabs();
  CountAllTelemetryChannels += PTabWidgetChannels->count();


//  rectTelemetryChannels.translate(-rectTelemetryChannels.left(), -rectTelemetryChannels.top());
//  rectTelemetryChannels.translate(3,0);
  rectTelemetryChannels.setTopLeft(QPoint(0,0));//.translate(-rectTelemetryChannels.left(), -rectTelemetryChannels.top());
//  rectTelemetryChannels.setBottom(rectTelemetryChannels.bottom() + PTabWidgetChannels->tabBar()->rect().height());
  rectTelemetryChannels.setBottomRight(QPoint(rectTelemetryChannels.right() + 15,
                                              rectTelemetryChannels.bottom() + 4 + PTabWidgetChannels->tabBar()->rect().height()));
//  PTabWidgetChannels->setGeometry(rectTelemetryChannels);
  return rectTelemetryChannels;
}
//--------------------------------------------------------------------------------------------
/*
void MTelemetry::SlotIndexTabChannelsChanged(int newIndex)
{
  if(CurrentIndexTabChannel != newIndex) {
    QTabBar* pTabBar = PTabWidgetChannels->tabBar();
    if(0 <= CurrentIndexTabChannel) {
      pTabBar->setTabTextColor(CurrentIndexTabChannel, QColor(0,0,0));
    }
    pTabBar->setTabTextColor(newIndex, QColor(0,0,255));
    CurrentIndexTabChannel = newIndex;
  }
}
*/
//--------------------------------------------------------------------------------------------
QRect MTelemetry::FillTelemetryStates(QWidget* pScrollAreaStatesContents)
{
//  QRect rectTelemetryStates;
//  PTabWidgetStates = new QTabWidget(pScrollAreaStatesContents);
//  PTabWidgetStates = new MTelemetryTabWidgetStates(pScrollAreaStatesContents);//, PTabWidgetChannels);
  PTabWidgetStates = new MTelemetryTabWidgetChannels(pScrollAreaStatesContents,
                                                     GetPMainWnd()->GetPListParamsTelemetryStates(),
                                                     GetPMainWnd()->GetIFirstItemListParamsStates());
//  PTabWidgetStates->setObjectName(QStringLiteral("PTabWidgetStates"));
//  PTabWidgetStates->setGeometry(QRect(0,0, 700,400));

  QRect rectTelemetryStates = PTabWidgetStates->AddTabs();
//PTabWidgetStates->setGeometry(0,0, 400,600);
  CountAllTelemetryChannels += PTabWidgetStates->count();

  return rectTelemetryStates;
}
//--------------------------------------------------------------------------------------------
QRect MTelemetry::FillTelemetryReports(QWidget* pScrollAreaReportsContents)
{
//  QRect rectTelemetryStates;
//  PTabWidgetStates = new QTabWidget(pScrollAreaStatesContents);
//  PTabWidgetReports = new MTelemetryTabWidgetReports(pScrollAreaReportsContents, PTabWidgetChannels, PTabWidgetStates);
  PTabWidgetReports = new MTelemetryTabWidgetReports(pScrollAreaReportsContents);

//  PTabWidgetReports->setObjectName(QStringLiteral("PTabWidgetReports"));
//  PTabWidgetStates->setGeometry(QRect(0,0, 700,400));

//QMessageBox msgBox; msgBox.setText("1  QRect MTelemetry::FillTelemetryReports(QWidget* pScrollAreaReportsContents)");   msgBox.exec();
  QRect rectTelemetryReports = PTabWidgetReports->AddTabs();
//msgBox.setText("2  QRect MTelemetry::FillTelemetryReports(QWidget* pScrollAreaReportsContents)");   msgBox.exec();

//  PTabWidgetReports->setGeometry(rectTelemetryReports);

//  PTabWidgetReports->setTabPosition(QTabWidget::South);
//  PTabWidgetReports->tabBar()->setShape(QTabBar::RoundedSouth);

  return rectTelemetryReports;
}
//--------------------------------------------------------------------------------------------
QRect MTelemetry::AddInfoPanel(QWidget* pScrollAreaGyrohorizonContents)
{
  int xLeftName = 20;  int yTopName = 370;
  QRect rectPanel(xLeftName,yTopName, 1,1);   QRect rectName;  QRect rectValue;

  int countChannelsStates = GetPMainWnd()->GetPListParamsTelemetryStates()->count();
  int countParamsInChannel;
  QString sInfoParam;   QLineEdit* pLineEditInfoParam;

  for(int i = 0; i < countChannelsStates; i++) {
    countParamsInChannel = (*GetPMainWnd()->GetPListParamsTelemetryStates())[i].count();
    for(int j = GetPMainWnd()->GetIFirstItemListParamsStates(); j < countParamsInChannel; j += 3) {
      sInfoParam = (*GetPMainWnd()->GetPListParamsTelemetryStates())[i][j];
      rectName.setRect(xLeftName,yTopName, 300,20);
      rectValue.setRect(xLeftName+245,yTopName, 50,20);
      pLineEditInfoParam = CreateLineEditCurrentValue(pScrollAreaGyrohorizonContents,
                                                      rectName,
//                                                      "Current Value of " + sParam + ":",
                                                      sInfoParam + ":",
                                                      rectValue);
      AssignCorrespondingChannelInfoParam(sInfoParam, pLineEditInfoParam);

      rectPanel |= rectName;
      rectPanel |= rectValue;
      yTopName += 25;
    }
  }

  int i = GetPMainWnd()->GetILongeronsTelemetryChannel();
  countParamsInChannel = (*GetPMainWnd()->GetPListParamsTelemetryChannels())[i].count();
  for(int j = GetPMainWnd()->GetIFirstItemListParamsTelemetry(); j < countParamsInChannel; j += 3) {
    sInfoParam = (*GetPMainWnd()->GetPListParamsTelemetryChannels())[i][j];
    rectName.setRect(xLeftName,yTopName, 300,20);
    rectValue.setRect(xLeftName+245,yTopName, 50,20);
    pLineEditInfoParam = CreateLineEditCurrentValue(pScrollAreaGyrohorizonContents,
                                                    rectName,
//                                                    "Current Value of " + sParam + ":",
                                                    sInfoParam + ":",
                                                    rectValue);
    AssignCorrespondingChannelInfoParam(sInfoParam, pLineEditInfoParam);

    rectPanel |= rectName;
    rectPanel |= rectValue;
    yTopName += 25;
  }

  return rectPanel;
}
//--------------------------------------------------------------------------------------------
void MTelemetry::AssignCorrespondingChannelInfoParam(QString& sInfoParam, QLineEdit* pLineEditInfoParam)
{
  MTelemetryTabChannel* pTabChannel;
  for(int i = 0; i < CountAllTelemetryChannels; i++) {
    pTabChannel = GetCurrentPTabChannel(i);
    for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j ++) {
      if(*pTabChannel->GetPNameParamInChannel(j) == sInfoParam) {
        pTabChannel->AddAssignCorrespondingInfoParam(pLineEditInfoParam);
        return;
      }
    }
  }
}
//--------------------------------------------------------------------------------------------
void MTelemetry::ActivateTabWidgetStates()
{
  SwitchActiveTabWidgetFromTo(PTabWidgetReports, PTabWidgetStates);
}
//--------------------------------------------------------------------------------------------
void MTelemetry::ActivateTabWidgetReports()
{
  SwitchActiveTabWidgetFromTo(PTabWidgetStates, PTabWidgetReports);
}
//--------------------------------------------------------------------------------------------
void MTelemetry::SwitchActiveTabWidgetFromTo(QTabWidget* pTabWidgetFrom, QTabWidget* pTabWidgetTo)
{
  pTabWidgetFrom->stackUnder(pTabWidgetTo);

  for(int i = 0; i < pTabWidgetFrom->count(); i++)  { pTabWidgetFrom->setEnabled(false); }
  for(int i = 0; i < pTabWidgetTo->count(); i++)    { pTabWidgetTo->setEnabled(true);    }
}
//--------------------------------------------------------------------------------------------
//void MTelemetry::DoTelemetry()
void MTelemetry::SlotStartTelemetry()
{
  if(IsTelemetryStarted)  return;
  IsTelemetryStarted = true;

  PPushButtonStartTelemetry->setEnabled(false);
  PPushButtonStopTelemetry->setEnabled(true);

  PPushButtonReadiness->setEnabled(false);

//++  GetPMainWnd()->GetPArduinoConnector()->SetTypeModeTelemetry();
  emit SignalSetTypeModeTelemetry();

  QDateTime currentDataTime = QDateTime::currentDateTime();

  qint64 timeStartTelemetry = currentDataTime.toMSecsSinceEpoch();
  GetPMainWnd()->SetTimeStartTelemetry(timeStartTelemetry);

  connect(&GetPMainWnd()->GetTimer(), SIGNAL(timeout()), this, SLOT(SlotTimerSignal()));

  PrepareFileReport(currentDataTime);

  IsReadyNextCycle = true;

  ICurrentAllChannel = 0; //-1;
//  IsMechanicalChannels = true;
/*+
  IsReadyNextChannel = true;
  IsReadyNextChannelParam = false;
*/
//  SlotTimerSignal();

  MTelemetryTabChannel* pTabChannel;
  for(int n = 0; n < CountAllTelemetryChannels; n++) {
    pTabChannel = GetCurrentPTabChannel(n);
    for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j ++) {
      pTabChannel->ClearPlots();
    }
  }

  GetPMainWnd()->GetTimer().start(TimerInterval);//1000); // /12); // int msec
}
//--------------------------------------------------------------------------------------------
void MTelemetry::SlotStopTelemetry()
{
  if(!IsTelemetryStarted)  return;
  IsTelemetryStarted = false;

  PPushButtonStartTelemetry->setEnabled(true);
  PPushButtonStopTelemetry->setEnabled(false);

  PPushButtonReadiness->setEnabled(true);

  emit SignalStopTakingData();

  if(!disconnect(&GetPMainWnd()->GetTimer(), SIGNAL(timeout()), this, SLOT(SlotTimerSignal()))) {
    QMessageBox msgBox(QMessageBox::Warning, SMessageBoxTitle,
                       "Problem::\n\ndisconnect(&GetPMainWnd()->GetTimer(), SIGNAL(timeout()), this, SLOT(SlotTimerSignal())) == false");
    msgBox.exec();
  }

  CloseFileReport();
}
//--------------------------------------------------------------------------------------------
void MTelemetry::PrepareFileReport(QDateTime& currentDataTime)
{
  NameFileReport = "Report - ";  NameFileReport += currentDataTime.toString("dd.MMM.yyyy - HH.mm.ss");  NameFileReport += ".wig";
  PFileReport = new QFile(NameFileReport);
  if(PFileReport->open(QIODevice::WriteOnly | QIODevice::Text)) {
    PStreamFileReport = new QTextStream(PFileReport);
  }
  else {
    QMessageBox msgBox; msgBox.setText("Problem file \""+NameFileReport+"\"");   msgBox.exec();
  }

  *PStreamFileReport << ReportFileVersion;   *PStreamFileReport << "\n\n";

  ListLengthAllParams.clear();
  MTelemetryTabChannel* pTabChannel;  QString sNameChannel;  QString sNameParamChannel;


//= Calculation of the Channel Lengths:
  QList<int> listLengthChannels;  int lengthChannel;   int lengthNameParamChannel;

//  for(int n = 0; n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count(); n++) {
  for(int n = 0; n < CountAllTelemetryChannels; n++) {
    lengthChannel = 0;

//    pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(n));
    pTabChannel = GetCurrentPTabChannel(n);
//    Q_ASSERT(pTabChannel != NULL); // Q_CHECK_PTR(pTabChannel);
    for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j ++) {
//1), 3)
      lengthChannel += 8; // "T(sec)  "; // = 8 chs
      ListLengthAllParams << 8;
//2), 4)
//      sNameParamChannel = (*pTabChannel->GetPListParamsTelemetryChannel())[pTabChannel->GetIFirstItemListParamsTelemetry() + j*3];
      sNameParamChannel = *pTabChannel->GetPNameParamInChannel(j);
      lengthNameParamChannel = qMax(sNameParamChannel.length(), 16);
//      lengthChannel += sNameParamChannel.length(); // "Rotation Speed (RPM)"
      lengthChannel += lengthNameParamChannel; // "Rotation Speed (RPM)"
                                               // "Power Consumption (W)"
      if(j < pTabChannel->GetPListPlots()->count()-1) {
//2)
        lengthChannel += 4; // "    "
        ListLengthAllParams << lengthNameParamChannel + 4;
      }
      else {
//4)
//        if(n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count()-1) {
        if(n < CountAllTelemetryChannels-1) {
          lengthChannel += 3; //3+1+3; // to "   |   ":  3+1+3 chs
          ListLengthAllParams << lengthNameParamChannel + 3; // to  "   |   ": 3+1+3;
        }
        else {
          ListLengthAllParams << lengthNameParamChannel;
        }
      }
    }
    listLengthChannels << lengthChannel;
  }

  NAllWritingParams = ListLengthAllParams.count();
  IWritingParam = 0;

//= Writing the Channel Names:
//  for(int n = 0; n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count(); n++) {
  for(int n = 0; n < CountAllTelemetryChannels; n++) {
//    sNameChannel = PTabWidgetChannels->tabBar()->tabText(n);
    sNameChannel = *GetCurrentPTabChannel(n)->GetPNameChannel();
    sNameChannel = sNameChannel.leftJustified(listLengthChannels[n]);
    *PStreamFileReport << sNameChannel;
//    if(n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count()-1) {
    if(n < CountAllTelemetryChannels-1) {
//5)
      *PStreamFileReport << "|   ";
    }
  }
  *PStreamFileReport << "\n";


//= Writing the Channel Params Names:

  int m = 0;  QString sParamX;  QString sParamY;

//  for(int n = 0; n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count(); n++) {
  for(int n = 0; n < CountAllTelemetryChannels; n++) {
//    pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(n));    Q_CHECK_PTR(pTabChannel);
    pTabChannel = GetCurrentPTabChannel(n);
    for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j ++) {
      sParamX = "T(sec)";
      sParamX = sParamX.leftJustified(ListLengthAllParams[m]);  m += 1;
      *PStreamFileReport << sParamX;
//      sParamY = (*pTabChannel->GetPListParamsTelemetryChannel())[GetPMainWnd()->GetIFirstItemListParamsTelemetry() + j*3]; //GetPMainWnd()->GetDeltaNItemListParamsTelemetry()];
      sParamY = *pTabChannel->GetPNameParamInChannel(j);
      sParamY = sParamY.leftJustified(ListLengthAllParams[m]);  m += 1;
      *PStreamFileReport << sParamY;
    }
//    if(n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count()-1) {
    if(n < CountAllTelemetryChannels-1) {
//5)
      *PStreamFileReport << "|   ";
    }
  }
  *PStreamFileReport << "\n";


//= Writing the Min and Max Normal Values:

  QString sMinNormalValue;  QString sMaxNormalValue;
  m = 0;  QString sRange;

//  for(int n = 0; n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count(); n++) {
  for(int n = 0; n < CountAllTelemetryChannels; n++) {
//    pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(n));    Q_CHECK_PTR(pTabChannel);
    pTabChannel = GetCurrentPTabChannel(n);

    for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j ++) {
      sRange = " ";  sRange = sRange.leftJustified(ListLengthAllParams[m]);  m += 1;
      *PStreamFileReport << sRange;
/*
      if((*pTabChannel->GetPListPMinNormalValues())[j])
        sMinNormalValue.sprintf("%.1f", *(*pTabChannel->GetPListPMinNormalValues())[j]);
      else
        sMinNormalValue = "N/A";
      if((*pTabChannel->GetPListPMaxNormalValues())[j])
        sMaxNormalValue.sprintf("%.1f", *(*pTabChannel->GetPListPMaxNormalValues())[j]);
      else
        sMaxNormalValue = "N/A";
*/
      sMinNormalValue = *pTabChannel->GetPStringMinNormalValue(j);
      sMaxNormalValue = *pTabChannel->GetPStringMaxNormalValue(j);

      sRange = sMinNormalValue + " -- " + sMaxNormalValue;
      sRange = sRange.leftJustified(ListLengthAllParams[m]);  m += 1;
      *PStreamFileReport << sRange;
    }
//    if(n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count()-1) {
    if(n < CountAllTelemetryChannels-1) {
      *PStreamFileReport << "|   ";
    }
  }
  *PStreamFileReport << "\n";
  PStreamFileReport->flush();
}
//--------------------------------------------------------------------------------------------
void MTelemetry::CloseFileReport()
{
  if(PStreamFileReport) {
    PStreamFileReport->flush();
    delete PStreamFileReport;  PStreamFileReport = NULL;
  }
  if(PFileReport) {
    if(PFileReport->isOpen()) PFileReport->close();
    delete PFileReport;  PFileReport = NULL;
  }
}
//--------------------------------------------------------------------------------------------
MTelemetryTabChannel* MTelemetry::GetCurrentPTabChannel(int iCurrentAllChannel)
{
  MTelemetryTabChannel* pTabChannel;
//  if(IsMechanicalChannels)  pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(iCurrentChannel));
//  else                      pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetStates->widget(ICurrentChannel));

  if(iCurrentAllChannel < PTabWidgetStates->count())
    pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetStates->widget(iCurrentAllChannel));
  else
    pTabChannel = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(iCurrentAllChannel - PTabWidgetStates->count()));

  Q_ASSERT(pTabChannel != NULL); // Q_CHECK_PTR(pTabChannel);
  return pTabChannel;
}
//--------------------------------------------------------------------------------------------
/*+
void MTelemetry::SlotTimerSignal()
{
  if(IsReadyNextChannel)  {
    IsReadyNextChannel = false;

    ICurrentAllChannel += 1;
    if(ICurrentAllChannel >= CountAllTelemetryChannels) {
      PStreamFileReport->flush();
      ICurrentAllChannel = 0;
    }
    MTelemetryTabChannel* pTabChannel = GetCurrentPTabChannel(ICurrentAllChannel);
    connect(pTabChannel, SIGNAL(SignalChannelTelemetryDoneParam(qreal,float,bool,bool)), this, SLOT(SlotChannelTelemetryDoneParam(qreal,float,bool,bool)));
    pTabChannel->BeginGetArduinoValues();
  }
  else {
    if(IsReadyNextChannelParam) {
      IsReadyNextChannelParam = false;
      GetCurrentPTabChannel(ICurrentAllChannel)->GetNextArduinoValue();
    }
  }
//QMessageBox msgBox;  msgBox.setText("1");   msgBox.exec();
}
*/
//--------------------------------------------------------------------------------------------
void MTelemetry::SlotTimerSignal()
{
  if(!IsReadyNextCycle)  return;
  IsReadyNextCycle = false;

  emit SignalGetAllTelemetryValues();

/*+
  if(IsReadyNextChannel)  {
    IsReadyNextChannel = false;

    ICurrentAllChannel += 1;
    if(ICurrentAllChannel >= CountAllTelemetryChannels) {
      PStreamFileReport->flush();
      ICurrentAllChannel = 0;
    }
*/
/*
    if(IsMechanicalChannels) {
      if(ICurrentChannel >= PTabWidgetChannels->count()) {
        ICurrentChannel = 0;
        IsMechanicalChannels = false;
      }
    }
    else {
      if(ICurrentChannel >= PTabWidgetStates->count()) {
        ICurrentChannel = 0;
        IsMechanicalChannels = true;
      }
    }
*/
/*+
    MTelemetryTabChannel* pTabChannel = GetCurrentPTabChannel(ICurrentAllChannel);
    connect(pTabChannel, SIGNAL(SignalChannelTelemetryDoneParam(qreal,float,bool,bool)), this, SLOT(SlotChannelTelemetryDoneParam(qreal,float,bool,bool)));
    pTabChannel->BeginGetArduinoValues();
  }
  else {
    if(IsReadyNextChannelParam) {
      IsReadyNextChannelParam = false;
      GetCurrentPTabChannel(ICurrentAllChannel)->GetNextArduinoValue();
    }
  }
*/
/*
//   double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
//  QString time = QDateTime::toString("mm:ss.z");
//  pPlot->AddValue(1.0, 1.0); pPlot->AddValue(2.0, 2.0);

//  QDateTime dt;
//  ListTabPlots[0]->AddValue(QDateTime::currentDateTime().toString("mm.z"), ((qrand()*1.0)/RAND_MAX)*100.0);
qreal dt = (QDateTime::currentDateTime().toMSecsSinceEpoch()-TimeStart)/1000.0;

MTelemetryTabChannel* pTab = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(0));
(*pTab->GetPListPlots())[1]->AddValue(dt, ((qrand()*1.0)/RAND_MAX)*100.0);


  MTelemetryTabChannel* pTab;
  for(int i = 0; i < PTabWidgetChannels->count(); i++) {
    pTab = qobject_cast<MTelemetryTabChannel*>(PTabWidgetChannels->widget(i));
    for(int n = 0; n < (*GetPMainWnd()->GetPListParamsTelemetryChannels())[i].count()-1; n++) {

   (*pTab->GetPListPlots())[1]->AddValue(dt, ((qrand()*1.0)/RAND_MAX)*100.0);

  }
*/
//QMessageBox msgBox;  msgBox.setText("1");   msgBox.exec();
}
//--------------------------------------------------------------------------------------------
/*+
void MTelemetry::SlotChannelTelemetryDoneParam(qreal dt, float value, bool isNonNormal, bool isLastParamInChannel)
{
  WriteFileReportValue(dt, value, isNonNormal, isLastParamInChannel);

  if(!isLastParamInChannel) {
    IsReadyNextChannelParam = true;
    return;
  }

  MTelemetryTabChannel* pTabChannel = GetCurrentPTabChannel(ICurrentAllChannel);

  if(!disconnect(pTabChannel, SIGNAL(SignalChannelTelemetryDoneParam(qreal,float,bool,bool)), this, SLOT(SlotChannelTelemetryDoneParam(qreal,float,bool,bool)))) {
    QMessageBox msgBox(QMessageBox::Warning, SMessageBoxTitle,
                       "Problem::\n\ndisconnect(pTab, SIGNAL(SignalChannelTelemetryDone()), this, SLOT(SlotChannelTelemetryDone())) == false");
    msgBox.exec();
  }
  IsReadyNextChannel = true;
}
*/
//--------------------------------------------------------------------------------------------
void MTelemetry::SlotChannelTelemetryDoneParam(qreal dt, float value, bool isNonNormal, bool isLastParamInChannel)
{
  WriteFileReportValue(dt, value, isNonNormal, isLastParamInChannel);

  ICurrentAllChannel += 1;
  if(ICurrentAllChannel >= CountAllTelemetryChannels) {
    PStreamFileReport->flush();

    ICurrentAllChannel = 0;
    IsReadyNextCycle = true;
}

/*+
  if(!isLastParamInChannel) {
    IsReadyNextChannelParam = true;
    return;
  }

  MTelemetryTabChannel* pTabChannel = GetCurrentPTabChannel(ICurrentAllChannel);

  if(!disconnect(pTabChannel, SIGNAL(SignalChannelTelemetryDoneParam(qreal,float,bool,bool)), this, SLOT(SlotChannelTelemetryDoneParam(qreal,float,bool,bool)))) {
    QMessageBox msgBox(QMessageBox::Warning, SMessageBoxTitle,
                       "Problem::\n\ndisconnect(pTab, SIGNAL(SignalChannelTelemetryDone()), this, SLOT(SlotChannelTelemetryDone())) == false");
    msgBox.exec();
  }
  IsReadyNextChannel = true;
*/
}
//--------------------------------------------------------------------------------------------
void MTelemetry::WriteFileReportValue(qreal dt, float value, bool isNonNormal, bool isLastParamInChannel)
{
//return;
  if(PStreamFileReport)  {  QString s;
    if(IWritingParam >= NAllWritingParams)  IWritingParam = 0;
    s.sprintf("%.3f", dt);
    s = s.leftJustified(ListLengthAllParams[IWritingParam]);  IWritingParam += 1;
    *PStreamFileReport << s;
    s.sprintf("%.5f", value);
    if(isNonNormal)  s += " *";
    s = s.leftJustified(ListLengthAllParams[IWritingParam]);  IWritingParam += 1;
    *PStreamFileReport << s;

    if(isLastParamInChannel) {
//      if(ICurrentChannel < PTabWidgetChannels->count()-1)  s = "|   ";
      if(ICurrentAllChannel < CountAllTelemetryChannels-1)  s = "|   ";
      else                                                  s = "\n";
      *PStreamFileReport << s;
    }
  }
}
//--------------------------------------------------------------------------------------------
