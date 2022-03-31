#include "Game.h"

//Private funcs

void Game::initVariables() {
	this->window = nullptr;


	this->credits = 0;
	this->creditsIn = 0;
	this->creditsOut = 0;

	this->numOfPlays = 0;

	this->runAnimation = false;

	this->endGame = false;
	this->numSlots = 55;


}


void Game::initWindow() {
	this->videoMode.height = 720;
	this->videoMode.width = 1280;
	this->window = new sf::RenderWindow(this->videoMode, "SlotMachine", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(24);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setPosition(
		static_cast <float>(10 + 100 * 8 + 10 * 4),
		static_cast<float> (30)
	);
	this->uiText.setString("NONE");
}

void Game::initSlots(){

	this->slot.setPosition(10.f,10.f);
	this->slot.setSize(sf::Vector2f(100.f,100.f));
	//this->slot.setScale(sf::Vector2f(0.5f,0.5f));
	this->slot.setFillColor(sf::Color::Blue);
	this->spawnSlots();

}


//Const/Dest
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initSlots();

}

Game::~Game() {
	delete this->window;
}



//Accessors

const bool Game::getWindowisOpen() const {
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Funcs

//Spawns each slot arranged in 5 lines of 10 columns = 50 slots
void Game::spawnSlots() {

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			this->slot.setPosition(
				static_cast<float>(10 + 70 * j + 10 * j),
				static_cast<float>(10 + 70 * i + 10 * i)
			);


			//Randomize slot type
			int type = rand() % 5;
			//Assign size and color by type
			switch (type)
			{
			case 0:
				this->slot.setFillColor(sf::Color::Magenta);
				break;
			case 1:
				this->slot.setFillColor(sf::Color::Blue);
				break;
			case 2:
				this->slot.setFillColor(sf::Color::Cyan);
				break;
			case 3:
				this->slot.setFillColor(sf::Color::Red);
				break;
			case 4:
				this->slot.setFillColor(sf::Color::Green);
				break;
			default:
				this->slot.setFillColor(sf::Color::Yellow);
				break;
			}

			this->slot.setSize(sf::Vector2f(70.f, 70.f));

			//spawn slot
			this->slots.push_back(this->slot);
		}
		
	}

}

void Game::rollSlots() {
	//Play animation to simulate roll
	//start roll if there are available credits and animation is not playing

	if (this->credits > 0 && !runAnimation)
	{
		//remove 1 credit
		this->credits -= 1;

		this->runAnimation = true;

	}


}



void Game::pollEvents() {

	//Event polling
	while (this->window->pollEvent(this->ev)) {

		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			if (this->ev.key.code == sf::Keyboard::Space) {
				this->rollSlots();
			}
			if (this->ev.key.code == sf::Keyboard::Right) {
				if (!this->runAnimation) {
					this->credits += 1 ;
					this->creditsIn += 1;
				}
			}
			if (this->ev.key.code == sf::Keyboard::Left) {
				if (this->credits > 0 && !this->runAnimation) {
					this->credits -= 1;
					this->creditsOut += 1;
				}
			}
			break;
		default:
			break;
		}
	}
}

void Game::updateMousePositions(){

	this->mousePos = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePos);

}

void Game::updateText() {

	std::stringstream ss;

	ss << "Credits: " << this->credits << "\n"
		<< "Credits In: " << this->creditsIn << "\n"
		<< "Credits Out: " << this->creditsOut << "\n"
		<< "Number of plays: " << this->numOfPlays << "\n"
		<< "\n\n\n\n"
		<< "Space: Start" << "\n"
		<< "Right Arrow: Add credits" << "\n"
		<< "Left Arrow : Remove credits" << "\n"
		<< "Esc: Quit" << "\n";



	this->uiText.setString(ss.str());
}

void Game::updateSlots(){

	
	//check slot position and remove if at bottom of window
	for (int i =0; i< this->slots.size();i++)
	{

		if (this->slots[i].getPosition().y > this->window->getSize().y)
		{
			this->slots.erase(this->slots.begin() + i);
		}
	}

	//Move slots

	if (runAnimation)
	{
		//run array of slots
		for (auto& e : this->slots)
		{
			e.move(0.f, 5.f);
		}

	}

	//if slots have disappeared reset game
	if (this->slots.size() < 1) {
		//stop animation
		this->runAnimation = false;
		//reset slots
		this->spawnSlots();
		//add +1 to number of plays
		this->numOfPlays += 1;
	}

}

void Game::update() {

	this->pollEvents();

	if (this->endGame == false ) {
		//Mouse position
		this->updateMousePositions();

		this->updateText();

		this->updateSlots();
	}
		

}

void Game::renderText(sf::RenderTarget& target) {
	target.draw(this->uiText);
}

void Game::renderSlots(sf::RenderTarget& target) {

	//Render slots
	for (auto& e : this->slots)
	{
		target.draw(e);
	}

}


void Game::render() {

	this->window->clear();

	//Draw game objects

	this->renderSlots(*this->window);

	this->renderText(*this->window);

	this->window->display();


}