#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System\String.hpp>
using namespace sf;
using namespace std;

class Bullet {
private:
	Texture bullet_texture;
	Sprite bullet_sprite;
	float x, y, speed, speed_x, speed_y;
	int dir;
	String image;
public:
	Bullet(String image, float x, float y, float speed, float dir);

	void update(float time);

	Sprite getSprite() {return bullet_sprite;}

	float getX() {return x;}

	float getY() {return y;}

	void setX(float x) {this->x = x;}

	void setY(float y) {this->y = y;}
};