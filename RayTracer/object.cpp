//
//  object.cpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/4/18.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//


#include "object.h"

obj::obj(){
    this->specularColor = {255,255,255};
}
Triangle* cube::getT(int &n) {
    n=12;
    return triangle;
}
Triangle* sphere::getT(int &n){
    n = SPHERELA*2*SPHERELONG*2;
    return triangle;
}
cube::cube(){}
cube::cube(vector3 p1,double size,RGB rgb){
    vector3 center = p1+vector3(size/2,size/2,size/2);
    vector3 p2 = p1+vector3(size,0,0);
    vector3 p3 = p1+vector3(size,0,size);
    vector3 p4 = p1+vector3(0,0,size);
    vector3 p5 = p1+vector3(0,size,0);
    vector3 p7 = p1+vector3(size,size,size);
    vector3 p6 = p1+vector3(size,size,0);
    vector3 p8 = p1+vector3(0,size,size);
    
    triangle[0].setPos(p1, p2, p3);
    triangle[0].setDirection(p1-center);
    triangle[1].setPos(p1, p4, p3);
    triangle[1].setDirection(p1-center);
    
    triangle[2].setPos(p2, p3, p6);
    triangle[2].setDirection(p2-center);
    triangle[3].setPos(p3, p6, p7);
    triangle[3].setDirection(p2-center);
    
    triangle[4].setPos(p2, p5, p6);
    triangle[4].setDirection(p2-center);
    triangle[5].setPos(p1, p2, p5);
    triangle[5].setDirection(p2-center);
    
    triangle[6].setPos(p1, p4, p5);
    triangle[6].setDirection(p4-center);
    triangle[7].setPos(p4, p5, p8);
    triangle[7].setDirection(p4-center);
    
    triangle[8].setPos(p3, p4, p7);
    triangle[8].setDirection(p4-center);
    triangle[9].setPos(p4, p7, p8);
    triangle[9].setDirection(p4-center);
    
    triangle[10].setPos(p6, p7, p8);
    triangle[10].setDirection(p6-center);
    triangle[11].setPos(p5, p6, p8);
    triangle[11].setDirection(p6-center);
    for(int i = 0;i<12;i++) {
        triangle[i].sColor={255,255,255};
        triangle[i].setColor(rgb);
    }
}

Triangle* wall::getT(int& n){
    n=2;
    return triangle;
}

wall::wall(vector3 v1,vector3 v2,vector3 dir,RGB rgb){
    vector3 v3,v4;
    if(v1.y==v2.y){
        v3.setPos(v1.x, v1.y, v2.z);
        v4.setPos(v2.x, v2.y, v1.z);
    }
    else{
        v3.setPos(v1.x, v2.y, v1.z);
        v4.setPos(v2.x, v1.y, v2.z);
    }
    triangle[0].setPos(v1, v2, v3);
    triangle[0].setDirection(dir);
    triangle[0].setColor(rgb);
    
    triangle[1].setPos(v1, v2, v4);
    triangle[1].setDirection(dir);
    triangle[1].setColor(rgb);
}

