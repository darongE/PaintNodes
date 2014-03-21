#ifndef USCENE3D_H
#define USCENE3D_H

#include <QGLWidget>
#include <GL/glu.h>

#include <QVariant>

#include <QDebug>

class Node
{
public:
    Node() { }
    Node( const QString & name, const QString & d ) { fromString( name, d ); }

    void fromString( const QString & name, const QString & d )
    {
        QStringList params = d.split(", ");
        QStringList listPos = params[0].split("x");

        QPointF p( listPos[0].toDouble(), listPos[1].toDouble() );
        uint r = params[1].toUInt();
        QColor c( params[2] );

        setText( name );
        setColor( c );
        setPos( p );
        setRadius( r );
    }
    QString toString()
    {
        const QString & strPos = QString( "%1x%2" ).arg( pos().x() ).arg( pos().y() );
        return QString( "%1, %2, %3" ).arg( strPos ).arg( radius() ).arg( color().name() );
    }

    void setText( const QString & t ) { d_data.insert( "text", t ); }
    QString text() { return d_data.value( "text" ).toString(); }

    void setColor( const QColor & c ) { d_data.insert( "color", c.name() ); }
    QColor color() { return QColor( d_data.value( "color" ).toString() ); }

    void setPos( const QPointF & p ) { d_data.insert( "pos", p ); }
    QPointF pos() { return d_data.value( "pos" ).toPointF(); }

    void setRadius( qreal r ) { d_data.insert( "radius", r ); }
    qreal radius() { return d_data.value( "radius" ).toDouble(); }

private:
    QMap < QString, QVariant > d_data;
};

Q_DECLARE_METATYPE( Node * )


class UScene3D: public QGLWidget
{
    Q_OBJECT

public:
    UScene3D( QWidget * parent = 0 );
    ~UScene3D();

    void addNode( Node * node ) { if ( nodes.indexOf( node ) == -1 ) nodes.append( node ); }
    void takeNode( Node * node ) { nodes.takeAt( nodes.indexOf( node ) ); }
    bool removeNode( Node * node ) { return nodes.removeOne( node ); }

private:
    void drawNode( Node * node );

private:
    QList < Node * > nodes;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
};

#endif // USCENE3D_H
