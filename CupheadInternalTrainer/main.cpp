#include <Windows.h>
#include <iostream>
#include <vector>


// UNITY OBJECT ADDRESS - ("mono.dll"+0026B610) + 0x100, 0x2B8, 0x78, 0x10, 0xC8, 0x38
// UNITY POS X OFFSET - 0x90
// UNITY POS Y OFFSET - 0x94
// UNITY SCALE X OFFSET - 0x50
// UNITY SCALE Y OFFSET - 0x54
// UNITY SCALE Z OFFSET - 0x58
bool isInfiniteHealthEnabled = false;
bool isSmallPlayerEnabled = false;
DWORD_PTR* cupheadModuleAddress;
DWORD_PTR* unityModuleAddress;
DWORD_PTR* playerUnityObject = nullptr;
static struct UnityPlayerOffsets
{
	static const int PosX = 0x90;
	static const int PosY = 0x94;
	static const int ScaleX = 0xE0;
	static const int ScaleY = 0xE4;
};
std::vector<int> unityPlayerObjectOffset{ 0x100, 0x2B8, 0x78, 0x10, 0xC8, 0x38 };
std::vector<int> healthOffset { 0xA0, 0xD20, 0xE8, 0x20, 0xA8, 0x10, 0xB4 }; // Offsets found through pointerscan -> CE
DWORD_PTR* health = nullptr;


float playerPosX;
float playerPosY;
DWORD_PTR* GetAddress(DWORD_PTR* baseAddress, std::vector<int> offsets) {
	DWORD_PTR* currentAddress = baseAddress;
	
	for (int i = 0; i < offsets.size(); i++) {
		if (currentAddress == NULL) return nullptr; // Prevent dereferencing uninitialized pointers (Runtime Crash - Access Violation)
		currentAddress = (DWORD_PTR*)(*currentAddress + offsets[i]);
	}
	return currentAddress;
}
void InfiniteHealth() {
	if (GetAsyncKeyState('P') & 1) {
		isInfiniteHealthEnabled = !isInfiniteHealthEnabled;
		Sleep(100);
	}
	if(health == NULL) { health = GetAddress(cupheadModuleAddress, healthOffset); }
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
		playerUnityObject = GetAddress(unityModuleAddress, unityPlayerObjectOffset);
		
	}
	else {
		if (isSmallPlayerEnabled) {
			DWORD_PTR* playerX = (DWORD_PTR*)(*playerUnityObject + (int)UnityPlayerOffsets::ScaleX);
			DWORD_PTR* playerY = (DWORD_PTR*)(*playerUnityObject + (int)UnityPlayerOffsets::ScaleY);
			*playerX = (float)0.5; // Setting value to 0 in game? Fix Soon: Most likely due to cast from float to DWORD or playerX being a DWORD to begin with?
			*playerY = (float)0.5;
			
		}
		
		
	}

}
void Trainer() {
	cupheadModuleAddress = (DWORD_PTR*)((DWORD_PTR)GetModuleHandleA("mono.dll") + 0x00264A68);
	unityModuleAddress = (DWORD_PTR*)((DWORD_PTR)GetModuleHandleA("mono.dll") + 0x0026B610);
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