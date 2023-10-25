#include <Windows.h>
#include <iostream>
#include <vector>
static class MemoryEdit {
	public : static DWORD_PTR* cupheadModuleAddress;
	public : static DWORD_PTR* unityModuleAddress;
public : static void Initialize() {
		cupheadModuleAddress = (DWORD_PTR*)((DWORD_PTR)GetModuleHandleA("mono.dll") + 0x00264A68);
		unityModuleAddress = (DWORD_PTR*)((DWORD_PTR)GetModuleHandleA("mono.dll") + 0x0026B610);
	}
	public: static DWORD_PTR* GetAddress(DWORD_PTR* baseAddress, std::vector<int> offsets) {
		DWORD_PTR* currentAddress = baseAddress;

		for (int i = 0; i < offsets.size(); i++) {
			if (currentAddress == NULL) return nullptr; // Prevent dereferencing uninitialized pointers (Runtime Crash - Access Violation)
			currentAddress = (DWORD_PTR*)(*currentAddress + offsets[i]);
		}
		return currentAddress;
	}
};