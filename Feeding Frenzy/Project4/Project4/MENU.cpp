#include "MENU.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<chrono>
#include<thread>
#include<SFML/Window.hpp>
using namespace std;
using namespace sf;


MENU::MENU(float width, float height) {
	newgame.loadFromFile("NEW GAME.png");
	gameoption.loadFromFile("GAME OPTIONS .png");
	exit.loadFromFile("EXIT.png");
	soundunmute.loadFromFile("unmute.png");
	soundmute.loadFromFile("mute.png");

	newgamee.setTexture(newgame);
	gameoptionn.setTexture(gameoption);
	exitt.setTexture(exit);
	soundunmutee.setTexture(soundunmute);
	soundmutee.setTexture(soundmute);


	newgamee.setTextureRect(IntRect(0, 0, 197, 197));
	gameoptionn.setTextureRect(IntRect(0, 0, 177, 171));
	exitt.setTextureRect(IntRect(0, 0, 196, 193));
	

	newgamee.setPosition(550, 520);
	gameoptionn.setPosition(1200, 520);
	exitt.setPosition(1000, 800);
	soundunmutee.setPosition(0, 0);
	soundmutee.setPosition(-500, 0);
	soundunmutee.setScale(0.2, 0.2);
	soundmutee.setScale(0.2, 0.2);
	selected = 1;
	

	mainmenumusic.openFromFile("mainmenu.ogg");
mainmenumusic.play();
}
MENU::~MENU() {};
void MENU::mousemove(RectangleShape& mouse) {
	if (mouse.getGlobalBounds().intersects(newgamee.getGlobalBounds())) {
		selected = 1;
	}
	if (mouse.getGlobalBounds().intersects(gameoptionn.getGlobalBounds())) {
		selected = 2;
	}
	if (mouse.getGlobalBounds().intersects(exitt.getGlobalBounds()) ) {
		selected = 3;
	}
	if (mouse.getGlobalBounds().intersects(soundunmutee.getGlobalBounds())&&Mouse::isButtonPressed(Mouse::Left)) {
		selected = 4;
		this_thread::sleep_for(chrono::milliseconds(200));
	}
	if (mouse.getGlobalBounds().intersects(soundmutee.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
		selected = 5;
		this_thread::sleep_for(chrono::milliseconds(200));
	}
}
void MENU::animation(RectangleShape& mouse) {
	if (selected == 1) {
		newgamee.setTextureRect(IntRect(202, 0, 197, 197));
		gameoptionn.setTextureRect(IntRect(0, 0, 177, 171));
		exitt.setTextureRect(IntRect(0, 0, 196, 193));
		newgamee.setScale(1.2, 1.2);
		gameoptionn.setScale(1, 1);
		exitt.setScale(1, 1);
	}
	if (selected == 2) {
		newgamee.setTextureRect(IntRect(0, 0, 197, 197));
		gameoptionn.setTextureRect(IntRect(223, 0, 177, 171));
		exitt.setTextureRect(IntRect(0, 0, 196, 193));
		gameoptionn.setScale(1.2, 1.2);
		newgamee.setScale(1, 1);
		exitt.setScale(1, 1);
	}
	if (selected == 3) {
		newgamee.setTextureRect(IntRect(0, 0, 197, 197));
		gameoptionn.setTextureRect(IntRect(0, 0, 177, 171));
		exitt.setTextureRect(IntRect(203, 0, 196, 193));
		exitt.setScale(1.2, 1.2);
		gameoptionn.setScale(1, 1);
		newgamee.setScale(1, 1);
	}
	if (selected == 4) {
		soundunmutee.setPosition(-500, 0);
		soundmutee.setPosition(0, 0);
		mainmenumusic.stop();
	}
	if (selected == 5) {
		soundmutee.setPosition(-500, 0);
		soundunmutee.setPosition(0, 0);
		mainmenumusic.play();
	}
	if (!mouse.getGlobalBounds().intersects(newgamee.getGlobalBounds())) {
		if (!mouse.getGlobalBounds().intersects(gameoptionn.getGlobalBounds())) {
			if (!mouse.getGlobalBounds().intersects(exitt.getGlobalBounds())) {
				newgamee.setTextureRect(IntRect(0, 0, 197, 197));
				gameoptionn.setTextureRect(IntRect(0, 0, 177, 171));
				exitt.setTextureRect(IntRect(0, 0, 196, 193));
				newgamee.setScale(1, 1);
				gameoptionn.setScale(1, 1);
				exitt.setScale(1, 1);
				selected = 0;
			}
		}
	}
}


void MENU::setselected(int n) {
	selected = n;
}
void MENU::draw(RenderWindow& window) {
	window.draw(newgamee);
	window.draw(gameoptionn);
	window.draw(exitt);
	window.draw(soundunmutee);
	window.draw(soundmutee);
	
}
