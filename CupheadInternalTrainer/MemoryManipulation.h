#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
class MemoryManipulation
{
public:
	MemoryManipulation();
	DWORD_PTR* cupheadModuleAddress;
	DWORD_PTR* unityModuleAddress;
	std::vector<int> unityPlayerObjectOffset{ 0x100, 0x2B8, 0x78, 0x10, 0xC8, 0x38 };
	std::vector<int> healthOffset{ 0xA0, 0xD20, 0xE8, 0x20, 0xA8, 0x10, 0xB4 };
	struct UnityPlayerOffsets {
		static const int PosX = 0x90;
		static const int PosY = 0x94;
		static const int ScaleX = 0xE0;
		static const int ScaleY = 0xE4;
	};
	DWORD_PTR* GetAddress(DWORD_PTR* baseAddress, std::vector<int> offsets);
};

