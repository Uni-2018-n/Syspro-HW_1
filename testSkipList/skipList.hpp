#ifndef _SKIPLIST_HPP_
#define _SKIPLIST_HPP_



class List{
public:
  int* item;
  List* lower_level;
  List* next;
  List(int* i);
  List(List* i);
  List(List* i, List* n);
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
  void insertItem(List* i);
  void testPrint();
  listHeader* forNextLayer();
};
/////////////////////////////////////
class skipNode{
public:
  listHeader* item;
  skipNode* prev;
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
  skipHeader(listHeader*);
  ~skipHeader();
  void insertItem(int* i);
  void testPrint();
};

#endif
