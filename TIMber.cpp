#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#define TOPSCORE 5
#define FILENAME "score.txt"

using namespace sf;
using namespace std;

void saveScoreFile(string name, int score);
void readScoreFile();
void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

struct ScoreData
{
	string name;
	int score;
};
ScoreData scoreData[TOPSCORE + 1];

int main()
{
	VideoMode vm(1920, 1080);
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	readScoreFile();


	// initialize Menu
	//============ bgMenu	=================
	Texture bgMenu;
	bgMenu.loadFromFile("Graphics/menu");
	Sprite spriteBgMenu;
	spriteBgMenu.setTexture(bgMenu);
	spriteBgMenu.setPosition(0, 0);

	//============ TITLE	=================
	Texture title;
	title.loadFromFile("Graphics/logo.png");
	Sprite spriteTitle;
	spriteTitle.setTexture(title);
	spriteTitle.setPosition(765, 80);

	//============ BUTTONPLAY	=================
	Texture buttonGame;
	buttonGame.loadFromFile("Graphics/button1");
	Sprite spriteButtonGame;
	spriteButtonGame.setTexture(buttonGame);
	spriteButtonGame.setPosition(850, 228);

	//============ BUTTONSCORE	=================
	Texture buttonScore;
	buttonScore.loadFromFile("Graphics/button2");
	Sprite spriteButtonScore;
	spriteButtonScore.setTexture(buttonScore);
	spriteButtonScore.setPosition(850, 428);

	//============ BUTTONQUIT	=================
	Texture  buttonQuit;
	buttonQuit.loadFromFile("Graphics/button3");
	Sprite spriteButtonQuit;
	spriteButtonQuit.setTexture(buttonQuit);
	spriteButtonQuit.setPosition(850, 628);

	sf::Text explainText1;
	Font explain;
	explain.loadFromFile("fonts/TA16BIT-Regular.otf");
	explainText1.setFont(explain);
	explainText1.setCharacterSize(18);
	explainText1.setFillColor(Color::Black);
	explainText1.setString("Press 'Enter'");
	explainText1.setPosition(944, 520);

	sf::Text explainText2;
	explainText2.setFont(explain);
	explainText2.setCharacterSize(18);
	explainText2.setFillColor(Color::Black);
	explainText2.setString("Press 'S'");
	explainText2.setPosition(960, 720);

	sf::Text explainText3;
	explainText3.setFont(explain);
	explainText3.setCharacterSize(18);
	explainText3.setFillColor(Color::Black);
	explainText3.setString("Press 'Esc'");
	explainText3.setPosition(955, 920);

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	
	// initialize Score
	//============ bgMenu	=================
	Texture bgScore;
	bgScore.loadFromFile("Graphics/bgscore");
	Sprite spriteBgScore;
	spriteBgScore.setTexture(bgScore);
	spriteBgScore.setPosition(0, 0);

	//============ bgMenu	=================
	Texture bgList;
	bgList.loadFromFile("Graphics/boradlist");
	Sprite spriteBgList;
	spriteBgList.setTexture(bgList);
	spriteBgList.setPosition(392, 189);
	
	
	Text scoreBoardText[TOPSCORE];
	const Vector2f startPos(645, 360);
	for (int i = 0; i < TOPSCORE; i++)
	{
		scoreBoardText[i].setFont(explain);
		scoreBoardText[i].setCharacterSize(38);
		scoreBoardText[i].setFillColor(Color::Black);
		scoreBoardText[i].setPosition(startPos + (Vector2f(0, 110) * (float)i));
	}

	//============ scoreList =================
	Texture scoreList;
	scoreList.loadFromFile("Graphics/list");
	Sprite spriteScoreList;
	spriteScoreList.setTexture(scoreList);
	spriteScoreList.setPosition(760, 10);

	
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>	
	// initialize Game
	//============	BackGound	=================
	Texture background;
	background.loadFromFile("Graphics/bg");
	Sprite spriteBg;
	spriteBg.setTexture(background);
	spriteBg.setPosition(0, 0);

	//============	Cachet	=================
	Texture cachet;
	cachet.loadFromFile("Graphics/cachet");
	Sprite spriteCachet;
	spriteCachet.setTexture(cachet);
	spriteCachet.setPosition(25, 0);

	//============	Tree	=================
	Texture tree;
	tree.loadFromFile("Graphics/tree");
	Sprite spriteTree;
	spriteTree.setTexture(tree);
	spriteTree.setPosition(810, 0);

	//============	Branch	=================
	Texture branch;
	branch.loadFromFile("Graphics/branches");
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(branch);
		branches[i].setOrigin(320, 20);
	}

	//============	Log	=================
	Texture log;
	log.loadFromFile("Graphics/log");
	Sprite spriteLog;
	spriteLog.setTexture(log);

	bool logActive = false;
	float logSpeedX = 1000;
	float lodSpeedY = -1500;

	//============	PONY	=================
	Texture pony;
	pony.loadFromFile("Graphics/pony");
	Sprite spritePony;
	spritePony.setTexture(pony);
	side playerSide = side::LEFT;

	//============	The gravestone =================
	Texture rip;
	rip.loadFromFile("Graphics/rip");
	Sprite spriteRip;
	spriteRip.setTexture(rip);

	//============	Axe	=================
	Texture axe;
	axe.loadFromFile("Graphics/Axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(axe);
	const float AXE_POSITON_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	//============	ReINDEER	=================
	Texture reindeer;
	reindeer.loadFromFile("Graphics/reindeer");
	Sprite spriteReindeer;
	spriteReindeer.setTexture(reindeer);
	bool reindeerAct = false;
	float reindeerSpeed = 0.0f;

	//============	Time bar	=================
	RectangleShape timeBar;	// รูปสี่เหลี่ยม
	float timeBarStartWidth = 545;
	float timeBarHeight = 30;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight)); // น้าเอากว้าง สูง มารวมกัน
	timeBar.setFillColor(Color::Cyan); // set สี
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	Texture barTime;
	Texture barTime2;
	barTime.loadFromFile("Graphics/time");
	barTime2.loadFromFile("Graphics/time2");
	Sprite Bar;
	Bar.setTexture(barTime);
	Sprite Bar2;
	Bar2.setTexture(barTime2);

	//============	CloudS	=================
	Texture cloud1, cloud2, cloud3, cloud4;
	cloud1.loadFromFile("Graphics/cloud1");
	cloud2.loadFromFile("Graphics/cloud2");
	cloud3.loadFromFile("Graphics/cloud3");
	cloud4.loadFromFile("Graphics/cloud4");
	Sprite spriteCloud1, spriteCloud2, spriteCloud3, spriteCloud4;
	spriteCloud1.setTexture(cloud1);
	spriteCloud2.setTexture(cloud2);
	spriteCloud3.setTexture(cloud3);
	spriteCloud4.setTexture(cloud4);
	bool  cloud1Act = false;
	bool  cloud2Act = false;
	bool  cloud3Act = false;
	bool  cloud4Act = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;
	float cloud4Speed = 0.0f;

	//============	Board =================
	Texture boardEnd;
	boardEnd.loadFromFile("Graphics/board");
	Sprite spriteBoardEnd;
	spriteBoardEnd.setTexture(boardEnd);
	FloatRect textBoardE;

	Texture boardStart;
	boardStart.loadFromFile("Graphics/boardS");
	Sprite spriteBoardStart;
	spriteBoardStart.setTexture(boardStart);
	FloatRect textBoardS;

	//============	Text =================
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;

	Font font;
	font.loadFromFile("fonts/TA16BIT-Regular.otf");
	messageText.setFont(font);
	scoreText.setFont(font);

	messageText.setString("Press Enter to start!");
	messageText.setCharacterSize(54);
	scoreText.setCharacterSize(75);

	messageText.setFillColor(Color::Black);
	scoreText.setFillColor(Color::Black);

	FloatRect textRect;

	//============	Item =================
	Texture item;
	item.loadFromFile("Graphics/item1");
	Sprite spriteItem;
	spriteItem.setTexture(item);

	bool itemAct = false;
	float itemSpeed = 0.0f;
	// Item2
	Texture item2;
	item2.loadFromFile("Graphics/item2");
	Sprite spriteItem2;
	spriteItem2.setTexture(item2);

	bool item2Act = false;
	float item2Speed = 0.0f;

	// Item3
	Texture bomb;
	bomb.loadFromFile("Graphics/bomb");
	Sprite spriteBomb;
	spriteBomb.setTexture(bomb);

	bool bombAct = false;
	float bombSpeed = 0.0f;

	// -------------- SETTING VARIABLES ETC -----------------
	Clock clock;
	bool paused = true;
	bool acceptInput = false;
	bool menuAct = false;
	float mx, my;

	// TextEntered Variable
	string playerName;
	Text nameText;
	nameText.setFont(explain);
	const Vector2f nameTextPos(977, 408);
	nameText.setOrigin(Vector2f(nameText.getGlobalBounds().width, nameText.getGlobalBounds().height) / 2.f);
	nameText.setFillColor(Color::Black);
	nameText.setPosition(nameTextPos);

	// SOUND
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	// DEATH
	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound die;
	die.setBuffer(deathBuffer);

	// Out of time
	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);
	
	// Out of time
	SoundBuffer itemBuffer;
	itemBuffer.loadFromFile("sound/item.wav");
	Sound Item;
	Item.setBuffer(itemBuffer);
	

Menu:
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
				else if (event.key.code == Keyboard::Enter)
				{
					goto Game;
				}
				else if (event.key.code == Keyboard::S)
				{
					goto Score;
				}
			}
		}

		window.clear();
		window.draw(spriteBgMenu);
		window.draw(spriteTitle);
		window.draw(explainText1);
		window.draw(explainText2);
		window.draw(explainText3);
		window.draw(spriteButtonGame);
		window.draw(spriteButtonScore);
		window.draw(spriteButtonQuit);
		window.display();
	}
	return 0;

Score:
	readScoreFile();
	for (int i = 0; i < TOPSCORE; i++)
	{
		scoreBoardText[i].setString(to_string(i + 1) + ". " +scoreData[i].name +"					"+ to_string(scoreData[i].score) + " p ");
	}
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
				else if (event.key.code == Keyboard::B)
				{
					goto Menu;
				}
			}
		}

		window.clear();
		window.draw(spriteBgScore);
		window.draw(spriteBgList);
		for (int i = 0; i < TOPSCORE; i++)
		{
			window.draw(scoreBoardText[i]);
		}
		window.draw(spriteScoreList);
		window.display();
	}
	return 0;

Game:
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setPosition(-2000, -2000);
	}
	// มีแล้วจะเกิดการสุ่มของ BRANCHES
	/*updateBranches(1);
	updateBranches(2);
	updateBranches(3);
	updateBranches(4);
	updateBranches(5);*/

	spriteLog.setPosition(810, 720);

	logActive = false;
	logSpeedX = 1000;
	lodSpeedY = -1500;

	spritePony.setPosition(580, 720);
	playerSide = side::LEFT;

	spriteRip.setPosition(-600, 800);

	spriteAxe.setPosition(700, 830);

	spriteReindeer.setPosition(-190, 800);
	reindeerAct = false;
	reindeerSpeed = 0.0f;

	timeBarStartWidth = 680; // กว้าง
	timeBarHeight = 30; // สูง										
	timeBar.setPosition((550), 980); // ตำแหน่ง

	timeRemaining = 7.74f; // ค่าที่ทำให้ลด เอาไปหาร
	timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;


	Bar.setPosition(530, 960);

	Bar2.setPosition(530, 960);

	spriteCloud1.setPosition(-300, 0);
	spriteCloud2.setPosition(-300, 175);
	spriteCloud3.setPosition(-300, 350);
	spriteCloud4.setPosition(-300, 460);

	cloud1Act = false;
	cloud2Act = false;
	cloud3Act = false;
	cloud4Act = false;

	cloud1Speed = 0.0f;
	cloud2Speed = 0.0f;
	cloud3Speed = 0.0f;
	cloud4Speed = 0.0f;

	textBoardE = spriteBoardEnd.getLocalBounds();
	spriteBoardEnd.setOrigin(textBoardE.left + textBoardE.width / 2.0f, textBoardE.top + textBoardE.height / 2.0f);
	spriteBoardEnd.setPosition(550, 500);
	spriteBoardEnd.setPosition(-1920 / 2.0f, 1080 / 2.0f);

	spriteBoardStart.setPosition(550, 500);
	textBoardS = spriteBoardStart.getLocalBounds(); // ขอบเขต  จัด Press Enter to start!
	spriteBoardStart.setOrigin(textBoardS.left + textBoardS.width / 2.0f, textBoardS.top + textBoardS.height / 2.0f);
	spriteBoardStart.setPosition(1920 / 2.0f, 1080 / 2.0f);

	score = 0;
	scoreText.setString("Score = 0");
	textRect = messageText.getLocalBounds(); // ขอบเขต  จัด Press Enter to start!
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
	scoreText.setPosition(20, 20);

	spriteItem.setPosition(600, -190);

	itemAct = false;
	itemSpeed = 0.0f;

	spriteItem2.setPosition(600, -190);

	item2Act = false;
	item2Speed = 0.0f;

	spriteBomb.setPosition(600, -190);

	bombAct = false;
	bombSpeed = 0.0f;

	clock.restart();
	paused = true;
	acceptInput = false;
	menuAct = false;

	playerName = "";
	nameText.setString("_");
	/*############################################
				START WHILE LOOP
	##############################################
	*/
	while (window.isOpen())
	{
		/*
		*********************************************************************************
							Handle the players input   จัดการอินพุตของผู้เล่น
		*********************************************************************************
		*/

		Event event;
		// ========================   ปล่อยคีย์บอด  =========================

		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !paused)
			{
				acceptInput = true;
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y);
			}
			if (paused)
			{
				if (event.type == Event::TextEntered)
				{
					switch (event.key.code)
					{
					case 8: // DELETE_KEY
						if (playerName.length() > 0)
							playerName.pop_back();
						break;
					default:
						playerName += (char)event.key.code;
						break;
					}
				}
			}
		}

		// ========================  กดปุ่ม esc  =========================
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		//  =========================  กดปุ่ม enter   =========================
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			playerName = "";
			nameText.setString("___");

			paused = false;

			score = 0;
			timeRemaining = 5;

			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}

			spriteRip.setPosition(675, 2000);

			spritePony.setPosition(580, 720);

			acceptInput = true;

			spriteBoardEnd.setPosition(550, 500);
			FloatRect textBoardE = spriteBoardEnd.getLocalBounds(); // ขอบเขต  จัด Press Enter to start!
			spriteBoardEnd.setOrigin(textBoardE.left + textBoardE.width / 2.0f, textBoardE.top + textBoardE.height / 2.0f);
			spriteBoardEnd.setPosition(-1920 / 2.0f, 1080 / 2.0f);
		}

		if (acceptInput)
		{
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{

				playerSide = side::RIGHT;
				score++;

				timeRemaining += (2 / score) + .15;
				spriteAxe.setPosition(AXE_POSITION_RIGHT, spriteAxe.getPosition().y);

				// ไปทางขวา
				spritePony.setPosition(1200, 720);

				updateBranches(score);

				spriteLog.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;

				acceptInput = false;

				chop.play();
			}

			if (Keyboard::isKeyPressed(Keyboard::Left))
			{

				playerSide = side::LEFT;
				score++;

				timeRemaining += (2 / score) + .15;

				spriteAxe.setPosition(AXE_POSITON_LEFT, spriteAxe.getPosition().y);

				spritePony.setPosition(580, 720);
				updateBranches(score);

				spriteLog.setPosition(810, 720);

				logSpeedX = 5000;
				logActive = true;

				acceptInput = false;
				chop.play();

			}

		}



		/*
		******************************************************
							Update the scene
		******************************************************
		*/

		if (!paused)
		{

			Time dt = clock.restart();

			// ************************ UPDATE Score **************************
			std::stringstream ss;
			ss << "SCORE = " << score;
			scoreText.setString(ss.str());

			if ((spriteItem2.getPosition().y >= 702 && spriteItem2.getPosition().y <= 802) && spriteItem2.getPosition().x == spritePony.getPosition().x)
			{
				score += 5;
				spriteItem2.setPosition(600, -190);
				item2Act = false;
				Item.play();
			}

			// ************************ UPDATE Time Bar **************************

			timeRemaining -= dt.asSeconds();
			timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

			if ((spriteItem.getPosition().y >= 702 && spriteItem.getPosition().y <= 802) && spriteItem.getPosition().x == spritePony.getPosition().x)
			{
				timeRemaining += 1.28;
				spriteItem.setPosition(600, -190);
				itemAct = false;
				Item.play();
			}

			// ************************ UPDATE reinDeer **************************
			if (!reindeerAct)
			{
				srand((int)time(0) * 10);
				reindeerSpeed = (rand() % 200) + 200;

				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteReindeer.setPosition(-200, height);
				reindeerAct = true;

			}
			else // Reindeer Move
			{
				spriteReindeer.setPosition(spriteReindeer.getPosition().x + (reindeerSpeed * dt.asSeconds()), spriteReindeer.getPosition().y);

				if (spriteReindeer.getPosition().x > 1920)
				{
					reindeerAct = false;
				}
			}

			// ************************ UPDATE item **************************
			if (!itemAct)
			{
				srand((int)time(0) * 10);
				itemSpeed = (rand() % 200) + 300;

				if (score % 227 == 0 && score != 0) {
					spriteItem.setPosition(580, -200);
					itemAct = true;
				}
				else if (score % 80 == 0 && score != 0)
				{
					spriteItem.setPosition(1200, -200);
					itemAct = true;
				}
			}
			else // item Move
			{
				spriteItem.setPosition(spriteItem.getPosition().x, spriteItem.getPosition().y + (itemSpeed * dt.asSeconds()));

				if (spriteItem.getPosition().y > 1200)
				{
					itemAct = false;

				}
			}

			if (!item2Act)
			{
				srand((int)time(0) * 10);
				item2Speed = (rand() % 200) + 150;


				if (score % 230 == 0 && score != 0) {
					spriteItem2.setPosition(1200, -200);
					item2Act = true;
				}
				else if (score % 108 == 0 && score != 0)
				{
					spriteItem2.setPosition(580, -200);
					item2Act = true;
				}
			}
			else // item Move
			{
				spriteItem2.setPosition(spriteItem2.getPosition().x, spriteItem2.getPosition().y + (item2Speed * dt.asSeconds()));

				if (spriteItem2.getPosition().y > 1200)
				{
					item2Act = false;

				}
			}

			// ************************ UPDATE Bomb to Death ***********************
			if (!bombAct)
			{
				srand((int)time(0) * 10);
				bombSpeed = (rand() % 200) + 480;


				if (score % 170 == 0 && score != 0) {
					spriteBomb.setPosition(1200, -200);
					bombAct = true;
				}
				else if (score % 234 == 0 && score != 0)
				{
					spriteBomb.setPosition(580, -200);
					bombAct = true;
				}
			}
			else // item Move
			{
				spriteBomb.setPosition(spriteBomb.getPosition().x, spriteBomb.getPosition().y + (bombSpeed * dt.asSeconds()));

				if (spriteBomb.getPosition().y > 1200)
				{
					bombAct = false;

				}
			}

			// ************************ UPDATE coulds **************************
			// Could 1
			if (!cloud1Act)
			{
				// How fast is the cloud
				srand((int)time(0) * 10);
				cloud1Speed = ((rand() % 200));

				// How high is the cloud
				srand((int)time(0) * 10);
				float height = (rand() % 150) - 50;
				spriteCloud1.setPosition(2000, height);
				cloud1Act = true;
			}
			else
			{	// cloud1 move

				spriteCloud1.setPosition(spriteCloud1.getPosition().x -
					(cloud1Speed * dt.asSeconds()),
					spriteCloud1.getPosition().y);

				if (spriteCloud1.getPosition().x < -250)
				{
					cloud1Act = false;
				}
			}

			// Could 2
			if (!cloud2Act)
			{
				srand((int)time(0) * 20);
				cloud2Speed = ((rand() % 200));

				srand((int)time(0) * 20);
				float height = (rand() % 300) - 40;
				spriteCloud2.setPosition(2000, height);
				cloud2Act = true;

			}
			else
			{	// cloud2 move

				spriteCloud2.setPosition(spriteCloud2.getPosition().x -
					(cloud2Speed * dt.asSeconds()),
					spriteCloud2.getPosition().y);

				if (spriteCloud2.getPosition().x < -250)
				{
					cloud2Act = false;
				}
			}
			// Could 3
			if (!cloud3Act)
			{
				srand((int)time(0) * 30);
				cloud3Speed = ((rand() % 200));

				srand((int)time(0) * 30);
				float height = (rand() % 300) - 120;
				spriteCloud3.setPosition(2000, height);
				cloud3Act = true;

			}
			else
			{	// cloud3 move

				spriteCloud3.setPosition(spriteCloud3.getPosition().x -
					(cloud3Speed * dt.asSeconds()),
					spriteCloud3.getPosition().y);

				if (spriteCloud3.getPosition().x < -250)
				{
					cloud3Act = false;
				}
			}
			// Could 4
			if (!cloud4Act)
			{
				srand((int)time(0) * 40);
				cloud4Speed = ((rand() % 200) + 30);

				srand((int)time(0) * 40);
				float height = (rand() % 300);
				spriteCloud4.setPosition(2000, height);
				cloud4Act = true;

			}
			else
			{	// cloud4 move

				spriteCloud4.setPosition(spriteCloud4.getPosition().x -
					(cloud4Speed * dt.asSeconds()),
					spriteCloud4.getPosition().y);

				if (spriteCloud4.getPosition().x < -250)
				{
					cloud4Act = false;
				}
			}


			//************************ UPDARE a flying log **************************
			if (logActive)
			{
				spriteLog.setPosition(
					spriteLog.getPosition().x + (logSpeedX * dt.asSeconds())
					, spriteLog.getPosition().y + (lodSpeedY * dt.asSeconds()));



				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x>2000)
				{

					logActive = false;
					spriteLog.setPosition(810, 720);
				}

			}
			//************************ UPDARE Branchres **************************
			for (int i = 0; i < NUM_BRANCHES; i++)
			{
				float height = i * 150;	// วางตำแหน่งกื่ง
				if (branchPositions[i] == side::LEFT)
				{

					branches[i].setPosition(610, height);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{

					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else
				{
					branches[i].setPosition(3000, height);
				}
			}

			if (branchPositions[5] == playerSide)
			{

				// death
				paused = true;
				acceptInput = false;
				itemAct = false;
				item2Act = false;
				bombAct = false;

				die.play();

				spriteRip.setPosition(525, 760);
				spritePony.setPosition(2000, 660);
				spriteItem.setPosition(600, -190);
				spriteItem2.setPosition(600, -190);
				spriteBomb.setPosition(600, -190);

				FloatRect textBoardE = spriteBoardEnd.getLocalBounds(); // gameover
				spriteBoardEnd.setOrigin(textBoardE.left + textBoardE.width / 2.0f, textBoardE.top + textBoardE.height / 2.0f);
				spriteBoardEnd.setPosition(1920 / 2.0f, 1080 / 2.0f);

				FloatRect textBoardS = spriteBoardStart.getLocalBounds(); // ขอบเขต  จัด Press Enter to start!
				spriteBoardStart.setOrigin(textBoardS.left + textBoardS.width / 2.0f, textBoardS.top + textBoardS.height / 2.0f);
				spriteBoardStart.setPosition(-1920 / 2.0f, 1080 / 2.0f);

				messageText.setString("GAME OVER!!");
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
			}
			// ************************ UPDATE Item to die **************************
			if ((spriteBomb.getPosition().y >= 698 && spriteBomb.getPosition().y <= 802) && spriteBomb.getPosition().x == spritePony.getPosition().x)
			{
				paused = true;
				acceptInput = false;
				spriteBomb.setPosition(600, -190);
				bombAct = false;
				die.play();

				FloatRect textBoardE = spriteBoardEnd.getLocalBounds(); // gameover
				spriteBoardEnd.setOrigin(textBoardE.left + textBoardE.width / 2.0f, textBoardE.top + textBoardE.height / 2.0f);
				spriteBoardEnd.setPosition(1920 / 2.0f, 1080 / 2.0f);

				FloatRect textBoardS = spriteBoardStart.getLocalBounds(); // ขอบเขต  จัด Press Enter to start!
				spriteBoardStart.setOrigin(textBoardS.left + textBoardS.width / 2.0f, textBoardS.top + textBoardS.height / 2.0f);
				spriteBoardStart.setPosition(-1920 / 2.0f, 1080 / 2.0f);

			}
			// ************************ UPDATE Out of time ***********************
			if (timeRemaining <= 0.0f)
			{
				paused = true;

				bombAct = false;
				itemAct = false;
				item2Act = false;
				spriteItem.setPosition(600, -190);
				spriteItem2.setPosition(600, -190);
				spriteBomb.setPosition(600, -190);

				FloatRect textBoardE = spriteBoardEnd.getLocalBounds(); // gameover
				spriteBoardEnd.setOrigin(textBoardE.left + textBoardE.width / 2.0f, textBoardE.top + textBoardE.height / 2.0f);
				spriteBoardEnd.setPosition(1920 / 2.0f, 1080 / 2.0f);

				FloatRect textBoardS = spriteBoardStart.getLocalBounds(); // ขอบเขต  จัด Press Enter to start!
				spriteBoardStart.setOrigin(textBoardS.left + textBoardS.width / 2.0f, textBoardS.top + textBoardS.height / 2.0f);
				spriteBoardStart.setPosition(-1920 / 2.0f, 1080 / 2.0f);

				outOfTime.play();
			}

		}// End if(paused)
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Space))
			{
				saveScoreFile(playerName, score);
				goto Menu;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}

			nameText.setString(playerName + "_");
			nameText.setOrigin(Vector2f(nameText.getGlobalBounds().width, nameText.getGlobalBounds().height) / 2.f);
			nameText.setPosition(nameTextPos);
		}

		window.clear();
		window.draw(spriteBg);

		window.draw(spriteCloud2);
		window.draw(spriteCloud4);
		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}
		window.draw(spriteTree);
		window.draw(spriteCachet);

		window.draw(spriteLog);

		window.draw(spriteCloud1);
		window.draw(spriteCloud3);
		window.draw(scoreText);
		window.draw(spriteRip);

		window.draw(spriteReindeer);
		window.draw(spriteItem);
		window.draw(spriteItem2);
		window.draw(spriteBomb);
		window.draw(spriteBoardEnd);//จบเกมส์

		if (!paused) {
			window.draw(Bar2);
			window.draw(timeBar);
			window.draw(Bar);
			window.draw(spritePony);
			window.draw(spriteAxe);

		}
		else if (paused)
		{

			window.draw(spriteBoardStart);//เริ่มเกมส์
			window.draw(nameText);
			//window.draw(messageText);
		}
		window.display();

	}//End while

	return 0;
}

void updateBranches(int seed)
{
	// <<<<<<<<<<<<<<<<<<<<   เป็นการสุ่มกิ่งไม้ แต่ละกิ่งอยู่ซ้าย ขวา หรือไม่มี    >>>>>>>>>>>>>>>>>>>>>>>>

	for (int j = NUM_BRANCHES - 1; j > 0; j--) // ส่วนที่ทำให้เคลื่อนที่ลงแต่อยู่ทำแหน่งเดิม
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r)
	{
	case 0:
		branchPositions[0] = side::LEFT;
		break;

	case 1:
		branchPositions[0] = side::RIGHT;
		break;

	default:
		branchPositions[0] = side::NONE;
		break;
	}
}

void sortScore()
{
	for (int i = 0; i < TOPSCORE; i++)
	{
		for (int j = i + 1; j < TOPSCORE + 1; j++)
		{
			if (scoreData[j].score > scoreData[i].score)
			{
				ScoreData temp = scoreData[i];
				scoreData[i] = scoreData[j];
				scoreData[j] = temp;
			}
		}
	}
}

void readScoreFile()
{
	fstream scoreFile;
	scoreFile.open(FILENAME, ios::app | ios::in);
	for (int i = 0; i < TOPSCORE; i++)
	{
		string tempname;
		string tempscore;
		if (!getline(scoreFile, tempname))
			return;
		if (!getline(scoreFile, tempscore))
			return;
		scoreData[i].name = tempname;
		scoreData[i].score = stoi(tempscore);
	}
	scoreFile.close();
	sortScore();
}

void saveScoreFile(string name, int score)
{
	scoreData[TOPSCORE].name = name;
	scoreData[TOPSCORE].score = score;
	sortScore();
	fstream scoreFile;
	scoreFile.open(FILENAME, ios::out | ios::in);
	for (int i = 0; i < TOPSCORE; i++)
	{
		scoreFile << scoreData[i].name << endl << scoreData[i].score << endl;
	}
	scoreFile.close();
}