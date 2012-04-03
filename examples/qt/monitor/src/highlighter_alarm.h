#ifndef __HIGHLIGHTER_ALARM_H
#define __HIGHLIGHTER_ALARM_H

#include <QSyntaxHighlighter>



class Highlighter_alarm : public QSyntaxHighlighter
{
    Q_OBJECT

 public:
    Highlighter_alarm(QTextDocument *parent = 0);

 protected:
     void highlightBlock(const QString &text);

 private:
     struct HighlightingRule
     {
         QRegExp pattern;
         QTextCharFormat format;
     };

     QVector<HighlightingRule> highlightingRules;
     QTextCharFormat formatRule;


     /*
     QVector<HighlightingRule> highlightingRules;

     QTextCharFormat predefinedVars;
     QTextCharFormat keywordFormat;
     QTextCharFormat nonTerminalSymbol;
     QTextCharFormat singleLineCommentFormat;
     QTextCharFormat expandVar;
     QTextCharFormat expandPredefVar;
     */
};

#endif // __HIGHLIGHTER_ALARM_H
