#pragma once
#include <SFML/Graphics.hpp>
#include <SFML\System\String.hpp>
#include "Map.h"
#include <iostream>
#include <ctime>
using namespace sf;
using namespace std;

class Enemy {
	Texture enemy_texture;
	Sprite enemy_sprite;
	float x, y, speed, speed_x, speed_y, repeate_shot;
	int w, h;
	int  dir;
	bool isTurnX, isTurnY;
	String image;
public:
	Enemy(String image, float x, float y, int w, int h, int dir, float speed);

	Sprite getSprite() {return enemy_sprite;}

	float getX() {return x;}

	float getY() {return y;}

	int getW() {return w;}

	int getH() {return h;}

	int getDir() {return dir;}

	bool getIsTurnX() {return isTurnX;}

	bool getIsTurnY() {return isTurnY;}

	float getRepeatShot() {return repeate_shot;}

	void setRepeatShot(float repeatShot) {this->repeate_shot = repeatShot;}

	void incRepeatShot(float time) {this->repeate_shot += time;}

	void setX(float x) {this->x = x;}

	void setY(float y) {this->y = y;}

	void setSpeed(float speed) {this->speed = speed;}

	void setIsTurnX(bool isTurnX) {this->isTurnX = isTurnX;}

	void setIsTurnY(bool isTurnY) {this->isTurnY = isTurnY;}

	void setDir(int dir);

	void updateEnemy(float time);

	bool interactionWithMap(String* currentLevel);
};