//
//  BSpline.cpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/7/4.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#include "BSpline.hpp"
void spline(float t,float r[4]){
    float u2 = t*t;
    float u3 = u2*t;
    for(int i = 0;i<4;i++){
        
        r[i]=m4[0][i]*u3+m4[1][i]*u2+m4[2][i]*t+m4[3][i];
        r[i]/=6;
    }
}
void draw(std::vector<std::vector<int>>& b,vector3 v4[4]){
    float p = 0.01;
    float r[4];
    while(p<1){
        spline(p,r);
        vector3 v = v4[0]*r[0]+v4[1]*r[1]+v4[2]*r[2]+v4[3]*r[3];
        p+=0.01;
        b[(int)v.x][(int)v.y]=true;
    }
}
void generateBSpline(std::vector<std::vector<int>>& b,vector3* v3,int n){
    if(n<3) return;
    int i = n-3;
    for(int j = 0;j<i;j++){
        draw(b,v3+j);
    }
    
}
