#include "MSyntaxHighlighterParamsTest.h"

  #include <QMessageBox>
//============================================================================================

MSyntaxHighlighterParamsTest::MSyntaxHighlighterParamsTest(QTextDocument* parent, QList<QString>* pListParamsChannel,
                                                           int iFirstItemListParamsChannel, int deltaNItemListParamsChannel) // QList<QString> *pListParamsNameTest, QList<int> *pListParamsRangeTest)
                            : QSyntaxHighlighter(parent), PListParamsChannel(pListParamsChannel),
                              IFirstItemListParamsChannel(iFirstItemListParamsChannel), DeltaNItemListParamsChannel(deltaNItemListParamsChannel)
{
//  int CountParams = pListParamsChannel->count();
//  int ICurrentParam = 0;

//  IListItem = 3;
  InitBegin();

//  PListParamsNameTest = new QList<QString>(*pListParamsNameTest);
//  PListParamsRangeTest = new QList<int>(*pListParamsRangeTest);
}
//--------------------------------------------------------------------------------------------
MSyntaxHighlighterParamsTest::~MSyntaxHighlighterParamsTest()
{
//  PListParamsNameTest->clear();    delete PListParamsNameTest;
//  PListParamsRangeTest->clear();   delete PListParamsRangeTest;
}
//--------------------------------------------------------------------------------------------
void MSyntaxHighlighterParamsTest::InitBegin()
{
  IListItem = IFirstItemListParamsChannel;
}
//--------------------------------------------------------------------------------------------
void MSyntaxHighlighterParamsTest::highlightBlock(const QString& text)
{

//  if(ICurrentParam >= CountParams)  ICurrentParam -= CountParams;

//+?  if(IListItem+2 >= PListParamsChannel->count())  IListItem = 3;

  int pos = text.indexOf((*PListParamsChannel)[IListItem], 0, Qt::CaseSensitive);
//QMessageBox msgBox;
//msgBox.setText(text);   msgBox.exec();
//msgBox.setText((*PListParamsChannel)[IListItem]);   msgBox.exec();
  if(pos >= 0) {
    pos += (*PListParamsChannel)[IListItem].length();
    QString s = text.mid(pos);
    if(!s.isEmpty()) {
      float param = s.toFloat();
      QColor color;
      if((*PListParamsChannel)[IListItem+1].toFloat() <= param && param <= (*PListParamsChannel)[IListItem+2].toFloat())
        color = QColor(0,255,0);
      else
        color = QColor(255,0,0);
      setFormat(pos, s.length(), color);

      IListItem += DeltaNItemListParamsChannel;
    }
//QMessageBox msgBox;  msgBox.setText(s);   msgBox.exec();
  }

/*
    QTextCharFormat myClassFormat;
    myClassFormat.setFontWeight(QFont::Bold);
    myClassFormat.setForeground(Qt::darkMagenta);
    QString pattern = "\\bMy[A-Za-z]+\\b";

    QRegExp expression(pattern);
    int index = text.indexOf(expression);
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, myClassFormat);
        index = text.indexOf(expression, index + length);
     }
 */
/*
  sTextTest = PTextEditTest->document()->toPlainText(); //> >plainText();//  (*PListParamsChannel)[2];
      sParam = (*PListParamsChannel)[IListItem-1];
      PosParam = sTextTest.indexOf(sParam, PosParam, Qt::CaseSensitive) + sParam.length();
      sTextTest.insert(PosParam,s);
      PTextEditTest->setText(sTextTest);
*/
//QMessageBox msgBox;  msgBox.setText(text);   msgBox.exec();

 }
 //--------------------------------------------------------------------------------------------
