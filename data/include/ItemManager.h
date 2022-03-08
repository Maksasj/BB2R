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

      void LoadFromMod(std::map<std::string, nlohmann::json> _item_data) {
            ItemData = _item_data;
      }
};

#endif