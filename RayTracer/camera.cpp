//
//  camera.cpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/4/18.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//



#include "camera.h"
#define MAX(a,b) (a)>(b)?(a):(b)

Camera::Camera(){
    pos = vector3(20,80.0,-140);
    u.setPos(1.0, 0, 0);
    v.setPos(0, 1.0, 0);
    w.setPos(0, 0, 1.0);
    distance = 200.0;
    left = -100;
    right = 100;
    top = 100;
    bottom = -100;
}

void Camera::shade(const Light& light, const vector3& intePoint , const vector3& n,RGB& r){
    RGB ret;
    vector3 l = light.pos-intePoint;
    l.normalize();
    double col = MAX(l*n,0);
    r=r*col;

}
void Camera::BFshade(const Light& light, const vector3& intePoint , const vector3& n,const vector3& pos,int pn,RGB& r){
    vector3 l = light.pos-intePoint;
    vector3 v = pos - intePoint;
    l.normalize();
    v.normalize();
    auto h = l+v;
    h.normalize();
    double col = MAX(n*h,0);
    col = pow(col,pn);
    r = r*col;
}

RGB Camera::Reflect(const vector3& intePoint,Light l,const std::vector<Triangle>& t,Triangle& near){
    auto origin = this->pos;
    //auto normal = near.vn;
    //normal.normalize();
    auto reflect = intePoint - origin;
    double ma =-(near.vn*reflect);
    double mb =sqrt(near.vn.lengthSquare());
    auto normal=near.vn*(ma/mb);
    
    //reflect.normalize();
    reflect=reflect+normal*2;
    Triangle nearest;
    double smallt=1/0.0;
    intersect(0.0000000001,intePoint, reflect, t, nearest, smallt);
    RGB ret;
    if(smallt==1/0.0){
        ret.setColor(0, 0, 0);
        return ret;
    }else{
        
    }
    vector3 iPoint(intePoint+reflect*smallt);
    return ColorFromPoint(iPoint,l,t,nearest);
}
bool Camera::intersect(double m,const vector3& origin,vector3& direction,const std::vector<Triangle>& t,Triangle& nearest,double &f){
    double smallt=1/0.0;
    double ru,rv,rt;
    // intersect check
    double mo = m;
    for(auto& tri:t){
        if(IntersectTriangle(origin,direction,tri.v[0],tri.v[1],tri.v[2],&rt,&ru,&rv)){
            if(rt<smallt&&rt>mo){
                smallt=rt;
                nearest = tri;
                
            }
        }
    }
    
    
    f=smallt;
    return true;
}
RGB Camera::ColorFromPoint(const vector3& intePoint,Light l,const std::vector<Triangle>& t,Triangle& nearest){
    if(nearest.getType()==1){
        return Reflect(intePoint, l, t, nearest);
    }
    double rt,ru,rv;
    RGB ret;
    //vector3 intePoint(origin+direction*smallt);
    
    float alpha = ((float)(rand()%256))/256.0;
    float beta = ((float)(rand()%256))/256.0;
    l.pos=l.pos+l.v1*alpha+l.v2*beta;
    auto reflectDir = l.pos-intePoint;
    for(auto& tri:t){
        if(IntersectTriangle(intePoint, reflectDir, tri.v[0], tri.v[1], tri.v[2], &rt, &ru, &rv)){
            if(rt>0.0000000001&&rt<1) {
                return RGB(0,0,0);
            }
        }
    }
    ret=ret+l.color;
    RGB r = nearest.color;
    shade(l,intePoint,nearest.vn,r);
    ret=ret+r;
    r = nearest.sColor;
    BFshade(l, intePoint, nearest.vn, pos, 85, r);
    ret=ret+r;
    return ret;
}
RGB Camera::draw(double x,double y,double nx,double ny,const std::vector<Triangle>& t,const std::vector<Light>& l){
    RGB res(0,0,0);
    
    float rr=0,rg=0,rb=0;
    
    for(int i = 0;i<j1.jN;i++){
        for(int j = 0;j<j1.jN;j++){
            float pX = 2*j1.jitterX[i][j]-1;
            float pY = 2*j1.jitterY[i][j]-1;
            auto m =drawA(x+pX,y+pY,nx,ny,t,l[0]);
            rr+=m.red;rg+=m.green;rb+=m.blue;
        }
    }
    
    rr/=j1.jN*j1.jN;
    rg/=j1.jN*j1.jN;
    rb/=j1.jN*j1.jN;
    
    return RGB(rr,rg,rb);
}
RGB Camera::drawA(double x,double y,double nx,double ny,const std::vector<Triangle>& t,Light l){
    //auto l = la[0];
    vector3 origin = pos;
    
    double U = left+(x+0.5)*(right-left)/nx;
    double V = bottom+(y+0.5)*(top-bottom)/ny;
    
    vector3 direction = w.product(distance)+u.product(U)+v.product(V);
    Triangle nearest;
    
    double smallt=1/0.0;

    
    intersect(0,origin, direction, t, nearest, smallt);
    
    RGB ret;
    if(smallt==1/0.0){
        ret.setColor(0, 0, 0);
        return ret;
    }
    
    vector3 intePoint(origin+direction*smallt);


    return ColorFromPoint(intePoint,l,t,nearest);

}
