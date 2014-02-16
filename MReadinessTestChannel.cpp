#include "MReadinessTestChannel.h"
#include "funcs.h"

#include <QMessageBox>
//#include <QTextEdit>

//  #include <QThread>
//  #include <QApplication>

//#include "MArduino.h"

//#include <QThread>

//============================================================================================
//MReadinessTestChannel::MReadinessTestChannel(QWidget* parent, const int yTopChannel, const char* nameChannel, const char* namePixmapFileChannel,
//                                             QString* pTextTest, QList<QString>* pListParamsNameTest, QList<int>* pListParamsRangeTest)
MReadinessTestChannel::MReadinessTestChannel(QWidget* pParent, const int yTopChannel, // const char* namePixmapFileChannel,
//                                             QString* pTextTest, QList<QString>* pListParamsChannel)
                                             QList<QString>* pListParamsChannel)
                      : QWidget(pParent), PListParamsChannel(pListParamsChannel)
{

//  TextTest = *pTextTest;

  SColorNeutral = QString("rgb(255,200,0)");
  SColorQuery = QString("rgb(255,225,0)");

  SColorReady = QString("rgb(0,255,0)");
  SColorUnready = QString("rgb(255,0,0)");

  int xLeft = 10;

  int widthLabelPixmapChannel = 101;   int heightLabelPixmapChannel = 71;
  int widthProgressBarTest = 91;       int heightProgressBarTest = 6;
  int widthTextEditTest = 121;         int heightTextEditTest = 75;
  int widthProgressBarStatus = 91;     int heightProgressBarStatus = 6;
  int widthLabelStatus = 121;          int heightLabelStatus = 41;

  QRect rect;

//== 2):

  PProgressBarTest1 = new QProgressBar(pParent);
//  PProgressBarTest1->setObjectName(QStringLiteral("ProgressBarTest_1"));
  PProgressBarTest1->setEnabled(true);
  rect = QRect(xLeft, yTopChannel+49, widthLabelPixmapChannel + widthProgressBarTest, heightProgressBarTest);
  PProgressBarTest1->setGeometry(rect);
  PProgressBarTest1->setMinimum(0);
  PProgressBarTest1->setTextVisible(false);
  RectChannel = rect;

//  PProgressBarTest1->setMaximum(100);  PProgressBarTest1->setValue(100);
//  PProgressBarTest1->setStyleSheet("QProgressBar::chunk { background-color: "+SColorNeutral+"; }");


//  pProgressBarTest1->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\ncolor: rgb(255, 255, 0);"));
//+  pProgressBarTest1->setStyleSheet(pProgressBarTest1->property("defaultStyleSheet").toString() +
//+                                                               " QProgressBar::chunk { background-color: red;\nwidth: 40px; }");
//+  pProgressBarTest1->setStyleSheet("QProgressBar::chunk { background-color: red;\n width: 20px;\n margin: 1.5px; }");

//  PProgressBarTest1->setStyleSheet("QProgressBar::chunk { background-color: rgb(255,0,0); }");

//PProgressBarTest1->setStyleSheet("QProgressBar{"
//                           "color:rgba(0,0,0);"
//                           "background-color: rgb(255,0,0);}");


/*
  PProgressBarTest1->setStyleSheet("QProgressBar::chunk { background-color: qlineargradient(spread:pad, x1: 0, y1: 0.5, x2: 1, y2: 0.5,"
//  " stop: 0 rgb(127,127,127), stop: 0.2 rgb(255,255,0), stop: 0.4 rgb(255,0,0), stop: 0.6 rgb(0,255,0), stop: 0.8 rgb(255,255,0), stop: 1 rgb(127,127,127));"
  " stop: 0 rgb(127,127,127), stop: 0.2 "+SColorQuery+", stop: 0.8 "+SColorQuery+", stop: 1 rgb(127,127,127));"
//  " background-color: qlineargradient(x1: 0.5, y1: 0, x2: 0.5, y2: 1,"
//  " stop: 0 rgb(255,0,0), stop: 1 rgb(0,0,255));"
  " width: 70px; margin: 1.5px }");
*/
/*
pProgressBarTest1->setStyleSheet("QProgressBar{"
                           "border: 1px solid transparent;"
                           "text-align: center;"
                           "color:rgba(0,0,0,100);"
                           "border-radius: 5px;"
                           "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(182, 182, 182, 100), stop:1 rgba(209, 209, 209, 100));"
                               "}"
                           "QProgressBar::chunk{"
                           "background-color: rgba(0,255,0,100);"
                           "}");
*/
//  pProgressBarTest1->setStyleSheet("QProgressBar::chunk:vertical {background: qlineargradient(spread:pad, x1: 0.5, y1: 0, x2: 0.5, y2: 1,"
//  " stop: 0 rgb(127,0,0), stop: 0.2 rgb(255,255,0), stop: 0.8 rgb(255,255,0), stop: 1 rgb(127,127,127));"
//  " width: 40px; margin: 0.5px }");

//  pProgressBarTest1->setStyleSheet("QProgressBar::chunk:horizontal {color : red;}");



//pProgressBarTest1->setStyleSheet("QProgressBar::chunk {" //::indeterminate {"
//    "background: qlineargradient(x1: 0, y1: 0.5, x2: 1, y2: 0.5, stop: 0 white, stop: 1 red);}");


//  pProgressBarTest1->setStyleSheet("QProgressBar::chunk { color: red; }");
//  pParent->setStyleSheet("QProgressBar { color: red; }");
//  pProgressBarTest1->setStyleSheet(QLatin1String("background-color: rgb(255, 0, 0);"));

//  pProgressBarTest1->setForegroundRole(QPalette::Midlight);

//QMessageBox msgBox(QMessageBox::Warning, pProgressBarTest1->format(), "pProgressBarTest1->format()");   msgBox.exec();
//QMessageBox msgBox(QMessageBox::Warning, "pProgressBarTest1->format()",pProgressBarTest1->property("defaultStyleSheet").toString());   msgBox.exec();

//pProgressBarTest1->setStyleSheet("QProgressBar::chunk:horizontal {"
// "background: qlineargradient(x1: 0, y1: 0.5, x2: 10, y2: 0.5, stop: 0 green, stop: 1 white);"
// "margin-right: 2px;  width: 25px; }");

//-

  PProgressBarTest2 = new QProgressBar(pParent);
//  PProgressBarTest2->setObjectName(QStringLiteral("ProgressBarTest_2"));
  PProgressBarTest2->setEnabled(true);
  rect = QRect(xLeft, yTopChannel+74, widthLabelPixmapChannel + widthProgressBarTest, heightProgressBarTest);
  PProgressBarTest2->setGeometry(rect);
  PProgressBarTest2->setMinimum(0);
  PProgressBarTest2->setTextVisible(false);
  RectChannel |= rect;

//  PProgressBarTest2->setMaximum(100);  PProgressBarTest2->setValue(100);
//  PProgressBarTest2->setStyleSheet("QProgressBar::chunk { background-color: "+SColorNeutral+"; }");

//== 1):

  QLineEdit* pLineEditNameChannel = new QLineEdit(pParent);
//  pLineEditNameChannel->setObjectName(QStringLiteral("LineEditNameChannel"));
  rect = QRect(xLeft, yTopChannel+4, widthLabelPixmapChannel, 20);
  pLineEditNameChannel->setGeometry(rect);
  pLineEditNameChannel->setFrame(false);
  pLineEditNameChannel->setReadOnly(true);
  pLineEditNameChannel->setStyleSheet(QLatin1String("background: transparent;"));
//  pLineEditNameChannel->setAlignment(Qt::AlignCenter);
  pLineEditNameChannel->setText((*PListParamsChannel)[0]); //nameChannel);
//  PLineEditNameChannel->setText(PListParamsChannel->takeFirst()); //nameChannel);
//  PListParamsChannel->removeFirst();
  RectChannel |= rect;

  QLabel* pLabelPixmapChannel = new QLabel(pParent);
//  pLabelPixmapChannel->setObjectName(QStringLiteral("LabelPixmapChannel"));
  rect = QRect(xLeft, yTopChannel+24, widthLabelPixmapChannel, heightLabelPixmapChannel);
  pLabelPixmapChannel->setGeometry(rect);
  pLabelPixmapChannel->setScaledContents(true);
  pLabelPixmapChannel->setPixmap(QPixmap((*PListParamsChannel)[1]));
  RectChannel |= rect;


//== 4):

  xLeft += widthLabelPixmapChannel + widthProgressBarTest;

  PProgressBarStatus = new QProgressBar(pParent);
//  PProgressBarStatus->setObjectName(QStringLiteral("ProgressBarStatus"));
  PProgressBarStatus->setEnabled(true);
  rect = QRect(xLeft, yTopChannel+62, widthTextEditTest+widthProgressBarStatus, heightProgressBarStatus);
  PProgressBarStatus->setGeometry(rect);
  PProgressBarStatus->setMinimum(0);
  PProgressBarStatus->setTextVisible(false);
  RectChannel |= rect;

//  PProgressBarStatus->setMaximum(100);  PProgressBarStatus->setValue(100);
//  PProgressBarStatus->setInvertedAppearance(true);
//  PProgressBarStatus->setStyleSheet("QProgressBar::chunk { background-color: "+SColorNeutral+"; }");

//== 3):

  QLineEdit* pLineEditTest = new QLineEdit(pParent);
//  pLineEditTest->setObjectName(QStringLiteral("LineEditTest"));
  rect = QRect(xLeft, yTopChannel, widthTextEditTest, 20);
  pLineEditTest->setGeometry(rect);
  pLineEditTest->setFrame(false);
  pLineEditTest->setReadOnly(true);
  pLineEditTest->setStyleSheet(QLatin1String("background: transparent;"));
  pLineEditTest->setAlignment(Qt::AlignCenter);
  pLineEditTest->setText(QStringLiteral("Test"));
  RectChannel |= rect;

//  QTextEdit* pTextEditTest = new QTextEdit(pParent);
  PTextEditTest = new QTextEdit(pParent);
//  PTextEditTest->setObjectName(QStringLiteral("TextEditTest"));
  rect = QRect(xLeft, yTopChannel+20, widthTextEditTest, heightTextEditTest);
  PTextEditTest->setGeometry(rect);
  PTextEditTest->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\ncolor: rgb(85, 255, 255);"));
  PTextEditTest->setTabStopWidth(8); // By default, this property contains a value of 80 pixels.
  PTextEditTest->setReadOnly(true);
  RectChannel |= rect;

//  pTextEditTest->setText(*pTextTest);

  PSyntaxHighlighterParamsTest = new MSyntaxHighlighterParamsTest(PTextEditTest->document(), pListParamsChannel,
                                            GetPMainWnd()->GetIFirstItemListParamsReadiness(), GetPMainWnd()->GetDeltaNItemListParamsReadiness());

//== 5):

  xLeft += widthTextEditTest + widthProgressBarStatus;

  QLineEdit* pLineEditStatus = new QLineEdit(pParent);
//  pLineEditStatus->setObjectName(QStringLiteral("LineEditStatus"));
  rect = QRect(xLeft, yTopChannel+24, widthLabelStatus, 20);
  pLineEditStatus->setGeometry(rect);
  pLineEditStatus->setFrame(false);
  pLineEditStatus->setReadOnly(true);
  pLineEditStatus->setStyleSheet(QLatin1String("background: transparent;"));
  pLineEditStatus->setAlignment(Qt::AlignCenter);
  pLineEditStatus->setText(QStringLiteral("Status"));
  RectChannel |= rect;

//  QTextEdit* pTextEditStatus = new QTextEdit(pParent);
  PLabelStatus = new QLabel(pParent);
  PLabelStatus->setObjectName(QStringLiteral("LabelStatus"));
  rect = QRect(xLeft, yTopChannel+44, widthLabelStatus, heightLabelStatus);
  PLabelStatus->setGeometry(rect);
//  pTextEditStatus->setTextBackgroundColor(QColor(255,0,0, 0));
  PLabelStatus->setAlignment(Qt::AlignCenter);
//  PLabelStatus->setFrameStyle(QFrame::Box); //QFrame::Panel | QFrame::Raised);
  PLabelStatus->setFrameShape(QFrame::StyledPanel);
  PLabelStatus->setFrameShadow(QFrame::Raised);
  RectChannel |= rect;

//  PLabelStatus->setStyleSheet(QLatin1String("background-color: rgb(255,255,0);\ncolor: rgb(0,0,0);"));

//== 6):

  xLeft += widthLabelStatus + 10;
  PLabelStatusPixmap = new QLabel(pParent);
//  PLabelStatusPixmap->setObjectName(QStringLiteral("LabelStatusPixmap"));
  rect = QRect(xLeft, yTopChannel+52, 25, 25);
  PLabelStatusPixmap->setGeometry(rect);
//-  pLabelStatus->setStyleSheet(QLatin1String("background: transparent;"));
//  pLabelStatus->setPixmap(QPixmap(QString::fromUtf8("NotPassed.ico")));
//  pLabelStatus->setPixmap(QPixmap(QString::fromUtf8("Passed.ico")));
  RectChannel |= rect;

//PLabelStatusPixmap->setPixmap(QPixmap(QString::fromUtf8("TestTransparent.ico")));

  InitState();

//  connect(this, &MReadinessTestChannel::SignalStartTest, GetPMainWnd()->GetPArduino(), &MArduino::SlotStartTest);
//  connect(GetPMainWnd()->GetPArduino(), &MArduino::SignalResultTest, this, &MReadinessTestChannel::SlotResultTest);
}
//--------------------------------------------------------------------------------------------
MReadinessTestChannel::~MReadinessTestChannel()
{
  PSyntaxHighlighterParamsTest->setDocument(0);  delete PSyntaxHighlighterParamsTest;
//ThreadTest.quit();  ThreadTest.wait();
}
//--------------------------------------------------------------------------------------------
void MReadinessTestChannel::InitState()
{
  PProgressBarTest1->setMaximum(100);  PProgressBarTest1->setValue(100);
  PProgressBarTest1->setStyleSheet("QProgressBar::chunk { background-color: "+SColorNeutral+"; }");

  PProgressBarTest2->setMaximum(100);  PProgressBarTest2->setValue(100);
  PProgressBarTest2->setStyleSheet("QProgressBar::chunk { background-color: "+SColorNeutral+"; }");


  PSyntaxHighlighterParamsTest->InitBegin();
//  PTextEditTest->setText(TextTest);
  PTextEditTest->setText((*PListParamsChannel)[2]);


  PProgressBarStatus->setMaximum(100);  PProgressBarStatus->setValue(100);
//  PProgressBarStatus->setInvertedAppearance(true);
  PProgressBarStatus->setStyleSheet("QProgressBar::chunk { background-color: "+SColorNeutral+"; }");

//  PLabelStatus->setStyleSheet(QLatin1String("background-color: rgb(255,255,0);\ncolor: rgb(0,0,0);"));
  PLabelStatus->setStyleSheet(QLatin1String("background-color: transparent;"));
  PLabelStatus->setText("");

  PLabelStatusPixmap->setPixmap(QPixmap());//(QString::fromUtf8("Transparent.ico")));
}
//--------------------------------------------------------------------------------------------
void MReadinessTestChannel::Test()
{
/*
//  PThreadTest = new MThreadTest(this);
  connect(this, SIGNAL(SignalStartTest(int, qreal)), &ThreadTest, SLOT(SlotStartTest(int, qreal)));
  connect(&ThreadTest, SIGNAL(SignalResultTest(qreal)), this, SLOT(SlotResultTest(qreal)));
  ThreadTest.start();//  PParent->moveToThread(&thread);
//  PParent->moveToThread(QApplication::instance()->thread());
//  moveToThread(QApplication::instance()->thread());
  emit SignalStartTest(1, 10.0);
*/
/*+
  MArduino* pArduino = new MArduino;
  pArduino->moveToThread(&ThreadTest);
  connect(&ThreadTest, &QThread::finished, pArduino, &QObject::deleteLater);
  connect(this, &MReadinessTestChannel::SignalStartTest, pArduino, &MArduino::SlotStartTest);
  connect(pArduino, &MArduino::SignalResultTest, this, &MReadinessTestChannel::SlotResultTest);
  ThreadTest.start(); // ThreadTest.wait(5000);
*/
//  GetPMainWnd()->GetPArduino()->moveToThread(GetPMainWnd()->GetPThreadArduino());
//  GetPMainWnd()->GetPThreadArduino()->start();

//  MArduino* pArduino = new MArduino;   GetPMainWnd()->SetPArduino(pArduino);

/*+
  GetPMainWnd()->CreatePArduino();
  GetPMainWnd()->GetPArduino()->moveToThread(GetPMainWnd()->GetPThreadArduino());
  connect(GetPMainWnd()->GetPThreadArduino(), &QThread::finished, GetPMainWnd()->GetPArduino(), &QObject::deleteLater);
  connect(this, &MReadinessTestChannel::SignalStartTest, GetPMainWnd()->GetPArduino(), &MArduino::SlotStartTest);
  connect(GetPMainWnd()->GetPArduino(), &MArduino::SignalResultTest, this, &MReadinessTestChannel::SlotResultTest);
  GetPMainWnd()->GetPThreadArduino()->start(); // ThreadTest.wait(5000);
*/

//  GetPMainWnd()->CreateArduinoObject(this, SIGNAL(SignalTest(QString*,QString*,QString*,QString*)), SLOT(SlotTest(QString*,QString*,QString*,QString*)),
//                                           SIGNAL(SignalResultTest(float)), SLOT(SlotResultTest(float)));

//  connect(this, SIGNAL(SignalTest(QString*,QString*,QString*,QString*)), GetPMainWnd()->GetPArduinoConnector(), SLOT(SlotTest(QString*,QString*,QString*,QString*)));
  connect(this, SIGNAL(SignalGetReadinessTestValue(QString*,QString*,QString*,QString*)), GetPMainWnd()->GetPArduinoConnector(), SLOT(SlotGetReadinessTestValue(QString*,QString*,QString*,QString*)));

//  connect(GetPMainWnd()->GetPArduinoConnector(), SIGNAL(SignalResultTest(float)), this, SLOT(SlotResultTest(float)));
  connect(GetPMainWnd()->GetPArduinoConnector(), SIGNAL(SignalTakeReadinessTestValue(float)), this, SLOT(SlotTakeReadinessTestValue(float)));

  BResult = true;
  NTestInChannel = 1;
  IListItem = GetPMainWnd()->GetIFirstItemListParamsReadiness();
  PosParam = 0;

  StartTest(NTestInChannel);

//  return false;
//  return true;
}
//--------------------------------------------------------------------------------------------
void MReadinessTestChannel::StartTest(int nTestInChannel)
{
  if(nTestInChannel == 1) {
    PProgressBarTest1->setStyleSheet("QProgressBar::chunk { background-color: qlineargradient(spread:pad, x1: 0.0, y1: 0.5, x2: 1.0, y2: 0.5,"
    " stop: 0 rgb(127,127,127), stop: 0.1 "+SColorQuery+", stop: 0.9 "+SColorQuery+", stop: 1 rgb(127,127,127));"
    " width: 70.0px; margin: 1.5px }");
    PProgressBarTest1->setMaximum(0);
  }
  else if(nTestInChannel == 2) {
    PProgressBarTest2->setStyleSheet("QProgressBar::chunk { background-color: qlineargradient(spread:pad, x1: 0.0, y1: 0.5, x2: 1.0, y2: 0.5,"
    " stop: 0 rgb(127,127,127), stop: 0.1 "+SColorQuery+", stop: 0.9 "+SColorQuery+", stop: 1 rgb(127,127,127));"
    " width: 70.0px; margin: 1.5px }");
    PProgressBarTest2->setMaximum(0);
  }
//                  &sNameChannel              &sInputTestName                      &sInputTestValue                     &sOutputTestName
//  emit SignalTest(&(*PListParamsChannel)[0], &(*PListParamsChannel)[IListItem-3], &(*PListParamsChannel)[IListItem-2], &(*PListParamsChannel)[IListItem-1]);
//                                 &sNameChannel              &sInputTestName                      &sInputTestValue                     &sOutputTestName
  emit SignalGetReadinessTestValue(&(*PListParamsChannel)[0], &(*PListParamsChannel)[IListItem-3], &(*PListParamsChannel)[IListItem-2], &(*PListParamsChannel)[IListItem-1]);
}
//--------------------------------------------------------------------------------------------
//void MReadinessTestChannel::SlotResultTest(float result)
void MReadinessTestChannel::SlotTakeReadinessTestValue(float result)
{
//  QMessageBox msgBox; // msgBox.setText((*PListParamsChannel)[2]);   msgBox.exec();
//QMessageBox msgBox; msgBox.setText("1");   msgBox.exec();

  if(IListItem < PListParamsChannel->count()) {
//msgBox.setText("2");   msgBox.exec();
    QString s;   QString sTextTest;  QString sParam;
/*
    int countLimits;
s = "countLimits = " + (*PListParamsChannel)[IListItem];
    countLimits = (*PListParamsChannel)[IListItem].toInt();
    if(countLimits == 1) {
      s += "\nvalue:  " + (*PListParamsChannel)[IListItem+1];
      s += "\n\nDO !!!";
      IListItem += 3;
QMessageBox msgBox(QMessageBox::Critical, "void MReadinessTestChannel::SlotResultTest(qreal result)", s);   msgBox.exec();
    }
    else if(countLimits == 2) {
*/
      s.sprintf("%.1f",result);
      sTextTest = PTextEditTest->document()->toPlainText(); //> >plainText();//  (*PListParamsChannel)[2];
      sParam = (*PListParamsChannel)[IListItem];
      PosParam = sTextTest.indexOf(sParam, PosParam, Qt::CaseSensitive) + sParam.length();
      sTextTest.insert(PosParam,s);
      PSyntaxHighlighterParamsTest->InitBegin();
      PTextEditTest->setText(sTextTest);

      if((*PListParamsChannel)[IListItem+1].toFloat() <= result && result <= (*PListParamsChannel)[IListItem+2].toFloat()) {
        TestPassed(NTestInChannel);
        BResult &= true;
      }
      else {
        TestNotPassed(NTestInChannel);
        BResult &= false;
      }
      NTestInChannel += 1;
      IListItem += GetPMainWnd()->GetDeltaNItemListParamsReadiness();

      if(IListItem < PListParamsChannel->count()) {
        StartTest(NTestInChannel);
//s += "\nvalues:  " + (*PListParamsChannel)[IListItem+1] + "  " + (*PListParamsChannel)[IListItem+2];
//QMessageBox msgBox; msgBox.setText(s);   msgBox.exec();
        return;
      }
 /*
    }
    else {
      s += ":   countLimits != 1 && != 2";
      IListItem += 10;
QMessageBox msgBox(QMessageBox::Critical, "void MReadinessTestChannel::SlotResultTest(qreal result)", s);   msgBox.exec();
    }
*/
  }

//+  ThreadTest.quit();    ThreadTest.wait();
//+  GetPMainWnd()->GetPThreadArduino()->quit();    GetPMainWnd()->GetPThreadArduino()->wait();

//  GetPMainWnd()->DestroyArduinoObject();
//  if(!disconnect(this, SIGNAL(SignalTest(QString*,QString*,QString*,QString*)), GetPMainWnd()->GetPArduinoConnector(), SLOT(SlotTest(QString*,QString*,QString*,QString*)))) {
  if(!disconnect(this, SIGNAL(SignalGetReadinessTestValue(QString*,QString*,QString*,QString*)), GetPMainWnd()->GetPArduinoConnector(), SLOT(SlotGetReadinessTestValue(QString*,QString*,QString*,QString*)))) {
    QMessageBox msgBox(QMessageBox::Warning, "void MReadinessTestChannel::SlotResultTest(float result)",
                       "Problem::\n\ndisconnect(this, SIGNAL(SignalGetReadinessTestValue(QString*,QString*,QString*,QString*)), GetPMainWnd()->GetPArduino(), SLOT(SlotGetReadinessTestValue(QString*,QString*,QString*,QString*))) == false");
      msgBox.exec();
  }
//  if(!disconnect(GetPMainWnd()->GetPArduinoConnector(), SIGNAL(SignalResultTest(float)), this, SLOT(SlotResultTest(float)))) {
  if(!disconnect(GetPMainWnd()->GetPArduinoConnector(), SIGNAL(SignalTakeReadinessTestValue(float)), this, SLOT(SlotTakeReadinessTestValue(float)))) {
    QMessageBox msgBox(QMessageBox::Warning, "void MReadinessTestChannel::SlotResultTest(float result)",
                       "Problem::\n\ndisconnect(GetPMainWnd()->GetPArduino(), SIGNAL(SignalTakeReadinessTestValue(float)), this, SLOT(SlotTakeReadinessTestValue(float))) == false");
      msgBox.exec();
  }

//  GetPMainWnd()->GetPArduino()->moveToThread(QApplication::instance()->thread());
//  GetPMainWnd()->GetPThreadArduino()->quit();    GetPMainWnd()->GetPThreadArduino()->wait();

  emit SignalResultTestChannel(BResult);

//  disconnect(this, &ThreadTest);   disconnect(&ThreadTest, this);
//  QObject::disconnect(this, SIGNAL(SignalStartTest(int, qreal)), &ThreadTest, SLOT(SlotStartTest(int, qreal)));
//  QObject::disconnect(&ThreadTest, SIGNAL(SignalResultTest(qreal)), this, SLOT(SlotResultTest(qreal)));
//  ThreadTest.quit();  ThreadTest.wait();
}
//--------------------------------------------------------------------------------------------
void MReadinessTestChannel::TestPassed(int nTestInChannel)
{
  if(nTestInChannel == 1) {
    PProgressBarTest1->setStyleSheet("QProgressBar::chunk { background-color: rgb(0,255,0);}");
    PProgressBarTest1->setMaximum(100);  PProgressBarTest1->setValue(100);
  }
  if(nTestInChannel == 2) {
    PProgressBarTest2->setStyleSheet("QProgressBar::chunk { background-color: rgb(0,255,0);}");
    PProgressBarTest2->setMaximum(100);  PProgressBarTest2->setValue(100);

    if(BResult) {
      PProgressBarStatus->setStyleSheet("QProgressBar::chunk { background-color: rgb(0,255,0);}");
//      PProgressBarStatus->setMaximum(100);  PProgressBarStatus->setValue(100);

      PLabelStatus->setStyleSheet(QLatin1String("background-color: rgb(0,255,0);\ncolor: rgb(0,0,0);"));
      PLabelStatus->setText("Ready");

      PLabelStatusPixmap->setPixmap(QPixmap(QString::fromUtf8(":/TestPassed.ico")));
    }
    else {
      PProgressBarStatus->setStyleSheet("QProgressBar::chunk { background-color: rgb(255,0,0);}");

      PLabelStatus->setStyleSheet(QLatin1String("background-color: rgb(255,0,0);\ncolor: rgb(0,0,0);"));
      PLabelStatus->setText("Unready");

      PLabelStatusPixmap->setPixmap(QPixmap(QString::fromUtf8(":/TestNotPassed.ico")));
    }
  }
}
//--------------------------------------------------------------------------------------------
void MReadinessTestChannel::TestNotPassed(int nTestInChannel)
{
  if(nTestInChannel == 1) {
    PProgressBarTest1->setStyleSheet("QProgressBar::chunk { background-color: rgb(255,0,0);}");
    PProgressBarTest1->setMaximum(100);  PProgressBarTest1->setValue(100);
  }
  if(nTestInChannel == 2) {
    PProgressBarTest2->setStyleSheet("QProgressBar::chunk { background-color: rgb(255,0,0);}");
    PProgressBarTest2->setMaximum(100);  PProgressBarTest2->setValue(100);

    PProgressBarStatus->setStyleSheet("QProgressBar::chunk { background-color: rgb(255,0,0);}");

    PLabelStatus->setStyleSheet(QLatin1String("background-color: rgb(255,0,0);\ncolor: rgb(0,0,0);"));
    PLabelStatus->setText("Unready");
    PLabelStatusPixmap->setPixmap(QPixmap(QString::fromUtf8(":/TestNotPassed.ico")));
  }
}
//--------------------------------------------------------------------------------------------
