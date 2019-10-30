#ifndef SFNCS
#define SFNCS
#include <iostream>
#include <Windows.h>
#include <fstream>

static void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

static void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

struct Move
{
public:
	Move() : X(0), Y(0) {}
	Move(short X, short Y) : X(X), Y(Y) {}

	void reset() { X = 0; Y = 0; }
	short X;
	short Y;
};

struct Coords
{
public:
	Coords() : X(0), Y(0) {}
	Coords(int x, int y) : X(x), Y(y) {}

	unsigned short X;
	unsigned short Y;
};

struct Settings
{
	Settings() :
		newGame(false),
		continueGame(false),
		exit(false),
		skin(1),
		difficulty(0),
		fps(30 + 15 * difficulty)
	{}

	bool serialize(std::ofstream& out)
	{
		out.write((const char*)&newGame, sizeof(newGame));
		out.write((const char*)&continueGame, sizeof(continueGame));
		out.write((const char*)&exit, sizeof(exit));
		out.write((const char*)&skin, sizeof(skin));
		out.write((const char*)&difficulty, sizeof(difficulty));
		out.write((const char*)&fps, sizeof(fps));

		return out.good();
	}
	bool deserialize(std::ifstream& in)
	{
		in.read((char*)&newGame, sizeof(newGame));
		in.read((char*)&continueGame, sizeof(continueGame));
		in.read((char*)&exit, sizeof(exit));
		in.read((char*)&skin, sizeof(skin));
		in.read((char*)&difficulty, sizeof(difficulty));
		in.read((char*)&fps, sizeof(fps));

		return in.good();
	}

	bool newGame;
	bool continueGame;
	bool exit;
	unsigned skin;
	unsigned difficulty;
	unsigned fps;
};
const unsigned WIDTH = 60, HEIGHT = 20; // Game resolution

enum EnemyLevel : int
{
	LEVEL1,
	LEVEL2,
	LEVEL3,
	BOSS
};

const struct EnemyInfo
{
	EnemyInfo(const unsigned _dimX, const unsigned _dimY, const Coords& _center) :
		dimX(_dimX),
		dimY(_dimY),
		center(_center)
	{};
	EnemyInfo(const unsigned _dimX, const unsigned _dimY) :
		dimX(_dimX),
		dimY(_dimY),
		center(WIDTH - 2, HEIGHT / 2)
	{};

	const unsigned dimX;
	const unsigned dimY;
	const Coords center;
};

const EnemyInfo Type1(3, 3, Coords(WIDTH - 3, 5));
const EnemyInfo Type2(3, 4);
const EnemyInfo Type3(5, 1);
const EnemyInfo TypeBoss(15, 7);

const unsigned SECOND = 1000;
const unsigned delay = 40;
const unsigned MAX_SPEED = delay;

const unsigned PLAYER_SPEED = delay - 1;
const unsigned FPS = 40;
const unsigned SHOTS_IN_SEC = 4;

const unsigned MAX_OBJ_WIDTH = 30, MAX_OBJ_HEIGHT = 14;
const unsigned MAX_PLAYER_WIDTH = 30, MAX_PLAYER_HEIGHT = 10;
const unsigned MAX_ENEMY_WIDTH = 30, MAX_ENEMY_HEIGHT = 14;
const unsigned MAX_ENEMY_CAPACITY = 4;

const unsigned MAX_BULLET_WIDTH = WIDTH - MAX_ENEMY_WIDTH;
const unsigned MAX_BULLET_HEIGHT = 4;

const unsigned MAX_BULLET_CAPACITY = WIDTH * 5;

struct Graphics
{
	Graphics(const char _graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH]) :
		dimX(0)
	{
		size_t i = 0;
		for (; _graphics[i][0] != '\0'; i++)
		{
			size_t j = 0;
			for (; _graphics[i][j] != '\0'; j++)
			{
				graphics[i][j] = _graphics[i][j];
			}
			graphics[i][j] = '\0';

			dimX < j ? dimX = j : dimX;
		}
		dimY = i;
	}
	Graphics(const Graphics& rhs)
	{
		this->dimX = rhs.dimX;
		this->dimY = rhs.dimY;
		for (size_t i = 0; i < MAX_OBJ_HEIGHT; i++)
			for (size_t j = 0; j < MAX_OBJ_WIDTH; j++)
				this->graphics[i][j] = rhs.graphics[i][j];
	}

	char graphics[MAX_OBJ_HEIGHT][MAX_OBJ_WIDTH];

	unsigned dimX;
	unsigned dimY;
};


const unsigned char field[HEIGHT][WIDTH + 1] = {
	"Lives:                                      Score: 0        ",
	"■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                                                            ",
	"                          _  _                              ",
	"                 /\\      | || |    _    /\\                  ",
	"      _        /\\||      | || |_ _| |   ||     ==           ",
	"    _| |   _   ||||      | || | | | |   ||    ====     _  _ ",
	"___| | |__| |__||||______| || | | | |___||___======___| || |"
};

//const char* EMPTY_ROW = field[10];
static void clearScreen()
{
	for (size_t i = 0; i < HEIGHT; i++)
		std::cout << field[10] << '\n';
}

const char NEW_GAME[] = "New game";
const char NEW_GAME_SELECTED[] = "NEW GAME";

const char CONTINUE[] = "Continue";
const char CONTINUE_SELECTED[] = "CONTINUE";

const char SETTINGS[] = "Settings";
const char SETTINGS_SELECTED[] = "SETTINGS";

const char EXIT[] = "Exit";
const char EXIT_SELECTED[] = "EXIT";

const char EASY[] = "Easy";
const char EASY_SELECTED[] = "EASY";

const char NORMAL[] = "Normal";
const char NORMAL_SELECTED[] = "NORMAL";

const char HARD[] = "Hard";
const char HARD_SELECTED[] = "HARD";

const char BACK[] = "Back";
const char BACK_SELECTED[] = "BACK";

const char SKIN[] = "Skin";
const char SKIN_SELECTED[] = "SKIN";

const unsigned NUM_OF_SKINS = 3;

static char player1[MAX_PLAYER_HEIGHT][MAX_PLAYER_WIDTH] = {
	"\\- ",
	"=x>",
	"/- ",
	""
};

static char player2[MAX_PLAYER_HEIGHT][MAX_PLAYER_WIDTH] = { "-(-)>" };

static char player3[MAX_PLAYER_HEIGHT][MAX_PLAYER_WIDTH] = { "=>" };


const char enemyType1[MAX_ENEMY_HEIGHT][MAX_ENEMY_WIDTH] = {
	" OO",
	"OOO",
	" OO",
	""
};

const char boss1[MAX_ENEMY_HEIGHT][MAX_ENEMY_WIDTH]{
	{ "   /\\______  __" },
	{ "  /-~     ,^~ /" },
	{ " / ,---x /_.-\"L" },
	{ "/-\".-- - .\\_. - '/!" },
	{ "0\\/0___/   x' /" },
	{ "\\.______.-'_./ " },
	{ " `x_________/  " },
	""
};


const char enemyType2[MAX_ENEMY_HEIGHT][MAX_ENEMY_WIDTH] = {
	" <  ",
	"<<<<",
	" <  ",
	""
};

const char bullet[MAX_BULLET_HEIGHT][MAX_BULLET_WIDTH] = {
	"-",
	""
};

#endif // !SFNCS
