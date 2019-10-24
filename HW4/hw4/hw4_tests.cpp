/*Author: Eric Gustin
  Assignment: CPSC223-01 HW04
  Description: Contains LinkedListCollection class testing. Contains 10 different
  assert blocks, each uniquely testing the functionality of the class's methods*/

#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "linked_list_collection.h"

using namespace std;

// Test 1
TEST(BasicsListTest, CorrectSize) {
 LinkedListCollection<string,double>* a = new LinkedListCollection<string,double>;
 ASSERT_EQ(a->size(), 0);
 a->insert("FB", 179.50);
 ASSERT_EQ(a->size(), 1);
 a->insert("AAPL", 220.29);
 ASSERT_EQ(a->size(), 2);
 a->insert("AMZN", 1739.81);
 ASSERT_EQ(a->size(), 3);
 a->insert("NFLX", 263.86);
 ASSERT_EQ(a->size(), 4);
 a->insert("GOOGL", 1240.54);
 ASSERT_EQ(a->size(), 5);
 delete a;

 // make sure doesn't drop to -1
 LinkedListCollection<string,int> zero_list;
 zero_list.remove("nothing");
 ASSERT_EQ(zero_list.size(), 0);
}

// Test 2
TEST(BasicListTest, InsertAndFind) {
 LinkedListCollection<string,double>* b = new LinkedListCollection<string,double>;
 double v;
 ASSERT_EQ(b->find("a", v), false);
 b->insert("a", 10.0);
 ASSERT_EQ(b->find("a", v), true);
 ASSERT_EQ(v, 10.0);
 ASSERT_EQ(b->find("b", v), false);
 b->insert("b", 20.0);
 ASSERT_EQ(b->find("b", v), true);
 ASSERT_EQ(v, 20.0);
 // insert/find a string that's longer than 1 char
 b->insert("GoNzAgA", 22);
 ASSERT_EQ(b->find("GoNzAgA", v), true);
 delete b;
}

 // Test 3
TEST(BasicListTest, RemoveElems) {
 LinkedListCollection<string,double>* c = new LinkedListCollection<string,double>;
 // attempt to remove from an empty object
 c->remove("");
 ASSERT_EQ(c->size(), 0);

 c->insert("a", 10.0);
 c->insert("b", 20.0);
 c->insert("c", 30.0);
 c->insert("d", 40.0);
 c->insert("e", 50.0);
 c->insert("f", 60.0);

 ASSERT_EQ(c->size(), 6);
 c->remove("q"); // try to remove an element that is not in c. should do nothing
 ASSERT_EQ(c->size(), 6);
 c->remove("a"); // remove first element
 ASSERT_EQ(c->size(), 5);

 double v;
 ASSERT_EQ(c->find("a", v), false);
 ASSERT_EQ(c->find("b", v), true);
 ASSERT_EQ(v, 20.0);
 ASSERT_EQ(c->find("c", v), true);
 ASSERT_EQ(v, 30.0);
 ASSERT_EQ(c->find("d", v), true);
 ASSERT_EQ(v, 40.0);
 ASSERT_EQ(c->find("e", v), true);
 ASSERT_EQ(v, 50.0);
 ASSERT_EQ(c->find("f", v), true);
 ASSERT_EQ(v, 60.0);
 c->remove("f"); // remove last element
 ASSERT_EQ(c->size(), 4);
 ASSERT_EQ(c->find("f", v), false);
 c->remove("d"); // remove non edge element
 ASSERT_EQ(c->size(), 3);
 ASSERT_EQ(c->find("d", v), false);
 c->remove("b");
 c->remove("c");
 c->remove("e"); // remove the only element in the list
 ASSERT_EQ(c->size(), 0);
 delete c;
}

 // Test 4
TEST(BasicListTest, GetKeys) {
 LinkedListCollection<string,double>* d = new LinkedListCollection<string,double>;
 d->insert("a", 10.0);
 d->insert("b", 20.0);
 d->insert("c", 30.0);
 vector<string> ks;
 d->keys(ks);
 vector<string>::iterator iter;
 iter = find(ks.begin(), ks.end(), "a");
 ASSERT_NE(iter, ks.end());
 iter = find(ks.begin(), ks.end(), "b");
 ASSERT_NE(iter, ks.end());
 iter = find(ks.begin(), ks.end(), "c");
 ASSERT_NE(iter, ks.end());
 iter = find(ks.begin(), ks.end(), "d");
 ASSERT_EQ(iter, ks.end());
 delete d;
}

 // Test 5
TEST(BasicListTest, GetKeyRange) {
 LinkedListCollection<string,double>* e = new LinkedListCollection<string,double>;
 e->insert("a", 10.0);
 e->insert("b", 20.0);
 e->insert("c", 30.0);
 e->insert("d", 40.0);
 e->insert("e", 50.0);
 vector<string> ks;

 e->find("b", "d", ks);
 vector<string>::iterator iter;
 iter = find(ks.begin(), ks.end(), "b");
 ASSERT_NE(iter, ks.end());
 iter = find(ks.begin(), ks.end(), "c");
 ASSERT_NE(iter, ks.end());
 iter = find(ks.begin(), ks.end(), "d");
 ASSERT_NE(iter, ks.end());
 iter = find(ks.begin(), ks.end(), "a");
 ASSERT_EQ(iter, ks.end());
 iter = find(ks.begin(), ks.end(), "e");
 ASSERT_EQ(iter, ks.end());
 delete e;
 // test if find range works for strings
 // longer than one character
 LinkedListCollection<string,double>* f = new LinkedListCollection<string,double>;
 f->insert("apples", 10);
 f->insert("zebras", 20);
 f->insert("golf", 30);
 f->insert("hydro", 40);
 vector<string> ks2;
 f->find("bees", "yoyo", ks2);
 vector<string>::iterator iter2;
 iter = find(ks2.begin(), ks2.end(), "golf");
 ASSERT_NE(iter, ks2.end());
 iter = find(ks2.begin(), ks2.end(), "hydro");
 ASSERT_NE(iter, ks2.end());
 iter = find(ks2.begin(), ks2.end(), "apples");
 ASSERT_EQ(iter, ks2.end());
 iter = find(ks2.begin(), ks2.end(), "zebras");
 ASSERT_EQ(iter, ks2.end());
 ASSERT_EQ(ks2.size(), 2);
 // find only 1 key
 vector<string> ks3;
 f->find("zebras", "zebras", ks3);
 ASSERT_EQ(ks3.size(), 1);
 ASSERT_EQ(ks3[0], "zebras");
 // find no keys
 vector<string> ks4;
 f->find("bye", "byzantine", ks4);
 ASSERT_EQ(ks4.size(), 0);
 delete f;
}

 // Test 6
TEST(BasicListTest, KeySort) {
 LinkedListCollection<string,double>* g = new LinkedListCollection<string,double>;
 g->insert("a", 10.0);
 g->insert("e", 50.0);
 g->insert("c", 30.0);
 g->insert("b", 20.0);
 g->insert("d", 40.0);
 vector<string> sorted_ks;
 g->sort(sorted_ks);
 // check if sort order
 for(int i = 0; i < int(sorted_ks.size()) - 1; ++i)
  ASSERT_LE(sorted_ks[i], sorted_ks[i+1]);
 delete g;

 LinkedListCollection<string,double>* h = new LinkedListCollection<string,double>;
 h->insert("anagrams", 23);
 h->insert("hemmingson", 1);
 h->insert("string", 44);
 h->insert("Regis", 99);
 h->insert("Salem Oregon", 98);
 h->insert("turing", 23);
 vector<string> sorted_stringInt;
 h->sort(sorted_stringInt);
 //check if sort order
 for (int i = 0; i < int(sorted_stringInt.size())-1; ++i)
  ASSERT_LE(sorted_stringInt[i], sorted_stringInt[i+1]);
 delete h;
}

TEST(BasicListTest, Negatives) {
 LinkedListCollection<double,string>* l = new LinkedListCollection<double,string>;
 l->insert(999.0, "DigitalLogic");
 l->insert(400.4, "AlgsAndDataStruct");
 l->insert(0.0, "Human Nature");
 l->insert(-33.2, "discreteMath");
 l->insert(-0.1, "Globals");
 vector<double> sorted_ints;
 l->sort(sorted_ints);
 for (int i = 0; i < int(sorted_ints.size()-1); ++i)
 {
  ASSERT_LE(sorted_ints[i], sorted_ints[i+1]);
 }
 delete l;
}

TEST(BasicListTest, SizeZero) {
 LinkedListCollection<int,int>* m = new LinkedListCollection<int,int>;
 ASSERT_EQ(m->size(), 0);
 m->remove(2);
 ASSERT_EQ(m->size(), 0);
 int my_val;
 ASSERT_EQ(m->find(0, my_val), false);
 vector<int> keys_ints;
 m->keys(keys_ints);
 ASSERT_EQ(keys_ints.size(), 0);
 m->sort(keys_ints);
 ASSERT_EQ(keys_ints.size(), 0);
 delete m;
}

TEST(BasicListTest, CopyList) {
 LinkedListCollection<string,int> n;
 n.insert("China", 1433783686);
 n.insert("India", 1366417754);
 n.insert("United States", 329064917);
 n.insert("Mars", 1);
 LinkedListCollection<string,int> n_copy = n;
 ASSERT_EQ(n_copy.size(), n.size());

 vector<string> n_keys;
 vector<string> n_copy_keys;
 n.keys(n_keys);
 n_copy.keys(n_copy_keys);
 ASSERT_EQ(n_copy_keys[1], "India");
 for (int i = 0; i < int(n.size()); ++i)
 {
  ASSERT_EQ(n_keys[i], n_copy_keys[i]);
 }
 // copy constructor with empty linked lists
 LinkedListCollection<string,int> empty;
 LinkedListCollection<string,int> empty_copy(empty);
 ASSERT_EQ(empty.size(), 0);
 ASSERT_EQ(empty_copy.size(), 0);
}

TEST(BasicListTest, AssignList) {
 LinkedListCollection<string,int> o;
 o.insert("January", 31);
 o.insert("February", 28);
 o.insert("March", 31);
 o.insert("April", 30);
 o.insert("May", 31);
 o.insert("June", 30);

 LinkedListCollection<string,int> p;
 p.insert("December", 31);
 p.insert("Year", 365);
 p.insert("Leap Year", 366);

 p = o;
 ASSERT_EQ(p.size(), 6);
 vector<string> o_keys;
 vector<string> p_keys;
 o.keys(o_keys);
 p.keys(p_keys);
 for (int i = 0; i < int(o.size()); ++i)
 {
  ASSERT_EQ(o_keys[i], p_keys[i]);
 }
 // assignment operator will not do copying if trying to copy itself.
 p = p;
}

int main(int argc, char** argv)
{
 testing::InitGoogleTest(&argc, argv);
 return RUN_ALL_TESTS();
}
