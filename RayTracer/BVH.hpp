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
#include "3DObject.h"
#include "object.h"
#endif /* BVH_hpp */

class BoundaryTree{
    float x1,x2,y1,y2,z1,z2;
    BoundaryTree* Left;
    BoundaryTree* Right;
    Triangle* t;
public:
    void bondary(Triangle* pT,float &x1,float &x2,float &y1,float &y2,float &z1,float &z2);
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
