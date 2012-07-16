// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2012
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert> // assert
#include <iterator> // iterator, bidirectional_iterator_tag
#include <memory> // allocator
#include <stdexcept> // out_of_range
#include <utility> // !=, <=, >, >=

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;
using namespace std;
// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);}
    return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        destroy(a, p, x);
        throw;}
    return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;}

// -----
// MyDeque
// -----

template < typename T, typename A = std::allocator<T> >
class MyDeque {
    public:
        // --------
        // typedefs
        // --------

        typedef A allocator_type;
        typedef typename allocator_type::value_type value_type;

        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;

    public:
        // -----------
        // operator ==
        // -----------

        /**
* <your documentation>
*/
        friend bool operator == (const MyDeque& lhs, const MyDeque& rhs) {
            // <your code>
            // you must use std::equal()
	    return(lhs.size() == rhs.size()) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

        // ----------
        // operator <
        // ----------

        /**
* <your documentation>
*/
        friend bool operator < (const MyDeque& lhs, const MyDeque& rhs) {
            // <your code>
            // you must use std::lexicographical_compare()
	    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
            }

    private:
        // ----
        // data
        // ----

        allocator_type _a;
        typename allocator_type::template rebind<T*>::other second_a;
	T* container;
        T* dequeSize;
	T* capacity;
        // <your data>

    private:
        // -----
        // valid
        // -----

        bool valid () const {
            // <your code>
	    return((!container && !dequeSize && !capacity) || (container <= dequeSize) && (dequeSize <= capacity));
            }

    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag iterator_category;
                typedef typename MyDeque::value_type value_type;
                typedef typename MyDeque::difference_type difference_type;
                typedef typename MyDeque::pointer pointer;
                typedef typename MyDeque::reference reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
* <your documentation>
*/
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    // <your code>
		    return (lhs._p == rhs._p) && (lhs._i == rhs._i);
                    }

                /**
* <your documentation>
*/
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
* <your documentation>
*/
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
* <your documentation>
*/
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----
               
                // <your data>
                MyDeque* _p;
		std::size_t _i;
            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
		    
                    return true;}

            public:
                // -----------
                // constructor
                // -----------

                /**
* <your documentation>
*/
                iterator (MyDeque* p, std::size_t i) : _p(p), _i(i) {
                    // <your code>
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
* <your documentation>
*/
                reference operator * () const {
                    // <your code>
                    // dummy is just to be able to compile the skeleton, remove it
                    return _p->container[_i];}

                // -----------
                // operator ->
                // -----------

                /**
* <your documentation>
*/
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
* <your documentation>
*/
                iterator& operator ++ () {
                    // <your code>
                    ++_i;
                    return *this;}

                /**
* <your documentation>
*/
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
* <your documentation>
*/
                iterator& operator -- () {
                    // <your code>
		    --_i;
                    assert(valid());
                    return *this;}

                /**
* <your documentation>
*/
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
* <your documentation>
*/
                iterator& operator += (difference_type d) {
                    // <your code>
		    _i += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
* <your documentation>
*/
                iterator& operator -= (difference_type d) {
                    // <your code>
		    _i -= d;
                    assert(valid());
                    return *this;}};

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag iterator_category;
                typedef typename MyDeque::value_type value_type;
                typedef typename MyDeque::difference_type difference_type;
                typedef typename MyDeque::const_pointer pointer;
                typedef typename MyDeque::const_reference reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
* <your documentation>
*/
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    // <your code>
			return (lhs._p == rhs._p) && (lhs._i == rhs._i);
                }

                /**
* <your documentation>
*/
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
* <your documentation>
*/
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
* <your documentation>
*/
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>
		MyDeque* _p;
		std::size_t _i;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    // <your code>
                    return true;}

            public:
                // -----------
                // constructor
                // -----------

                /**
* <your documentation>
*/
                const_iterator (MyDeque* p, std::size_t i) : _p(p), _i(i) {
                    // <your code>
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
* <your documentation>
*/
                reference operator * () const {
                    // <your code>
                    // dummy is just to be able to compile the skeleton, remove it
                    return _p->container[_i];}

                // -----------
                // operator ->
                // -----------

                /**
* <your documentation>
*/
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
* <your documentation>
*/
                const_iterator& operator ++ () {
                    // <your code>
		    ++_i;
                    assert(valid());
                    return *this;}

                /**
* <your documentation>
*/
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
* <your documentation>
*/
                const_iterator& operator -- () {
                    // <your code>
		    --_i;
                    assert(valid());
                    return *this;}

                /**
* <your documentation>
*/
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
* <your documentation>
*/
                const_iterator& operator += (difference_type d) {
                    // <your code>
		    _i += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
* <your documentation>
*/
                const_iterator& operator -= (difference_type d) {
                    // <your code>
		    _i -= d;
                    assert(valid());
                    return *this;}};

    public:
        // ------------
        // constructors
        // ------------

        /**
* <your documentation>
*/
        explicit MyDeque (const allocator_type& a = allocator_type()): _a(a) {
            // <your code>
	    container = dequeSize = capacity = 0;
            assert(valid());}

        /**
* <your documentation>
*/
        explicit MyDeque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type()) : _a(a){
            // <your code>
	    container = _a.allocate(s);
	    dequeSize = capacity = container + s;
	    uninitialized_fill(_a, begin(), end(), v);
            assert(valid());}

        /**
* <your documentation>
*/
        MyDeque (const MyDeque& that) : _a(that._a){
            // <your code>
	    container = _a.allocate(that.size());
	    dequeSize = capacity = container + that.size();
	    uninitialized_copy(_a, that.begin(), that.end(), begin());
            assert(valid());}

        // ----------
        // destructor
        // ----------

        /**
* <your documentation>
*/
        ~MyDeque () {
            // <your code>
	    if(container){
		clear();
	 	_a.deallocate(container, myCapacity());
	    }
            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
* <your documentation>
*/
        MyDeque& operator = (const MyDeque& rhs) {
            // <your code>
	    if(this == &rhs)
		return *this;
	    if(rhs.size() == size())
		std::copy(rhs.begin(), rhs.end(), begin());
	    else if (rhs.size() < size()){
		std::copy(rhs.begin(), rhs.end(), begin());
		resize(rhs.size());
	    }
	    else if(rhs.size() <= myCapacity()){
		std::copy(rhs.begin(), rhs.begin() + size(), begin());
		dequeSize = uninitialized_copy(_a, rhs.begin() + size(), rhs.end(), end());
	    }
	    else{
		clear();
		reserve(rhs.size());
		dequeSize = uninitialized_copy(_a, rhs.begin(), rhs.end(), begin());
	    }
            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
* <your documentation>
*/
        reference operator [] (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            return begin()[index];}

        /**
* <your documentation>
*/
        const_reference operator [] (size_type index) const {
            return const_cast<MyDeque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
* <your documentation>
*/
        reference at (size_type index) throw (std::out_of_range){
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            if(index >= size())
		throw std::out_of_range("deque::_M_range_check");
            return (*this)[index];}

        /**
* <your documentation>
*/
        const_reference at (size_type index) const {
            return const_cast<MyDeque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
* <your documentation>
*/
        reference back () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            assert(!empty());
            return *(end() - 1);}

        /**
* <your documentation>
*/
        const_reference back () const {
            return const_cast<MyDeque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
* <your documentation>
*/
        iterator begin () {
            // <your code>
	    size_t t = 0;
            return iterator(*this, t);}

        /**
* <your documentation>
*/
        const_iterator begin () const {
            // <your code>
	    size_t t = 0;
            return const_iterator(*this, t);}

        // -----
        // clear
        // -----

        /**
* <your documentation>
*/
        void clear () {
            // <your code>
	    resize(0);
            assert(valid());}

        // -----
        // empty
        // -----

        /**
* <your documentation>
*/
        bool empty () const {
            return size() == 0;}

        // ---
        // end
        // ---

        /**
* <your documentation>
*/
        iterator end () {
            // <your code>
	    size_t t = size();
            return iterator(*this, *t);}

        /**
* <your documentation>
*/
        const_iterator end () const {
            // <your code>
	    size_t t = size();
            return const_iterator(*this, *t);}

        // -----
        // erase
        // -----

        /**
* <your documentation>
*/
        iterator erase (iterator) {
            // <your code>
            assert(valid());
            return iterator();}

        // -----
        // front
        // -----

        /**
* <your documentation>
*/
        reference front () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            assert(!empty());
            return *begin();}

        /**
* <your documentation>
*/
        const_reference front () const {
            return const_cast<MyDeque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
* <your documentation>
*/
        iterator insert (iterator, const_reference) {
            // <your code>
            assert(valid());
            return iterator();}

        // ---
        // pop
        // ---

        /**
* <your documentation>
*/
        void pop_back () {
            assert(!empty());
            resize(size() - 1);
            assert(valid());}

        /**
* <your documentation>
*/
        void pop_front () {
            // <your code>
            assert(valid());}

        // ----
        // push
        // ----

        /**
* <your documentation>
*/
        void push_back (const_reference v) {
            resize(size() + 1, v);
            assert(valid());
        }

        /**
* <your documentation>
*/
        void push_front (const_reference v) {
            // <your code>
            assert(valid());}

        // ------
        // resize
        // ------

//reserve

/*void reserve(size_type c){
	if(c > myCapacity()){
		MyDeque x(*this, c, second_a);
		swap(x);
	}
}*/

        /**
* <your documentation>
*/
        void resize (size_type s, const_reference v = value_type()) {
            if (s == size())
                return;
            else if (s < size()){
                iterator it  = destroy(_a, begin() + s, end());
	        dequeSize = (int*)s;
	    }
            else if (s <= myCapacity()){
                iterator it = uninitialized_fill(_a, end(), begin() + s, v);
		dequeSize = (int*)s;
	    }
            else {
		if(s > (2 * size())){
			MyDeque deque (s, v);
			swap(deque);
		}
		else{
			MyDeque deque (2* size(), v);
			swap(deque);
		}
	     }
            assert(valid());}

        // ----
        // size
        // ----

        /**
* <your documentation>
*/
        size_type size () const {
            // <your code>
            return dequeSize - container;}




//capacity

	size_type myCapacity() const{
		return capacity - container;
	}
        // ----
        // swap
        // ----

        /**
* <your documentation>
*/
        void swap (MyDeque& that) {
            // <your code>
            if(_a == that._a){
		std::swap(container, that.container);
		std::swap(dequeSize, that.dequeSize);
		std::swap(capacity, that.capacity);
	    }
	    else{
		MyDeque x(*this);
		*this = that;
		that = x;
	    }
	    assert(valid());
}};

#endif // Deque_h
