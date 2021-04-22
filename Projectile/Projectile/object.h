#pragma once
#include<iostream>
#include<cmath>
#include<SFML/Graphics.hpp>

using namespace std;

#define G 6.67430 * pow(10, -11)
#define M 5.972 * pow(10, 24)
#define R 6378 * pow(10, 3)
#define PI 3.14

class object
{
public:

	object();
	void run();

private:

	void getsize();
	void processevents();
	void update(const sf::Time dt);
	void render();
	void calcvelo();
	sf::Vector2f getposition();
	void resizeview(const sf::Window& window, sf::View &view);

private:

	sf::View view;
	sf::RenderWindow window;
	sf::RectangleShape trail;
	sf::CircleShape _shape;
	int mass;
	double ux;
	double uy;
	double angle;
	double g;
	int width;
	int height;
	double r;
	double t;
	sf::Vector2u size;
};