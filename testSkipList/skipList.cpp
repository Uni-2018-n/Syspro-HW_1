#include <iostream>
#include "skipList.hpp"
#include <math.h>
using namespace std;

//////////////////////////// List
List::List(int* i){//initialize i
  item = i;
  lower_level = NULL;
  next = NULL;
}

List::List(List* i){//copy i and set lower_level
  item = i->item;
  lower_level = i;
  next = NULL;
}

List::List(List* i, List* n){//copy i and set it to lower lever also add next node
  item = i->item;
  next = n;
  lower_level= i;
}

List::List(int* i, List* n){//initialize i and set next node
  item = i;
  next = n;
  lower_level = NULL;
}

List::~List(){
  //dont need to free anything cause we are taking things from stack
}

void List::testPrint(){
  cout << *item << " ";
}

//////////////////////////// listHeader
listHeader::listHeader(){
  start = NULL;
  pl =0;
}

listHeader::~listHeader(){
  List* temp = start;
  List* tmp = NULL;
  while(temp != NULL){
    tmp = temp->getNext();
    delete temp;
    temp= tmp;
  }
}

List* listHeader::insertAtStart(List* i){
  List* new_item = new List(i, start);
  start = new_item;
  pl++;
  return new_item;
}

List* listHeader::searchItem(int i){
  List* temp = start;
  if(temp == NULL){
    return NULL;
  }
  if(temp->getItem() == i){
    while(temp->getLowerLevel() != NULL){
      temp= temp->getLowerLevel();
    }
    return temp;//found
  }else if(temp->getItem() > i){
    return temp;//cant found this from this level
  }
  if(temp->getNext() == NULL){
    if(temp->getItem() < i){
      while(temp->getNext() == NULL){
        temp = temp->getLowerLevel();
      }
    }
  }

  while(temp->getNext() != NULL){
    if(temp->getNext()->getItem() == i){
      temp = temp->getNext();
      while(temp->getLowerLevel() != NULL){
        temp = temp->getLowerLevel();
      }
      return temp;//found
    }
    if(temp->getNext()->getItem() > i){
      if(temp->getLowerLevel() == NULL){
        return NULL;//dosent exist
      }
      temp = temp->getLowerLevel();
    }else if(temp->getNext()->getItem() < i){
      temp= temp->getNext();
      while(temp->getNext() == NULL){
        if(temp->getLowerLevel() == NULL){
          return NULL;//dosent exist
        }
        temp =temp->getLowerLevel();
      }
    }
  }
  cout << "listheader::searchItem gone here im illegal" << endl; //TODO: remove this
  return NULL;
}

List* listHeader::insertItem(int* i, int top_lvl){
  List** level_array = new List*[3];//TODO: set this as max_lvl
  int lvl_counter=0;
  List* temp = start;
  if(temp == NULL){
    List* new_node = new List(i, start);
    start = new_node;
    pl++;
    delete[] level_array;
    return new_node;
  }
  if(temp->getItem() == *i){
    while(temp->getLowerLevel() != NULL){
      temp= temp->getLowerLevel();
    }
    delete[] level_array;
    return NULL;//found
  }else if(temp->getItem() > *i){
    if(temp->getLowerLevel() == NULL && temp->getItem() > *i){//case this is needs to be the first node of last layer
      List* new_node = new List(i, start);
      start = new_node;
      pl++;
      delete[] level_array;
      return new_node;
    }

    delete[] level_array;
    return temp;//cant found this from this level
  }
  if(temp->getNext() == NULL){
    if(temp->getItem() < *i){
      while(temp->getNext() == NULL){
        if(temp->getLowerLevel() == NULL){//case we are in lowest level and the item needs to be in the end
          List* new_node = new List(i, NULL);
          temp->setNext(new_node);
          {
            while(lvl_counter> 0 && top_lvl>0){
              lvl_counter--;
              List* tmp = new List(new_node, level_array[lvl_counter]->getNext());
              level_array[lvl_counter]->setNext(tmp);
              new_node = tmp;
              top_lvl--;
            }
          }
          pl++;
          delete[] level_array;
          return new_node;
        }
        level_array[lvl_counter] = temp;
        lvl_counter++;
        temp = temp->getLowerLevel();
      }
    }
  }

  while(temp->getNext() != NULL){
    if(temp->getNext()->getItem() == *i){
      temp = temp->getNext();
      while(temp->getLowerLevel() != NULL){
        temp = temp->getLowerLevel();
      }
      delete[] level_array;
      return NULL;//found
    }
    if(temp->getNext()->getItem() > *i){
      if(temp->getLowerLevel() == NULL){
        //dosent exist
        List* new_node = new List(i, temp->getNext());
        temp->setNext(new_node);
        {
          while(lvl_counter> 0 && top_lvl > 0){
            lvl_counter--;
            List* tmp = new List(new_node, level_array[lvl_counter]->getNext());
            level_array[lvl_counter]->setNext(tmp);
            new_node = tmp;
            top_lvl--;
          }
        }
        pl++;
        delete[] level_array;
        return new_node;
      }
      level_array[lvl_counter] = temp;
      lvl_counter++;
      temp = temp->getLowerLevel();
    }else if(temp->getNext()->getItem() < *i){
      temp= temp->getNext();
      while(temp->getNext() == NULL){
        if(temp->getLowerLevel() == NULL){
          //dosent exist, case: last item in list.
          List* new_node = new List(i);
          temp->setNext(new_node);
          {
            while(lvl_counter> 0 && top_lvl>0){
              lvl_counter--;
              List* tmp = new List(new_node, level_array[lvl_counter]->getNext());
              level_array[lvl_counter]->setNext(tmp);
              new_node = tmp;
              top_lvl--;
            }
          }
          pl++;
          delete[] level_array;
          return new_node;
        }
        level_array[lvl_counter] = temp;
        lvl_counter++;
        temp =temp->getLowerLevel();
      }
    }
  }
  cout << "listheader::insertItem gone here im illegal" << endl; //TODO: remove this
  return NULL;
}

void listHeader::testPrint(){
  List* temp = start;
  while(temp != NULL){
    temp->testPrint();
    temp = temp->getNext();
  }
}

//////////////////////////////////////// skipNode
skipNode::skipNode(){
  item= new listHeader();
  next= NULL;
  prev= NULL;
}

List* skipNode::insertAtStart(List* i){
  return item->insertAtStart(i);
}

skipNode::~skipNode(){
  delete item;
}

void skipNode::testPrint(){
  item->testPrint();
}

///////////////////////////////////// skipHeader
skipHeader::skipHeader(){
  skipNode* temp = new skipNode();
  start = temp;
  end = temp;
  lvlnum = 1;
  max_lvl = MAXIMUM; //TODO might need to change here something
  for(int i=0;i<max_lvl;i++){//create all the layers
    addLayer();
  }
}

skipHeader::~skipHeader(){
  skipNode* temp = start;
  skipNode* tmp = NULL;
  while(temp != NULL){
    tmp = temp->getNext();
    delete temp;
    temp = tmp;
  }
}

void skipHeader::addLayer(){
  skipNode* temp = new skipNode();
  temp->setPrev(end);
  end->setNext(temp);
  end = end->getNext();
}

bool skipHeader::searchItem(int i){
  skipNode* temp = end;
  while(temp->getItem()->getPl() == 0){//case no items in lists
    temp = temp->getPrev();
    if(temp == NULL){//case no items in skip list
      return false;
    }
  }
  List* tmp = temp->getItem()->searchItem(i);//start searching from the first list with items
  if(tmp != NULL){//if it found something
      while(tmp->getItem() > i && temp->getPrev() != NULL){//if tmp->item > i that means that we need to start searching from lower level
        temp = temp->getPrev();
        tmp = temp->getItem()->searchItem(i);//search lower level
        if(tmp == NULL){//item not found
          return false;
        }
      }
      if(temp->getPrev() == NULL && tmp != NULL && tmp->getItem() != i){//case every first item of each level is > i
        return false;
      }
      return true;
  }else{
    return false;
  }
}

bool skipHeader::insertItem(int* i){
  // int top_lvl = rand() % max_lvl + 0;
  int top_lvl =0;//calculate in how many levels the item will go to
  {
    int f=1;
    while(f && top_lvl < max_lvl){
      if((rand() % 2 + 1) == 1){
        top_lvl++;
      }else{
        f=0;
      }
    }

  }
  // cout << "top level: " << top_lvl << endl; //TODO: clean
  int skiped_layers =0;//used to see how many layers was skiped because first item is > i
  skipNode* temp = end;//use of dual linked list, start == list with all the items. with that in mind, we start our search with the list with the less amount of items
  while(temp->getItem()->getPl() == 0){//same with search
    if(temp->getPrev() == NULL){//if for example list with all the items is empty, need to add it there
      break;
    }
    temp = temp->getPrev();
    skiped_layers++;
  }
  List* tmp = temp->getItem()->insertItem(i, top_lvl);
  bool final;
  bool final_tmp= false;
  if(tmp != NULL){
    if(tmp->getItem() == *i){//case inserted
      final= true;
    }
    while(tmp->getItem() > *i && temp->getPrev() != NULL){
      skiped_layers++;
      temp = temp->getPrev();
      tmp = temp->getItem()->insertItem(i, top_lvl);
      if(tmp == NULL){//item couldnt be inserted, already exists
        final = false;
        final_tmp = true;
        break;
      }
    }
    if(!final_tmp){
      final = true;
    }
  }else{//item couldnt be inserted, already exists
    final = false;
  }
  if(final){//insert the item to every level that it needs to
    int t= max_lvl-skiped_layers;
    t= top_lvl-t;
    while(t>0 && temp->getNext() != NULL){
      temp = temp->getNext();
      tmp = temp->insertAtStart(tmp);//the first item of every skiped list is >i so insert i as first
      t--;
    }
    return true;
  }else{
    return false;
  }
}

void skipHeader::testPrint(){
  skipNode* temp = end;
  while(temp != NULL){
    temp->getItem()->testPrint();
    temp = temp->getPrev();
    cout << endl;
  }
}


//
