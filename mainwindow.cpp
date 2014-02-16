#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "constants.h"

//#include <QSplitter>
//#include <QScrollBar>
  #include <QMessageBox>
//#include <QtSerialPort/QtSerialPort>

//#include "Windows.h"
//#define IDM_ABOUTBOX 0x0010

QString SNameTelemetryTabChannel_HS;
QString SNameTelemetryTabChannel_Angles;
QString SNameTelemetryTabChannel_TP;

//============================================================================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//--
//  HMENU hMenu = ::GetSystemMenu((HWND)winId(), FALSE);
//  if(hMenu != NULL) {
//    ::AppendMenuA(hMenu, MF_SEPARATOR, 0, 0);    ::AppendMenuA(hMenu, MF_SEPARATOR, 0, 0);
//    ::AppendMenuA(hMenu, MF_STRING, IDM_ABOUTBOX, "About WIGTS...");
//  }

//+  ListMainSplitterSizes << 100 << 200;

//  Init();

//  setMenuBar(new QMenuBar(0));
//--
}
//--------------------------------------------------------------------------------------------
/*
bool MainWindow::winEvent(MSG *m, long *result)
{
QMessageBox msgBox;  msgBox.setText("bool MainWindow::winEvent(MSG *message, long *result)");    msgBox.exec();
  if(m->message == WM_SYSCOMMAND) {
    if((m->wParam & 0xfff0) == IDM_ABOUTBOX) {
QMessageBox msgBox;  msgBox.setText("bool MainWindow::winEvent(MSG *message, long *result)");    msgBox.exec();
      *result = 0;
      return true;
    }
  }
  return false;
}
*/
//--------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
/*
if(PMainSplitter->isWindow()) {
  QMessageBox msgBox;
  msgBox.setText("MainWindow::~MainWindow()\nPMainSplitter->isWindow() == true   <<===  Correct!");
  msgBox.exec();
}
*/
if(PTelemetry->isWindow()) {
  QMessageBox msgBox;
  msgBox.setText("MainWindow::~MainWindow()\nPTelemetry->isWindow() == true   <<===  Correct!");
  msgBox.exec();
}
if(PReadiness->isWindow()) { //   PReadiness->close();
  QMessageBox msgBox;
  msgBox.setText("MainWindow::~MainWindow()\nPReadiness->isWindow() == true   <<===  Correct!");
  msgBox.exec();
//  delete PReadiness;
//  if(PReadiness->isWindow()) {    QMessageBox msgBox;  msgBox.setText("2 PReadiness->isWindow()");  msgBox.exec(); }
//  PReadiness = NULL;
}
/*
//delete PSceneEkranoplan;
if(PViewEkranoplan->isWindow()) {
  QMessageBox msgBox;
  msgBox.setText("MainWindow::~MainWindow()\nPViewEkranoplan->isWindow() == true   <<===  Correct!");
  msgBox.exec();
}
*/

  DeleteArduinoConnector();
//--
    delete ui;
}
//--------------------------------------------------------------------------------------------
bool MainWindow::event(QEvent* event)
{
//if(isWindow()) {
//  if(isVisible()) {
//    QString s; s.sprintf("event->type() = %d",event->type());  statusBar()->showMessage(s);
//  }
//}
  if(event->type() == QEvent::Close) {
//QMessageBox msgBox;  msgBox.setText("bool MainWindow::event(QEvent* event)");    msgBox.exec();
    if(PReadiness->parentWidget() == NULL)  PReadiness->setParent(this); //  PReadiness->close();
    if(PTelemetry->parentWidget() == NULL)  PTelemetry->setParent(this); //  PTelemetry->close();
  }
//--
//  if(event->type() == IDM_ABOUTBOX) { //QEvent::WinEventAct) {
//  if(m->message == WM_SYSCOMMAND) {
//    if((m->wParam & 0xfff0) == IDM_ABOUTBOX) {
//QMessageBox msgBox;  msgBox.setText("bool MainWindow::event(QEvent* event)");    msgBox.exec();
//      *result = 0;
//      return true;
//    }

  return QMainWindow::event(event); //catch different events
}
//--------------------------------------------------------------------------------------------
void MainWindow::Init()
{
  CreateArduinoConnector();

//  QString sTextTest0("   State of Execution\n");
  InitLists();

//=======

/*++++
  PMainSplitter = new QSplitter(Qt::Horizontal, this); //&w);
  setCentralWidget(PMainSplitter);

//===####  I: Left (Ekranoplan):  ####===
  PSceneEkranoplan = new QGraphicsScene(PMainSplitter);  //    scene.addText("Hello, world!");
  PSceneEkranoplan->addPixmap(QPixmap(":/Ekranoplan.png"));
    //scene.setSceneRect(0,0, 100,100);

  PViewEkranoplan = new QGraphicsView(PSceneEkranoplan);
    //view.setBaseSize(200,500);
  PMainSplitter->addWidget(PViewEkranoplan);

//int ind = psplitter->indexOf(&view);
//QString s;  s.sprintf("ind = %d", ind);
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();

    //psplitter->handle(0)->setFixedWidth(100);
    //psplitter->handle(0)->setMaximumWidth(100);
    //psplitter->setHandleWidth(50);
    //psplitter->resize(1200,500);


//  InitReadiness(this, pSplitter);

//    scene.addEllipse(QRectF(180,360, 40,40),QPen(),QBrush(QColor(255,0,0,255)));
    int xc = 200;  int yc = 380;  int rc = 25;
    QRadialGradient radialGradTestSpot(QPointF(xc, yc), rc);
//    radialGradTestSpot.setColorAt(0, Qt::red);
    radialGradTestSpot.setColorAt(0, QColor(255, 0, 0, 155)); // 255
//    radialGrad.setColorAt(0.5, Qt::blue);
//    radialGradTestSpot.setColorAt(1, Qt::green);
    radialGradTestSpot.setColorAt(1, QColor(0, 255, 0, 155));

//radialGradTestSpot.setColorAt(0, QColor(20, 255, 180, 255)); // 255
//radialGradTestSpot.setColorAt(0.6, QColor(180, 255, 180, 155)); // 255
//radialGradTestSpot.setColorAt(1, QColor(220, 0, 0, 100)); // 255

    PTestSpot = PSceneEkranoplan->addEllipse(QRectF(xc-rc,yc-rc, 2*rc,2*rc),QPen(Qt::NoPen),QBrush(radialGradTestSpot));
*/

//PTelemetry = new MTelemetry(this); //(pSplitter);

//===####  II: 1) Right (Readiness):  ####===

//  QSplitter* pSplitterReadiness = new QSplitter(Qt::Vertical, pSplitter);
  PReadiness = new MReadiness();//PTelemetry);//this);//(pSplitter);
  PReadiness->Init();

//  setCentralWidget(PReadiness);

//PReadiness->Init();

//===####  III: 1) Right (Telemetry):  ####===
  PTelemetry = new MTelemetry(this); //(pSplitter);
  PTelemetry->Init(); // PTelemetry->move(20,0);
//  PTelemetry->setParent(NULL);

//===####    ####===


//  pSplitter->addWidget(PReadiness);
//  PMainSplitter->addWidget(PTelemetry);

//SlotSwitchToTelemetry();
  SlotSwitchToReadiness();


//  QList<int> list;  list << 500 << 1000;    PMainSplitter->setSizes(list);   list.clear();

//======
  connect(PReadiness, SIGNAL(SignalSetTypeModeReadiness()), PArduinoConnector, SLOT(SlotSetTypeModeReadiness()));
  connect(PTelemetry, SIGNAL(SignalSetTypeModeTelemetry()), PArduinoConnector, SLOT(SlotSetTypeModeTelemetry()));

  connect(PTelemetry, SIGNAL(SignalGetAllTelemetryValues()), PArduinoConnector, SLOT(SlotGetAllTelemetryValues()));
  connect(PTelemetry, SIGNAL(SignalStopTakingData()), PArduinoConnector, SLOT(SlotStopTakingData()));


//  PArduinoObject->InitPort();
//  PArduinoConnector->moveToThread(&ThreadArduinoConnector);
//  ThreadArduinoConnector.start();

//PTelemetry->update();
}
//--------------------------------------------------------------------------------------------
void MainWindow::CreateArduinoConnector()
{
//  PArduino = NULL;
  PArduinoConnector = new MArduinoConnector();//this);
//  PArduinoConnector->setParent(NULL);

  PArduinoConnector->moveToThread(&ThreadArduinoConnector);
  connect(&ThreadArduinoConnector, &QThread::finished, PArduinoConnector, &QObject::deleteLater);
  ThreadArduinoConnector.start();

//  connect(PArduinoConnector, SIGNAL(SignalMessage(QString*)), this, SLOT(SlotMessage(QString*)));


//  PArduinoConnector->InitPort();

//++++  PArduinoConnector->moveToThread(&ThreadArduinoConnector);

//++++  ThreadArduinoConnector.start();
}
//--------------------------------------------------------------------------------------------
void MainWindow::DeleteArduinoConnector()
{
  ThreadArduinoConnector.quit();   ThreadArduinoConnector.wait();
}
//--------------------------------------------------------------------------------------------
void MainWindow::SlotMessage(QString* pStr)
{
  QMessageBox msg;  msg.setText(*pStr);   msg.exec();
}
//--------------------------------------------------------------------------------------------
//void MainWindow::InitLists(QString& sTextTest0)
void MainWindow::InitLists()
{
  QString sTextTestTitle("   State of Execution\n");

  QString sNameChannel;     QString sNameChannelPixmapFile;
  QString sTextTest;
  QString sInputTestName1;  QString sInputTestValue1;  QString sOutputTestName1;
  QString sInputTestName2;  QString sInputTestValue2;  QString sOutputTestName2;
  QString sParam1;          QString sParam2;
  QList<QString> list;


// == 1) Engines:  ===

sTextTest = sTextTestTitle;
  sNameChannel = "Right Engine";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Voltage (V)";
  sTextTest += sInputTestName1 + ":\t\t"; //5\n";
  sInputTestValue1 = "5";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "RPM";
//  sParam1 = "    " + sOutputTestName1 + ":\t\t\t\t\t\t\t";
  sParam1 = "    ";  sParam1 += sOutputTestName1;  sParam1 += ":\t\t\t\t\t\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Voltage (V)";
  sTextTest += sInputTestName2 + ":\t\t"; //20\n";
  sInputTestValue2 = "20";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "RPM";
  sParam2 = "    " + sOutputTestName2 + ":\t\t\t\t\t\t\t";
  sTextTest += sParam2;

//=For ChannelTest:
//        0               1                         2
  list << sNameChannel << sNameChannelPixmapFile << sTextTest
 //       3                  4                   5                   6          7        8
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "8"   << "12"
//        9                  10                  11                  12         13       14
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "400" << "600";
  IFirstItemListParamsReadiness = 6;  //  number of "sParam1"
  DeltaNItemListParamsReadiness = 6;  // = 12-6: distance between "sParam1" and "sParam2"
  ListParamsReadinessChannels << list;   list.clear();

//=For ChannelStart:
  ListNamesEngines << sNameChannel;

//=For Telemetry Channel:
//        0               1
  list << sNameChannel << sNameChannelPixmapFile
//        2                         3        4
       << "Rotation Speed (RPM)" << "0.5" << "99.5" //  "2.0 - 98.0"  is the the Range of the "Rotation Speed (RPM)"
//        5                          6        7
       << "Power Consumption (W)" << "0.5" << "99.5"; //  "2.0 - 98.0"  is the the Range of the "Power Consumption (W)"
  IFirstItemListParamsTelemetry = 2; // number of the first param
//  DeltaNItemListParamsTelemetry = 3;  // = 5-2: distance between param1 ("Rotation Speed (RPM)") and param2 ("Power Consumption (W)")
  ListParamsTelemetryChannels << list;   list.clear();


sTextTest = sTextTestTitle;
  sNameChannel = "Left Engine";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Voltage (V)";
  sTextTest += sInputTestName1 + ":\t\t"; //5\n";
  sInputTestValue1 = "5";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "RPM";
  sParam1 = "    " + sOutputTestName1 + ":\t\t\t\t\t\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Voltage (V)";
  sTextTest += sInputTestName2 + ":\t\t"; //20\n";
  sInputTestValue2 = "20";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "RPM";
  sParam2 = "    " + sOutputTestName2 + ":\t\t\t\t\t\t\t";
  sTextTest += sParam2;

//=For ChannelTest:
  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "8"   << "12"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "400" << "600";
  ListParamsReadinessChannels << list;   list.clear();

//=For ChannelStart:
  ListNamesEngines << sNameChannel;

//=For Telemetry Channel:
  list << sNameChannel << sNameChannelPixmapFile
       << "Rotation Speed (RPM)" << "0.5" << "99.5"
       << "Power Consumption (W)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();


// == 2) Sensors:  ===

sTextTest = sTextTestTitle;
  sNameChannel = "Right Sensor";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Angle (°)";
  sTextTest += sInputTestName1 + ":\t\t"; //1\n";
  sInputTestValue1 = "1";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "Voltage (V)";
  sParam1 = "    " + sOutputTestName1 + ":\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Angle (°)";
  sTextTest += sInputTestName2 + ":\t\t"; //10\n";
  sInputTestValue2 = "10";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "Voltage (V)";
  sParam2 = "    " + sOutputTestName2 + ":\t\t";
  sTextTest += sParam2;

//=For ChannelTest:
  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "4.5" << "5.5"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "19"  << "21";
  ListParamsReadinessChannels << list;   list.clear();

//=For ChannelStart:
  ListNamesSensors << sNameChannel;

//=For Telemetry Channel:
  list << sNameChannel << sNameChannelPixmapFile
       << "Voltage (V)" << "20.0" << "80.0"
       << "Power Consumption (W)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();


sTextTest = sTextTestTitle;
  sNameChannel = "Left Sensor";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Angle (°)";
  sTextTest += sInputTestName1 + ":\t\t"; //1\n";
  sInputTestValue1 = "1";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "Voltage (V)";
  sParam1 = "    " + sOutputTestName1 + ":\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Angle (°)";
  sTextTest += sInputTestName2 + ":\t\t"; //10\n";
  sInputTestValue2 = "10";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "Voltage (V)";
  sParam2 = "    " + sOutputTestName2 + ":\t\t";
  sTextTest += sParam2;

//=For ChannelTest:
  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "9.5" << "10.5"   //  "4.5" << "5.5"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "9.5" << "10.5";  //  "19"  << "21";
  ListParamsReadinessChannels << list;   list.clear();

//=For ChannelStart:
  ListNamesSensors << sNameChannel;

//=For Telemetry Channel:
  list << sNameChannel << sNameChannelPixmapFile
       << "Voltage (V)" << "0.5" << "99.5"
       << "Power Consumption (W)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();


// == 3) ServoMotors:  ===

sTextTest = sTextTestTitle;
//  sNameChannel = "Right ServoMotor";  sNameChannelPixmapFile = ":/Engine.png";
  sNameChannel = "Right Longeron";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Voltage (V)";
  sTextTest += sInputTestName1 +":\t\t"; //5\n";
  sInputTestValue1 = "5";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "Angle (°)";
  sParam1 = "    " + sOutputTestName1 + ":\t\t\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Voltage (V)";
  sTextTest += sInputTestName2 + ":\t\t"; //20\n";
  sInputTestValue2 = "20";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "Angle (°)";
  sParam2 = "    " + sOutputTestName2 + ":\t\t\t\t";
  sTextTest += sParam2;

//=For ChannelTest:
  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "0.8" << "1.2"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "9.5" << "10.5";
  ListParamsReadinessChannels << list;   list.clear();

//=For ChannelStart:
  ListNamesServoMotors << sNameChannel;

//=For Telemetry Channel:
  list << "Longerons" << sNameChannelPixmapFile
       << "Left Longeron Angle (°)" << "0.5" << "99.5"
       << "Right Longeron Angle (°)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();
  ILongeronsTelemetryChannel = ListParamsTelemetryChannels.count() - 1;


sTextTest = sTextTestTitle;
//  sNameChannel = "Left ServoMotor";  sNameChannelPixmapFile = ":/Engine.png";
  sNameChannel = "Left Longeron";  sNameChannelPixmapFile = ":/Engine.png";
  sInputTestName1 = "Min Voltage (V)";
  sTextTest += sInputTestName1 +":\t\t"; //5\n";
  sInputTestValue1 = "5";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "Angle (°)";
  sParam1 = "    " + sOutputTestName1 + ":\t\t\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Voltage (V)";
  sTextTest += sInputTestName2 + ":\t\t"; //20\n";
  sInputTestValue2 = "20";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "Angle (°)";
  sParam2 = "    " + sOutputTestName2 + ":\t\t\t\t";
  sTextTest += sParam2;

//=For ChannelTest:
  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "0.8" << "1.2"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "9.5" << "10.5";
  ListParamsReadinessChannels << list;   list.clear();

//=For ChannelStart:
  ListNamesServoMotors << sNameChannel;
/*
//=For Telemetry Channel:
  list << sNameChannel << sNameChannelPixmapFile
       << "Angle (°)" << "0.5" << "99.5"
       << "Power Consumption (W)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();
*/
//--
/*
sTextTest = sTextTestTitle;
  sNameChannel = "Right Longeron";  sNameChannelPixmapFile = ":/Engine.png";

  sInputTestName1 = "Min Voltage (V)";
  sTextTest += sInputTestName1 +":\t\t"; //5\n";
  sInputTestValue1 = "5";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "Angle (°)";
  sParam1 = "    " + sOutputTestName1 + ":\t\t\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Voltage (V)";
  sTextTest += sInputTestName2 + ":\t\t"; //20\n";
  sInputTestValue2 = "20";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "Angle (°)";
  sParam2 = "    " + sOutputTestName2 + ":\t\t\t\t";
  sTextTest += sParam2;

//=For ChannelTest:
  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "0.8" << "1.2"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "9.5" << "10.5";
  ListParamsReadinessChannels << list;   list.clear();

//=For ChannelStart:
  ListNamesServoMotors << sNameChannel;

//=For Telemetry Channel:
  list << sNameChannel << sNameChannelPixmapFile
       << "Angle (°)" << "0.5" << "99.5"
       << "Power Consumption (W)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();


sTextTest = sTextTestTitle;
  sNameChannel = "Left Longeron";  sNameChannelPixmapFile = ":/Engine.png";

  sInputTestName1 = "Min Voltage (V)";
  sTextTest += sInputTestName1 +":\t\t"; //5\n";
  sInputTestValue1 = "5";
  sTextTest += sInputTestValue1;  sTextTest += "\n";
  sOutputTestName1 = "Angle (°)";
  sParam1 = "    " + sOutputTestName1 + ":\t\t\t\t";
  sTextTest += sParam1;  sTextTest += "\n";

  sInputTestName2 = "Max Voltage (V)";
  sTextTest += sInputTestName2 + ":\t\t"; //20\n";
  sInputTestValue2 = "20";
  sTextTest += sInputTestValue2;  sTextTest += "\n";
  sOutputTestName2 = "Angle (°)";
  sParam2 = "    " + sOutputTestName2 + ":\t\t\t\t";
  sTextTest += sParam2;

//=For ChannelTest:
  list << sNameChannel << sNameChannelPixmapFile << sTextTest
       << sInputTestName1 << sInputTestValue1 << sOutputTestName1 << sParam1 << "0.8" << "1.2"
       << sInputTestName2 << sInputTestValue2 << sOutputTestName2 << sParam2 << "9.5" << "10.5";
  ListParamsReadinessChannels << list;   list.clear();

//=For ChannelStart:
  ListNamesServoMotors << sNameChannel;

//=For Telemetry Channel:
  list << sNameChannel << sNameChannelPixmapFile
       << "Angle (°)" << "0.5" << "99.5"
       << "Power Consumption (W)" << "0.5" << "99.5";
  ListParamsTelemetryChannels << list;   list.clear();
*/
//====

//=For Telemetry State:
//  QString sNameParams;  QString sNameParamsPixmapFile;
//sNameParams = "Flight";  sNameParamsPixmapFile = ":/Engine.png";

SNameTelemetryTabChannel_HS = "H, S";
//        0           1
  list << SNameTelemetryTabChannel_HS << ":/Engine.png"
//        2           3       4
       << "Height (cm)" << "N/A" << "N/A"
//        5          6       7
       << "Speed (m/s)" << "N/A" << "N/A";
  ListParamsTelemetryStates << list;   list.clear();
  IFirstItemListParamsStates = 2;  //  number of the first param ("Height")

  SNameTelemetryTabChannel_Angles = "Angles";
  list << SNameTelemetryTabChannel_Angles << ":/Engine.png"
       << "Pitch (°)" << "N/A" << "N/A"
       << "Roll (°)" << "N/A" << "N/A";
  ListParamsTelemetryStates << list;   list.clear();

  list << "D, A" << ":/Engine.png"
       << "Distance Traveled (m)" << "N/A" << "N/A"
       << "Acceleration (m/s**2)" << "N/A" << "N/A";
  ListParamsTelemetryStates << list;   list.clear();

  SNameTelemetryTabChannel_TP = "T, P";
  list << SNameTelemetryTabChannel_TP << ":/Engine.png"
       << "Temperature (°C)" << "N/A" << "N/A"
       << "Pressure (Pa)" << "N/A" << "N/A";
  ListParamsTelemetryStates << list;   list.clear();
}
//--------------------------------------------------------------------------------------------
void MainWindow::SlotSwitchToReadiness()
{
//  SwitchSplitterFromTo(PTelemetry, PReadiness);
  SwitchSplitterTo(PReadiness);
/*
//QString s;  s.sprintf("ind = %d", PMainSplitter->indexOf(PTelemetry));
//QMessageBox msgBox; msgBox.setText(s);   msgBox.exec();

//int x = PViewAirplane->horizontalScrollBar()->value();
//int y = PViewAirplane->verticalScrollBar()->value();
//QString s;  s.sprintf("x = %d   y = %d", x,y);
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();

  int x, y;
  int index = PMainSplitter->indexOf(PTelemetry);
  if(index >= 0) {
    x = PViewAirplane->horizontalScrollBar()->value();
    y = PViewAirplane->verticalScrollBar()->value();
    ListMainSplitterSizes = PMainSplitter->sizes();
    PMainSplitter->widget(index)->setParent(NULL);
  }
  PMainSplitter->addWidget(PReadiness);
//  if(index < 0)  {
//    QList<int> list;  list << 500 << 1000;    PMainSplitter->setSizes(list);   list.clear();
  PMainSplitter->setSizes(ListMainSplitterSizes);//  ListMainSplitterSizes.clear();
//  }
  if(index >= 0) {  //  PViewAirplane->scroll(x,y);
    PViewAirplane->horizontalScrollBar()->setValue(x);
    PViewAirplane->verticalScrollBar()->setValue(y);
  }
*/
}
//--------------------------------------------------------------------------------------------
void MainWindow::SlotSwitchToTelemetry()
{
//  SwitchSplitterFromTo(PReadiness, PTelemetry);
  SwitchSplitterTo(PTelemetry);

//+  PTelemetry->DoTelemetry();

/*
//int x = PViewAirplane->horizontalScrollBar()->value();
//int y = PViewAirplane->verticalScrollBar()->value();
//QString s;  s.sprintf("x = %d   y = %d", x,y);
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();

  int x, y;
  int index = PMainSplitter->indexOf(PReadiness);

  if(index >= 0) {
    x = PViewAirplane->horizontalScrollBar()->value();
    y = PViewAirplane->verticalScrollBar()->value();
    ListMainSplitterSizes = PMainSplitter->sizes();
    PMainSplitter->widget(index)->setParent(NULL);
  }
  PMainSplitter->addWidget(PTelemetry);


//  if(index < 0)  {
//    QList<int> list;  list << 500 << 1000;    PMainSplitter->setSizes(list);   list.clear();
  PMainSplitter->setSizes(ListMainSplitterSizes);//  ListMainSplitterSizes.clear();
//  }
  if(index >= 0) {  //  PViewAirplane->scroll(x,y);
    PViewAirplane->horizontalScrollBar()->setValue(x);
    PViewAirplane->verticalScrollBar()->setValue(y);
  }
*/
}
//--------------------------------------------------------------------------------------------
//void MainWindow::SwitchSplitterFromTo(QWidget* pWidgetFrom, QWidget* pWidgetTo)
void MainWindow::SwitchSplitterTo(QWidget* pWidget)
{
//  Q_ASSERT(pWidgetFrom == takeCentralWidget());
  takeCentralWidget();
  setCentralWidget(pWidget);

/*++++
//QString s;  s.sprintf("ind = %d", PMainSplitter->indexOf(PTelemetry));
//QMessageBox msgBox; msgBox.setText(s);   msgBox.exec();

//int x = PViewAirplane->horizontalScrollBar()->value();
//int y = PViewAirplane->verticalScrollBar()->value();
//QString s;  s.sprintf("x = %d   y = %d", x,y);
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();

  int x, y;
  int index = PMainSplitter->indexOf(pWidgetFrom);
  if(index >= 0) {
    x = PViewEkranoplan->horizontalScrollBar()->value();
    y = PViewEkranoplan->verticalScrollBar()->value();
    ListMainSplitterSizes = PMainSplitter->sizes();
    PMainSplitter->widget(index)->setParent(NULL);
  }
  PMainSplitter->addWidget(pWidgetTo);
//pWidgetTo->setParent(PMainSplitter);

//  if(index < 0)  {
//    QList<int> list;  list << 500 << 1000;    PMainSplitter->setSizes(list);   list.clear();
  PMainSplitter->setSizes(ListMainSplitterSizes);//  ListMainSplitterSizes.clear();
//  }
  if(index >= 0) {  //  PViewAirplane->scroll(x,y);
    PViewEkranoplan->horizontalScrollBar()->setValue(x);
    PViewEkranoplan->verticalScrollBar()->setValue(y);
  }

//QString s; s.sprintf("PMainSplitter->count()   = %d",PMainSplitter->count());
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();
*/
}
//--------------------------------------------------------------------------------------------
/*
void MainWindow::CreateArduinoObject(const QObject* pSenderReceiver, const char *signalThis, const char *slotArduino,
                                                                     const char *signalArduino, const char *slotThis)
{
//  if(PArduino == NULL)  {
  PArduino = new MArduino;
  PArduino->moveToThread(&ThreadArduino);
  connect(&ThreadArduino, &QThread::finished, PArduino, &QObject::deleteLater);
//  }
  connect(pSenderReceiver, signalThis, PArduino, slotArduino);
  connect(PArduino, signalArduino, pSenderReceiver, slotThis);
//  if(!ThreadArduino.isRunning())
  ThreadArduino.start(); // ThreadTest.wait(5000);
}
//--------------------------------------------------------------------------------------------
void MainWindow::DestroyArduinoObject()
{
  ThreadArduino.quit();    ThreadArduino.wait();
}
*/
//--------------------------------------------------------------------------------------------
