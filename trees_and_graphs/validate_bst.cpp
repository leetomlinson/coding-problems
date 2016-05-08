/**
 * 4.5  Validate BST
 * Lee Tomlinson
 **/
#include <memory>
#include <iostream>

template <typename T>
class TNode {
 public:
  std::shared_ptr<TNode> left;
  std::shared_ptr<TNode> right;
  T value;
  TNode(T init_value) : value{init_value}, left{nullptr}, right{nullptr} {}
};

template <typename T>
bool ValidateBST(std::shared_ptr<TNode<T>> parent, T left_bound = 0,
                 T right_bound = 0, bool apply_left_bound = false,
                 bool apply_right_bound = false) {
  if (parent == nullptr) return true;
  auto cond1 = parent->left == nullptr ||
               parent->left->value <= parent->value &&
                   (parent->left->value > left_bound || !apply_left_bound);
  auto cond2 = parent->right == nullptr ||
               parent->right->value > parent->value &&
                   (parent->right->value <= right_bound || !apply_right_bound);
  return cond1 && cond2 && ValidateBST(parent->left, left_bound, parent->value,
                                       apply_left_bound, true) &&
         ValidateBST(parent->right, parent->value, right_bound, true,
                     apply_right_bound);
}

int main() {
  auto tree1 = std::shared_ptr<TNode<int>>{new TNode<int>{4}};
  tree1->left.reset(new TNode<int>{3});
  tree1->right.reset(new TNode<int>{6});
  tree1->left->left.reset(new TNode<int>{1});
  tree1->right->left.reset(new TNode<int>{5});
  tree1->right->right.reset(new TNode<int>{7});
  tree1->left->left->right.reset(new TNode<int>{2});

  auto tree2 = std::shared_ptr<TNode<int>>{new TNode<int>{4}};
  tree2->left.reset(new TNode<int>{2});
  tree2->right.reset(new TNode<int>{6});
  tree2->left->left.reset(new TNode<int>{1});
  tree2->right->left.reset(new TNode<int>{1});
  tree2->right->right.reset(new TNode<int>{8});
  tree2->left->left->right.reset(new TNode<int>{8});

  std::cout << "ValidateBST(tree1)=" << ValidateBST(tree1) << '\n';
  std::cout << "ValidateBST(tree2)=" << ValidateBST(tree2) << '\n';

  return 0;
}
