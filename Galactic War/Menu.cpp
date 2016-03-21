#include "pch.h"
#include "Menu.h"
using namespace DirectX;
using namespace DirectX::SimpleMath;



Menu::Menu()
{
	
}

Menu::~Menu()
{

}

void Menu::startInput()
{
	auto mouse = m_mouse->GetState();

	if ((mouse.x > startRect.left && mouse.x < startRect.right) && (mouse.y > startRect.top && mouse.y < startRect.bottom))
	{

		if (mouse.leftButton)
		{
			setMenu(false);
			setGame(true);
		}
	}
}

void Menu::drawBatch()
{
		// Draw the background for the menu
		m_background1->Draw(background1, m_view, m_proj, Colors::White, menuB.Get());

		// Begin spriteBatch
		m_spriteBatch->Begin();
		// Draw start button
		m_spriteBatch->Draw(startB.Get(), startRect);
		// Draw title 
		m_spriteBatch->Draw(titleT.Get(), m_screenPos1, nullptr, Colors::White, 0.f, m_origin1);
		// End spriteBatch
		m_spriteBatch->End();  
}