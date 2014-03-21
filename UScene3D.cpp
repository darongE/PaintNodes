#include "UScene3D.h"

#include <math.h>

UScene3D::UScene3D( QWidget * parent )
    : QGLWidget( parent )
{
}
UScene3D::~UScene3D()
{
    qDeleteAll( nodes );
}

void UScene3D::drawNode( Node * node )
{
    const QColor & color = node->color();
    qreal x = node->pos().x();
    qreal y = node->pos().y();
    qreal radius = node->radius();

    qglColor( color );

    // рисование круга
    glBegin( GL_TRIANGLE_FAN );
    glVertex2d( x, y );
    for( int i = 0; i <= radius; i++ )
    {
        qreal temp = ( qreal ) i / radius * M_PI * 2.0;
        glVertex2d( x + cos(temp) * ( radius / 10.0 ), y + sin(temp) * ( radius / 10.0 ) );
    }
    glEnd();
}

void UScene3D::initializeGL()
{
    qglClearColor( Qt::black );
}
void UScene3D::resizeGL(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0, 0, width, height);
    gluOrtho2D(0, width, 0, height);
}
void UScene3D::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT );
    glPushMatrix();
    glTranslated( width() / 2, height() / 2, 0 );

    foreach ( Node * node, nodes )
        drawNode( node );

    glPopMatrix();
}
