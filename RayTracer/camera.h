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
#include "3DObject.h"
#include "Jitter.hpp"
class wall;
class Light :public Object{
public:
    enum {pointLight,parallelLight};
    RGB color;
    vector3 dir;
    double intensity;
    vector3 v1;
    vector3 v2;
    //void set(vector3& x);
    Light(){pos = vector3(0,10,0);v1=vector3(10,0,0);v2=vector3(0,0,10);}
};

class Director;
class Camera{
    Jitter j1;
    Jitter j2;
    friend Director;
    vector3 pos;
    vector3 u,v,w;
    double left;
    double right;
    double top;
    double bottom;
    double distance;
    Camera();
    bool intersect(double m,const vector3& origin,vector3& direction,const std::vector<Triangle>& t,Triangle& nearest,double& f);
    RGB Reflect(const vector3& intePoint,Light l,const std::vector<Triangle>& t,Triangle& nearest);
    RGB ColorFromPoint(const vector3& eye,Light l,const std::vector<Triangle>& t,Triangle& nearest);
    RGB drawA(double x,double y,double nx,double ny,const std::vector<Triangle>& t,Light l);
    bool isIntersect(const std::vector<Triangle>& t,vector3& origin,vector3& dir);
    float shade(double x,double y,double nx,double ny,Light l,const std::vector<Triangle>& t);
    void shade(const Light&,const vector3&,const vector3&,RGB&);
    void BFshade(const Light&,const vector3&,const vector3&,const vector3&,int pn,RGB& r);
    friend Director;
    RGB draw(double x,double y,double nx,double ny,const std::vector<Triangle>& t,const std::vector<Light>& l);
    //bool softShade(float jx,float jy,float alpha,float beta,double x,double y,double nx,double ny,const std::vector<Triangle>& t,Light light);
};
