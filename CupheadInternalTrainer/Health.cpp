#include <Windows.h>
#include <iostream>
#include <vector>
#include "MemoryEdit.cpp"
const static std::vector<int> healthOffset{ 0xA0, 0xD20, 0xE8, 0x20, 0xA8, 0x10, 0xB4 }; // Offsets found through pointerscan -> CE
DWORD_PTR* health = nullptr;
static bool isInfiniteHealthEnabled;
static class Health {
public : static void InfiniteHealth() {
		if (GetAsyncKeyState('P') & 1) {
			isInfiniteHealthEnabled = !isInfiniteHealthEnabled;
			Sleep(100);
		}
		if (health == NULL) { health = MemoryEdit::GetAddress(MemoryEdit::cupheadModuleAddress, healthOffset); }
		if (isInfiniteHealthEnabled) {
			if (*health < 3) *health = 3;
		}

		return;
	}
};