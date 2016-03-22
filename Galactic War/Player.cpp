#include "pch.h"
#include "Player.h"
using namespace DirectX::SimpleMath;

Player::Player()
{
	xpos = 0.0f;
	ypos = 0.0f;
	bulletFired = false;
}

Player::~Player()
{
	
}

// Getters

float Player::getXpos()
{
	return xpos;
}

float Player::getYpos()
{
	return ypos;
}

bool Player::getBulletFired()
{
	return bulletFired;
}

// Setters

void Player::setXpos(float theXpos)
{
	xpos = theXpos;
}

void Player::setYpos(float theYpos)
{
	ypos = theYpos;
}

void Player::setBulletFired(bool theFire)
{
	bulletFired = theFire;
}


void Player::playerlProperties()
{
	
	scale[0] = Matrix::CreateScale(0.002);
	rotate[0] = Matrix::CreateRotationX(7.f);
	rotate[1] = Matrix::CreateRotationY(1.f);
	model = scale[0] * rotate[0] * rotate[1]; 
	
}



void Player::playerMovement()
{
	auto kb = m_keyboard->GetState();
	if (kb.Escape)
	PostQuitMessage(0);

	if (kb.A)
	{
		model = Matrix::CreateTranslation(-Vector3::Right) * Matrix::CreateRotationY(-0.1f) * model;
	}
	if (kb.S)
	{
		model = Matrix::CreateTranslation(-Vector3::Backward * 8) * Matrix::CreateRotationY(.0f) * model;
	}
	if (kb.D)
	{
		model = Matrix::CreateTranslation(-Vector3::Left) * Matrix::CreateRotationY(0.1f) * model;;
	}

}

