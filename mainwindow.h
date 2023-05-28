#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <vector>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Object;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void Simulation();
    void Output(std::string s);

    std::vector <Object*> Create_UserEquipment(int mapx, int mapy, double latA, double lonA, double scale);
    void randomwalk_objs(std::vector <Object*> *objs, int mapx, int mapy);
};
#endif // MAINWINDOW_H
