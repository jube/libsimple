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
#ifndef SIMPLE_MATRIX_H
#define SIMPLE_MATRIX_H

#include <memory>
#include <stdexcept>

namespace simple {

  template<class T, class Allocator =  std::allocator<T>>
  class matrix {
    static_assert(std::is_default_constructible<T>::value, "T should be default constructible");
    static_assert(std::is_copy_constructible<T>::value, "T should be copy constructible");
  public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename std::allocator_traits<Allocator>::pointer pointer;
    typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;

    matrix()
    : m_allocator(Allocator())
    , m_rows(0)
    , m_cols(0)
    , m_content(nullptr)
    {
    }

    matrix(size_type rows, size_type cols)
    : m_allocator(Allocator())
    , m_rows(rows)
    , m_cols(cols)
    , m_content(m_allocator.allocate(rows * cols))
    {
      size_type end = m_rows * m_cols;
      for (size_type i = 0; i < end; ++i) {
        m_allocator.construct(m_content + i);
      }
    }

    matrix(const matrix& other)
    : m_allocator(std::allocator_traits<allocator_type>::select_on_container_copy_construction(other.m_allocator))
    , m_rows(other.m_rows)
    , m_cols(other.m_cols)
    , m_content(m_allocator.allocate(m_rows * m_cols))
    {
      size_type end = m_rows * m_cols;
      for (size_type i = 0; i < end; ++i) {
        m_allocator.construct(m_content + i, other.m_content[i]);
      }
    }

    matrix(matrix&& other)
    : m_allocator(std::move(other.m_allocator))
    , m_rows(other.m_rows)
    , m_cols(other.m_cols)
    , m_content(other.m_content)
    {
      other.m_rows = other.m_cols = 0;
      other.m_content = nullptr;
    }

    ~matrix() {
      clear();
    }

    matrix& operator=(const matrix& other) {
      clear();
      m_allocator = other.m_allocator;
      m_rows = other.m_rows;
      m_cols = other.m_cols;
      m_content = m_allocator.allocate(m_rows * m_cols);
      size_type end = m_rows * m_cols;

      for (size_type i = 0; i < end; ++i) {
        m_allocator.construct(m_content + i, other.m_content[i]);
      }

      return *this;
    }

    matrix& operator=(matrix&& other) {
      clear();
      m_allocator = std::move(other.m_allocator);
      m_rows = other.m_rows;
      m_cols = other.m_cols;
      m_content = other.m_content;

      other.m_rows = 0;
      other.m_cols = 0;
      other.m_content = nullptr;

      return *this;
    }

    allocator_type get_allocator() const {
      return m_allocator;
    }

    // element access

    reference at(size_type row, size_type col) {
      if (row >= m_rows || col >= m_cols) {
        throw std::out_of_range("matrix::at");
      }

      return m_content[row * m_cols + col];
    }

    const_reference at(size_type row, size_type col) const {
      if (row >= m_rows || col >= m_cols) {
        throw std::out_of_range("matrix::at");
      }

      return m_content[row * m_cols + col];
    }

    reference operator()(size_type row, size_type col) {
      return m_content[row * m_cols + col];
    }

    const_reference operator()(size_type row, size_type col) const {
      return m_content[row * m_cols + col];
    }

    // capacity

    bool empty() const {
      return m_content == nullptr;
    }

    size_type rows() const {
      return m_rows;
    }

    size_type cols() const {
      return m_cols;
    }

    // modifiers

    void clear() {
      if (m_content) {
        size_type end = m_rows * m_cols;
        for (size_type i = 0; i < end; ++i) {
          m_allocator.destroy(m_content + i);
        }

        m_allocator.deallocate(m_content, m_rows * m_cols);
        m_rows = m_cols = 0;
        m_content = nullptr;
      }
    }

    void swap(matrix& other) {
      std::swap(m_allocator, other.m_allocator);
      std::swap(m_rows, other.m_rows);
      std::swap(m_cols, other.m_cols);
      std::swap(m_content, other.m_content);
    }

  private:
    allocator_type m_allocator;
    size_type m_rows;
    size_type m_cols;
    pointer m_content;
  };

}

#endif // SIMPLE_MATRIX_H
