#ifndef _FMT_MEM_VIEW_HPP_
#define _FMT_MEM_VIEW_HPP_

#include <cassert>
#include <cstdint>
#include <cstdlib>

namespace fmt {

template<typename T>
class mem_view {
public:
  mem_view() : data_(nullptr), size_(0) {}

  mem_view(T* data, uint32_t size)
      : data_(data), size_(size) {
    assert(size == 0 || (size > 0 && data != nullptr));
  }

  mem_view sub_view(uint32_t a, uint32_t b) {
    assert(b <= size_);
    assert(a < b);
    assert(0 <= a);

    return mem_view(&data_[from], b - a);
  }

  uint32_t size() const {
    return size_;
  }

  bool empty() const {
    return size_ == 0;
  }

  T *begin() const {
    return data_;
  }

  T *end() const {
    return &data_[length];
  }

  T &operator[](uint32_t i) const {
    assert(0 <= i && i < size_);
    return data_[i];
  }

  T &first() {
    return data_[0];
  }

  T &last() {
    return data_[length_ - 1];
  }

private:
  T* data_;
  size_t size_;
};

}

#endif
