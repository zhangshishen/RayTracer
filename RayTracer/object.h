//
//  object.h
//  RayTracer
//
//  Created by Shishen Zhang on 2017/4/19.
//  Copyright © 2017年 Shishen Zhang. All rights reserved.
//

#ifndef object_h
#define object_h

#include "camera.h"
#include "math.h"
#define SPHERELONG 10
#define SPHERELA 23
#define PI 3.14159265
#endif /* object_h */
class obj{
public:
    enum type{solid,mirror};
    virtual Triangle* getT(int &n)=0;
    virtual enum type getType()=0;
    RGB specularColor;
    obj();
};
class sphere:public obj{
public:
    Triangle triangle[SPHERELA*2*SPHERELONG*2];
    int index = 0;
    float radius;
    vector3 pos;
    RGB rgb;
    virtual Triangle* getT(int &n);
    float radiusSize[SPHERELONG];
    float latitudeInteval[SPHERELA];
    std::vector<vector3> v3;
    enum type getType(){return solid;}
    void normalCalc(){
        for(int i = 0;i<SPHERELA*2*SPHERELONG*2;i++){
            triangle[i].vn = (triangle[i].v[1]-triangle[i].v[0]).cross((triangle[i].v[2]-triangle[i].v[0]));
            triangle[i].vn.normalize();
            triangle[i].vn = -triangle[i].vn;
            triangle[i].color = rgb;
        }
    }
    sphere(vector3 pos,float radius,RGB rgb){
        this->rgb=rgb;
        this->pos = pos;
        this->radius = radius;
        for(int i = 0;i<SPHERELONG;i++){
//            float m = sinf(PI/(4.0));
            radiusSize[i] = radius*sinf((PI/(2.0*(float)SPHERELONG))*(float)(i+1));
            latitudeInteval[i]=radius*(1.0-cosf((PI/(2.0*(float)SPHERELONG))*(float)(i+1)));
        }
        float za =pos.z;
        float xa = pos.x;
        float ya = pos.y+radius;
        for(int i = 0;i<SPHERELONG;i++){
            xa = pos.x-radiusSize[i];
            ya = pos.y+radius-latitudeInteval[i];
            vector3 start(xa,ya,za);
            for(int j = 0;j<SPHERELA;j++){
                //sinf((PI/SPHERELA)*j)*radiusSize[i];
                start.z=pos.z+sinf((2*PI/SPHERELA)*j)*radiusSize[i];
                start.x=pos.x-cosf((2*PI/SPHERELA)*j)*radiusSize[i];
                v3.push_back(start);
            }
        }
        for(int i = 1;i<SPHERELONG;i++){
            xa = pos.x-radiusSize[SPHERELONG-i-1];
            ya = pos.y-radius+latitudeInteval[SPHERELONG-i-1];
            vector3 start(xa,ya,za);
            for(int j = 0;j<SPHERELA;j++){
                //sinf((PI/SPHERELA)*j)*radiusSize[i];
                start.z=pos.z+sinf((2*PI/SPHERELA)*j)*radiusSize[SPHERELONG-i-1];
                start.x=pos.x-cosf((2*PI/SPHERELA)*j)*radiusSize[SPHERELONG-i-1];
                v3.push_back(start);
            }
        }
        generateTriangle();
    }
    void generateTriangle(){
        vector3 start(pos.x,pos.y+radius,pos.z);
        vector3 end(pos.x,pos.y-radius,pos.z);
        int endindex = v3.size()-SPHERELA;
        for(int i = 0;i<SPHERELA;i++){
            triangle[index].v[0]=start;
            triangle[index].v[2]=v3[i];
            triangle[index].v[1]=v3[(i+1)%SPHERELA];
            index++;
            triangle[index].v[0]=end;
            triangle[index].v[2]=v3[endindex+(i+endindex+1)%SPHERELA];
            triangle[index].v[1]=v3[i+endindex];
            index++;
        }
        int startIndex = 0;
        for(int i = 0;i<2*(SPHERELONG-1);i++){
            startIndex=SPHERELA*i;
            for(int j = 0;j<SPHERELA;j++){
                generateTriangleByRect(v3[startIndex+j],v3[startIndex+(j+1)%SPHERELA],v3[startIndex+SPHERELA+j],v3[startIndex+(j+1)%SPHERELA+SPHERELA]);
            }
        }
        normalCalc();
    }
    void generateTriangleByRect(vector3& v1,vector3& v2,vector3& v3, vector3& v4){
        triangle[index].v[0]=v1;
        triangle[index].v[1]=v4;
        triangle[index].v[2]=v3;
        triangle[index+1].v[0]=v1;
        triangle[index+1].v[1]=v2;
        triangle[index+1].v[2]=v4;
        index+=2;
    }
//    std::vector<Triangle> belt(vector3 center,float z,vector3 start,vector3 end){
//        
//    }
};
class cube :public obj{
public:
    Triangle triangle[12];
    virtual Triangle* getT(int &n);
    enum type getType(){return solid;}
    cube(vector3 p1,double size,RGB rgb);
    cube();
};

class wall :public obj{
public:
    Triangle triangle[2];
    virtual Triangle* getT(int& n);
    enum type getType(){return solid;}
    wall(vector3 v1,vector3 v2,vector3 dir,RGB rgb);
};
class mirror:public wall{
public:
    enum type getType(){return obj::mirror;}
    mirror(vector3 v1,vector3 v2,vector3 dir,RGB rgb):wall(v1,v2,dir,rgb){
        triangle[0].type=1;triangle[1].type=1;
    }
};
