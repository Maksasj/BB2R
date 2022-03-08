#ifndef INVENTORY_CLASS_H
#define INVENTORY_CLASS_H

#include <iostream>
#include <string>
#include <vector>
#include "Item.h"

typedef struct ItemCell {
    Item item;
    int count;
} ItemCell;

struct Inventory
{     
      std::vector<ItemCell> storage; 
      int max_size;
      Inventory(int inv_size) {
            max_size = inv_size;

            storage.push_back({Item("pickaxe"), 1});

            SortInStacks();
      }

      void AddItem(std::string _id, int _count) {
            storage.push_back({Item(_id), _count});
            SortInStacks();
      }

      void SortInStacks() {
            std::map<std::string, int> tmp_inv;

            //Fill clear
            for (auto itemcell : storage) { tmp_inv[itemcell.item.id] = 0; }

            //Sum items
            for (auto itemcell : storage) {
                  tmp_inv[itemcell.item.id] += itemcell.count;
            }

            storage.clear();

            for (auto itemcell : tmp_inv) {
                  if (itemcell.second > 0) { storage.push_back({Item(itemcell.first), itemcell.second}); }
            }
      }
};

#endif