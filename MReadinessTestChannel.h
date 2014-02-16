#ifndef MREADINESSTESTCHANNEL_H
#define MREADINESSTESTCHANNEL_H

#include "MSyntaxHighlighterParamsTest.h"

#include <QWidget>
#include <QString>
#include <QList>
#include <QLineEdit>
#include <QProgressBar>
#include <QTextEdit>
#include <QLabel>
//#include <QThread>

//============================================================================================

class MReadinessTestChannel : public QWidget
{
    Q_OBJECT
public:
//    MReadinessTestChannel(QWidget* parent, const int yTopChannel, const char* nameChannel, const char* namePixmapFileChannel,
//                          QString* pTextTest, QList<QString>* pListParamsNameTest, QList<int>* pListParamsRangeTest);
 MReadinessTestChannel(QWidget* pParent, const int yTopChannel, // const char* namePixmapFileChannel,
//                       QString* pTextTest, QList<QString>* pListParamsChannel);
                       QList<QString>* pListParamsChannel);
  virtual ~MReadinessTestChannel();

//  QThread ThreadTest;

  QString GetNameChannel() { return (*PListParamsChannel)[0]; } //  PLineEditNameChannel->text(); }
  QRect GetRectChannel() { return RectChannel; }

  void Test();
  void InitState();

private:

  QRect RectChannel;
//  QString TextTest;

  bool BResult;
  int  NTestInChannel;
  int  IListItem;
  int  PosParam;

  QList<QString>* PListParamsChannel;

//  QLineEdit* PLineEditNameChannel;
  MSyntaxHighlighterParamsTest* PSyntaxHighlighterParamsTest;

  QString SColorNeutral;  QString SColorQuery;
  QString SColorReady;    QString SColorUnready;

  QProgressBar* PProgressBarTest1;
  QProgressBar* PProgressBarTest2;
  QProgressBar* PProgressBarStatus;

  QTextEdit* PTextEditTest;

  QLabel* PLabelStatus;
  QLabel* PLabelStatusPixmap;

  void StartTest(int nTestInChannel);
  void TestPassed(int nTestInChannel);
  void TestNotPassed(int nTestInChannel);

signals:
//  void SignalTest(const char* nameParam, float valueParam);
//  void SignalTest(QString* psNameChannel, QString* psInputTestName, QString* psInputTestValue, QString* psOutputTestName);
  void SignalGetReadinessTestValue(QString* psNameChannel, QString* psInputTestName, QString* psInputTestValue, QString* psOutputTestName);
  void SignalResultTestChannel(bool bResult);

public slots:
//  void SlotResultTest(float result);
  void SlotTakeReadinessTestValue(float result);
};
//============================================================================================

#endif // MREADINESSTESTCHANNEL_H
