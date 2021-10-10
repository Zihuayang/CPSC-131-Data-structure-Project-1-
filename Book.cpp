#include <cmath>                                                      // abs(), pow()
#include <iomanip>                                                    // quoted()
#include <iostream>
#include <string>
#include <type_traits>                                                // is_floating_point_v, common_type_t
#include <utility>                                                    // move()

#include "Book.hpp"

/*******************************************************************************
**  Constructors, assignments, and destructor
*******************************************************************************/

// Default and Conversion Constructor
Book::Book(std::string title, std::string author, std::string isbn, double price)
///////////////////////// TO-DO (2) //////////////////////////////
{}
/////////////////////// END-TO-DO (2) ////////////////////////////




// Copy constructor
Book::Book(Book const & other)
///////////////////////// TO-DO (3) //////////////////////////////
{}
/////////////////////// END-TO-DO (3) ////////////////////////////




// Copy Assignment Operator
Book & Book::operator=(Book const & rhs) &
///////////////////////// TO-DO (5) //////////////////////////////
{}
/////////////////////// END-TO-DO (5) ////////////////////////////



// Destructor
Book::~Book() noexcept
///////////////////////// TO-DO (7) //////////////////////////////
{}
/////////////////////// END-TO-DO (7) ////////////////////////////








/*******************************************************************************
**  Accessors
*******************************************************************************/

// isbn() const
std::string const & Book::isbn() const &
{
	///////////////////////// TO-DO (8) //////////////////////////////
	/////////////////////// END-TO-DO (8) ////////////////////////////
}




// title() const
std::string const & Book::title() const &
{
	///////////////////////// TO-DO (9) //////////////////////////////
	/////////////////////// END-TO-DO (9) ////////////////////////////
}




// author() const
std::string const & Book::author() const &
{
	///////////////////////// TO-DO (10) //////////////////////////////
	/////////////////////// END-TO-DO (10) ////////////////////////////
}



// price() const
double Book::price() const &
{
	///////////////////////// TO-DO (11) //////////////////////////////
	/////////////////////// END-TO-DO (11) ////////////////////////////
}




// isbn()
std::string Book::isbn() &&
{
	///////////////////////// TO-DO (12) //////////////////////////////
	/////////////////////// END-TO-DO (12) ////////////////////////////
}




// title()
std::string Book::title() &&
{
	///////////////////////// TO-DO (13) //////////////////////////////
	/////////////////////// END-TO-DO (13) ////////////////////////////
}




// author()
std::string Book::author() &&
{
	///////////////////////// TO-DO (14) //////////////////////////////
	/////////////////////// END-TO-DO (14) ////////////////////////////
}








/*******************************************************************************
**  Modifiers
*******************************************************************************/

// isbn()
Book & Book::isbn(std::string newIsbn) &
{
	///////////////////////// TO-DO (15) //////////////////////////////
	/////////////////////// END-TO-DO (15) ////////////////////////////
}




// title()
Book & Book::title(std::string newTitle) &
{
	///////////////////////// TO-DO (16) //////////////////////////////
	/////////////////////// END-TO-DO (16) ////////////////////////////
}




// author()
Book & Book::author(std::string newAuthor) &
{
	///////////////////////// TO-DO (17) //////////////////////////////
	/////////////////////// END-TO-DO (17) ////////////////////////////
}




// price()
Book & Book::price(double newPrice) &
{
	///////////////////////// TO-DO (18) //////////////////////////////
	/////////////////////// END-TO-DO (18) ////////////////////////////
}



/*******************************************************************************
**  Relational Operators
*******************************************************************************/


// operator==
bool Book::operator==(const Book & rhs) const noexcept
{
	// All attributes must be equal for the two books to be equal to the other.  This can be done in any order, so put the quickest
	// and then the most likely to be different first.

	///////////////////////// TO-DO (20) //////////////////////////////
	/////////////////////// END-TO-DO (20) ////////////////////////////
}

// operator!=
bool Book::operator!=(const Book & rhs) const noexcept
{
	// Two books are unequal if any of their attributes are unequal.

	///////////////////////// TO-DO (20) //////////////////////////////
	/////////////////////// END-TO-DO (20) ////////////////////////////
}

// operator<
bool Book::operator<(const Book & rhs) const noexcept
{
	// Books are ordered (sorted) by ISBN, author, title, then price.

	///////////////////////// TO-DO (20) //////////////////////////////
	/////////////////////// END-TO-DO (20) ////////////////////////////
}

// operator<=
bool Book::operator<=(const Book & rhs) const noexcept
{
	// Books are ordered (sorted) by ISBN, author, title, then price.

	///////////////////////// TO-DO (20) //////////////////////////////
	/////////////////////// END-TO-DO (20) ////////////////////////////
}

// operator>
bool Book::operator>(const Book & rhs) const noexcept
{
	// Books are ordered (sorted) by ISBN, author, title, then price.

	///////////////////////// TO-DO (20) //////////////////////////////
	/////////////////////// END-TO-DO (20) ////////////////////////////
}

// operator>=
bool Book::operator>=(const Book & rhs) const noexcept
{
	// Books are ordered (sorted) by ISBN, author, title, then price.

	///////////////////////// TO-DO (20) //////////////////////////////
	/////////////////////// END-TO-DO (20) ////////////////////////////
}







/*******************************************************************************
**  Insertion and Extraction Operators
*******************************************************************************/

// operator>>
std::istream & operator>>(std::istream & stream, Book & book)
{
	///////////////////////// TO-DO (21) //////////////////////////////
	/// A lot can go wrong when reading from streams - no permission, wrong types, end of file, etc. Minimal exception guarantee says
	/// there should be no side affects if an error or exception occurs, so let's do our work in a local object and move it into place
	/// at the end if all goes well.
	///
	/// This function should be symmetrical with operator<< below.  Read what your write, and write what you read
	///
	///
	/// Assume fields are separated by commas and string attributes are enclosed with double quotes.  For example:
	///    ISBN             | Title                 | Author             | Price
	///    -----------------+-----------------------+--------------------+-----
	///    "9789998287532",   "Over in the Meadow",   "Ezra Jack Keats",   91.11
	///
	///
	/// Hint:  Use std::quoted to read and write quoted strings.  See
	///        1) https://en.cppreference.com/w/cpp/io/manip/quoted
	///        2) https://www.youtube.com/watch?v=Mu-GUZuU31A


	/////////////////////// END-TO-DO (21) ////////////////////////////
}




// operator<<
std::ostream & operator<<(std::ostream & stream, const Book & book)
{
	///////////////////////// TO-DO (22) //////////////////////////////
	/// This function should be symmetrical with operator>> above.  Read what your write, and write what you read
	/////////////////////// END-TO-DO (22) ////////////////////////////
}