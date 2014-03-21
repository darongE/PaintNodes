#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class QTreeWidgetItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void updateStates();
    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);
    void addNode();
    void deleteNode();
    void clear();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
