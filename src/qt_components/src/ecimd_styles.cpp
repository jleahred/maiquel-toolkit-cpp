#include "ecimd_styles.h"




namespace ecimd_styles {



    namespace {
        int base_font_size=13;
    };



    int get_base_font_size(void)
    {
        return base_font_size;
    }

    void set_base_font_size(int new_size)
    {
        base_font_size = new_size;
    }




    QString  style_get_component(void)
    {
        return QLatin1String(
                "QFrame {"
                "    background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(230,230,255), stop: 1 rgb(170,200,255));"
                "}"

                "QLabel {"
                "    background-color: rgb(255, 255, 255);"
                "    font: 12pt;"
                "}"

                "qLocaleDoubleSpinBox , QDoubleSpinBox  {"
                "    background-color: rgb(255, 255, 100);"
                "}"

                "QToolButton:checked {"
                "    background-color: rgb(255, 255, 100);"
                "    font: 12pt;"
                "    font-weight: bold;"
                "}"

                "QToolButton:!checked {"
                "    background-color: rgb(255, 255, 200);"
                "    font: 12pt;"
                "    font-weight: bold;"
                "}"


                "QToolButton#bid_button {"
                "color:darkgreen;"
                "}"

                "QToolButton#ask_button {"
                "color:darkred;"
                "}"
                );
    }

    QString  style_get_component_editing(void)
    {
        return QLatin1String(
                "QFrame {"
                "        background-color:  rgb(120,120,255);"
                "}"

                "QLabel {"
                "    background-color: rgb(30,0,100);"

                "    font: 12pt;"
                "}"

                "qLocaleDoubleSpinBox , QDoubleSpinBox  {"
                "    background-color: rgb(255, 255, 100);"
                "}"

                "QToolButton:checked {"
                "    background-color: rgb(255, 255, 100);"
                "    font: 12pt;"
                "    font-weight: bold;"
                "}"

                "QToolButton:!checked {"
                "    background-color: rgb(255, 255, 200);"
                "    font: 12pt;"
                "    font-weight: bold;"
                "}"


                "QToolButton#bid_button {"
                "color:darkgreen;"
                "}"

                "QToolButton#ask_button {"
                "color:darkred;"
                "}"
                );
    }

    QString  style_get_component_error      (void)
    {
        return QLatin1String(
                "QFrame {"
                "        background-color:  rgb(255,0,0);"
                "}"

                "QLabel {"
                "    background-color: rgb(255, 0, 0);"
                "    font: 12pt;"
                "}"

                "qLocaleDoubleSpinBox , QDoubleSpinBox  {"
                "    background-color: rgb(255, 255, 100);"
                "}"

                "QToolButton:checked {"
                "    background-color: rgb(255, 255, 100);"
                "    font: 12pt;"
                "    font-weight: bold;"
                "}"

                "QToolButton:!checked {"
                "    background-color: rgb(255, 255, 200);"
                "    font: 12pt;"
                "    font-weight: bold;"
                "}"


                "QToolButton#bid_button {"
                "color:darkgreen;"
                "}"

                "QToolButton#ask_button {"
                "color:darkred;"
                "}"
                );
    }







    QString  style_get_label_product_ok             (void)
    {
        return QLatin1String(
        "background-color: rgb(255, 255, 255);\n"
        "font: 12pt;\n"
        //"font-weight: bold;\n"
        "color: rgb(30,0,100);"
        );

    }

    QString  style_get_label_product_missing_info   (void)
    {
        return QLatin1String(
        "background-color: rgb(255, 255, 100);\n"
        "font: 12pt;\n"
        //"font-weight: bold;\n"
        "color: rgb(30,0,100);"
        );
    }


    QString  style_get_label_product_drag_over_ok   (void)
    {
        return QLatin1String(
        "background-color: rgb(255, 255, 200);\n"
        "font: 12pt;\n"
        //"font-weight: bold;\n"
        "color: rgb(30,0,100);"
        );
    }


};      //      namespace ecimd_styles {


