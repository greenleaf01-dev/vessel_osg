#ifndef HHTHUMBNAILCANVAS_H
#define HHTHUMBNAILCANVAS_H

#include "ihhthumbnailcanvas.h"
#include "ihhcanvas.h"
#include "lib_global.h"
#include <QGraphicsView>
class IHHPresentation;
class LIB_EXPORT HHThumbnailCanvas : public QGraphicsView, public IHHThumbnailCanvas, public IHHCanvasImdDraw
{
    Q_OBJECT
    Q_INTERFACES( IHHThumbnailCanvas )
public:
    HHThumbnailCanvas( QWidget *parent = 0 );
    virtual ~HHThumbnailCanvas();
    virtual void attachScene( QGraphicsScene *scene );
    virtual void setGeometryRect( QRect geometry );
    virtual void setDrawRange( QRectF range );
    virtual void drawItems(QPainter *painter, int numItems,
                           QGraphicsItem *items[],
                           const QStyleOptionGraphicsItem options[]);
    virtual void changeRoveType( QString strType );

public:
	void setPresentation(IHHPresentation   *presentation);
protected:
    bool viewportEvent(QEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE; 
	void wheelEvent(QWheelEvent *event);
    void scrollContentsBy(int dx, int dy);

private:
    IHHPresentation    *m_presentation;
    QRectF              m_rectRange;
    QString             m_strRov;


    //2018-07-05 GJB  Immediate draw interface implementation
    public:
        /* @brief  Immediate drawing on GraphicsView.
         * @param  rcUpdate  -- drawing bounding rect.
         * @param  fnDrawImp -- function which User provided to  do drawing.
        */
        virtual void drawImmediate( const QRectF& rcSceneUpdate, std::function< void (QPainter * p ) >  fn ) Q_DECL_OVERRIDE;
        virtual void paintEvent   ( QPaintEvent *event ) Q_DECL_OVERRIDE;

    private:
        void setImdDrawFunc   ( std::function< void (QPainter * p ) >  fn )
        {
            m_fnImdDrawFunc = fn ;
        }
        void clearImdDrawFunc( )
        {
            m_fnImdDrawFunc = std::function< void (QPainter * p )> ();
        }
    private:
        std::function< void (QPainter * p ) >    m_fnImdDrawFunc;
};

#endif // HHTHUMBNAILCANVAS_H
