#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

/*

	Game supervisor class

*/

class Game
{
	private:
		//Window params
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event ev;

		//Mouse position
		sf::Vector2i mousePos;
		sf::Vector2f mousePosView;

		//Resources
		sf::Font font;

		//Text
		sf::Text uiText;

		//Game logic
		int credits;
		int creditsIn;
		int creditsOut;

		int numOfPlays;

		bool runAnimation;

		bool endGame;
		int numSlots;

		//Game objs
		std::vector<sf::RectangleShape> slots;
		sf::RectangleShape slot;

		//Private funcs
		void initVariables();
		void initWindow();
		void initFonts();
		void initText();
		void initSlots();

	public:
		//Constructors/Destructors
		Game();
		virtual ~Game();

		//Accessors
		const bool getWindowisOpen() const;
		const bool getEndGame() const;


		//Funcs
		void spawnSlots();
		void rollSlots();


		void pollEvents();
		void updateMousePositions();
		void updateText();
		void updateSlots();
		void update();

		void renderText(sf::RenderTarget& target);
		void renderSlots(sf::RenderTarget& target);
		void render();
};
