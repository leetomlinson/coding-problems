/**
 * Implementation of binary tree class with method to get random node
 * Lee Tomlinson
 * 28/05/2016
 **/
#include <random>
#include <queue>
#include <map>

unsigned int Random(unsigned int m, unsigned int n) {
  // Return a uniformly distributed unsigned integer in the interval [m, n]
  auto eng = std::default_random_engine{};
  auto udist = std::uniform_int_distribution<unsigned int>{m, n};
  return udist(eng);
}

enum class Direction { left, right };

template <typename T>
class TNode {
 private:
  T m_value;
  TNode* m_left;
  TNode* m_right;
  TNode* m_parent;
  unsigned int m_n_left;   // Number of nodes in left sub-tree
  unsigned int m_n_right;  // Number of nodes in right sub-tree

  void add_one(TNode* child) {
    if (child == m_left) ++m_n_left;
    if (child == m_right) ++m_n_right;
    if (m_parent != nullptr) m_parent->add_one(this);
  }

  void subtract(TNode* child, unsigned int n) {
    if (child == m_left) m_n_left -= n;
    if (child == m_right) m_n_right -= n;
    if (m_parent != nullptr) m_parent->subtract(this, n);
  }

 public:
  TNode(T const& value, TNode* parent)
      : m_value{value},
        m_left{nullptr},
        m_right{nullptr},
        m_parent{parent},
        m_n_left{0},
        m_n_right{0} {}

  virtual ~TNode() {
    if (m_parent != nullptr) {
      // Fix sub-tree counts of ancestors
      auto n = m_n_left + m_n_right + 1;  // Number of nodes in this sub-tree
      m_parent->subtract(this, n);

      // Fix child pointer of parent (no dangling pointers)
      if (m_parent->m_left == this) m_parent->m_left = nullptr;
      if (m_parent->m_right == this) m_parent->m_right = nullptr;
    }

    // Delete children
    if (m_left != nullptr) {
      m_left->m_parent = nullptr;  // Safeguard against fixing sub-tree counts
                                   // of ancestors multiple times
      delete m_left;
    }
    if (m_right != nullptr) {
      m_right->m_parent = nullptr;
      delete m_right;
    }
  }

  TNode* GetRandomNode() const {
    unsigned int rnd{Random(0, m_n_left + m_n_right)};
    if (rnd == 0) return this;
    if (rnd <= m_n_left)
      return m_left->GetRandomNode();
    else
      return m_right->GetRandomNode();
  }

  TNode* insert(T const& value, Direction dir) {
    // Create a new child node on the appropriate side
    auto& child = dir == Direction::left ? m_left : m_right;
    if (child != nullptr) return nullptr;
    child = new TNode{value, this};
    add_one(child);
  }

  TNode* find(T const& value) const {
    // Breadth-first search this sub-tree for first node with the given value
    std::queue<TNode*> queue;
    std::map<TNode*, bool> visited;
    queue.push(this);
    visited[this] = true;
    while (!queue.empty()) {
      auto node = queue.peek();
      queue.pop();
      if (node->m_value == value) return node;
      visited[node] = true;
      if (node->m_left != nullptr && !visited[node->m_left])
        queue.push(node->m_left);
      if (node->m_right != nullptr && !visited[node->m_right])
        queue.push(node->m_right);
    }
  }
};

template <typename T>
class Tree {
 private:
  TNode<T>* m_root;

 public:
  Tree() : m_root{nullptr} {}

  TNode<T>* GetRandomNode() {
    if (m_root == nullptr) return nullptr;
    return m_root->GetRandomNode();
  }

  TNode<T>* insert(TNode<T>* parent, T const& value, Direction dir) {
    parent->insert(value, dir);
  }

  void delete_node(TNode<T>* node) { delete node; }

  TNode<T>* find(T const& value) const { m_root->find(value); }
};

int main() { return 0; }
