//
//  director.cpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/4/18.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//



#include "director.h"

Director* Director::_dir=NULL;
Director::Director(){_cam = new Camera();}
Director::~Director(){delete _cam;}
Camera* Director::getCam(){return _cam;}
void Director::addObj(obj* ob){
    int n;
    auto p = ob->getT(n);
    for(int i = 0;i<n;i++) triSet.push_back(p[i]);
}
void Director::addLight(const Light& l){
    lightSet.push_back(l);
}
Director* Director::getDirector(){
    if(_dir==NULL){
        _dir=new Director();
    }
    return _dir;
}
RGB Director::draw(int x,int y,int nx,int ny){
    if(_cam->bTree==NULL) {
        _cam->bTree = new BoundaryTree();
        std::vector<Triangle*> s;
        for(auto& a:triSet){
            s.push_back(&a);
        }
        _cam->bTree->Create(s, 0);
    }
    return _cam->draw(x, y, nx, ny, triSet, lightSet);
}
