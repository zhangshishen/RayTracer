//
//  BVH.cpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/7/7.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#include "BVH.hpp"
#define MAX3(a,b,c)
void BVH::createBoundary(const std::vector<obj*>& obj){
    std::vector<Triangle*> v;

    for(auto p:obj){
        int n;
        auto m = p->getT(n);
        while(n) {v.push_back(m+n-1);n--;}
    }
    btree.Create(v, 1);
}
void BoundaryTree::bondary(Triangle* pT,float &x1,float &x2,float &y1,float &y2,float &z1,float &z2){

    
    
}
void BoundaryTree::Create(std::vector<Triangle*>& v,int axis){
    axis%=3;
    
    if(v.size()==1){
        Left=NULL,Right=NULL;
        t=v[0];
        return;
    }
    sort(v.begin(),v.end(),
         [axis](const Triangle* t1,const Triangle* t2){
             
             float max1 = std::max(std::max(t1->v[0][axis],t1->v[1][axis]),t1->v[2][axis]);
             float min1 = std::min(std::min(t1->v[0][axis],t1->v[1][axis]),t1->v[2][axis]);
             
             float max2 = std::max(std::max(t2->v[0][axis],t2->v[1][axis]),t2->v[2][axis]);
             float min2 = std::min(std::min(t2->v[0][axis],t2->v[1][axis]),t2->v[2][axis]);
             
             return (max1+min1)<(max2+min2);
         }
         );
}
