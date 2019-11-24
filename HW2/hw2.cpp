// Author Eric Gustin
// Assignment #2
// Description: Throrough testing of my integer class. Covers all
// comparison operators, negation, double negation, multiple
// operations in a single expression, and every possible
// case for subtracting and addition.
#include <iostream>
#include <cassert>
#include "integer.h"

using namespace std;

int main()
{
 // test same values
 Integer x1("42");
 Integer x2("42");

 assert(x1 == x2);
 assert(!(x1 != x2));
 assert(!(x1 < x2));
 assert(!(x1 > x2));
 assert(x1 <= x2);
 assert(x1 >= x2);

 //test two different values
 Integer x3("50");
 Integer x4("57");
 assert(x3 != x4);
 assert(x3 < x4);
 assert(x3 <= x4);
 assert(!(x3 > x4));
 assert(!(x3 >= x4));
 assert(!(x3 == x4));
 assert(x4 > x3);
 assert(x4 >= x3);
 assert(!(x4 < x3));
 assert(!(x4 <= x3));

 // test adding two different values
 Integer x5("99999999999999999999");
 Integer x6("1");
 Integer r1("100000000000000000000");
 assert(x5 + x6 == r1);

 // no carry add test
 Integer x7("21");
 Integer x8("175");
 Integer r2("196");
 assert(x7 + x8 == r2);

 // test subtraction borrowing over multiple integers
 Integer x9("1000000");
 Integer x10("999999");
 assert(x9 >= x10);
 Integer r3("1");
 assert(x9 - x10 == r3);

 Integer x11("9742");
 Integer x12("67897");
 Integer r4("58155");
 assert(x11 - x12 == (-r4));

//adding two negatives. 
 Integer x13("400");
 Integer x14("800");
 Integer r5("1200");
 assert((-x13) + (-x14) == (-r5)); //-400+-800 = -1200

 //adding 1 pos and 1 neg. Where lhs < rhs
 Integer x15("1");
 Integer x16("9876");
 Integer r6("9875");
 assert(x15 + (-x16) == (-r6)); //1+-9876 = -9875

 //adding 1 pos and 1 neg. Where lhs > rhs
 Integer x15a("189234467");
 Integer x16a("9876");
 Integer r6a("189224591");
 assert(x15a + (-x16a) == (r6a)); //189234467+-9876 = 189224591
 
 //subtracting 2 negs
 Integer x17("192837");
 Integer x18("5647");
 Integer r7("187190");
 assert((-x17) - (-x18) == (-r7)); //-192837--5647 = -187190

 //subtracting 1 neg and 1 pos. Where lhs > rhs
 Integer x19("10000");
 Integer x20("999");
 Integer r8("10999");
 assert((-x19) - x20 == (-r8)); //-10000-999 = -10999

 //subtracting 1 neg and 1 pos. Where lhs < rhs. Where rhs is negative.
 Integer x21("90000");
 Integer x22("900000");
 Integer r9("990000");
 assert(x21 - (-x22) == (r9)); //90000 - -900000 = 990000

 // test imultiple operations in a single expression
 Integer x23("3874562983");
 Integer x24("1844674");
 Integer r10("0");
 assert(((x23 - x24) + ((-x23) - (-x24))) == r10);

 // additional tests for addition , subtraction , and unary minus
 // print tests
 cout << "\nTesting unary minus and other additional tests:" << endl;
 cout << "should be 1:       " << x6 << endl;
 cout << "should be 42:      " << x1 << endl;
 cout << "should be -42:    " << -x1 << endl;
 cout << "should be 42:      " << -(-x1) << endl;
 cout << "should be 175:     " << x8 << endl;
 cout << "should be -58155: " << x11 - x12 << endl;


 Integer small("9934");
 Integer big("98765");
 Integer neg_small = -small;
 Integer neg_big = -big;

 //all addition cases
 cout << "\nAll Addition Case Tests:" << endl;
 cout << "should be -108699:  " << neg_small + neg_big << endl; //-9934 + -98765
 cout << "should be -108699:  " << neg_big + neg_small << endl; //-98765 + -9934
 cout << "should be -19868:   " << neg_small + neg_small << endl; //-9934 + -9934
 cout << "should be  88831:    " << neg_small + big << endl; //-9934 + 98765
 cout << "should be -88831:   " << neg_big + small << endl; //-98765 + 9934
 cout << "should be  0:        " << neg_small + small << endl; //-9934 + 9934
 cout << "should be -88831:   " << small + neg_big << endl; //9934 + -98765
 cout << "should be  88831:    " << big + neg_small << endl; //98765 + -9934
 cout << "should be  0:        " << small + neg_small << endl; //9934 + -9934
 cout << "should be  108699:   " << small + big << endl; //9934 + 98765
 cout << "should be  108699:   " << big + small << endl; //98765 + 9934
 cout << "should be  19868:    " << small + small << endl; //9934 + 9934

 //all subtraction cases
 cout << "\nAll Subtraction Case Tests:" << endl;
 cout << "should be  88831:   " << neg_small - neg_big << endl; //-9934 - -98765
 cout << "should be -88831:  " << neg_big - neg_small << endl; //-98765 - -9934
 cout << "should be  0:       " << neg_small - neg_small << endl; //-9934 - -9934
 cout << "should be -108699: " << neg_small - big << endl; //-9934 - 98765
 cout << "should be -108699  " << neg_big - small << endl; //-98765 - 9934
 cout << "should be -19868   " << neg_small - small << endl; //-9934 - 9934
 cout << "should be  108699:  " << small - neg_big << endl; //9934 - -98765
 cout << "should be  108699:  " << big - neg_small << endl; //98765 - -9934
 cout << "should be  19868:   " << small - neg_small << endl; //9934 - -9934
 cout << "should be -88831:   " << small - big << endl; //9934 - 98765
 cout << "should be  88831    " << big - small << endl; //98765 - 9934
 cout << "should be  0        " << small - small << endl; //9934 - 9934
}