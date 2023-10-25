#include <Windows.h>
#include <iostream>
#include <vector>
#include "MemoryManipulation.h"
#include "PlayerHacks.h"
extern MemoryManipulation MemoryManipulator;
PlayerHacks playerHacks;
void Trainer() {
	MemoryManipulator = MemoryManipulation();
	playerHacks = PlayerHacks(MemoryManipulator);
	MessageBox(0, "injected", "injected", 0);
	while (true) {
		if (GetAsyncKeyState(VK_END)) {
			MessageBox(0, "Exited Trainer", "by Insert Name", 0);
			return;
		}


		playerHacks.InfiniteHealth();
		playerHacks.SmallPlayer();
		Sleep(1);
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Trainer, NULL, 0, NULL);
	}
	return true;
}