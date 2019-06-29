#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#define MAP_WIDTH 600
#define MAP_HEIGHT 600

void move_square(sf::RectangleShape &square, int map_width, int map_height, char direction, std::vector<sf::RectangleShape> &tails);
void determine_direction(char &direction);
void set_bonus_position(sf::RectangleShape &bonus, int map_width, int map_height);
bool add_point(sf::RectangleShape &bonus, sf::RectangleShape &square, int &point, std::vector<sf::RectangleShape> &tails);
void move_tail(std::vector<sf::RectangleShape> &tails, sf::Vector2f position);

int main()
{
	/**
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}


	*****/

	//init random number generator
	srand(time(0));

	//Rendering Window


	sf::RenderWindow window(sf::VideoMode(MAP_WIDTH, MAP_HEIGHT), "Snake game");

	


	char direction = 'd';

	int count = 0;
	int point = 0;
	

	

	//Draw head square
	sf::RectangleShape square(sf::Vector2f(10, 10));
	square.setPosition(300, 300);
	square.setFillColor(sf::Color::Green);

	//bonus square

	sf::RectangleShape bonus(sf::Vector2f(10, 10));
	bonus.setFillColor(sf::Color::Red);
	bool change_position = true;


	//tails 

	std::vector<sf::RectangleShape> tails;
	






	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		if (change_position)
		{
			set_bonus_position(bonus, MAP_WIDTH, MAP_HEIGHT);
			change_position = false;
		}

		change_position = add_point(bonus, square, point, tails);

		determine_direction(direction);
		move_square(square, MAP_WIDTH, MAP_HEIGHT,direction, tails);

		
		
		//check if palyer and bonus overlap
		


		
		for (auto &i : tails)
			window.draw(i);
		window.draw(bonus);
		window.draw(square);

		window.display();

		//Lower the refresh rate
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		
	}

	return 0;
}


void set_bonus_position(sf::RectangleShape &bonus, int map_width, int map_height)
{
	sf::Vector2f position;
	
	int width_factor = map_width / 10;
	int height_factor = map_height / 10;

	position.x = fmod(abs(rand()), width_factor) * 10;
	position.y = fmod(abs(rand()), height_factor) * 10;

	bonus.setPosition(position);

}


void move_square(sf::RectangleShape &square, int map_width, int map_height, char direction, std::vector<sf::RectangleShape> &tails)
{
	sf::Vector2f tails_position = square.getPosition();
	if(direction == 'd')
		square.move(10, 0);
	else if(direction == 'w')
		square.move(0, -10);
	else if(direction == 'a')
		square.move(-10, 0);
	else
		square.move(0, 10);

	sf::Vector2f position = square.getPosition();
	

	position.x = fmod(position.x+map_width, map_width);
	position.y = fmod(position.y+map_height, map_height);

	square.setPosition(position);

	move_tail(tails, tails_position);

	

}

void determine_direction(char &direction)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (direction == 'd' || direction == 'a')
			direction = 'w';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (direction == 'w' || direction == 's')
			direction = 'd';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (direction == 'a' || direction == 'd')
			direction = 's';
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (direction == 'w' || direction == 's')
			direction = 'a';
	}
}




bool add_point(sf::RectangleShape &bonus, sf::RectangleShape &square, int &point, std::vector<sf::RectangleShape> &tails)
{
	if (bonus.getPosition() == square.getPosition())
	{
		sf::RectangleShape temp(sf::Vector2f(10, 10));
		temp.setFillColor(sf::Color::Green);
		tails.push_back(temp);


		++point;
		return true;
	}
	else
		return false;
}

void move_tail(std::vector<sf::RectangleShape> &tails, sf::Vector2f position)
{
	sf::Vector2f temp;
	for (auto &i : tails)
	{
		temp = i.getPosition();
		i.setPosition(position);
		position = temp;
	}
}