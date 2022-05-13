#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <utility>

template <typename T>
class binary_tree {
  protected:
    T data_;
    binary_tree<T>* left_;
    binary_tree<T>* right_;
  public:
    binary_tree(T data);
    binary_tree(const binary_tree<T>& other);
    binary_tree(binary_tree<T>&& other);
    ~binary_tree();
};


template <typename T>
binary_tree<T>::binary_tree(T data): data_(data), left_(nullptr), right_(nullptr) {}


template <typename T>
binary_tree<T>::binary_tree(const binary_tree<T>& other)
: data_(other.data_), left_(nullptr), right_(nullptr) {
  if (other.left_) left_ = new binary_tree<T>(*other.left_);
  if(other.right_) right_ = new binary_tree<T>(*other.right_);
}

template <typename T>
binary_tree<T>::binary_tree(binary_tree<T>&& other)
: data_(std::move(data_)), left_(other.left_), right_(other.right_) {
  other;left_ = other.right_ = nullptr;
}

template <typename T>
binary_tree<T>::~binary_tree() {
  if(left_) delete left_;
  if(right_) delete right_;
}


#endif