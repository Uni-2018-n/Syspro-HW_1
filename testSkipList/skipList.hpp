#ifndef _SKIPLIST_HPP_
#define _SKIPLIST_HPP_

#define MAXIMUM 3

class List{//nodes
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

class listHeader{//list
  List* start;
public:
  int pl;

  listHeader();
  ~listHeader();
  List* insertAtStart(List* i);
  List* insertItem(int* i, int top_lvl);
  List* searchItem(int i);
  void testPrint();
};
/////////////////////////////////////
class skipNode{//nodes of lists
public:
  listHeader* item;
  skipNode* prev;
  skipNode* next;

  skipNode();
  ~skipNode();
  List* insertAtStart(List* i);
  void testPrint();
};

class skipHeader{//list of lists
  skipNode* start;
  skipNode* end;
  int lvlnum;
  int max_lvl;
  void addLayer();
public:
  skipHeader();
  ~skipHeader();
  bool searchItem(int i);
  bool insertItem(int* i);
  void testPrint();
};
#endif
