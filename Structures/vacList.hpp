#ifndef _VACLIST_HPP_
#define _VACLIST_HPP_

#include "../classes.hpp"

class VlistNode{
public:
  vaccinateRecord* item;
  VlistNode* next;

  VlistNode(vaccinateRecord*);
  ~VlistNode();
};

class VlistHeader{
public:
  VlistNode* start;
  VlistNode* end;
  VlistHeader();
  ~VlistHeader();
  void insertItem(vaccinateRecord* i);
  void testPrint();
};
#endif
