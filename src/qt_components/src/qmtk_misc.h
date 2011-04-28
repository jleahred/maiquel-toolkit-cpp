#ifndef QMTKMISC_H
#define QMTKMISC_H


#include <QString>
#include "support/fixed_number.h"

#include <QDropEvent>
#include <QColor>

#include "components/msg_common.h"



QString fn_as_QString(const mtk::FixedNumber& fn);


QString                             dragProductText (const mtk::msg::sub_product_code& product);
mtk::msg::sub_product_code          get_product_code(QDropEvent *event);


//const QColor mtk_yellow(QColor(Qt::yellow).lighter(150));
//const QColor mtk_yellow(QColor(227,233,255));
const QColor mtk_color_header(QColor(191,219,255));
const QColor mtk_color_problem   (QColor(Qt::red).lighter());
const QColor mtk_color_buy (QColor(Qt::green).lighter());

int get_base_font_size(void);
void set_base_font_size(int new_size);




#endif // QMTKMISC_H
