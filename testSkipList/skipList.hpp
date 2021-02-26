#ifndef _SKIPLIST_HPP_
#define _SKIPLIST_HPP_



class List{
public:
  int* item;
  List* next;
  List(int* i);
  List(int* i, List* n);
  ~List();
  void testPrint();
};

class listHeader{
  List* start;
public:
  int pl;
  listHeader();
  ~listHeader();
  void insertItem(int* i);
  void testPrint();
  listHeader* forNextLayer();
};
/////////////////////////////////////
class skipNode{
public:
  listHeader* item;
  skipNode* next;
  skipNode(listHeader* i);
  skipNode();
  skipNode(listHeader* i, skipNode* n);
  ~skipNode();
  void testPrint();
};

class skipHeader{
  skipNode* start;
  skipNode* end;
  int lvlnum;
  int max_lvl;
  void addLayer();
public:
  skipHeader(listHeader* i);
  ~skipHeader();
  void insertItem(int* i);
  void testPrint();
};

#endif
