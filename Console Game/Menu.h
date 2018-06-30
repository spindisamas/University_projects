#ifndef MENU_H
#define MENU_H
#include "SideFuncs.h"
class Menu
{
public:
	Menu();
	~Menu();

	void goToMainMenu();

	void browse(Settings& settings);


private:

	void clearSkin();
	void goToSettingsMenu();
	void goToSkinMenu(Settings& settings);
	void browseSettings(Settings& settings);

	void selectUpMainMenu();
	void selectDownMainMenu();

	void selectUpSettingsMenu();
	void selectDownSettingsMenu();

	void selectNewGame();
	void selectContinue();
	void selectSettings();
	void selectExit();
	void selectEasy();
	void selectNormal();
	void selectHard();
	void selectBack();
	void selectSkin1();
	void selectSkin2();
	void selectSkin3();
	void selectSkin();

	void deselectNewGame();
	void deselectContinue();
	void deselectSettings();
	void deselectExit();
	void deselectEasy();
	void deselectNormal();
	void deselectHard();
	void deselectBack();
	void deselectSkin();

	unsigned rowSelected;
};

#endif // !MENU_H
