/**
 * 4.12  Paths with Sum
 * Lee Tomlinson
 **/
#include <iostream>
#include <list>
#include <memory>

class TNode {
 public:
  std::shared_ptr<TNode> left_child;
  std::shared_ptr<TNode> right_child;
  int value;
  TNode(int t_value)
      : value{t_value}, left_child{nullptr}, right_child{nullptr} {}
};

void NumberOfPaths(std::shared_ptr<TNode> node, int target,
                   std::list<int>& values, int& count) {
  if (node == nullptr) return;  // Stop when leaf has been reached
  values.push_back(node->value);
  int sum{0};
  auto it = values.end();
  while (it != values.begin() && sum < target) {
    --it;
    sum += *it;
    if (sum == target) ++count;
  }
  // Visit children in depth-first search
  NumberOfPaths(node->left_child, target, values, count);
  NumberOfPaths(node->right_child, target, values, count);
  values.pop_back();
}

int NumberOfPaths(std::shared_ptr<TNode> root, int target) {
  std::list<int> values;  // List of values from root to some node
  int count{0};           // Number of paths whose values sum to target
  NumberOfPaths(root, target, values, count);
  return count;
}

int main() {
  std::shared_ptr<TNode> tree{new TNode(2)};
  tree->left_child.reset(new TNode(7));
  tree->right_child.reset(new TNode(1));
  tree->left_child->left_child.reset(new TNode(8));
  tree->left_child->right_child.reset(new TNode(2));
  tree->right_child->left_child.reset(new TNode(8));
  tree->right_child->right_child.reset(new TNode(1));
  tree->left_child->right_child->left_child.reset(new TNode(8));
  tree->left_child->right_child->right_child.reset(new TNode(2));
  tree->right_child->right_child->left_child.reset(new TNode(8));
  tree->right_child->right_child->right_child.reset(new TNode(4));
  tree->left_child->right_child->right_child->left_child.reset(new TNode(5));
  tree->right_child->right_child->right_child->left_child.reset(new TNode(9));

  // Expect 3
  std::cout << NumberOfPaths(tree, 11) << '\n';
}
