/*Author: Eric Gustin
  Assignment: CPSC223-01 HW06
  Description: This is the linked_list_collection.h. It is an extension to the Linked List
  implementation in HW4 by adding sorting algoirthms Insertion sort, Merge Sort, and Quick Sort.
  Merge Sort and Quick Sort are recursive formulas.
*/

#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"



template<typename K, typename V>
class LinkedListCollection : public Collection <K,V>
{
public:

 // create an empty linked list
 LinkedListCollection();

 // copy a linked list
 LinkedListCollection(const LinkedListCollection <K,V>& rhs);

 // assign a linked list
 LinkedListCollection <K,V>& operator=(const LinkedListCollection <K,V>& rhs);

 // delete a linked list
 ~LinkedListCollection();

 // insert a key - value pair into the collection
 void insert(const K& key, const V& val);

 // remove a key - value pair from the collection
 void remove(const K& key);

 // find the value associated with the key
 bool find(const K& key, V& val) const;

 // find the keys associated with the range
 void find(const K& k1, const K& k2, std::vector<K>& keys) const;

 // return all keys in the collection
 void keys(std::vector<K>& keys) const;

 // return collection keys in sorted order
 void sort(std::vector<K>& keys) const;

 // return the number of keys in collection
 int size() const;

 // in place sorting
 void insertion_sort();
 void merge_sort();
 void quick_sort();

private :

 // linked list node structure
 struct Node{
 K key;
 V value;
 Node* next;
 };
 Node* head;
 Node* tail;

 int length;

 // helper to delete linked list
 void make_empty();

 // merge sort helper ( see course notes for details )
 Node* merge_sort(Node* left, int len);

 // quick sort helper ( see course notes for details )
 Node* quick_sort(Node* start, int len);

 // helper function for destructor & assignment operator
 void make_empty(LinkedListCollection<K,V>& list);
};

template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection()
: head(nullptr), tail(nullptr), length(0)
{}

template <typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection(const LinkedListCollection<K,V>& rhs)
: head(nullptr), tail(nullptr), length(0)
{
 *this = rhs;
}

template <typename K, typename V>
LinkedListCollection<K,V>& LinkedListCollection<K,V>::operator=(const LinkedListCollection<K,V>& rhs)
{
 // ensure that an object is not being assigned to itself
 if (this != &rhs) {
  // empty contents of this object
  make_empty(*this);
  // copy contents into this object
  Node* curr = rhs.head;
  while (curr != nullptr) {
   insert(curr->key, curr->value);
   curr = curr->next;
  }
  delete curr;
  curr = nullptr;
 }
 return *this;
}

template <typename K, typename V>
LinkedListCollection<K,V>::~LinkedListCollection()
{
 make_empty(*this);
}

template <typename K, typename V>
void LinkedListCollection<K,V>::make_empty(LinkedListCollection<K,V>& list) {
 Node* curr = new Node;
 curr = head;
 while (curr != nullptr) {
  head = head->next;
  delete curr;
  curr = head;
  --length;
 }
 head = nullptr;
 tail = nullptr;
}

template <typename K, typename V>
void LinkedListCollection<K,V>::insert(const K& key, const V& val) {
 Node* curr = new Node;
 // edge cases
 if (size() == 0)
  head = curr;

 if (size() > 0)
  tail->next = curr;

 tail = curr;
 // assign values to the current node's members variables
 curr->key = key;
 curr->value = val;
 curr->next = nullptr;

 ++length;
}

template <typename K, typename V>
void LinkedListCollection<K,V>::remove(const K& key){
 if (size() > 0) {
   Node* prev = head;
   Node* curr = head->next;
   // edge case where desired key is contained in head
   if (head->key == key) {
    head = head->next;
    delete prev;
    prev = nullptr;
    --length;
   }
   else {
    while (curr != nullptr) {
     if (curr->key == key) {
      //edge case where desired key is at end of list
      if (curr->next == nullptr)
       tail = prev;
      prev->next = curr->next;
      delete curr;
      curr = nullptr;
      curr = nullptr;
      --length;
      break;
     }
     prev = curr;
     curr = curr->next;
    }
   }
  }
 }

template <typename K, typename V>
bool LinkedListCollection<K,V>::find(const K& key, V& val) const
{
 Node* curr = head;
 // iterate through linked list until desired key is found or end of list is reached
 while (curr != nullptr) {
  if (curr->key == key) {
   val = curr->value;
   return true;
  }
  curr = curr->next;
 }
 return false;
}

template <typename K, typename V>
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, std::vector<K>& keys) const
{
 //for-loop variable to keep track of current index of keys vector
 unsigned int curr_index = 0;
 // set keys vector equal to kv_list
 this->keys(keys);
 //iterate through keys and remove pairs that dont meet requirements
 //curr_index is not incremented if an element is erased since all
 //elements coming after will be moved forward 1 index.
 for (int i = 0; i < size(); ++i) {
  if ((keys[curr_index] < k1) || (keys[curr_index] > k2)) {
   keys.erase(keys.begin()+curr_index);
  }
  else
   ++curr_index;
 }
}

template <typename K, typename V>
void LinkedListCollection<K,V>::keys(std::vector<K>& keys) const
{
 // inserts keys of the list into a vector
 Node* cur = head;
 while (cur != nullptr) {
  keys.push_back(cur->key);
  cur = cur->next;
 }
}

template <typename K, typename V>
void LinkedListCollection<K,V>::sort(std::vector<K>& keys) const
{
 Node* ptr = head;
 while(ptr != nullptr) {
  keys.push_back(ptr->key);
  ptr = ptr->next;
 }
 std::sort(keys.begin(), keys.end());
}

template <typename K, typename V>
int LinkedListCollection<K,V>::size() const
{
 return length;
}

template<typename K, typename V>
void LinkedListCollection<K,V>::insertion_sort()
{
 if (size() <= 1)
  return; 
 Node* sorted_head = head;
 Node* sorted_tail = head;
 Node* curr = head; // keeps track of where the candidate should be moved to
 Node* candidate = head->next; // first item in unsorted region
 Node* temp = head; // keeps track of the node after candidate;
 int sorted_size = 1; // size of the sorted array
 int j = 0;

 // insertion sort algorithm. Stop when the entire list is sorted.
 while (sorted_tail->next != nullptr) {
  j = 0;
  if (candidate->key < curr->key) {
   // move the candidate to the front of the sorted list.
   if (candidate->key <= sorted_head->key) {
    temp = candidate->next;
    candidate->next = sorted_head;
    sorted_head = candidate;
   }
   // move candidate into where it belongs in the sorted list as long as it isnt greater 
   // than the sorted_tail and less than the sorted_head.
   else {
    temp->next = candidate;
    temp = candidate->next;
    candidate->next = curr;
   }
   curr = sorted_head;
   sorted_tail->next = temp;
   candidate = temp;
   temp = sorted_head;
   ++sorted_size;
  }
  else {
   // iterate through the sorted list until candidate's desired spot in the sorted list is found
   while ((candidate->key > curr->key) && (sorted_size > j)) {
    temp = curr;
    curr = curr->next;
    ++j;
   }
   // move the candidate to the end of the sorted list.
   if (j == sorted_size) {
    sorted_tail = candidate;
    candidate = candidate->next;
    curr = sorted_head;
    temp = sorted_head;
    ++sorted_size;
   }
  }
 }

 head = sorted_head;
 tail = sorted_tail;
}

 // helper function
template<typename K, typename V>
typename LinkedListCollection<K,V>::Node*
LinkedListCollection<K,V>::merge_sort(Node* left, int len)
{
 if (len <= 1)
  return left;

 int mid = len / 2;
 Node* right = left;
 // traverse list until the node before the desired "right" is found
 for (int i = 0; i < mid-1; ++i)
  right = right->next;
 // splice the list (note: doesn't have to splice if it's at the end of the list)
 if (right->next != nullptr) {
  Node* temp = right;
  right = right->next;
  temp->next = nullptr; 
  }
 
 // recursive step
 left = merge_sort(left, mid);
 right = merge_sort(right, len - mid);

 // do merging
 Node* curr_small = left; 
 Node* curr_big = right;
 Node* temp_node = curr_small->next; // main purpose is to be a placeholder for curr_small->next

 while ((curr_small != nullptr) && (curr_big != nullptr)) {

  // if the initialization of curr_small and curr_big were incorrect, then it will correct itself here
  if (curr_small->key > curr_big->key) {
   temp_node = curr_small;
   curr_small = curr_big;
   curr_big = temp_node;
  }

  temp_node = curr_small->next;

  // traverse list until curr_small->next is no longer smaller than curr_big. Allows for multiple nodes to be 
  // prepended at a single time since all the nodes that were traversed are already connected. Gets rid of the 
  // need to insert single nodes in between two other nodes.
  while ((curr_small != nullptr) && (curr_small->next != nullptr) && (curr_small->next->key <= curr_big->key))
   curr_small = curr_small->next;
  temp_node = curr_small->next;

  curr_small->next = curr_big; // reattach 
  curr_small = temp_node;
 }

 // assign last node in the list to "tail"
 Node* new_tail = curr_big;
 while ((new_tail != nullptr) && (new_tail->next != nullptr))
  new_tail = new_tail->next;
 tail = new_tail;

 if (left->key > right->key)
  return right;
 return left;
}

template<typename K, typename V>
void LinkedListCollection<K,V>::merge_sort()
{
 if (size() > 0)
  head = merge_sort(head, size());
}

// helper function
template<typename K, typename V>
typename LinkedListCollection<K,V>::Node*
LinkedListCollection<K,V>::quick_sort(Node* start, int len)
{
 // case statements to stop recursion if len <= 2
 if (len == 0)
  return nullptr;
 if (len == 1)
  return start;
 
 int len_left = 0; // keep track of the length of the left side of the list
 int len_right = 0; // keep track of the length of the right side of the list
 Node* left_head = nullptr;
 Node* right_head = nullptr;
 Node* temp = start->next;

 while (temp != nullptr) {

  start->next = temp->next; // use start's next pointer as a placeholder for temp's next address

  // add node to left side list if...
  if (temp->key <= start->key) {
   temp->next = left_head;
   left_head = temp;
   ++len_left;
  }

  // else add node to right side
  else {
   temp->next = right_head;
   right_head = temp;
   ++len_right;
  }

  // continue to traverse through the whole list
  temp = start->next;
 }
 
 // recursive step
 Node* left = quick_sort(left_head, len_left);
 Node* right = quick_sort(right_head, len_right);

 // find the last element in the list so that it can be assigned to "tail"
 Node* max_left = left;
 Node* max_right = right;
 while ((max_left != nullptr) && (max_left->next != nullptr))
  max_left = max_left->next;
 while ((max_right != nullptr) && (max_right->next != nullptr))
  max_right = max_right->next;

 // case: reattach if left of list is empty
 if (len_left == 0) {
  start->next = right;
  if ((len_left == 0) && (len_right == 0))
   tail = start;
  else
   tail = max_right;
  return start;
 }

 // reattach left side of list to the pivot node
 max_left->next = start;
 // case: reattach pivot to right side of list if right side of list isn't empty
 if (len_right > 0)
  start->next = right;
 if (len_right == 0)
  tail = start;
 
 return left;
}

template<typename K, typename V>
void LinkedListCollection<K,V>::quick_sort()
{
 if (size() > 0)
  head = quick_sort(head, size());
}

#endif