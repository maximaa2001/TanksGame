#pragma warning(disable : 4996) .
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML\System\String.hpp>
#include "Tank.h"
#include "Map.h"
#include "Bullet.h"
#include "Enemy.h"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace sf;
using namespace std;

int randDirX();
int randDirY();
bool isBarrierY(float x, float enemyY, float heroY, String* currentLevel);
bool isBarrierX(float y, float enemyX, float heroX, String* currentLevel);
void interactionWithMap(vector<Bullet*>& vector, String* currentLevel);
void interactionWithMap(Bullet* bullet, Tank& hero, vector<Enemy*>& vector, String* currentLevel);
void interectionWithHero(vector<Bullet*>& vector, Tank& hero);
void loadMenu(RenderWindow& window, int& menu, RectangleShape& rectangle, float& time, bool& isMenu, Tank& hero);
void destructionHero(RenderWindow& window, Tank& hero, bool& isMenu, Music& gameOver, bool& isPlayGameOver);

int wWinMain(int args, wchar_t* argc[])
{
	RenderWindow window(VideoMode(1200, 800), "Tanks");
	Tank hero("tank.png", 150, 70, 75, 52);

	Texture map_texture;
	map_texture.loadFromFile("images/map.png");

	Sprite map_sprite;
	map_sprite.setTexture(map_texture);

	RectangleShape rectangle(Vector2f(285, 50));
	rectangle.setFillColor(Color::Red);

	SoundBuffer bufferShotHero;
	bufferShotHero.loadFromFile("music/ShotHero.ogg");
	Sound shotHero(bufferShotHero);

	SoundBuffer bufferShotEnemy;
	bufferShotEnemy.loadFromFile("music/ShotEnemy.ogg");
	Sound shotEnemy(bufferShotEnemy);

	Music gameOverMus;
	gameOverMus.openFromFile("music/GameOver.ogg");
	bool isPlayGameOver = false;

	String currentLevel[16];

	Music youWinMus;
	youWinMus.openFromFile("music/YouWin.ogg");
	bool isPlayYouWin = false;

	Clock clock;
	float time;
	float timeShotEnemy = 3000;
	float timePressed = 0;
	float readyGamer = 0;
	float timeLevelCompleted = 0;
	bool LevelCompleted = false;
	int level = 1;
	const int MAX_LEVEL = 4;
	Vector2f vector_hero;
	Vector2f vector_enemy;

	vector<String*> levels;
	levels.push_back(level_1);
	levels.push_back(level_2);
	levels.push_back(level_3);
	levels.push_back(level_4);
	
	vector<Enemy*> enemyes;
	vector<Bullet*> bullets;


	bool isClash;
	bool startGame = false;
	bool loadEnemy = false;
	bool isMenu = true;
	int menu = 1;

	Font font;
	font.loadFromFile("DS Stamper.ttf");

	while (window.isOpen())
	{
		while (isMenu && window.isOpen()) {
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed) {
					window.close();
				}
			}
			enemyes.clear();
			bullets.clear();
			isPlayGameOver = false;
			isPlayYouWin = false;
			loadEnemy = false;
			level = 1;
			float t = clock.getElapsedTime().asMicroseconds();
			t = t / 800;
			clock.restart();
			timePressed += t;
			loadMenu(window, menu, rectangle, timePressed, isMenu, hero);
			readyGamer = 0;
		}
		time = clock.getElapsedTime().asMicroseconds();
		time = time / 800;
		clock.restart();

		timeShotEnemy += time;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		/*
		* Загрузка первого уровня
		*/
		
		for (int i = 0;i < levels.size();i++) {
			if (level-1 == i) {
				for (int j = 0;j <HEIGH_MAP;j++) {
					currentLevel[j] = levels[i][j];
				}
			}
		}
		if (!loadEnemy) {
			if (level == 1) {
				enemyes.push_back(new Enemy("tank.png", 350, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 600, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 500, 700, 75, 52, 1, 0.15));
				enemyes.push_back(new Enemy("tank.png", 850, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 1050, 700, 75, 52, 0, 0.15));
			}
			else if (level == 2) {
				enemyes.push_back(new Enemy("tank.png", 600, 100, 75, 52, 3, 0.15));
				enemyes.push_back(new Enemy("tank.png", 600, 700, 75, 52, 3, 0.15));
				enemyes.push_back(new Enemy("tank.png", 650, 450, 75, 52, 0, 0.15));
				enemyes.push_back(new Enemy("tank.png", 800, 70, 75, 52, 1, 0.15));
				enemyes.push_back(new Enemy("tank.png", 800, 700, 75, 52, 1, 0.15));
				enemyes.push_back(new Enemy("tank.png", 1100, 450, 75, 52, 3, 0.15));
			}
			else if (level == 3) {
				enemyes.push_back(new Enemy("tank.png", 100, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 1100, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 300, 730, 75, 52, 0, 0.15));
				enemyes.push_back(new Enemy("tank.png", 900, 730, 75, 52, 0, 0.15));
			}
			else if (level == 4) {
				enemyes.push_back(new Enemy("tank.png", 100, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 1100, 70, 75, 52, 2, 0.15));
				enemyes.push_back(new Enemy("tank.png", 450, 70, 75, 52, 3, 0.15));
				enemyes.push_back(new Enemy("tank.png", 650, 70, 75, 52, 1, 0.15));
				enemyes.push_back(new Enemy("tank.png", 950, 280, 75, 52, 3, 0.15));
				enemyes.push_back(new Enemy("tank.png", 100, 730, 75, 52, 1, 0.15));
				enemyes.push_back(new Enemy("tank.png", 1100, 730, 75, 52, 3, 0.15));
			}
			loadEnemy = true;
		}
		for (int i = 0; i < HEIGH_MAP; i++) {
			for (int j = 0; j < WIDTH_MAP; j++) {
				if (currentLevel[i][j] == '0') {
					map_sprite.setTextureRect(IntRect(0, 0, 50, 50));
				}
				if (currentLevel[i][j] == ' ') {
					map_sprite.setTextureRect(IntRect(50, 0, 50, 50));
				}
				map_sprite.setPosition(j * 50, i * 50);

				window.draw(map_sprite);
			}
		}
		Text timeToStartGame("", font, 100);
		timeToStartGame.setColor(Color::Red);
		timeToStartGame.setStyle(Text::Bold);
		readyGamer += time;
		if (readyGamer > 0 && readyGamer < 1000) {
			timeToStartGame.setString("3");
			timeToStartGame.setPosition(550, 350);
			window.draw(timeToStartGame);
		}
		else if (readyGamer > 1000 && readyGamer < 2000) {
			timeToStartGame.setString("2");
			timeToStartGame.setPosition(550, 350);
			window.draw(timeToStartGame);
		}
		else if (readyGamer > 2000 && readyGamer < 3000) {
			timeToStartGame.setString("1");
			timeToStartGame.setPosition(550, 350);
			window.draw(timeToStartGame);
		}
		else if (readyGamer > 3000 && readyGamer < 4000) {
			timeToStartGame.setString("Go");
			timeToStartGame.setPosition(520, 350);
			window.draw(timeToStartGame);
			startGame = true;
			hero.setIsLife(true);
		}
		if (startGame && hero.getIsLife()) {
			hero.controls(time, currentLevel, shotHero);// управление героем, его движение и взаимодействие с картой
			/*
			* Проверка выстелил ли герой
			*/
			if (hero.getIsShot()) {
				hero.getBullet()->update(time);// если выстрелил, движение пули
				interactionWithMap(hero.getBullet(), hero, enemyes, currentLevel); // взаимодействие пули с картой и врагами
				window.draw(hero.getBullet()->getSprite());// отображение пули
			}

			for (auto enemyLoop:enemyes) {
				enemyLoop->updateEnemy(time);//движение врагов
				enemyLoop->incRepeatShot(time);// инкремент времени выстрела
				bool isNotWall = enemyLoop->interactionWithMap(currentLevel);// проверка врезался ли враг в стену
				if (!isNotWall) {// если не врезался

					/*
					* движение врага влево или вправо при одинаковой координате X
					*/
					if (enemyLoop->getX() > hero.getX() - hero.getW() / 2 && enemyLoop->getX() < hero.getX() + hero.getW() / 2 && !isBarrierY(enemyLoop->getX(), enemyLoop->getY(), hero.getY(), currentLevel)) {//остановка при наличии героя на одной линии
						if (hero.getY() > enemyLoop->getY()) {
							enemyLoop->setDir(2);
							enemyLoop->setSpeed(0);// остановка и выстрел при находжении героя
							if (enemyLoop->getRepeatShot() >= 3000) {//выстрел каждые 3 секунды
								bullets.push_back(new Bullet("bullet.png", enemyLoop->getX(), enemyLoop->getY(), 0.5, enemyLoop->getDir()));
								shotEnemy.play();
								enemyLoop->setRepeatShot(0);
							}
						}
						if (hero.getY() < enemyLoop->getY()) {
							enemyLoop->setDir(0);
							enemyLoop->setSpeed(0);// остановка и выстрел при находжении героя
							if (enemyLoop->getRepeatShot() >= 3000) {//выстрел каждые 3 секунды
								bullets.push_back(new Bullet("bullet.png", enemyLoop->getX(), enemyLoop->getY(), 0.5, enemyLoop->getDir()));
								shotEnemy.play();
								enemyLoop->setRepeatShot(0);
							}
						}
						enemyLoop->setIsTurnX(true);
					}
					else {
						/*
						* вернуться к движению вдоль оси ОХ
						*/
						if (enemyLoop->getIsTurnX()) {
							enemyLoop->setDir(randDirX());
							enemyLoop->setSpeed(0.15);
							enemyLoop->setIsTurnX(false);
						}
					}
					/*
					*движение врага вверх и вниз при одинаковой координате Y
					*/
					if (enemyLoop->getY() > hero.getY() - hero.getH() / 2 && enemyLoop->getY() < hero.getY() + hero.getH() / 2 && !isBarrierX(enemyLoop->getY(), enemyLoop->getX(), hero.getX(), currentLevel)) {//остановка при наличии героя на одной линии
						if (hero.getX() > enemyLoop->getX()) {
							enemyLoop->setDir(1);
							enemyLoop->setSpeed(0);// остановка и выстрел при находжении героя
							if (enemyLoop->getRepeatShot() >= 3000) {//выстрел каждые 3 секунды
								bullets.push_back(new Bullet("bullet.png", enemyLoop->getX(), enemyLoop->getY(), 0.5, enemyLoop->getDir()));
								shotEnemy.play();
								enemyLoop->setRepeatShot(0);
							}
						}
						if (hero.getX() < enemyLoop->getX()) {
							enemyLoop->setDir(3);
							enemyLoop->setSpeed(0);// остановка и выстрел при находжении героя
							if (enemyLoop->getRepeatShot() >= 3000) {//выстрел каждые 3 секунды
								bullets.push_back(new Bullet("bullet.png", enemyLoop->getX(), enemyLoop->getY(), 0.5, enemyLoop->getDir()));
								shotEnemy.play();
								enemyLoop->setRepeatShot(0);
							}
						}
						enemyLoop->setIsTurnY(true);
					}
					else {
						/*
						* вернуться к движению вдоль оси OY
						*/
						if (enemyLoop->getIsTurnY()) {
							enemyLoop->setDir(randDirY());
							enemyLoop->setSpeed(0.15);
							enemyLoop->setIsTurnY(false);
						}
					}
				}
			}
			for (auto bulletLoop:bullets) {//перебор всех вражеских пуль
				bulletLoop->update(time);//движение пуль
				window.draw(bulletLoop->getSprite());//отображение пули
			}
			interactionWithMap(bullets, currentLevel);// их взаимодействие с картой
			interectionWithHero(bullets, hero);// их взаимодействие с героем

			for (int index = 0;index<enemyes.size();index++) { //столкновения врагов
				switch (enemyes[index]->getDir())
			  {
				case 0: vector_enemy.x = enemyes[index]->getX();
					vector_enemy.y = enemyes[index]->getY() - enemyes[index]->getH() / 2;
					break;
				case 1: vector_enemy.x = enemyes[index]->getX() + enemyes[index]->getW() / 2;
					vector_enemy.y = enemyes[index]->getY();
					break;
				case 2: vector_enemy.x = enemyes[index]->getX();
					vector_enemy.y = enemyes[index]->getY() + enemyes[index]->getH() / 2;
					break;
			     case 3: vector_enemy.x = enemyes[index]->getX() - enemyes[index]->getW() / 2;
					vector_enemy.y = enemyes[index]->getY();
					break;
				}
				//isClash = false;
				for (int i = vector_enemy.x - enemyes[index]->getW() / 2;i <= vector_enemy.x + enemyes[index]->getW() / 2;i++) {
					for (int j = vector_enemy.y - enemyes[index]->getH() / 2;j <= vector_enemy.y + enemyes[index]->getH() / 2;j++) {
						int k = index+1;
						while (k<enemyes.size()) {
							if (i >= enemyes[k]->getX() - enemyes[k]->getW() / 2 && i <= enemyes[k]->getX() + enemyes[k]->getW() / 2 &&
								j >= enemyes[k]->getY() - enemyes[k]->getH() / 2 && j <= enemyes[k]->getY() + enemyes[k]->getH() / 2) {

								if (enemyes[index]->getDir() == 0 || enemyes[index]->getDir() == 2) {
									enemyes[index]->setDir(randDirX());
								}
								else if (enemyes[index]->getDir() == 1 || enemyes[index]->getDir() == 3) {
									enemyes[index]->setDir(randDirY());
								}

								if (enemyes[k]->getDir() == 0 || enemyes[k]->getDir() == 2) {
									enemyes[k]->setDir(randDirX());
								}
								else if (enemyes[k]->getDir() == 1 || enemyes[k]->getDir() == 3) {
									enemyes[k]->setDir(randDirY());
								}
							}
							k++;
						}
					}
					//if (isClash) {
					//	break;
					//}
				}
			}

			for (auto enemyLoop:enemyes) { // столкновения героя и врагов
				switch (hero.getDir())
				{
				case 0: vector_hero.x = hero.getX();
					vector_hero.y = hero.getY() - hero.getH() / 2;
					break;
				case 1: vector_hero.x = hero.getX() + hero.getW() / 2;
					vector_hero.y = hero.getY();
					break;
				case 2: vector_hero.x = hero.getX();
					vector_hero.y = hero.getY() + hero.getH() / 2;
					break;
				case 3: vector_hero.x = hero.getX() - hero.getW() / 2;
					vector_hero.y = hero.getY();
					break;
				}
				isClash = false;
				for (int i = vector_hero.x - hero.getW() / 2;i <= vector_hero.x + hero.getW() / 2;i++) {
					for (int j = vector_hero.y - hero.getH() / 2;j <= vector_hero.y + hero.getH() / 2;j++) {
						if (i >= enemyLoop->getX() - enemyLoop->getW() / 2 && i <= enemyLoop->getX() + enemyLoop->getW() / 2 &&
							j >= enemyLoop->getY() - enemyLoop->getH() / 2 && j <= enemyLoop->getY() + enemyLoop->getH() / 2) {
							if (hero.getDir() == 0) {
								hero.setY(hero.getY() + 2);
								isClash = true;
								break;
							}
							else if (hero.getDir() == 1) {
								hero.setX(hero.getX() - 2);
								isClash = true;
								break;
							}
							else if (hero.getDir() == 2) {
								hero.setY(hero.getY() - 2);
								isClash = true;
								break;
							}
							else if (hero.getDir() == 3) {
								hero.setX(hero.getX() + 2);
								isClash = true;
								break;
							}
						}
					}
					if (isClash) {
						break;
					}
				}
			}
			if (enemyes.size() == 0) {
				startGame = false;
				bullets.clear();
				LevelCompleted = true;
				timeLevelCompleted = 0;
			}
		}
		if (LevelCompleted) {
			if (level < MAX_LEVEL) {
				Text levelCompleted("Level completed", font, 70);
				levelCompleted.setColor(Color::Red);
				levelCompleted.setStyle(Text::Bold);
				levelCompleted.setPosition(300, 380);
				timeLevelCompleted += time;
				hero.setRepeatShot(3000);
				if (timeLevelCompleted < 3000) {
					window.draw(levelCompleted);
				}
				else {
					readyGamer = 0;
					LevelCompleted = false;
					level++;
					loadEnemy = false;
					if (level == 2) {
						hero.setX(100);
						hero.setY(100);
					}
					else if (level == 3) {
						hero.setX(600);
						hero.setY(500);
					}
					else if (level == 4) {
						hero.setX(550);
						hero.setY(650);
					}
				}
			}
			else if (level == MAX_LEVEL) {
				if (!isPlayYouWin) {
					youWinMus.play();
					youWinMus.setLoop(true);
					isPlayYouWin = true;
				}
				Text YouWin("You Win", font, 100);
				Text Continue("Press ESCAPE to exit in main menu", font, 30);
				YouWin.setColor(Color::Red);
				Continue.setColor(Color::White);
				YouWin.setStyle(Text::Bold);
				Continue.setStyle(Text::Bold);
				YouWin.setPosition(400, 350);
				Continue.setPosition(350, 450);
				window.draw(YouWin);
				window.draw(Continue);
				if (Keyboard::isKeyPressed(Keyboard::Escape)) {
					isMenu = true;
					LevelCompleted = false;
					youWinMus.stop();
				}
			}
		}
		if (hero.getIsLife() && startGame) {
			window.draw(hero.getSprite());
			for (int i = 0; i<enemyes.size();i++) {
				window.draw(enemyes[i]->getSprite());
			}
		}
		if (!hero.getIsLife()) {
			startGame = false;
			destructionHero(window, hero, isMenu, gameOverMus, isPlayGameOver);
			if (!isPlayGameOver) {
				gameOverMus.play();
				gameOverMus.setLoop(true);
				isPlayGameOver = true;
			}

		}
		window.display();
	}
	return 0;
}

int randDirX() {// рандомное движение вдоль оси OX
	int number = rand() % 2;
	if (number == 0) {
		number = 3;
	}
	return number;
}

int randDirY() {// рандомное движение вдоль оси OY
	int number = rand() % 2;
	if (number == 1) {
		number = 2;
	}
	return number;
}

bool isBarrierY(float x, float enemyY, float heroY, String* currentLevel) {// проверка на наличие препятствия вдоль оси OY
	bool isBarrierY = false;
	int enemyX = x / 50;
	if (enemyY / 50 < heroY / 50) {
		for (int i = enemyY / 50; i < heroY / 50;i++) {
			if (currentLevel[i][enemyX] == '0') {
				isBarrierY = true;
				break;
			}
		}
	}
	else if (heroY / 50 < enemyY / 50) {
		for (int i = heroY / 50; i < enemyY / 50;i++) {
			if (currentLevel[i][enemyX] == '0') {
				isBarrierY = true;
				break;
			}
		}
	}
	return isBarrierY;
}

bool isBarrierX(float y, float enemyX, float heroX, String* currentLevel) {// проверка на наличие препятствия вдоль оси OX
	bool isBarrierX = false;
	int enemyY = y / 50;
	if (enemyX / 50 < heroX / 50) {
		for (int i = enemyX / 50; i < heroX / 50;i++) {
			if (currentLevel[enemyY][i] == '0') {
				isBarrierX = true;
				break;
			}
		}
	}
	else if (heroX / 50 < enemyX / 50) {
		for (int i = heroX / 50; i < enemyX / 50;i++) {
			if (currentLevel[enemyY][i] == '0') {
				isBarrierX = true;
				break;
			}
		}
	}
	return isBarrierX;
}

void interactionWithMap(vector<Bullet*>& vector, String* currentLevel) {// взаимодействие с картой вражеских пуль
	int k = 0;
	while (k<vector.size()) {
		int i = vector[k]->getY() / 50;
		int j = vector[k]->getX() / 50;
		if (currentLevel[i][j] == '0') {
			delete vector[k];
			vector.erase(vector.begin()+k);
		}
		k++;
	}
}
void interectionWithHero(vector<Bullet*>& vector, Tank& hero) {
	int k = 0;
	while (k < vector.size()) {
		if (vector[k]->getX() >= hero.getX() - hero.getW() / 2 && vector[k]->getX() <= hero.getX() + hero.getW() / 2 &&
			vector[k]->getY() >= hero.getY() - hero.getH() / 2 && vector[k]->getY() <= hero.getY() + hero.getW() / 2) {
			if (hero.getIsShot()) {
				delete hero.getBullet();
				hero.setIsShot(false);
			}
			hero.setIsLife(false);
		}
		k++;
	}
}

void interactionWithMap(Bullet* bullet, Tank& hero, vector<Enemy*>& vector, String* currentLevel) {// взаимодействие с картой пуль героя
	int i = (bullet)->getY() / 50;
	int j = (bullet)->getX() / 50;
	if (currentLevel[i][j] == '0') {
		delete bullet;
		hero.setIsShot(false);
	}
	else {
		int k = 0;
		while (k<vector.size()) {
			if (bullet->getX() >= vector[k]->getX() - vector[k]->getW() / 2 && bullet->getX() <= vector[k]->getX() + vector[k]->getW() / 2 &&
				bullet->getY() >= vector[k]->getY() - vector[k]->getH() / 2 && bullet->getY() <= vector[k]->getY() + vector[k]->getH() / 2) {
				delete vector[k];
				vector.erase(vector.begin()+k);
				delete bullet;
				hero.setIsShot(false);
				break;
			}
			k++;
		}
	}
}

void loadMenu(RenderWindow& window, int& menu, RectangleShape& rectangle, float& time, bool& isMenu, Tank& hero) {
	if (menu == 1) {
		rectangle.setPosition(790, 300);
	}
	Texture menu_tank, fon;
	menu_tank.loadFromFile("images/menu_tank.png");
	fon.loadFromFile("images/fon.jpg");
	Sprite menu_1(menu_tank);
	Sprite fon_sprite(fon);
	menu_1.setPosition(100, 100);
	fon_sprite.setPosition(0, 0);
	Font font;
	font.loadFromFile("DS Stamper.ttf");
	Text StartGame("Начать игру", font, 40);
	Text AboutGame("Об игре", font, 40);
	Text Exit("Выход", font, 40);
	StartGame.setColor(Color::White);
	AboutGame.setColor(Color::White);
	Exit.setColor(Color::White);
	StartGame.setStyle(Text::Bold);
	AboutGame.setStyle(Text::Bold);
	Exit.setStyle(Text::Bold);
	StartGame.setPosition(800, 300);
	AboutGame.setPosition(840, 380);
	Exit.setPosition(860, 460);
	if (Keyboard::isKeyPressed) {
		if (time > 200) {
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				if (menu == 1) {
					rectangle.setPosition(790, 380);
					menu = 2;
				}
				else if (menu == 2) {
					rectangle.setPosition(790, 460);
					menu = 3;
				}
				else if (menu == 3) {
					rectangle.setPosition(790, 300);
					menu = 1;
				}
				time = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				if (menu == 1) {
					rectangle.setPosition(790, 460);
					menu = 3;
				}
				else if (menu == 2) {
					rectangle.setPosition(790, 300);
					menu = 1;
				}
				else if (menu == 3) {
					rectangle.setPosition(790, 380);
					menu = 2;
				}
				time = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				if (menu == 1) {
					isMenu = false;
					hero.setX(hero.getFirstX());
					hero.setY(hero.getFirstY());
				}
				else if (menu == 2) {
					window.clear();
					while (!Keyboard::isKeyPressed(Keyboard::Escape) && window.isOpen()) {
						Text title_1("Об игре", font, 40);
						Text About(" Данное игровое программное средство написано студентом \n Белорусского Государственного Университета Информатики и \n Радиоэлектроники Авсюкевичем Максимом. Цель игры : уничтожение \n всех вражеских танков.", font, 30);
						Text title_2("Обратная связь", font, 40);
						Texture qr_code;
						qr_code.loadFromFile("images/qr.png");
						Sprite qr_sprite(qr_code);
						title_1.setColor(Color::Red);
						About.setColor(Color::White);
						title_2.setColor(Color::Red);
						title_1.setStyle(Text::Bold);
						About.setStyle(Text::Bold);
						title_2.setStyle(Text::Bold);
						title_1.setPosition(500, 0);
						About.setPosition(0, 60);
						title_2.setPosition(430, 250);
						qr_sprite.setPosition(400, 350);
						window.draw(fon_sprite);
						window.draw(title_1);
						window.draw(About);
						window.draw(title_2);
						window.draw(qr_sprite);
						window.display();
						Event event;
						while (window.pollEvent(event))
						{
							if (event.type == Event::Closed)
								window.close();
						}
					}
				}
				else if (menu == 3) {
					window.close();
				}
			}
		}
	}
	window.draw(fon_sprite);
	window.draw(menu_1);
	window.draw(rectangle);
	window.draw(StartGame);
	window.draw(AboutGame);
	window.draw(Exit);
	window.display();
}

void destructionHero(RenderWindow& window, Tank& hero, bool& isMenu, Music& gameOverMus, bool& isPlayGameOver) {
	Font font;
	font.loadFromFile("DS Stamper.ttf");
	Text GameOver("Game Over", font, 100);
	Text ClickToContinue("Press LEFT SHIFT to continue", font, 30);
	GameOver.setColor(Color::Red);
	ClickToContinue.setColor(Color::White);
	GameOver.setStyle(Text::Bold);
	ClickToContinue.setStyle(Text::Bold);
	GameOver.setPosition(300, 300);
	ClickToContinue.setPosition(350, 420);
	window.draw(GameOver);
	window.draw(ClickToContinue);
	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		isMenu = true;
		hero.setIsLife(true);
		gameOverMus.stop();
	}
}