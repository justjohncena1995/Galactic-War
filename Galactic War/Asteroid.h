#pragma once
#include "Game.h"

class Asteroid : public Game
{
 public:
	Asteroid();
	~Asteroid();
	void rockProperties();

	// Getters

	float getXpos();
	float getYpos();

	// Setters
	void setXpos(float theXpos);
	void setYpos(float theYpos);

 private:
	 float Xpos;
	 float Ypos;
	 std::unique_ptr<DirectX::Model> asteroid;
	 DirectX::SimpleMath::Matrix rockScale;
	 DirectX::SimpleMath::Matrix model1[20];
};