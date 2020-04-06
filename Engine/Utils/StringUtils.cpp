#include "StringUtils.h"

#include <cstdint>
#include <string>

HexString StringUtils::PtrToHexString(uintptr_t pointer)
{
	const HexString string;

	const auto p8pointer = (uint8_t*)&pointer;
	const auto p16lut	 = (char16_t*)_byteLut;
	const auto p16string = (char16_t*)string.value;

	const int size16 = (HexString::SIZE - 2) / 2;
	
	for (auto i = 0; i < size16; i++)
	{
		p16string[size16 - i] = p16lut[p8pointer[i]];
	}

	return string;
}
