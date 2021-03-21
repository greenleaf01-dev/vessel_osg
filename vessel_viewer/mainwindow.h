#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
    void onSave();
    void onLoad();

    void switchLayoutDirection();
    void setDockOptions();
private:
    void setupMenuBar();
    void setupDockWidgets();
};

#endif // MAINWINDOW_H
