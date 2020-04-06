#include <cstdint>

// std::string has size 40 bytes vs 19 bytes on x64
//					and 28 bytes vs 11 bytes on x86					 
struct HexString
{
#ifdef _WIN64
	static const int SIZE = 19;
	char value[SIZE] = "0x0000000000000000";
#else
	static const int SIZE = 11;
	char value[11] = "0x00000000";
#endif
};

class StringUtils
{
public:
	StringUtils() = delete;

	static HexString PtrToHexString(uintptr_t pointer);

private:
	static constexpr char _byteLut[] = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f303132333435363738393a3b3c3d3e3f"\
									   "404142434445464748494a4b4c4d4e4f505152535455565758595a5b5c5d5e5f606162636465666768696a6b6c6d6e6f707172737475767778797a7b7c7d7e7f"\
									   "808182838485868788898a8b8c8d8e8f909192939495969798999a9b9c9d9e9fa0a1a2a3a4a5a6a7a8a9aaabacadaeafb0b1b2b3b4b5b6b7b8b9babbbcbdbebf"\
									   "c0c1c2c3c4c5c6c7c8c9cacbcccdcecfd0d1d2d3d4d5d6d7d8d9dadbdcdddedfe0e1e2e3e4e5e6e7e8e9eaebecedeeeff0f1f2f3f4f5f6f7f8f9fafbfcfdfeff";
};
