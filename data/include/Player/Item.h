#ifndef ITEM_CLASS_H
#define ITEM_CLASS_H

#include <string>

struct Item
{     
      std::string id;
      Item(std::string _id) {
            id = _id;
      }
};

#endif