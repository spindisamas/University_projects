#include <iostream>
#include <windows.h>
#include "SideFuncs.h"
#include "Game.h"
#include "Menu.h"

using namespace std;

int main()
{
	cout << "For best experience set the console properties: \n";
	cout << "Screen buffer size\n";
	cout << "\tWidth: 61\n\tHeight: 20\n";
	cout << "Window size:\n";
	cout << "\tWidth: 60\n\tHeight: 20\n\n";
	cout << "And then restart the game.\n";
	Sleep(SECOND * 5);
	ShowConsoleCursor(false);

	Menu* menu = nullptr;
	Settings* settings = nullptr;
	try
	{
		menu = new Menu();
		settings = new Settings();
	}
	catch (const std::exception&)
	{
		cout << "Something went wrong. The program will shut down\n";
		getchar();
		delete menu;
		delete settings;
		return 1;
	}
	menu->browse(*settings);
	if (settings->exit)
		return 0;

	Game* m = nullptr;
	try
	{
		m = new Game(field, *settings);
	}
	catch (const std::exception&)
	{
		cout << "Something went wrong. The program will shut down\n";
		getchar();
		delete menu;
		delete settings;
		delete m;
		return 1;
	}
	
	while (true)
	{
		m->draw1stFrame();

		Move move;
		bool gameContinues = true;
		bool shoot = false;
		while (true)
		{
			shoot = false;

			if (GetAsyncKeyState(VK_UP))
			{
				move.Y = 1;
			}
			if (GetAsyncKeyState(VK_DOWN))
			{
				move.Y = -1;
			}
			if (GetAsyncKeyState(VK_LEFT))
			{
				move.X = -1;
			}
			if (GetAsyncKeyState(VK_RIGHT))
			{
				move.X = 1;
			}
 			if (GetAsyncKeyState(VK_SPACE))
			{
				shoot = true;
			}
			if (GetAsyncKeyState(0x53))
			{
				m->serialize(*settings);
			}

			gameContinues = m->update(move, shoot);

			move.reset();

			Sleep(SECOND/settings->fps);

			if (gameContinues == false)
				break;
		}
	
		menu->browse(*settings);
		if (settings->exit)
			return 0;

		else
		{
			delete m;
			m = nullptr;
			try
			{
				m = new Game(field, *settings);
			}
			catch (const std::exception&)
			{
				cout << "Something went wrong. The program will shut down\n";
				getchar();
				delete menu;
				delete settings;
				delete m;
			}
		}
	}
	delete settings;
	delete menu;
	delete m;
	return 0;
}
	//HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	//SetConsoleDisplayMode(console, CONSOLE_FULLSCREEN_MODE, 0);
	//COORD coord = GetLargestConsoleWindowSize(console);
	//coord.X = coord.X - 2;
	//SetConsoleScreenBufferSize(console, coord);