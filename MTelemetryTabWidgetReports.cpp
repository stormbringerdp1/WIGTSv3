#include "MTelemetryTabWidgetReports.h"
#include "MTelemetryTabBarReports.h"
#include "MTelemetryTabReport.h"
#include "MLabelCloseTab.h"
#include "funcs.h"

//#include <QTabBar>
//#include <QFileDialog>
//#include <QTabWidget>
//#include <QLabel>
//#include <QtGlobal>
//  #include <QMessageBox>
//  #include <QApplication>

//============================================================================================
MTelemetryTabWidgetReports::MTelemetryTabWidgetReports(QWidget *parent) //, MTelemetryTabWidgetChannels* pTabWidgetChannels)
                          : QTabWidget(parent) //, PTabWidgetChannels(pTabWidgetChannels)
{
  setTabBar(new MTelemetryTabBarReports(this));

  CurrentIndex = 0; // IsNewTab = false;
  connect(this, SIGNAL(currentChanged(int)), SLOT(SlotIndexChanged(int)));

//  connect(this, SIGNAL(tabBarClicked(int)), SLOT(SlotTabBarClicked(int)));
}
//--------------------------------------------------------------------------------------------
/*
void MTelemetryTabWidgetReports::SlotTabBarClicked(int index)
{
//QMessageBox msgBox;  msgBox.setText("void MTelemetryTabWidgetReports::SlotTabBarClicked(int index)");   msgBox.exec();

//  IsActive = true;

//  MTelemetry* pTelemetry = qobject_cast<MTelemetry*>(parent());
//  Q_ASSERT(pTelemetry != NULL); //  Q_CHECK_PTR(pTelemetry);
//  pTelemetry->ActiveTabWidgetReports();
  GetPMainWnd()->GetPTelemetry()->ActivateTabWidgetReports();
}
*/
//--------------------------------------------------------------------------------------------
QRect MTelemetryTabWidgetReports::AddTabs()
{
//  QList<QString> listNameTabs;    listNameTabs << "Report" << "";

  QRect rectTelemetryReports;
//QMessageBox msgBox; msgBox.setText("1  QRect MTelemetryTabWidgetReports::AddTabs()");   msgBox.exec();
  MTelemetryTabReport* pTabReport = new MTelemetryTabReport(this);
//msgBox.setText("2  QRect MTelemetryTabWidgetReports::AddTabs()");   msgBox.exec();
//      pTabReport->setMouseTracking(true);
  pTabReport->Init();
  addTab(pTabReport, "Report");//listNameTabs[i]);
  rectTelemetryReports = pTabReport->geometry(); //rectReport;

  QWidget* pTab = new QWidget(this);
  int index = addTab(pTab, "");//listNameTabs[i]);
//      if(index == listNameTabs.count()-1) {
//        setTabToolTip(index, "Open past report");
//        tabBar()->setToolTipDuration(2000); //(int msec)
//      }
//      if(index == list.count()-1)  PTabWidgetStates ->setTabWhatsThis(index, "Open past report");


//  tabBar()->setShape(QTabBar::RoundedSouth);

//  rectTelemetryReports.moveTo(0,33);

  return rectTelemetryReports;
}
//--------------------------------------------------------------------------------------------
void MTelemetryTabWidgetReports::SlotIndexChanged(int newIndex)
{
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

  tabBar()->setTabTextColor(CurrentIndex, QColor(0,0,0));
  tabBar()->setTabTextColor(newIndex, QColor(0,0,255));
  CurrentIndex = newIndex;
}
//--------------------------------------------------------------------------------------------
/*
void MTelemetryTabWidgetReports::mousePressEvent(QMouseEvent* event)
{
//QMessageBox msgBox(QMessageBox::Warning, "Open Report File", "void MTelemetryTabWidgetReports::mousePressEvent(QMouseEvent* event)");  msgBox.exec();

QTabWidget::mousePressEvent(event);

//  QTabBar::mousePressEvent(event);  return;
//--
//  if(event->button() == Qt::RightButton) {

//  if(event->button() == Qt::LeftButton && event->type() == QEvent::MouseButtonRelease && tabAt(event->pos()) == count())  return;

//  if(IsNewTab) return;
//  IsNewTab = true;

//QString s; s.sprintf("event->pos().x() = %d,   event->pos().y() = %d\ntabBar()->tabAt(event->pos()) = %d",
//                      event->pos().x(),        event->pos().y(),      tabBar()->tabAt(event->pos()));
//QMessageBox msgBox; msgBox.setText(s);  msgBox.exec();

//  if(tabBar()->tabAt(event->pos()) >= 0) {
//QMessageBox msgBox(QMessageBox::Warning, "Open Report File", "2  void MTelemetryTabWidgetReports::mousePressEvent(QMouseEvent* event)");  msgBox.exec();
//    setCurrentIndex(tabBar()->tabAt(event->pos()));
//  }

  if(event->button() == Qt::LeftButton && tabBar()->tabAt(event->pos()) == count()-1) {
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
        MTelemetryTabWidgetStates* pTabWidgetState = qobject_cast<MTelemetryTabWidgetStates*>(parent());
        Q_ASSERT(pTabWidgetState != NULL); // Q_CHECK_PTR(pTabWidgetState);
        MTelemetryTabReport* pTabReport = new MTelemetryTabReport(pTabWidgetState);
        int index = pTabWidgetState->insertTab(count()-1, pTabReport, nameFileReport.left(nameFileReport.length()-4));
//        addTab(pTab, fileNames.at(0));
//        QLabel* pLabelName = new QLabel(this);
//        pLabelName->setText(nameFileReport.left(nameFileReport.length()-4));
//        MLabelCloseTab* pLabelPixmap = new MLabelCloseTab(this, pTabReport);

//        setTabButton(count()-2, QTabBar::LeftSide, pLabelName);
        tabBar()->setTabButton(count()-2, QTabBar::RightSide, new MLabelCloseTab(this, pTabReport));

//        if(InsertDataFromFileReport(pTabReport, pathNamesFiles.at(0))) {
        if(pTabReport->InsertDataFromFileReport(pathNamesFiles.at(0))) {
          setCurrentIndex(index); // emit tabBarClicked(index);//   emit currentChanged(index);//   pLabelPixmap->setFocus();
//          QMouseEvent eventPress(QEvent::MouseButtonPress, tabRect(index).topLeft()+=QPoint(5,5), Qt::LeftButton, 0, 0);
//          QApplication::sendEvent(this, &eventPress);
//          QMouseEvent eventRelease(QEvent::MouseButtonRelease, tabRect(index+1).topLeft()+=QPoint(20,8), Qt::LeftButton, 0, 0);
//          QApplication::postEvent(this, &eventRelease);
        }
        else  CloseTab(pTabReport);
      }
      else {
        QMessageBox msgBox(QMessageBox::Warning, "Open Report File", "Selected file:\n\""+nameFileReport+"\"\nis the current report file.");  msgBox.exec();
      }
    }
//    IsNewTab = false;
  }
  else {
    QTabWidget::mousePressEvent(event);
  }
}
*/
//--------------------------------------------------------------------------------------------
/*
void MTelemetryTabWidgetReports::setCurrentIndex(int index)
{
  QMessageBox msgBox(QMessageBox::Warning, "Open Report File", "void MTelemetryTabWidgetReports::setCurrentIndex(int index)");  msgBox.exec();

  QTabWidget::setCurrentIndex(index);
}
*/
//--------------------------------------------------------------------------------------------
bool MTelemetryTabWidgetReports::event(QEvent* e)
{
  if(e->type() == QEvent::MouseButtonPress && !isEnabled()) {
    GetPMainWnd()->GetPTelemetry()->ActivateTabWidgetReports();
  }
  return QTabWidget::event(e);
}
//--------------------------------------------------------------------------------------------
/*
void MTelemetryTabWidgetReports::changeEvent(QEvent * ev)
{
//QMessageBox msgBox(QMessageBox::Warning, "Open Report File", "void MTelemetryTabWidgetReports::changeEvent(QEvent * ev)");  msgBox.exec();
//return;
  QTabWidget::changeEvent(ev);
}
*/
//--------------------------------------------------------------------------------------------
void MTelemetryTabWidgetReports::CloseTab(QWidget* pTab)
{
//  MTelemetryTabWidgetStates* pTabWidgetState = qobject_cast<MTelemetryTabWidgetStates*>(parent());
//  Q_ASSERT(pTabWidgetState != NULL); // Q_CHECK_PTR(pTabWidgetState);
  int index = indexOf(pTab);
  removeTab(index);
  if(index  == currentIndex())  setCurrentIndex(qMin(index,count()-2));
}
//--------------------------------------------------------------------------------------------
