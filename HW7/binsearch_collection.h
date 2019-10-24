/*Author: Eric Gustin
  Assignment: CPSC223-01 HW05 binsearch_collection.h
  Description: This program uses the collection abstract class to implement
  a collection using a vector. For the insert, remove, find(2 parameter),
  find(3 parameter), this program uses the binary search algorithm. The find
  function saw the largest drop in execution time when compared with a vector
  that does not implement the binary search algorithm.
*/

1 # ifndef HASH_TABLE_COLLECTION_H
2 # define HASH_TABLE_COLLECTION_H
3
4 # include < vector >
5 # include < algorithm >
6 # include < functional >
7 # include " collection .h"
8
9 template < typename K , typename V >
10 class HashTableCollection : public Collection <K ,V >
11 {
12 public :
13
14 // create an empty linked list
15 HashTableCollection ();
16
17 // copy a linked list
18 HashTableCollection ( const HashTableCollection <K ,V >& rhs );
19
20 // assign a linked list
21 HashTableCollection <K ,V >& operator =( const HashTableCollection <K ,V >& rhs );
22
23 // delete a linked list
24 ~ HashTableCollection ();
25
26 // insert a key - value pair into the collection
27 void insert ( const K & key , const V & val );
28
29 // remove a key - value pair from the collection
30 void remove ( const K & key );
31
32 // find the value associated with the key
33 bool find ( const K & key , V & val ) const ;
34
35 // find the keys associated with the range
36 void find ( const K & k1 , const K & k2 , std :: vector <K >& keys ) const ;
4
37
38 // return all keys in the collection
39 void keys ( std :: vector <K >& keys ) const ;
40
41 // return collection keys in sorted order
42 void sort ( std :: vector <K >& keys ) const ;
43
44 // return the number of keys in collection
45 int size () const ;
46
47 private :
48
49 // helper to empty entire hash table
50 void make_empty ();
51
52 // resize and rehash the hash table
53 void resize_and_rehash ();
54
55 // linked list node structure
56 struct Node {
57 K key ;
58 V value ;
59 Node * next ;
60 };
61
62 // number of k-v pairs in the collection
63 int collection_size ;
64
65 // number of hash table buckets ( default is 16)
66 int table_capacity ;
67
68 // hash table array load factor ( set at 75% for resizing )
69 const double load_factor_threshold ;
70
71 // hash table array
72 Node ** hash_table ;
73 };
74
75
76 template < typename K , typename V >
77 HashTableCollection <K ,V >:: HashTableCollection () :
78 collection_size (0) , table_capacity (16) , load_factor_threshold (0.75)
79 {
80 // dynamically allocate the hash table array
81 hash_table = new Node *[ table_capacity ];
82 // initialize the hash table chains
83 for (int i = 0; i < table_capacity ; ++ i )
84 hash_table [ i ] = nullptr ;
85 }
86
87 template < typename K , typename V >
88 void HashTableCollection <K ,V >:: make_empty ()
89 {
5
90 // make sure hash table exists
91 // ...
92 // remove each key
93 // ...
94 // remove the hash table
95 delete hash_table ;
96 }
97
98 template < typename K , typename V >
99 HashTableCollection <K ,V >::~ HashTableCollection ()
100 {
101 make_empty ();
102 }
103
104
105 template < typename K , typename V >
106 HashTableCollection <K ,V >:: HashTableCollection ( const HashTableCollection <K ,V >& rhs )
107 : hash_table ( nullptr )
108 {
109 * this = rhs ;
110 }
111
112 template < typename K , typename V >
113 HashTableCollection <K ,V >&
114 HashTableCollection <K ,V >:: operator =( const HashTableCollection <K ,V >& rhs )
115 {
116 // check if rhs is current object and return current object
117 if ( this == & rhs )
118 return * this ;
119 // delete current object
120 make_empty ();
121 // initialize current object
122 // ...
123 // create the hash table
124 // ...
125 // do the copy
126 // ...
127 return * this ;
128 }
129
130 template < typename K , typename V >
131 void HashTableCollection <K ,V >:: resize_and_rehash ()
132 {
133 // setup new table
134 int new_capacity = table_capacity * 2;
135 // ... similarly with collection size ...
136 // dynamically allocate the new table
137 Node ** new_table = new Node *[ new_capacity ];
138 // initialize new table
139 // ...
140 // insert key values
141 std :: vector <K > ks ;
142 keys ( ks );
6
143 for ( K key : ks ) {
144 // hash the key
145 // ...
146 // create a new node in new table
147 // ...
148 }
149 // clear the current data
150 make_empty ();
151 // update to the new settings
152 hash_table = new_table ;
153 // ... update remaining vars ...
154 }
155
156 template < typename K , typename V >
157 void HashTableCollection <K ,V >:: insert ( const K & key , const V & val )
158 {
159 // check current load factor versus load factor threshold ,
160 // and resize and copy if necessary by calling resize_and_rehash ()
161 // ...
162 // hash the key
163 // ...
164 // create the new node
165 // ...
166 // update the size
167 // ...
168 }
169
170 ...
171
172 template < typename K , typename V >
173 void HashTableCollection <K ,V >:: sort ( std :: vector <K >& ks ) const
174 {
175 keys ( ks );
176 std :: sort ( ks . begin () , ks . end ());
177 }
178
179 template < typename K , typename V >
180 int HashTableCollection <K ,V >:: size () const
181 {
182 return collection_size ;
183 }
184
185 # endif