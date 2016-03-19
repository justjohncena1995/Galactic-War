#include "pch.h"
#include "Planets.h"
using namespace DirectX::SimpleMath;

planets::planets()
{

}

planets::~planets()
{

}

void planets::cubes()
{
	world[1]->Draw(m_world, m_view, m_proj);
	
}

