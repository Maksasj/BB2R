#ifndef INVENTORY_CLASS_H
#define INVENTORY_CLASS_H

#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "ItemManager.h"

typedef struct ItemCell {
    Item item;
    int count;
} ItemCell;

struct Inventory
{     
      std::vector<ItemCell> storage;
      int max_size;

      ItemManager *itemmanager;

      Inventory(int inv_size) {
            max_size = inv_size;

            storage.push_back({Item("pickaxe"), 1});
      }

      void SetUpNEU(ItemManager *_itemmanager) {
            itemmanager = _itemmanager;
      }

      void DeleteEmptyStack() {
            std::vector<ItemCell> tmp_storage;
            for (auto &itemcell : storage) { if (itemcell.count > 0) { tmp_storage.push_back(itemcell); }}
            storage = tmp_storage;
      }

      int GetItemCount(std::string _id) {
            std::map<std::string, int> tmp_inv; tmp_inv[_id] = 0;
            for (auto itemcell : storage) { tmp_inv[itemcell.item.id] += itemcell.count; }
            return tmp_inv[_id];
      }

      std::vector<std::string> GetItemVector() {
            std::vector<std::string> tpm_vector;
            std::map<std::string, int> tmp_inv;

            for (auto itemcell : storage) { tmp_inv[itemcell.item.id] += itemcell.count; }
            for (auto item : tmp_inv) { tpm_vector.push_back(item.first); }

            return tpm_vector;
      }

      void AddItem(std::string _id, int _count) {
            for (auto &itemcell : storage) {
                  if (itemcell.item.id == _id && _count > 0) {
                        if (itemcell.count + _count < (int)itemmanager->ItemData[_id]["stack_size"]) {
                              itemcell.count += _count; _count = 0; break;
                        } else {
                              _count -= (int)itemmanager->ItemData[_id]["stack_size"] - itemcell.count;
                              itemcell.count = (int)itemmanager->ItemData[_id]["stack_size"];
                        }
                  }
            }
            if (_count > 0) { storage.push_back({Item(_id), _count}); }
      }
      
      void SubtractItem(std::string _id, int _count) {
            for (auto &itemcell : storage) {
                  if (itemcell.item.id == _id && _count >= 0) {
                        if (itemcell.count - _count > 0) {
                              itemcell.count -= _count; _count = 0;
                        } else if (itemcell.count - _count == 0) {
                              itemcell.count = _count = 0;

                              DeleteEmptyStack();
                        }
                  }
            }
      }
};

#endif