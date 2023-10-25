#include <Windows.h>
#include <iostream>
#include <vector>
#include "MemoryManipulation.h"

MemoryManipulation MemoryManipulator;
bool isInfiniteHealthEnabled = false;
bool isSmallPlayerEnabled = false;
DWORD_PTR* playerUnityObject = nullptr;
static struct UnityPlayerOffsets
{
	static const int PosX = 0x90;
	static const int PosY = 0x94;
	static const int ScaleX = 0xE0;
	static const int ScaleY = 0xE4;
};
DWORD_PTR* health = nullptr;


float playerPosX;
float playerPosY;

void InfiniteHealth() {
	if (GetAsyncKeyState('P') & 1) {
		isInfiniteHealthEnabled = !isInfiniteHealthEnabled;
		Sleep(100);
	}
	if(health == NULL) { health = MemoryManipulator.GetAddress(MemoryManipulator.cupheadModuleAddress, MemoryManipulator.healthOffset); }
	if (isInfiniteHealthEnabled) {
			if (*health < 3) *health = 3;
	}

	return;
}
void SmallPlayer() {
	if (GetAsyncKeyState('O') & 1) {
		isSmallPlayerEnabled = !isSmallPlayerEnabled;
		Sleep(100);
	}
	if (playerUnityObject == NULL) { 
		playerUnityObject = MemoryManipulator.GetAddress(MemoryManipulator.unityModuleAddress, MemoryManipulator.unityPlayerObjectOffset);
		
	}
	else {
		if (isSmallPlayerEnabled) {
			float* playerX = (float*)(*playerUnityObject + (int)UnityPlayerOffsets::ScaleX);
			float* playerY = (float*)(*playerUnityObject + (int)UnityPlayerOffsets::ScaleY);
			*playerX = (float)0.5;
			*playerY = (float)0.5;
			
		}
		
		
	}

}
void Trainer() {
	MemoryManipulator = MemoryManipulation();
	MessageBox(0, "injected", "injected", 0);
	while (true) {
		if (GetAsyncKeyState(VK_END)) {
			MessageBox(0, "Exited Trainer", "by Insert Name", 0);
			return;
		}


		InfiniteHealth();
		SmallPlayer();
		Sleep(1);
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Trainer, NULL, 0, NULL);
	}
	return true;
}