#ifndef PLAYERINVENTORY_CLASS_H
#define PLAYERINVENTORY_CLASS_H

#include "GuiElement.h"
#include "Font.h"
#include "Text.h"
#include "Field.h"
#include "Window.h"
#include "InventoryList.h"

#include "../ItemManager.h"
#include "../Player.h"
#include "../Entity.h"

#include "../utilities/vector.h"

struct PlayerInventory : public GuiElement
{     
      Window *window;
      InventoryList *invlist;
      Text *hoveredname;
      Text *hovereddesc;

      std::string *selected_item;
      
      Player *link_player;
      ItemManager *itemmanager;

      PlayerInventory(Player *_link_player, vec2 _pos, game::font* _font) : GuiElement(_pos) {
            selected_item = new std::string("nothing");
            link_player = _link_player;

            window = new Window({450, 600}, {100, 100});
            window->color = {180, 180, 180, 150};
            window->setDraggable({450, 15});
            window->setTitle("Inventory", _font);
            window->SetKey(KEY_E);
            
            invlist = new InventoryList(_link_player, {150, 580}, {100, 100}, _font);
            invlist->BindSelector(selected_item);
            window->addElement(invlist, {5, 17});

            hoveredname = new Text("Test Item", _font, 30, {100, 100});
            hovereddesc = new Text("test description", _font, 16, {100, 100});

            window->addElement(hoveredname, {155, 25});
            window->addElement(hovereddesc, {155, 80});
      }

      void SetUpItemManager(ItemManager *_itemmanager) { itemmanager = _itemmanager; }

      void Update() {
            if (invlist->hovered_element >= 0) { 
                  hoveredname->actext = link_player->inventory->storage[invlist->hovered_element].item.id; 
                  
                  if (itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id].contains("tags")) {
                        if (itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id]["tags"].contains("description")) {
                              hovereddesc->actext = itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id]["tags"]["description"];
                        }
                  }
            }

            if (*selected_item != "nothing") {
                  link_player->hotbar_item_list[ link_player->hotbar_active_cell] = *selected_item;
                  link_player->hotbar_item_id = *selected_item;
                  *selected_item = "nothing";
            }

            window->Update();
      }

      void Render() {
            window->Render();
      }
};

#endif