#include <iostream>
#include "skipList.hpp"
#include <math.h>
using namespace std;


List::List(int* i){//only copy i
  item = i;
  lower_level = NULL;
  next = NULL;
}

List::List(List* i){//copy i and set lower_level
  item = i->item;
  lower_level = i;
  next = NULL;
}

List::List(List* i, List* n){//copy
  item = i->item;
  next = n;
  lower_level= i;
}

List::List(int* i, List* n){
  item = i;
  next = n;
  lower_level = NULL;
}

List::~List(){
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
    tmp = temp->next;
    delete temp;
    temp= tmp;
  }
}

void listHeader::insertItemTemp(int* i){
  if(start == NULL){
    List *new_item = new List(i);
    start = new_item;
    pl++;
  }else if(*(start->item) > *i){
    List *new_item = new List(i, start);
    start = new_item;
    pl++;
  }else{
    List* temp = start;
    while(temp->next != NULL){
      if(*i < *(temp->next->item)){
        List *new_item = new List(i, temp->next);
        temp->next = new_item;
        pl++;
        return;
      }
      temp = temp->next;
    }
    List *new_item = new List(i);
    temp->next = new_item;
    pl++;
  }
}

void listHeader::insertItem(List* i){
  if(start == NULL){
    List *new_item = new List(i);
    start = new_item;
    pl++;
  }else if(*(start->item) > *(i->item)){
    List *new_item = new List(i, start);
    start = new_item;
    pl++;
  }else{
    List* temp = start;
    while(temp->next != NULL){
      if(*(i->item) < *(temp->next->item)){
        List *new_item = new List(i, temp->next);
        temp->next = new_item;
        pl++;
        return;
      }
      temp = temp->next;
    }
    List *new_item = new List(i);
    temp->next = new_item;
    pl++;
  }
}

List* listHeader::searchItem(int i){
  List* temp = start;
  if(*(temp->item) == i){
    while(temp->lower_level != NULL){
      temp= temp->lower_level;
    }
    return temp;//found
  }else if(*(temp->item) > i){
    return temp;//cant found this from this level
  }
  if(temp->next == NULL){
    if(*(temp->item) < i){
      while(temp->next == NULL){
        temp = temp->lower_level;
      }
    }
  }

  while(temp->next != NULL){
    if(*(temp->next->item) == i){
      temp = temp->next;
      while(temp->lower_level != NULL){
        temp = temp->lower_level;
      }
      return temp;//found
    }
    if(*(temp->next->item) > i){
      if(temp->lower_level == NULL){
        return NULL;//dosent exist
      }
      temp = temp->lower_level;
      continue;
    }
    if(*(temp->next->item) < i){
      temp= temp->next;
      while(temp->next == NULL){
        if(temp->lower_level == NULL){
          return NULL;//dosent exist
        }
        temp =temp->lower_level;
      }
    }
  }
}

List* listHeader::insertItem(int* i, int top_lvl){
  List** level_array = new List*[3];//TODO: set this as max_lvl
  int lvl_counter=0;
  List* temp = start;
  if(*(temp->item) == *i){
    while(temp->lower_level != NULL){
      temp= temp->lower_level;
    }
    return NULL;//found
  }else if(*(temp->item) > *i){
    return temp;//cant found this from this level
  }
  if(temp->next == NULL){
    if(*(temp->item) < *i){
      while(temp->next == NULL){
        temp = temp->lower_level;
      }
    }
  }

  while(temp->next != NULL){
    if(*(temp->next->item) == *i){
      temp = temp->next;
      while(temp->lower_level != NULL){
        temp = temp->lower_level;
      }
      return NULL;//found
    }
    if(*(temp->next->item) > *i){
      if(temp->lower_level == NULL){
        // return NULL;//dosent exist
        List* new_node = new List(i, temp->next);
        temp->next = new_node;
        {
          // cout << "here1" << endl;
          while(lvl_counter> 0 && top_lvl > 0){
            lvl_counter--;
            List* tmp = new List(new_node, level_array[lvl_counter]->next);
            // cout << "test" << endl;
            level_array[lvl_counter]->next = tmp;
            top_lvl--;
          }
        }
        return new_node;
      }
      level_array[lvl_counter] = temp;
      lvl_counter++;
      temp = temp->lower_level;
      continue;
    }
    if(*(temp->next->item) < *i){
      temp= temp->next;
      while(temp->next == NULL){
        if(temp->lower_level == NULL){
          // return NULL;//dosent exist, case: last item in list.
          List* new_node = new List(i);
          temp->next = new_node;
          {
            // cout << "here2" << endl;
            while(lvl_counter> 0 && top_lvl>0){
              lvl_counter--;
              List* tmp = new List(new_node, level_array[lvl_counter]->next);
              level_array[lvl_counter]->next = tmp;
              top_lvl--;
            }
          }
          return new_node;
        }
        level_array[lvl_counter] = temp;
        lvl_counter++;
        temp =temp->lower_level;
      }
    }
  }
}

void listHeader::testPrint(){
  List* temp = start;
  while(temp != NULL){
    temp->testPrint();
    temp = temp->next;
  }
}

listHeader* listHeader::forNextLayer(){
  listHeader* to_return = new listHeader();
  List* temp = start;
  while(temp != NULL){
    if((random() % 100 + 0) > 35){//might also need to make it more flip a coin like
      to_return->insertItem(temp);
    }
    temp = temp->next;
  }
  return to_return;
}


//////////////////////////////////////// skipNode
skipNode::skipNode(listHeader* i){
  item = i;
  next = NULL;
  prev= NULL;
}

skipNode::skipNode(){
  item =NULL;
  next= NULL;
}

skipNode::skipNode(listHeader* i, skipNode* n){
  item = i;
  next = n;
}

skipNode::~skipNode(){
  delete item;
}

void skipNode::testPrint(){
  item->testPrint();
}

///////////////////////////////////// skipHeader
skipHeader::skipHeader(listHeader* i){
  skipNode* temp = new skipNode(i);
  start = temp;
  end = temp;
  lvlnum = 1;
  max_lvl = log(i->pl)+1; //TODO might need to change here something
  // max_lvl = 1;// TODO fix this
  for(int i=0;i<max_lvl;i++){
    addLayer();
  }

  {
    skipNode* temp= start;
    while(temp->next != NULL){
      temp->next->item = temp->item->forNextLayer();
      temp = temp->next;
    }
  }
}

skipHeader::~skipHeader(){
  skipNode* temp = start;
  skipNode* tmp = NULL;
  while(temp != NULL){
    tmp = temp->next;
    delete temp;
    temp = tmp;
  }
}

void skipHeader::addLayer(){
  skipNode* temp = new skipNode();
  temp->prev= end;
  end->next = temp;
  end = end->next;
}

bool skipHeader::searchItem(int i){
  skipNode* temp = end;
  while(temp->item->pl == 0){
    temp = temp->prev;
  }
  List* tmp = temp->item->searchItem(i);
  if(tmp != NULL){ //TODO: re-check the not found from if != NULL
      while(*(tmp->item) > i){
        temp = temp->prev;
        tmp = temp->item->searchItem(i);
      }
      cout << "FOUND" << endl;
      return true;
  }else{
    cout << "NOT FOUND" << endl;
    return false;
  }
}


bool skipHeader::insertItem(int* i){
  int top_lvl = rand() % max_lvl + 0;
  skipNode* temp = end;
  while(temp->item->pl == 0){
    temp = temp->prev;
  }
  List* tmp = temp->item->insertItem(i, top_lvl);
  bool final;
  bool final_tmp= false;
  if(tmp != NULL){ //TODO: re-check the not found from if != NULL
    if(*(tmp->item) == *i){//case inserted
      // return true;
      final= true;
    }
    while(*(tmp->item) > *i){//case first first's level is >i
      temp = temp->prev;
      tmp = temp->item->insertItem(i, top_lvl);
      if(tmp == NULL){
        // return false;
        final = false;
        final_tmp = true;
        break;
      }
    }
    // return true;
    if(!final_tmp){
      final = true;
    }
  }else{
    // return false;
    final = false;
  }
  if(final){

    // int to_levels= random() % max_lvl + 0;
    // to_levels = max_lvl - to_levels;
    // skipNode* temp= end;
    // while(to_levels >0){
    //   temp = temp->prev;
    //   to_levels--;
    // }
    //
    // while(temp != NULL){
    //
    // }

    return true;
  }else{
    return false;
  }
}

void skipHeader::testPrint(){
  skipNode* temp = end;
  while(temp != NULL){
    temp->item->testPrint();
    temp = temp->prev;
    cout << endl;
  }
}


//
