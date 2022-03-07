#ifndef ITEMMANAGER_CLASS_H
#define ITEMMANAGER_CLASS_H

#include <iostream>
#include <map>
#include <json.h>

struct ItemManager
{     
      std::map<std::string , nlohmann::json> ItemData;

      ItemManager() {

      }

      void LoadFromMod(std::vector<nlohmann::json> _item_data) {
            for (auto tmp_item_data : _item_data) {
                  std::cout << "Loaded: " << tmp_item_data["id"] << "\n";
                  ItemData[tmp_item_data["id"]] = tmp_item_data;
            }
      }
};

#endif