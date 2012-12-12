#include <iostream>
#include <cmath>
#include "md5.hpp"

using namespace std;
using namespace md5;

uint32 hash(const char* text, size_t length) {
	md5_context md5;
	uint8 digest[16];
	uint32* result = (uint32*)digest;
	md5_starts(&md5);
	md5_update(&md5, (uint8 *)text, length);
	md5_finish(&md5, digest);
	return *result;
};

int populationCount(int x) {
		x = x - ((x >> 1) & 0x55555555);
		x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
		x = (x + (x >> 4)) & 0x0F0F0F0F;
		x = x + (x >> 8);
		x = x + (x >> 16);
		return x & 0x0000003F;
}

class LinearCounter {

private:
	char* vector;
	size_t size;
	
public:
	LinearCounter() : size(1250000) {
		vector = (char*)malloc(size);
		memset(vector, 0,  size);
	}
	
	~LinearCounter() {
		free(vector);
	}
	
	void offer(const char* text, size_t textSize) {
		int h = hash(text, textSize) % (size * 8);
		
		int byte = h / 8;
		int bit = h % 8;
		vector[byte] |= 1 << bit;
	}
	
	int usedBits() {
		int* p = (int*)vector;
		int* last = (int*)(vector + size);
		int result = 0;
		while(p < last) {
			result += populationCount(*(p++));
		}
		return result;
	}
	
	int unusedBits() {
		return length() - usedBits();
	}
	
	float usedBitsProportion() {
		return (float)usedBits() / length();
	}
	
	int cardinalityEstimate() {
		return length() * log((float)length() / unusedBits());
	}
	
	int length() {
		return size * 8;
	}
};

int main(int argc, char** argv) {
	string line;
	LinearCounter a;
	
	while (getline(cin, line)) {
		a.offer(line.c_str(), line.size());
	}
	
	cout << a.cardinalityEstimate() << endl;
	return 0;
}