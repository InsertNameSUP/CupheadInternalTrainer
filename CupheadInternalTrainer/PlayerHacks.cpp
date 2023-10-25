#include "PlayerHacks.h"
#include "MemoryManipulation.h"
#include <Windows.h>
#include <iostream>
#include <vector>
bool isInfiniteHealthEnabled = false;
bool isSmallPlayerEnabled = false;
DWORD_PTR* playerUnityObject = nullptr;
DWORD_PTR* health = nullptr;
float playerPosX;
float playerPosY;
MemoryManipulation MemoryManipulator;
PlayerHacks::PlayerHacks(MemoryManipulation m) {
	MemoryManipulator = m;
	isInfiniteHealthEnabled = false;
	isSmallPlayerEnabled = false;
}
PlayerHacks::PlayerHacks() {
	isInfiniteHealthEnabled = false;
	isSmallPlayerEnabled = false;
}
void PlayerHacks::InfiniteHealth() {
	if (GetAsyncKeyState('P') & 1) {
		isInfiniteHealthEnabled = !isInfiniteHealthEnabled;
		Sleep(100);
	}
	if (health == NULL) { health = MemoryManipulator.GetAddress(MemoryManipulator.cupheadModuleAddress, MemoryManipulator.healthOffset); }
	if (isInfiniteHealthEnabled) {
		if (*health < 3) *health = 3;
	}

	return;
}
void PlayerHacks::SmallPlayer() {
	if (GetAsyncKeyState('O') & 1) {
		isSmallPlayerEnabled = !isSmallPlayerEnabled;
		Sleep(100);
	}
	if (playerUnityObject == NULL) {
		playerUnityObject = MemoryManipulator.GetAddress(MemoryManipulator.unityModuleAddress, MemoryManipulator.unityPlayerObjectOffset);

	}
	else {
		if (isSmallPlayerEnabled) {
			float* playerX = (float*)(*playerUnityObject + (int)MemoryManipulation::UnityPlayerOffsets::ScaleX);
			float* playerY = (float*)(*playerUnityObject + (int)MemoryManipulation::UnityPlayerOffsets::ScaleY);
			*playerX = (float)0.5;
			*playerY = (float)0.5;

		}


	}

}