#include "Menu.h"



Menu::Menu():
	rowSelected(1)
{
}


Menu::~Menu()
{
}

void Menu::goToMainMenu()
{
	clearScreen();

	rowSelected = 1;

	selectNewGame();
	deselectContinue();
	deselectSettings();
	deselectExit();
}

void Menu::clearSkin()
{
	setCursorPosition(WIDTH / 2 - 2, HEIGHT / 2 - 1);
	std::cout << "      ";

	setCursorPosition(WIDTH / 2 - 2, HEIGHT / 2);
	std::cout << "      ";

	setCursorPosition(WIDTH / 2 - 2, HEIGHT / 2 + 1);
	std::cout << "      ";
}

void Menu::goToSettingsMenu()
{
	clearScreen();

	rowSelected = 1;

	selectEasy();
	deselectNormal();
	deselectHard();
	deselectSkin();
	deselectBack();
}

void Menu::goToSkinMenu(Settings& settings)
{
	rowSelected = 1;

	clearScreen();
	while (true)
	{
		Sleep(150);
		
		clearSkin();
		if (GetAsyncKeyState(VK_RIGHT))
		{
			++rowSelected;
			if (rowSelected > NUM_OF_SKINS)
				rowSelected = 1;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			--rowSelected;
			if (rowSelected == 0)
				rowSelected = 3;
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			settings.skin = rowSelected;
			break;
		}

		if (rowSelected == 1)
			selectSkin1();
		else if (rowSelected == 2)
			selectSkin2();
		else if (rowSelected == 3)
			selectSkin3();
	}
}

void Menu::browse(Settings& settings)
{
	goToMainMenu();
	while (true)
	{
		Sleep(150);
		if (GetAsyncKeyState(VK_UP))
		{
			selectUpMainMenu();
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			selectDownMainMenu();
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			switch (rowSelected)
			{
			default:
			case 1:
				settings.newGame = true;
				return;
			case 2:
				settings.continueGame = true;
				return;
			case 3:
				browseSettings(settings);
				goToMainMenu();
				break;
			case 4:
				settings.exit = true;
				return;
			}
		}
	}
	return;
}

void Menu::browseSettings(Settings& settings)
{
	goToSettingsMenu();
	while (true)
	{
		Sleep(150);
		if (GetAsyncKeyState(VK_UP))
		{
			selectUpSettingsMenu();
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			selectDownSettingsMenu();
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			switch (rowSelected)
			{
			default:
			case 1:
				settings.difficulty = 0;
				settings.fps = 30 + 15 * settings.difficulty;
				return;
			case 2:
				settings.difficulty = 1;
				settings.fps = 30 + 15 * settings.difficulty;
				return;
			case 3:
				settings.difficulty = 2;
				settings.fps = 30 + 15 * settings.difficulty;
				return;
			case 4:
				goToSkinMenu(settings);
				goToSettingsMenu();
				break;
			case 5:
				return;
			}
		}
	}
}

void Menu::selectUpMainMenu()
{
	switch (rowSelected)
	{
	case 1:
		deselectNewGame();
		selectExit();

		rowSelected = 4;
		break;
	case 2:
		deselectContinue();
		selectNewGame();

		rowSelected = 1;
		break;
	case 3:
		deselectSettings();
		selectContinue();

		rowSelected = 2;
		break;
	case 4:
		deselectExit();
		selectSettings();

		rowSelected = 3;
		break;
	}
}

void Menu::selectDownMainMenu()
{
	switch (rowSelected)
	{
	case 1:
		deselectNewGame();
		selectContinue();

		rowSelected = 2;
		break;
	case 2:
		deselectContinue();
		selectSettings();

		rowSelected = 3;
		break;
	case 3:
		deselectSettings();
		selectExit();

		rowSelected = 4;
		break;
	case 4:
		deselectExit();
		selectNewGame();

		rowSelected = 1;
		break;
	}
}

void Menu::selectUpSettingsMenu()
{
	switch (rowSelected)
	{
	case 1:
		deselectEasy();
		selectBack();

		rowSelected = 5;
		break;
	case 2:
		deselectNormal();
		selectEasy();

		rowSelected = 1;
		break;
	case 3:
		deselectHard();
		selectNormal();

		rowSelected = 2;
		break;
	case 4:
		deselectSkin();
		selectHard();

		rowSelected = 3;
		break;
	case 5:
		deselectBack();
		selectSkin();

		rowSelected = 4;
		break;
	}
}

void Menu::selectDownSettingsMenu()
{
	switch (rowSelected)
	{
	case 1:
		deselectEasy();
		selectNormal();

		rowSelected = 2;
		break;
	case 2:
		deselectNormal();
		selectHard();

		rowSelected = 3;
		break;
	case 3:
		deselectHard();
		selectSkin();

		rowSelected = 4;
		break;
	case 4:
		deselectSkin();
		selectBack();
	
		rowSelected = 5;
		break;
	case 5:
		deselectBack();
		selectEasy();

		rowSelected = 1;
		break;
	}
}

void Menu::selectNewGame()
{
	setCursorPosition(WIDTH / 2 - 3, HEIGHT / 2 - 3);
	std::cout << NEW_GAME_SELECTED;
}

void Menu::selectContinue()
{
	setCursorPosition(WIDTH / 2 - 3, HEIGHT / 2 - 2);
	std::cout << CONTINUE_SELECTED;
}

void Menu::selectSettings()
{
	setCursorPosition(WIDTH / 2 - 3, HEIGHT / 2 - 1);
	std::cout << SETTINGS_SELECTED;
}

void Menu::selectExit()
{
	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2);
	std::cout << EXIT_SELECTED;
}

void Menu::selectEasy()
{
	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2 - 3);
	std::cout << EASY_SELECTED;
}

void Menu::selectNormal()
{
	setCursorPosition(WIDTH / 2 - 2, HEIGHT / 2 - 2);
	std::cout << NORMAL_SELECTED;
}

void Menu::selectHard()
{
	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2 - 1);
	std::cout << HARD_SELECTED;
}

void Menu::selectBack()
{
	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2 + 1);
	std::cout << BACK_SELECTED;
}

void Menu::selectSkin1()
{
	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2 - 1);
	std::cout << player1[0];

	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2);
	std::cout << player1[1];

	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2 + 1);
	std::cout << player1[2];
}

void Menu::selectSkin2()
{
	setCursorPosition(WIDTH / 2 - 2, HEIGHT / 2);
	std::cout << player2[0];
}

void Menu::selectSkin3()
{
	setCursorPosition(WIDTH / 2, HEIGHT / 2);
	std::cout << player3[0];
}

void Menu::selectSkin()
{
	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2);
	std::cout << SKIN_SELECTED;
}

void Menu::deselectNewGame()
{
	setCursorPosition(WIDTH / 2 - 3, HEIGHT / 2 - 3);
	std::cout << NEW_GAME;
}

void Menu::deselectContinue()
{
	setCursorPosition(WIDTH / 2 - 3, HEIGHT / 2 - 2);
	std::cout << CONTINUE;
}

void Menu::deselectSettings()
{
	setCursorPosition(WIDTH / 2 - 3, HEIGHT / 2 - 1);
	std::cout << SETTINGS;
}

void Menu::deselectExit()
{
	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2);
	std::cout << EXIT;
}

void Menu::deselectEasy()
{
	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2 - 3);
	std::cout << EASY;
}

void Menu::deselectNormal()
{
	setCursorPosition(WIDTH / 2 - 2, HEIGHT / 2 - 2);
	std::cout << NORMAL;
}

void Menu::deselectHard()
{
	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2 - 1);
	std::cout << HARD;
}

void Menu::deselectBack()
{
	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2 + 1);
	std::cout << BACK;
}

void Menu::deselectSkin()
{
	setCursorPosition(WIDTH / 2 - 1, HEIGHT / 2);
	std::cout << SKIN;
}




