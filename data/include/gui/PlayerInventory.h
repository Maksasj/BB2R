#ifndef PLAYERINVENTORY_CLASS_H
#define PLAYERINVENTORY_CLASS_H

#include "GuiElement.h"
#include "Font.h"
#include "Text.h"
#include "Field.h"
#include "Window.h"
#include "InventoryList.h"

#include "../Mod/ItemManager.h"
#include "../Player/Player.h"
#include "../prototype/Entity.h"

#include "../Utilities/vector.h"

struct PlayerInventory : public GuiElement
{     
      Window *window;
      InventoryList *invlist;

      Text *hovereddesc;
      Field *hovereddescfield;

      Text *hoveredname;
      Text *hoveredtype;
      Text *hoveredstack;

      std::string *selected_item;
      
      Player *link_player;
      ItemManager *itemmanager;

      PlayerInventory(Player *_link_player, vec2 _pos, game::font* _font) : GuiElement(_pos) {
            selected_item = new std::string("nothing");
            link_player = _link_player;

            window = new Window({450, 600}, {100, 100});
            window->color = {180, 180, 180, 150};
            window->setDraggable({450, 20});
            window->setTitle("Inventory", _font);
            window->SetKey(KEY_E);
            
            invlist = new InventoryList(_link_player, {150, 580}, {100, 100}, _font);
            invlist->BindSelector(selected_item);
            window->addElement(invlist, {5, 22});

            hovereddesc = new Text("Hover an item, to see rich description", _font, 17, {0, 0});
            Vector2 hovereddesc_size = MeasureTextEx(*hovereddesc->Gfont->Rfont, "Hover an item, to see rich description", 17, 0); 
            hovereddescfield = new Field({285, hovereddesc_size.y + 2}, {0, 0}, { 130, 130, 130, 150});

            hoveredname = new Text("Nothing selected", _font, 37, {0, 0});
            hoveredtype = new Text("Type: test", _font, 22, {0, 0});
            hoveredstack = new Text("Stack size: 50", _font, 22, {0, 0});

            window->addElement(hoveredname, {160, 25});
            window->addElement(hovereddescfield, {160, 85});
            window->addElement(hovereddesc, {162, 85});
            window->addElement(hoveredtype, {160, 60});
            window->addElement(hoveredstack, {250, 60});
      }

      void SetUpItemManager(ItemManager *_itemmanager) { itemmanager = _itemmanager; }

      void Update() {
            if (invlist->hovered_element >= 0) { 
                  hoveredname->actext = itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id]["title"];
                  hoveredtype->actext = "Type: "+(std::string)itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id]["tags"]["type"]["title"];
                  hoveredtype->color = { itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id]["tags"]["type"]["color"][0], itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id]["tags"]["type"]["color"][1], itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id]["tags"]["type"]["color"][2], 255 };
                  
                  Vector2 hoveredtypesize = MeasureTextEx(*hovereddesc->Gfont->Rfont, hoveredtype->actext.c_str(), 22, 0);
                  hoveredstack->offset.x = hoveredtype->offset.x + hoveredtypesize.x + 5;
                  hoveredstack->actext = "Stack size: "+std::to_string((int)itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id]["stack_size"]);
                  
                  if (itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id].contains("tags")) {
                        if (itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id]["tags"].contains("description")) {
                              Vector2 hovereddesc_size = MeasureTextEx(*hovereddesc->Gfont->Rfont, ((std::string)itemmanager->ItemData[link_player->inventory->storage[invlist->hovered_element].item.id]["tags"]["description"]).c_str(), 17, 0); 
                              hovereddescfield->rect.height = hovereddesc_size.y;
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