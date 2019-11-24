/*Author: Eric Gustin
  Assignment: CPSC223-01 HW10 rbt_collection.h

*/
#ifndef RBT_COLLECTION_H
#define RBT_COLLECTION_H

#include <vector>
#include "collection.h"


template <typename K, typename V>
class RBTCollection : public Collection<K,V>
{
public:

 // create an empty linked list
 RBTCollection();

 // copy a linked list
 RBTCollection(const RBTCollection<K,V>& rhs);

 // assign a linked list
 RBTCollection<K,V>& operator=(const RBTCollection<K,V>& rhs);

 // delete a linked list
 ~RBTCollection();

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

 // return the height of the tree
 int height() const;
 
private:

 // binary search tree node structure
 struct Node {
  K key;
  V value;
  Node* left;
  Node* right;
  bool is_black;
 };

 // root node of the search tree
 Node* root;

 // number of k-v pairs in the collection
 int collection_size;

 // helper to recursively empty search tree
 void make_empty(Node* subtree_root);

 // helper to recursively remove key in BST
 Node* remove(const K& key, Node* subtree_root);

 // recursive helper to do red-black insert key-val pair (backtracking)
 Node* insert(const K& key, const V& val, Node* subtree_root);

 // helper functions to perform a single right rotation
 Node* rotate_right(Node* k2);

 // helper functions to perform a single left rotation
 Node* rotate_left(Node* k2);

 // helper to recursively build sorted list of keys
 void inorder(const Node* subtree, std::vector<K>& keys) const;

 // helper to recursively build sorted list of keys
 void preorder(const Node* subtree, std::vector<K>& keys) const;

 void preorder_copy(Node* lhs_subtree, const Node* rhs_subtree);

 // helper to recursively find range of keys
 void range_search(const Node* subtree, const K& k1, const K& k2,
 std::vector<K>& keys) const;

 // return the height of the tree rooted at subtree_root
 int height(const Node* subtree_root) const;

};


template <typename K, typename V>
RBTCollection<K,V>::RBTCollection() :
collection_size(0), root(nullptr)
{
}


template <typename K, typename V>
void RBTCollection<K,V>::make_empty(Node* subtree_root)
{
 // this is a recursive helper function
 // base case
 if (subtree_root == nullptr)
  return;
 // postorder delete
 make_empty(subtree_root->left);
 make_empty(subtree_root->right);
  delete subtree_root;
  subtree_root = nullptr;
  --collection_size;
}


template <typename K, typename V>
RBTCollection<K,V>::~RBTCollection()
{
 make_empty(root);
}


template <typename K, typename V>
RBTCollection<K,V>::RBTCollection(const RBTCollection<K,V>& rhs)
: collection_size(0), root(nullptr)
{
 *this = rhs;
}


template <typename K, typename V>
RBTCollection <K,V>& RBTCollection<K,V>::operator=(const RBTCollection<K,V>& rhs)
{
 if (this == &rhs)
  return *this;

 // delete current
 make_empty(root);
 root = nullptr;
 // build tree
 std::vector<K> ks;
 preorder(rhs.root, ks);

 V val;
 // find value that corresponds to current key, and insert into tree
 for (int i = 0; i < ks.size(); ++i) {
  find(ks[i], val);
  insert(ks[i], val);
 }

 return *this;
}

template <typename K, typename V>
void RBTCollection<K,V>::remove(const K& key)
{
 // remove desired node
 if (collection_size > 0) {
  if (root->key == key)
   root = remove(key, root);
  else
   remove(key, root);
 }
}

template <typename K, typename V>
typename RBTCollection<K,V>::Node*
RBTCollection<K,V>::remove(const K& key, Node* subtree_root)
{
 // BST is empty
 
 // go left
 if (subtree_root && key < subtree_root->key)
  subtree_root->left = remove(key, subtree_root->left);

 // go right
 else if (subtree_root && key > subtree_root->key)
  subtree_root->right = remove(key, subtree_root->right);

 else if (subtree_root && key == subtree_root->key) {
  //case1: leaf.
  if (subtree_root->left == nullptr && subtree_root->right == nullptr) {
   delete subtree_root;
   subtree_root = nullptr;
   --collection_size;
   return nullptr;
  }
  // case2: one child
  else if (subtree_root->left == nullptr ^ subtree_root->right == nullptr) {
   Node* replace = nullptr;
   // ternanry conditional
   (subtree_root->left != nullptr) ?
   (replace = subtree_root->left) : (replace = subtree_root->right);
   delete subtree_root;
   subtree_root = nullptr;
   --collection_size;
   return replace;

  }
  //case3: two children.
  else if (subtree_root->left != nullptr && subtree_root->right != nullptr) {
   Node* successor = subtree_root->right;
   // right child doesn't have a left child, so inorder successor = right child
   if (successor->left == nullptr) {
    // copy contents of sucessor into subtree_root
    subtree_root->key = successor->key;
    subtree_root->value = successor->value;
    subtree_root->right = successor->right;
    delete successor;
    successor = nullptr;
    --collection_size;
   }
   else {
    // iteratively find inorder successor
    while (successor->left != nullptr)
     successor = successor->left;
    K k = successor->key;
    V v = successor->value;
    // remove leaf node
    remove(successor->key, root);
    // copy contents or inorder successor into subtree_root
    subtree_root->key = k;
    subtree_root->value = v;
   }
  }
 }
 return subtree_root;
}

template <typename K, typename V>
bool RBTCollection<K,V>::find(const K& key, V& val) const
{
 Node* temp = root;
 while (temp != nullptr) {
  // key found in tree
  if (temp->key == key) {
   val = temp->value;
   return true;
  }
  // temp node is greater than key. Traverse left
  if (temp->key > key)
   temp = temp->left;
  // temp node is less than key. Traverse right
  else
   temp = temp->right;
 }
 return false;
}


template <typename K, typename V>
void RBTCollection<K,V>::
range_search(const Node* subtree, const K& k1, const K& k2, std::vector<K>& ks) const
{
 // this is a recursive helper function
 // base statement
 if (subtree == nullptr)
  return;

 // modified inorder traversal. Only traverses nodes between k1 and k2 (inclusive)
 // traverse left until k1 >= the subtree's key
 if (k1 < subtree->key)
  range_search(subtree->left, k1, k2, ks);
 // insert qualifying nodes into vector
 if (k1 <= subtree->key && k2 >= subtree->key)
  ks.push_back(subtree->key);
 // traverse right until k2 <= subtree's key
 if (k2 > subtree->key)
  range_search(subtree->right, k1, k2, ks);
}


template <typename K, typename V> 
void RBTCollection<K,V>::find(const K& k1, const K& k2, std::vector<K>& ks) const
{
 // defer to the range search ( recursive ) helper function
 range_search(root, k1, k2, ks);
}


template <typename K, typename V>
void RBTCollection<K,V>::inorder(const Node* subtree, std::vector<K>& ks) const
{
 // this is a recursive helper function
 // base statement
 if (subtree == nullptr)
  return;
 // left, "print", right
 inorder(subtree->left, ks);
 ks.push_back(subtree->key);
 inorder(subtree->right, ks);
}


template <typename K, typename V>
void RBTCollection<K,V>::preorder(const Node* subtree, std::vector<K>& ks) const
{
 // this is a recursive helper function
 // base statement
 if (subtree == nullptr)
  return;
 // "print" --> left --> right
 ks.push_back(subtree->key);
 preorder(subtree->left, ks);
 preorder(subtree->right, ks);
}

template <typename K, typename V>
void RBTCollection<K,V>::keys(std::vector<K>& ks) const
{
 // defer to the inorder ( recursive ) helper function
 inorder(root, ks);
}


template <typename K, typename V>
void RBTCollection<K,V>::sort(std::vector<K>& ks) const
{
 // defer to the inorder ( recursive ) helper function
 inorder(root, ks);
}


template <typename K, typename V>
int RBTCollection<K,V>::size() const
{
 return collection_size;
}


template <typename K, typename V>
int RBTCollection<K,V>::height(const Node* subtree_root) const
{
 // this is a recursive helper function
 // base case
 if (subtree_root == nullptr)
  return 0;
 //if (subtree_root->left == nullptr && subtree_root->right == nullptr)
 // return 1;

 return 1 + std::max(height(subtree_root->left), height(subtree_root->right));
}


template <typename K, typename V>
int RBTCollection<K,V>::height() const
{
 // defer to the height ( recursive ) helper function
 return height(root);
}

template <typename K, typename V>
typename RBTCollection<K,V>::Node* RBTCollection<K,V>::rotate_right(Node* k2)
{
 Node* k1 = k2->left;
 k2->left = k1->right;
 k1->right = k2;
 return k1;
}

template <typename K, typename V>
typename RBTCollection<K,V>::Node* RBTCollection<K,V>::rotate_left(Node* k2)
{
 Node* k1 = k2->right;
 k2->right = k1->left;
 k1->left = k2;
 return k1;
}

template <typename K, typename V>
typename RBTCollection<K,V>::Node*
RBTCollection<K,V>::insert(const K& key, const V& val, Node* subtree_root)
{
 // recursive base case. insert new node.
 if (!subtree_root) {
  Node* insert_node = new Node;
  insert_node->key = key;
  insert_node->value = val;
  insert_node->left = nullptr;
  insert_node->right = nullptr;
  insert_node->is_black = false;
  return insert_node;
 }

 else {
  // traverse left
  if (key < subtree_root->key)
   subtree_root->left = insert(key, val, subtree_root->left);
  // traverse right
  else
   subtree_root->right = insert(key, val, subtree_root->right);
 }

 // NOTE: subtree_root represents the 'grandparent'
 //       the children of subtree_root represent the 'parent'
 //       the children of the parent represent 'x'
 //       the child of subtree_root that is on the opposite side of the conflict is the 'sibling'
 if (subtree_root->right && subtree_root->right->right) { // check to see if parent and x exist
  if (!subtree_root->right->is_black && !subtree_root->right->right->is_black) { // two reds in a row
   if (!subtree_root->left || subtree_root->left->is_black) {
   // sibling is black or null. right outside grandchild
   // rotate left
   subtree_root = rotate_left(subtree_root);
   // recolor
   subtree_root->is_black = true;
   subtree_root->left->is_black = false;
   }
   else {  // parent has a sibling that is red
    // color flip
    subtree_root->is_black = false;
    subtree_root->left->is_black = true;
    subtree_root->right->is_black = true;
   }
  }
 }
 if (subtree_root->right && subtree_root->right->left) { // check to see if parent and x exist
  if (!subtree_root->right->is_black && !subtree_root->right->left->is_black) { // two reds in a row
   if (!subtree_root->left || subtree_root->left->is_black) {
   // sibling is black or null. right inside grandchild
   // right and left rotate
   subtree_root->right = rotate_right(subtree_root->right);
   subtree_root = rotate_left(subtree_root);
   subtree_root->is_black = true;
   subtree_root->left->is_black = false;
   subtree_root->right->is_black = false;
   }
   
   else { // parent has a sibling that is red
    // color flip
    subtree_root->is_black = false;
    subtree_root->left->is_black = true;
    subtree_root->right->is_black = true;
   }
  }
 }

 if (subtree_root->left && subtree_root->left->left) { // check to see if parent and x exist
  if (!subtree_root->left->is_black && !subtree_root->left->left->is_black) { // two reds in a row
   if (!subtree_root->right || subtree_root->right->is_black) {
    // sibling is black or null. left outside grandchild
    // rotate right
    subtree_root = rotate_right(subtree_root);
    // recolor
    subtree_root->is_black = true;
    subtree_root->right->is_black = false;
   }
   else { // parent has a sibling that is red
    // color flip
    subtree_root->is_black = false;
    subtree_root->left->is_black = true;
    subtree_root->right->is_black = true;
   }
  }
 }

 if (subtree_root->left && subtree_root->left->right) { // check to see if parent and x exist
  if (!subtree_root->left->is_black && !subtree_root->left->right->is_black) { // two reds in a row
   if (!subtree_root->right || subtree_root->right->is_black) {
   // sibling is black or null. left inside grandchild
   // left and right rotate
   subtree_root->left = rotate_left(subtree_root->left);
   subtree_root = rotate_right(subtree_root);
   subtree_root->is_black = true;
   subtree_root->left->is_black = false;
   subtree_root->right->is_black = false;
   }
   else { // parent has a sibling that is red
    // color flip
    subtree_root->is_black = false;
    subtree_root->left->is_black = true;
    subtree_root->right->is_black = true;
   }
  }
 } 
 return subtree_root;
}

template <typename K, typename V>
void RBTCollection<K,V>::insert(const K& key, const V& val)
{
 root = insert(key, val, root);
 root->is_black = true;
 ++collection_size;
}

#endif