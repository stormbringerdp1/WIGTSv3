#include "MReadiness.h"
#include "mainwindow.h"
#include "funcs.h"

#include <QApplication>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QIcon>
#include <QLabel>
#include <QListWidgetItem>
  #include <QMessageBox>
#include <QProgressBar>
#include <QRadialGradient>
#include <QScrollArea>
  #include <QStatusBar>

//============================================================================================
MReadiness::MReadiness(QWidget *parent) :
//  QSplitter(Qt::Vertical, parent)
  QSplitter(Qt::Horizontal, parent)
{
  SMessageBoxTitle = QCoreApplication::instance()->applicationName()+":  Readiness";

//  Init();
}
//--------------------------------------------------------------------------------------------
MReadiness::~MReadiness()
{
//PPort->close();
}
//--------------------------------------------------------------------------------------------
/*
MainWindow* MReadiness::GetPMainWnd()
{
  MainWindow* pMainWindow;
  foreach(QWidget* pwidget, QApplication::topLevelWidgets()) {
    pMainWindow = qobject_cast<MainWindow*>(pwidget);
    if(pMainWindow != NULL) break;
  }

//  MainWindow* pMainWindow = qobject_cast<MainWindow*>(parentWidget()->parentWidget());
  if(pMainWindow == NULL) {
//    QString s;  s.sprintf("ind = %d", ind);
    QMessageBox msgBox(QMessageBox::Critical, SMessageBoxTitle, "GetPMainWnd() == NULL");   msgBox.exec();
  }
  return pMainWindow;
}
*/
//--------------------------------------------------------------------------------------------
void MReadiness::Init()
{
//===####  I: Left (Ekranoplan):  ####===

  QGraphicsScene* PSceneEkranoplan = new QGraphicsScene(this);//PMainSplitter);  //    scene.addText("Hello, world!");
  PSceneEkranoplan->addPixmap(QPixmap(":/Ekranoplan.png"));
    //scene.setSceneRect(0,0, 100,100);

  QGraphicsView* PViewEkranoplan = new QGraphicsView(PSceneEkranoplan, this);
    //view.setBaseSize(200,500);
//  PMainSplitter->addWidget(PViewEkranoplan);
//++  addWidget(PViewEkranoplan);


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

     QGraphicsEllipseItem* PTestSpot = PSceneEkranoplan->addEllipse(QRectF(xc-rc,yc-rc, 2*rc,2*rc),QPen(Qt::NoPen),QBrush(radialGradTestSpot));



//===####  II: 1) Right (Channels):  ####===

  QSplitter* pSplitterReadiness = new QSplitter(Qt::Vertical, this);//pSplitter);
//++  addWidget(pSplitterReadiness);

  QList<int> list;  list << 150 << 200;    setSizes(list);   list.clear();


//===  1) ReadinessTest:

//    scrollArea = new QScrollArea(centralWidget);
  QScrollArea* pScrollAreaTest = new QScrollArea(pSplitterReadiness);//this);
//  pScrollAreaTest->setObjectName(QStringLiteral("ScrollAreaTest"));
//+  pScrollAreaTest->setGeometry(QRect(40, 70, 611, 111));
  pScrollAreaTest->setWidgetResizable(true);
//pScrollAreaTest->setBaseSize(30,40);
//addWidget(pScrollAreaTest);

  QWidget* pScrollAreaTestContents = new QWidget(pSplitterReadiness);//this);
  pScrollAreaTestContents->setObjectName(QStringLiteral("ScrollAreaTestContents"));
//+  pScrollAreaTestContents->setGeometry(QRect(0, 0, 609, 109));
//pScrollAreaTestContents->setBaseSize(30,40);
//  pScrollAreaTestContents->setMinimumSize(609,109);

//pScrollAreaTest->setWidget(pScrollAreaTestContents);
//pScrollAreaTestContents->setParent(pScrollAreaTest);

//  pScrollAreaTestContents->setMinimumSize(609,109);
  QRect rect = FillReadinessTest(pScrollAreaTestContents);
  pScrollAreaTestContents->setMinimumSize(rect.right()+3,rect.bottom()+3);

//pScrollAreaTest->adjustSize();
//pScrollAreaTest->setMinimumWidth(100);
//pScrollAreaTest->setMaximumWidth(200);
//pScrollAreaTestContents->setMinimumWidth(600);
//pScrollAreaTestContents->setMaximumWidth(200);
  pScrollAreaTest->setWidget(pScrollAreaTestContents);


//===  2) ReadinessStart:

  QScrollArea* pScrollAreaStart = new QScrollArea(pSplitterReadiness);//this);
//  pScrollAreaStart->setObjectName(QStringLiteral("ScrollAreaStart"));
  pScrollAreaStart->setGeometry(QRect(40, 70, 611, 111));
  pScrollAreaStart->setWidgetResizable(true);
//addWidget(pScrollAreaStart);

  QWidget* pScrollAreaStartContents = new QWidget(pSplitterReadiness);//this);
//  pScrollAreaStartContents->setObjectName(QStringLiteral("ScrollAreaStartContents"));
//  pScrollAreaStartContents->setGeometry(QRect(0, 0, 609, 109));
//  pScrollAreaStartContents->setMinimumSize(609,109);

  rect = FillReadinessStart(pScrollAreaStartContents);
  pScrollAreaStartContents->setMinimumSize(rect.right()+3,rect.bottom()+3);
  pScrollAreaStart->setWidget(pScrollAreaStartContents);

//===

//  pSplitterReadiness->addWidget(pScrollAreaTest);
//  pSplitterReadiness->addWidget(pScrollAreaStart);
//  list << 700 << 200;    pSplitterReadiness->setSizes(list);

//++  pSplitterReadiness->addWidget(pScrollAreaTest);
//++  pSplitterReadiness->addWidget(pScrollAreaStart);
  list << 800 << 200;   pSplitterReadiness->setSizes(list);  list.clear();

//pScrollAreaTest->setWidget(listview);
//pScrollAreaTest->setWidget(treeview);
//pScrollAreaTest->setWidget(textedit);
//     MTestChannel* pTestCannel = new MTestChannel;


//=================
//=================
/*
//  QSerialPort* pSerialPort = new QSerialPort(this);
  QString sp;
  foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
    sp += QObject::tr("Port: ") + info.portName() + "\n"
        + QObject::tr("Location: ") + info.systemLocation() + "\n"
        + QObject::tr("Description: ") + info.description() + "\n"
        + QObject::tr("Manufacturer: ") + info.manufacturer() + "\n"
        + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
        + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n"
        + QObject::tr("Busy: ") + (info.isBusy() ? QObject::tr("Yes") : QObject::tr("No")) + "\n";
  }
QMessageBox msgBox;  msgBox.setText(sp);  msgBox.exec();
*/

/*++++
//=================

//  QSerialPort* pSerialPort = new QSerialPort(this);
//  QString sp;

QSlider* pSlider = new QSlider(pScrollAreaTest);
//pSlider->setObjectName(QStringLiteral("verticalSlider"));
pSlider->setOrientation(Qt::Vertical);
pSlider->setGeometry(QRect(600, 120, 16, 160));
pSlider->setMinimum(0);
pSlider->setMaximum(255);
pSlider->setSingleStep(1);
pSlider->setPageStep(25);
pSlider->setValue(0);
pSlider->setTickPosition(QSlider::TicksAbove);


QString portName("COM3");
PPort = new QSerialPort(this);
PPort->setPortName(portName);
if(PPort->open(QIODevice::WriteOnly))  {
  PPort->setBaudRate(QSerialPort::Baud9600);
  PPort->setDataBits(QSerialPort::Data8);
  PPort->setParity(QSerialPort::NoParity);
  PPort->setStopBits(QSerialPort::OneStop);
  PPort->setFlowControl(QSerialPort::NoFlowControl);

  QMessageBox msgBox;  msgBox.setText("Port \""+portName+"\" is open");  msgBox.exec();
}
else {
  QMessageBox msgBox;  msgBox.setText("Port \""+portName+"\" is not open");  msgBox.exec();
}

connect(pSlider, SIGNAL(valueChanged(int)), this, SLOT(SlotArduino_ControlLED(int)));
connect(PPort, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(SlotPortError(QSerialPort::SerialPortError)));
//=================
*/
}
//............................................................................................
/*++++
void MReadiness::SlotArduino_ControlLED(int value)
{
if(value < 0 || value > 255) return;

//==Qt 5.1.1(x86):
//byte bytes[1]; bytes[0] = (byte)value;
//==Qt 5.2.0(x64):
uchar bytes[1]; bytes[0] = (uchar)value;

//QByteArray ba(1, bvalue);
//QString sv; sv.sprintf("%d",value);
//GetPMainWnd()->statusBar()->showMessage(sv);
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();
//PPort->write(sv.toStdString().c_str());
PPort->write((char*)bytes, 1);
}
//............................................................................................
void MReadiness::SlotPortError(QSerialPort::SerialPortError ierror)
{
if(ierror == 0)  return;
QString s; s.sprintf("ierror = %d\n", ierror); s += PPort->errorString();
QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();
*/
/*
QSerialPort::NoError	0	No error occurred.
QSerialPort::DeviceNotFoundError	1	An error occurred while attempting to open an non-existing device.
QSerialPort::PermissionError	2	An error occurred while attempting to open an already opened device by another process or a user not having enough permission and credentials to open.
QSerialPort::OpenError	3	An error occurred while attempting to open an already opened device in this object.
QSerialPort::ParityError	4	Parity error detected by the hardware while reading data.
QSerialPort::FramingError	5	Framing error detected by the hardware while reading data.
QSerialPort::BreakConditionError	6	Break condition detected by the hardware on the input line.
QSerialPort::WriteError	7	An I/O error occurred while writing the data.
QSerialPort::ReadError	8	An I/O error occurred while reading the data.
QSerialPort::ResourceError	9	An I/O error occurred when a resource becomes unavailable, e.g. when the device is unexpectedly removed from the system.
QSerialPort::UnsupportedOperationError	10	The requested device operation is not supported or prohibited by the running operating system.
QSerialPort::UnknownError	11	An unidentified error occurred.
*/
//}
//--------------------------------------------------------------------------------------------
QRect MReadiness::FillReadinessTest(QWidget* pScrollAreaTestContents)
{
  QRect rectReadinessTest;    QRect rect;
  int yTopChannel = 0;

  int count = GetPMainWnd()->GetPListParamsReadinessChannels()->count();
  for(int i = 0; i < count; i++) {
//    rect = AddReadinessTestChannel(pScrollAreaTestContents, yTopChannel,// "Engine.png",
//                                              &(*GetPMainWnd()->GetPListParamsReadinessChannels())[i]);
    MReadinessTestChannel* pReadinessTestChannel = new MReadinessTestChannel(pScrollAreaTestContents, yTopChannel,// namePixmapFileChannel,
                                                                           &(*GetPMainWnd()->GetPListParamsReadinessChannels())[i]);
//    pReadinessTestChannel->setObjectName(QStringLiteral("MReadinessTestChannel"));
//    pReadinessTestChannel->setGeometry(QRect(0,0, 1,1));
    ListReadinessTestChannels << pReadinessTestChannel;

//  connect(pReadinessTestChannel, SIGNAL(SignalStartTestChannel()), this, SLOT(SlotStartTestChannel()));
    connect(pReadinessTestChannel, SIGNAL(SignalResultTestChannel(bool)), this, SLOT(SlotResultTestChannel(bool)));

    rect = pReadinessTestChannel->GetRectChannel();

    yTopChannel += rect.height() + 10;
    if(i == 0)  rectReadinessTest = rect;
    else        rectReadinessTest |= rect;
  }

/*
  QList<QString> listParamsNameTest;
  QList<int>     listParamsRangeTest;
  QString        sTextTest0("   State of Execution\n");
  QString        sTextTest;

//=1)= Right Engine:
  listParamsNameTest  << "Max RPM:"  <<  "Min RPM:";
  listParamsRangeTest << 400 << 600  <<  8 << 12;

  sTextTest  = sTextTest0;
  sTextTest += "Max Voltage:\t20 V\n";
  sTextTest += listParamsNameTest[0];  sTextTest += "\t\n";
  sTextTest += "Min Voltage:\t5 V\n";
  sTextTest += listParamsNameTest[1];  sTextTest += "\t";

  yBottomChannel = AddReadinessTestChannel(pScrollAreaTestContents, yBottomChannel+10, "Right Engine", "Engine.png",
                                           &sTextTest, &listParamsNameTest, &listParamsRangeTest);
  listParamsNameTest.clear();  listParamsNameTest.clear();  sTextTest.clear();
*/

//=2)= Left Engine:
/*
  listParamsNameTest  << "Max RPM:"  <<  "Min RPM:";
  listParamsRangeTest << 400 << 600  <<  8 << 12;

  sTextTest  = sTextTest0;
  sTextTest += "Max Voltage:\t20 V\n";
  sTextTest += listParamsNameTest[0];  sTextTest += "\t\n";
  sTextTest += "Min Voltage:\t5 V\n";
  sTextTest += listParamsNameTest[1];  sTextTest += "\t";

  yBottomChannel = AddReadinessTestChannel(pScrollAreaTestContents, yBottomChannel+10, "Left Engine", "Engine.png",
                                           &sTextTest, &listParamsNameTest, &listParamsRangeTest);
  listParamsNameTest.clear();  listParamsNameTest.clear();  sTextTest.clear();
*/
  return rectReadinessTest;
}
//--------------------------------------------------------------------------------------------
/*
//int MReadiness::AddReadinessTestChannel(QWidget* pParent, const int yTopChannel, const char* nameChannel, const char* namePixmapFileChannel,
//                                                QString* pTextTest, QList<QString>* pListParamsNameTest, QList<int>* pListParamsRangeTest)
QRect MReadiness::AddReadinessTestChannel(QWidget* pParent, const int yTopChannel, //const char* namePixmapFileChannel,
//                                        QString* pTextTest, QList<QString>* pListParamsChannel)
                                        QList<QString>* pListParamsChannel)
{
  MReadinessTestChannel* pReadinessTestChannel = new MReadinessTestChannel(pParent, yTopChannel,// namePixmapFileChannel,
//                                                                           pTextTest, pListParamsChannel);
                                                                           pListParamsChannel);
  pReadinessTestChannel->setObjectName(QStringLiteral("MReadinessTestChannel"));
//  pReadinessTestChannel->setGeometry(QRect(0,0, 1,1));
  ListReadinessTestChannels << pReadinessTestChannel;

//  connect(pReadinessTestChannel, SIGNAL(SignalStartTestChannel()), this, SLOT(SlotStartTestChannel()));
  connect(pReadinessTestChannel, SIGNAL(SignalResultTestChannel(bool)), this, SLOT(SlotResultTestChannel(bool)));

//  ListReadinessTestChannels <<  new MReadinessTestChannel(pParent, yTopChannel, namePixmapFileChannel,
//                                                          pTextTest, pListParamsChannel);
//  int count = ListReadinessTestChannels.count();
//  PListReadinessTestChannel[count-1]->
//  return 140;
  return pReadinessTestChannel->GetRectChannel();
}
*/
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
QRect MReadiness::FillReadinessStart(QWidget* pScrollAreaStartContents)
{
  QRect rectReadinessStart;    QRect rect;

//= Button "START":
  PPushButtonStart = new QPushButton(pScrollAreaStartContents);
//  PPushButtonStart->setObjectName(QStringLiteral("PushButton"));
  rect = QRect(20, 30, 61, 51);   rectReadinessStart = rect;
  PPushButtonStart->setGeometry(rect);
//  PPushButtonStart->setAutoDefault(true);
//  PPushButtonStart->setDefault(true);
  PPushButtonStart->setText(QApplication::translate("MainWindow", "START", 0));
//PPushButtonStart->setFlat(false);
  connect(PPushButtonStart, SIGNAL(clicked()), this, SLOT(SlotStart()));

/*
iListView = new QListView(this);
//Creating a standard item model
iStandardModel = new QStandardItemModel(this);
//First item
QStandardItem* item1 = new QStandardItem(QIcon("c:\\data\\Nokia- logo.bmp"),"First Item");
//Second item
QStandardItem* item2 = new QStandardItem(QIcon("c:\\data\\sample.bmp"),"Second item");
//third item without icon
QStandardItem* item3 = new QStandardItem("Without icon item");
//Appending the items into model
iStandardModel->appendRow(item1);
iStandardModel->appendRow(item2);
iStandardModel->appendRow(item3);
//Setting the icon size
iListView->setIconSize(QSize(40,30));
//Setting the model
iListView->setModel(iStandardModel);
//Setting listview geometry
iListView->setGeometry(QRect(0,0,240,320));
*/
//  QListWidget* pListWidgetEngines; // = new QListWidget(pScrollAreaStartContents);
  rect = QRect(100, 30, 121, 101);   rectReadinessStart |= rect;
  CreateListWidget("Engines", PListWidgetEngines, pScrollAreaStartContents, rect, GetPMainWnd()->GetPListNamesEngines());
  rect = QRect(250, 30, 121, 101);   rectReadinessStart |= rect;
  CreateListWidget("Sensors", PListWidgetSensors, pScrollAreaStartContents, rect, GetPMainWnd()->GetPListNamesSensors());
  rect = QRect(400, 30, 121, 101);   rectReadinessStart |= rect;
  CreateListWidget("ServoMotors", PListWidgetServoMotors, pScrollAreaStartContents, rect, GetPMainWnd()->GetPListNamesServoMotors());

//  AddReadinessStartListItem(pListWidgetEngines, GetPMainWnd()->GetPListNamesEngine());
//  AddReadinessStartListItem(pListWidgetSensors, GetPMainWindow()->GetPListNamesSensor());
//  AddReadinessStartListItem(pListWidgetServoMotors, GetPMainWindow()->GetPListNamesServoMotor());

//= Button "Telemetry":
  PPushButtonTelemetry = new QPushButton(pScrollAreaStartContents);
//  PPushButtonTelemetry->setObjectName(QStringLiteral("PushButton"));
  rect = QRect(535, 10, 60, 30);   rectReadinessStart |= rect;
  PPushButtonTelemetry->setGeometry(rect);
  PPushButtonTelemetry->setAutoDefault(true);
//  PPushButtonStart->setDefault(true);
  PPushButtonTelemetry->setText(QApplication::translate("MainWindow", "Telemetry", 0));
  connect(PPushButtonTelemetry, SIGNAL(clicked()), GetPMainWnd(), SLOT(SlotSwitchToTelemetry()));

  return rectReadinessStart;
}
//--------------------------------------------------------------------------------------------
void MReadiness::CreateListWidget(const char* nameList, QListWidget*& pListWidget, QWidget* pParent, QRect rectList,
                                          QList<QString>* pListNames)
{
  QRect rect;  rect.setRect(rectList.left()+18,rectList.top()-20, 80,16);
/*
  QLineEdit* pLineEditName = new QLineEdit(pParent);
  pLineEditName->setObjectName(QStringLiteral("LineEditName"));
  pLineEditName->setGeometry(rect);
  pLineEditName->setFrame(false);
  pLineEditName->setReadOnly(true);
  pLineEditName->setStyleSheet(QLatin1String("background: transparent;"));
  pLineEditName->setText(nameList);
  pLineEditName->setTextInteractionFlags(Qt::NoTextInteraction);
*/
  QLabel* pNameList = new QLabel(pParent);
//  pNameList->setObjectName(QStringLiteral("NameList"));
  pNameList->setGeometry(rect);
  pNameList->setText(QApplication::translate("MainWindow", nameList, 0));

  pListWidget = new QListWidget(pParent);
//  pListWidget->setObjectName(QStringLiteral("listWidget"));
  pListWidget->setGeometry(rectList);
  pListWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
  pListWidget->setResizeMode(QListView::Adjust);
  pListWidget->setFrameShape(QFrame::WinPanel);
  pListWidget->setFrameShadow(QFrame::Sunken);
//  pListWidgetEngines->setFocusPolicy(Qt::NoFocus);
//  pListWidgetEngines->setSelectionRectVisible(false);
  pListWidget->setSelectionMode(QAbstractItemView::NoSelection);

  QListWidgetItem* pItem;
  int count = pListNames->count();
  for(int i = 0; i < count; i++) {
    pItem = new QListWidgetItem(QIcon(QString::fromUtf8(":/StartCircleEmpty.png")), (*pListNames)[i], pListWidget);
//    pListWidget->addItem(pItem);
   }
}
//--------------------------------------------------------------------------------------------
/*
void MReadiness::AddReadinessStartListItem(QListWidget* pListWidget, QList<QString>* pListNamesDevice)
{
  QListWidgetItem* pItem;
  int count = pListNamesDevice->count();
  for(int i = 0; i < count; i++) {
    pItem = new QListWidgetItem(QIcon(QString::fromUtf8("StartCircleEmpty.png")), (*pListNamesDevice)[i], pListWidget);
//    pListWidget->addItem(pItem);
   }
}
*/
//--------------------------------------------------------------------------------------------
void MReadiness::SlotStart()
{
//QMessageBox msgBox;  msgBox.setText("void MReadiness::Start()");  msgBox.exec();

  PPushButtonStart->setEnabled(false);
//  PPushButtonStart->setDown(true);
  PPushButtonTelemetry->setEnabled(false);

//  GetPMainWnd()->GetPArduinoConnector()->SetTypeModeReadiness();
  emit SignalSetTypeModeReadiness();

  BResultTests = true;
  ITestChannel = -1;

  for(int i = 0; i < ListReadinessTestChannels.count(); i++) {
    ListReadinessTestChannels[i]->InitState();
    GetListWidgetItem(ListReadinessTestChannels[i]->GetNameChannel())->setIcon(QIcon(QString::fromUtf8(":/StartCircleEmpty.png")));
  }

  StartNextTestChannel();
}
//--------------------------------------------------------------------------------------------
void MReadiness::StartNextTestChannel()
{
  ITestChannel += 1;

//  QListWidgetItem* pItem;
//  int count = ListReadinessTestChannels.count();
  if(ITestChannel < ListReadinessTestChannels.count()) {
//    pItem = GetListWidgetItem(ListReadinessTestChannels[ITestChannel]->GetNameChannel());
//    if(ListReadinessTestChannels[ITestChannel]->Test()) {

//QString s; s.sprintf("ITestChannel = %d\nListReadinessTestChannels.count() = %d", ITestChannel,ListReadinessTestChannels.count());
//QMessageBox msgBox;  msgBox.setText(s);  msgBox.exec();
    ListReadinessTestChannels[ITestChannel]->Test();
/*
      ListReadinessTestChannels[i]->TestPassed();
      pItem->setIcon(QIcon(QString::fromUtf8("StartPassed.png")));
    }
    else {
      ListReadinessTestChannels[i]->TestNotPassed();
      pItem->setIcon(QIcon(QString::fromUtf8("StartNotPassed.png")));
      QMessageBox msgBox(QMessageBox::Critical, SMessageBoxTitle, "=====  TROUBLE!  =====");   msgBox.exec();
      break;
    }
*/
  }
  else {
    PPushButtonStart->setEnabled(true);
//PPushButtonTelemetry->setEnabled(BResultTests);
    PPushButtonTelemetry->setEnabled(true);
  }
}
//--------------------------------------------------------------------------------------------
void MReadiness::SlotResultTestChannel(bool bResult)
{
  BResultTests &= bResult;

  QListWidgetItem* pItem = GetListWidgetItem(ListReadinessTestChannels[ITestChannel]->GetNameChannel());
  if(bResult) {
//      ListReadinessTestChannels[i]->TestPassed();
    pItem->setIcon(QIcon(QString::fromUtf8(":/StartPassed.png")));
  }
  else {
//      ListReadinessTestChannels[i]->TestNotPassed();
    pItem->setIcon(QIcon(QString::fromUtf8(":/StartNotPassed.png")));
//      QMessageBox msgBox(QMessageBox::Critical, SMessageBoxTitle, "=====  TROUBLE!  =====");   msgBox.exec();
//      break;
  }
//QMessageBox msgBox(QMessageBox::Critical, SMessageBoxTitle, "=====  TROUBLE!  =====");   msgBox.exec();
  StartNextTestChannel();
}
//--------------------------------------------------------------------------------------------
QListWidgetItem* MReadiness::GetListWidgetItem(QString nameItem)
{
  QListWidgetItem* pItem;
  pItem = GetListWidgetItem(PListWidgetEngines, nameItem);
  if(pItem != NULL)  return pItem;
  pItem = GetListWidgetItem(PListWidgetSensors, nameItem);
  if(pItem != NULL)  return pItem;
  pItem = GetListWidgetItem(PListWidgetServoMotors, nameItem);
  if(pItem == NULL) {
    QMessageBox msgBox(QMessageBox::Warning, SMessageBoxTitle, "GetListWidgetItem == NULL");   msgBox.exec();
  }
  return pItem;
}
//--------------------------------------------------------------------------------------------
QListWidgetItem* MReadiness::GetListWidgetItem(QListWidget* pListWidget, QString nameItem)
{
  QListWidgetItem* pItem;
  int count = pListWidget->count();
  for(int i = 0; i < count; i++) {
    pItem = pListWidget->item(i);
    if(pItem->text() == nameItem) return pItem;
   }
  return NULL;
}
//--------------------------------------------------------------------------------------------
