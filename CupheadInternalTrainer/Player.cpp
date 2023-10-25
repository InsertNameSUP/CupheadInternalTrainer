#include <Windows.h>
#include <iostream>
#include <vector>
#include "MemoryEdit.cpp"
static bool isSmallPlayerEnabled = false;
static DWORD_PTR* playerUnityObject = nullptr;
static std::vector<int> unityPlayerObjectOffset{ 0x100, 0x2B8, 0x78, 0x10, 0xC8, 0x38 };
static struct UnityPlayerOffsets
{
	static const int PosX = 0x90;
	static const int PosY = 0x94;
	static const int ScaleX = 0xE0;
	static const int ScaleY = 0xE4;
};
static class Player {
	float playerPosX;
	float playerPosY;

	public : static void SmallPlayer() {
		if (GetAsyncKeyState('O') & 1) {
			isSmallPlayerEnabled = !isSmallPlayerEnabled;
			Sleep(100);
		}
		if (playerUnityObject == NULL) {
			playerUnityObject = MemoryEdit::GetAddress(MemoryEdit::unityModuleAddress, unityPlayerObjectOffset);

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
};