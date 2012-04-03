#include "highlighter_rules.h"






 Highlighter_rules::Highlighter_rules(QTextDocument *parent)
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
     formatRule.setForeground(Qt::darkBlue);
     formatRule.setBackground(QColor(240, 240, 255));
     rule.pattern = QRegExp("^ *- description:.*$");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Bold);
     //formatRule.setFontItalic(true);
     formatRule.setForeground(Qt::darkCyan);
     //formatRule.setBackground(Qt::lightGray);
     rule.pattern = QRegExp("^ *re_rule:.*$");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Bold);
     //formatRule.setFontItalic(true);
     formatRule.setForeground(Qt::darkMagenta);
     //formatRule.setBackground(Qt::lightGray);
     rule.pattern = QRegExp("^ *n_received:.*$");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Bold);
     //formatRule.setFontItalic(true);
     formatRule.setForeground(Qt::gray);
     //formatRule.setBackground(Qt::lightGray);
     rule.pattern = QRegExp("^[ -]*[^:]+:");
     rule.format = formatRule;
     highlightingRules.append(rule);



}


 void Highlighter_rules::highlightBlock(const QString &text)
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
