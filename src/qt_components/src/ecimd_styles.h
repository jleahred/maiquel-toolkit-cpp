#ifndef ECIMD_STYLES_H__
#define ECIMD_STYLES_H__


#include <QColor>




namespace ecimd_styles {


    //const QColor mtk_yellow(QColor(Qt::yellow).lighter(150));
    //const QColor mtk_yellow(QColor(227,233,255));
    const QColor color_header       (QColor(191,219,255));
    const QColor color_problem      (QColor(Qt::red));
    const QColor color_sell         (QColor(Qt::red).lighter(160));
    const QColor color_buy          (QColor(Qt::green).lighter(160));
    const QColor color_sell_cell    (QColor(255,215,225));
    const QColor color_buy_cell     (QColor(215,255,225));
    const QColor color_executed     (QColor(Qt::cyan).lighter(120));
    //const QColor color_executed     (QColor(255, 175, 75));
    const QColor color_pending      (QColor(Qt::yellow).lighter(150));
    const QColor color_null         (QColor(40, 0, 60));
    //const QColor color_rejected     (QColor(100, 0, 50));
    //const QColor color_rejected     (QColor(200, 100, 150));
    //const QColor color_rejected     (QColor(230, 130, 180));
    const QColor color_rejected     (QColor(255, 0, 0));
    const QColor color_blinking     (QColor(105, 145, 192));
    const QColor color_blinking2    =  color_blinking;
    //const QColor color_blinking     (QColor(140, 40, 90));



    int  get_base_font_size(void);
    void set_base_font_size(int new_size);




    QString  style_get_component            (void);
    QString  style_get_component_editing    (void);
    QString  style_get_component_error      (void);


    QString  style_get_label_product_ok             (void);
    QString  style_get_label_product_missing_info   (void);
    QString  style_get_label_product_drag_over_ok   (void);



};      //      namespace ecimd_styles {

#endif // ECIMD_STYLES_H__
