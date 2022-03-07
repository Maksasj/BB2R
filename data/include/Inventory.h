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
      int size;
      Inventory(int inv_size) {
            size = inv_size;

            storage.push_back({Item("pickaxe"), 1});
            for (int x = 1; x < inv_size; x++) {
                  storage.push_back({Item("stone_wall"), 8});
            }

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
                  storage.push_back({Item(itemcell.first), itemcell.second});
            }
      }
};

#endif