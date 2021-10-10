///////////////////////////////////////////////////////////////////////////////
// BookList_test.cpp
//
// Unit tests for code declared in BookList.hpp.
//
///////////////////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Book.hpp"
#include "BookList.hpp"

TEST(ConstructorsAndAssignment, Unused) {
  const Book book_1( "book_1" ),
           book_2( "book_2" ),
           book_3( "book_3" ),
           book_4( "book_4" ),
           book_5( "book_5" ),
           book_6( "book_6" );
  // default constructor
  {
    BookList list;
    EXPECT_EQ(0U, list.size());
  }

  // copy constructor and equality
  {
    BookList list1 = { book_2, book_3, book_1, book_4 };
    BookList list2( list1 );
    EXPECT_EQ(list1, list2);
  }

  // initializer list constructor
  {
    BookList list;
    list.insert( book_3                             );
    list.insert( book_4, BookList::Position::BOTTOM );
    list.insert( book_1, 1U                         );
    list.insert( book_2                           );

    BookList expected = {book_2, book_3, book_1, book_4};
    EXPECT_EQ(4U, list.size());
    EXPECT_EQ(expected, list);
  }
}

TEST(Accessors, Unused) {
  {
    const Book book_1( "book_1" ),
             book_2( "book_2" ),
             book_3( "book_3" ),
             book_4( "book_4" ),
             book_5( "book_5" ),
             book_6( "book_6" );

    BookList list1 = {book_2, book_3, book_1, book_4};
    list1 += {book_3, book_1, book_2, book_5};

    BookList list2 = {book_2, book_6, book_1, book_4};
    list1 += list2;

    BookList expected = {book_2, book_3, book_1, book_4, book_5, book_6};

    EXPECT_EQ(6U, list1.size());
    EXPECT_EQ(expected, list1);
    EXPECT_EQ(0U, list1.find(book_2));
    EXPECT_EQ(1U, list1.find(book_3));
    EXPECT_EQ(2U, list1.find(book_1));
    EXPECT_EQ(3U, list1.find(book_4));
    EXPECT_EQ(4U, list1.find(book_5));
    EXPECT_EQ(5U, list1.find(book_6));
    EXPECT_EQ(6U, list1.find(Book("Unincluded Book")));
  }
}

TEST(Modifiers, Unused) {
  const Book book_1( "book_1" ),
    book_2( "book_2" ),
    book_3( "book_3" ),
    book_4( "book_4" ),
    book_5( "book_5" ),
    book_6( "book_6" );
    {
      BookList list = {book_2, book_1, book_4, book_5, book_6};

      //Remove by item
      EXPECT_EQ(&list, &list.remove( book_1 ));
      EXPECT_EQ(list, BookList ({book_2, book_4, book_5, book_6}));//Remove middle

      EXPECT_EQ(&list, &list.remove( book_6 ));
      EXPECT_EQ(list, BookList ({book_2, book_4, book_5}));//Remove bottom

      EXPECT_EQ(&list, &list.remove( book_2 ));
      EXPECT_EQ(list, BookList ({book_4, book_5}));//Remove top

      EXPECT_EQ(&list, &list.remove( Book("not there") ));
      EXPECT_EQ(list, BookList ({book_4, book_5}));//Remove back
    }

    {
      BookList list = {book_2, book_1, book_4, book_5, book_6};

      //Remove by position
      EXPECT_EQ(&list, &list.remove( 1U ));
      EXPECT_EQ(list, BookList ({book_2, book_4, book_5, book_6}));//Remove middle

      EXPECT_EQ(&list, &list.remove( 3U ));
      EXPECT_EQ(list, BookList ({book_2, book_4, book_5}));//Remove bottom

      EXPECT_EQ(&list, &list.remove( 0U ));
      EXPECT_EQ(list, BookList ({book_4, book_5}));//Remove top

      EXPECT_EQ(&list, &list.remove( 10U ));
      EXPECT_EQ(list, BookList ({book_4, book_5}));//Remove bad index
    }

    {
      BookList list = {book_2, book_1, book_4, book_5, book_6};

      EXPECT_EQ(&list, &list.moveToTop( book_5        ));
      list.moveToTop( book_6        );
      list.moveToTop( book_6        );
      list.moveToTop( book_5        );
      list.moveToTop( book_4        );
      EXPECT_EQ(&list, &list.moveToTop( {"not there"} ));

      BookList expected = {book_4, book_5, book_6, book_2, book_1};

      EXPECT_EQ(expected, list);
    }

    {
      BookList list;

      try
      {
        for( unsigned i = 0; i < 100; ++i ) list.insert( Book{ "Book-" + std::to_string( i ) } );
        EXPECT_EQ(1,2);
      }
      catch ( const BookList::CapacityExceeded_Ex & )  // expected
      {
        EXPECT_EQ(1,1);
      }
    }

  {
      Book a("a"), b("b");
      BookList list = {b};

      // chaining
      EXPECT_EQ(&list, &(list.insert(a).moveToTop(b).remove(0)));
      EXPECT_EQ(list.size(), 1);
      EXPECT_EQ(list, BookList( {a} ));
  }

}

TEST(RelationalOperators, Unused) {
  // comparison operators
  {
    Book a("a"), b("b");
    BookList list_a = {a};
    BookList list_b = {b};
    EXPECT_TRUE(list_a < list_b);
    EXPECT_TRUE(list_a <= list_b);
    EXPECT_TRUE(list_a != list_b);
    EXPECT_TRUE(list_b > list_a);
    EXPECT_TRUE(list_b >= list_a);

    EXPECT_FALSE(list_b < list_a);
    EXPECT_FALSE(list_b <= list_a);
    EXPECT_FALSE(list_b == list_a);
    EXPECT_FALSE(list_a > list_b);
    EXPECT_FALSE(list_a >= list_b);

    BookList list_ab = {a, b};
    EXPECT_TRUE(list_a<list_ab);
    EXPECT_TRUE(list_a<=list_ab);
    EXPECT_TRUE(list_ab>list_a);
    EXPECT_TRUE(list_ab>=list_a);
    EXPECT_TRUE(list_ab!=list_a);
    EXPECT_FALSE(list_ab==list_a);
  }
}

TEST(StreamInsertion, Unused) {

  // returns reference to stream
  {
    std::stringstream ss;
    EXPECT_EQ(&ss, &(ss << Book()));
  }

  {
    std::stringstream ss;
    ss << BookList({ Book("title", "author", "isbn", 1.0) });
    EXPECT_EQ("1\n    0:  \"isbn\",\"title\",\"author\",1\n\n", ss.str());
  }

  {
    std::stringstream ss;
    ss << BookList();
    EXPECT_EQ("0\n", ss.str());
  }

  {
    std::stringstream ss;
    ss << BookList( {Book("Goodnight Moon", "Margaret Wise Brown", "9780064430173", 8.99)} );
    EXPECT_EQ("1\n    0:  \"9780064430173\",\"Goodnight Moon\",\"Margaret Wise Brown\",8.99\n\n", ss.str());
  }

  // multiple item insertion
  {
    std::stringstream ss;
    BookList list = { Book("A", "B", "123", 1.0),
      Book("D", "E", "456", 2.0),
      Book("G", "H", "789", 3.0)
    };
    ss << list;
    EXPECT_EQ("3\n    0:  \"123\",\"A\",\"B\",1\n\n    1:  \"456\",\"D\",\"E\",2\n\n    2:  \"789\",\"G\",\"H\",3\n\n",
              ss.str());
  }

  // chain item insertion - Detection of multiple lists
  {
    std::stringstream ss;
    BookList list_1 = { Book("A", "B", "123", 1.0),
      Book("D", "E", "456", 2.0) };
    BookList list_2 = {Book("G", "H", "789", 3.0)};

    ss << list_1 << list_2;
    EXPECT_EQ("2\n    0:  \"123\",\"A\",\"B\",1\n\n    1:  \"456\",\"D\",\"E\",2\n\n1\n    0:  \"789\",\"G\",\"H\",3\n\n",
              ss.str());
  }
}

TEST(StreamExtraction, Unused) {
  // returns reference to stream
  {
    std::stringstream ss("1\n 0:\"\",\"\",\"\",0\n");
    BookList b;
    EXPECT_EQ(&ss, &(ss >> b));
  }

  // opposite of insertion examples above

  {
    std::stringstream ss("1\n 0:  \"isbn\",\"title\",\"author\",1\n\n");
    BookList list;
    ss >> list;
    EXPECT_EQ(BookList({ Book("title", "author", "isbn", 1.0) }), list);
  }

  {
    std::stringstream ss("1\n 0: \"\",\"\",\"\",0\n");
    BookList list;
    ss >> list;
    EXPECT_EQ(BookList( {Book("", "", "", 0)}), list);
  }

  {
    std::stringstream ss("1\n 0:  \"9780064430173\",\"Goodnight Moon\",\"Margaret Wise Brown\",8.99\n\n");
    BookList list;
    ss >> list;
    EXPECT_EQ(BookList({ Book("Goodnight Moon", "Margaret Wise Brown", "9780064430173", 8.99) }), list);
  }

  {
    std::stringstream ss("3\n 0:  \"123\", \"A\", \"B\", 1\n 1:  \"456\", \"D\", \"E\", 2\n 2:  \"789\", \"G\", \"H\", 3\n\n");
    BookList list;
    ss >> list;
    EXPECT_EQ(list,BookList({ Book("A", "B", "123", 1.0),
      Book("D", "E", "456", 2.0),
      Book("G", "H", "789", 3.0)
    } ));
  }
  {
    std::stringstream ss("2\n 0:  \"123\", \"A\", \"B\", 1\n 1:  \"456\", \"D\", \"E\", 2\n\n1\n 2:  \"789\", \"G\", \"H\", 3\n");
    BookList list1, list2;
    ss >> list1 >> list2;
    EXPECT_EQ(list1,BookList({ Book("A", "B", "123", 1.0),
      Book("D", "E", "456", 2.0)}));

    EXPECT_EQ(list2,BookList({Book("G", "H", "789", 3.0)
    } ));
  }
}
