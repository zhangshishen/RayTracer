#include "SolidNoise.hpp"
#define INTERVAL 50

vector3 randomVector(){     //随机向量生成,
    
    float m = rand()%256;
    
    float n = rand()%256;
    
    float x = m/256.0;
    
    x = 2*x-1;
    
    float y = n/256.0;
    
    y = 2*y-1;
    
    vector3 res(x,y,0);
    
    if(res.lengthSquare()>1){
        
        return randomVector();
        
    }else {
        
        res.normalize();
        
        return res;
        
    }
    
};


float weight(float t){      //插值参数 6t^5-15t^4+10t^3
    
    return t * t * t * (t * (t * 6 - 15) + 10);
//    return t;
    
}


float leap(float x,float y,float z){    //插值
    
    return x+z*(y-x);
    
}

float effect(int i,int j,const std::vector<std::vector<vector3>>& v){   //计算顶点值
    
    if(i%INTERVAL==0&&i!=0) {
        
        //return 0;
        
    }
    
    int m = i%INTERVAL;     //网格内部坐标
    
    int n = j%INTERVAL;
    
    int x = i/INTERVAL;     //网格坐标
    
    int y = j/INTERVAL;
    
    vector3 v1((float)m/INTERVAL,(float)n/INTERVAL,0);
    
    vector3 v2(v1.x,v1.y-1,0);
    
    vector3 v3(v1.x-1,v1.y,0);
    
    vector3 v4(v1.x-1,v1.y-1,0);
    
    float x0 = v1*v[x][y];
    
    float x1 = v2*v[x][y+1];
    
    float x3 = v3*v[x+1][y];
    
    float x4 = v4*v[x+1][y+1];
    
    float m1 = leap(x0,x1,weight(v1.y));
    
    float m2 = leap(x3,x4,weight(v1.y));
    
    return leap(m1,m2,weight(v1.x));
    
}



std::vector<std::vector<float>> SolidNoise(int x,int y){ //主方法体，返回一个二维浮点集
    srand(time(0));
    std::vector<std::vector<float>> res(x,std::vector<float>(y));
    
    int intervalX = x/INTERVAL;
    
    int intervalY = y/INTERVAL;
    
    std::vector<std::vector<vector3>> vec(intervalX+1,std::vector<vector3>(intervalY+1));
    
    //循环生成随机向量
    
    for(int i = 0;i<intervalX+1;i++){
        
        for(int j = 0;j<intervalY+1;j++){
            
            vec[i][j] = randomVector();
            
        }
        
    }
    
    //主循环
    
    for(int i = 0;i<x;i++){
        
        for(int j = 0;j<y;j++){
            
            res[i][j] = (effect(i,j,vec)+1)*0.8;
            
        }
        
    }
    
    return res;
    
}

