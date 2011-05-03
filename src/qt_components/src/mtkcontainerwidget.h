#ifndef UMTK_CONTAINER
#define UMTK_CONTAINER

#include <QWidget>
#include <QPoint>
#include <QImage>




class QMouseEvent;
namespace YAML { class Emitter;  class Node;      };




class mtk_uTitle : public QWidget
{
    Q_OBJECT
public:
    explicit mtk_uTitle(QWidget *parent = 0);



private:
    void updateBackground(bool show);
    //QColor basecolor;
    bool    moving;
    QImage  image_close;

signals:
    void on_mousePressEvent(QMouseEvent* event);
    void on_mouseMoveEvent(QMouseEvent* event);
    void on_mouseReleaseEvent(QMouseEvent* event);

public slots:

private slots:

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void leaveEvent ( QEvent * event );
    virtual void paintEvent(QPaintEvent *);
};

class mtk_uResize : public QWidget
{
    Q_OBJECT
public:
    explicit mtk_uResize(QWidget *parent = 0);



private:
    QColor basecolor;
    //void updateBackground(bool focus);


signals:
    void on_mouseMoveEvent(QMouseEvent* event);

public slots:

private slots:

protected:
    //void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    //void mouseReleaseEvent(QMouseEvent* event);

};




class mtkContainerWidget : public QWidget
{
    Q_OBJECT
    friend YAML::Emitter&   operator << (YAML::Emitter&     out, const mtkContainerWidget& m);
    friend void             operator >> (const YAML::Node& node,    mtkContainerWidget& m);

public:
    explicit mtkContainerWidget(QWidget *parent = 0);
    virtual ~mtkContainerWidget(){}

    void inserting_components_ended(void);


private:

    QPoint  moving_offset;
    mtk_uTitle* title;
    mtk_uResize* resizer;

protected:
    virtual void    resizeEvent  (QResizeEvent * event );
    virtual void    focusInEvent (QFocusEvent * /*event*/ ) { raise(); }
    virtual void    paintEvent   (QPaintEvent *);


signals:
    void signal_start_moving(void);
    void signal_stop_moving (void);


public slots:

private slots:
    void title_mousePressEvent(QMouseEvent* event);
    void title_mouseMoveEvent(QMouseEvent* event);
    void title_mouseReleaseEvent(QMouseEvent* event);

    void resize_mouseMoveEvent(QMouseEvent* event);

};



YAML::Emitter& operator << (YAML::Emitter& out, const mtkContainerWidget& m);





#endif // UMTK_CONTAINER
