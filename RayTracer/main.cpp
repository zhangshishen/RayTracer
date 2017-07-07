//
//  main.cpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/4/18.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//



//#include "director.cpp"

#include "2D.h"
#include "director.h"
#include "SolidNoise.hpp"

#include <stdlib.h>
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include "BSpline.hpp"

void myinit(void) {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}
void rayTracerInit(){
    Director* dir = Director::getDirector();
    Light* l = new Light();
    l->setPos(vector3(25,135,25));
    //dir->addLight(*l);
    //l = new Light();
    //l->setPos(vector3(25,55,0));
    //l->v1=vector3(5,0,0);
    //l->v2=vector3(0,5,0);
    dir->addLight(*l);
    //l->setPos(vector3(0,15,-20));
    //dir->addLight(*l);
    obj* obj = new cube(vector3(-15,0,30),35,RGB(100,0,0));
    dir->addObj(obj);
    obj = new cube(vector3(50,0,30),35,RGB(0,100,0));
    dir->addObj(obj);
    obj = new cube(vector3(-15,35,30),35,RGB(100,0,0));
    dir->addObj(obj);
    obj = new mirror(vector3(-30,25,99.99999),vector3(80,125,99.99999),vector3(0,0,-1),RGB(100,0,0));
    dir->addObj(obj);
    obj= new wall(vector3(-50,0,-50),vector3(100,0,100),vector3(0,1,0),RGB(0,100,0));//bottom
    dir->addObj(obj);
    obj = new wall(vector3(-50,0,-50),vector3(-50,150,100),vector3(1,0,0),RGB(100,0,0));//left
    dir->addObj(obj);
    //obj= new wall(vector3(20,1,20),vector3(40,1,40),vector3(0,1,0),RGB(0,0,50));
    obj = new wall(vector3(100,0,-50),vector3(100,150,100),vector3(-1,0,0),RGB(100,0,0));//right
    dir->addObj(obj);
    obj = new wall(vector3(-50,0,100),vector3(100,150,100),vector3(0,0,-1),RGB(0,100,0));//back
    //obj = new sphere(vector3(30,15,15),15,RGB(111,0,0));
    dir->addObj(obj);
    obj = new wall(vector3(-50,150,-50),vector3(100,150,100),vector3(0,-1,0),RGB(0,100,0));//top
    dir->addObj(obj);
    obj = new wall(vector3(15,149.999,15),vector3(35,149.999,35),vector3(0,-1,0),RGB(110,110,110));//light
    //obj = new wall(vector3(-50,0,-50),vector3(100,150,-50),vector3(0,0,1),RGB(0,50,0));
    dir->addObj(obj);
}
std::vector<std::vector<float>> fa(500,std::vector<float>(500,0.5));
void SolidDisplay(){
    typedef GLfloat point2[2];
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i = 0;i<500;i++){
        for(int j = 0;j<500;j++){
//            
//            auto pa = (m[i][j]+1)*0.5;
            int c = 90;
////            c*=pa;
            c*=fa[i][j];
            glColor3b(c,c,c);
            glBegin(GL_POINTS);
            point2 p;
            p[0]=i,p[1]=j;
            glVertex2fv(p);
            glEnd();
        }
    }
    glFlush();
}
void display(void) {
    
    typedef GLfloat point2[2];
    point2 p = {0.0, 0.0};
    //glColor3b(100, 100, 100);
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i = 0;i<500;i++){
        for(int j = 0;j<500;j++){
            auto _dir = Director::getDirector();
            auto color = _dir->draw(i, j, 500, 500);
            p[0]=i;p[1]=j;
            glColor3b(color.red, color.green, color.blue);
            glBegin(GL_POINTS);
            glVertex2fv(p);
            glEnd();
        }
    }
    glFlush();
}
void SPLine(void){
    typedef GLfloat point2[2];
    point2 p = {0.0, 0.0};
    vector3 v3[10]={{100,50,0},{125,110,0},{150,50,0},{175,110,0},{200,50,0},{225,110,0},{250,50,0},{275,110,0},{300,50,0},{325,110,0}};
    std::vector<std::vector<int>> s(500,std::vector<int>(500));
    for(auto&m:v3){
        s[m.x][m.y]=2;
    }
    generateBSpline(s, v3, 10);
    //glColor3b(100, 100, 100);
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i = 0;i<500;i++){
        for(int j = 0;j<500;j++){
            //auto _dir = Director::getDirector();
            //auto color = _dir->draw(i, j, 500, 500);
            p[0]=i;p[1]=j;
            if(s[i][j]==true)
                glColor3b(111, 111, 111);
            else if(s[i][j]==2)glColor3b(100, 0, 0);
            else glColor3b(0, 0, 0);
            glBegin(GL_POINTS);
            glVertex2fv(p);
            glEnd();
        }
    }
    glFlush();
}
int main(int argc, char **argv) {
    
    vector3 dir(-4,-7,20),origin(0,20,-20),v1(-10,0,20),v2(-10,0,40),v3(-10,20,20);
    double x,y,z;
    fa = SolidNoise(500,500);
    rayTracerInit();
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Sierpinski Gasket");
    glutDisplayFunc (SPLine);
    myinit();
    glutMainLoop();
}
