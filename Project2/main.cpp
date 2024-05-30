#include "include/main.h"

int WinMain(int argv, char** argc) {
	Main cmain;

	bool isRunning = true;

	cmain.createWindow();

	cmain.createFPSText();


	while (isRunning) {
		isRunning = cmain.processEvent();
		cmain.renderFPSText();
		cmain.gameGrav();
		cmain.update();
		cmain.renderWindow();
	}

	cmain.onQuit();

	return 0;
	
}