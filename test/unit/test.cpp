#include "InlineVector.hpp"
#include <gtest/gtest.h>

class TestVec : public testing::Test
{
};

TEST_F (TestVec, push_back)
{
  InlineVector<int, 10> test_vec;

  test_vec.push_back (1);
  test_vec.push_back (2);
  test_vec.push_back (3);
  test_vec.push_back (4);
  test_vec.push_back (5);
  test_vec.push_back (6);
  test_vec.push_back (7);
  test_vec.push_back (8);
  test_vec.push_back (9);

  ASSERT_EQ (test_vec[0], 1);
  ASSERT_EQ (test_vec[1], 2);
  ASSERT_EQ (test_vec[2], 3);
  ASSERT_EQ (test_vec[3], 4);
  ASSERT_EQ (test_vec[4], 5);
  ASSERT_EQ (test_vec[5], 6);
  ASSERT_EQ (test_vec[6], 7);
  ASSERT_EQ (test_vec[7], 8);
  ASSERT_EQ (test_vec[8], 9);
  ASSERT_EQ (test_vec.len (), 9);

  test_vec[0] = 5;
  ASSERT_EQ (test_vec[0], 5);
  ASSERT_EQ (test_vec[1], 2);
  ASSERT_EQ (test_vec[2], 3);
  ASSERT_EQ (test_vec[3], 4);
  ASSERT_EQ (test_vec[4], 5);
  ASSERT_EQ (test_vec[5], 6);
  ASSERT_EQ (test_vec[6], 7);
  ASSERT_EQ (test_vec[7], 8);
  ASSERT_EQ (test_vec[8], 9);
  ASSERT_EQ (test_vec.len (), 9);
}

TEST_F (TestVec, pop_back)
{
  InlineVector<int, 10> test_vec;
  test_vec.push_back (1);
  test_vec.push_back (2);
  test_vec.push_back (3);
  test_vec.push_back (4);
  test_vec.push_back (5);
  test_vec.push_back (6);
  test_vec.push_back (7);
  test_vec.push_back (8);
  test_vec.push_back (9);

  test_vec.pop_back ();
  test_vec.pop_back ();
  test_vec.push_back (10);
  test_vec.push_back (11);
  test_vec.pop_back ();
  ASSERT_EQ (test_vec[0], 1);
  ASSERT_EQ (test_vec[1], 2);
  ASSERT_EQ (test_vec[2], 3);
  ASSERT_EQ (test_vec[3], 4);
  ASSERT_EQ (test_vec[4], 5);
  ASSERT_EQ (test_vec[5], 6);
  ASSERT_EQ (test_vec[6], 7);
  ASSERT_EQ (test_vec[7], 10);

  test_vec[0] = 5;
  ASSERT_EQ (test_vec[0], 5);
  ASSERT_EQ (test_vec[1], 2);
  ASSERT_EQ (test_vec[2], 3);
  ASSERT_EQ (test_vec[3], 4);
  ASSERT_EQ (test_vec[4], 5);
  ASSERT_EQ (test_vec[5], 6);
  ASSERT_EQ (test_vec[6], 7);
  ASSERT_EQ (test_vec[7], 10);
  ASSERT_EQ (test_vec.len (), 8);
}

TEST_F (TestVec, const_arr_overflow)
{
  InlineVector<int, 2> test_vec;
  test_vec.push_back (1);
  test_vec.push_back (2);
  test_vec.push_back (3);
  test_vec.push_back (4);
  test_vec.push_back (5);
  test_vec.push_back (6);
  test_vec.push_back (7);
  test_vec.push_back (8);
  test_vec.push_back (9);

  test_vec.pop_back ();
  test_vec.pop_back ();
  test_vec.push_back (10);
  test_vec.push_back (11);
  test_vec.pop_back ();
  ASSERT_EQ (test_vec[0], 1);
  ASSERT_EQ (test_vec[1], 2);
  ASSERT_EQ (test_vec[2], 3);
  ASSERT_EQ (test_vec[3], 4);
  ASSERT_EQ (test_vec[4], 5);
  ASSERT_EQ (test_vec[5], 6);
  ASSERT_EQ (test_vec[6], 7);
  ASSERT_EQ (test_vec[7], 10);

  test_vec[0] = 5;
  ASSERT_EQ (test_vec[0], 5);
  ASSERT_EQ (test_vec[1], 2);
  ASSERT_EQ (test_vec[2], 3);
  ASSERT_EQ (test_vec[3], 4);
  ASSERT_EQ (test_vec[4], 5);
  ASSERT_EQ (test_vec[5], 6);
  ASSERT_EQ (test_vec[6], 7);
  ASSERT_EQ (test_vec[7], 10);
  ASSERT_EQ (test_vec.len (), 8);
}

TEST_F (TestVec, insert)
{
  InlineVector<int, 4> test_vec;
  test_vec.push_back (1);
  test_vec.push_back (2);
  test_vec.push_back (3);
  test_vec.push_back (4);
  test_vec.push_back (5);
  test_vec.push_back (6);
  test_vec.push_back (7);
  test_vec.push_back (8);

  test_vec.insert (test_vec.begin () + 2, 12);
  ASSERT_EQ (test_vec[0], 1);
  ASSERT_EQ (test_vec[1], 2);
  ASSERT_EQ (test_vec[2], 12);
  ASSERT_EQ (test_vec[3], 3);
  ASSERT_EQ (test_vec[4], 4);
  ASSERT_EQ (test_vec[5], 5);
  ASSERT_EQ (test_vec[6], 6);
  ASSERT_EQ (test_vec[7], 7);
  ASSERT_EQ (test_vec[8], 8);

  test_vec.insert (test_vec.begin () + 6, 12);
  ASSERT_EQ (test_vec[0], 1);
  ASSERT_EQ (test_vec[1], 2);
  ASSERT_EQ (test_vec[2], 12);
  ASSERT_EQ (test_vec[3], 3);
  ASSERT_EQ (test_vec[4], 4);
  ASSERT_EQ (test_vec[5], 5);
  ASSERT_EQ (test_vec[6], 12);
  ASSERT_EQ (test_vec[7], 6);
  ASSERT_EQ (test_vec[8], 7);
  ASSERT_EQ (test_vec[9], 8);
  ASSERT_EQ (test_vec.len (), 10);
}

TEST_F (TestVec, iters)
{
  InlineVector<int, 2> test_vec;
  test_vec.push_back (1);
  test_vec.push_back (2);
  test_vec.push_back (3);
  test_vec.push_back (4);
  test_vec.push_back (5);
  test_vec.push_back (6);
  test_vec.push_back (7);
  test_vec.push_back (8);
  test_vec.push_back (9);

  test_vec.pop_back ();
  test_vec.pop_back ();
  test_vec.push_back (10);
  test_vec.push_back (11);
  test_vec.pop_back ();
  test_vec.insert (test_vec.begin () + 2, 12);
  test_vec.insert (test_vec.begin () + 6, 12);
  ASSERT_EQ (test_vec[0], 1);
  ASSERT_EQ (test_vec[1], 2);
  ASSERT_EQ (test_vec[2], 12);
  ASSERT_EQ (test_vec[3], 3);
  ASSERT_EQ (test_vec[4], 4);
  ASSERT_EQ (test_vec[5], 5);
  ASSERT_EQ (test_vec[6], 12);
  ASSERT_EQ (test_vec[7], 6);
  ASSERT_EQ (test_vec[8], 7);
  ASSERT_EQ (test_vec[9], 10);

  int answers[] = { 1, 2, 12, 3, 4, 5, 12, 6, 7, 10 };

  int c = 0;
  for (auto x : test_vec)
    {

      ASSERT_EQ (x, answers[c]);
      c++;
    }
}

TEST_F (TestVec, clear)
{
  InlineVector<int, 2> test_vec;
  test_vec.push_back (1);
  test_vec.push_back (2);
  test_vec.push_back (3);
  test_vec.push_back (4);
  test_vec.push_back (5);
  test_vec.push_back (6);
  test_vec.push_back (7);
  test_vec.push_back (8);
  test_vec.push_back (9);

  test_vec.pop_back ();
  test_vec.pop_back ();
  test_vec.push_back (10);
  test_vec.push_back (11);
  test_vec.pop_back ();
  test_vec.insert (test_vec.begin () + 2, 12);
  test_vec.insert (test_vec.begin () + 6, 12);

  test_vec.clear ();

  ASSERT_EQ (test_vec.len (), 0);
}

int
main (int argc, char *argv[])
{
  testing::InitGoogleTest (&argc, argv);
  return RUN_ALL_TESTS ();
}