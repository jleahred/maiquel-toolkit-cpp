#include "highlighter.h"






 Highlighter::Highlighter(QTextDocument *parent)
     : QSyntaxHighlighter(parent)
 {
     HighlightingRule rule;

     /*
     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Bold);
     //formatRule.setForeground(Qt::darkBlue);
     formatRule.setBackground(Qt::lightGray);
     //rule.pattern = QRegExp("^[^ ].*@[^ ]+");
     rule.pattern = QRegExp("^[^ ].*@.+");
     rule.format = formatRule;
     highlightingRules.append(rule);
    */
     formatRule = QTextCharFormat();
     rule.pattern = QRegExp("^[^ ].*@");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     //formatRule.setFontWeight(QFont::Bold);
     formatRule.setFontItalic(true);
     //formatRule.setForeground(Qt::darkBlue);
     formatRule.setBackground(Qt::lightGray);
     rule.pattern = QRegExp("@.*");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Bold);
     formatRule.setForeground(Qt::darkBlue);
     rule.pattern = QRegExp("^[^ ][^#]+#");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Normal);
     formatRule.setForeground(Qt::black);
     rule.pattern = QRegExp("^[^ ][^#]+");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Bold);
     //formatRule.setForeground(Qt::darkRed);
     formatRule.setBackground(Qt::yellow);
     rule.pattern = QRegExp("^[^ ]+ CRIT\\. ");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Bold);
     formatRule.setForeground(Qt::darkRed);
     rule.pattern = QRegExp("^[^ ]+ ERROR ");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontWeight(QFont::Bold);
     formatRule.setForeground(Qt::darkBlue);
     rule.pattern = QRegExp("^[^ ]+");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setForeground(Qt::darkGray);
     //rule.pattern = QRegExp("^..:..:...... ...............     \\|.*$");
     rule.pattern = QRegExp("^.{33}\\|.*$");
     rule.format = formatRule;
     highlightingRules.append(rule);

     /*formatRule = QTextCharFormat();
     formatRule.setFontItalic(true);
     rule.pattern = QRegExp("^      .+$");
     rule.format = formatRule;
     highlightingRules.append(rule);
     */
    /*
     formatRule = QTextCharFormat();
     formatRule.setFontItalic(true);
     formatRule.setFontWeight(QFont::Bold);
     formatRule.setForeground(Qt::darkBlue);
     rule.pattern = QRegExp("^      [^#]+#");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontItalic(true);
     formatRule.setFontWeight(QFont::Normal);
     formatRule.setForeground(Qt::black);
     rule.pattern = QRegExp("^      [^#]+");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontItalic(true);
     formatRule.setFontWeight(QFont::Bold);
     formatRule.setForeground(Qt::darkRed);
     rule.pattern = QRegExp("^      [^ ]+( ERROR | CRITIC )");
     rule.format = formatRule;
     highlightingRules.append(rule);

     formatRule = QTextCharFormat();
     formatRule.setFontItalic(true);
     formatRule.setForeground(Qt::darkBlue);
     rule.pattern = QRegExp("^      [^ ]+");
     rule.format = formatRule;
     highlightingRules.append(rule);
    */



        /*
     //nonTerminalSymbol.setFontWeight(QFont::Bold);
     nonTerminalSymbol.setForeground(Qt::darkBlue);
     rule.pattern = QRegExp("(^| )[A-Z][^ ]+($|)");
     rule.format = nonTerminalSymbol;
     highlightingRules.append(rule);


     singleLineCommentFormat.setForeground(Qt::darkGreen);
     rule.pattern = QRegExp("//[^\n]*");
     rule.format = singleLineCommentFormat;
     highlightingRules.append(rule);


     expandVar.setForeground(Qt::darkMagenta);
     rule.pattern = QRegExp("\\$\\([^\\)]+\\)");
     rule.format = expandVar;
     highlightingRules.append(rule);

     {
         expandPredefVar.setForeground(Qt::darkGreen);
         QStringList keywordPatterns;
         keywordPatterns << "\\$\\(__endl__\\)" << "\\$\\(__nothing__\\)"
                         << "\\$\\(__space__\\)" << "\\$\\(__counter__\\)"
                         ;
         foreach (const QString &pattern, keywordPatterns) {
             rule.pattern = QRegExp(pattern);
             rule.format = expandPredefVar;
             highlightingRules.append(rule);
         }
    }
    */
     /*
     expandPredefVar.setFontItalic(true);
     expandPredefVar.setForeground(Qt::darkMagenta);
     rule.pattern = QRegExp("\\$\\(__[^\\)]+__\\)");
     rule.format = expandPredefVar;
     highlightingRules.append(rule);
    */

 }


 void Highlighter::highlightBlock(const QString &text)
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
