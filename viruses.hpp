#ifndef _VIRUSES_HPP_
#define _VIRUSES_HPP_
#include <iostream>
#include "bloomFilter.hpp"

using namespace std;

class viruses{
  string name;
  bloomFilter* bloom;
  // skipList* skip;

public:
  viruses(string name, int len);
};
#endif
