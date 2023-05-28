#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <ctime>

#include "coordinates.hpp"
#include "Object.hpp"
#include "UserEquipment.hpp"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textBrowser_output->setHtml(" <div> Init window </div> ");
    Simulation();
}

void MainWindow::Simulation(){

    int size_x = 1000, size_y = 1000;
    double latA = 55.084656, lonA = 82.4626;
    double latB = 54.874631, lonB = 82.8410;
    vector <Object*> objs;
    double scale = (lonB - lonA)/(double)size_x;
    objs = Create_UserEquipment(size_x, size_y, latA, latB, scale);
    randomwalk_objs(&objs, size_x, size_y);


    Output("End program\n");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::Output(string s){
    std::string s2 = ui->textBrowser_output->toHtml().toStdString() + " <div> " + s + " </div> ";
    ui->textBrowser_output->setHtml(QString::fromStdString(s2));
}


vector <Object*> MainWindow::Create_UserEquipment(int mapx, int mapy, double latA, double lonA, double scale){
    int count = 5;
    vector <Object*> obj;
    Object *newobj;
    int i, i2;
    int id;
    int create_id;
    double pos_lat, pos_lon;
    for(i = 0; i < count; ++i){
        create_id = 0;
        while(create_id != 1){
            create_id = 1;
            id = 99 + (rand() % 10000);
            for(i2 = 0; i2 < i; ++i2){
                if(id == obj[i2]->get_id()){
                    create_id = 0;
                    break;
                }
            }
        }
        //cout<<"id = "<<id<<endl;
        Output("id = " + to_string(id) + "\n");
        pos_lat = latA + (rand() % mapx) * scale;
        pos_lon = lonA + (rand() % mapy) * scale;
        newobj = new UserEquipment(id, pos_lat, pos_lon, scale);
        obj.push_back(newobj);
    }
    return obj;
}


void MainWindow::randomwalk_objs(vector <Object*> *objs, int mapx, int mapy){
    int count = 5;

    int i, i2;
    for(i = 0; i < count; ++i){
        Output("iteration: " + to_string(i) + "\n");

        for(i2 = 0; i2 < objs->size(); ++i2){
            objs->at(i2)->randomwalk(mapx, mapy);
            Output("\tid = " + to_string(objs->at(i2)->get_id()) + \
                "\tlat = " + to_string(objs->at(i2)->get_position()->get_lat()) + \
                "\tlon = " + to_string(objs->at(i2)->get_position()->get_lon()) + "\n");
        }
    }
    Object *ptr, *ptr2;
    for(i2 = 0; i2 < objs->size(); ++i2){
        ptr = objs->at(i2);
        Output("id - " + to_string(ptr->get_id()) + "\n");
        Output("\tpath = " + to_string(ptr->get_path()) + "\n");
        Output("\tcount point = " + to_string(ptr->get_count_point()) + "\n");
        Output("\tpath to \n");

        for(i = 0; i < objs->size(); ++i){
            if(i != i2){
                ptr2 = objs->at(i);
                Output("\t\t[id - " + to_string(ptr2->get_id()) + "] = " + to_string(ptr->get_path_coord(ptr2->get_position())) + "\n");
            }
        }
    }

    Output("End iteratrion move\n");
}






