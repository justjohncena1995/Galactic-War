#include "Game.h"
#include "Gamestate.h"

#pragma once 

class Menu : Game, gameState
{
	public:
		Menu();
		~Menu();
		void startInput();
		void drawBatch();
		

	private:
		std::unique_ptr<DirectX::Mouse> m_mouse;
		std::unique_ptr<DirectX::GeometricPrimitive > m_background1;
		DirectX::SimpleMath::Matrix background1;
		DirectX::SimpleMath::Vector2 m_origin;
		DirectX::SimpleMath::Vector2 m_screenPos1;
		DirectX::SimpleMath::Vector2 m_origin1;
		DirectX::SimpleMath::Vector2 m_screenPos2;
		DirectX::SimpleMath::Vector2 m_origin2;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> startB;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> menuB;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> titleT;
		std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		RECT startRect;
		
};