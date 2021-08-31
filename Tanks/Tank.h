#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML\System\String.hpp>
#include "Map.h"
#include "Bullet.h"
using namespace sf;
using namespace std;

class Tank {
private:
	Texture tank_texture;
	Sprite tank_sprite;
	float x, y, firstX, firstY, speed, speed_x, speed_y, repeate_shot;
	int w, h, temp;
	int dir;
	bool isLife, isShot, isU, isR, isD, isLe;
	String image;
	Bullet* bullet;
public:
	Tank(String image, float x, float y, int w, int h);

	Sprite getSprite() {return tank_sprite;}

	Bullet* getBullet() {return bullet;}

	float getX() {return x;}

	float getFirstX() {return firstX;}

	float getY() {return y;}

	float getFirstY() {return firstY;}

	bool getIsShot() {return isShot;}

	void setIsShot(bool isShot) {this->isShot = isShot;}

	void setRepeatShot(float repeate_shot) {this->repeate_shot = repeate_shot;}

	int getDir() {return dir;}

	void setX(float x) {this->x = x;}

	void setIsLife(bool isLife) {this->isLife = isLife;}

	void setY(float y) {this->y = y;}

	int getW() {return w;}

	int getH() {return h;}

	bool getIsLife() {return isLife;}

	void setSpeed(float speed) {this->speed = speed;}

	void controls(float time, String* currentLevel, Sound& shot);

	void update(float time, String* currentLevel);

	void interactionWithMap(String* currentLevel);
};