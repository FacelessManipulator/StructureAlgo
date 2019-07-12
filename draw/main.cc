#include "draw/table.hpp"

using namespace Faceless;

int main() {
Table table;
Terminal term;
table[0][0].setContent("root ").setAlign(Cell::Right).setFiller('-');
    table[0][1].setContent("--> child1 ").setAlign(Cell::Right).setFiller('-');
    table[0][2].setContent("--> child2 ").setAlign(Cell::Right).setFiller('-');
    table[1][2].setContent("|-> child3 ").setAlign(Cell::Left).setFiller('-');
    table[1][1].setContent("|  ").setAlign(Cell::Left);
    table[2][1].setContent("|-> child4 ").setAlign(Cell::Left).setFiller('-');
table.dump(term);
}