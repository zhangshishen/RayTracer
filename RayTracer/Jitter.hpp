//
//  Jitter.hpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/6/28.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef Jitter_hpp
#define Jitter_hpp

#include <stdio.h>
#include "random"
#endif /* Jitter_hpp */

#define N 1
class Jitter{
public:
    int jN = N;
    float jitterX[N][N];
    float jitterY[N][N];
    Jitter();
    void create();
};
