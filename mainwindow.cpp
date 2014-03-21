#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->splitter->setStretchFactor( 1, 2 );

    connect( ui->actionAddNode, SIGNAL(triggered()), SLOT(addNode()) );
    connect( ui->actionDeleteNode, SIGNAL(triggered()), SLOT(deleteNode()) );
    connect( ui->actionClear, SIGNAL(triggered()), SLOT(clear()) );

    connect( ui->treeWidget, SIGNAL(itemSelectionChanged()), SLOT(updateStates()) );

    updateStates();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStates()
{
    bool isEmptyGraph = ui->treeWidget->topLevelItemCount() == 0;
    ui->actionClear->setEnabled( !isEmptyGraph );

    bool hasSelection = ui->treeWidget->selectionModel()->hasSelection();
    ui->actionDeleteNode->setEnabled( hasSelection );
}
void MainWindow::on_treeWidget_itemChanged( QTreeWidgetItem * item, int column)
{
    Node * node = item->data( 0, Qt::UserRole ).value < Node * > ();
    if ( column == 0 )
        node->setText( item->text( column ) );

    else if ( column == 1 )
        node->fromString( item->text(0), item->text(1) );

    if ( item->checkState(0) == Qt::Checked )
        ui->widget->addNode( node );
    else
        ui->widget->takeNode( node );

    ui->widget->updateGL();
}
void MainWindow::addNode()
{
    QString text = QString( "Вершина %1" ).arg( ui->treeWidget->topLevelItemCount() + 1 );

    Node * node = new Node();
    node->setText( text );
    node->setPos( QPointF( 0.0, 0.0 ) );
    node->setRadius( 20.0 );
    node->setColor( Qt::white );

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
    QVariant pointer = QVariant::fromValue( node );

    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setFlags( flags );
    item->setText( 0, node->text() );
    item->setText( 1, node->toString() );
    item->setData( 0, Qt::UserRole, pointer ); // сохраним указатель на вершину
    item->setCheckState( 0, Qt::Checked );

    ui->treeWidget->addTopLevelItem( item );

    if ( item->checkState(0) == Qt::Checked )
        ui->widget->addNode( node );

    ui->widget->updateGL();
    updateStates();
}
void MainWindow::deleteNode()
{
    int row = ui->treeWidget->currentIndex().row();
    QTreeWidgetItem * item = ui->treeWidget->takeTopLevelItem( row );
    Node * node = item->data( 0, Qt::UserRole ).value < Node * > ();
    delete item;

    ui->widget->removeNode( node );
    ui->widget->updateGL();
    updateStates();
}
void MainWindow::clear()
{
    while ( ui->treeWidget->topLevelItemCount() )
    {
        QTreeWidgetItem * item = ui->treeWidget->takeTopLevelItem(0);
        Node * node = item->data( 0, Qt::UserRole ).value < Node * > ();
        delete item;

        ui->widget->removeNode( node );
    }

    ui->widget->updateGL();
    updateStates();
}
