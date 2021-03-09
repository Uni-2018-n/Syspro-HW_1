#include <iostream>
#include "skipList.hpp"
#include <math.h>
using namespace std;

//////////////////////////// SkiplistNode
SkiplistNode::SkiplistNode(int* i, citizenRecord* c, string* dv){//initialize i
  item = i;
  citizen = c;
  date_vaccinated = dv;
  lower_level = NULL;
  next = NULL;
  prev = NULL;
}

SkiplistNode::SkiplistNode(SkiplistNode* i){//copy i and set lower_level
  item = i->item;
  date_vaccinated = NULL;
  citizen = NULL;
  lower_level = i;
  next = NULL;
  prev = NULL;
}

SkiplistNode::SkiplistNode(SkiplistNode* i, SkiplistNode* n){//copy i and set it to lower lever also add next node
  item = i->item;
  date_vaccinated = NULL;
  citizen = NULL;
  next = n;
  prev = NULL;
  lower_level= i;
}

SkiplistNode::SkiplistNode(int* i, citizenRecord* c, string* dv, SkiplistNode* n){//initialize i and set next node
  item = i;
  date_vaccinated = dv;
  citizen = c;
  next = n;
  prev = NULL;
  lower_level = NULL;
}

SkiplistNode::~SkiplistNode(){
  if(date_vaccinated != NULL){
    delete date_vaccinated;
  }
}

void SkiplistNode::print(){
  citizen->print();
}

void SkiplistNode::testPrint(){
  cout << *item << "(";
  if(prev != NULL){
    cout << *(prev->item);
  }
  cout << ") -> ";
}

//////////////////////////// SkiplistHeader
SkiplistHeader::SkiplistHeader(){
  start = NULL;
}

SkiplistHeader::~SkiplistHeader(){
  SkiplistNode* temp = start;
  SkiplistNode* tmp = NULL;
  while(temp != NULL){
    tmp = temp->getNext();
    delete temp;
    temp= tmp;
  }
}

SkiplistNode* SkiplistHeader::insertAtStart(SkiplistNode* i){
  SkiplistNode* new_item = new SkiplistNode(i, start);
  if(start != NULL){
    start->setPrev(new_item);
    new_item->setNext(start);
  }
  start = new_item;
  return new_item;
}

SkiplistNode* SkiplistHeader::searchItem(int i){
  SkiplistNode* temp = start;
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
        if(temp == NULL){
          return NULL;
        }
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
  cout << "SkiplistHeader::searchItem gone here im illegal" << endl; //TODO: remove this
  return NULL;
}

SkiplistNode* SkiplistHeader::insertItem(int* i, citizenRecord* c, string* dv, int top_lvl){
  SkiplistNode** level_array = new SkiplistNode*[MAXIMUM];//TODO: set this as max_lvl
  int lvl_counter=0;
  SkiplistNode* temp = start;
  if(temp == NULL){
    SkiplistNode* new_node = new SkiplistNode(i, c, dv, start);
    start = new_node;
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
      SkiplistNode* new_node = new SkiplistNode(i, c, dv, start);
      start = new_node;
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
          SkiplistNode* new_node = new SkiplistNode(i, c, NULL);
          temp->setNext(new_node);
          new_node->setPrev(temp);
          {
            while(lvl_counter> 0 && top_lvl>0){
              lvl_counter--;
              SkiplistNode* tmp = new SkiplistNode(new_node, level_array[lvl_counter]->getNext());
              if(level_array[lvl_counter]->getNext()!= NULL){
                level_array[lvl_counter]->getNext()->setPrev(tmp);
              }
              level_array[lvl_counter]->setNext(tmp);
              tmp->setPrev(level_array[lvl_counter]);
              new_node = tmp;
              top_lvl--;
            }
          }
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
        SkiplistNode* new_node = new SkiplistNode(i, c, dv, temp->getNext());
        if(temp->getNext() != NULL){
          temp->getNext()->setPrev(new_node);
        }
        temp->setNext(new_node);
        new_node->setPrev(temp);
        {
          while(lvl_counter> 0 && top_lvl > 0){
            lvl_counter--;
            SkiplistNode* tmp = new SkiplistNode(new_node, level_array[lvl_counter]->getNext());
            if(level_array[lvl_counter]->getNext()!= NULL){
              level_array[lvl_counter]->getNext()->setPrev(tmp);
            }
            level_array[lvl_counter]->setNext(tmp);
            tmp->setPrev(level_array[lvl_counter]);
            new_node = tmp;
            top_lvl--;
          }
        }
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
          //dosent exist, case: last item in SkiplistNode.
          SkiplistNode* new_node = new SkiplistNode(i, c, dv);
          temp->setNext(new_node);
          new_node->setPrev(temp);
          {
            while(lvl_counter> 0 && top_lvl>0){
              lvl_counter--;
              SkiplistNode* tmp = new SkiplistNode(new_node, level_array[lvl_counter]->getNext());
              if(level_array[lvl_counter]->getNext()!= NULL){
                level_array[lvl_counter]->getNext()->setPrev(tmp);
              }
              level_array[lvl_counter]->setNext(tmp);
              tmp->setPrev(level_array[lvl_counter]);
              new_node = tmp;
              top_lvl--;
            }
          }
          delete[] level_array;
          return new_node;
        }
        level_array[lvl_counter] = temp;
        lvl_counter++;
        temp =temp->getLowerLevel();
      }
    }
  }
  cout << "SkiplistHeader::insertItem gone here im illegal" << endl; //TODO: remove this
  return NULL;
}

SkiplistNode* SkiplistHeader::deleteItem(int i){
  SkiplistNode* temp = start;
  if(temp == NULL){
    return NULL;
  }
  if(temp->getItem() == i){
    while(temp->getLowerLevel() != NULL){
      if(temp->getPrev() != NULL){
        temp->getPrev()->setNext(temp->getNext());
        if(temp->getNext() != NULL){
          temp->getNext()->setPrev(temp->getPrev());
        }
        SkiplistNode* tmp = temp;
        temp = temp->getLowerLevel();
        if(temp != NULL){
          delete tmp;
        }
        continue;
      }
      temp= temp->getLowerLevel();
    }
    if(temp->getPrev() != NULL){
      temp->getPrev()->setNext(temp->getNext());
      if(temp->getNext() != NULL){
        temp->getNext()->setPrev(temp->getPrev());
      }
    }
    return temp;//found
  }else if(temp->getItem() > i){
    return temp;//cant found this from this level
  }
  if(temp->getNext() == NULL){
    if(temp->getItem() < i){
      while(temp->getNext() == NULL){
        temp = temp->getLowerLevel();
        if(temp == NULL){
          return NULL;
        }
      }
    }
  }

  while(temp->getNext() != NULL){
    if(temp->getNext()->getItem() == i){
      temp = temp->getNext();
      while(temp->getLowerLevel() != NULL){
        SkiplistNode* tmp = temp;
        if(temp->getPrev() != NULL){
          temp->getPrev()->setNext(temp->getNext());
        }
        if(temp->getNext() != NULL){
          temp->getNext()->setPrev(temp->getPrev());
        }
        temp = temp->getLowerLevel();
        delete tmp;
      }
      if(temp->getPrev() != NULL){
        temp->getPrev()->setNext(temp->getNext());
      }
      if(temp->getNext() != NULL){
        temp->getNext()->setPrev(temp->getPrev());
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
  cout << "SkiplistHeader::searchItem gone here im illegal" << endl; //TODO: remove this
  return NULL;
}

void SkiplistHeader::print(){
  SkiplistNode* temp = start;
  while(temp != NULL){
    temp->print();
    temp = temp->getNext();
  }
}

void SkiplistHeader::testPrint(){
  SkiplistNode* temp = start;
  while(temp != NULL){
    temp->testPrint();
    temp = temp->getNext();
  }
}

//////////////////////////////////////// skipNode
skipNode::skipNode(){
  item= new SkiplistHeader();
  next= NULL;
  prev= NULL;
}

SkiplistNode* skipNode::insertAtStart(SkiplistNode* i){
  return item->insertAtStart(i);
}

skipNode::~skipNode(){
  delete item;
}

void skipNode::print(){
  item->print();
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
  while(temp->getItem()->getFirst() == NULL){//case no items in SkiplistNodes
    temp = temp->getPrev();
    if(temp == NULL){//case no items in skip SkiplistNode
      return false;
    }
  }
  SkiplistNode* tmp = temp->getItem()->searchItem(i);//start searching from the first SkiplistNode with items
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

bool skipHeader::insertItem(int* i, citizenRecord* c, string* dv){
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
  skipNode* temp = end;//use of dual linked SkiplistNode, start == SkiplistNode with all the items. with that in mind, we start our search with the SkiplistNode with the less amount of items
  while(temp->getItem()->getFirst() == NULL){//same with search
    if(temp->getPrev() == NULL){//if for example SkiplistNode with all the items is empty, need to add it there
      break;
    }
    temp = temp->getPrev();
    skiped_layers++;
  }
  SkiplistNode* tmp = temp->getItem()->insertItem(i, c, dv, top_lvl);
  bool final;
  bool final_tmp= false;
  if(tmp != NULL){
    if(tmp->getItem() == *i){//case inserted
      final= true;
    }
    while(tmp->getItem() > *i && temp->getPrev() != NULL){
      skiped_layers++;
      temp = temp->getPrev();
      tmp = temp->getItem()->insertItem(i, c, dv, top_lvl);
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
      tmp = temp->insertAtStart(tmp);//the first item of every skiped SkiplistNode is >i so insert i as first
      t--;
    }
    return true;
  }else{
    delete dv;
    return false;
  }
}

SkiplistNode* skipHeader::deleteItem(int i){
  skipNode* temp = end;
  while(temp->getItem()->getFirst() == NULL){//case no items in SkiplistNodes
    temp = temp->getPrev();
    if(temp == NULL){//case no items in skip SkiplistNode
      return NULL;
    }
  }
  SkiplistNode* tmp = temp->getItem()->deleteItem(i);//start searching from the first SkiplistNode with items
  if(tmp != NULL){//if it found something
      while(tmp->getItem() > i && temp->getPrev() != NULL){//if tmp->item > i that means that we need to start searching from lower level
        temp = temp->getPrev();
        tmp = temp->getItem()->deleteItem(i);//search lower level
        if(tmp == NULL){//item not found
          return NULL;
        }
      }
      if(temp->getPrev() == NULL && tmp != NULL && tmp->getItem() != i){//case every first item of each level is > i
        return NULL;
      }

      if(tmp != NULL){
        skipNode* temp = end;
        while(temp != NULL){
          if(temp->getItem()->getFirst() != NULL){
            if(temp->getItem()->getFirst()->getItem() == i){
              temp->getItem()->removeFirst();
            }
          }
          temp = temp->getPrev();
        }
      }

      return tmp;
  }else{
    return NULL;
  }
}


void skipHeader::print(){
  start->print();
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
