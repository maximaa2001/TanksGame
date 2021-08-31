#include "Enemy.h"

Enemy::Enemy(String image, float x, float y, int w, int h, int dir, float speed) {
	this->image = image;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	enemy_texture.loadFromFile("images/" + image);
	enemy_sprite.setTexture(enemy_texture);
	enemy_sprite.setTextureRect(IntRect(149, 31, this->w, this->h));
	enemy_sprite.setOrigin(this->w / 2, this->h / 2);
	enemy_sprite.setPosition(this->x, this->y);
	repeate_shot = 3000;
	this->dir = dir;
	this->speed = speed;
	isTurnX = false;
	isTurnY = false;
}

void Enemy::setDir(int dir) {
	int temp;
	if (dir == 0 || dir == 2) {
		if (this->dir == 1 || this->dir == 3) {
			temp = w;
			w = h;
			h = w;
		}
	}
	else if (dir == 1 || dir == 3) {
		if (this->dir == 0 || this->dir == 2) {
			temp = w;
			w = h;
			h = w;
		}
	}
	this->dir = dir;
}

void Enemy::updateEnemy(float time) {
	switch (dir)
	{
	case 0:
		enemy_sprite.setRotation(90);
		speed_x = 0;
		speed_y = -speed;
		break;

	case 1:

		enemy_sprite.setRotation(180);
		speed_x = speed;
		speed_y = 0;
		break;

	case 2:

		enemy_sprite.setRotation(-90);
		speed_x = 0;
		speed_y = speed;
		break;

	case 3:

		enemy_sprite.setRotation(0);
		speed_x = -speed;
		speed_y = 0;
		break;
	}
	x += time * speed_x;
	y += time * speed_y;
	enemy_sprite.setPosition(x, y);
}

bool Enemy::interactionWithMap(String* currentLevel) {
	bool q = false;
	for (int i = y / 50;i < HEIGH_MAP && i < (y + h) / 50 - 1; i++) {
		for (int j = x / 50;j < WIDTH_MAP && j < (x + w) / 50 - 1; j++) {
			if (currentLevel[i][j] == '0') {
				if (speed_y < 0) {
					setY(getY() + 5);
					dir = 2;
					q = true;
				}
				if (speed_x > 0) {
					setX(getX() - 5);
					dir = 3;
					q = true;
				}
				if (speed_y > 0) {

					setY(getY() - 5);
					dir = 0;
					q = true;
				}
				if (speed_x < 0) {
					setX(getX() + 5);
					dir = 1;
					q = true;
				}
			}
		}
	}
	return q;
}