//
//  3DObject.h
//  RayTracer
//
//  Created by Shishen Zhang on 2017/4/19.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef _DObject_h
#define _DObject_h

#include "vector"
#include "math.h"
#endif /* _DObject_h */
#pragma once
class RGB{
public:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    RGB();
    void setColor(unsigned char r,unsigned char g,unsigned char b);
    RGB(unsigned char r,unsigned char g,unsigned char b);
    RGB operator+(const RGB& rgb) const;
    RGB operator*(double d) const;
};


typedef float Matrix4[4][4];
class wall;
class vector3{
public:
    double x;
    double y;
    double z;
    friend wall;
public:
    vector3(){};
    void setPos(double x,double y,double z){this->x=x;this->y=y;this->z=z;}
    vector3(double x,double y,double z):x(x),y(y),z(z){};
    vector3 operator+(const vector3& a) const;
    vector3 cross(const vector3 &a) const;
    vector3 operator-(const vector3& a) const;
    
    bool isZero();
    void normalize();
    bool operator==(const vector3&) const;
    vector3 operator-();
    vector3 product(double a) const;
    vector3 operator*(double a) const;
    vector3& operator=(const vector3& v);
    
    double operator*(const vector3& a) const;
    double lengthSquare();
    
};

class Object{
public:
    vector3 pos;
public:
    Object();
    void setPos(const vector3& v);
};
bool IntersectTriangle(const vector3& orig, const vector3& dir,
                       const vector3& v0, const vector3& v1, const vector3& v2,
                       double* t, double* u, double* v);

class Triangle{
public:
    vector3 v[3];
    vector3 vn;
    int getType(){return type;}
    RGB color;
    int type = 0;
    RGB sColor;
    bool operator==(const Triangle&) const;
    Triangle(vector3& v1,vector3& v2,vector3& v3,RGB& rgb);
    void setColor(RGB rgb);
    void setPos(vector3& v1,vector3& v2,vector3& v3);
    Triangle();
    void setDirection (const vector3& dir);
};
