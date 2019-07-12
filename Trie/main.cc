#include <iostream>
#include "timing/timing.hpp"
#include "Trie/trie.hpp"

using namespace Faceless;
int main() {
  Trie::Tree trie;
  Timing::run([&](){
      trie.insert("hello");
      trie.insert("helrw");
      trie.insert("apple");
      trie.insert("appoas");
      trie.insert("azshh");
  });
  trie.dump();
}