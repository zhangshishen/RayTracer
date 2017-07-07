//
//  Jitter.cpp
//  RayTracer
//
//  Created by Shishen Zhang on 2017/6/28.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#include "Jitter.hpp"
void Jitter::create(){
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            float x = rand()%256;
            float y = rand()%256;
            jitterX[i][j] = x/256.0;
            jitterX[i][j] = y/256.0;
        }
    }
}
Jitter::Jitter(){
    create();
}
