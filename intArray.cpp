/*
HANDOUT 2
Class IntArray
*/

//The following code would be in a header file
//intarray.h

#ifndef __INTARRAY__
#define __INTARRAY__

#include <iostream>
#include <iomanip> //For output formatting
#include <iterator> // for reverse_iterator
#include <algorithm> // for stl functions
using namespace std;

typedef int* iter;
typedef reverse_iterator<iter> rev_iterator;
typedef const int* const_iterator;
typedef reverse_iterator<const_iterator> const_rev_iterator;

class Array_Error {
private:
    string err_msg;
public:
    Array_Error(const string& s) : err_msg(s) {}
    string get_message() { return err_msg; }
};

class IntArray {
private:
    int* p; //pointer to int array data
    unsigned size; //size of the array (elements already in the array)
    unsigned capacity; // capacity of the array (max number of elements)

public:
    //Constructors
    IntArray(); //Default constructor
    IntArray(unsigned n, int val = 0);
    IntArray(const int* a, unsigned n);
    IntArray(const IntArray& a); //Copy constructor

    //Destructor
    ~IntArray();

    //Assignment operators
    IntArray& operator=(const IntArray& a);

    //Subscript operators
    int& operator[](unsigned pos);
    const int& operator[](unsigned pos) const; //const version

    //Size functions
    unsigned length() const { return size; }
    bool empty() const { return size == 0; }
    void resize(unsigned sz, int val = 0);



    //additional
    IntArray(IntArray &&a )noexcept;// move constructor
    IntArray(initializer_list<int> l); //Initializer list constructor
    template<class InputIterator>
    IntArray(InputIterator begin, InputIterator end); //range constructor
    IntArray& operator=( IntArray &&a)noexcept; // move operator
    void assign(int* a, unsigned n); // assign operator
    int* begin(); // begin
    const int* begin() const; // const begin
    int* end(); // end
    const int* end() const; // const end
    rev_iterator rbegin(); // rbegin
    const_rev_iterator rbegin() const; // const rbegin
    rev_iterator rend(); // rend
    const_rev_iterator rend() const; // const rend
    int front(); // front
    const int front() const; // const front
    int back(); // back
    const int back() const; // const back
    void insert(unsigned pos, int x); // insert x before pos
    void insert(unsigned pos, unsigned n, int x); //n x's
    void push_back(int x); // add x to end of array
    void pop_back(); // removes last element of array
    void erase(unsigned pos); // remove the element at pos
    void erase(unsigned first, unsigned last); // erase[first,last)
    void clear(); // clears the content of array, but the capacity stays the same
    unsigned cap(); // returns the number of possible elements
    void reserve(unsigned n); // enlarges capacity to n
    void swap(IntArray& a); // swaps data with IntArray a
    bool operator < (IntArray& a); // less than
    bool operator <= (IntArray& a); // less than or equal to
    bool operator >= (IntArray& a); // greater than or equal to
    bool operator > (IntArray& a); // greater than
    IntArray operator + (IntArray& a); // addition
    IntArray operator * (IntArray& a);// multiplication
};





//I/O functions
ostream& operator<<(ostream& out, const IntArray& a);
istream& operator>>(istream& in, IntArray& a);

//Relational operators
bool operator==(const IntArray& a1, const IntArray& a2);
bool operator!=(const IntArray& a1, const IntArray& a2);

//Default constructor, creates array of size 0
inline
IntArray::IntArray() : p(0), size(0), capacity(0) {}

//Creates array of n elements all initialized to val
inline
IntArray::IntArray(unsigned n, int val) : p(new int[n]), size(n), capacity(n)
{
    
    for (unsigned i = 0; i < n; i++) p[i] = val;
    // cout << size << " " << capacity << endl; // debug
}

//Creates a copy of integer array a
inline
IntArray::IntArray(const int* a, unsigned n) : p(new int[n]), size(n), capacity(n)
{
    for (unsigned i = 0; i < n; i++) p[i] = a[i];
    //cout << size << " " << capacity << endl; // debug
}

//Creates a copy of IntArray a
inline
IntArray::IntArray(const IntArray& a) : p(new int[a.capacity]), size(a.size), capacity(a.capacity)
{
    for (unsigned i = 0; i < size; i++) p[i] = a.p[i];
    cout << "copy constructor" << endl; // debug
    //cout << size << " " << capacity << endl;
}

//Destructor
inline
IntArray::~IntArray()
{
    delete[] p;
}

//Subscript operators

//The following works for const arrays
inline
const int& IntArray::operator[](unsigned pos) const
{
    if (pos >= size)
        throw(Array_Error("Out of range"));
    return(p[pos]);
}

//The following works for non-const arrays
inline
int& IntArray::operator[](unsigned pos)
{
    return const_cast<int&>(static_cast<const IntArray&>(*this)[pos]);
}






//additional
//move constructor
inline
IntArray::IntArray(IntArray&& a) noexcept : p(a.p), size(a.size), capacity(a.capacity)
{
    while (capacity < a.size) capacity *= 2;
    resize(capacity);
    a.p = NULL;
    a.size = 0;
    a.capacity = 0;
    cout << "move constructor" << endl; // debug
    //cout << size << " " << capacity << endl;
}

// initializer list constructor
IntArray::IntArray(initializer_list<int> a) : p(new int[a.size()]) 
{
    size = a.size();
    capacity = a.size();
    int i = 0;
    auto j = a.begin();
    while (i < size) p[i++] = *j++;

    cout << "initializer list constructor" << endl;
}

// range constructor
template<class InputIterator>
IntArray::IntArray(InputIterator begin, InputIterator end) : p(new int[distance(begin, end)]) 
{
    size = distance(begin, end);
    capacity = size;
    int i = 0;
    while (i < size) p[i++] = *begin++;

    cout << "range constructor" << endl;
}

//move operator
IntArray& IntArray::operator=( IntArray &&a)noexcept
{
    //size = a.size;
    //avoid self assignment
    //p = a.p;

    //cout << " move " << endl;
    //cout << size << capacity << endl;
    //cout << *this << endl;

    //a.size = 0;
    //a.capacity = 0;
    if (&a != this) {
        delete[] p;
        p = a.p;
        size = a.size;
        capacity = a.capacity;
        while (capacity < a.size) capacity *= 2;
    }
    a.p = 0;
    a.size = 0;
    a.capacity = 0;

    cout << "move operator" << endl; // debug
    
    return *this;
    
}

// assign operator
void IntArray::assign(int* a, unsigned n)
{
    if (n > capacity)
    {
        while (capacity < n) capacity *= 2;
    }

    for (int i = 0; i < n; i++)
    {
        p[i] = a[i];
    }

    size = n;
    cout << "assign operator" << endl;

}

// begin function
int* IntArray::begin() 
{
    int* ptr = &p[0];

    return ptr;
}

// const begin function
const int* IntArray::begin() const
{
    int* ptr = &p[0];

    return ptr;
}

// end function
int* IntArray::end()
{
    int* ptr = &p[size];
    //int* ptr2 = 0; // debug
    //int i = 0; // debug

    // debug
    /*while( i < capacity)
    {
        cout << &p[i] << endl;
        ptr2 = &p[i];
        i++;
    }*/

    //cout << ++ptr << endl; // debug
    

    return ptr;
}

// const end function
const int* IntArray::end() const
{
    int* ptr = &p[size];
    //int* ptr2 = 0; // debug
    //int i = 0; // debug

    // debug
    /*while( i < capacity)
    {
        cout << &p[i] << endl;
        ptr2 = &p[i];
        i++;
    }*/

    //cout << ++ptr << endl; // debug


    return ptr;
}

// rbegin
rev_iterator IntArray::rbegin()
{
    return rev_iterator(end());
}

// const rbegin
const_rev_iterator IntArray::rbegin() const
{
    return const_rev_iterator(end());
}

// rend
rev_iterator IntArray::rend()
{
    int* ptr = &p[0];

    ptr--;

    return rev_iterator(begin());
}

// const rend
const_rev_iterator IntArray::rend()const
{
    int* ptr = &p[0];

    ptr--;

    return const_rev_iterator(begin());
}

// front
int IntArray::front()
{
    return p[capacity - capacity];
}

// const front
const int IntArray::front() const
{
    return p[capacity - capacity];
}

// back
int IntArray::back()
{
    return p[size - 1];
}

// const back
const int IntArray::back() const
{
    return p[capacity - 1];
}

// insert x before pos
void IntArray::insert(unsigned pos, int x) 
{
    int i;
    //cout << size << " " << capacity << endl; // debug
    size++;
    //p[size] = 0;
    while (size >= capacity) capacity *= 2;
    resize(capacity);
    //cout << size << " " << capacity << endl; // debug

    for (i = (size-1); i >= pos; i--)
    {
        p[i] = p[i-1];
    }
    //if (i == 0) p[i + 1] = p[i];
    
    p[pos] = x;
    
}

// insert n x's
void IntArray::insert(unsigned pos, unsigned n, int x)
{
    int i;
    //cout << size << " " << capacity << endl; // debug
    size += n;
    while (size >= capacity) capacity *= 2;
    resize(capacity);

    for (i = (size - 1); (i-n) >= pos; i--)
    {
        //cout << "in" << endl;
        p[i] = p[i - n];
    }
    //if (i == 0) p[i + 1] = p[i];

    //cout << size << " " << capacity << endl; // debug
    //cout << i << endl; // debug
    i = pos;
    for (int ctr = 0; ctr < n ; ctr++)
    {
        //cout << "in" << endl; // debug
        p[i] = x;
        i++;
    }

}

// add x to end of array
void IntArray::push_back(int x)
{
    size++;
    while (size >= capacity) capacity *= 2;
    resize(capacity);
    p[size - 1] = x;
}

// removes last element of array
void IntArray::pop_back()
{
    size--;
}

// remove the element at pos
void IntArray::erase(unsigned pos)
{
    int i;

    for (i = pos; i < size; i++)
    {
        p[i] = p[i + 1];
    }
    size--;
}

// erase[first,last)
void IntArray::erase(unsigned first, unsigned last)
{
    // get displacement or number of elements to be removed
    int disp = last - first;

    for (int i = first; i < last; i++)
    {
        p[i] = p[i + disp];
    }

    size -= disp;

}

// clears the content of array, but the capacity stays the same
void IntArray::clear()
{
    size = 0;
    //cout << size << " " << capacity << endl; // debug
}

// returns the number of possible elements
unsigned IntArray::cap()
{
    return capacity;
}

// enlarges capacity to n
void IntArray::reserve(unsigned n)
{
    //cout << size << " " << capacity << endl; // debug
    capacity = n;
    //cout << size << " " << capacity << endl; // debug
}

// swaps data with IntArray a
void IntArray::swap(IntArray& a)
{
    IntArray tmp = a;
    int sz = a.size;

    int i = 0;
    //cout << size << " " << capacity << endl; // debug
    while (size >= a.capacity) a.capacity *= 2;
    resize(a.capacity);

    while (a.size >= capacity) capacity *= 2;
    resize(capacity);


    for (int i = 0; i < size; i++)
    {
        a[i] = p[i];
    }

    for (int i = 0; i < a.size; i++)
    {
        p[i] = tmp[i];
    }

    a.size = size;
    size = sz;
    
}

// less than
bool IntArray::operator < (IntArray& a)
{
    bool ans = false;
    int sz = 0;

    if (size > a.size)
    {
        sz = a.size;
    }
    else
    {
        sz = size;
    }

    for (int i = 0; i < sz; i++)
    {
        //cout << p[i] << endl; // debug
        //cout << a.p[i] << endl; // debug
        if (p[i] < a.p[i])
        {
            ans = true;
            return ans;
        }
        else if (p[i] > a.p[i])
        {
            return ans;
        }
    }

    
}

// less than or equal to
bool IntArray::operator <= (IntArray& a)
{
    bool ans = false;
    int sz = 0;

    if (size > a.size)
    {
        sz = a.size;
    }
    else
    {
        sz = size;
    }

    for (int i = 0; i < sz; i++)
    {
        //cout << p[i] << endl; // debug
        //cout << a.p[i] << endl; // debug
        if (p[i] <= a.p[i])
        {
            ans = true;
            return ans;
        }
        else if (p[i] > a.p[i])
        {
            return ans;
        }
    }


}

//greater than or equal to
bool IntArray::operator >= (IntArray& a)
{
    bool ans = false;
    int sz = 0;

    if (size > a.size)
    {
        sz = a.size;
    }
    else
    {
        sz = size;
    }

    for (int i = 0; i < sz; i++)
    {
        //cout << p[i] << endl; // debug
        //cout << a.p[i] << endl; // debug
        if (p[i] >= a.p[i])
        {
            ans = true;
            return ans;
        }
        else if (p[i] < a.p[i])
        {
            return ans;
        }
    }


}

//greater than
bool IntArray::operator > (IntArray& a)
{
    bool ans = false;
    int sz = 0;

    if (size > a.size)
    {
        sz = a.size;
    }
    else
    {
        sz = size;
    }

    for (int i = 0; i < sz; i++)
    {
        //cout << p[i] << endl; // debug
        //cout << a.p[i] << endl; // debug
        if (p[i] > a.p[i])
        {
            ans = true;
            return ans;
        }
        else if (p[i] < a.p[i])
        {
            return ans;
        }
    }


}

// addition
IntArray IntArray::operator + (IntArray& a)
{
    if (size != a.size)
    {
        cout << "size are not the same. Cant add!" << endl;
        return *this;
    }
    for (int i = 0; i < size; i++)
    {
        p[i] += a.p[i];
    }
    return *this;
}

// multiplication
IntArray IntArray::operator * (IntArray& a)
{
    if (size != a.size)
    {
        cout << "size are not the same. Cant multiply!" << endl;
        return *this;
    }
    for (int i = 0; i < size; i++)
    {
        p[i] *= a.p[i];
    }
    return *this;
}

#endif





//The following code would be in a .cpp file
//intarray.cpp

//Assignment operators
IntArray& IntArray::operator=(const IntArray& a)
{
    if (&a != this) { //Avoids self-assignment
        delete[] p;
        p = new int[a.capacity];
        size = a.size;
        capacity = a.capacity;
        for (unsigned i = 0; i < capacity; i++) p[i] = a.p[i];
    }
    return *this;
}

//Resize array, initialize new elements to val
void IntArray::resize(unsigned cp, int val)
{
    int* temp = new int[cp];
    unsigned i;
    //unsigned cap = capacity;

    //cout << sz << " " << val << " " << cap <<  endl; // debug

    // increase capacity if new size > current capacity
    //while (sz > cap) cap *= 2;

    //cout << size << " " << val << " " << capacity << endl; // debug

    if (cp > size) { //Array is increasing in size
        for (i = 0; i < size; i++)
        {
            
            temp[i] = p[i];  // i keeps the math changes after the for loop because it is initialized outside for loop
            
        }
        if (val != 0) for (; i < cp; i++) temp[i] = val;

    }
    else { //Array is decreasing in size
        for (i = 0; i < cp; i++) temp[i] = p[i];
    }
    delete[] p;
    p = temp;
    size = i;

    if (cp>capacity) capacity = cp;

    //cout << size << capacity << endl; // debug
}

//I/O functions
ostream& operator<<(ostream& out, const IntArray& a)
{
    unsigned size = a.length();

    for (unsigned i = 0; i < size; i++)
        out << setw(6) << a[i];
    return out;
}

istream& operator>>(istream& in, IntArray& a)
{
    unsigned size = a.length();

    for (unsigned i = 0; i < size; i++)
        in >> a[i];
    return in;
}

//Relational operators
bool operator==(const IntArray& a1, const IntArray& a2)
{
    bool equal = false;

    if (a1.length() == a2.length()) 
    {
        unsigned size = a1.length();
        unsigned i;

        for (i = 0; i < size && a1[i] == a2[i]; i++)
            ;
        if (i == size) equal = true;
    }
    return equal;
}

bool operator!=(const IntArray& a1, const IntArray& a2)
{
    return !(a1 == a2);
}







int main() {
    int arr[4] = { 1,6,3,5 };
    IntArray a(arr, 4);
    IntArray b(6);

    for (int i = 0; i < 6; i++)
        b[i] = 3 * i * i - 4 * i + 2;

    // copy constructor
    IntArray c(b);
    IntArray f(c);

    // move constructor
    cout << "move c to d" << endl;
    IntArray d = (IntArray&&)c;

    //initializer list constructor
    IntArray e{ 1,2,3,4,5,6,7,8,9,10 };
    IntArray g{ 1,2,3,4};
    IntArray h{ 1,2,3,4,5,6,7,8,9,10 };
    
    // move operator
    cout << "move d to c" << endl;
    c = (IntArray&&)d;

    // assign operator
    cout << "assign arr[4] to c" << endl;
    c.assign(arr, 4);

    //insert x before pos
    b.insert(1, 100);

    // insert n x's
    e.insert(2, 3, 100);

    // add element to the end of array
    e.push_back(100);

    // remove last element from the end of array
    e.pop_back();

    // remove element in pos
    e.erase(5);

    // remove element in a range 
    e.erase(5, 9);

    // clear array, but leave capacity the same
    f.clear();

    // reserve number of slots for capacity
    f.reserve(50);

    //return capacity
    cout << "Aray a capacity: " << a.cap() << endl;

    //swap elements of 2 IntArrays
    cout << "swap e and d" << endl;
    b.swap(e);

    cout << "Array a:" << a << endl;
    cout << "Array b:" << b << endl;
    cout << "Array c:" << c << endl;
    cout << "Array d:" << d << endl;
    cout << "Array e:" << e << endl;
    cout << "Array f:" << f << endl;
    cout << "Array g:" << g << endl;
    cout << "Array h:" << h << endl;

    if (b == c)
        cout << "Arrays b and c are equal\n\n";
    if (b < a)
        cout << "Array b is less than array a \n\n";
    if (b <= a)
        cout << "Array b is less than or equal to array a \n\n";
    if (a >= b)
        cout << "Array a is greater than or equal to array b \n\n";
    if (a > b)
        cout << "Array a is greater than array b \n\n";

    cout << "a+c: " << a + c << endl;
    cout << "a*c: " << a * c << endl;

    d.resize(3,3);
    //cout << "d: " << d << endl; // debug
    cin >> d;
    cout << "Array d:" << d << endl;

    cout << "BEGIN - address of the first element of a: " << a.begin() << endl;
    cout << "END - address of the memory space after a: " << a.end() << endl;
    cout << "RBEGIN - address of the last element of a: " <<  *a.rbegin() << endl;
    cout << "REND - address of the memory space before a: " << *a.rend() << endl;
    cout << "FRONT - value of the first element of a: " << a.front() << endl;
    cout << "BACK - value of the last element of a: " << a.back() << endl;
    cout << endl;

    sort(a.begin(), a.end());
    cout << "STD sort: " << a << endl;

    copy(g.begin(), g.end(), a.begin());
    cout << "STD copy g to a: " << a << endl;

    reverse_copy(a.begin(), a.end(), a.begin());
    cout << "STD reverse_copy a to a " << a << endl;

    copy_backward(a.begin(), a.end(), b.end());
    cout << "STD copy_backward from a to b: " << b << endl;

    fill(a.begin(), a.end(), 100);
    cout << "STD fill a with 100's: " << a << endl;

    remove_copy(c.begin(), c.end(), c.begin(),6);
    cout << "STD remove_copy c to c while removing 6's: " << c << endl;

    copy_n(a.begin(), 4, b.begin());
    cout << "STD copy_n a to b: " << b << endl;

    transform(a.begin(), a.end(), c.begin(), h.begin(), [](int i, int j) {return i + j; });
    cout << "STD transform: " << h << endl;


    return 0;
}
