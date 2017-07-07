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
    double x;
    double y;
};
double determinant(double v1, double v2, double v3, double v4);  // 行列式

bool intersect3(Point aa, Point bb, Point cc, Point dd);
