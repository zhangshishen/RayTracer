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

void BoundaryTree::calcT(const vector3& origin,const vector3& dir,int axis,float& max,float& min){
    float d=1/dir[axis],m2,m1;
    if(axis==0) {m2=x2;m1=x1;}
    else if(axis==1) {m2=y2;m1=y1;}
    else {m2=z2;m1=z1;}
    if(d>=0){
        max = (m2-origin[axis])*d;
        min = (m1-origin[axis])*d;
    }else{
        min = (m2-origin[axis])*d;
        max = (m1-origin[axis])*d;
    }
}

inline bool BoundaryTree::intersect(float x1,float x2,float y1,float y2){
    if(x1>y2||y1>x2) return false;
    return true;
}

bool BoundaryTree::hit(const vector3& origin,const vector3& dir,float& ta,Triangle& rt,float mi,float ma){
    float t,u,v;
    if(Left==NULL&&Right==NULL){
        if(!IntersectTriangle(origin, dir,
                               this->tw->v[0], this->tw->v[1], this->tw->v[2],
                              &t, &u, &v)) return false;
        ta=t;
        if(t>mi&&t<ma) {rt = *tw;return true;}
        return false;
    }
    
    float txmax,txmin,tymax,tymin,tzmax,tzmin;
    float xd = dir.x,yd=dir.y;
    
    calcT(origin,dir,0,txmax,txmin);
    calcT(origin,dir,1,tymax,tymin);
    calcT(origin,dir,2,tzmax,tzmin);
    bool m = (intersect(txmin,txmax,tymin,tymax)&&intersect(txmin,txmax,tzmin,tzmax)&&intersect(tymin,tymax,tzmin,tzmax));
    if(m==false) return false;
    
    float t1,t2;
    Triangle tem1,tem2;
    auto m1 = Left->hit(origin,dir,t1,tem1,mi,ma);
    auto m2 = Right->hit(origin,dir,t2,tem2,mi,ma);
    bool res = false;
    if(m1&&m2&&t1>mi&&t1<ma&&t2>mi&&t2<ma){
        if(t1>t2) rt=tem2;
        else rt =tem1;
        ta = t1>t2?t2:t1;
        return true;
    }else if(m1&&t1>mi&&t1<ma) {ta=t1;rt=tem1;return true;}
    else if(m2&&t2>mi&&t2<ma) {ta=t2;rt=tem2;return true;}
    else return false;
    
    
}

void BoundaryTree::bound(std::vector<Triangle*>& v,float &x1,float &x2,float &y1,float &y2,float &z1,float &z2){
    boundary(v[0],x1,x2,y1,y2,z1,z2);
    for(auto m:v){
        float a,b,c,d,e,f;
        boundary(m,a,b,c,d,e,f);
        if(a<x1) x1=a;
        if(b>x2) x2=b;
        if(c<y1) y1=c;
        if(d>y2) y2=d;
        if(e<z1) z1=e;
        if(f>z2) z2=f;
    }
}

void BoundaryTree::boundary(Triangle* pT,float &x1,float &x2,float &y1,float &y2,float &z1,float &z2){
    
    x2=std::max(std::max(pT->v[0].x,pT->v[1].x),pT->v[2].x);
    x1 = std::min(std::min(pT->v[0].x,pT->v[1].x),pT->v[2].x);
    y2=std::max(std::max(pT->v[0].y,pT->v[1].y),pT->v[2].y);
    y1 = std::min(std::min(pT->v[0].y,pT->v[1].y),pT->v[2].y);
    z2=std::max(std::max(pT->v[0].z,pT->v[1].z),pT->v[2].z);
    z1 = std::min(std::min(pT->v[0].z,pT->v[1].z),pT->v[2].z);
    
}
void BoundaryTree::Create(std::vector<Triangle*>& v,int axis){
    axis%=3;
    bound(v,x1,x2,y1,y2,z1,z2);
    if(v.size()==1){
        Left=NULL,Right=NULL;
        tw=v[0];
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
    
    int mid = v.size()/2;
    std::vector<Triangle*> v1(v.begin(),v.begin()+mid);
    std::vector<Triangle*> v2(v.begin()+mid,v.end());
    
    if(v1.size()>0){
        Left = new BoundaryTree();
        Left->Create(v1, axis+1);
    }
    
    if(v2.size()>0){
        Right = new BoundaryTree();
        Right->Create(v2, axis+1);
    }
    
    
}
