#pragma once


class gameState
{
public:

	gameState();
	~gameState();

	// Getters Prototypes

	bool getPaused();
	bool getMenu();
	bool getgameP();

	// Setters Prototypes

	void setPaused(bool thePaused);
	void setMenu(bool theMenu);
	void setGame(bool theGame);
	

private:
	bool isPaused;
	bool menu;
	bool gameplay;



};