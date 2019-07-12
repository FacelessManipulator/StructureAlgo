#include <iostream>
#include <map>
#include <string>
#include "draw/table.hpp"

namespace Faceless {
namespace Trie {
template <typename _TU, typename _TD>
struct Node {
  typedef _TU TypeUnit;
  typedef _TD TypeData;
  TypeUnit unit;
  TypeData data;
  Node* parent;
  std::map<int, Node*> children;
  Node(Node* _parent = nullptr) : parent(_parent) {}
};

// typename _TU is the unit of typename _TK, and need the support of operation
// [].
template <typename _TK = std::string, typename _TU = char,
          typename _TD = char[0]>
class Tree {
 public:
  typedef _TK TypeKey;
  typedef _TU TypeUnit;
  typedef _TD TypeData;
  typedef Node<_TU, _TD> TypeNode;

 public:
  Tree() { root = new TypeNode(); }
  ~Tree() {}

 public:
  TypeNode& insert(const _TK& key) {
    TypeNode* cur = root;
    for (const auto& u : key) {
      int unit2int = int(u);
      auto next_unit = cur->children.find(unit2int);
      // if path node not exists
      if (next_unit == cur->children.end()) {
        TypeNode* node_n = new TypeNode(cur);
        cur->children[unit2int] = node_n;
        node_n->unit = u;
        cur = node_n;
      } else {
        cur = next_unit->second;
      }
    }
    return *cur;
  }
  
  void dump() {
    Table table;
    Terminal term;
    toTable(table, 0, 0, root);
    table[0][0].setContent("root");
    table.dump(term);
  }

private:
  int toTable(Table& table, int treeLevel, int startRow, TypeNode* curnode, bool firstChild=true) {
    std::string prefix;
    if(firstChild) {
      prefix = "-->";
    } else {
      prefix = "|->";
    }
    prefix.push_back(curnode->unit);
    table[startRow][treeLevel].setContent(prefix).setAlign(Cell::Left).setFiller('-');
    int curRow = startRow;
    firstChild = true;
    for(auto nodeIt : curnode->children) {
      for(int i = curRow+1; i < startRow; i++)
        table[i][treeLevel+1].setContent("|").setAlign(Cell::Left);
      curRow = startRow;
      startRow = toTable(table, treeLevel+1, curRow, nodeIt.second, firstChild) + 2;
      firstChild = false;
    }
    curRow = startRow;
    if(curnode->children.size() > 0) {
      curRow -= 2;
    }
    // return the cursor of next row
    return curRow;
  }
  

 private:
  TypeNode* root;
};

};  // namespace Trie
};  // namespace Faceless