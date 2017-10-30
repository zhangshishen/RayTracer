//
//  director.h
//  RayTracer
//
//  Created by Shishen Zhang on 2017/4/19.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef director_h
#define director_h

#include "3DObject.h"
#include "object.h"
#include "camera.h"
#endif /* director_h */
class Director{
private:
    static Director* _dir;
    Camera* _cam;
    Director();
    std::vector<Triangle> triSet;
    std::vector<Light> lightSet;
    
public:
    ~Director();
    Camera* getCam();
    void addObj(obj* ob);
    void addLight(const Light& l);
    static Director* getDirector();
    RGB draw(int x,int y,int nx,int ny);
};
