#include "object.h"

static const float VIEW_H = 768.0f;

#define G 6.67430 * pow(10, -11)
#define M 5.972 * pow(10, 24)
#define R 6378 * pow(10, 3)
#define PI 3.14

object::object() :

	window(sf::VideoMode(800, 800), "2D Kinematics", sf::Style::Close | sf::Style::Resize),
	view(sf::Vector2f(0.f, 0.f), sf::Vector2f(768.f, 768.f)),
	mass(20),
	trail(sf::Vector2f(2.0f, 2.0f)),
	t(0),
	angle(75),
	g(9.8),
	r(0),
	width(700),
	height(700),
	ux(0),
	uy(0),
	_shape() {
	_shape.setRadius(10.f);
	//_shape.setOrigin(_shape.getRadius() / 2, _shape.getRadius() / 2);
	_shape.setFillColor(sf::Color::Red);
	_shape.setPosition(50.f, 680.f);
	}

void object::calcvelo() {
	ux = 100 * cos(angle * PI / 180);
	uy = 100 * sin(angle * PI / 180);
}

sf::Vector2f object::getposition() {
	return _shape.getPosition();
}

void object::resizeview(const sf::Window& window, sf::View& view) {
	float aspectratio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_H * aspectratio, VIEW_H);
}

void object::getsize() {
	sf::Vector2u size = window.getSize();
	unsigned int width = size.x - 50;
	unsigned int height = size.y - 50;
}

void object::run() {

	sf::Clock clock;
	view.zoom(2.f);
	const sf::Time timePerFrame = sf::seconds(1.0f / 120.0f);
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
		case sf::Event::Resized:
		{
			resizeview(window, view);
			view.zoom(2.f);
		}
		default:
			break;
		}
	}
}

void object::update(const sf::Time dt) {

	sf::Vector2f pos = getposition();
	sf::Vector2f movement(0.f, 0.f);
	if (pos.y <= 680) 
	{	
		g = ((G * M) / ((R + pos.y) * (R + pos.y)));				
		uy -= g * dt.asSeconds();
	}
	else {
		if (ux > 0)
		{
			ux -= g * 0.8 * dt.asSeconds();
		}
		if (uy < 0)
		{
			uy = -uy * 0.8;
		}
		uy -= g * dt.asSeconds();
	}
	t += dt.asSeconds();
	movement.x = ux * dt.asSeconds();
	movement.y = -(uy * dt.asSeconds() + 0.5 * g * dt.asSeconds() * dt.asSeconds());
	trail.setPosition(getposition());
	_shape.move(movement);
}

void object::render(){
	
	sf::Vertex line1[] =
	{
		sf::Vertex(sf::Vector2f(50.f, height)),
		sf::Vertex(sf::Vector2f(3000, height))
	};
	sf::Vertex line2[] =
	{
		sf::Vertex(sf::Vector2f(50.f, 50)),
		sf::Vertex(sf::Vector2f(50.f, height))
	};
	window.clear();
	view.setCenter(getposition());
	window.setView(view);
	window.draw(line1, 2, sf::Lines);
	window.draw(line2, 2, sf::Lines);
	window.draw(_shape);
	window.display();
}