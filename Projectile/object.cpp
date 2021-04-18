#include "object.h"

#define G 6.67430 * pow(10, -11)
#define M 5.972 * pow(10, 24)
#define R 6378 * pow(10, 3)
#define PI 3.14

object::object() :
	window(sf::VideoMode(800, 800), "2D Kinematics", sf::Style::Close),
	mass(20),
	t(0),
	angle(80),
	g(9.8),
	r(0),
	width(700),
	height(700),
	ux(0),
	uy(0),
	_shape() {
	_shape.setRadius(10.f);
	_shape.setFillColor(sf::Color::Red);
	_shape.setPosition(50.f, 680.f);
	}

void object::calcvelo() {
	ux = 100 * cos(angle * PI / 180);
	uy = 100 * sin(angle * PI / 180);
}

void object::run() {

	sf::Clock clock;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	calcvelo();
	while (window.isOpen()) {

		processevents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processevents();
			update(timePerFrame);
			render();
		}
	}
}

void object::processevents() {

	sf::Event event;

	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			window.close();
			break;
		}
		default:
			break;
		}
	}
}

void object::update(const sf::Time dt) {
	sf::Vector2f pos = _shape.getPosition();
	sf::Vector2f movement(0.f, 0.f);
	if (pos.y <= 680) 
	{	
		g = ((G * M) / ((R + pos.y) * (R + pos.y)));
		t += dt.asSeconds();		
		uy -= g * dt.asSeconds();
		movement.x = ux * dt.asSeconds();
		movement.y = -(uy * dt.asSeconds() + 0.5 * g * dt.asSeconds() * dt.asSeconds());
		_shape.move(movement);
		std::cout << pos.x << " " << pos.y <<" "<< dt.asSeconds()<< std::endl;
		std::cout << ux << " " << uy <<" "<<t<<std::endl;
	}
	else {
		if (ux > 0)
		{
			ux -= g * 0.8 * dt.asSeconds();
		}
		uy = -uy*0.9;
		uy -= g * dt.asSeconds();
		movement.x = ux * dt.asSeconds();
		movement.y = -(uy * dt.asSeconds() + 0.5 * g * dt.asSeconds() * dt.asSeconds());
		_shape.move(movement);
	}
}

void object::getsize() {
	sf::Vector2u size = window.getSize();
	unsigned int width = size.x - 50;
	unsigned int height = size.y - 50;
}

void object::render(){
	
	sf::Vertex line1[] =
	{
		sf::Vertex(sf::Vector2f(50.f, height)),
		sf::Vertex(sf::Vector2f(width, height))
	};
	sf::Vertex line2[] =
	{
		sf::Vertex(sf::Vector2f(50.f, 50)),
		sf::Vertex(sf::Vector2f(50.f, height))
	};

	window.clear();
	window.draw(line1, 2, sf::Lines);
	window.draw(line2, 2, sf::Lines);
	window.draw(_shape);
	window.display();
}