//
//  2D.cpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/4/18.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#include "2D.h"

float determinant(float v1, float v2, float v3, float v4)  // 行列式
{
    return (v1*v3-v2*v4);
}

bool intersect3(Point aa, Point bb, Point cc, Point dd)
{
    float delta = determinant(bb.x-aa.x, cc.x-dd.x, bb.y-aa.y, cc.y-dd.y);
    if ( delta<=(1e-6) && delta>=-(1e-6) )  // delta=0，表示两线段重合或平行
    {
        return false;
    }
    float namenda = determinant(cc.x-aa.x, cc.x-dd.x, cc.y-aa.y, cc.y-dd.y) / delta;
    if ( namenda>1 || namenda<0 )
    {
        return false;
    }
    float miu = determinant(bb.x-aa.x, cc.x-aa.x, bb.y-aa.y, cc.y-aa.y) / delta;
    if ( miu>1 || miu<0 )
    {
        return false;
    }
    return true;
}
