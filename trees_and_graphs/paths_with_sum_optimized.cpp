/**
 * 4.12  Paths with Sum (optimized)
 * Lee Tomlinson
 **/
#include <iostream>
#include <unordered_map>
#include <memory>

class TNode {
 public:
  std::shared_ptr<TNode> left;
  std::shared_ptr<TNode> right;
  int value;
  TNode(int t_value) : value{t_value}, left{nullptr}, right{nullptr} {}
};

int CountPathsWhichSum(std::shared_ptr<TNode> node, int target,
                       std::unordered_map<int, int>& hist, int running_sum) {
  if (node == nullptr) return 0;
  running_sum += node->value;
  ++hist[running_sum];
  int total_paths{hist[running_sum - target]};
  total_paths += CountPathsWhichSum(node->left, target, hist, running_sum);
  total_paths += CountPathsWhichSum(node->right, target, hist, running_sum);
  --hist[running_sum];
  return total_paths;
}

int CountPathsWhichSum(std::shared_ptr<TNode> root, int target) {
  std::unordered_map<int, int> hist;
  ++hist[0];
  return CountPathsWhichSum(root, target, hist, 0);
}

int main() {
  std::shared_ptr<TNode> tree{new TNode(2)};
  tree->left.reset(new TNode(7));
  tree->right.reset(new TNode(1));
  tree->left->left.reset(new TNode(8));
  tree->left->right.reset(new TNode(2));
  tree->right->left.reset(new TNode(8));
  tree->right->right.reset(new TNode(1));
  tree->left->right->left.reset(new TNode(8));
  tree->left->right->right.reset(new TNode(2));
  tree->right->right->left.reset(new TNode(8));
  tree->right->right->right.reset(new TNode(4));
  tree->left->right->right->left.reset(new TNode(5));
  tree->right->right->right->left.reset(new TNode(9));

  // Expect 3
  std::cout << CountPathsWhichSum(tree, 11) << '\n';
}
