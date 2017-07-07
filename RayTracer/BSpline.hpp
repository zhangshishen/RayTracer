//
//  BSpline.hpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/7/4.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef BSpline_hpp
#define BSpline_hpp

#include <stdio.h>
#include "3DObject.h"
#endif /* BSpline_hpp */
const Matrix4 m4={{-1,3,-3,1},{3,-6,3,0},{-3,0,3,0},{1,4,1,0}};
//const Matrix4 m4={{1,0,0,0},{-3,3,0,0},{3,-6,3,0},{-1,3,-3,1}};
void spline(float t,float r[4]);
void draw(std::vector<std::vector<int>>& b,vector3 v4[4]);
void generateBSpline(std::vector<std::vector<int >>& b,vector3* v3,int n);
