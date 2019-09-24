#pragma once 

#include "Components.hpp"

class CircleComponent : public Component{
public: 
	CircleComponent(float xX, float yY, float rR){
		x = static_cast<int>(xX);
		y = static_cast<int>(yY);
		r = static_cast<int>(rR);
	}
	~CircleComponent(){};
    int x, y;
    int r;
};