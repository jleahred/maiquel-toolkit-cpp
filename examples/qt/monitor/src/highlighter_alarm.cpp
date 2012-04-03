#include "highlighter_alarm.h"






 Highlighter_alarm::Highlighter_alarm(QTextDocument *parent)
     : QSyntaxHighlighter(parent)
 {
     HighlightingRule rule;

     /*
     formatRule = QTextCharFormat();
     //formatRule.setFontWeight(QFont::Bold);
     formatRule.setFontItalic(true);
     //formatRule.setForeground(Qt::darkBlue);
     formatRule.setBackground(Qt::lightGray);
     rule.pattern = QRegExp("@.*");
     rule.format = formatRule;
     highlightingRules.append(rule);
     */

     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Bold);
     //formatRule.setFontItalic(true);
     //formatRule.setForeground(Qt::darkMagenta);
     //formatRule.setBackground(QColor(255, 255, 200));
     rule.pattern = QRegExp("^ +(broker_code|process_name):.*$");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     //formatRule.setFontWeight(QFont::Bold);
     //formatRule.setFontItalic(true);
     formatRule.setForeground(Qt::darkMagenta);
     //formatRule.setBackground(Qt::lightGray);
     rule.pattern = QRegExp("^ +[^:]+:");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     //formatRule.setFontWeight(QFont::Bold);
     //formatRule.setFontItalic(true);
     //formatRule.setForeground(Qt::darkMagenta);
     formatRule.setBackground(QColor(255, 255, 200));
     rule.pattern = QRegExp("^message:.*$");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Bold);
     //formatRule.setFontItalic(true);
     formatRule.setForeground(Qt::darkMagenta);
     //formatRule.setBackground(Qt::lightGray);
     rule.pattern = QRegExp("^[^ ]+:");
     rule.format = formatRule;
     highlightingRules.append(rule);
}


 void Highlighter_alarm::highlightBlock(const QString &text)
 {
     foreach (const HighlightingRule &rule, highlightingRules) {
         QRegExp expression(rule.pattern);
         int index = expression.indexIn(text);
         while (index >= 0) {
             int length = expression.matchedLength();
             setFormat(index, length, rule.format);
             index = expression.indexIn(text, index + length);
         }
     }
     setCurrentBlockState(0);
 }
