#ifndef _SKIPLIST_HPP_
#define _SKIPLIST_HPP_

#define MAXIMUM 3

class List{//nodes
  int* item;
  List* next;
  List* lower_level;
public:
  List(int* i);
  List(List* i);
  List(List* i, List* n);
  List(int* i, List* n);
  ~List();

  int getItem(){
    return *item;
  }
  List* getNext(){
    return next;
  }
  void setNext(List* n){
    next = n;
  }
  List* getLowerLevel(){
    return lower_level;
  }

  void testPrint();
};

class listHeader{//list
  List* start;
  int pl;
public:
  listHeader();
  ~listHeader();
  List* insertAtStart(List* i);
  List* insertItem(int* i, int top_lvl);
  List* searchItem(int i);

  int getPl(){
    return pl;
  }

  void testPrint();
};
/////////////////////////////////////
class skipNode{//nodes of lists
  skipNode* prev;
  skipNode* next;
  listHeader* item;
public:
  skipNode();
  ~skipNode();
  List* insertAtStart(List* i);
  
  skipNode* getNext(){
    return next;
  }
  skipNode* getPrev(){
    return prev;
  }
  listHeader* getItem(){
    return item;
  }
  void setNext(skipNode* n){
    next = n;
  }
  void setPrev(skipNode* p){
    prev = p;
  }

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
