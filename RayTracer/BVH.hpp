//
//  BVH.hpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/7/7.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef BVH_hpp
#define BVH_hpp

#include <stdio.h>
#include "object.h"
#endif /* BVH_hpp */
#pragma once
class BoundaryTree{
    
    float x1,x2,y1,y2,z1,z2;
    BoundaryTree* Left=NULL;
    BoundaryTree* Right=NULL;
    Triangle* tw=NULL;
    
public:
    float operator[](int);
    void calcT(const vector3& origin,const vector3& dir,int axis,float& max,float& min);
    bool intersect(float x1,float y1,float x2,float y2);
    void bound(std::vector<Triangle*>& v,float &x1,float &x2,float &y1,float &y2,float &z1,float &z2);
    BoundaryTree()=default;
    bool hit(const vector3& origin,const vector3& dir,float& t,Triangle& rt,float t1,float t2);
    void boundary(Triangle* pT,float &x1,float &x2,float &y1,float &y2,float &z1,float &z2);
    void Intersect(const vector3& origin,const vector3& dir,float &t,float u,float v);
    BoundaryTree(const std::vector<Triangle*>& v);
    void Create(std::vector<Triangle*>& v,int axis);
};
class BVH{
private:
    BoundaryTree btree;
public:
    //void add(Triangle& t);
    void Intersect(const vector3& origin,const vector3& dir,float &t,float u,float v);
    void createBoundary(const std::vector<obj*>& obj);
};
