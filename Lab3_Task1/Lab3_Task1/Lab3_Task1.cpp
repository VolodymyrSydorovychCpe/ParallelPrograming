#include <iostream>
#include <omp.h>
#include <intrin.h>
#include <string.h>
#include <map>

std::string getProcessorType() {
	std::string result = "OTHER";

	char INTELName[13] = "GenuineIntel";
	char AMDName[13] = "AuthenticAMD";
	char ProcessorName[13];
	ProcessorName[12] = 0;
	/*cpuInfo - An array of four integers that contains the information returned in EAX, EBX, ECX, and EDX about supported features of the CPU*/
	int cpuInfo[4];
	__cpuid(cpuInfo, 0);
	memcpy(ProcessorName, &cpuInfo[1], 4);
	memcpy(ProcessorName + 4, &cpuInfo[3], 4);
	memcpy(ProcessorName + 8, &cpuInfo[2], 4);
	
	if (memcmp(INTELName, ProcessorName, 12) == 0)
		result = "INTEL";
	else if (memcmp(AMDName, ProcessorName, 12) == 0) {
		result = "AMD";
	}
	return result;
}

unsigned check_max_fun(unsigned* ExtFun) {
	int cpuInfo[4];
	__cpuidex(cpuInfo, 0, 0);
	int res = cpuInfo[0];
	__cpuidex(cpuInfo, 0x80000000, 0);
	if (ExtFun) {
		*ExtFun = cpuInfo[0];
	}
	return res;
}

bool check_properties(uint32_t fun, uint32_t index, uint32_t bit) {
	uint32_t r[4];
	uint32_t mask = 1 << bit;
	__cpuidex((int*)r, fun, 0);
	return (r[index] & mask) == mask;
}

std::map<std::string, bool> SIMDSupport() {
	std::map<std::string, bool> result;
	unsigned max_fun = check_max_fun(0);
	if (max_fun >= 1) {
		if (check_properties(1, 2, 26) && check_properties(1, 2, 27)) {
			unsigned long long res = _xgetbv(0);
			int flags1 = 7 + (7 << 5), flags2 = 7, flags3 = 3;
			bool AVX512 = (res & flags1) == flags1;
			bool AVX = (res & flags2) == flags2;
			bool SSE = (res & flags3) == flags3;

			if (max_fun >= 7 && AVX512) {
				if (check_properties(7, 1, 16)) {
					result["AVX512SUPPORT"] = true;
				}
			}
			if (AVX) {
				if (max_fun >= 7) {
					if (check_properties(7, 1, 5)) {
						result["AVX2SUPPORT"] = true;
					}
				}
				if (max_fun >= 1) {
					if (check_properties(1, 2, 28)) {
						result["AVXSUPPORT"] = true;
					}
				}
			}
			if (SSE) {
				if (check_properties(1, 2, 20)) {
					result["SSE42SUPPORT"] = true;
				}
				if (check_properties(1, 2, 19)) {
					result["SSE41SUPPORT"] = true;
				}
				if (check_properties(1, 2, 9)) {
					result["SSSE3SUPPORT"] = true;
				}
				if (check_properties(1, 2, 0)) {
					result["SSE3SUPPORT"] = true;
				}
				if (check_properties(1, 3, 26)) {
					result["SSE2SUPPORT"] = true;
				}
				if (check_properties(1, 3, 25)) {
					result["SSESUPPORT"] = true;
				}
			}
		}
	}
	return result;
}

int main()
{
	std::string processorType;
	processorType = getProcessorType();

	std::cout << "ProcessorType: " << processorType << "\n";

	std::map<std::string, bool> result = SIMDSupport();

	std::cout << "\nSSE: " << result["SSESUPPORT"];
	std::cout << "\nSSE2: " << result["SSE2SUPPORT"];
	std::cout << "\nSSE3: " << result["SSE3SUPPORT"];
	std::cout << "\nSSE41: " << result["SSE41SUPPORT"];
	std::cout << "\nSSE42: " << result["SSE42SUPPORT"];
	std::cout << "\nSSSE3: " << result["SSSE3SUPPORT"];
	std::cout << "\nAVX: " << result["AVXSUPPORT"];
	std::cout << "\nAVX2: " << result["AVX2SUPPORT"];
	std::cout << "\nAVX512: " << result["AVX512SUPPORT"];
}
