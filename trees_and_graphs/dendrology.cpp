/**
 * Dendrology
 **/
#include <list>
#include <memory>
#include <queue>
#include <unordered_map>
#include <iostream>

template <typename T>
class TNode {
 public:
  std::list<std::shared_ptr<TNode>> children;
  T value;
  TNode(T init_value) : value{init_value} {}
};

template <typename T>
void print_value(std::shared_ptr<TNode<T>> node) {
  std::cout << node->value << '\n';
}

template <typename T>
void DFT(std::shared_ptr<TNode<T>> parent,
         void (*func)(std::shared_ptr<TNode<T>>)) {
  // Depth-first application of func to all nodes branching from parent
  func(parent);
  for (auto child : parent->children) {
    DFT(child, func);
  }
}

template <typename T>
void BFT(std::shared_ptr<TNode<T>> parent,
         void (*func)(std::shared_ptr<TNode<T>>)) {
  // Breadth-first application of func to all nodes branching from parent
  std::queue<std::shared_ptr<TNode<T>>> queue;
  std::unordered_map<std::shared_ptr<TNode<T>>, bool> queued_up;
  queue.push(parent);
  queued_up[parent] = true;
  while (!queue.empty()) {
    parent = queue.front();
    queue.pop();
    func(parent);
    for (auto child : parent->children) {
      if (!queued_up[child]) {
        queue.push(child);
        queued_up[child] = true;
      }
    }
  }
}

int main() {
  auto n1 = std::shared_ptr<TNode<int>>{new TNode<int>{1}};
  auto n2 = std::shared_ptr<TNode<int>>{new TNode<int>{2}};
  auto n3 = std::shared_ptr<TNode<int>>{new TNode<int>{3}};
  auto n4 = std::shared_ptr<TNode<int>>{new TNode<int>{4}};
  auto n5 = std::shared_ptr<TNode<int>>{new TNode<int>{5}};
  auto n6 = std::shared_ptr<TNode<int>>{new TNode<int>{6}};
  auto n7 = std::shared_ptr<TNode<int>>{new TNode<int>{7}};
  auto n8 = std::shared_ptr<TNode<int>>{new TNode<int>{8}};
  auto n9 = std::shared_ptr<TNode<int>>{new TNode<int>{9}};
  n1->children.push_back(n2);
  n1->children.push_back(n6);
  n2->children.push_back(n3);
  n2->children.push_back(n4);
  n2->children.push_back(n5);
  n6->children.push_back(n7);
  n6->children.push_back(n8);
  n8->children.push_back(n9);

  std::cout << "Depth-first traversal:\n";
  DFT(n1, print_value);
  std::cout << "Breadth-first traversal:\n";
  BFT(n1, print_value);
}
