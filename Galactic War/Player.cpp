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
	trans[0] = Matrix::CreateTranslation(2.0f, 0.0f, 1.0f);
	scale[0] = Matrix::CreateScale(0.002);
	rotate[0] = Matrix::CreateRotationX(4.f);
	rotate[1] = Matrix::CreateRotationY(1.f);
	model = scale[0] * trans[0] * rotate[0] * rotate[1]; 
	xpos = 0.0f;
	ypos = 2.0f;
}

void Player::player2Properties()
{
	trans[1] = Matrix::CreateTranslation(2.0f, 0.0f, 1.0f);
	scale[1] = Matrix::CreateScale(0.002);
	rotate[2] = Matrix::CreateRotationX(4.f);
	rotate[3] = Matrix::CreateRotationY(1.f);
	model1 = scale[1] * trans[1] * rotate[2] * rotate[3];
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

