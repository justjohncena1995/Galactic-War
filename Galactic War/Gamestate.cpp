#include "pch.h"
# include "Gamestate.h"

gameState::gameState()
{
	isPaused = false;
	menu = false;
	gameplay = false;
}

gameState::~gameState()
{

}

// Getters
bool gameState::getgameP()
{
	return gameplay;
}

bool gameState::getMenu()
{
	return menu;
}

bool gameState::getPaused()
{
	return isPaused;
}

// Setters

void gameState::setPaused(bool thePaused)
{
	isPaused = thePaused;
}

void gameState::setMenu(bool theMenu)
{
	menu = theMenu;
}

void gameState::setGame(bool theGame)
{
	gameplay = theGame;
}