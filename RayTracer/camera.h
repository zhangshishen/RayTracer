//
//  camera.h
//  RayTracer
//
//  Created by Shishen Zhang on 2017/4/19.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef camera_h
#define camera_h


#endif /* camera_h */
#include "BVH.hpp"
#include "3DObject.h"
#include "Jitter.hpp"
#include "BVH.hpp"

class wall;
class Light :public Object{
public:
    enum {pointLight,parallelLight};
    RGB color;
    vector3 dir;
    float intensity;
    vector3 v1;
    vector3 v2;
    //void set(vector3& x);
    Light(){pos = vector3(0,10,0);v1=vector3(10,0,0);v2=vector3(0,0,10);}
};

class Director;
class Camera{
    Jitter j1;
    BoundaryTree* bTree=NULL;
    Jitter j2;
    friend Director;
    vector3 pos;
    vector3 u,v,w;
    float left;
    float right;
    float top;
    float bottom;
    float distance;
    Camera();
    bool intersect(float m,const vector3& origin,vector3& direction,const std::vector<Triangle>& t,Triangle& nearest,float& f);
    RGB Reflect(const vector3& intePoint,Light l,const std::vector<Triangle>& t,Triangle& nearest);
    RGB ColorFromPoint(const vector3& eye,Light l,const std::vector<Triangle>& t,Triangle& nearest);
    RGB drawA(float x,float y,float nx,float ny,const std::vector<Triangle>& t,Light l);
    bool isIntersect(const std::vector<Triangle>& t,vector3& origin,vector3& dir);
    float shade(float x,float y,float nx,float ny,Light l,const std::vector<Triangle>& t);
    void shade(const Light&,const vector3&,const vector3&,RGB&);
    void BFshade(const Light&,const vector3&,const vector3&,const vector3&,int pn,RGB& r);
    friend Director;
    RGB draw(float x,float y,float nx,float ny,const std::vector<Triangle>& t,const std::vector<Light>& l);
    //bool softShade(float jx,float jy,float alpha,float beta,float x,float y,float nx,float ny,const std::vector<Triangle>& t,Light light);
};
