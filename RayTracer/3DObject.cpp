//
//  3DObject.cpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/4/18.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//



#include "3DObject.h"

RGB::RGB(){red=green=blue=0;}
RGB::RGB(unsigned char r,unsigned char g,unsigned char b):red(r),green(g),blue(b){}
RGB RGB::operator+(const RGB& rgb) const{
    RGB ret;
    if(red+rgb.red>=128)
        ret.red = 127;
    else ret.red=red+rgb.red;
    if(green+rgb.green>=128)
        ret.green = 127;
    else ret.green=green+rgb.green;
    if(blue+rgb.blue>=128)
        ret.blue = 127;
    else ret.blue=blue+rgb.blue;
    return ret;
}
void RGB::setColor(unsigned char r,unsigned char g,unsigned char b){
    red = r;
    green = g;
    blue = b;
}

RGB RGB::operator*(double d) const{
    RGB ret;
    if(red*d>red) ret.red = 255;
    else ret.red=red*d;
    if(green*d>green) ret.green = 255;
    else ret.green=green*d;
    if(blue*d>blue) ret.blue = 255;
    else ret.blue=blue*d;
    return ret;
}


vector3 vector3::operator+(const vector3& a) const{
    vector3 ret;
    ret.setPos(a.x+x, a.y+y, a.z+z);
    return ret;
}
vector3 vector3::cross(const vector3 &a) const{
    vector3 ret;
    ret.x = y*a.z-z*a.y;
    ret.y = z*a.x-x*a.z;
    ret.z = x*a.y-y*a.x;
    return ret;
}
vector3 vector3::operator-(const vector3& a) const{
    vector3 ret;
    ret.setPos(x-a.x, y-a.y, z-a.z);
    return ret;
}
double vector3::operator[](int a) const{
    if(a==0) return x;
    if(a==1) return y;
    else return z;
}
bool vector3::isZero(){
    return (x==0.0)&&(y==0.0)&&(z==0.0);
}
void vector3::normalize(){
    double m = x*x+y*y+z*z;
    m=sqrt(m);
    x=x/m;
    y/=m;
    z/=m;
}
vector3 vector3::operator-(){
    vector3 ret;
    ret.setPos(-x, -y, -z);
    return ret;
}
vector3 vector3::product(double a) const{
    vector3 ret;
    ret.setPos(a*x, a*y, a*z);
    return ret;
}
vector3 vector3::operator*(double a) const{
    vector3 ret;
    ret.setPos(a*x, a*y, a*z);
    return ret;
}
vector3& vector3::operator=(const vector3& v){
    x=v.x;
    y=v.y;
    z=v.z;
    return *this;
}
bool vector3::operator==(const vector3& v) const{
    return (this->x==v.x)&&(this->y==v.y)&&(this->z==v.z);
}

double vector3::operator*(const vector3& a) const{
    return a.x*x+a.y*y+a.z*z;
}
double vector3::lengthSquare(){
    return x*x+y*y+z*z;
}


Object::Object(){
    
}
void Object::setPos(const vector3& v){
    pos = v;
}
bool IntersectTriangle(const vector3& orig, const vector3& dir,
                       const vector3& v0, const vector3& v1, const vector3& v2,
                       double* t, double* u, double* v)
{
    // E1
    vector3 E1 = v1 - v0;
    
    // E2
    vector3 E2 = v2 - v0;
    
    // P
    vector3 P = dir.cross(E2);
    
    // determinant
    double det = E1*P;
    
    // keep det > 0, modify T accordingly
    vector3 T;
    if( det >0 )
    {
        T = orig - v0;
    }
    else
    {
        T = v0 - orig;
        det = -det;
    }
    if( det < 0.0001 )
        return false;
    *u = T*P;
    if( *u < 0.0 || *u > det )
        return false;
    vector3 Q = T.cross(E1);
    *v = dir*Q;
    if( *v < 0.0 || *u + *v > det )
        return false;
    *t = E2*Q;
    
    double fInvDet = 1.0 / det;
    *t *= fInvDet;
    *u *= fInvDet;
    *v *= fInvDet;
    
    return true;
}



Triangle::Triangle(vector3& v1,vector3& v2,vector3& v3,RGB& rgb){
    v[0]=v1,v[1]=v2,v[2]=v3;
    vn=(v2-v1).cross(v3-v1);
    color=rgb;
    vn.normalize();
    
}
bool Triangle::operator==(const Triangle& t) const{
    return(this->v[0]==t.v[0])&&(this->v[1]==t.v[1])&&(this->v[2]==t.v[2]);
}
void Triangle::setColor(RGB rgb){color=rgb;}
void Triangle::setPos(vector3& v1,vector3& v2,vector3& v3){
    v[0]=v1,v[1]=v2,v[2]=v3;
    vn=(v2-v1).cross(v3-v1);
    vn.normalize();
}
Triangle::Triangle(){}
void Triangle::setDirection (const vector3& dir){
    if(dir*vn<0)
        vn=-vn;
}


