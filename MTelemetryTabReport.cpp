#include "MTelemetryTabReport.h"
#include "MTelemetry.h"
//#include "MTelemetryTabWidgetReports.h"
//#include "MLabelCloseTab.h"
//#include "MTelemetryTabWidgetChannels.h"
#include "MTelemetryTabChannel.h"
#include "funcs.h"
//#include "constants.h"

#include <QFileDialog>
//#include <QTabWidget>
//#include <QLabel>
#include <QtGlobal>
#include <QMessageBox>
//  #include <QApplication>


extern const char* ReportFileVersion;

//============================================================================================
MTelemetryTabReport::MTelemetryTabReport(QWidget* parent) //, MTelemetryTabWidgetChannels *pTabWidgetChannels) :
//                   : QWidget(parent) //, PTabWidgetChannels(pTabWidgetChannels)
                   : QScrollArea(parent)
{
//  PTabWidgetReports = qobject_cast<MTelemetryTabWidgetReports*>(parent);
//  Q_ASSERT(PTabWidgetReports != NULL); //   Q_CHECK_PTR(pTabWidgetStates);
//  return PTabWidgetStates->GetPTabWidgetChannels();
//  Init();
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabReport::AddPlot(MPlot* pPlot)
{
  ListPlots << pPlot;
}
//--------------------------------------------------------------------------------------------
/*
bool MTelemetryTabReport::event(QEvent* event)
{
  bool b = QWidget::event(event); //catch different events
//--
  if(event->type() == QEvent::Polish) {//Polish is caught
//    Init();
  }
  return b;
}
*/
//--------------------------------------------------------------------------------------------
/*
MTelemetryTabWidgetChannels* MTelemetryTabReport::GetPTabWidgetChannels()
{
//  MTelemetryTabWidgetStates* pTabWidgetStates = qobject_cast<MTelemetryTabWidgetStates*>(parentWidget());
//  Q_ASSERT(pTabWidgetStates != NULL); //   Q_CHECK_PTR(pTabWidgetStates);
  return PTabWidgetStates->GetPTabWidgetChannels();
}
*/
//--------------------------------------------------------------------------------------------
void MTelemetryTabReport::Init()
{
//  MTelemetryTabChannel* pTabChannel;

//  int countParamsTelemetryChannels = GetPMainWnd()->GetPListParamsTelemetryChannels()->count();
  int countParamsTelemetryChannels = 0;
  QList<QString>        listNamesChannels;
  QList<int>            listCountPlotsInChannels;
  QList<QList<QString>> listNameParamsInChannels;
/*
  MTelemetryTabWidgetReports* pTabWidgetReports = qobject_cast<MTelemetryTabWidgetReports*>(parent());
  Q_ASSERT(pTabWidgetReports != NULL); //   Q_CHECK_PTR(pTabWidgetStates);
//  return PTabWidgetStates->GetPTabWidgetChannels();
*/
  MTelemetryTabWidgetChannels* pTabWidget;

  pTabWidget = GetPMainWnd()->GetPTelemetry()->GetPTabWidgetStates();
  FormListsParams(pTabWidget, countParamsTelemetryChannels, listNamesChannels, listCountPlotsInChannels, listNameParamsInChannels);

  pTabWidget = GetPMainWnd()->GetPTelemetry()->GetPTabWidgetChannels();
  FormListsParams(pTabWidget, countParamsTelemetryChannels, listNamesChannels, listCountPlotsInChannels, listNameParamsInChannels);

//  QRect rectReport = FillTabReport(pTabReport, countParamsTelemetryChannels, listNamesChannels, listCountPlotsInChannels, listNameParamsInChannels, true);//isAssignCorrespondingReportPlot)
  QRect rectReport = FillTabReport(countParamsTelemetryChannels, listNamesChannels, listCountPlotsInChannels, listNameParamsInChannels, true);//isAssignCorrespondingReportPlot)
//      rectTelemetryStates = rectReport;

//  pScrollAreaReportContents->setMinimumSize(rectReport.right()+3,rectReport.bottom()+3);
//  pScrollAreaReport->setWidget(pScrollAreaReportContents);

//setGeometry(0,0, rectReport.width()+60,321+60);
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabReport::FormListsParams(MTelemetryTabWidgetChannels* pTabWidget, int& countParamsTelemetryChannels,
                                          QList<QString>& listNamesChannels, QList<int>& listCountPlotsInChannels,
                                          QList<QList<QString>>& listNameParamsInChannels)
{
//  int countParamsTelemetryChannels = pTabWidgetReports->GetPTabWidgetChannels()->count();
  int countParams = pTabWidget->count();
  countParamsTelemetryChannels += countParams;

  MTelemetryTabChannel* pTabChannel;

  QString sNameChannel;           QString sNameParamChannel;
  QString sMinParamYNormalValue;  QString sMaxParamYNormalValue;
  QList<QString> list; //  int m;

//  for(int n = 0; n < countParamsTelemetryChannels; n++) {
  for(int n = 0; n < countParams; n++) {
//    pTabChannel = qobject_cast<MTelemetryTabChannel*>(pTabWidgetReports->GetPTabWidgetChannels()->widget(n));
    pTabChannel = qobject_cast<MTelemetryTabChannel*>(pTabWidget->widget(n));
    Q_ASSERT(pTabChannel != NULL); //   Q_CHECK_PTR(pTabChannel);
//    sNameChannel = pTabWidgetReports->GetPTabWidgetChannels()->tabBar()->tabText(n);
//    sNameChannel = pTabWidget->tabBar()->tabText(n);
    sNameChannel = *pTabChannel->GetPNameChannel();
    listNamesChannels << sNameChannel;
    listCountPlotsInChannels << pTabChannel->GetPListPlots()->count();

    for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j++) {
//      m = GetPMainWnd()->GetIFirstItemListParamsTelemetry() + j*3; //GetPMainWnd()->GetDeltaNItemListParamsTelemetry();
/*
      m = pTabChannel->GetIFirstItemListParamsTelemetry() + j*3; //GetPMainWnd()->GetDeltaNItemListParamsTelemetry();
      sNameParamChannel = (*pTabChannel->GetPListParamsTelemetryChannel())[m];
      sMinParamYNormalValue = (*pTabChannel->GetPListParamsTelemetryChannel())[m+1];
      sMaxParamYNormalValue = (*pTabChannel->GetPListParamsTelemetryChannel())[m+2];
*/
      sNameParamChannel = *pTabChannel->GetPNameParamInChannel(j);
      sMinParamYNormalValue = *pTabChannel->GetPStringMinNormalValue(j);
      sMaxParamYNormalValue = *pTabChannel->GetPStringMaxNormalValue(j);

      list << sNameParamChannel << sMinParamYNormalValue << sMaxParamYNormalValue;
    }
    listNameParamsInChannels << list;  list.clear();
  }
}
//--------------------------------------------------------------------------------------------
QRect MTelemetryTabReport::FillTabReport(int countParamsTelemetryChannels, QList<QString>& listNamesChannels,
                                         QList<int>& listCountPlotsInChannels, QList<QList<QString>>& listNameParamsInChannels,
                                         bool isAssignCorrespondingReportPlot)
{
//  MTelemetryTabWidgetReports* pTabWidgetReports = qobject_cast<MTelemetryTabWidgetReports*>(parent());
//  Q_ASSERT(pTabWidgetReports != NULL); //   Q_CHECK_PTR(pTabWidgetStates);

/*
  QScrollArea* pScrollAreaReport = new QScrollArea(this);
  pScrollAreaReport->setObjectName(QStringLiteral("ScrollAreaReport"));
//pScrollAreaReport->setGeometry(QRect(0, 0, 611, 311));
  pScrollAreaReport->setWidgetResizable(true);//false);
*/

  QWidget* pScrollAreaReportContents = new QWidget(this);
//QWidget* pScrollAreaReportContents = this;
//  PTabWidgetStates = new MTelemetryTabWidgetStates(pScrollAreaState, PTabWidgetChannels);
//  MTelemetryTabWidgetStates* pScrollAreaStateContents = PTabWidgetStates;
  pScrollAreaReportContents->setObjectName(QStringLiteral("ScrollAreaReportContents"));
//pScrollAreaReportContents->setGeometry(QRect(0, 0, 609, 409));
//  pScrollAreaReportContents->setMinimumSize(609,109);

//  QWidget* pScrollAreaReportContents = new QWidget(pScrollAreaReportContents0);

  MTelemetryTabWidgetChannels* pTabWidgetStates = GetPMainWnd()->GetPTelemetry()->GetPTabWidgetStates();
  MTelemetryTabWidgetChannels* pTabWidgetChannels = GetPMainWnd()->GetPTelemetry()->GetPTabWidgetChannels();

  int countTabsStates = pTabWidgetStates->count();

  MTelemetryTabChannel* pTabChannel;// = NULL;

  QString sNameChannel;  QString sNameParam;
  QRect rectReport;  int yTopChannel = -5;//0;
  QLineEdit* pLineEditNameChannel;  QRect rect;
  MPlot* pPlot;   QRect rectPlot(9,10, 321,321);


  int n = 0;
//      for (int n = 0; n < GetPMainWnd()->GetPListParamsTelemetryChannels()->count(); n++) {
  while(n < countParamsTelemetryChannels) {

    yTopChannel += 10;

    pLineEditNameChannel = new QLineEdit(pScrollAreaReportContents);//this);//pTabReport);
//    pLineEditNameChannel = new QLineEdit(this);//pTabReport);
    pLineEditNameChannel->setObjectName(QStringLiteral("LineEditNameChannel"));
    rect = QRect(285, yTopChannel, 100, 20);
    pLineEditNameChannel->setGeometry(rect);
    pLineEditNameChannel->setFrame(false);
    pLineEditNameChannel->setReadOnly(true);
    pLineEditNameChannel->setStyleSheet(QLatin1String("background: transparent;"));
    pLineEditNameChannel->setAlignment(Qt::AlignCenter);
//        sNameChannel = PTabWidgetChannels->tabBar()->tabText(n);
    sNameChannel = listNamesChannels[n];
    pLineEditNameChannel->setText(sNameChannel);

    if(n == 0)  rectReport = rect;
    else        rectReport |= rect;

    yTopChannel += 30;
    rectPlot.moveTop(yTopChannel);

    if(isAssignCorrespondingReportPlot) {
//      pTabChannel = qobject_cast<MTelemetryTabChannel*>(pTabWidgetReports->GetPTabWidgetChannels()->widget(n));
//      Q_ASSERT(pTabChannel != NULL); // Q_CHECK_PTR(pTabChannel);
      if(n < countTabsStates)  pTabChannel = qobject_cast<MTelemetryTabChannel*>(pTabWidgetStates->widget(n));
      else                     pTabChannel = qobject_cast<MTelemetryTabChannel*>(pTabWidgetChannels->widget(n-countTabsStates));
      Q_ASSERT(pTabChannel != NULL); // Q_CHECK_PTR(pTabChannel);
    }

    int j = 0;
//        for(int j = 0; j < pTabChannel->GetPListPlots()->count(); j ++) {
    while(j < listCountPlotsInChannels[n]) {
      Q_ASSERT(listNameParamsInChannels[n].count() == 3*2);
//      if(listNameParamsInChannels[n].count() != 3*2) {
//        QMessageBox msgBox(QMessageBox::Critical, "QRect MTelemetry::FillTabReport(...)",
//                                                  "if(listNameParamsInChannels[n].count() != 3*2) == TRUE (!)");   msgBox.exec();
//      }
      sNameParam = listNameParamsInChannels[n][j*3]; //GetPMainWnd()->GetDeltaNItemListParamsTelemetry()];

      float* pminValue = NULL;
      if(listNameParamsInChannels[n][j*3+1] != "N/A") {
        pminValue = new float;   *pminValue = listNameParamsInChannels[n][j*3+1].toFloat();
      }
      float* pmaxValue = NULL;
      if(listNameParamsInChannels[n][j*3+2] != "N/A") {
        pmaxValue = new float;  *pmaxValue = listNameParamsInChannels[n][j*3+2].toFloat();
      }
//      pPlot = new MPlot(this, true, sNameParam.toStdString().c_str(), listNameParamsInChannels[n][j*3+1].toFloat(), listNameParamsInChannels[n][j*3+2].toFloat());
//      pPlot = new MPlot(pScrollAreaReportContents, true, sNameParam.toStdString().c_str(), listNameParamsInChannels[n][j*3+1].toFloat(), listNameParamsInChannels[n][j*3+2].toFloat());
      pPlot = new MPlot(pScrollAreaReportContents, true, sNameParam.toStdString().c_str(), pminValue, pmaxValue);
      delete pminValue;  delete pmaxValue;
      pPlot->setGeometry(rectPlot);
      if(isAssignCorrespondingReportPlot)  pTabChannel->AddAssignCorrespondingReportPlot(pPlot);
//      else                                 pTabReport->AddPlot(pPlot);
      else                                 AddPlot(pPlot);
      rectReport |= rectPlot;
      rectPlot.translate(rectPlot.width()+10,0);
      j += 1;
    }

    yTopChannel += rectPlot.height()+20;
    rectPlot.moveTopLeft(QPoint(10,yTopChannel));

    n += 1;
  }

  rectReport.setTopLeft(QPoint(0,0));
  rectReport.setBottomRight(QPoint(rectReport.right()-3,// + 15,
                                   rectReport.bottom()));// + 4));// + PTabWidgetStates->tabBar()->rect().height()));

//setGeometry(0,0, rectReport.width()+60,321+60);
//pScrollAreaReport->setWidget(this);


//pScrollAreaReport->setMinimumSize(rectReport.right()+3,rectReport.bottom()+3);

//  pScrollAreaReport->setGeometry(QRect(-2,-2, rectReport.right()+15,rectPlot.height()+50));
  setGeometry(QRect(0,0, rectReport.right()+38,rectPlot.height()+70));
//  pScrollAreaReportContents->setGeometry(QRect(0, 0, rectReport.right()+5,rectPlot.height()+5));

//pScrollAreaReportContents->setGeometry(geometry().left(), geometry().top()-5, geometry().width()-50, geometry().height()-30);

  pScrollAreaReportContents->setMinimumSize(rectReport.right()+5,rectReport.bottom()+3);
//  pScrollAreaReportContents->setMinimumSize(geometry().width()-20, rectReport.bottom());
//  pScrollAreaReportContents->setMinimumSize(600,1800);
//  pScrollAreaReport->setWidget(pScrollAreaReportContents);
  setWidget(pScrollAreaReportContents);
//  pScrollAreaReportContents->setMinimumSize(rectReport.right()+3,rectReport.bottom()+3);

//  pScrollAreaReport->setBackgroundRole(QPalette::Base);//QPalette::Window);

//+  setGeometry(0,0, pScrollAreaReport->geometry().width()+3,pScrollAreaReport->geometry().height()+23);

//pScrollAreaReportContents->setGeometry(geometry().left(), geometry().top()-50, geometry().width()-50, geometry().height()-30);


  return rectReport;
}
//--------------------------------------------------------------------------------------------
//bool MTelemetryTabReport::InsertDataFromFileReport(MTelemetryTabReport* pTab, const QString& pathNameFileReport)
bool MTelemetryTabReport::InsertDataFromFileReport(const QString& pathNameFileReport)
{
  int iResult = 0; // OK
  bool bMaybeFileCorrupted = false;

//  MTelemetry* PTelemetry = GetPMainWnd()->GetPTelemetry();

  QString sReportFileVersion;
  int countTelemetryChannels = 0;
  QList<QString>        listNamesChannels;
  QList<QString>        listMinMaxNormalValues;
  QList<int>            listCountPlotsInChannels;       int countPlotsInChannel;
  QList<QList<QString>> listNameParamsInChannelsTemp;   QList<QList<QString>> listNameParamsInChannels;
  QList<QString> list;

  QString sNameChannel;  QString sNameParam;  QString s;

  QFile fileReport(pathNameFileReport);
  if(!fileReport.open(QIODevice::ReadOnly | QIODevice::Text)) {
    QMessageBox msgBox; msgBox.setText("Problem file \""+pathNameFileReport+"\"");   msgBox.exec();
  }
  QTextStream streamFileReport(&fileReport);

  QString line;  int lineLength;  int pos1,pos2;
  int countAllPlots;  int indexAllPlots;
  QRegExp rex("[+.0-9]");  QRegExp rey("N/A|[-+.0-9]");
  QString sValue;  qreal fx,fy;

  while(!streamFileReport.atEnd()) {
    line = streamFileReport.readLine();
    if(line.length() == 0)  continue;

//=Check ReportFileVersion:
    if(sReportFileVersion.length() == 0) {
      sReportFileVersion = ReportFileVersion;
      if(line.mid(0, sReportFileVersion.length()) != sReportFileVersion)  { iResult = 2;  break; }  // Unsupported version of file
      continue;
    }


    pos1 = 0;  pos2 = 0;

    if(listNamesChannels.isEmpty()) {
      lineLength = line.length();
//= Reading the Channel Names:
      while(pos2 >= 0) {
        pos2 = line.indexOf('|', pos1);
        if(pos2 >= 0) {
          sNameChannel = line.mid(pos1, pos2-pos1);  pos1 = pos2+1;
          listNamesChannels << sNameChannel.trimmed();
          countTelemetryChannels += 1;
        }
      }
      sNameChannel = line.mid(pos1);
      listNamesChannels << sNameChannel.trimmed();
      countTelemetryChannels += 1;
      continue;
    }

    if(listCountPlotsInChannels.isEmpty()) {
      if(line.length() != lineLength)  { iResult = 1;  break; }  // corrupted file
//= Reading the Channel Params Names:
      int pos2r, posm;
      QString sParamX = "T(sec)";   countPlotsInChannel = 0;
      pos2 = line.indexOf(sParamX, pos1);
      while(pos2 < line.length()) {
        countPlotsInChannel += 1;
        pos1 = pos2 + sParamX.length();
        pos2 = line.indexOf(sParamX, pos1);
        pos2r = line.indexOf("|", pos1);
        if(pos2 < 0)  pos2 = line.length();

        posm = pos2r > 0 ? qMin(pos2,pos2r) : pos2;
        sNameParam = line.mid(pos1, posm-pos1);
        list << sNameParam.trimmed();
        if((pos2r >= 0 && pos2r < pos2) || (pos2r < 0 && pos2 == line.length())) {
          listCountPlotsInChannels << countPlotsInChannel;   countPlotsInChannel = 0;
          listNameParamsInChannelsTemp << list;  list.clear();
        }
      }

//      MTelemetryTabWidgetStates* pTabWidgetState = qobject_cast<MTelemetryTabWidgetStates*>(parent());
//      Q_CHECK_PTR(pTabWidgetState);
//      pTabWidgetState->FillTabReport(pTab, countTelemetryChannels, listNamesChannels, listCountPlotsInChannels, listNameParamsInChannels, false);//bool isAssignCorrespondingReportPlot)

      countAllPlots = 0;
      for(int n = 0; n < listCountPlotsInChannels.count(); n++) {
        countAllPlots += listCountPlotsInChannels[n];
      }
      continue;
    }

    if(listMinMaxNormalValues.isEmpty()) {
      if(line.length() != lineLength)  { iResult = 1;  break; }  // corrupted file
//= Reading the Min and Max Normal Values:
//MinNormalValue:
      QString sMinNormalValue;  QString sMaxNormalValue;
      while(1) {
        pos1 = line.indexOf(rey, pos2);
        if(pos1 < 0) break;
        pos2 = line.indexOf(' ', pos1);
        sMinNormalValue = line.mid(pos1, pos2-pos1);
        listMinMaxNormalValues << sMinNormalValue;
//MaxNormalValue:
        pos2 += 4; //  " -- "
        pos1 = line.indexOf(rey, pos2);
        if(pos1 < 0) break;
        pos2 = line.indexOf(' ', pos1);
        sMaxNormalValue = line.mid(pos1, pos2-pos1);
        listMinMaxNormalValues << sMaxNormalValue;
      }

//QString s;
//for(int n = 0; n < listMinMaxNormalValues.count(); n++) {
//  s += listMinMaxNormalValues[n]; s += "\n";
//}
//QMessageBox msgBox;  msgBox.setText(s);   msgBox.exec();
      int m = 0;
      for(int n = 0; n < listNameParamsInChannelsTemp.count(); n++) {
//QString s; s.sprintf("listNameParamsInChannels.count() = %d\nn = %d,  %d = listNameParamsInChannels[n].count()\nlistMinMaxNormalValues.count() = %d", listNameParamsInChannels.count(), n, listNameParamsInChannels[n].count(),listMinMaxNormalValues.count());
//QMessageBox msgBox;  msgBox.setText(s);   msgBox.exec();
        for(int j = 0; j < listNameParamsInChannelsTemp[n].count(); j++) {
          list << listNameParamsInChannelsTemp[n][j];
          list << listMinMaxNormalValues[m] << listMinMaxNormalValues[m+1];
          m += 2;
        }
        listNameParamsInChannels << list;  list.clear();
      }

//      MTelemetryTabWidgetStates* pTabWidgetState = qobject_cast<MTelemetryTabWidgetStates*>(parent());
//      Q_ASSERT(pTabWidgetState != NULL); //   Q_CHECK_PTR(pTabWidgetState);
//      pTabWidgetState->FillTabReport(pTab, countTelemetryChannels, listNamesChannels, listCountPlotsInChannels, listNameParamsInChannels, false);//bool isAssignCorrespondingReportPlot)
//      pTab->FillTabReport(countTelemetryChannels, listNamesChannels, listCountPlotsInChannels, listNameParamsInChannels, false);//bool isAssignCorrespondingReportPlot)
      FillTabReport(countTelemetryChannels, listNamesChannels, listCountPlotsInChannels, listNameParamsInChannels, false);//bool isAssignCorrespondingReportPlot)

      continue;
    }

//= Reading the Params Values:
    if(bMaybeFileCorrupted)          { iResult = 1;      break; }  // corrupted file
    if(line.length() != lineLength)  { bMaybeFileCorrupted = true;  }
    indexAllPlots = 0;
    while(1) {
//dt:
      pos1 = line.indexOf(rex, pos2);
      if(pos1 < 0) break;
      pos2 = line.indexOf(' ', pos1);
      sValue = line.mid(pos1, pos2-pos1);  fx = sValue.toFloat();//  pos1 = pos2;
//param:
      pos1 = line.indexOf(rey, pos2);
      if(pos1 < 0) break;
      pos2 = line.indexOf(' ', pos1);
      sValue = line.mid(pos1, pos2-pos1);  fy = sValue.toFloat();

//      pTab->GetPPlot(indexAllPlots)->AddValue(fx,fy);
      GetPPlot(indexAllPlots)->AddValue(fx,fy);
      indexAllPlots += 1;
    }
  }
  fileReport.close();

  if(iResult == 1 || iResult == 2) { // Not OK
    QString sMessage;
    if(iResult == 1)  sMessage = "Selected file:\n\"" + pathNameFileReport + "\"\nis corrupted.";
    else              sMessage = "Unsupported version of selected file:\n\"" + pathNameFileReport + "\".";
    QMessageBox msgBox(QMessageBox::Critical, "Open Report File", s);  msgBox.exec();
  }

  return iResult == 0 ? true : false;
}
//--------------------------------------------------------------------------------------------
