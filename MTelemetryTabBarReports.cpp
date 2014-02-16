#include "MTelemetryTabBarReports.h"
#include "MTelemetryTabWidgetReports.h"
#include "MLabelCloseTab.h"
#include "funcs.h"

#include <QFileDialog>
#include <QMessageBox>

//============================================================================================
MTelemetryTabBarReports::MTelemetryTabBarReports(QWidget *parent) :
    QTabBar(parent)
{
//  CurrentIndex = 0; // IsNewTab = false;
//  connect(this, SIGNAL(currentChanged(int)), SLOT(SlotIndexChanged(int)));
}
//--------------------------------------------------------------------------------------------
/*+
void MTelemetryTabBarStates::SlotIndexChanged(int newIndex)
{
*/
/*
//return;
//QMessageBox msgBox;  msgBox.setText("void MTelemetryTabBarStates::SlotIndexChanged(int newIndex)");   msgBox.exec();
//  if(CurrentIndex != newIndex) {
//  if(0 <= CurrentIndex && CurrentIndex < count()-1) {
  if(CurrentIndex < count()-1) {
// rgb(0,0,0):
    if(CurrentIndex < 2)  setTabTextColor(CurrentIndex, QColor(0,0,0));
    else {
      QLabel* pName = qobject_cast<QLabel*>(tabButton(CurrentIndex, QTabBar::LeftSide));
//      Q_ASSERT(pName != NULL); //  Q_CHECK_PTR(pName);
      if(pName != NULL)  pName->setStyleSheet("QLabel { color : rgb(0,0,0); }");
    }
  }

// rgb(0,0,255):
  if(newIndex < 2)  setTabTextColor(newIndex, QColor(0,0,255));
  else {
    QLabel* pName = qobject_cast<QLabel*>(tabButton(newIndex, QTabBar::LeftSide));
//    Q_ASSERT(pName != NULL);  Q_CHECK_PTR(pName);
    if(pName != NULL)  pName->setStyleSheet("QLabel { color : rgb(0,0,255); }");
//        CurrentIndex = newIndex;
//    }
//      else setCurrentIndex(CurrentIndex);
  }

  CurrentIndex = newIndex;
//  }
*/
/*+
  setTabTextColor(CurrentIndex, QColor(0,0,0));
  setTabTextColor(newIndex, QColor(0,0,255));
  CurrentIndex = newIndex;
}
*/
//--------------------------------------------------------------------------------------------
void MTelemetryTabBarReports::mousePressEvent(QMouseEvent* event)
{
//  QTabBar::mousePressEvent(event);  return;
//--
//  if(event->button() == Qt::RightButton) {

//  if(event->button() == Qt::LeftButton && event->type() == QEvent::MouseButtonRelease && tabAt(event->pos()) == count())  return;

//  if(IsNewTab) return;
//  IsNewTab = true;

  if(event->button() == Qt::LeftButton && tabAt(event->pos()) == count()-1) {
//    IsNewTab = true;
//  if(event->button() == Qt::LeftButton && event->type() == QEvent::MouseButtonRelease && tabAt(event->pos()) == count()-1) {

//    QMouseEvent eventRelease(QEvent::MouseButtonRelease, tabRect(tabAt(event->pos())).topLeft()+=QPoint(20,8), Qt::LeftButton, 0, 0);
//    QApplication::sendEvent(this, &eventRelease);

//    int index = currentIndex();
    QFileDialog dialog(this, "Open File Report", "", "Files (*.wig)");  dialog.setAcceptMode(QFileDialog::AcceptOpen);//Save);
    QStringList pathNamesFiles;
    if(dialog.exec() == QDialog::Accepted) {
//=Add Report Tab:
      pathNamesFiles = dialog.selectedFiles();
      QDir path;
      QString nameFileReport = path.relativeFilePath(pathNamesFiles.at(0));
      if(*GetPMainWnd()->GetPTelemetry()->GetCurrentPNameFileReport() != nameFileReport) {
//        QWidget* pTab = new QWidget(this);
//        insertTab(count()-1, pTab, QIcon(QString::fromUtf8(":/TestNotPassed.ico")), fileNames.at(0));
        MTelemetryTabWidgetReports* pTabWidgetReports = qobject_cast<MTelemetryTabWidgetReports*>(parent());
        Q_ASSERT(pTabWidgetReports != NULL); // Q_CHECK_PTR(pTabWidgetState);
        MTelemetryTabReport* pTabReport = new MTelemetryTabReport(pTabWidgetReports);
        int index = pTabWidgetReports->insertTab(count()-1, pTabReport, nameFileReport.left(nameFileReport.length()-4));
//        addTab(pTab, fileNames.at(0));
//        QLabel* pLabelName = new QLabel(this);
//        pLabelName->setText(nameFileReport.left(nameFileReport.length()-4));
//        MLabelCloseTab* pLabelPixmap = new MLabelCloseTab(this, pTabReport);

//        setTabButton(count()-2, QTabBar::LeftSide, pLabelName);
        setTabButton(count()-2, QTabBar::RightSide, new MLabelCloseTab(this, pTabReport));

        if(pTabReport->InsertDataFromFileReport(pathNamesFiles.at(0))) {
          setCurrentIndex(index); // emit tabBarClicked(index);//   emit currentChanged(index);//   pLabelPixmap->setFocus();
//          QMouseEvent eventPress(QEvent::MouseButtonPress, tabRect(index).topLeft()+=QPoint(5,5), Qt::LeftButton, 0, 0);
//          QApplication::sendEvent(this, &eventPress);
//          QMouseEvent eventRelease(QEvent::MouseButtonRelease, tabRect(index+1).topLeft()+=QPoint(20,8), Qt::LeftButton, 0, 0);
//          QApplication::postEvent(this, &eventRelease);
        }
        else  pTabWidgetReports->CloseTab(pTabReport);
      }
      else {
        QMessageBox msgBox(QMessageBox::Warning, "Open Report File", "Selected file:\n\""+nameFileReport+"\"\nis the current report file.");  msgBox.exec();
      }
    }
//    IsNewTab = false;
  }
  else {
    QTabBar::mousePressEvent(event);
  }
}
//--------------------------------------------------------------------------------------------
/*
void MTelemetryTabBarStates::mouseReleaseEvent(QMouseEvent* event)
{
//  if(event->button() == Qt::LeftButton && tabAt(event->pos()) == count())
//  return;
  QTabBar::mouseReleaseEvent(event);
}
*/
//--------------------------------------------------------------------------------------------
/*
void MTelemetryTabBarStates::CloseTab(QWidget* pTab)
{
  MTelemetryTabWidgetStates* pTabWidgetState = qobject_cast<MTelemetryTabWidgetStates*>(parent());
  Q_ASSERT(pTabWidgetState != NULL); // Q_CHECK_PTR(pTabWidgetState);
  int index = pTabWidgetState->indexOf(pTab);
  pTabWidgetState->removeTab(index);
  if(index  == currentIndex())  setCurrentIndex(qMin(index,count()-2));
}
*/
//--------------------------------------------------------------------------------------------
/*
void MTelemetryTabBarStates::mouseMoveEvent(QMouseEvent* event)
{
//setMouseTracking(true);
  QTabBar::mouseMoveEvent(event);
//  QWidget::mouseMoveEvent(event);
//QMessageBox msgBox;  msgBox.setText("void MTelemetryTabBarStates::mouseMoveEvent(QMouseEvent* event)");   msgBox.exec();
//--
  QWidget* pChild = childAt(event->pos().x(),event->pos().y());
  if(pChild) {
//    MTelemetryTabReport* pTabReport = qobject_cast<MTelemetryTabReport*>(pChild);
    QLabel* pTabReport = qobject_cast<QLabel*>(pChild);
    if(pTabReport) {
//QMessageBox msgBox;  msgBox.setText("pTabReport");   msgBox.exec();
    }
  }
}
*/
//--------------------------------------------------------------------------------------------
/*
bool MTelemetryTabBarStates::event(QEvent* e)
{
  bool b = QTabBar::event(e);
//--
//  if(e->type() == QEvent::MouseMove) {
//  if(e->type() == QEvent::HoverMove) {
//  if(e->type() == QEvent::HoverEnter) {
//QMessageBox msgBox;  msgBox.setText("QEvent::HoverEnter");   msgBox.exec();
//  }
//  if(e->type() == QEvent::HoverLeave) {
//QMessageBox msgBox;  msgBox.setText("QEvent::HoverLeave");   msgBox.exec();
//  }

//  if(e->type() == QEvent::ToolTip) {
//QMessageBox msgBox;  msgBox.setText("e->type() == QEvent::ToolTip");   msgBox.exec();
//  }

  return b;
}
*/
//--------------------------------------------------------------------------------------------
/*
bool MTelemetryTabBarStates::InsertDataFromFileReport(MTelemetryTabReport* pTab, const QString& pathNameFileReport)
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
  QRegExp rex("[+.0-9]");  QRegExp rey("[-+.0-9]");
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
      pTab->FillTabReport(countTelemetryChannels, listNamesChannels, listCountPlotsInChannels, listNameParamsInChannels, false);//bool isAssignCorrespondingReportPlot)

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

      pTab->GetPPlot(indexAllPlots)->AddValue(fx,fy);
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
*/
//--------------------------------------------------------------------------------------------
