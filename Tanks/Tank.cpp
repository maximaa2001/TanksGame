#include "Tank.h"

Tank::Tank(String image, float x, float y, int w, int h) {
	this->image = image;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	firstX = x;
	firstY = y;
	tank_texture.loadFromFile("images/" + image);
	tank_sprite.setTexture(tank_texture);
	tank_sprite.setTextureRect(IntRect(23, 31, this->w, this->h));
	tank_sprite.setOrigin(this->w / 2, this->h / 2);
	tank_sprite.setPosition(this->x, this->y);
	repeate_shot = 3000;
	this->dir = 1;
	isShot = false;
	isLife = true;
	isU = true;
	isR = true;
	isD = true;
	isLe = true;
}

void Tank::controls(float time, String* currentLevel, Sound& shot) {
	repeate_shot += time;
	if (Keyboard::isKeyPressed) {
		if (Keyboard::isKeyPressed(Keyboard::Up) && isU) {
			if (dir == 1 || dir == 3) {
				temp = w;
				w = h;
				h = w;
			}
			dir = 0;
			speed = 0.28;
			tank_sprite.setRotation(-90);
			isR = true;
			isD = true;
			isLe = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right) && isR) {
			if (dir == 0 || dir == 2) {
				temp = w;
				w = h;
				h = w;
			}
			dir = 1;
			speed = 0.28;
			tank_sprite.setRotation(0);
			isU = true;
			isD = true;
			isLe = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down) && isD) {
			if (dir == 1 || dir == 3) {
				temp = w;
				w = h;
				h = w;
			}
			dir = 2;
			speed = 0.28;
			tank_sprite.setRotation(90);
			isR = true;
			isU = true;
			isLe = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left) && isLe) {
			if (dir == 0 || dir == 2) {
				temp = w;
				w = h;
				h = w;
			}
			dir = 3;
			speed = 0.28;
			tank_sprite.setRotation(180);
			isR = true;
			isD = true;
			isU = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			if (repeate_shot >= 3000) {
				if (!isShot) {
					bullet = new Bullet("bullet.png", this->getX(), this->getY(), 0.5, this->getDir());
					shot.play();
					isShot = true;
					repeate_shot = 0;
				}
			}
		}
	}
	update(time, currentLevel);
}

void Tank::update(float time, String* currentLevel) {
	switch (dir)
	{
	case 0:
		speed_x = 0;
		speed_y = -speed;
		break;

	case 1:
		speed_x = speed;
		speed_y = 0;
		break;

	case 2:
		speed_x = 0;
		speed_y = speed;
		break;

	case 3:
		speed_x = -speed;
		speed_y = 0;
		break;
	}
	x += time * speed_x;
	y += time * speed_y;
	speed = 0;
	tank_sprite.setPosition(x, y);
	interactionWithMap(currentLevel);
}

void Tank::interactionWithMap(String* currentLevel) {
	for (int i = y / 50;i < HEIGH_MAP && i < (y + h) / 50 - 1; i++) {
		for (int j = x / 50;j < WIDTH_MAP && j < (x + w) / 50 - 1; j++) {
			if (currentLevel[i][j] == '0') {
				if (speed_y > 0) {
					y = i * 50 - h / 2;
					isD = false;
				}
				if (speed_y < 0) {
					y = i * 50 + 75;
					isU = false;
				}
				if (speed_x < 0) {
					x = j * 50 + 75;
					isLe = false;
				}
				if (speed_x > 0) {
					x = j * 50 - w / 2;
					isR = false;
				}
			}
		}
	}
}