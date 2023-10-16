#include <Windows.h>

bool isInfiniteHealthEnabled = true;
DWORD_PTR* moduleAddress;
DWORD healthOffset[] = { 0xA0, 0xD20, 0xE8, 0x20, 0xA8, 0x10, 0xB4 };
DWORD_PTR* health;
DWORD_PTR* GetAddress(DWORD_PTR* baseAddress, DWORD offsets[]) {
	DWORD_PTR* currentAddress = baseAddress;
	
	for (int i = 0; i < 7; i++) {
		currentAddress = (DWORD_PTR*)(*currentAddress + offsets[i]);
	}
	return currentAddress;
}
void InfiniteHealth() {
	if (isInfiniteHealthEnabled) {
		if(*health < 3) *health = 3;
	}

	return;
}
void Trainer() {
	moduleAddress = (DWORD_PTR*)((DWORD_PTR)GetModuleHandleA("mono.dll") + 0x00264A68);
	health = GetAddress(moduleAddress, healthOffset);
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