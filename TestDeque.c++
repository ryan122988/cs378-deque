// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2012
// Glenn P. Downing
/*
To test the program:
	% g++ -ansi -pedantic -lcppunit -ldl -Wall TestDeque.c++ -o TestDeque.c++.app
	% valgrind TestDeque.c++.app >& TestDeque.out
*/

// --------
// includes
#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>	 // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>	// ==

#include "cppunit/extensions/HelperMacros.h" // CPPUNIT_TEST, CPPUNIT_TEST_SUITE, CPPUNIT_TEST_SUITE_END
#include "cppunit/TestFixture.h"			 // TestFixture
#include "cppunit/TestSuite.h"			   // TestSuite
#include "cppunit/TextTestRunner.h"		  // TestRunner

#include "Deque.h"

// ---------
// TestDeque
template <typename C>
struct TestDeque : CppUnit::TestFixture {
	// -----------
	// constructor
	void test_constructor_1 () {
		C x;
		CPPUNIT_ASSERT(x.size() == 0);
	}

	void test_constructor_2 () {
		C x(25);
		CPPUNIT_ASSERT(x.size() == 25);
	}

	void test_constructor_3 () {
		C x(7, 13);
		CPPUNIT_ASSERT(x.size() == 3);
		CPPUNIT_ASSERT(x[0] == 13);
		CPPUNIT_ASSERT(x[1] == 13);
		CPPUNIT_ASSERT(x[2] == 13);
		CPPUNIT_ASSERT(x[3] == 13);
		CPPUNIT_ASSERT(x[4] == 13);
		CPPUNIT_ASSERT(x[5] == 13);
		CPPUNIT_ASSERT(x[6] == 13);
	}

	void test_constructor_4 () {
		C x(7, 13);
		C y(x);
		CPPUNIT_ASSERT(x.size() == 3);
		CPPUNIT_ASSERT(x[0] == 13);
		CPPUNIT_ASSERT(x[1] == 13);
		CPPUNIT_ASSERT(x[2] == 13);
		CPPUNIT_ASSERT(x[3] == 13);
		CPPUNIT_ASSERT(x[4] == 13);
		CPPUNIT_ASSERT(x[5] == 13);
		CPPUNIT_ASSERT(x[6] == 13);		
		CPPUNIT_ASSERT(y.size() == 3);
		CPPUNIT_ASSERT(y[0] == 13);
		CPPUNIT_ASSERT(y[1] == 13);
		CPPUNIT_ASSERT(y[2] == 13);
		CPPUNIT_ASSERT(y[3] == 13);
		CPPUNIT_ASSERT(y[4] == 13);
		CPPUNIT_ASSERT(y[5] == 13);
		CPPUNIT_ASSERT(y[6] == 13);

	}

	// ----
	// size
	void test_size_1 () {
		const C x;
		CPPUNIT_ASSERT(x.size() == 0);
	}

	void test_size_2 () {
		const C x(45);
		CPPUNIT_ASSERT(x.size() == 45);
	}

	void test_size_3 () {
		const C x (245, 20);
		CPPUNIT_ASSERT(x.size() == 245);
	}

	// ----
	// back
	void test_back_1 () {
		C x(4, 32);
		CPPUNIT_ASSERT(x.back() == 32);
	}

	void test_back_2 () {
		C x;
		CPPUNIT_ASSERT(x.empty() );
		x.push_back(3);
		CPPUNIT_ASSERT(x.back() == 3);
	}

	void test_back_3 () {
		C x(6, 13);
		CPPUNIT_ASSERT(!x.empty() );
		CPPUNIT_ASSERT(x.back() == 13);
	}

	// ----------
	// back_const
	void test_back_const_1 () {
		const C x(13, 10);
		CPPUNIT_ASSERT(x.back() == 10);
	}

	void test_back_const_2 () {
		const C x(15, 2);
		CPPUNIT_ASSERT(x.back() == 2);
	}

	void test_back_const_3 () {
		const C x(350, 13);
		CPPUNIT_ASSERT(x.back() == 13);
	}

	// ---------
	// push_back
	void test_push_back_1 () {
		C x;
		x.push_back(13);
		CPPUNIT_ASSERT(x.size() == 1);
		CPPUNIT_ASSERT(x.back() == 13);
	}

	void test_push_back_2 () {
		C x (4);
		x.push_back(2);
		CPPUNIT_ASSERT(x.size() == 5);
		CPPUNIT_ASSERT(x.back() == 2);
	}

	void test_push_back_3 () {
		C x;
		x.push_back(13);
		x.push_back(12);		
		x.push_back(11);
		x.push_back(10);
		CPPUNIT_ASSERT(x.size() == 4);
		CPPUNIT_ASSERT(x.back() == 10);
	}

	// ----
	// front
	void test_front_1 () {
		C x;
		CPPUNIT_ASSERT(x.empty());
		x.push_front(42);
		CPPUNIT_ASSERT(x.front() == 42);
	}

	void test_front_2 () {
		C x(13, 8);
		CPPUNIT_ASSERT(x.front() == 8);
	}

	void test_front_3 () {
		C x(5, 13);
		CPPUNIT_ASSERT(x.front() == 13);
	}

	// -----------
	// front_const
	void test_front_const_1 () {
		const C x(1, 7);
		CPPUNIT_ASSERT(x.front() == 7);
	}

	void test_front_const_2 () {
		const C x(45, 1);
		CPPUNIT_ASSERT(x.front() == 1);
	}

	void test_front_const_3 () {
		const C x(10, 30);
		CPPUNIT_ASSERT(x.front() == 30);
	}

	// ----------
	// push_front
	void test_push_front_1 () {
		C x(13);
		x.push_back(10);
		x.push_front(7);
		CPPUNIT_ASSERT(x.size() == 15);
		CPPUNIT_ASSERT(x.front() == 7);
	}

	void test_push_front_2 () {
		C x;
		x.push_front(13);
		CPPUNIT_ASSERT(x.size() == 1);
		CPPUNIT_ASSERT(x.front() == 13);
	}

	void test_push_front_3 () {
		C x;
		x.push_front(2);
		x.push_front(20);
		x.push_front(8);
		x.push_front(13);
		CPPUNIT_ASSERT(x.size() == 4);
		CPPUNIT_ASSERT(x.front() == 13);
	}
	// --------
	// pop_back
	void test_pop_back_1 () {
		C x(1);
		x.pop_back();
		CPPUNIT_ASSERT(x.size() == 0);
	}

	void test_pop_back_2 () {
		C x(4, 8);
		x.pop_back();
		CPPUNIT_ASSERT(x.size() == 3);
		CPPUNIT_ASSERT(x.back() == 8);
		x.pop_back();
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(x.back() == 8);
		x.pop_back();		
		CPPUNIT_ASSERT(x.size() == 1);
		CPPUNIT_ASSERT(x.back() == 8);
		x.pop_back();		
		CPPUNIT_ASSERT(x.size() == 0);
	}

	void test_pop_back_3 () {
		C x(22, 12);
		x.pop_back();
		CPPUNIT_ASSERT(x.size() == 21);
		CPPUNIT_ASSERT(x.back() == 12);
	}

	// ---------
	// pop_front
	void test_pop_front_1 () {
		C x(1);
		CPPUNIT_ASSERT(x.size() == 1);
		x.pop_front();
		CPPUNIT_ASSERT(x.size() != 1);
		CPPUNIT_ASSERT(x.size() == 0);
	}

	void test_pop_front_2 () {
		C x(3, 1);
		x.pop_front();
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(x.front() == 1);
	}

	void test_pop_front_3 () {
		C x(10, 2);
		x.pop_front();
		CPPUNIT_ASSERT(x.size() == 9);
		CPPUNIT_ASSERT(x.front() == 2);
		x.pop_front();
		CPPUNIT_ASSERT(x.size() == 8);
		CPPUNIT_ASSERT(x.front() == 2);
		x.pop_front();
		CPPUNIT_ASSERT(x.size() == 7);
		CPPUNIT_ASSERT(x.front() == 2);
		x.pop_front();
		CPPUNIT_ASSERT(x.size() == 6);
		CPPUNIT_ASSERT(x.front() == 2);
		x.pop_front();
		CPPUNIT_ASSERT(x.size() == 5);
		CPPUNIT_ASSERT(x.front() == 2);
		x.pop_front(); //4	
		x.pop_front(); //3
		x.pop_front(); //2
		x.pop_front(); //1
		x.pop_front(); //0
		CPPUNIT_ASSERT(x.size() == 0);
	}

	// --
	// at
	void test_at_1 () {
		C x(1, 5);
		CPPUNIT_ASSERT(x.at(0) == 5);
	}
	
	void test_at_2 () {
		C x;
		x.push_back(10);
		CPPUNIT_ASSERT(x.at(0) == 10);
	}

	void test_at_3 () {
		C x(5, 13);
		CPPUNIT_ASSERT(x.at(0) == 13);
		CPPUNIT_ASSERT(x.at(1) == 13);
		CPPUNIT_ASSERT(x.at(2) == 13);			
		CPPUNIT_ASSERT(x.at(3) == 13);
		CPPUNIT_ASSERT(x.at(4) == 13);
	}

	void test_at_4 () {
		C x;
		try {
			x.at(0);
			CPPUNIT_ASSERT(false);
		}
		catch (std::out_of_range e) {
			CPPUNIT_ASSERT(true);
		}
	}

	// --------
	// at_const
	void test_at_const_1 () {
		const C x(5, 13);
		CPPUNIT_ASSERT(x.at(0) == 13);
		CPPUNIT_ASSERT(x.at(1) == 13);
		CPPUNIT_ASSERT(x.at(2) == 13);			
		CPPUNIT_ASSERT(x.at(3) == 13);
		CPPUNIT_ASSERT(x.at(4) == 13);
	}

	void test_at_const_2 () {
		const C x(1, 5);
		CPPUNIT_ASSERT(x.at(0) == 5);
	}

	void test_at_const_3 () {
		const C x;
		try {
			x.at(0);
			CPPUNIT_ASSERT(false);
		}
		catch (std::out_of_range e) {
			CPPUNIT_ASSERT(true);
		}
	}

	// ---------
	// subscript
	void test_subscript_1 () {
		C x(1, 1);
		CPPUNIT_ASSERT(x[0] == 1);
	}

	void test_subscript_2 () {
		C x(4, 2);
		CPPUNIT_ASSERT(x[0] == 2);
		CPPUNIT_ASSERT(x[1] == 2);
		CPPUNIT_ASSERT(x[2] == 2);
		CPPUNIT_ASSERT(x[3] == 2);
	}

	void test_subscript_3 () {
		C x;
		x.push_back(13);
		x.push_back(13);
		CPPUNIT_ASSERT(x[0] == 13);
	}

	// ---------------
	// const subscript
	void test_subscript_const_1 () {
		const C x(5, 7);
		CPPUNIT_ASSERT(x[0] == 7);
		CPPUNIT_ASSERT(x[1] == 7);
		CPPUNIT_ASSERT(x[2] == 7);
		CPPUNIT_ASSERT(x[3] == 7);
		CPPUNIT_ASSERT(x[4] == 7);
		}

	void test_subscript_const_2 () {
		const C x(50, 13);
		CPPUNIT_ASSERT(x[0] == 13);
		CPPUNIT_ASSERT(x[13] == 13);
		CPPUNIT_ASSERT(x[28] == 13);
		CPPUNIT_ASSERT(x[34] == 13);
		CPPUNIT_ASSERT(x[40] == 13);
		CPPUNIT_ASSERT(x[49] == 13);
	}

	void test_subscript_const_3 () {
		const C x(300);
		CPPUNIT_ASSERT(x[0] == 0);
		CPPUNIT_ASSERT(x[100] == 0);
		CPPUNIT_ASSERT(x[200] == 0);
		CPPUNIT_ASSERT(x[x.size()-1] == 0);
	}

	// -----
	// begin
	void test_begin_1 () {
		C x;
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(true);
	}

	void test_begin_2 () {
		C x(7);
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(true);
	}

	void test_begin_3 () {
		C x(5, 6);
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(true);
		++b;
		CPPUNIT_ASSERT(true);
		++b;
	}

	// -----------
	// begin_const
	void test_begin_const_1 () {
		const C x;
		typename C::const_iterator b = x.begin();
		CPPUNIT_ASSERT(true);
	}

	void test_begin_const_2 () {
		const C x(7);
		typename C::const_iterator b = x.begin();
		CPPUNIT_ASSERT(true);
	}

	void test_begin_const_3 () {
		const C x(5, 6);
		typename C::const_iterator b = x.begin();
		CPPUNIT_ASSERT(true);
		++b;
		CPPUNIT_ASSERT(true);
	}

	// ---
	// end
	void test_end_1 () {
		C x;
		typename C::iterator e = x.end();
		CPPUNIT_ASSERT(true);
	}

	void test_end_2 () {
 		C x(5);
		typename C::iterator e = x.end();
		CPPUNIT_ASSERT(true);
	}

	void test_end_3 () {
		C x(3, 2);
		typename C::iterator e = x.end();
		CPPUNIT_ASSERT(true);
	}

	// ---------
	// end_const
	void test_end_const_1 () {
		const C x;
		typename C::const_iterator e = x.end();
		CPPUNIT_ASSERT(true);
	}	

	void test_end_const_2 () {
		const C x(6);
		typename C::const_iterator e = x.end();
		CPPUNIT_ASSERT(true);
	}

	void test_end_const_3 () {
		const C x(6, 4);
		typename C::const_iterator e = x.end();
		CPPUNIT_ASSERT(true);
	}

	// ------
	// insert
	void test_insert_1 () {
		C x;
		x.insert(x.begin(), 2);
		x.insert(x.end(), 9);
		CPPUNIT_ASSERT(true);
	}

	void test_insert_2 () {
		C x(4);
		x.insert(x.begin()+1, 5);
		CPPUNIT_ASSERT(true);
	}

	void test_insert_3 () {
		C x(5, 7);
		x.insert(x.begin(), 9);
		CPPUNIT_ASSERT(true);
	}

	void test_insert_4 () {
		C x(5, 7);
		x.insert(x.end(), 9);
		CPPUNIT_ASSERT(true);
	}

	// ------
	// resize
	void test_resize_1 () {
		C x(13);
		CPPUNIT_ASSERT(x.size() == 13);
		x.resize(13);
		CPPUNIT_ASSERT(x.size() == 13);
	}

	void test_resize_2 () {
		C x;
		CPPUNIT_ASSERT(x.size() == 0);
		x.resize(30);
		CPPUNIT_ASSERT(x.size() == 30);
	}

	void test_resize_3 () {
		C x(2);
		CPPUNIT_ASSERT(x.size() == 2);
		x.resize(10);
		CPPUNIT_ASSERT(x.size() == 10);
	}

	void test_resize_4 () {
		C x(10);
		CPPUNIT_ASSERT(x.size() == 10);
		x.resize(2);
		CPPUNIT_ASSERT(x.size() == 2);
	}

	void test_resize_5 () {
		C x(6);
		CPPUNIT_ASSERT(x.size() == 6);
		x.resize(7, 7);
		CPPUNIT_ASSERT(x.size() == 7);
	}

	void test_resize_6 () {
		C x(2,7);
		CPPUNIT_ASSERT(x.size() == 2);
		x.resize(3);
		CPPUNIT_ASSERT(x.size() == 3);
		CPPUNIT_ASSERT(x[0] == 7);
		CPPUNIT_ASSERT(x[1] == 7);
		CPPUNIT_ASSERT(x[2] == 7);
	}

	void test_resize_7 () {
		C x(3,3);
		CPPUNIT_ASSERT(x.size() == 3);
		x.resize(6, 6);
		CPPUNIT_ASSERT(x.size() == 6);
		CPPUNIT_ASSERT(x[0] == 3);
		CPPUNIT_ASSERT(x[1] == 3);
		CPPUNIT_ASSERT(x[2] == 3);
		CPPUNIT_ASSERT(x[3] == 3);
		CPPUNIT_ASSERT(x[4] == 3);
		CPPUNIT_ASSERT(x[5] == 3);
	}

	void test_resize_8 () {
		C x(4);
		CPPUNIT_ASSERT(x.size() == 4);
		x.resize(6);
		CPPUNIT_ASSERT(x.size() == 6);
	}

	// -----
	// erase
	void test_erase_1 () {
		C x(13, 2);
		x.erase(x.begin()+0);
		CPPUNIT_ASSERT(true);
	}

	void test_erase_2 () {
		C x(4, 13);
		x.erase(x.begin()+2);
		CPPUNIT_ASSERT(true);
	}

	void test_erase_3 () {
		C x(8, 8);
		x.erase(x.begin()+5);
		CPPUNIT_ASSERT(true);
	}

	// -----
	// swap
	void test_swap_1 () {
		C x(2, 4);
		C y(2, 4);
		x.swap(y);
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(y.size() == 2);
		CPPUNIT_ASSERT(x[0] == 4);
		CPPUNIT_ASSERT(y[0] == 4);
	}

	void test_swap_2 () {
		C x(2, 6);
		C y(4, 13);
		x.swap(y);
		CPPUNIT_ASSERT(x.size() == 2);
		CPPUNIT_ASSERT(y.size() == 3);
		CPPUNIT_ASSERT(x[0] == 13);
		CPPUNIT_ASSERT(y[0] == 6);
	}

	void test_swap_3 () {
		C x(3, 7);
		C y(6, 13);
		x.swap(y);
		CPPUNIT_ASSERT(x.size() == 6);
		CPPUNIT_ASSERT(y.size() == 10);
		CPPUNIT_ASSERT(x[0] == 13);
		CPPUNIT_ASSERT(x[1] == 13);
		CPPUNIT_ASSERT(x[2] == 13);
		CPPUNIT_ASSERT(x[3] == 13);
		CPPUNIT_ASSERT(x[4] == 13);
		CPPUNIT_ASSERT(x[5] == 13);
		CPPUNIT_ASSERT(y[0] == 7);
		CPPUNIT_ASSERT(y[1] == 7);
		CPPUNIT_ASSERT(y[2] == 7);
	}

	// -----
	// clear
	void test_clear_1 () {
		C x;
		x.clear();
		CPPUNIT_ASSERT(x.size() == 0);
	}

	void test_clear_2 () {
		C x(5, 13);
		x.clear();
		CPPUNIT_ASSERT(x.size() == 0);
	}

	void test_clear_3 () {
		C x(5, 13);
		x.clear();
		CPPUNIT_ASSERT(x.size() == 0);
		x.push_back(10);
		CPPUNIT_ASSERT(x[0] == 10);
	}

	// ------
	// assignment
	void test_assignment_1 () {
		C x(4, 2);
		C y(18, 4);
		y = x;
		CPPUNIT_ASSERT(y.size() == 4);
		CPPUNIT_ASSERT(x.size() == 4);
		CPPUNIT_ASSERT(y[0] == 2);
		CPPUNIT_ASSERT(y[1] == 2);
		CPPUNIT_ASSERT(y[2] == 2);
		CPPUNIT_ASSERT(y[3] == 2);
		y[2] = 13;
		CPPUNIT_ASSERT(x[2] == 2);
	}

	void test_assignment_2 () {
		C x;
		C y(5, -4);
		y = x;
		CPPUNIT_ASSERT(y.size() == 0);
		CPPUNIT_ASSERT(x.size() == 0);
		CPPUNIT_ASSERT(y.empty() );
		CPPUNIT_ASSERT(x.empty() );
		y.push_front(1);
		CPPUNIT_ASSERT(x.empty() );
	}

	void test_assignment_3 () {
		C x(7);
		C y(2);
		y = x;
		CPPUNIT_ASSERT(y.size() == 7);
		CPPUNIT_ASSERT(x.size() == 7);
		CPPUNIT_ASSERT(!y.empty() );
		CPPUNIT_ASSERT(!x.empty() );
		y.push_back(1);
		CPPUNIT_ASSERT(x.size() == 7);
	}

	// -------------
	// test_equality
	void test_equality_1 () {
		C x;
		C y;
		CPPUNIT_ASSERT(x == x);
		CPPUNIT_ASSERT(x == y);
	}

	void test_equality_2 () {
		C x(1);
		C y;
		CPPUNIT_ASSERT(x == x);
		CPPUNIT_ASSERT(y == y);
		CPPUNIT_ASSERT(!(x == y));
	}

	void test_equality_3 () {
		C x(1);
		C y(3);
		CPPUNIT_ASSERT(y == y);
		CPPUNIT_ASSERT(!(x == y));
	}

	void test_equality_4 () {
		C x(1);
		C y(1);
		CPPUNIT_ASSERT(x == y);
	}

	void test_equality_5 () {
		C x(3, 5);
		C y(3, 5);
		CPPUNIT_ASSERT(x == y);
	}

	void test_equality_6 () {
		C x(2, 3);
		C y(2, 3);
		x.push_back(2);
		y.push_back(2);
		CPPUNIT_ASSERT((x == y));
	}

	void test_equality_7 () {
		C x(2, 3);
		C y(2, 3);
		x.push_back(2);
		CPPUNIT_ASSERT(!(x == y));
	}

	void test_equality_8 () {
		C x(6, 7);
		C y(6, 7);
		y[2] = 3;
		CPPUNIT_ASSERT(!(x == y));
	}

	// -------------
	// test_less_than
	void test_less_than_1 () {
		C x;
		C y;
		CPPUNIT_ASSERT(!(x < x));
		CPPUNIT_ASSERT(!(x < y));
	}

	void test_less_than_2 () {
		C x(7);
		C y;
		CPPUNIT_ASSERT(!(x < x));
		CPPUNIT_ASSERT(y < x);
	}

	void test_less_than_3 () {
		C x(3, -2);
		C y(7);
		CPPUNIT_ASSERT(x < y);
	}
	
	void test_less_than_4 () {
		C x(-5, 3);
		C y(4);
		CPPUNIT_ASSERT(x < y);
	}
	// -----------------
	// iterator_equality
	void test_iterator_equality_1 () {
		C x;
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(x.begin == b);
	}

	void test_iterator_equality_2 () {
		C x(450);
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(x.begin == b);
	}

	void test_iterator_equality_3 () {
		C x(600, 10);
		typename C::iterator b = x.begin();
		CPPUNIT_ASSERT(x.begin == b);
	}

	// -----
	// suite
	CPPUNIT_TEST_SUITE(TestDeque);
	CPPUNIT_TEST (test_constructor_1) 
	CPPUNIT_TEST (test_constructor_2)
	CPPUNIT_TEST (test_constructor_3) 
	CPPUNIT_TEST (test_constructor_4) 	
	CPPUNIT_TEST (test_size_1)
	CPPUNIT_TEST (test_size_2)
	CPPUNIT_TEST (test_size_3) 
	CPPUNIT_TEST (test_back_4) 
	CPPUNIT_TEST (test_back_5) 
	CPPUNIT_TEST (test_back_6)
	CPPUNIT_TEST (test_back_const_1)  
	CPPUNIT_TEST (test_back_const_2) 
	CPPUNIT_TEST (test_back_const_3) 
	CPPUNIT_TEST (test_push_back_1) 
	CPPUNIT_TEST (test_push_back_2)
	CPPUNIT_TEST (test_push_back_3) 
	CPPUNIT_TEST (test_front_1)
	CPPUNIT_TEST (test_front_2)
	CPPUNIT_TEST (test_front_3)
	CPPUNIT_TEST (test_front_const_1)  
	CPPUNIT_TEST (test_front_const_2) 
	CPPUNIT_TEST (test_front_const_3) 
	CPPUNIT_TEST (test_push_front_1)
	CPPUNIT_TEST (test_push_front_2)
	CPPUNIT_TEST (test_push_front_3)
	CPPUNIT_TEST (test_pop_back_1)
	CPPUNIT_TEST (test_pop_back_2)
	CPPUNIT_TEST (test_pop_back_3) 
	CPPUNIT_TEST (test_pop_front_1)  
	CPPUNIT_TEST (test_pop_front_2) 
	CPPUNIT_TEST (test_pop_front_3) 
	CPPUNIT_TEST (test_at_1)
	CPPUNIT_TEST (test_at_2)
	CPPUNIT_TEST (test_at_3)
	CPPUNIT_TEST (test_at_4)
	CPPUNIT_TEST (test_at_const_1)
	CPPUNIT_TEST (test_at_const_2)
	CPPUNIT_TEST (test_at_const_3)
	CPPUNIT_TEST (test_subscript_1) 
	CPPUNIT_TEST (test_subscript_2)
	CPPUNIT_TEST (test_subscript_3)
	CPPUNIT_TEST (test_subscript_const_1) 
	CPPUNIT_TEST (test_subscript_const_2)
	CPPUNIT_TEST (test_subscript_const_3)
	CPPUNIT_TEST (test_begin_1)
	CPPUNIT_TEST (test_begin_2)
	CPPUNIT_TEST (test_begin_3)
	CPPUNIT_TEST (test_begin_const_1) 
	CPPUNIT_TEST (test_begin_const_2)
	CPPUNIT_TEST (test_begin_const_3)
	CPPUNIT_TEST (test_end_1)
	CPPUNIT_TEST (test_end_2)
	CPPUNIT_TEST (test_end_3)
	CPPUNIT_TEST (test_end_const_1) 
	CPPUNIT_TEST (test_end_const_2)
	CPPUNIT_TEST (test_end_const_3)
	CPPUNIT_TEST (test_insert_1)
	CPPUNIT_TEST (test_insert_2)
	CPPUNIT_TEST (test_insert_3)
	CPPUNIT_TEST (test_insert_4)
	CPPUNIT_TEST (test_resize_1)
	CPPUNIT_TEST (test_resize_2)
	CPPUNIT_TEST (test_resize_3)
	CPPUNIT_TEST (test_resize_4)
	CPPUNIT_TEST (test_resize_5)
	CPPUNIT_TEST (test_resize_6)
	CPPUNIT_TEST (test_resize_7)
	CPPUNIT_TEST (test_erase_1)
	CPPUNIT_TEST (test_erase_2)
	CPPUNIT_TEST (test_erase_3)
	CPPUNIT_TEST (test_swap_1)
	CPPUNIT_TEST (test_swap_2)
	CPPUNIT_TEST (test_swap_3)
	CPPUNIT_TEST (test_clear_1) 
	CPPUNIT_TEST (test_clear_2)
	CPPUNIT_TEST (test_clear_3)
	CPPUNIT_TEST (test_assignment_1) 
	CPPUNIT_TEST (test_assignment_2)
	CPPUNIT_TEST (test_assignment_3)
	CPPUNIT_TEST (test_equality_1)
	CPPUNIT_TEST (test_equality_2)
	CPPUNIT_TEST (test_equality_3)
	CPPUNIT_TEST (test_equality_4)
	CPPUNIT_TEST (test_equality_5)
	CPPUNIT_TEST (test_equality_6)
	CPPUNIT_TEST (test_equality_7)
	CPPUNIT_TEST (test_equality_8)
	CPPUNIT_TEST (test_less_than_1) 
	CPPUNIT_TEST (test_less_than_2)
	CPPUNIT_TEST (test_less_than_3)
	CPPUNIT_TEST (test_less_than_4)
	CPPUNIT_TEST (test_iterator_equality_1) 
	CPPUNIT_TEST (test_iterator_equality_2)
	CPPUNIT_TEST (test_iterator_equality_3)
	CPPUNIT_TEST_SUITE_END();
};

// ----
// main
int main () {
	using namespace std;
	ios_base::sync_with_stdio(false);		// turn off synchronization with C I/O
	cout << "TestDeque.c++" << endl << endl;

	CppUnit::TextTestRunner tr;
	tr.addTest(TestDeque<   deque<int> >::suite() );
	tr.addTest(TestDeque< MyDeque<int> >::suite() );
	tr.run();

	cout << "Done." << endl;
	return 0;
}
