#include "include/main.h"

int main(int argv, char** argc) {
	Main cmain;

	bool isRunning = true;

	cmain.createWindow();

	cmain.createFPSText();


	while (isRunning) {
		isRunning = cmain.processEvent();
		cmain.debugLoop();
		cmain.renderFPSText();
		cmain.gameGrav();
		cmain.update();
		cmain.renderWindow();
	}

	cmain.onQuit();

	return 0;
	
}