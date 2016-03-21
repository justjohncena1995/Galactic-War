#include "Game.h"

#pragma once

class Player : public Game
{
	public: 

		Player();
		~Player();
		void playerlProperties();
		void playerMovement();
		void player2Properties();
		void detectCollision(float p1xpos, float p1ypos, float p2xpos, float p2ypos, bool detect);

		// Getters 
		float getXpos();
		float getYpos();
		bool getBulletFired();


		// Setters
		void setXpos(float theXpos);
		void setYpos(float theYpos);
		void setBulletFired(bool theFire);

	private:
		DirectX::SimpleMath::Matrix rotate[2];
		DirectX::SimpleMath::Matrix trans[2];
		DirectX::SimpleMath::Matrix scale[2];
		std::unique_ptr<DirectX::Keyboard> m_keyboard;

	protected:
		float xpos;
		float ypos;
		bool bulletFired;
		
};