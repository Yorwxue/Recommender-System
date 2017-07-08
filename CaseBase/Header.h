#include<iostream>
#include<time.h>

using namespace std;

template<class T>
class List;
class Item;

//data_base.cpp
void new_Case(List<Item>* new_case);
void new_item(List<Item>* Case, Item* new_item);

//similarity.cpp
float sim_cast(List<Item>* case_A, List<Item>* case_B);