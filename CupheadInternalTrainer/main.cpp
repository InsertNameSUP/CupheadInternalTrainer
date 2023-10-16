#include <Windows.h>
#include <iostream>
#include <vector>
bool isInfiniteHealthEnabled = false;
DWORD_PTR* moduleAddress;
std::vector<DWORD> healthOffset { 0xA0, 0xD20, 0xE8, 0x20, 0xA8, 0x10, 0xB4 }; // Offsets found through pointerscan -> CE
DWORD_PTR* health = NULL;
DWORD_PTR* GetAddress(DWORD_PTR* baseAddress, std::vector<DWORD> offsets) {
	DWORD_PTR* currentAddress = baseAddress;
	
	for (int i = 0; i < healthOffset.size(); i++) {
		if (*currentAddress == NULL) return NULL; // Prevent dereferencing uninitialized pointers (Runtime Crash - Access Violation)
		currentAddress = (DWORD_PTR*)(*currentAddress + offsets[i]);
	}
	return currentAddress;
}
void InfiniteHealth() {


	if(health == NULL) { health = GetAddress(moduleAddress, healthOffset); }
	if (isInfiniteHealthEnabled) {
			if (*health < 1 || *health > 3) return;
			if (*health < 3) *health = 3;
	}

	return;
}
void Trainer() {
	moduleAddress = (DWORD_PTR*)((DWORD_PTR)GetModuleHandleA("mono.dll") + 0x00264A68);
	MessageBox(0, "injected", "injected", 0);
	while (true) {

		if (GetAsyncKeyState('P') & 1) {
			isInfiniteHealthEnabled = !isInfiniteHealthEnabled;
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_END)) {
			MessageBox(0, "Exited Trainer", "by Insert Name", 0);
			return;
		}
		InfiniteHealth();
		Sleep(1);
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Trainer, NULL, 0, NULL);
	}
	return true;
}