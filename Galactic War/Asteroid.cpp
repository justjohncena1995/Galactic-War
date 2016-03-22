#include "pch.h"
#include "Asteroid.h"

using namespace DirectX::SimpleMath;


Asteroid::Asteroid()
{
	Xpos = 0.0f;
	Ypos = 0.0f;
}

Asteroid::~Asteroid()
{

}

float Asteroid::getXpos()
{
	return Xpos;
}

float Asteroid::getYpos()
{
	return Ypos;
}

void Asteroid::setXpos(float theXpos)
{
	Xpos = theXpos;
}

void Asteroid::setYpos(float theYpos)
{
	Ypos = theYpos;
}

void Asteroid::rockProperties()
{
	rockScale = Matrix::CreateScale(0.005);

	for (int n = 0; n > 20; n++)
	{
		model1[n] = rockScale;
	}
}