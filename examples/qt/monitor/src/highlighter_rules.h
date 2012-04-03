#ifndef __HIGHLIGHTER__RULES_H
#define __HIGHLIGHTER__RULES_H

#include <QSyntaxHighlighter>



class Highlighter_rules : public QSyntaxHighlighter
{
    Q_OBJECT

 public:
    Highlighter_rules(QTextDocument *parent = 0);

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

#endif // __HIGHLIGHTER__RULES_H
