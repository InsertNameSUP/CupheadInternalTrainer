#include "MemoryManipulation.h"
#include <Windows.h>
#include <iostream>
#include <vector>

std::vector<int> unityPlayerObjectOffset{ 0x100, 0x2B8, 0x78, 0x10, 0xC8, 0x38 };
std::vector<int> healthOffset{ 0xA0, 0xD20, 0xE8, 0x20, 0xA8, 0x10, 0xB4 }; // Offsets found through pointerscan -> CE
MemoryManipulation::MemoryManipulation() {
	cupheadModuleAddress = (DWORD_PTR*)((DWORD_PTR)GetModuleHandleA("mono.dll") + 0x00264A68);
	unityModuleAddress = (DWORD_PTR*)((DWORD_PTR)GetModuleHandleA("mono.dll") + 0x0026B610);
}
DWORD_PTR* MemoryManipulation::GetAddress(DWORD_PTR* baseAddress, std::vector<int> offsets) {
	DWORD_PTR* currentAddress = baseAddress;

	for (int i = 0; i < offsets.size(); i++) {
		if (currentAddress == NULL) return nullptr; // Prevent dereferencing uninitialized pointers (Runtime Crash - Access Violation)
		currentAddress = (DWORD_PTR*)(*currentAddress + offsets[i]);
	}
	return currentAddress;
}

