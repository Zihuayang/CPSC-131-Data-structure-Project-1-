#include <algorithm>    // find(), move(), move_backward(), equal(), swap(), lexicographical_compare()
#include <cstddef>      // size_t
#include <initializer_list>
#include <iomanip>      // setw()
#include <iterator>     // distance(), next()
#include <stdexcept>    // logic_error
#include <string>

#include "Book.hpp"
#include "BookList.hpp"



// As a rule, I strongly recommend avoiding macros, unless there is a compelling reason - this is such a case. This really does need
// to be a macro and not a function due to the way the preprocessor expands the source code location information.  It's important to
// have these expanded where they are used, and not here. But I just can't bring myself to writing this, and getting it correct,
// everywhere it is used.  Note:  C++20 will change this technique with the introduction of the source_location class. Also note the
// usage of having the preprocessor concatenate two string literals separated only by whitespace.
#define exception_location "\n detected in function \"" + std::string(__func__) +  "\""    \
                           "\n at line " + std::to_string( __LINE__ ) +                    \
                           "\n in file \"" __FILE__ "\""






/*******************************************************************************
**  Private implementations, types, and objects
*******************************************************************************/
bool BookList::containersAreConsistent() const
{
    // Sizes of all containers must be equal to each other
    if (_books_array_size != _books_vector.size()
        || _books_array_size != _books_dl_list.size()
        || _books_array_size != books_sl_list_size()) return false;

    // Element content and order must be equal to each other
    auto current_array_position = _books_array.cbegin();
    auto current_vector_position = _books_vector.cbegin();
    auto current_dl_list_position = _books_dl_list.cbegin();
    auto current_sl_list_position = _books_sl_list.cbegin();

    while (current_vector_position != _books_vector.cend())
    {
        if (*current_array_position != *current_vector_position
            || *current_array_position != *current_dl_list_position
            || *current_array_position != *current_sl_list_position) return false;

        // Advance the iterators to the next element in unison
        ++current_array_position;
        ++current_vector_position;
        ++current_dl_list_position;
        ++current_sl_list_position;
    }

    return true;
}




// Calculate the size of the singly linked list on demand
std::size_t BookList::books_sl_list_size() const
{
    ///////////////////////// TO-DO (1) //////////////////////////////
      /// Some implementations of a singly linked list maintain the size (number of elements in the list).  std::forward_list does
      /// not. The size of singly linked list must be calculated on demand by walking the list from beginning to end counting the
      /// number of elements visited.  The STL's std::distance() function does that, or you can write your own loop.
      //https://www.geeksforgeeks.org/find-length-of-a-linked-list-iterative-and-recursive/
    
    return std::distance(_books_sl_list.begin(), _books_sl_list.end());
    
      
      /////////////////////// END-TO-DO (1) ////////////////////////////
}











/*******************************************************************************
**  Constructors, destructor, and assignment operators
*******************************************************************************/
// Rule of 6 - I wanted a tailored assignment operator, so I should (best practice) write the other too
BookList::BookList() = default;

BookList::BookList(const BookList & other) = default;
BookList::BookList(BookList && other) = default;

BookList& BookList::operator=(BookList    rhs) { swap(rhs); return *this; }
BookList& BookList::operator=(BookList && rhs) = default;

BookList::~BookList() = default;



BookList::BookList(const std::initializer_list<Book> &initList)
{
    for (auto&& book : initList)   insert(book, Position::BOTTOM);

    // Verify the internal book list state is still consistent amongst the four containers
    if (!containersAreConsistent())   throw BookList::InvalidInternalState_Ex("Container consistency error" exception_location);
}



BookList& BookList::operator+=(const std::initializer_list<Book> &rhs)
{
    ///////////////////////// TO-DO (2) //////////////////////////////
      /// Concatenate the right hand side book list of books to this list by repeatedly inserting at the bottom of this book list.
      /// The input type is a container of books accessible with iterators like all the other containers.  The constructor above gives
      /// an example.  Use BookList::insert() to insert at the bottom.

    for (auto&& book : rhs) 
    {
        BookList::insert(book, Position::BOTTOM);
    }

    /////////////////////// END-TO-DO (2) ////////////////////////////

    // Verify the internal book list state is still consistent amongst the four containers
    if (!containersAreConsistent())   throw BookList::InvalidInternalState_Ex("Container consistency error" exception_location);
    return *this;
}



BookList& BookList::operator+=(const BookList & rhs)
{
    ///////////////////////// TO-DO (3) //////////////////////////////
      /// Concatenate the right hand side book list of books to this list by repeatedly inserting at the bottom of this book list.
      /// All the rhs containers (array, vector, list, and forward_list) contain the same information, so pick just one to traverse.
      /// Walk the container you picked inserting its books to the bottom of this book list. Use BookList::insert() to insert at the
      /// bottom.

    for (auto&& book : rhs._books_vector) 
    {
        BookList::insert(book, Position::BOTTOM);
    }

    /////////////////////// END-TO-DO (3) ////////////////////////////

    // Verify the internal book list state is still consistent amongst the four containers
    if (!containersAreConsistent())   throw BookList::InvalidInternalState_Ex("Container consistency error" exception_location);
    return *this;
}







/*******************************************************************************
**  Queries
*******************************************************************************/
std::size_t BookList::size() const
{
    // Verify the internal book list state is still consistent amongst the four containers
    if (!containersAreConsistent())   throw BookList::InvalidInternalState_Ex("Container consistency error" exception_location);

    ///////////////////////// TO-DO (4) //////////////////////////////
      /// All the containers are the same size, so pick one and return the size of that.  Since the forward_list has to calculate the
      /// size on demand, stay away from using that one.

    return _books_vector.size();
    /////////////////////// END-TO-DO (4) ////////////////////////////
}



std::size_t BookList::find(const Book & book) const
{
    // Verify the internal book list state is still consistent amongst the four containers
    if (!containersAreConsistent())   throw BookList::InvalidInternalState_Ex("Container consistency error" exception_location);

    ///////////////////////// TO-DO (5) //////////////////////////////
      /// Locate the book in this book list and return the zero-based position of that book.  If the book does not exist, return the
      /// size of this book list as an indicator the book does not exist.  The book will be in the same position in all the containers
      /// (array, vector, list, and forward_list) so pick just one of those to search.  The STL provides the find() function that is a
      /// perfect fit here, but you may also write your own loop.
  
    size_t pos = size();
    
    for (int i = 0; i < size(); i++)
    {
        if (_books_vector[i] == book)
        {
            pos = i;
        }
    }

    return pos;

    /////////////////////// END-TO-DO (5) ////////////////////////////
}












/*******************************************************************************
**  Mutators
*******************************************************************************/
BookList& BookList::insert(const Book & book, Position position)
{
    // Convert the TOP and BOTTOM enumerations to an offset and delegate the work
    if (position == Position::TOP)  insert(book, 0);
    else if (position == Position::BOTTOM)  insert(book, size());
    else                                     throw std::logic_error("Unexpected insertion position" exception_location);  // Programmer error.  Should never hit this!
    return *this;
}



BookList& BookList::insert(const Book & book, std::size_t offsetFromTop)       // insert new book at offsetFromTop, which places it before the current book at offsetFromTop
{
    // Validate offset parameter before attempting the insertion.  std::size_t is an unsigned type, so no need to check for negative
    // offsets, and an offset equal to the size of the list says to insert at the end (bottom) of the list.  Anything greater than the
    // current size is an error.
    if (offsetFromTop > size())   throw InvalidOffset_Ex("Insertion position beyond end of current list size" exception_location);


    /**********  Prevent duplicate entries  ***********************/
    ///////////////////////// TO-DO (6) //////////////////////////////
      /// Silently discard duplicate items from getting added to the book list.  If the to-be-inserted book is already in the list,
      /// simply return.

    if (find(book) == size())
    {
        return *this;
    }

    /////////////////////// END-TO-DO (6) ////////////////////////////




    // Inserting into the book list means you insert the book into each of the containers (array, vector, list, and forward_list).
    // Because the data structure concept is different for each container, the way a book gets inserted is a little different for
    // each.  You are to insert the book into each container such that the ordering of all the containers is the same.  A check is
    // made at the end of this function to verify the contents of all four containers are indeed the same.


    /**********  Insert into array  ***********************/
    {
        ///////////////////////// TO-DO (7) //////////////////////////////
          /// Unlike the other containers, std::array has no insert() function, so you have to write it yourself. Insert into the array
          /// by shifting all the items at and after the insertion point (offsetFromTop) to the right opening a gap in the array that
          /// can be populated with the given book.  Remember that arrays have fixed capacity and cannot grow, so make sure there is
          /// room in the array for another book before you start by verifying _books_array_size is less than _books_array.size().  If
          /// not, throw CapacityExceeded_ex.  Also remember that you must keep track of the number of valid books in your array, so
          /// don't forget to adjust _books_array_size.
          ///
          /// open a hole to insert new book by shifting to the right everything at and after the insertion point.
          /// For example:  a[8] = a[7];  a[7] = a[6];  a[6] = a[5];  and so on.
          /// std::move_backward will be helpful, or write your own loop.
          ///
          /// In our Sequence Container Implementation Examples, see function Vector::insert() in "Vector (normal)/Vector.hpp" for a
          /// "std::move_backward" example and in "Vector (simplified)/Vector.hpp" for a "write your own loop" example.  Also see
          /// RationalArray::insert() in RationalArray.cpp in our Rational Number Case Study examples.

        if (_books_array_size < _books_array.size())
        {
            for (int i = _books_array_size; i > offsetFromTop; i--)
            {
                _books_array[i] = _books_array[i - 1];
            }

            _books_array[offsetFromTop] = book;
            _books_array_size++;
        }
        else 
        {
            throw BookList::CapacityExceeded_Ex("Capacity Exceeded" exception_location);
        }

        


        /////////////////////// END-TO-DO (7) ////////////////////////////
    }  // Insert into array



    /**********  Insert into vector  **********************/
    {
        ///////////////////////// TO-DO (8) //////////////////////////////
          /// The vector STL container std::vector has an insert function, which can be directly used here.  But that function takes a
          /// pointer (or more accurately, an iterator) that points to the book to insert before.  You need to convert the zero-based
          /// offset from the top to an iterator by advancing _books_vector.begin() offsetFromTop times.  The STL has a function called
          /// std::next() that does that, or you can use simple pointer arithmetic to calculate it.
          ///
          /// Behind the scenes, std::vector::insert() shifts to the right everything at and after the insertion point, just like you
          /// did for the array above.

        std::next(_books_vector.begin(), offsetFromTop);

        _books_vector.insert(_books_vector.begin(), book);

        /////////////////////// END-TO-DO (8) ////////////////////////////
    } // Insert into vector



    /**********  Insert into doubly linked list  **********/
    {
        ///////////////////////// TO-DO (9) //////////////////////////////
          /// The doubly linked list STL container std::list has an insert function, which can be directly used here.  But that function
          /// takes a pointer (or more accurately, an iterator) that points to the book to insert before.  You need to convert the
          /// zero-based offset from the top to an iterator by advancing _books_dl_list.begin() offsetFromTop times.  The STL has a
          /// function called std::next() that does that, or you can write your own loop.
        
        std::next(_books_dl_list.begin(),offsetFromTop);

        _books_dl_list.insert(_books_dl_list.begin(), book);
        
        /////////////////////// END-TO-DO (9) ////////////////////////////
    } // Insert into doubly linked list



    /**********  Insert into singly linked list  **********/
    {
        ///////////////////////// TO-DO (10) //////////////////////////////
          /// The singly linked list STL container std::forward_list has an insert function, which can be directly used here.  But that
          /// function inserts AFTER the book pointed to, not before like the other containers.  A singly linked list cannot look
          /// backwards, only forward.  You need to convert the zero-based offset from the top to an iterator by advancing
          /// _books_sl_list.before_begin() offsetFromTop times.  The STL has a function called std::next() that does that, or you can
          /// write your own loop.

        std::next(_books_sl_list.begin(), offsetFromTop - 1);

        _books_sl_list.insert_after(_books_sl_list.begin(), book);

        /////////////////////// END-TO-DO (10) ////////////////////////////
    } // Insert into singly linked list

    // Verify the internal book list state is still consistent amongst the four containers
    if (!containersAreConsistent())   throw BookList::InvalidInternalState_Ex("Container consistency error" exception_location);
    return *this;
} // insert( const Book & book, std::size_t offsetFromTop )



BookList& BookList::remove(const Book & book)
{
    remove(find(book));
    return *this;
}



BookList& BookList::remove(std::size_t offsetFromTop)
{
    // Removing from the book list means you remove the book from each of the containers (array, vector, list, and forward_list).
    // Because the data structure concept is different for each container, the way an book gets removed is a little different for
    // each.  You are to remove the book from each container such that the ordering of all the containers is the same.  A check is
    // made at the end of this function to verify the contents of all four containers are indeed the same.

    if (offsetFromTop >= size())   return *this;                                          // no change occurs if (zero-based) offsetFromTop >= size()

    /**********  Remove from array  ***********************/
    {
        ///////////////////////// TO-DO (11) //////////////////////////////
          /// Close the hole created by shifting to the left everything at and after the remove point.
          /// For example:  a[5] = a[6];  a[6] = a[7];  a[7] = a[8];  and so on
          ///
          /// std::move() will be helpful, or write your own loop.  Also remember that you must keep track of the number of valid books
          /// in your array, so don't forget to adjust _books_array_size.
          ///
          /// In our Sequence Container Implementation Examples, see function Vector::erase() in "Vector (normal)/Vector.hpp" for a
          /// "std::move()" example and in "Vector (simplified)/Vector.hpp" for a "write your own loop" example.  Also see
          /// RationalArray::remove() in RationalArray.cpp in our Rational Number Case Study examples.

        for (int i = offsetFromTop; i < size(); i++)
        {
            _books_array[i] = _books_array[i + 1];
        }

        _books_array_size--;

        /////////////////////// END-TO-DO (11) ////////////////////////////
    } // Remove from array



    /**********  Remove from vector  **********************/
    {
        ///////////////////////// TO-DO (12) //////////////////////////////
          /// The vector STL container std::vector has an erase function, which can be directly used here.  But that function takes a
          /// pointer (or more accurately, an iterator) that points to the book to be removed.  You need to convert the zero-based
          /// offset from the top to an iterator by advancing _books_vector.begin() offsetFromTop times.  The STL has a function called
          /// std::next() that does that, or you can use simple pointer arithmetic to calculate it.
          ///
          /// Behind the scenes, std::vector::erase() shifts to the left everything after the insertion point, just like you did for the
          /// array above.

        std::next(_books_vector.begin(), offsetFromTop);

        _books_vector.erase(_books_vector.begin());

        /////////////////////// END-TO-DO (12) ////////////////////////////
    } // Remove from vector



    /**********  Remove from doubly linked list  **********/
    {
        ///////////////////////// TO-DO (13) //////////////////////////////
          /// The doubly linked list STL container std::list has an erase function, which can be directly used here.  But that function
          /// takes a pointer (or more accurately, an iterator) that points to the book to remove.  You need to convert the zero-based
          /// offset from the top to an iterator by advancing _books_dl_list.begin() offsetFromTop times.  The STL has a function called
          /// std::next() that does that, or you can write your own loop.

        std::next(_books_dl_list.begin(), offsetFromTop);

        _books_dl_list.erase(_books_dl_list.begin());

        /////////////////////// END-TO-DO (13) ////////////////////////////
    } // Remove from doubly linked list



    /**********  Remove from singly linked list  **********/
    {
        ///////////////////////// TO-DO (14) //////////////////////////////
          /// The singly linked list STL container std::forward_list has an erase function, which can be directly used here.  But that
          /// function erases AFTER the book pointed to, not the one pointed to like the other containers.  A singly linked list cannot
          /// look backwards, only forward.  You need to convert the zero-based offset from the top to an iterator by advancing
          /// _books_sl_list.before_begin() offsetFromTop times.  The STL has a function called std::next() that does that, or you can
          /// write your own loop.

        std::next(_books_sl_list.begin(), offsetFromTop - 1);

        _books_sl_list.erase_after(_books_sl_list.begin());


        /////////////////////// END-TO-DO (14) ////////////////////////////
    } // Remove from singly linked list

    // Verify the internal book list state is still consistent amongst the four containers
    if (!containersAreConsistent())   throw BookList::InvalidInternalState_Ex("Container consistency error" exception_location);
    return *this;
} // remove( std::size_t offsetFromTop )



BookList& BookList::moveToTop(const Book & book)
{
    ///////////////////////// TO-DO (15) //////////////////////////////
      /// If the book exists, then remove and reinsert it.  Else do nothing.  Use BookList::find() to determine if the book exists in
      /// this book list.


    if (BookList::find(book))
    {
        BookList::remove(book);
        BookList::insert(book);
    }

    return *this;

    /////////////////////// END-TO-DO (15) ////////////////////////////
    // Verify the internal book list state is still consistent amongst the four containers
    if (!containersAreConsistent())   throw BookList::InvalidInternalState_Ex("Container consistency error" exception_location);
    return *this;
}



void BookList::swap(BookList & rhs) noexcept
{
    if (this == &rhs) return;

    _books_array.swap(rhs._books_array);
    _books_vector.swap(rhs._books_vector);
    _books_dl_list.swap(rhs._books_dl_list);
    _books_sl_list.swap(rhs._books_sl_list);

    std::swap(_books_array_size, rhs._books_array_size);
}












/*******************************************************************************
**  Insertion and Extraction Operators
*******************************************************************************/
std::ostream& operator<<(std::ostream & stream, const BookList & bookList)
{
    if (!bookList.containersAreConsistent())   throw BookList::InvalidInternalState_Ex("Container consistency error" exception_location);

    unsigned count = 0;
    stream << bookList.size();
    for (auto&& book : bookList._books_sl_list)   stream << '\n' << std::setw(5) << count++ << ":  " << book;
    stream << '\n';
    return stream;
}



std::istream& operator>>(std::istream & stream, BookList & bookList)
{
    if (!bookList.containersAreConsistent())   throw BookList::InvalidInternalState_Ex("Container consistency error" exception_location);
    std::string label_holder;
    size_t count;
    ///////////////////////// TO-DO (16) //////////////////////////////
      /// Read in data from a stream and use it to fill in the data of
      /// a BookList object. Create a function that will read the output created
      /// by the ostream operator above into an object properly.

    stream >> count;
    Book book;

    for (int i = 0; i < count; i++)
    {
        stream >> label_holder;
        stream >> book;
        bookList.insert(book, 0);
    }

    /////////////////////// END-TO-DO (16) ////////////////////////////

    return stream;
}












/*******************************************************************************
**  Relational Operators
*******************************************************************************/
int BookList::compare(const BookList & other) const
{
    if (!containersAreConsistent() || !other.containersAreConsistent())   throw BookList::InvalidInternalState_Ex("Container consistency error" exception_location);

    ///////////////////////// TO-DO (17) //////////////////////////////
      /// Compare this Booklist object with the other Booklist object.  Return a negative number if this Booklist object is less than
      /// the other Booklist object, zero if this Booklist object is equal to the other Booklist object, and a positive number if this
      /// Booklist object is greater than the other Booklist object.
      ///
      /// Compare the size of the two Booklist objects first.  If the sizes are different, you have your answer: if size() <
      /// other.size() then return -1, and so on. If the sizes are equal, then walk the lists from beginning to end comparing the
      /// contents of the two books, one from this Booklist and one from the other Booklist. The content of all the containers in a
      /// Booklist is the same - so pick one to walk. If the books are different, you have your answer. If you get all the way to the
      /// end of the list and found no books that are different, you have your answer:  the lists are equal.

    if (size() < other.size())
    {
        return -1;
    }

    if (size() > other.size())
    {
        return 1;
    }

    for (int i = 0; i < _books_vector.size(); i++)
    {
        if (_books_vector[i] < other._books_vector[i])
        {
            return -1;
        }

        if (_books_vector[i] > other._books_vector[i])
        {
            return 1;
        }
    }

    return 0;

    /////////////////////// END-TO-DO (17) ////////////////////////////
}



bool operator==(const BookList & lhs, const BookList & rhs) { return lhs.compare(rhs) == 0; }
bool operator!=(const BookList & lhs, const BookList & rhs) { return lhs.compare(rhs) != 0; }
bool operator< (const BookList & lhs, const BookList & rhs) { return lhs.compare(rhs) < 0; }
bool operator<=(const BookList & lhs, const BookList & rhs) { return lhs.compare(rhs) <= 0; }
bool operator> (const BookList & lhs, const BookList & rhs) { return lhs.compare(rhs) > 0; }
bool operator>=(const BookList & lhs, const BookList & rhs) { return lhs.compare(rhs) >= 0; }
