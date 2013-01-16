#include <iostream>
#include <cmath>
#include <boost/program_options.hpp>
#include "md5.hpp"

using namespace std;
using namespace md5;
namespace po = boost::program_options;

uint32 do_hash(const char* text, size_t length) {
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
	LinearCounter(int sz) : size(sz) {
		vector = (char*)malloc(size);
		memset(vector, 0, size);
	}
	
	~LinearCounter() {
		free(vector);
	}
	
	void offer(const char* text, size_t textSize) {
		uint32 h = do_hash(text, textSize) % ((int)size * 8);
		
		uint32 byte = h / 8;
		uint32 bit = h % 8;
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
	
	size_t unusedBits() {
		return length() - usedBits();
	}
	
	double usedBitsProportion() {
		return (double)usedBits() / length();
	}
	
	long cardinalityEstimate() {
		size_t unused_bits = unusedBits();
		if (unused_bits == 0) {
			return -1;
		} else {
			return length() * log((double)length() / unusedBits());
		}
	}
	
	size_t length() {
		return size * 8;
	}
};

int main(int argc, char** argv) {
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("size", po::value<int>()->default_value(125000), "the size of the linear counter in bytes")
		("buffer", po::value<int>()->default_value(1024), "the size of the line buffer in bytes");
	
	po::variables_map vm;
	
	po::basic_parsed_options<char> opts = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
	po::store(opts, vm);
	
  if (vm.count("help")) {
		cout << desc << endl;
		return 1;
	}
	
	int size = vm["size"].as<int>();
	string line;
	LinearCounter a(size);
	
	int buffer_size = vm["size"].as<int>();
	char buffer[buffer_size];
	
	while (fgets(buffer, buffer_size, stdin)) {
		a.offer(buffer, strlen(buffer));
	}
	
	long est = a.cardinalityEstimate();
	if (est < 0) {
		cerr << "Estimate could not be given. Try greater mask (--size)" << endl;
		return 255;
	} else {
		cout << est << endl;
		return 0;
	}
}