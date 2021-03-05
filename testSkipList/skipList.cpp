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
    tmp = temp->next;
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
    }else if(*(temp->next->item) < i){
      temp= temp->next;
      while(temp->next == NULL){
        if(temp->lower_level == NULL){
          return NULL;//dosent exist
        }
        temp =temp->lower_level;
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
  if(*(temp->item) == *i){
    while(temp->lower_level != NULL){
      temp= temp->lower_level;
    }
    delete[] level_array;
    return NULL;//found
  }else if(*(temp->item) > *i){
    if(temp->lower_level == NULL && *(temp->item) > *i){//case this is needs to be the first node of last layer
      List* new_node = new List(i, start);
      start = new_node;
      pl++;
      delete[] level_array;
      return new_node;
    }

    delete[] level_array;
    return temp;//cant found this from this level
  }
  if(temp->next == NULL){
    if(*(temp->item) < *i){
      while(temp->next == NULL){
        if(temp->lower_level == NULL){//case we are in lowest level and the item needs to be in the end
          List* new_node = new List(i, NULL);
          temp->next= new_node;
          {
            while(lvl_counter> 0 && top_lvl>0){
              lvl_counter--;
              List* tmp = new List(new_node, level_array[lvl_counter]->next);
              level_array[lvl_counter]->next = tmp;
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
      delete[] level_array;
      return NULL;//found
    }
    if(*(temp->next->item) > *i){
      if(temp->lower_level == NULL){
        //dosent exist
        List* new_node = new List(i, temp->next);
        temp->next = new_node;
        {
          while(lvl_counter> 0 && top_lvl > 0){
            lvl_counter--;
            List* tmp = new List(new_node, level_array[lvl_counter]->next);
            level_array[lvl_counter]->next = tmp;
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
      temp = temp->lower_level;
    }else if(*(temp->next->item) < *i){
      temp= temp->next;
      while(temp->next == NULL){
        if(temp->lower_level == NULL){
          //dosent exist, case: last item in list.
          List* new_node = new List(i);
          temp->next = new_node;
          {
            while(lvl_counter> 0 && top_lvl>0){
              lvl_counter--;
              List* tmp = new List(new_node, level_array[lvl_counter]->next);
              level_array[lvl_counter]->next = tmp;
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
        temp =temp->lower_level;
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
    temp = temp->next;
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
  while(temp->item->pl == 0){//case no items in lists
    temp = temp->prev;
    if(temp == NULL){//case no items in skip list
      return false;
    }
  }
  List* tmp = temp->item->searchItem(i);//start searching from the first list with items
  if(tmp != NULL){//if it found something
      while(*(tmp->item) > i && temp->prev != NULL){//if tmp->item > i that means that we need to start searching from lower level
        temp = temp->prev;
        tmp = temp->item->searchItem(i);//search lower level
        if(tmp == NULL){//item not found
          return false;
        }
      }
      if(temp->prev == NULL && tmp != NULL && *(tmp->item) != i){//case every first item of each level is > i
        return false;
      }
      return true;
  }else{
    return false;
  }
}

bool skipHeader::insertItem(int* i){
  int top_lvl = rand() % max_lvl + 0;//calculate in how many levels the item will go to
  // cout << "top level: " << top_lvl << endl; //TODO: clean
  int skiped_layers =0;//used to see how many layers was skiped because first item is > i
  skipNode* temp = end;//use of dual linked list, start == list with all the items. with that in mind, we start our search with the list with the less amount of items
  while(temp->item->pl == 0){//same with search
    if(temp->prev == NULL){//if for example list with all the items is empty, need to add it there
      break;
    }
    temp = temp->prev;
    skiped_layers++;
  }
  List* tmp = temp->item->insertItem(i, top_lvl);
  bool final;
  bool final_tmp= false;
  if(tmp != NULL){
    if(*(tmp->item) == *i){//case inserted
      final= true;
    }
    while(*(tmp->item) > *i && temp->prev != NULL){
      skiped_layers++;
      temp = temp->prev;
      tmp = temp->item->insertItem(i, top_lvl);
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
    while(t>0 && temp->next != NULL){
      temp = temp->next;
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
    temp->item->testPrint();
    temp = temp->prev;
    cout << endl;
  }
}


//
