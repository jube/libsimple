/*
 * Copyright (c) 2014, Julien Bernard
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
#include <simple/matrix.h>

#include "gtest/gtest.h"

TEST(MatrixTest, EmptyConstructor) {
  simple::matrix<double> mat;

  EXPECT_TRUE(mat.empty());
  EXPECT_EQ(mat.rows(), 0);
  EXPECT_EQ(mat.cols(), 0);
}

TEST(MatrixTest, Constructor) {
  simple::matrix<int> mat(2, 3);

  EXPECT_FALSE(mat.empty());
  EXPECT_EQ(mat.rows(), 2);
  EXPECT_EQ(mat.cols(), 3);

  for (std::size_t i = 0; i < mat.rows(); ++i) {
    for (std::size_t j = 0; j < mat.cols(); ++j) {
      EXPECT_EQ(mat(i, j), 0);
    }
  }

}

TEST(MatrixTest, CopyConstructor) {
  simple::matrix<short> mat(2, 3);
  mat(0, 0) = 0;
  mat(0, 1) = 1;
  mat(0, 2) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;
  mat(1, 2) = 5;

  simple::matrix<short> copy(mat);

  // check the copy worked
  EXPECT_FALSE(copy.empty());
  EXPECT_EQ(copy.rows(), 2);
  EXPECT_EQ(copy.cols(), 3);
  EXPECT_EQ(copy(0, 0), 0);
  EXPECT_EQ(copy(0, 1), 1);
  EXPECT_EQ(copy(0, 2), 2);
  EXPECT_EQ(copy(1, 0), 3);
  EXPECT_EQ(copy(1, 1), 4);
  EXPECT_EQ(copy(1, 2), 5);

  // check the original matrix is still here
  EXPECT_FALSE(mat.empty());
  EXPECT_EQ(mat.rows(), 2);
  EXPECT_EQ(mat.cols(), 3);
  EXPECT_EQ(mat(0, 0), 0);
  EXPECT_EQ(mat(0, 1), 1);
  EXPECT_EQ(mat(0, 2), 2);
  EXPECT_EQ(mat(1, 0), 3);
  EXPECT_EQ(mat(1, 1), 4);
  EXPECT_EQ(mat(1, 2), 5);
}

TEST(MatrixTest, MoveConstructor) {
  simple::matrix<short> mat(2, 3);
  mat(0, 0) = 0;
  mat(0, 1) = 1;
  mat(0, 2) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;
  mat(1, 2) = 5;

  simple::matrix<short> copy(std::move(mat));

  // check the copy worked
  EXPECT_FALSE(copy.empty());
  EXPECT_EQ(copy.rows(), 2);
  EXPECT_EQ(copy.cols(), 3);
  EXPECT_EQ(copy(0, 0), 0);
  EXPECT_EQ(copy(0, 1), 1);
  EXPECT_EQ(copy(0, 2), 2);
  EXPECT_EQ(copy(1, 0), 3);
  EXPECT_EQ(copy(1, 1), 4);
  EXPECT_EQ(copy(1, 2), 5);

  // check the original matrix is not here anymore
  ASSERT_TRUE(mat.empty());
  EXPECT_EQ(mat.rows(), 0);
  EXPECT_EQ(mat.cols(), 0);
}

TEST(MatrixTest, CopyOperator) {
  simple::matrix<short> mat(2, 3);
  mat(0, 0) = 0;
  mat(0, 1) = 1;
  mat(0, 2) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;
  mat(1, 2) = 5;

  simple::matrix<short> copy;

  copy = mat;

  // check the copy worked
  EXPECT_FALSE(copy.empty());
  EXPECT_EQ(copy.rows(), 2);
  EXPECT_EQ(copy.cols(), 3);
  EXPECT_EQ(copy(0, 0), 0);
  EXPECT_EQ(copy(0, 1), 1);
  EXPECT_EQ(copy(0, 2), 2);
  EXPECT_EQ(copy(1, 0), 3);
  EXPECT_EQ(copy(1, 1), 4);
  EXPECT_EQ(copy(1, 2), 5);

  // check the original matrix is still here
  EXPECT_FALSE(mat.empty());
  EXPECT_EQ(mat.rows(), 2);
  EXPECT_EQ(mat.cols(), 3);
  EXPECT_EQ(mat(0, 0), 0);
  EXPECT_EQ(mat(0, 1), 1);
  EXPECT_EQ(mat(0, 2), 2);
  EXPECT_EQ(mat(1, 0), 3);
  EXPECT_EQ(mat(1, 1), 4);
  EXPECT_EQ(mat(1, 2), 5);
}

TEST(MatrixTest, CopyOperatorWithSameMatrix) {
  simple::matrix<short> mat(2, 3);
  mat(0, 0) = 0;
  mat(0, 1) = 1;
  mat(0, 2) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;
  mat(1, 2) = 5;

  mat = mat;

  // check the original matrix is still here
  EXPECT_FALSE(mat.empty());
  EXPECT_EQ(mat.rows(), 2);
  EXPECT_EQ(mat.cols(), 3);
  EXPECT_EQ(mat(0, 0), 0);
  EXPECT_EQ(mat(0, 1), 1);
  EXPECT_EQ(mat(0, 2), 2);
  EXPECT_EQ(mat(1, 0), 3);
  EXPECT_EQ(mat(1, 1), 4);
  EXPECT_EQ(mat(1, 2), 5);
}


TEST(MatrixTest, MoveOperator) {
  simple::matrix<short> mat(2, 3);
  mat(0, 0) = 0;
  mat(0, 1) = 1;
  mat(0, 2) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;
  mat(1, 2) = 5;

  simple::matrix<short> copy;

  copy = std::move(mat);

  // check the copy worked
  EXPECT_FALSE(copy.empty());
  EXPECT_EQ(copy.rows(), 2);
  EXPECT_EQ(copy.cols(), 3);
  EXPECT_EQ(copy(0, 0), 0);
  EXPECT_EQ(copy(0, 1), 1);
  EXPECT_EQ(copy(0, 2), 2);
  EXPECT_EQ(copy(1, 0), 3);
  EXPECT_EQ(copy(1, 1), 4);
  EXPECT_EQ(copy(1, 2), 5);

  // check the original matrix is not here anymore
  ASSERT_TRUE(mat.empty());
  EXPECT_EQ(mat.rows(), 0);
  EXPECT_EQ(mat.cols(), 0);
}

TEST(MatrixTest, MoveOperatorWithSameMatrix) {
  simple::matrix<short> mat(2, 3);
  mat(0, 0) = 0;
  mat(0, 1) = 1;
  mat(0, 2) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;
  mat(1, 2) = 5;

  mat = std::move(mat);

  // check the original matrix is still here
  EXPECT_FALSE(mat.empty());
  EXPECT_EQ(mat.rows(), 2);
  EXPECT_EQ(mat.cols(), 3);
  EXPECT_EQ(mat(0, 0), 0);
  EXPECT_EQ(mat(0, 1), 1);
  EXPECT_EQ(mat(0, 2), 2);
  EXPECT_EQ(mat(1, 0), 3);
  EXPECT_EQ(mat(1, 1), 4);
  EXPECT_EQ(mat(1, 2), 5);
}

TEST(MatrixTest, At) {
  simple::matrix<int> mat(2, 3);
  mat(0, 0) = 0;
  mat(0, 1) = 1;
  mat(0, 2) = 2;
  mat(1, 0) = 3;
  mat(1, 1) = 4;
  mat(1, 2) = 5;

  EXPECT_THROW(mat.at(2, 0), std::out_of_range);
  EXPECT_THROW(mat.at(0, 3), std::out_of_range);

  for (std::size_t i = 0; i < mat.rows(); ++i) {
    for (std::size_t j = 0; j < mat.cols(); ++j) {
      ASSERT_NO_THROW(mat.at(i, j));
      EXPECT_EQ(mat.at(i, j), mat(i, j));
    }
  }
}

TEST(MatrixTest, Clear) {
  simple::matrix<int> mat(2, 3);
  mat.clear();

  EXPECT_TRUE(mat.empty());
  EXPECT_EQ(mat.rows(), 0);
  EXPECT_EQ(mat.cols(), 0);
}

TEST(MatrixTest, Swap) {
  simple::matrix<int> mat1(2, 3);

  int content = 0;

  for (std::size_t i = 0; i < mat1.rows(); ++i) {
    for (std::size_t j = 0; j < mat1.cols(); ++j) {
      mat1(i, j) = content++;
    }
  }

  simple::matrix<int> mat2(4, 5);

  for (std::size_t i = 0; i < mat2.rows(); ++i) {
    for (std::size_t j = 0; j < mat2.cols(); ++j) {
      mat2(i, j) = content++;
    }
  }

  mat1.swap(mat2);

  EXPECT_EQ(mat2.rows(), 2);
  EXPECT_EQ(mat2.cols(), 3);
  EXPECT_EQ(mat1.rows(), 4);
  EXPECT_EQ(mat1.cols(), 5);

  content = 0;

  for (std::size_t i = 0; i < mat2.rows(); ++i) {
    for (std::size_t j = 0; j < mat2.cols(); ++j) {
      EXPECT_EQ(mat2(i, j), content);
      content++;
    }
  }

  for (std::size_t i = 0; i < mat1.rows(); ++i) {
    for (std::size_t j = 0; j < mat1.cols(); ++j) {
      EXPECT_EQ(mat1(i, j), content);
      content++;
    }
  }
}
