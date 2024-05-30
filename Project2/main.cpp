#include "include/main.h"

int WinMain(int argv, char** argc) {
	Main cmain;

	bool isRunning = true;

	cmain.createWindow();

	while (isRunning) {
		isRunning = cmain.processEvent();
		cmain.update();
		cmain.renderWindow();
	}

	cmain.onQuit();

	return 0;
	
}