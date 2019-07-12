#pragma once
#include <assert.h>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>
#include <cmath>
#include "draw/terminal.hpp"

namespace Faceless {
void fill(char filler=' ', int count = 1) {
  int left_space = count;
  while (left_space > 0) {
    std::cout << filler;
    left_space -= 1;
  }
}

struct Cell {
 public:
  enum Alignment {
    Left = 0,
    Median,
    Right,
  };

 public:
  std::string content;
  Alignment align;
  char filler;

 public:
  Cell(const std::string& _cnt = "", Alignment _ali = Left, char _fill = ' ')
      : content(_cnt), align(_ali), filler(_fill) {}
  void dump(unsigned int width) const {
    if (content.size() > width) {
      std::cout << content.substr(0, width);
    } else {
      if (align == Left) {
        std::cout << content;
        fill(filler, width - content.size());

      } else if (align == Median) {
        fill(filler, std::floor((width - content.size()) / 2));
        std::cout << content;
        fill(filler, std::ceil((width - content.size()) / 2));
      } else if (align == Right) {
        fill(filler, width - content.size());
        std::cout << content;
      }
    }
  }
  Cell& setContent(const std::string& dest) { content = dest; }
    Cell& setAlign(Alignment dest) {align = dest;}
    Cell& setFiller(char _fill) {filler = _fill;}
};

class Table {
 public:
  static const int MAX_ROW_NUM = 128;
  static const int MAX_COL_NUM = 128;

  class Row {
   public:
    std::vector<Cell> cells;
    Table* table;
  public:
    Cell& operator[](unsigned int id) {
      assert (id < MAX_COL_NUM);
      while (cells.size() <= id) {
        cells.emplace_back();
      }
      table->col_num = table->col_num < id+1? id+1 : table->col_num;
      assert(cells.size() > id);
      return cells[id];
    }
    size_t size() const { return cells.size(); }
    Row(Table* _tb): table(_tb) {}
  };

 public:
  std::vector<Row> rows;
  std::vector<unsigned int> cols_width;
  // rabbish row to handle the content which exceeds max row limit
  Row rabbishR;

 public:
  void auto_fit(const Terminal& term) {
    int total_width_min, col_spare = 0;
    std::vector<unsigned int> cols_width_min(col_num);
    unsigned int width_left = term.width;
    // calc min width for each column
    for (int i = 0; i < col_num; i++) {
      // for each row, find target column cell and compare the content size
      for (auto& row : rows) {
        if (row.size() > i) {
          int cnt_size = row[i].content.size();
          cols_width_min[i] =
              cols_width_min[i] < cnt_size ? cnt_size : cols_width_min[i];
        }
      }
    }

    // currently, column doesn't need spare space
    total_width_min =
        std::accumulate(cols_width_min.begin(), cols_width_min.end(), 0);
    if (total_width_min < term.width) {
      col_spare = (term.width - total_width_min) / col_num;
    }
    cols_width.resize(col_num);
    for (int i = 0; i < col_num; i++) {
      width_left -= cols_width_min[i];
      if (width_left >= 0)
        cols_width[i] = cols_width_min[i];
      else
        break;
    }
  }

  Row& operator[](unsigned int row_id) {
    if (row_id > MAX_ROW_NUM) return rabbishR;
    while (rows.size() <= row_id && rows.size() < MAX_ROW_NUM) {
      rows.emplace_back(this);
    }
    assert(rows.size() > row_id);
    return rows[row_id];
  }

  void dump(const Terminal& term) {
    auto_fit(term);
    for (auto& row : rows) {
      for (int i = 0; i < row.size(); i++) {
        row[i].dump(cols_width[i]);
      }
      std::cout  << std::endl;
    }
  }

  Table(): rabbishR(this), col_num(0) {}

 public:
  unsigned int col_num;
};
};  // namespace Faceless