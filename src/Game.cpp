
#include <chrono>
#include <string>
#include <iostream>

#include "Game.hpp"
#include "Coordinates.hpp"

Game::Game()
{}

Game::~Game()
{

}

void	Game::init()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib [core] example - basic window");
	SetTargetFPS(60);

	Coordinates::initializeSpace(SCREEN_WIDTH, SCREEN_HEIGHT);

	Game::loadAssets();

	Game::readLevels("assets/levels.txt");
}

void	Game::readLevels(std::string file)
{
	std::ifstream readFile;
	readFile.open(file, std::ios::in);

	if (readFile.is_open())
	{
		std::string line;
		std::string str = "";
		int row = 0;
		while (std::getline(readFile, line))
		{
			for (int i = 0; i < line.length(); ++i)
			{
				char c = line[i];
				if (c == '}')
				{
					m_levelManager.addLevel(str);
					str = "";
				}
				else if (c != ',' && c != '{')
					str += c;
			}
		}
		readFile.close();
	}
	else
	{
		std::cerr << "Unable to open file" << std::endl;
	}
}

void	Game::loadAssets()
{
	Image ship = LoadImage("assets/ship2.png");
	Image assets = LoadImage("assets/assets_minestorm_new.png");
	Image floatmine = LoadImage("assets/floatmine2.png");
	Image fireballmine = LoadImage("assets/fireballmine.png");
	Image hybridmine = LoadImage("assets/hybridmine.png");
	Image magmine = LoadImage("assets/magneticmine2.png");
	Image minelay = LoadImage("assets/minelay2.png");
	Image bullet = LoadImage("assets/bullet.png");


	m_textures[0] = LoadTexture("assets/minestorm_background.png");
	m_textures[1] = LoadTexture("assets/minestorm_forground.png");
	m_textures[2] = LoadTextureFromImage(ImageFromImage(ship, { 0, 0, 84, 140 }));
	m_textures[3] = LoadTextureFromImage(ImageFromImage(assets, { 356, 99, 58, 59 })); //spawn texture
	m_textures[4] = LoadTextureFromImage(ImageFromImage(floatmine, { 2, 3, 115, 107 }));
	m_textures[5] = LoadTextureFromImage(ImageFromImage(fireballmine, { 2, 2, 104, 105 }));
	m_textures[6] = LoadTextureFromImage(ImageFromImage(magmine, { 1, 0, 98, 102 }));
	m_textures[7] = LoadTextureFromImage(ImageFromImage(hybridmine, { 2, 1, 146, 152 }));
	m_textures[8] = LoadTextureFromImage(ImageFromImage(minelay, { 2, 1, 254, 78 }));
	m_textures[9] = LoadTextureFromImage(ImageFromImage(bullet, { 2, 2, 27, 27 }));
	m_textures[10] = LoadTexture("assets/fireball2.png");


	m_levelManager.setTextures(m_textures);

	UnloadImage(ship);
	UnloadImage(assets);
	UnloadImage(floatmine);
	UnloadImage(fireballmine);
	UnloadImage(hybridmine);
	UnloadImage(magmine);
	UnloadImage(minelay);
	UnloadImage(bullet);
}

void	Game::unloadAssets()
{
	int arrsize = sizeof(m_textures) / sizeof(m_textures[0]);
	for (int i = 0; i < arrsize; ++i)
		UnloadTexture(m_textures[i]);
}

void	Game::shutdown()
{
	Game::unloadAssets();
	CloseWindow();       
}

void	Game::update(float elapsedTime)
{
	if (m_screenState != static_cast<int>(m_Screen::PAUSED) && m_screenState != static_cast<int>(m_Screen::MAIN_MENU))
		m_levelManager.update(elapsedTime);
}

void	Game::run()
{
	SetExitKey(0);
	auto lastTime = std::chrono::high_resolution_clock::now();
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto elapsedTime = currentTime - lastTime;
		lastTime = currentTime;

		// paused, menu, in game, etc
		Game::setScreenState();

		// update elements movement based on time - turning, rotation, acceleration, etc
		Game::update(std::chrono::duration<float>(elapsedTime).count());

		// draw
		if (m_screenState == static_cast<int>(m_Screen::EXITING))
			break;
		Game::draw();
	}
}

void	Game::draw()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	DrawTexture(m_textures[0], 0, 0, WHITE); // background

	Game::drawScreen();

	EndDrawing();
}

void	Game::setScreenState()
{
	switch (m_screenState)
	{
		case static_cast<int>(m_Screen::MAIN_MENU):
			if (IsKeyPressed(KEY_F))
			{
				m_playerCount = 1;
				m_levelManager.setPlayers(m_playerCount);
				m_screenState = m_screens[static_cast<int>(m_Screen::IN_GAME)];
			}
			else if (IsKeyPressed(KEY_K))
			{
				m_playerCount = 2;
				m_levelManager.setPlayers(m_playerCount);
				m_screenState = m_screens[static_cast<int>(m_Screen::IN_GAME)];
			}
			else if (IsKeyPressed(KEY_ESCAPE))
			{
				std::cout << "Player has chosen to quit game. Exiting..." << std::endl;
				m_screenState = m_screens[static_cast<int>(m_Screen::EXITING)];
			}
			break;
		case static_cast<int>(m_Screen::IN_GAME) :
			if (IsKeyPressed(KEY_P))
			{
				m_screenState = m_screens[static_cast<int>(m_Screen::PAUSED)];
			}
			else if (IsKeyPressed(KEY_C))
			{
				if (m_collisionLinesActive)
					m_collisionLinesActive = false;
				else
					m_collisionLinesActive = true;
			}
			else if (!m_livesP1 && !m_livesP2 || !m_livesP1 && m_playerCount == 1)
			{
				m_screenState = static_cast<int>(m_Screen::GAME_OVER);
			}
			break;
		case static_cast<int>(m_Screen::PAUSED) :
			if (IsKeyPressed(KEY_P))
			{
				m_screenState = m_screens[static_cast<int>(m_Screen::IN_GAME)];
			}
			else if (IsKeyPressed(KEY_ESCAPE))
			{
				m_screenState = m_screens[static_cast<int>(m_Screen::MAIN_MENU)];
				m_playerCount = 2;
				m_levelManager.clearLevels();
				m_score = 0;
			}
			break;
		case static_cast<int>(m_Screen::GAME_OVER) :
			if (IsKeyPressed(KEY_ESCAPE))
			{
				m_screenState = m_screens[static_cast<int>(m_Screen::MAIN_MENU)];
				m_playerCount = 2;
				m_levelManager.clearLevels();
				m_score = 0;
			}
			break;
	default:
		break;
	}
}

void	Game::drawScreen()
{
	switch (m_screenState)
	{
		case static_cast<int>(m_Screen::MAIN_MENU):
			Game::mainMenu();
			break;
		case static_cast<int>(m_Screen::PAUSED):
			Game::pauseScreen();
			break;
		case static_cast<int>(m_Screen::GAME_OVER) :
			Game::gameOverScreen();
			break;
		case static_cast<int>(m_Screen::IN_GAME) :
			Game::inGame();
			break;
		case static_cast<int>(m_Screen::EXITING) :
			break;
		default:
			std::cerr << "INVALID SCREEN STATE: " << m_screenState << ". Exiting..." << std::endl;
			exit(1);
			break;
	}
}

void	Game::mainMenu()
{
	Game::drawBubble();
	Game::drawPlayerInfo();
	Game::drawInstructions();
	DrawTexture(m_textures[1], 0, 0, WHITE); // foreground

	DrawText("BRAVE THE VACUUM OF SPACE", Coordinates::getSpaceLength() - 570, Coordinates::getSpaceHeight() * 0.4f - 10, 30, BLACK);
	DrawText("Press F - Single Player", Coordinates::getSpaceLength() / 3, Coordinates::getSpaceHeight() * 0.4f + 25, 15, BLUE);
	DrawText("Press K - Two Players", Coordinates::getSpaceLength() / 3, Coordinates::getSpaceHeight() * 0.4f + 50, 15, GREEN);
	DrawText("Press ESC - Quit", Coordinates::getSpaceLength() / 3, Coordinates::getSpaceHeight() * 0.4f + 75, 15, RED);
}

void	Game::pauseScreen()
{
	Game::drawBubble();
	Game::drawPlayerInfo();
	Game::drawInstructions();
	DrawTexture(m_textures[1], 0, 0, WHITE); // foreground
	Game::drawScore();

	DrawText("GAME PAUSED", Coordinates::getSpaceLength() - 440, Coordinates::getSpaceHeight() * 0.4f - 10, 30, BLACK);
	DrawText("Press P - Continue", Coordinates::getSpaceLength() / 3, Coordinates::getSpaceHeight() * 0.4f + 25, 15, BLUE);
	DrawText("Press ESC - Main Menu", Coordinates::getSpaceLength() / 3, Coordinates::getSpaceHeight() * 0.4f + 50, 15, GREEN);
	
}

void	Game::gameOverScreen()
{
	std::string score = "SCORE: " + std::to_string(m_score);
	Game::drawBubble();
	Game::drawPlayerInfo();
	DrawTexture(m_textures[1], 0, 0, WHITE); // foreground

	DrawText("GAME OVER", Coordinates::getSpaceLength() - 440, Coordinates::getSpaceHeight() * 0.4f - 10, 30, BLACK);
	DrawText(score.c_str(), Coordinates::getSpaceLength() - 400, Coordinates::getSpaceHeight() * 0.4f + 25, 25, PURPLE);
	DrawText("Press ESC - Main Menu", Coordinates::getSpaceLength() - 430, Coordinates::getSpaceHeight() * 0.4f + 60, 15, GREEN);
}

void	Game::inGame()
{
	Game::drawPlayerInfo(true);
	m_levelManager.drawLevel(m_collisionLinesActive, m_score, m_livesP1, m_livesP2);
	DrawTexture(m_textures[1], 0, 0, WHITE); // foreground
	Game::drawScore();
	
}

void	Game::drawBubble()
{
	DrawRectangleRounded({ Coordinates::getLeftOffset() + 20.f, Coordinates::getTopOffset() + 20.f, 126, 60 }, 0.5f, 5, BLUE);
	if (m_playerCount == 2)
		DrawRectangleRounded({ Coordinates::getSpaceLength() - (Coordinates::getRightOffset() + 145.f), Coordinates::getTopOffset() + 20.f, 126, 60 }, 0.5f, 5, GREEN);
}

void	Game::drawPlayerInfo(bool ingame)
{
	Color color1 = BLACK;
	Color color2 = BLACK;
	if (ingame)
	{
		color1 = BLUE;
		color2 = GREEN;
	}

	DrawText("PLAYER ONE", Coordinates::getLeftOffset() + 35, Coordinates::getTopOffset() + 25, 15, color1);
	for (int i = 0; i < m_livesP1; ++i)
	{
		DrawTextureEx(m_textures[2], { (float)Coordinates::getLeftOffset() + 45.f + (30.f * i) , Coordinates::getTopOffset() + 45.F }, 0.f, 0.15f, color1);
	}
	
	if (m_playerCount == 2)
	{
		DrawText("PLAYER TWO", Coordinates::getSpaceLength() - (Coordinates::getRightOffset() + 130), Coordinates::getTopOffset() + 25, 15, color2);
		for (int i = 0; i < m_livesP2; ++i)
		{
			DrawTextureEx(m_textures[2], { Coordinates::getSpaceLength() - (Coordinates::getRightOffset() + 120.f - (30.f * i)), Coordinates::getTopOffset() + 45.f }, 0.f, 0.15f, color2);
		}
	}
}

void	Game::drawInstructions()
{
	DrawText("FORWARD:\t 'R'", Coordinates::getLeftOffset() + 25, Coordinates::getTopOffset() + 85, 10, LIGHTGRAY);
	DrawText("SHOOT:\t 'F'", Coordinates::getLeftOffset() + 25, Coordinates::getTopOffset() + 97, 10, LIGHTGRAY);
	DrawText("Rotate:\t 'D' & 'G'", Coordinates::getLeftOffset() + 25, Coordinates::getTopOffset() + 109, 10, LIGHTGRAY);
	DrawText("Teleport:\t 'E' or 'T'", Coordinates::getLeftOffset() + 25, Coordinates::getTopOffset() + 121, 10, LIGHTGRAY);

	if (m_playerCount == 2)
	{
		DrawText("FORWARD:\t 'I'", Coordinates::getSpaceLength() - (Coordinates::getRightOffset() + 140.f), Coordinates::getTopOffset() + 85, 10, LIGHTGRAY);
		DrawText("SHOOT:\t 'K'", Coordinates::getSpaceLength() - (Coordinates::getRightOffset() + 140.f), Coordinates::getTopOffset() + 97, 10, LIGHTGRAY);
		DrawText("Rotate:\t 'J' & 'L'", Coordinates::getSpaceLength() - (Coordinates::getRightOffset() + 140.f), Coordinates::getTopOffset() + 109, 10, LIGHTGRAY);
		DrawText("Teleport:\t 'U' or 'O'", Coordinates::getSpaceLength() - (Coordinates::getRightOffset() + 140.f), Coordinates::getTopOffset() + 121, 10, LIGHTGRAY);
	}
	
}

void	Game::drawScore()
{
	std::string score = "SCORE: " + std::to_string(m_score);
	DrawText(score.c_str(), Coordinates::getSpaceLength() - 380, Coordinates::getSpaceHeight() - 80, 20, GREEN);
}




