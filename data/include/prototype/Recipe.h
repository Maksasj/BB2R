#ifndef RECIPE_CLASS_H
#define RECIPE_CLASS_H

#include <vector>
#include "Item.h"

typedef struct ItemRecipe {
      Item item;
      int count;
} ItemRecipe;

typedef struct Recipe {
      std::vector<ItemRecipe> ingredients;
      Item result;
} Recipe;

#endif