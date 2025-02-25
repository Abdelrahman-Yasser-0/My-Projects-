#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
using namespace std;
using namespace sf;
class MENU
{
public:
	Sprite newgamee;
	Sprite gameoptionn;
	Sprite exitt;
	Sprite soundunmutee;
	Sprite soundmutee;
	Music mainmenumusic;
	Sprite gameoptionback;
	MENU(float width, float height);
	void setselected(int n);
	int pressed() {
		return selected;
	}
	void mousemove(RectangleShape& mouse);
	void animation(RectangleShape& mouse);
	void draw(RenderWindow& windwo);
	~MENU();
  
private:
	int selected;
	Texture newgame;
	Texture gameoption;
	Texture exit;
	Texture soundunmute;
	Texture soundmute;
	
};

