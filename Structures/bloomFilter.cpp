#include <iostream>
#include <cstring>
#include "bloomFilter.hpp"

using namespace std;

bloomFilter::bloomFilter(int l):
len(l){
  array = new char[len]();
  for(int i=0;i<len;i++){
    array[i] = 0;
  }
}

bloomFilter::~bloomFilter(){
  delete array;
}

void bloomFilter::insert(int s){
  unsigned char* s_char = new unsigned char[sizeof(s)]();
  for(int i=0;i<k;i++){
    memcpy(s_char, &s, sizeof(s));
    int bit= hash_i(s_char,i) % (len*8);
    int array_index = bit / 8;
    int bit_index = bit % 8;
    array[array_index] |= 1 << bit_index;
  }
  delete s_char;
}

bool bloomFilter::is_inside(int s){
  unsigned char* s_char = new unsigned char[sizeof(s)]();
  for(int i=0;i<k;i++){
    memcpy(s_char, &s, sizeof(s));
    int bit= hash_i(s_char,i) % (len*8);
    int array_index = bit / 8;
    int bit_index = bit % 8;
    if((array[array_index] & (1 << bit_index)) ==0){
      delete s_char;
      return false;
    }
  }
  delete s_char;
  return true;
}



//for hash
unsigned long bloomFilter::djb2(unsigned char *str) {
	unsigned long hash = 5381;
	int c;
	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return hash;
}


unsigned long bloomFilter::sdbm(unsigned char *str) {
	unsigned long hash = 0;
	int c;

	while ((c = *str++)) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}


unsigned long bloomFilter::hash_i(unsigned char *str, unsigned int i) {
	return djb2(str) + i*sdbm(str) + i*i;
}
