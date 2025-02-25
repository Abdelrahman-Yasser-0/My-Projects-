#include "MENU.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<chrono>
#include<thread>


/*..........................................
.
.  pagenum            .       function     .
.---------------------.--------------------.
.     mainmenu        .          0         .
.     newgame         .          1         .
.     gameoptiopns    .          2         .
.     exit            .         -1         .
.     instructions    .          3         .
.     level1          .          4         .
.     gameover        .          5         .
.     level menu      .          6         .
.     win             .          7         .
.     level 3         .          8         .
.     level2          .          9         .
.     credits         .          10        .
.                     .                    .
.                     .                    .
.                     .                    .
............................................*/


using namespace std;
using namespace sf;
//Global var//
float ground = 1013.5;
float leftwall = 53;
float rightwall = 1867;
float top = 160;
int fish1_eaten;
int fish2_eaten;
int fish3_eaten;
int totalF_eaten;
int score;
int pagenum = 0;
int  frenzy_animation_y = 0, frenzy_animation_x = 1, fishs = 5;
int l = 0;
int retry = 0;
//done

struct eat {
	int fish1_eaten = 0;
	int fish2_eaten = 0;
	int fish3_eaten = 0;
	int totalF_eaten = 0;
	int score = 0;
};
struct fishh {
	Sprite fish1;
	int speed_x;
	int speed_y;
	float animation = 0;
}; fishh smallF[10];
fishh midF[6];
fishh bigF[4];
struct player {

	//define//
	float move_x, move_y;
	FloatRect rect;
	Sprite player;
	float currentframe = 0;
	float eatcurrentframe = 0;
	int lives = 5;
	bool spawned = false;
	Sound spawnsound;
	SoundBuffer spawnsoundbuffer;
	bool spawnsoundplayed = false;
	bool collisionwtihfish = false;
	float scaleonx = 0.5;
	float scaleony = 0.5;
	//done//

	//intialize//
	void input(Texture& player_text, Vector2f& size) {
		move_x = 0; move_y = 0;
		player.setTexture(player_text);
		spawnsoundbuffer.loadFromFile("playerSpawn.wav");
		spawnsound.setBuffer(spawnsoundbuffer);
		rect.left = 960; rect.top = -200;
		player.setScale(scaleonx, scaleonx);
		player.setTextureRect(IntRect(int(currentframe) * size.x, 1 * size.y + 2, size.x - 10, size.y - 4));
		player.setOrigin(player.getLocalBounds().width / 2, player.getLocalBounds().height / 2);
	}

	//animation func//

	void update(float& time, Vector2f size) {

		//spwan animation//
		if (spawned == false) {
			if (spawnsoundplayed == false) {
				spawnsound.play();
				spawnsoundplayed = true;
			}
			if (rect.top < 600) {
				move_y = 0.25;
			}
			else {
				spawned = true;

			}

			currentframe += 0.005 * time;
			if (currentframe > 6) {
				currentframe -= 6;
			}
			if (int(currentframe) != 0) {
				player.setTextureRect(IntRect(int(currentframe) * size.x + 5, 1 * size.y + 2, size.x - 10, size.y - 4));
			}
			if (int(currentframe) == 0) {
				player.setTextureRect(IntRect(5, 1 * size.y + 2, size.x - 10, size.y - 4));
			}
		}
		//done// 
		rect.left += move_x * time;//movement//
		rect.top += move_y * time;//movement//
		int state = 0;
		for (int i = 0; i < 8; i++) {

			if (player.getGlobalBounds().intersects(smallF[i].fish1.getGlobalBounds()) || player.getGlobalBounds().intersects(midF[i].fish1.getGlobalBounds()) || player.getGlobalBounds().intersects(bigF[i].fish1.getGlobalBounds()))
			{
				state = 1;
			}
			if (move_x > 0)
				state = 2;

			if (move_x < 0)
				state = 3;

			if (move_x == 0 && move_y == 0)
				state = 4;
		}



		if (state == 2 && collisionwtihfish == false) {  //animation to right//
			player.setScale(scaleonx * -1, scaleony);
			currentframe += 0.005 * time;
			if (currentframe > 15) {
				currentframe -= 15;
			}
			if (int(currentframe) != 0) {
				player.setTextureRect(IntRect(int(currentframe) * size.x + 5, 2 * size.y + 2, size.x - 10, size.y - 4));
			}
			if (int(currentframe) == 0) {
				player.setTextureRect(IntRect(5, 2 * size.y + 2, size.x - 10, size.y - 4));
			}

			if ((fish1_eaten + fish2_eaten) >= 20 && (fish1_eaten + fish2_eaten) < 40) {
				player.setScale(-0.7, 0.7);
			}
			if ((fish1_eaten + fish2_eaten + fish3_eaten) >= 40) {

				player.setScale(-0.9, 0.9);
			}


		}


		if (state == 3 && collisionwtihfish == false) { //animation to left//
			player.setScale(scaleonx, scaleony);
			currentframe += 0.005 * time;
			if (currentframe > 15) {
				currentframe -= 15;
			}
			if (int(currentframe) != 0) {
				player.setTextureRect(IntRect(int(currentframe) * size.x + 5, 2 * size.y + 2, size.x - 10, size.y - 4));
			}
			if (int(currentframe) == 0) {
				player.setTextureRect(IntRect(5, 2 * size.y + 2, size.x - 10, size.y - 4));
			}

			if ((fish1_eaten + fish2_eaten) >= 20 && (fish1_eaten + fish2_eaten) < 40) {
				player.setScale(0.7, 0.7);
			}
			if ((fish1_eaten + fish2_eaten + fish3_eaten) >= 40) {

				player.setScale(0.9, 0.9);
			}

		}

		if (state == 4 && collisionwtihfish == false) { //idel animation//
			currentframe += 0.005 * time;
			if (currentframe > 6) {
				currentframe -= 6;
			}
			if (int(currentframe) != 0) {
				player.setTextureRect(IntRect(int(currentframe) * size.x + 5, 1 * size.y + 2, size.x - 10, size.y - 4));
			}
			if (int(currentframe) == 0) {
				player.setTextureRect(IntRect(5, 1 * size.y + 2, size.x - 10, size.y - 4));
			}

		}

		//eating animation 


		if (collisionwtihfish) {
			eatcurrentframe += 0.008 * time;
			if (eatcurrentframe > 6) {
				eatcurrentframe -= 6;
				collisionwtihfish = false;
			}

			if (int(eatcurrentframe) != 0) {
				player.setTextureRect(IntRect(int(eatcurrentframe) * size.x + 5, 0 * size.y + 2, size.x - 10, size.y - 4));
			}
			if (int(eatcurrentframe) == 0) {
				player.setTextureRect(IntRect(5, 1 * size.y + 2, size.x - 10, size.y - 4));
			}

		}

		if (rect.left < leftwall) { //collosin with left wall//
			rect.left = leftwall;
		}
		if (rect.left > rightwall) {//collison with right wall//
			rect.left = rightwall;
		}
		if (rect.top > ground) {//collison with ground//
			rect.top = ground;
		}
		if (spawned == true) {
			if (rect.top < top) {//collison with top//
				rect.top = top;
			}
		}
		player.setPosition(rect.left, rect.top);
		move_x = 0;
		move_y = 0;

	}
}player;



struct options { //options window struct//
	//define//
	Sprite gameoptionback;
	Text gameoptiontext[4];
	Sprite windoow;
	Sprite titlee;
	Sprite checkk;
	int checkcout = 39;
	Texture back_1;
	Texture check;
	Font font;
	Texture windoww;
	Texture title;
	//done//
	//intialize the texture and font //
	void setup() {
		back_1.loadFromFile("back.png");
		gameoptionback.setTexture(back_1);
		windoww.loadFromFile("PC Computer - Feeding Frenzy - M.png");
		windoow.setTexture(windoww);
		windoow.setPosition(600, 150);
		title.loadFromFile("title.png");
		titlee.setTexture(title);
		titlee.setPosition(850, 70);
		titlee.setScale(1.4, 1.4);
		font.loadFromFile("HTDaisyDelight-Regular-PersonalUse.otf");
	}
	//done//

	// initialize the defualt //
	void initialize() {
		gameoptiontext[0].setFont(font);
		gameoptiontext[0].setString("Sound");
		gameoptiontext[0].setFillColor(Color::White);
		gameoptiontext[0].setPosition(650, 250);
		gameoptiontext[0].setCharacterSize(60);

		gameoptiontext[1].setFont(font);
		gameoptiontext[1].setString("Instructions");
		gameoptiontext[1].setFillColor(Color::White);
		gameoptiontext[1].setPosition(650, 450);
		gameoptiontext[1].setCharacterSize(60);


		gameoptiontext[2].setFont(font);
		gameoptiontext[2].setString("Credits");
		gameoptiontext[2].setFillColor(Color::White);
		gameoptiontext[2].setPosition(650, 650);
		gameoptiontext[2].setCharacterSize(60);


		gameoptiontext[3].setFont(font);
		gameoptiontext[3].setString("Back");
		gameoptiontext[3].setFillColor(Color::White);
		gameoptiontext[3].setPosition(950, 750);
		gameoptiontext[3].setCharacterSize(60);


		check.loadFromFile("Check.png");
		checkk.setTexture(check);
		checkk.setTextureRect(IntRect(4, checkcout, 38, 30));
		checkk.setPosition(900, 265);
		checkk.setScale(1.3, 1.3);
	}
	//done//

	//update function//
	void gameoptionwindow(RenderWindow& window, RectangleShape& mouse, MENU& menu, bool& soundplayed) {
		soundplayed = false;
		mouse.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		if (mouse.getGlobalBounds().intersects(checkk.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			checkcout += 36;
			this_thread::sleep_for(chrono::milliseconds(200));
			if (checkcout > 40) {
				checkcout = 3;
			}
			if (checkcout == 3)
				menu.mainmenumusic.stop();
			if (checkcout == 39)
				menu.mainmenumusic.play();
			checkk.setTextureRect(IntRect(4, checkcout, 38, 32));
		}
		if (mouse.getGlobalBounds().intersects(gameoptiontext[3].getGlobalBounds())) {
			gameoptiontext[3].setFillColor(Color::Yellow);
		}
		else
			gameoptiontext[3].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(gameoptiontext[2].getGlobalBounds())) {
			gameoptiontext[2].setFillColor(Color::Yellow);
		}
		else
			gameoptiontext[2].setFillColor(Color::White);


		if (mouse.getGlobalBounds().intersects(gameoptiontext[3].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			pagenum = 0;
			this_thread::sleep_for(chrono::milliseconds(200));
		}

		if (mouse.getGlobalBounds().intersects(gameoptiontext[1].getGlobalBounds())) {
			gameoptiontext[1].setFillColor(Color::Yellow);
		}
		else
			gameoptiontext[1].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(gameoptiontext[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			pagenum = 3;
			this_thread::sleep_for(chrono::milliseconds(200));
		}

		if (mouse.getGlobalBounds().intersects(gameoptiontext[2].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			pagenum = 10;
			this_thread::sleep_for(chrono::milliseconds(200));
		}

	}

	//done//

	//draw function//
	void gameoptionwindowdraw(RenderWindow& window, RectangleShape& mouse) {
		window.draw(gameoptionback);
		window.draw(windoow);
		window.draw(titlee);
		window.draw(checkk);
		for (int x = 0; x < 4; x++) {
			window.draw(gameoptiontext[x]);
		}
	}
	//done//

}gameoptions;

struct Credits {
	//define.//
	Sprite creditsback;
	Sprite titlee;
	Sprite popup;
	Text creditstext[2];
	Texture back_1;
	Texture title;
	Texture popuptext;
	Font font;
	//done//
	//intialize the texture and font //
	void setup() {
		back_1.loadFromFile("back.png");
		creditsback.setTexture(back_1);
		popuptext.loadFromFile("instructionsback.png");
		popup.setTexture(popuptext);
		popup.setPosition(400, 150);
		popup.setScale(1.5, 1);
		title.loadFromFile("title.png");
		titlee.setTexture(title);
		titlee.setPosition(800, 70);
		titlee.setScale(1.4, 1.4);
		font.loadFromFile("HTDaisyDelight-Regular-PersonalUse.otf");

	}
	//done//
	// initialize the defualt //
	void initialize() {

		creditstext[0].setFont(font);
		creditstext[0].setString("Special Thanks: \n - A big shoutout to everyone who supported us along the way. Your cheers and advice kept us \ngoing! \n Our Team:                    id: \n - Toqa Monged          2023170154 \n - Jana Medhat          2023170165 \n -Ahmed ELkomy          2023170032\n -Abdelrahman Yasser           2023170349 \nTo our incredible team: Your dedication and talent have brought this game to life.\n Thank you for your hard work and commitment. ");
		creditstext[0].setFillColor(Color::White);
		creditstext[0].setPosition(500, 270);
		creditstext[0].setCharacterSize(28);

		creditstext[1].setFont(font);
		creditstext[1].setString("Back");
		creditstext[1].setFillColor(Color::White);
		creditstext[1].setPosition(950, 650);
		creditstext[1].setCharacterSize(60);


	}
	//done//
	//update function//
	void creditswindow(RenderWindow& window, RectangleShape& mouse, MENU& menu, bool& soundplayed) {
		soundplayed = false;
		mouse.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

		if (mouse.getGlobalBounds().intersects(creditstext[1].getGlobalBounds()))
			creditstext[1].setFillColor(Color::Yellow);
		else
			creditstext[1].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(creditstext[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			pagenum = 2;
			this_thread::sleep_for(chrono::milliseconds(200));
		}



	}
	void creditswindowdraw(RenderWindow& window, RectangleShape& mouse) {
		window.draw(creditsback);
		window.draw(popup);
		window.draw(titlee);
		for (int x = 0; x < 2; x++) {
			window.draw(creditstext[x]);
		}
	}
} credits;



struct instructions {
	//define.//
	Sprite instructionback;
	Sprite titlee;
	Sprite popup;
	Text instructionstext[2];
	Texture back_1;
	Texture title;
	Texture popuptext;
	Font font;
	//done//
	//intialize the texture and font //
	void setup() {
		back_1.loadFromFile("back.png");
		instructionback.setTexture(back_1);
		popuptext.loadFromFile("instructionsback.png");
		popup.setTexture(popuptext);
		popup.setPosition(600, 150);
		title.loadFromFile("title.png");
		titlee.setTexture(title);
		titlee.setPosition(850, 70);
		titlee.setScale(1.4, 1.4);
		font.loadFromFile("HTDaisyDelight-Regular-PersonalUse.otf");

	}
	//done//
	// initialize the defualt //
	void initialize() {

		instructionstext[0].setFont(font);
		instructionstext[0].setString("HOW TO PLAY : \n - Eat fish that are smaller than you \n - Avoid fish that are bigger than you \n - Eat enough fish and you will grow in size\nCan you grow large enough to advance to the next stage ? ");
		instructionstext[0].setFillColor(Color::White);
		instructionstext[0].setPosition(665, 350);
		instructionstext[0].setCharacterSize(32);


		instructionstext[1].setFont(font);
		instructionstext[1].setString("Back");
		instructionstext[1].setFillColor(Color::White);
		instructionstext[1].setPosition(950, 650);
		instructionstext[1].setCharacterSize(60);


	}
	//done//
	//update function//
	void instructionwindow(RenderWindow& window, RectangleShape& mouse, MENU& menu, bool& soundplayed) {
		soundplayed = false;
		mouse.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

		if (mouse.getGlobalBounds().intersects(instructionstext[1].getGlobalBounds()))
			instructionstext[1].setFillColor(Color::Yellow);
		else
			instructionstext[1].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(instructionstext[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			pagenum = 2;
			this_thread::sleep_for(chrono::milliseconds(200));
		}



	}
	void instructionwindowdraw(RenderWindow& window, RectangleShape& mouse) {
		window.draw(instructionback);
		window.draw(popup);
		window.draw(titlee);
		for (int x = 0; x < 2; x++) {
			window.draw(instructionstext[x]);
		}
	}


} instructions;
struct win {
	Sprite winback;
	Sprite titlee;
	Sprite popup;
	Text wintext[4];
	Texture back_1;
	Texture title;
	Texture popuptext;



	Font font;
	//done//
	//intialize the texture and font //
	void setup() {
		back_1.loadFromFile("PC_Computer_-_Feeding_Frenzy_-_M.png");
		winback.setTexture(back_1);
		popuptext.loadFromFile("instructionsback.png");
		popup.setTexture(popuptext);
		popup.setPosition(600, 150);
		title.loadFromFile("title.png");
		titlee.setTexture(title);
		titlee.setPosition(850, 70);
		titlee.setScale(1.4, 1.4);
		font.loadFromFile("HTDaisyDelight-Regular-PersonalUse.otf");

	}
	//done//
	// initialize the defualt //
	void initialize() {

		wintext[0].setFont(font);
		wintext[0].setString("Next level");
		wintext[0].setFillColor(Color::White);
		wintext[0].setPosition(1100, 650);
		wintext[0].setCharacterSize(60);

		wintext[1].setFont(font);
		wintext[1].setString("Mainmenu");
		wintext[1].setFillColor(Color::White);
		wintext[1].setPosition(662, 649);
		wintext[1].setCharacterSize(60);


		wintext[2].setFont(font);
		wintext[2].setString("CONGRATULATIONS\!");
		wintext[2].setFillColor(Color::Green);
		wintext[2].setPosition(710, 260);
		wintext[2].setOutlineColor(Color::Black);
		wintext[2].setOutlineThickness(10);
		wintext[2].setCharacterSize(80);

		wintext[3].setFont(font);
		wintext[3].setString("     Horraaay... \n          you are amazing \!   ");
		wintext[3].setFillColor(Color::White);
		wintext[3].setPosition(700, 440);
		wintext[3].setOutlineColor(Color::Black);
		wintext[3].setOutlineThickness(2);
		wintext[3].setCharacterSize(60);

	}

	//done//
	//update function//
	void winwindow(RenderWindow& window, RectangleShape& mouse, MENU& menu) {

		//menu.mainmenumusic.stop();
		mouse.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

		if (mouse.getGlobalBounds().intersects(wintext[1].getGlobalBounds()))
			wintext[1].setFillColor(Color::Yellow);
		else
			wintext[1].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(wintext[0].getGlobalBounds()))
			wintext[0].setFillColor(Color::Yellow);
		else
			wintext[0].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(wintext[0].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			if (l == 1)
				pagenum = 9;
			else if (l == 2)
				pagenum = 8;
			if (l == 3)
				pagenum = 4;
			this_thread::sleep_for(chrono::milliseconds(200));
		}

		if (mouse.getGlobalBounds().intersects(wintext[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			pagenum = 0;
			this_thread::sleep_for(chrono::milliseconds(200));
		}


	}
	void winwindowdraw(RenderWindow& window, RectangleShape& mouse) {
		window.draw(winback);
		window.draw(popup);
		window.draw(titlee);
		for (int x = 0; x < 4; x++) {
			window.draw(wintext[x]);
		}
	}

}win;
struct newgame {

	//define.//
	Sprite newgameback;
	Sprite titlee;
	Sprite popup;
	Text newgametext[4];
	Texture back_1;
	Texture title;
	Texture popuptext;
	Font font;
	//done//
	//intialize the texture and font //
	void setup() {
		back_1.loadFromFile("back.png");
		newgameback.setTexture(back_1);
		popuptext.loadFromFile("instructionsback.png");
		popup.setTexture(popuptext);
		popup.setPosition(600, 150);
		title.loadFromFile("title.png");
		titlee.setTexture(title);
		titlee.setPosition(850, 70);
		titlee.setScale(1.4, 1.4);
		font.loadFromFile("HTDaisyDelight-Regular-PersonalUse.otf");
	}
	//done//
	// initialize the defualt //
	void initialize() {

		newgametext[0].setFont(font);
		newgametext[0].setString("Options");
		newgametext[0].setFillColor(Color::White);
		newgametext[0].setPosition(670, 670);
		newgametext[0].setCharacterSize(36);


		newgametext[1].setFont(font);
		newgametext[1].setString("Continue");
		newgametext[1].setFillColor(Color::White);
		newgametext[1].setPosition(900, 650);
		newgametext[1].setCharacterSize(60);

		newgametext[2].setFont(font);
		newgametext[2].setString("Quit game");
		newgametext[2].setFillColor(Color::White);
		newgametext[2].setPosition(1200, 670);
		newgametext[2].setCharacterSize(36);


		newgametext[3].setFont(font);
		newgametext[3].setString("                      Small Fish Small Pond \n Where the fish are small and the minnows are crunchy!\n Meet Aandy the Angel Fish . Use w,a,s,d to \ncontrol Andy through the dangerous waters ahead.\n \n HOW TO PLAY :\n                  -Eat fish that are smaller than you \n                  -Avoid fish that are bigger than you \n                 -Eat enough fish and you will grow in size\nCan you grow large enough to advance to the next stage?");

		newgametext[3].setFillColor(Color::White);
		newgametext[3].setPosition(700, 270);
		newgametext[3].setCharacterSize(28);






	}
	//done//
	//update function//
	void newgamewindow(RenderWindow& window, RectangleShape& mouse, MENU& menu, Sound& intro, bool& soundplayed) {
		if (soundplayed == false) {
			intro.play();
			soundplayed = true;
		}
		menu.mainmenumusic.stop();
		mouse.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

		if (mouse.getGlobalBounds().intersects(newgametext[0].getGlobalBounds()))
			newgametext[0].setFillColor(Color::Yellow);
		else
			newgametext[0].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(newgametext[1].getGlobalBounds()))
		{
			newgametext[1].setFillColor(Color::Yellow);
		}
		else
			newgametext[1].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(newgametext[2].getGlobalBounds()))
			newgametext[2].setFillColor(Color::Yellow);
		else
			newgametext[2].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(newgametext[2].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			window.close();
			this_thread::sleep_for(chrono::milliseconds(200));
		}
		if (mouse.getGlobalBounds().intersects(newgametext[0].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			pagenum = 2;
			this_thread::sleep_for(chrono::milliseconds(200));
		}
		if (mouse.getGlobalBounds().intersects(newgametext[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			if (l == 1)
				pagenum = 4;
			else if (l == 3)
				pagenum = 8;
			else if (l == 2)
				pagenum = 9;
			this_thread::sleep_for(chrono::milliseconds(200));
		}
	}
	void newgamewindowdraw(RenderWindow& window, RectangleShape& mouse) {
		window.draw(newgameback);
		window.draw(popup);
		window.draw(titlee);
		for (int x = 0; x < 4; x++) {
			window.draw(newgametext[x]);


		}


	}



}newgame;

struct levelmenu {
	//define.//
	Sprite levelmenuback;
	Sprite titlee;
	Sprite popup;
	Text levelmenutext[3];
	Texture back_1;
	Texture title;
	Texture popuptext;
	Font font;
	//done//
	//intialize the texture and font //
	void setup() {
		back_1.loadFromFile("PC_Computer_-_Feeding_Frenzy_-_M.png");
		levelmenuback.setTexture(back_1);
		popuptext.loadFromFile("instructionsback.png");
		popup.setTexture(popuptext);
		popup.setPosition(600, 150);
		title.loadFromFile("title.png");
		titlee.setTexture(title);
		titlee.setPosition(850, 70);
		titlee.setScale(1.4, 1.4);
		font.loadFromFile("HTDaisyDelight-Regular-PersonalUse.otf");
	}
	//done//
	// initialize the defualt //
	void initialize() {

		levelmenutext[0].setFont(font);
		levelmenutext[0].setString("Humble Beginning");
		levelmenutext[0].setFillColor(Color::White);
		levelmenutext[0].setPosition(800, 270);
		levelmenutext[0].setCharacterSize(60);


		levelmenutext[1].setFont(font);
		levelmenutext[1].setString("Shark House");
		levelmenutext[1].setFillColor(Color::White);
		levelmenutext[1].setPosition(850, 435);
		levelmenutext[1].setCharacterSize(60);

		levelmenutext[2].setFont(font);
		levelmenutext[2].setString("Time Bounded ");
		levelmenutext[2].setFillColor(Color::White);
		levelmenutext[2].setPosition(830, 600);
		levelmenutext[2].setCharacterSize(60);
	}
	//done//
		//update function//
	void levelmenuwindow(RenderWindow& window, RectangleShape& mouse, MENU& menu, Sound& intro, bool& soundplayed) {
		if (soundplayed == false) {
			intro.play();
			soundplayed = true;
		}
		menu.mainmenumusic.stop();
		mouse.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
		if (mouse.getGlobalBounds().intersects(levelmenutext[0].getGlobalBounds()))
			levelmenutext[0].setFillColor(Color::Yellow);
		else
			levelmenutext[0].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(levelmenutext[1].getGlobalBounds()))
		{
			levelmenutext[1].setFillColor(Color::Yellow);
		}
		else
			levelmenutext[1].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(levelmenutext[2].getGlobalBounds()))
			levelmenutext[2].setFillColor(Color::Yellow);
		else
			levelmenutext[2].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(levelmenutext[0].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			pagenum = 1;
			l = 1;
			this_thread::sleep_for(chrono::milliseconds(200));
		}
		if (mouse.getGlobalBounds().intersects(levelmenutext[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			pagenum = 1;
			l = 2;
			this_thread::sleep_for(chrono::milliseconds(200));
		}
		if (mouse.getGlobalBounds().intersects(levelmenutext[2].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			pagenum = 1;
			l = 3;
			this_thread::sleep_for(chrono::milliseconds(200));
		}
	}
	void levelmenudraw(RenderWindow& window, RectangleShape& mouse) {
		window.draw(levelmenuback);
		window.draw(popup);
		window.draw(titlee);
		for (int x = 0; x < 3; x++) {
			window.draw(levelmenutext[x]);
		}
	}
}levelmenu;
struct gameover {

	Sprite gameoverback;
	Sprite titlee;
	Sprite popup;
	Text gameovertext[4];
	Texture back_1;
	Texture title;
	Texture popuptext;

	Font font;
	bool goverplayed = false;
	//done//
	//intialize the texture and font //
	void setup() {
		back_1.loadFromFile("back.png");
		gameoverback.setTexture(back_1);
		popuptext.loadFromFile("instructionsback.png");
		popup.setTexture(popuptext);
		popup.setPosition(600, 150);
		title.loadFromFile("title.png");
		titlee.setTexture(title);
		titlee.setPosition(850, 70);
		titlee.setScale(1.4, 1.4);
		font.loadFromFile("HTDaisyDelight-Regular-PersonalUse.otf");

	}
	//done//
	// initialize the defualt //
	void initialize() {

		gameovertext[0].setFont(font);
		gameovertext[0].setString("Retry");
		gameovertext[0].setFillColor(Color::White);
		gameovertext[0].setPosition(1200, 649);
		gameovertext[0].setCharacterSize(60);

		gameovertext[1].setFont(font);
		gameovertext[1].setString("Mainmenu");
		gameovertext[1].setFillColor(Color::White);
		gameovertext[1].setPosition(662, 649);
		gameovertext[1].setCharacterSize(60);

		gameovertext[2].setFont(font);
		gameovertext[2].setString("GAMEOVER\!");
		gameovertext[2].setFillColor(Color::Red);
		gameovertext[2].setPosition(800, 260);
		gameovertext[2].setOutlineColor(Color::Black);
		gameovertext[2].setOutlineThickness(10);
		gameovertext[2].setCharacterSize(100);

		gameovertext[3].setFont(font);
		gameovertext[3].setString("          Be carefull next time ");
		gameovertext[3].setFillColor(Color::White);
		gameovertext[3].setPosition(700, 460);
		gameovertext[3].setOutlineColor(Color::Black);
		gameovertext[3].setOutlineThickness(2);
		gameovertext[3].setCharacterSize(50);

	}

	//done//
	//update function//
	void gameoverwindow(RenderWindow& window, RectangleShape& mouse, MENU& menu, Sound& gover) {

		if (goverplayed) {
			gover.play();
			goverplayed = false;
		}

		//menu.mainmenumusic.stop();
		mouse.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);

		if (mouse.getGlobalBounds().intersects(gameovertext[1].getGlobalBounds()))
			gameovertext[1].setFillColor(Color::Yellow);
		else
			gameovertext[1].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(gameovertext[0].getGlobalBounds()))
			gameovertext[0].setFillColor(Color::Yellow);
		else
			gameovertext[0].setFillColor(Color::White);

		if (mouse.getGlobalBounds().intersects(gameovertext[1].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			pagenum = 0;
			this_thread::sleep_for(chrono::milliseconds(200));
		}
		if (mouse.getGlobalBounds().intersects(gameovertext[0].getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)) {
			if (retry == 1)
				pagenum = 4;
			else if (retry == 3)
				pagenum = 8;
			else if (retry == 2)
				pagenum = 9;

			player.lives = 5;
			score = 0;
			fish1_eaten = 0;
			fish2_eaten = 0;
			fish3_eaten = 0;


			this_thread::sleep_for(chrono::milliseconds(200));
		}

	}


	void gameoverwindowdraw(RenderWindow& window, RectangleShape& mouse) {
		window.draw(gameoverback);
		window.draw(popup);
		window.draw(titlee);
		for (int x = 0; x < 4; x++) {
			window.draw(gameovertext[x]);
		}
	}


}gameover;

struct level {

	//define//

	Texture background;
	Sprite backgound_spr;



	Texture fish1_pic;
	Texture fish2_pic;
	Texture fish3_pic;


	SoundBuffer crunch1;
	Sound s1;
	SoundBuffer crunch2;
	Sound s2;
	SoundBuffer crunch3;
	Sound s3;


	Sound playerdie;
	SoundBuffer playerdiebuff;
	bool diesoundplayed = false;

	Texture fish;
	Vector2f size;
	Clock c;
	float time;
	bool collision_check = false;
	Clock eating_clock;
	int liveduration;
	//Fonts
	Font font1;
	Font font2;

	//fish textures for scorebar
	Texture minnow;
	Sprite minnowS;

	Texture surgeon;
	Sprite surgeonS;

	Texture lion;
	Sprite lionS;

	//score bar texture
	Texture scorebartexture;
	Sprite ScoreBar;

	Text scoretext;
	string scorestring = to_string(score);


	Text livestext;
	string livesstring = to_string(player.lives);

	Text fish1text;
	string fish1string = to_string(fish1_eaten);

	Text fish2text;
	string fish2string = to_string(fish2_eaten);

	Text fish3text;
	string fish3string = to_string(fish3_eaten);

	Text x1text;
	int x;

	//fish eaten bar
	RectangleShape BarBlack;

	CircleShape Triangle1;

	CircleShape Triangle2;

	//Transperent
	Texture unlocked;
	Sprite unlockedSpr1;
	Sprite unlockedSpr2;


	//fish eaten bluebar
	RectangleShape BarBlue;

	//..............................Frenzy..............................//
	Texture frenzy;
	Sprite Frenzy;
	SoundBuffer feeding_frenzy;
	Sound feedingfrenzy;
	bool restart = false;
	

	//..............................Done..............................//
	// 
	//..........................mid & big fish eating ................//
	bool midcollision = false;
	bool bigcollision = false;
	float mideat = 0;
	float bigeat = 0;
	int index;
	bool indexsaved = false;

	//..............................Done..............................//
	// 
	//..............................barracuda..............................//
	Sprite barracudaspr;
	Texture barracuda;
	float barracudacurrentframe = 0;
	float barracudamovement = 0;

	Sound danger;
	SoundBuffer dangersound;

	bool dangersoubdplayed = false;

	// Set initial position and speed
	int speed = 5;
	Clock barracu;


	Clock dangertime;
	bool barrcudacollision = false;

	//.................................oyster.................................//
	Sprite oysterspr;
	Texture oyster;
	float oystercurrentframe = 0;

	Sprite pearlspr;
	Texture pearl;

	Clock oyster_open;
	bool oysteranimationdone = false;
	bool pearleating = false;

	Sound pearlpickup;
	SoundBuffer pearlpickupBuff;

	//......................Visual effects.........................//
	Texture yum;
	Texture crunch;
	Texture chomp;

	Sprite yumspr;
	Sprite crunchspr;
	Sprite chompspr;

	Vector2f playerposition;

	bool yummy = false;
	bool crunchy = false;
	bool chompy;

	//..................................Level 2 background................................//
	Sprite level2back;
	Texture level2backtex;

	//...............................................................Done.........................................................//

	void intialize() {

		//..............................Background..............................//
		background.loadFromFile("back.png");

		backgound_spr.setTexture(background);

		//..............................done..............................//



			//..............................Background..............................//
		level2backtex.loadFromFile("PC Computer - Feeding Frenzy - Star Fish.png");

		level2back.setTexture(level2backtex);

		//..............................done..............................//


   //..............................Enemy..............................//
		fish1_pic.loadFromFile("Minnow.png");
		fish2_pic.loadFromFile("PC Computer - Feeding Frenzy - Surgeonfish.png");
		fish3_pic.loadFromFile("PC Computer - Feeding Frenzy - Lionfish.png");

		for (int i = 0; i < 8; i++) {             //adjust postion//
			smallF[i].fish1.setTexture(fish1_pic);

			smallF[i].fish1.setScale(-1, 1);
			int y = rand() % (1060 - 50 + 1) + 50;

			for (int i = 0; i < 6; i++) {
				smallF[i].speed_y = rand() % 7 - 5;  //speed of every fish//
			}

			smallF[i].speed_x = abs(rand() % (6 - 4 + 1) + 4);


			if (i < 3) {
				smallF[i].fish1.setPosition(0, y);  //first 3 start from left//
			}
			else {
				smallF[i].fish1.setPosition(1900, y);// the rest form right//
			}
		}
		for (int i = 0; i < 4; i++) {
			midF[i].fish1.setTexture(fish2_pic);
			midF[i].fish1.setTextureRect(IntRect(2, 1 * 107, 165, 104));

			int y = rand() % (1060 - 50 + 1) + 50;
			//midF[i].fish1.setScale(-0.5, 0.5);

			for (int i = 0; i < 4; i++) {
				midF[i].speed_y = rand() % 5 - 3;  //speed of every fish//
			}

			midF[i].speed_x = abs(rand() % (6 - 4 + 1) + 4);


			if (i < 2) {
				midF[i].fish1.setScale(-0.7, 0.7);

				midF[i].fish1.setPosition(0, y);  //position of the first 2
			}
			else {
				midF[i].fish1.setScale(0.7, 0.7);

				midF[i].fish1.setPosition(1900, y);  //position of the second 2
			}
		}

		for (int i = 0; i < 2; i++) {
			bigF[i].fish1.setTexture(fish3_pic);
			bigF[i].fish1.setTextureRect(IntRect(5, 2 * 163, 175, 155));
			bigF[i].fish1.setScale(-1, 1);
			int y = rand() % (1060 - 50 + 1) + 50;

			for (int i = 0; i < 3; i++) {
				bigF[i].speed_y = rand() % 4 - 3;  //speed of every fish//
			}

			bigF[i].speed_x = abs(rand() % (4 - 3 + 1) + 3);

			if (i < 1) {
				bigF[i].fish1.setPosition(0, y);  //position of the first 1
			}
			else {
				bigF[i].fish1.setPosition(1900, y);  //position of the second 1
			}
		}
		//..............................done..............................//
	   //..............................Sound eat..............................//
		crunch1.loadFromFile("crunch1.wav");

		s1.setBuffer(crunch1);

		crunch2.loadFromFile("crunch2.wav");

		s2.setBuffer(crunch2);

		crunch3.loadFromFile("crunch3.wav");

		s3.setBuffer(crunch3);



		playerdiebuff.loadFromFile("playerDie.wav");
		playerdie.setBuffer(playerdiebuff);
		//..............................done..............................//

		/*bool musicplay = true;
		Music music;
		music.openFromFile("mainmenu.ogg");
		music.setLoop(musicplay);
		music.play();
		*/
		//..............................Player..............................//
		fish.loadFromFile("PC Computer - Feeding Frenzy - Angelfish.png");

		size.x = 126;
		size.y = 106;

		player.input(fish, size);
		//.............................done..............................//




		//Fonts

		font1.loadFromFile("HTDaisyDelight-Regular-PersonalUse.otf");

		font2.loadFromFile("GUMDROP.ttf");

		//.............................Frenzy..............................//

		frenzy.loadFromFile("FRENZY.png");
		Frenzy.setTexture(frenzy);
		Frenzy.setScale(0.7, 0.7);
		Frenzy.setPosition(800, 135);
		Frenzy.setTextureRect(IntRect(0, 0, 351, 351));
		feeding_frenzy.loadFromFile("feedingFrenzy.wav");
		feedingfrenzy.setBuffer(feeding_frenzy);

		//.............................Done..............................//


	//fish textures for scorebar

		minnow.loadFromFile("Minnow.png");

		minnowS.setTexture(minnow);
		minnowS.setPosition(500, 20);
		minnowS.setScale(-1.3, 1.3);


		surgeon.loadFromFile("Surgeonfish.png");

		surgeonS.setTexture(surgeon);
		surgeonS.setPosition(740, 20);
		surgeonS.setScale(-0.6, 0.6);


		lion.loadFromFile("Lionfish.png");

		lionS.setTexture(lion);
		lionS.setPosition(990, 10);
		lionS.setScale(-0.7, 0.5);

		//score bar texture

		scorebartexture.loadFromFile("Scorebar.jpeg");

		ScoreBar.setTexture(scorebartexture);
		ScoreBar.setScale(1.5, 1);



		scoretext.setFont(font2);
		scoretext.setString(scorestring);
		scoretext.setCharacterSize(50);
		scoretext.setPosition(1525, 10);


		livestext.setFont(font2);
		livestext.setString(livesstring);
		livestext.setPosition(1550, 60);
		livestext.setCharacterSize(50);


		fish1text.setFont(font1);
		fish1text.setString(fish1string);
		fish1text.setPosition(80, 120);

		fish2text.setFont(font1);
		fish2text.setString(fish2string);
		fish2text.setPosition(80, 160);

		fish3text.setFont(font1);
		fish3text.setString(fish3string);
		fish3text.setPosition(80, 200);


		//fish eaten blackbar
		BarBlack.setSize(Vector2f(600, 15));
		BarBlack.setPosition(390, 93);
		BarBlack.setFillColor(Color::Black);

		//fish eaten bluebar
		BarBlue.setSize(Vector2f(0, 15));
		BarBlue.setPosition(390, 93);
		BarBlue.setFillColor(Color::Cyan);

		Triangle1.setRadius(18);
		Triangle1.setPointCount(3);
		Triangle1.setPosition(565, 100);
		Triangle1.setFillColor(Color::Red);


		Triangle2.setRadius(18);
		Triangle2.setPointCount(3);
		Triangle2.setPosition(805, 100);
		Triangle2.setFillColor(Color::Red);

		//.......................Frenzyscore...................//
		x1text.setFont(font2);
		x1text.setPosition(1780, 16);
		x1text.setCharacterSize(80);

		x = 1;
		x1text.setString(to_string(x) + "X");
		x1text.setFillColor(Color::White);
		x1text.setOutlineColor(Color::Black);
		x1text.setOutlineThickness(10);

		//Transperent

		unlocked.loadFromFile("unlockedfish.png");

		unlockedSpr1.setTexture(unlocked);
		unlockedSpr1.setScale(0.8, 0.9);
		unlockedSpr1.setPosition(615, 1);


		unlockedSpr2.setTexture(unlocked);
		unlockedSpr2.setScale(0.8, 0.9);
		unlockedSpr2.setPosition(840, 1);

		//fish eaten blackbar
		BarBlack.setSize(Vector2f(700, 15));
		BarBlack.setPosition(390, 93);
		BarBlack.setFillColor(Color::Black);
		//fish eaten bluebar
		BarBlue.setSize(Vector2f(0, 15));
		BarBlue.setPosition(390, 93);
		BarBlue.setFillColor(Color::Cyan);

		//..............................barracuda..............................//

		barracuda.loadFromFile("PC Computer - Feeding Frenzy - Barracuda.png");
		barracudaspr.setTexture(barracuda);
		barracudaspr.setTextureRect(IntRect(0 + 8, 0 + 5, 260, 115));


		dangersound.loadFromFile("barracudaWarn.wav");
		danger.setBuffer(dangersound);


		// Set initial position and speed

		barracudaspr.setPosition(0, 300);
		barracudaspr.setScale(-1.5, 1.5);

		//..............................oyster.............................//

		oyster.loadFromFile("PC Computer - Feeding Frenzy - Oyster.png");
		oysterspr.setTexture(oyster);
		oysterspr.setTextureRect(IntRect(0 + 8, 0 + 5, 90, 90));

		pearl.loadFromFile("pearl.png");
		pearlspr.setTexture(pearl);
		pearlspr.setScale(0, 0);
		pearlspr.setPosition(1222, 1005);
		oysterspr.setPosition(1190, 950);
		oysterspr.setScale(1.5, 1.5);

		pearlpickupBuff.loadFromFile("oysterPearl.wav");
		pearlpickup.setBuffer(pearlpickupBuff);
		//..............................visual effects.....................//
		yum.loadFromFile("yumeffect.png");
		yumspr.setTexture(yum);
		yumspr.setScale(0, 0);

		crunch.loadFromFile("cruncheffect.png");
		crunchspr.setTexture(crunch);
		crunchspr.setScale(0, 0);

		chomp.loadFromFile("chompeffect.png");
		chompspr.setTexture(chomp);
		chompspr.setScale(0, 0);

		playerposition.x = player.player.getPosition().x;
		playerposition.y = player.player.getPosition().y;
		//...........................Done...................................//
	}


	Clock c_frenzy;
	Clock visual_yum;
	Clock visual_crunch;
	Clock visual_chomp;

	void update() {
		//..............................Player movement..............................//
		time = c.getElapsedTime().asMicroseconds();
		c.restart();
		time /= 650;
		if (time > 20) {
			time = 20;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {

			player.move_x = 0.5;
			player.spawned = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.move_x = -0.5;
			player.spawned = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player.move_y = -0.4;
			player.spawned = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			player.move_y = 0.4;
			player.spawned = true;
		}
		playerposition.x = player.player.getPosition().x;
		playerposition.y = player.player.getPosition().y;
		//..............................done..............................//

		////.............................GREEN FRENZY..............................//

		if (restart == false) {
			c_frenzy.restart();
			restart = true;
		}
		for (int i = 0; i < 7; i++) {
			/*if (totalF_eaten == 60 || player.lives == 0) {
				Frenzy.setTextureRect(IntRect(0, 0, 350.5, 120));
				frenzy_animation_y = 0;
				frenzy_animation_x = 1;
				x = 1;
				x1text.setString(to_string(x) + "X");
				x1text.setFillColor(Color::White);
				x1text.setOutlineColor(Color::Black);
				x1text.setOutlineThickness(10);
			}*/
			if ((fish1_eaten + fish2_eaten + fish3_eaten >= fishs) && ((int)c_frenzy.getElapsedTime().asSeconds() <= 5)) {
				Frenzy.setTextureRect(IntRect(frenzy_animation_x * 351, frenzy_animation_y * 120, 350.5, 120));
				if ((frenzy_animation_y == 6) && (frenzy_animation_x == 2))
					continue;
				else
					frenzy_animation_y++;
				fishs += 3;
				c_frenzy.restart();
			}
			else if (fish1_eaten + fish2_eaten + fish3_eaten < fishs && c_frenzy.getElapsedTime().asSeconds() > 5) {
				if (frenzy_animation_y > 0) {
					frenzy_animation_y--;
					Frenzy.setTextureRect(IntRect(frenzy_animation_x * 351, frenzy_animation_y * 120, 350.5, 120));
					if (frenzy_animation_y == 0 && frenzy_animation_x == 1) {
						Frenzy.setTextureRect(IntRect(0, 0, 350.5, 120));
					}
					c_frenzy.restart();
				}
				c_frenzy.restart();

			}


		}
		if ((frenzy_animation_y == 7) && (frenzy_animation_x == 1)) {
			x = 2;
			x1text.setString(to_string(x) + "X");
			x1text.setFillColor(Color::Green);
			x1text.setOutlineColor(Color::Black);
			x1text.setOutlineThickness(10);

			feedingfrenzy.play();
			frenzy_animation_y = 0;
			frenzy_animation_x = 2;
		}
		//........................RED FRENZY.......................................//
		for (int i = 0; i < 7; i++) {
			/*if (totalF_eaten == 60 || player.lives == 0) {
				Frenzy.setTextureRect(IntRect(0, 0, 350.5, 120));
				frenzy_animation_y = 0;
				frenzy_animation_x = 1;
				x = 1;
				x1text.setString(to_string(x) + "X");
				x1text.setFillColor(Color::White);
				x1text.setOutlineColor(Color::Black);
				x1text.setOutlineThickness(10);
			}*/
			if ((fish1_eaten + fish2_eaten + fish3_eaten >= fishs) && ((int)c_frenzy.getElapsedTime().asSeconds() <= 5)) {
				Frenzy.setTextureRect(IntRect(frenzy_animation_x * 351, frenzy_animation_y * 120, 350.5, 120));
				if ((frenzy_animation_y == 6) && (frenzy_animation_x == 2))
					continue;
				else
					frenzy_animation_y++;
				fishs += 3;
				c_frenzy.restart();
			}

			else if (c_frenzy.getElapsedTime().asSeconds() > 3 && fish1_eaten + fish2_eaten + fish3_eaten < fishs) {
				if (frenzy_animation_y > 0) {
					frenzy_animation_y--;
					Frenzy.setTextureRect(IntRect(frenzy_animation_x * 351, frenzy_animation_y * 120, 350.5, 120));

					if (frenzy_animation_y == 0 && frenzy_animation_x == 2) {
						Frenzy.setTextureRect(IntRect(1 * 351, 6 * 120, 350.5, 120));
						frenzy_animation_y = 6;
						frenzy_animation_x = 1;
						if (frenzy_animation_y < 7 && frenzy_animation_y != 0) {

							frenzy_animation_y--;

							Frenzy.setTextureRect(IntRect(1 * 351, frenzy_animation_y * 120, 350.5, 120));
						}

						if (frenzy_animation_y == 0 && frenzy_animation_x == 1) {
							Frenzy.setTextureRect(IntRect(0, 0, 350.5, 120));
						}

						c_frenzy.restart();


					}
					c_frenzy.restart();
				}
				c_frenzy.restart();
			}
		}
		if ((frenzy_animation_y == 6) && (frenzy_animation_x == 2)) {
			x = 3;
			x1text.setFillColor(Color::Red);
			x1text.setString(to_string(x) + "X");
			x1text.setOutlineColor(Color::Black);
			x1text.setOutlineThickness(10);
			
		}

		//.............................Done..............................//




	   //..............................Text In Scoreboard..............................//
		scorestring = to_string(score);
		scoretext.setString(scorestring);

		livesstring = to_string(player.lives);
		livestext.setString(livesstring);

		fish1string = to_string(fish1_eaten);
		fish1text.setString(fish1string);

		fish2string = to_string(fish2_eaten);
		fish2text.setString(fish2string);

		fish3string = to_string(fish3_eaten);
		fish3text.setString(fish3string);
		//..............................done..............................//

		//..............................Enemy..............................//
		for (int i = 0; i < 8; i++) {

			if (i < 4) {//first 5 fishes//
				smallF[i].fish1.move(smallF[i].speed_x, smallF[i].speed_y);//movement of fish//
				if (smallF[i].fish1.getPosition().x > 2200 or smallF[i].fish1.getPosition().x < 0) {//fish out of the frame//
					int y = rand() % (1000) + 50; //random place //
					smallF[i].fish1.setPosition(0, y);

					smallF[i].speed_x = abs(rand() % (5 - 3 + 1) + 3);


					for (int i = 0; i < 6; i++) {
						smallF[i].speed_y = rand() % 7 - 5;
					}
				}
				if (player.player.getGlobalBounds().intersects(smallF[i].fish1.getGlobalBounds())) {
					fish1_eaten++;
					totalF_eaten++;

				}
			}
			else {//the last 5//
				smallF[i].fish1.setScale(1, 1);
				smallF[i].fish1.move(smallF[i].speed_x, smallF[i].speed_y);//movement of fish//
				if (smallF[i].fish1.getPosition().x < 0 or smallF[i].fish1.getPosition().x > 2200) {
					int y = rand() % (1000) + 50;//random place//
					smallF[i].fish1.setPosition(1900, y);

					smallF[i].speed_x = -(abs(rand() % (5 - 3 + 1) + 3));


					for (int i = 0; i < 6; i++) {
						smallF[i].speed_y = rand() % 7 - 5;
					}

				}
				if (player.player.getGlobalBounds().intersects(smallF[i].fish1.getGlobalBounds())) {
					fish1_eaten++;
					totalF_eaten++;

				}
			}
		}

		for (int i = 0; i < 4; i++) {
			midF[i].animation += 0.1;
			if (i < 2) {
				midF[i].fish1.move(midF[i].speed_x, midF[i].speed_y);//movemnt of fish//
				if (midF[i].fish1.getPosition().x > 1900 or midF[i].fish1.getPosition().x < 0) {//fish out of the frame//
					int y = rand() % (1000) + 50; //random place //
					midF[i].fish1.setPosition(0, y);

					for (int i = 0; i < 4; i++) {
						midF[i].speed_y = rand() % 5 - 3;  //speed of every fish//
					}

					midF[i].speed_x = abs(rand() % (5 - 3 + 1) + 3);
				}
				midF[i].animation += 0.005 * time;
				if (int(midF[i].animation) > 13) {
					midF[i].animation = 0;
				}

				if (int(midF[i].animation) == 0) {
					midF[i].fish1.setTextureRect(IntRect(2, 1 * 107, 165, 104));
				}
				if (int(midF[i].animation) != 0) {
					midF[i].fish1.setTextureRect(IntRect(int(midF[i].animation) * 171 + 2, 1 * 107, 165, 104));
				}



			}

			else {//the last 5//
				//midF[i].fish1.setScale(0.5, 0.5);
				midF[i].fish1.move(midF[i].speed_x, midF[i].speed_y);//movement of fish//
				if (midF[i].fish1.getPosition().x < 0 or midF[i].fish1.getPosition().x > 2200) {
					int y = rand() % (1000) + 50;//random place//
					midF[i].fish1.setPosition(1900, y);

					for (int i = 0; i < 4; i++) {
						midF[i].speed_y = rand() % 5 - 3;  //speed of every fish//
					}

					midF[i].speed_x = -abs(rand() % (5 - 3 + 1) + 3);
				}

				midF[i].animation += 0.005 * time;
				if (int(midF[i].animation) > 13) {
					midF[i].animation = 0;
				}

				if (int(midF[i].animation) == 0) {
					midF[i].fish1.setTextureRect(IntRect(2, 1 * 107, 165, 104));
				}
				if (int(midF[i].animation) != 0) {
					midF[i].fish1.setTextureRect(IntRect(int(midF[i].animation) * 171 + 2, 1 * 107, 165, 104));
				}


			}
		}

		for (int i = 0; i < 2; i++) {
			bigF[i].animation += 0.1;
			if (i < 1) {
				bigF[i].fish1.move(bigF[i].speed_x, bigF[i].speed_y);//movemnt of fish//
				if (bigF[i].fish1.getPosition().x > 2200 or bigF[i].fish1.getPosition().x < 0) {//fish out of the frame//
					int y = rand() % (1000) + 50; //random place //
					bigF[i].fish1.setPosition(0, y);
					bigF[i].speed_y = abs(rand() % (4 - 3 + 1) + 3);

					bigF[i].speed_x = abs(rand() % (5 - 3 + 1) + 3);

				}
				if (bigF[i].animation > 13) {
					bigF[i].animation = 0;
				}
				if (int(bigF[i].animation) == 0) {
					bigF[i].fish1.setTextureRect(IntRect(5, 2 * 163, 175, 155));
				}
				if (int(bigF[i].animation) != 0) {
					bigF[i].fish1.setTextureRect(IntRect(int(bigF[i].animation) * 181 + 2, 2 * 163, 175, 155));
				}
			}

			else {
				bigF[i].fish1.setScale(1, 1);
				bigF[i].fish1.move(bigF[i].speed_x, bigF[i].speed_y);//movement of fish//
				if (bigF[i].fish1.getPosition().x < 0 or bigF[i].fish1.getPosition().x > 2200) {
					int y = rand() % (1000) + 50;//random place//
					bigF[i].fish1.setPosition(1900, y);

					bigF[i].speed_y = -(abs(rand() % (4 - 3 + 1) + 3));

					bigF[i].speed_x = -abs(rand() % (5 - 3 + 1) + 3);
				}
				if (bigF[i].animation > 13) {
					bigF[i].animation = 0;
				}
				if (int(bigF[i].animation) == 0) {
					bigF[i].fish1.setTextureRect(IntRect(5, 2 * 163, 175, 155));
				}
				if (int(bigF[i].animation) != 0) {
					bigF[i].fish1.setTextureRect(IntRect(int(bigF[i].animation) * 181 + 2, 2 * 163, 175, 155));
				}

			}

		}

		//..............................playereating..............................//
		for (int i = 0; i < 8; i++) {
			if (player.player.getGlobalBounds().intersects(smallF[i].fish1.getGlobalBounds())) {


				int y = rand() % (1000) + 50; //random place //
				smallF[i].fish1.setPosition(0, y);

				for (int i = 0; i < 6; i++) {
					smallF[i].speed_y = rand() % 7 - 5;
				}
				player.collisionwtihfish = true;
				yummy = true;
				crunchy = false;
				chompy = false;

				s1.play();

				s1.play();
				if (frenzy_animation_x == 1 && frenzy_animation_y == 6) {
					score += 20;
				}
				else if (frenzy_animation_x == 2 && frenzy_animation_y == 6) {
					score += 30;
				}
				else if (frenzy_animation_x == 2 && frenzy_animation_y < 6) {
					score += 20;
				}
				else
					score += 10;

			}
			yumspr.setPosition(playerposition.x - 90, playerposition.y - 90);
			if (player.collisionwtihfish && yummy) {
				yumspr.setScale(1, 1);
			}
			if (visual_yum.getElapsedTime().asMilliseconds() > 10) {
				yumspr.setScale(0, 0);
				visual_yum.restart();
			}


			if (fish1_eaten < 20) {

				if (player.player.getGlobalBounds().intersects(midF[i].fish1.getGlobalBounds())) {

					midcollision = true;
					player.spawned = false;
					player.rect.left = 960; player.rect.top = -200;
					collision_check = true;
					if (collision_check == true)
						player.lives--;
					if (player.lives != 1)
						playerdie.play();
					if (player.lives == 0)
						pagenum = 5;
					if (indexsaved == false) {
						index = i;
						indexsaved = true;
					}
				}
				if (player.player.getGlobalBounds().intersects(bigF[i].fish1.getGlobalBounds())) {

					bigcollision = true;
					player.spawned = false;
					player.rect.left = 960; player.rect.top = -200;
					collision_check = true;
					player.lives--;
					if (player.lives != 1)
						playerdie.play();
					if (player.lives == 0)
						pagenum = 5;
					if (indexsaved == false) {
						index = i;
						indexsaved = true;
					}
				}
			}
			if ((fish1_eaten + fish2_eaten) >= 20 && (fish1_eaten + fish2_eaten) < 43) {
				player.scaleonx = 0.8;
				player.scaleony = 0.8;
				unlockedSpr1.setScale(0, 0);



				if (player.player.getGlobalBounds().intersects(midF[i].fish1.getGlobalBounds())) {
					int y = rand() % (1000) + 50;
					midF[i].fish1.setPosition(0, y);
					midF[i].speed_y = rand() % (4 - 3 + 1) + 3;
					yummy = false;
					crunchy = true;
					chompy = false;
					player.collisionwtihfish = true;
					s2.play();

					if (frenzy_animation_x == 1 && frenzy_animation_y == 6) {
						score += 40;
					}
					else if (frenzy_animation_x == 2 && frenzy_animation_y == 6) {
						score += 60;
					}
					else if (frenzy_animation_x == 2 && frenzy_animation_y < 6) {
						score += 40;
					}
					else
						score += 20;
					fish2_eaten++;
					totalF_eaten++;

				}
				crunchspr.setPosition(playerposition.x - 90, playerposition.y - 90);
				if (player.collisionwtihfish && crunchy) {
					crunchspr.setScale(1, 1);
				}
				if (visual_crunch.getElapsedTime().asMilliseconds() > 5) {
					crunchspr.setScale(0, 0);
					visual_crunch.restart();
				}
				if (player.player.getGlobalBounds().intersects(bigF[i].fish1.getGlobalBounds())) {
					bigcollision = true;
					player.spawned = false;
					player.rect.left = 960; player.rect.top = -200;
					collision_check = true;
					player.lives--;
					if (player.lives != 1)
						playerdie.play();
					if (player.lives == 0)
						pagenum = 5;
				}


			}
			if ((fish1_eaten + fish2_eaten + fish3_eaten) >= 43) {
				player.scaleonx = 1;
				player.scaleony = 1;
				unlockedSpr2.setScale(0, 0);



				if (player.player.getGlobalBounds().intersects(midF[i].fish1.getGlobalBounds())) {
					int y = rand() % (1000) + 50;
					midF[i].fish1.setPosition(0, y);
					midF[i].speed_y = rand() % (4 - 3 + 1) + 3;
					player.collisionwtihfish = true;
					yummy = false;
					crunchy = true;
					chompy = false;
					s2.play();

					if (frenzy_animation_x == 1 && frenzy_animation_y == 6) {
						score += 40;
					}
					else if (frenzy_animation_x == 2 && frenzy_animation_y == 6) {
						score += 60;
					}
					else if (frenzy_animation_x == 2 && frenzy_animation_y < 6) {
						score += 40;
					}
					else
						score += 20;
					fish2_eaten++;
					totalF_eaten++;

				}
				crunchspr.setPosition(playerposition.x - 90, playerposition.y - 90);
				if (player.collisionwtihfish && crunchy) {
					crunchspr.setScale(1, 1);
				}
				if (visual_crunch.getElapsedTime().asMilliseconds() > 5) {
					crunchspr.setScale(0, 0);
					visual_crunch.restart();
				}


				if (player.player.getGlobalBounds().intersects(bigF[i].fish1.getGlobalBounds())) {
					int y = rand() % (1000) + 50;
					bigF[i].fish1.setPosition(0, y);
					bigF[i].speed_y = rand() % (4 - 3 + 1) + 3;
					player.collisionwtihfish = true;
					yummy = false;
					crunchy = false;
					chompy = true;
					s3.play();

					if (frenzy_animation_x == 1 && frenzy_animation_y == 6 || frenzy_animation_x == 2 && frenzy_animation_y < 6) {
						score += 60;
					}
					else if (frenzy_animation_x == 2 && frenzy_animation_y == 6) {
						score += 90;
					}
					else
						score += 30;
					fish3_eaten++;
					totalF_eaten++;
				}
				chompspr.setPosition(playerposition.x - 90, playerposition.y - 90);
				if (player.collisionwtihfish && chompy) {
					chompspr.setScale(0.7, 0.7);
				}
				if (visual_chomp.getElapsedTime().asMilliseconds() > 5) {
					chompspr.setScale(0, 0);
					visual_chomp.restart();
				}
			}
			if (bigcollision == true) {
				bigeat += 0.02;
				if ((int)bigeat > 5) {
					bigeat = 0;
					bigcollision = false;
					indexsaved = false;
				}
				if (int(bigeat) == 0) {
					bigF[index].fish1.setTextureRect(IntRect(5, 5, 175, 155));
				}
				if (int(bigeat) != 0) {
					bigF[index].fish1.setTextureRect(IntRect(int(bigeat) * 181 + 2, 5, 175, 155));
				}
			}

			if (midcollision == true) {
				mideat += 0.02;
				if ((int)mideat > 4) {
					mideat = 0;
					midcollision = false;
					indexsaved = false;
				}
				if (int(mideat) == 0) {
					midF[index].fish1.setTextureRect(IntRect(2, 5, 165, 104));
				}
				if (int(mideat) != 0) {
					midF[index].fish1.setTextureRect(IntRect(int(mideat) * 171 + 2, 5, 165, 104));
				}
			}
			if (BarBlue.getSize().x < 600) {

				BarBlue.setSize(Vector2f(totalF_eaten * 10, 15));

			}

		}

		int HORIZONTAL = 1980, VERTICAL = 1040;
		for (int i = 0; i < 8; i++) {
			if (smallF[i].fish1.getPosition().y > VERTICAL) {
				smallF[i].speed_y = -abs(rand() % (6 - 4 + 1) + 4);
			}
			else if (smallF[i].fish1.getPosition().y < 150) {
				smallF[i].speed_y = abs(rand() % (6 - 4 + 1) + 4);
			}

			if (midF[i].fish1.getPosition().y > VERTICAL) {
				midF[i].speed_y = -abs(rand() % (6 - 4 + 1) + 4);
			}
			else if (midF[i].fish1.getPosition().y < 150) {
				midF[i].speed_y = abs(rand() % (6 - 4 + 1) + 4);
			}

			if (bigF[i].fish1.getPosition().y > 1000) {
				bigF[i].speed_y = -abs(rand() % (4 - 3 + 1) + 3);
			}
			else if (bigF[i].fish1.getPosition().y < 150) {
				bigF[i].speed_y = abs(rand() % (4 - 3 + 1) + 3);
			}
			// ..............................win & gameover condition......................... //
			if (player.lives == 0) {
				pagenum = 5;
				player.lives = 5;
				gameover.goverplayed = true;
				score = 0;
				fish1_eaten = 0;
				fish2_eaten = 0;
				fish3_eaten = 0;
				totalF_eaten = 0;
				BarBlue.setSize(Vector2f(0, 15));
				player.scaleonx = 0.5;
				player.scaleony = 0.5;
				yummy = false;
				crunchy = false;
				chompy = false;
				Frenzy.setTextureRect(IntRect(0, 0, 350.5, 120));
				frenzy_animation_y = 0;
				frenzy_animation_x = 1;
				x = 1;
				x1text.setString(to_string(x) + "X");
				x1text.setFillColor(Color::White);
				x1text.setOutlineColor(Color::Black);
				x1text.setOutlineThickness(10);

			}
			if (totalF_eaten == 60) {
				score = 0;
				player.lives = 5;
				fish1_eaten = 0;
				fish2_eaten = 0;
				fish3_eaten = 0;
				totalF_eaten = 0;
				BarBlue.setSize(Vector2f(0, 15));
				player.scaleonx = 0.5;
				player.scaleony = 0.5;
				pagenum = 7;
				yummy = false;
				crunchy = false;
				chompy = false;
				Frenzy.setTextureRect(IntRect(0, 0, 350.5, 120));
				frenzy_animation_y = 0;
				frenzy_animation_x = 1;
				x = 1;
				x1text.setString(to_string(x) + "X");
				x1text.setFillColor(Color::White);
				x1text.setOutlineColor(Color::Black);
				x1text.setOutlineThickness(10);
		
			}
			if (pagenum == 4) {
				retry = 1;
			}
			else if (pagenum == 9) {
				retry = 2;
			}
			//Done//

		}
		if (pagenum == 9) {
			//..............................barracuda..............................//
			if ((int)dangertime.getElapsedTime().asSeconds() == 5) {
				if (dangersoubdplayed == false) {
					danger.play();
					dangersoubdplayed = true;
				}
				dangertime.restart();
			}
			if (barracu.getElapsedTime().asSeconds() > 10) {
				// Update the sprite's position
				barracudaspr.move(speed, 0);
				// Check if the sprite has reached the left edge of the window
				if (barracudaspr.getPosition().x < 0 || barracudaspr.getPosition().x > 2500)
				{
					int y = (700 - 400 + 1) + 400;
					barracudaspr.setPosition(0, y);
					barracu.restart();
					dangertime.restart();
					dangersoubdplayed = false;
				}

			}
			//.............................barracudaanimation........................//
			barracudamovement += 0.2;

			barracudaspr.setTextureRect(IntRect(((int)barracudamovement * 271) + 8, (1 * 115) + 7, 260, 115));
			if ((int)barracudamovement > 12) {
				barracudamovement = 0;
			}

			//..............................barracuda eat..............................//
			if (barracudaspr.getGlobalBounds().intersects(player.player.getGlobalBounds())) {
				barrcudacollision = true;
				player.spawned = false;
				player.rect.left = 960; player.rect.top = -200;
				player.lives--;
			}
			if (barrcudacollision == true) {
				barracudacurrentframe += 0.2;
				if ((int)barracudacurrentframe > 5) {
					barracudacurrentframe = 0;
					barrcudacollision = false;
				}
				barracudaspr.setTextureRect(IntRect(((int)barracudacurrentframe * 271) + 8, 0 + 5, 260, 115));
			}
			//player.player.setScale(0,0);

			//..............................done..............................//

			if (oyster_open.getElapsedTime().asSeconds() > 10) {

				oysterspr.setTextureRect(IntRect(0 + 8, 0 + 5, 90, 90));
				oyster_open.restart();
				oysteranimationdone = false;
				oystercurrentframe = 0;
				pearleating = false;
				pearlspr.setScale(0, 0);
			}
			if (oyster_open.getElapsedTime().asSeconds() > 5) {
				if (oysteranimationdone == false)
					oystercurrentframe += 0.2;
				oysterspr.setTextureRect(IntRect(((int)oystercurrentframe * 101) + 8, 0 + 5, 90, 90));

			}
			if (player.player.getGlobalBounds().intersects(pearlspr.getGlobalBounds())) {
				score += 200;
				player.collisionwtihfish = true;
				pearleating = true;
				pearlpickup.play();
			}

			if (oystercurrentframe >= 4) {
				oysteranimationdone = true;
				oystercurrentframe = 4;
				if (pearleating == false)
					pearlspr.setScale(1.2, 1.2);
				else
					pearlspr.setScale(0, 0);
			}



		}
		//..............................Player update Function..............................//
		player.update(time, size);
		//..............................done..............................//

	}

	void drawlevel(RenderWindow& window) {
		if (pagenum == 4)
			window.draw(backgound_spr);
		if (pagenum == 9)
			window.draw(level2back);
		for (int i = 0; i < 10; i++) {
			window.draw(smallF[i].fish1);
		}
		for (int i = 0; i < 6; i++) {
			window.draw(midF[i].fish1);
		}
		for (int i = 0; i < 4; i++) {
			window.draw(bigF[i].fish1);
		}
		if (pagenum == 9) {
			window.draw(oysterspr);
			window.draw(pearlspr);
			window.draw(barracudaspr);
		}
		window.draw(player.player);
		window.draw(yumspr);
		window.draw(crunchspr);
		window.draw(chompspr);
		window.draw(ScoreBar);
		window.draw(scoretext);
		window.draw(Frenzy);
		window.draw(livestext);
		window.draw(BarBlack);
		window.draw(BarBlue);
		window.draw(Triangle1);
		window.draw(Triangle2);
		window.draw(minnowS);
		window.draw(surgeonS);
		window.draw(lionS);
		window.draw(unlockedSpr1);
		window.draw(unlockedSpr2);
		window.draw(x1text);
	}
}level1;
struct level3 {
	//define//
	Texture timerLevelBackgorund;
	Sprite timerLback;
	Texture timerpic;
	Sprite timerspr;

	Texture fish1_pic;

	SoundBuffer crunch1;
	Sound s1;

	Text x1text;
	int x;

	Texture fish;
	Vector2f size;

	Clock c;
	float time;

	//Fonts
	Font font1;
	Font font2;
	Font font3;


	//timer//
	int timer = 30;
	//fish no//
	int fishs = 2;

	//fish textures for scorebar
	Texture minnow;
	Sprite minnowS;

	//score bar texture//
	Texture scorebartimer;
	Sprite timerScoreBar;

	Text scoretext;
	string scorestring = to_string(score);

	Text zero;
	Text outof;

	Text countdown;
	string timerr = to_string(timer);

	Text fish1text;
	string fish1string = to_string(fish1_eaten);

	//fish eaten blackbar
	RectangleShape BarBlack;

	//fish eaten bluebar
	RectangleShape BarBlue;

	//timerclock//
	Clock timer_clock;
	//done//

	//FRENZY//
	Texture frenzy;
	Sprite Frenzy;
	SoundBuffer feeding_frenzy;
	Sound feedingfrenzy;
	SoundBuffer Double_frenzy;
	Sound doublefrenzy;
	bool restart = false;
	bool doublefrenzysoundplayed = false;
	//Done//

	void initialize() {

		timerLevelBackgorund.loadFromFile("timerbackground.png");

		timerLback.setTexture(timerLevelBackgorund);


		timerpic.loadFromFile("timerpic.jpeg");

		timerspr.setTexture(timerpic);
		timerspr.setPosition(850, 940);
		timerspr.setScale(0.2, 0.2);



		fish1_pic.loadFromFile("Minnow.png");




		for (int i = 0; i < 8; i++) {             //adjust postion//
			smallF[i].fish1.setTexture(fish1_pic);

			smallF[i].fish1.setScale(-1, 1);
			int y = rand() % (1060 - 50 + 1) + 50;

			for (int i = 0; i < 6; i++) {
				smallF[i].speed_y = rand() % 7 - 5;  //speed of every fish//
			}

			smallF[i].speed_x = abs(rand() % (6 - 4 + 1) + 4);


			if (i < 3) {
				smallF[i].fish1.setPosition(0, y);  //first 3 start from left//
			}
			else {
				smallF[i].fish1.setPosition(1900, y);// the rest form right//
			}
		}


		crunch1.loadFromFile("crunch1.wav");
		s1.setBuffer(crunch1);

		/*bool musicplay = true;
		Music music;
		music.openFromFile("mainmenu.ogg");
		music.setLoop(musicplay);
		music.play();
		*/

		fish.loadFromFile("PC Computer - Feeding Frenzy - Angelfish.png");

		size.x = 126;
		size.y = 106;
		player.input(fish, size);

		float time;

		//Fonts

		font1.loadFromFile("HTDaisyDelight-Regular-PersonalUse.otf");

		font2.loadFromFile("GUMDROP.ttf");

		font3.loadFromFile("digital.ttf");

		//timer//
		int timer = 30;

		//fish textures for scorebar

		minnow.loadFromFile("Minnow.png");

		minnowS.setTexture(minnow);
		minnowS.setPosition(370, 20);
		minnowS.setScale(-1.3, 1.3);

		//.......................Frenzyscore...................//
		x1text.setFont(font2);
		x1text.setPosition(1780, 16);
		x1text.setCharacterSize(80);

		x = 1;
		x1text.setString(to_string(x) + "X");
		x1text.setFillColor(Color::White);
		x1text.setOutlineColor(Color::Black);
		x1text.setOutlineThickness(10);

		//score bar texture//

		scorebartimer.loadFromFile("timerscorebar.jpeg");

		timerScoreBar.setTexture(scorebartimer);
		timerScoreBar.setScale(1.5, 1);


		scoretext.setFont(font2);
		scoretext.setString(scorestring);
		scoretext.setCharacterSize(50);
		scoretext.setPosition(1565, 40);


		zero.setFont(font3);
		zero.setString("00:");
		zero.setCharacterSize(50);
		zero.setPosition(900, 950);


		outof.setFont(font1);
		outof.setString(" out of 30");
		outof.setCharacterSize(50);
		outof.setPosition(1600, 950);


		countdown.setFont(font3);
		countdown.setString(timerr);
		countdown.setPosition(990, 950);
		countdown.setCharacterSize(50);



		fish1text.setFont(font1);
		fish1text.setString(fish1string);
		fish1text.setPosition(1570, 950);
		fish1text.setCharacterSize(50);


		//fish eaten blackbar

		BarBlack.setSize(Vector2f(600, 15));
		BarBlack.setPosition(300, 93);
		BarBlack.setFillColor(Color::Black);

		//fish eaten bluebar

		BarBlue.setSize(Vector2f(0, 15));
		BarBlue.setPosition(300, 93);
		BarBlue.setFillColor(Color::Cyan);

		//.............................Frenzy..............................//

		frenzy.loadFromFile("FRENZY.png");
		Frenzy.setTexture(frenzy);
		Frenzy.setScale(0.7, 0.7);
		Frenzy.setPosition(800, 135);
		Frenzy.setTextureRect(IntRect(0, 0, 351, 351));
		feeding_frenzy.loadFromFile("feedingFrenzy.wav");
		feedingfrenzy.setBuffer(feeding_frenzy);
		Double_frenzy.loadFromFile("doubleFrenzy.wav");
		doublefrenzy.setBuffer(Double_frenzy);

		//.............................Done..............................//
	}

	Clock c_frenzy;
	void update() {
		time = c.getElapsedTime().asMicroseconds();
		c.restart();
		time /= 650;
		if (time > 20) {
			time = 20;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			player.move_x = 0.5;
		}
		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.move_x = -0.5;
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player.move_y = -0.4;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			player.move_y = 0.4;
		}

		scorestring = to_string(score);
		scoretext.setString(scorestring);

		fish1string = to_string(fish1_eaten);
		fish1text.setString(fish1string);

		if (timer_clock.getElapsedTime().asSeconds() >= 1) {
			timer--;
			timer_clock.restart();
		}

		timerr = to_string(timer);
		countdown.setString(timerr);

		////.............................GREEN FRENZY..............................//

		if (restart == false) {
			c_frenzy.restart();
			restart = true;
		}
		for (int i = 0; i < 7; i++) {
			if (fish1_eaten == 30 || timer == 0) {
				Frenzy.setTextureRect(IntRect(0, 0, 350.5, 120));
				frenzy_animation_y = 0;
				frenzy_animation_x = 1;
				x = 1;
				x1text.setString(to_string(x) + "X");
				x1text.setFillColor(Color::White);
				x1text.setOutlineColor(Color::Black);
				x1text.setOutlineThickness(10);
			}
			if ((fish1_eaten + fish2_eaten + fish3_eaten >= fishs) && ((int)c_frenzy.getElapsedTime().asSeconds() <= 5)) {
				Frenzy.setTextureRect(IntRect(frenzy_animation_x * 351, frenzy_animation_y * 120, 350.5, 120));
				if ((frenzy_animation_y == 6) && (frenzy_animation_x == 2))
					continue;
				else
					frenzy_animation_y++;
				fishs += 3;
				c_frenzy.restart();
			}
			else if (fish1_eaten + fish2_eaten + fish3_eaten < fishs && c_frenzy.getElapsedTime().asSeconds() > 5) {
				if (frenzy_animation_y > 0) {
					frenzy_animation_y--;
					Frenzy.setTextureRect(IntRect(frenzy_animation_x * 351, frenzy_animation_y * 120, 350.5, 120));
					if (frenzy_animation_y == 0 && frenzy_animation_x == 1) {
						Frenzy.setTextureRect(IntRect(0, 0, 350.5, 120));
					}
					c_frenzy.restart();
				}
				c_frenzy.restart();

			}


		}
		if ((frenzy_animation_y == 7) && (frenzy_animation_x == 1)) {
			x = 2;
			x1text.setString(to_string(x) + "X");
			x1text.setFillColor(Color::Green);
			x1text.setOutlineColor(Color::Black);
			x1text.setOutlineThickness(10);

			feedingfrenzy.play();
			frenzy_animation_y = 0;
			frenzy_animation_x = 2;
		}
		//........................RED FRENZY.......................................//
		for (int i = 0; i < 7; i++) {
			if (fish1_eaten == 30 || timer == 0) {
				Frenzy.setTextureRect(IntRect(0, 0, 350.5, 120));
				frenzy_animation_y = 0;
				frenzy_animation_x = 1;
				x = 1;
				x1text.setString(to_string(x) + "X");
				x1text.setFillColor(Color::White);
				x1text.setOutlineColor(Color::Black);
				x1text.setOutlineThickness(10);
			}
			if ((fish1_eaten + fish2_eaten + fish3_eaten >= fishs) && ((int)c_frenzy.getElapsedTime().asSeconds() <= 5)) {
				Frenzy.setTextureRect(IntRect(frenzy_animation_x * 351, frenzy_animation_y * 120, 350.5, 120));
				if ((frenzy_animation_y == 6) && (frenzy_animation_x == 2))
					continue;
				else
					frenzy_animation_y++;
				fishs += 3;
				c_frenzy.restart();
			}

			else if (c_frenzy.getElapsedTime().asSeconds() > 3 && fish1_eaten + fish2_eaten + fish3_eaten < fishs) {
				if (frenzy_animation_y > 0) {
					frenzy_animation_y--;
					Frenzy.setTextureRect(IntRect(frenzy_animation_x * 351, frenzy_animation_y * 120, 350.5, 120));

					if (frenzy_animation_y == 0 && frenzy_animation_x == 2) {
						Frenzy.setTextureRect(IntRect(1 * 351, 6 * 120, 350.5, 120));
						frenzy_animation_y = 6;
						frenzy_animation_x = 1;
						if (frenzy_animation_y < 7 && frenzy_animation_y != 0) {

							frenzy_animation_y--;

							Frenzy.setTextureRect(IntRect(1 * 351, frenzy_animation_y * 120, 350.5, 120));
						}

						if (frenzy_animation_y == 0 && frenzy_animation_x == 1) {
							Frenzy.setTextureRect(IntRect(0, 0, 350.5, 120));
						}

						c_frenzy.restart();


					}
					c_frenzy.restart();
				}
				c_frenzy.restart();
			}
		}
		bool doublee = false;

		if ((frenzy_animation_y == 6) && (frenzy_animation_x == 2)) {
			x = 3;
			x1text.setFillColor(Color::Red);
			x1text.setString(to_string(x) + "X");
			x1text.setOutlineColor(Color::Black);
			x1text.setOutlineThickness(10);
			doublefrenzysoundplayed = true;
		}


		//.............................Done..............................//
		// ............................win & Gameoverr conditions ...................//
		if (timer == 0) {  //game over//
			pagenum = 5;
			timer = 30;
			player.lives = 5;
			score = 0;
			fish1_eaten = 0;
			totalF_eaten = 0;
			BarBlue.setSize(Vector2f(0, 15));
			player.scaleonx = 0.5;
			player.scaleony = 0.5;
		}

		if (fish1_eaten == 30) {
			timer = 30;
			player.lives = 5;
			score = 0;
			fish1_eaten = 0;
			totalF_eaten = 0;
			BarBlue.setSize(Vector2f(0, 15));
			player.scaleonx = 0.5;
			player.scaleony = 0.5;
			pagenum = 7;
		}
		l = 3;
		retry = 3;



		if ((frenzy_animation_y == 6) && (frenzy_animation_x == 2)) {
			x = 3;
			x1text.setFillColor(Color::Red);
			x1text.setString(to_string(x) + "X");
			x1text.setOutlineColor(Color::Black);
			x1text.setOutlineThickness(10);
		}

		//.............................Done..............................//

		for (int i = 0; i < 8; i++) {

			if (i < 4) {//first 5 fishes//
				smallF[i].fish1.move(smallF[i].speed_x, smallF[i].speed_y);//movement of fish//
				if (smallF[i].fish1.getPosition().x > 1920 or smallF[i].fish1.getPosition().x < -10) {//fish out of the frame//
					int y = rand() % (1000) + 50; //random place //
					smallF[i].fish1.setPosition(0, y);

					smallF[i].speed_x = abs(rand() % (6 - 4 + 1) + 4);


					for (int i = 0; i < 6; i++) {
						smallF[i].speed_y = rand() % 7 - 5;
					}
				}
				if (player.player.getGlobalBounds().intersects(smallF[i].fish1.getGlobalBounds())) {

					int y = rand() % (1000) + 50; //random place //
					smallF[i].fish1.setPosition(0, y);
					for (int i = 0; i < 6; i++) {
						smallF[i].speed_y = rand() % 7 - 5;
					}

					player.collisionwtihfish = true;
					s1.play();
					score += 10;

					fish1_eaten++;

				}
			}
			else {//the last 5//
				smallF[i].fish1.setScale(1, 1);
				smallF[i].fish1.move(smallF[i].speed_x, smallF[i].speed_y);//movement of fish//
				if (smallF[i].fish1.getPosition().x < 0 or smallF[i].fish1.getPosition().x > 1900) {
					int y = rand() % (1000) + 50;//random place//
					smallF[i].fish1.setPosition(1900, y);

					smallF[i].speed_x = -(abs(rand() % (6 - 4 + 1) + 4));


					for (int i = 0; i < 6; i++) {
						smallF[i].speed_y = rand() % 7 - 5;
					}

				}
				if (player.player.getGlobalBounds().intersects(smallF[i].fish1.getGlobalBounds())) {
					int y = rand() % (1000) + 50; //random place //
					smallF[i].fish1.setPosition(0, y);
					for (int i = 0; i < 6; i++) {
						smallF[i].speed_y = rand() % 7 - 5;
					}

					player.collisionwtihfish = true;
					s1.play();
					score += 10;

					fish1_eaten++;

				}
			}
		}

		for (int i = 0; i < 8; i++) {

			if (BarBlue.getSize().x < 600) {

				BarBlue.setSize(Vector2f(fish1_eaten * 20, 15));

			}

		}

		int HORIZONTAL = 1980, VERTICAL = 1040;
		for (int i = 0; i < 8; i++) {
			if (smallF[i].fish1.getPosition().y > VERTICAL) {
				smallF[i].speed_y = -abs(rand() % (6 - 4 + 1) + 4);
			}
			else if (smallF[i].fish1.getPosition().y < 150) {
				smallF[i].speed_y = abs(rand() % (6 - 4 + 1) + 4);
			}


		}
		player.update(time, size);
	}

	void draw1(RenderWindow& window) {
		window.draw(timerLback);
		for (int i = 0; i < 10; i++) {
			window.draw(smallF[i].fish1);
		}
		window.draw(player.player);
		window.draw(timerspr);
		window.draw(timerScoreBar);
		window.draw(scoretext);
		window.draw(Frenzy);
		window.draw(fish1text);
		window.draw(outof);
		window.draw(zero);
		window.draw(countdown);
		window.draw(BarBlack);
		window.draw(BarBlue);
		window.draw(minnowS);
		window.draw(x1text);


	}
}level3;

int main() {
	RenderWindow window(VideoMode(1920, 1080), " ", Style::Fullscreen);
	window.setFramerateLimit(60);

	//main menu//
	RectangleShape mouse(Vector2f(20, 20));
	mouse.setOrigin(mouse.getLocalBounds().width / 2 - 5, mouse.getLocalBounds().height / 2 - 10);//mouse//
	MENU menu(1920, 1080);
	Sprite backgroundd;
	Texture back;
	back.loadFromFile("main menu background.jpg");
	backgroundd.setTexture(back);
	//done//

	//gameoptions//
	gameoptions.setup();
	gameoptions.initialize();
	//done//

	//instructions//
	instructions.setup();
	instructions.initialize();
	//done// 

	//credits//
	credits.setup();
	credits.initialize();
	//done//

   //new game//
	Sound intro;
	SoundBuffer introbuffer;
	bool soundplayed = false;
	introbuffer.loadFromFile("stageIntro.OGG");
	intro.setBuffer(introbuffer);

	newgame.setup();
	newgame.initialize();

	//done//

	//level1//
	level1.intialize();
	level3.initialize();
	//done//



	//gameover//
	Sound gover;
	SoundBuffer overbuffer;
	overbuffer.loadFromFile("gameOver.wav");
	gover.setBuffer(overbuffer);
	gameover.setup();
	gameover.initialize();
	//done//

		// level menu //
	levelmenu.setup();
	levelmenu.initialize();
	//done//

	// win //
	win.setup();
	win.initialize();
	//done//



	while (true) {
		if (!window.isOpen()) {
			break;
		}
		if (pagenum == 0) {
			while (window.isOpen()) {
				Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == Event::Closed) {
						window.close();
					}

				}
				soundplayed = false;
				mouse.setPosition(Mouse::getPosition(window).x, Mouse::getPosition(window).y);
				menu.mousemove(mouse);
				menu.animation(mouse);
				if (menu.pressed() == 2 && Mouse::isButtonPressed(Mouse::Left)) {
					pagenum = 2;
					this_thread::sleep_for(chrono::milliseconds(100));
				}
				if (menu.pressed() == 3 && Mouse::isButtonPressed(Mouse::Left)) {
					pagenum = -1;
					this_thread::sleep_for(chrono::milliseconds(100));
				}
				if (menu.pressed() == 1 && Mouse::isButtonPressed(Mouse::Left)) {
					pagenum = 6;
					this_thread::sleep_for(chrono::milliseconds(100));
					//intro.play();
				}
				window.clear();
				if (pagenum != 0) {
					break;
				}
				window.draw(backgroundd);
				menu.draw(window);
				window.display();
			}
		}
		if (pagenum == -1) {
			window.close();
			break;
		}
		if (pagenum == 2) {
			while (window.isOpen()) {
				Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == Event::Closed) {
						window.close();
					}
				}
				gameoptions.gameoptionwindow(window, mouse, menu, soundplayed);
				window.clear();
				if (pagenum != 2) {
					break;
				}
				window.clear();
				gameoptions.gameoptionwindowdraw(window, mouse);
				window.display();
			}
		}
		if (pagenum == 3) {
			while (window.isOpen()) {
				Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == Event::Closed) {
						window.close();
					}
				}
				instructions.instructionwindow(window, mouse, menu, soundplayed);
				window.clear();
				if (pagenum != 3) {
					break;
				}
				instructions.instructionwindowdraw(window, mouse);
				window.display();
			}
		}
		if (pagenum == 10) {
			while (window.isOpen()) {
				Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == Event::Closed) {
						window.close();
					}
				}
				credits.creditswindow(window, mouse, menu, soundplayed);
				window.clear();
				if (pagenum != 10) {
					break;
				}
				credits.creditswindowdraw(window, mouse);
				window.display();
			}
		}
		if (pagenum == 1) {
			while (window.isOpen()) {
				Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == Event::Closed) {
						window.close();
					}
				}
				newgame.newgamewindow(window, mouse, menu, intro, soundplayed);
				window.clear();
				if (pagenum != 1) {
					break;
				}
				newgame.newgamewindowdraw(window, mouse);
				window.display();

			}
		}
		if (pagenum == 4) {
			while (window.isOpen()) {
				Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == Event::Closed) {
						window.close();
					}
				}

				level1.liveduration = level1.c.getElapsedTime().asMicroseconds();
				if (level1.liveduration == 4 || level1.collision_check == true) {
					level1.eating_clock.restart();
					level1.collision_check = false;
				}
				level1.update();

				window.clear();
				if (pagenum != 4) {
					break;
				}
				level1.drawlevel(window);
				window.display();
			}
		}
		if (pagenum == 5) {
			while (window.isOpen()) {
				Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == Event::Closed) {
						window.close();
					}
				}
				gameover.gameoverwindow(window, mouse, menu, gover);
				window.clear();
				if (pagenum != 5) {
					break;
				}
				window.clear();
				gameover.gameoverwindowdraw(window, mouse);
				window.display();
			}
		}
		if (pagenum == 6) {
			while (window.isOpen()) {
				Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == Event::Closed) {
						window.close();
					}
				}
				levelmenu.levelmenuwindow(window, mouse, menu, intro, soundplayed);
				window.clear();
				if (pagenum != 6) {
					break;
				}
				window.clear();
				levelmenu.levelmenudraw(window, mouse);
				window.display();

			}
		}
		if (pagenum == 7) {
			while (window.isOpen()) {
				Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == Event::Closed) {
						window.close();
					}
				}
				win.winwindow(window, mouse, menu);
				window.clear();
				if (pagenum != 7) {
					break;
				}
				window.clear();
				win.winwindowdraw(window, mouse);
				window.display();

			}
		}
		if (pagenum == 8) {
			while (window.isOpen()) {
				Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == Event::Closed) {
						window.close();
					}
				}
				level3.update();

				window.clear();
				if (pagenum != 8) {
					break;
				}
				window.clear();
				level3.draw1(window);
				window.display();
			}
		}
		if (pagenum == 9) {
			while (window.isOpen()) {
				Event ev;
				while (window.pollEvent(ev)) {
					if (ev.type == Event::Closed) {
						window.close();
					}
				}

				level1.liveduration = level1.c.getElapsedTime().asMicroseconds();
				if (level1.liveduration == 4 || level1.collision_check == true) {
					level1.eating_clock.restart();
					level1.collision_check = false;
				}
				level1.update();

				window.clear();
				if (pagenum != 9) {
					break;
				}
				level1.drawlevel(window);
				window.display();
			}
		}
	}
	return 0;
}







