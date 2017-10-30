//
//  2D.h
//  RayTracer
//
//  Created by Shishen Zhang on 2017/4/19.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef _D_h
#define _D_h


#endif /* _D_h */
struct Point{
    float x;
    float y;
};
float determinant(float v1, float v2, float v3, float v4);  // 行列式

bool intersect3(Point aa, Point bb, Point cc, Point dd);
