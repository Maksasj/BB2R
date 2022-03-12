#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include <raylib.h>
#include <string>

#include "Defines.h"
#include "Timer.h"

#include "TextureManager.h"
#include "ModLoader.h"
#include "ItemManager.h"
#include "World.h"
#include "Player.h"
#include "Hand.h"

#include "gui/Hotbar.h"
#include "gui/Font.h"
#include "gui/Text.h"
#include "gui/Field.h"
#include "gui/Window.h"
#include "gui/GuiElement.h"
#include "gui/Gui.h"
#include "gui/InventoryList.h"
#include "gui/PlayerInventory.h"

void ScreenShot() {
      std::string path = "screenshots/";
      std::string PATH = path;

      int s = 0;
      while(true) {
      
            bool exist = exists(path + "screenshot_" + std::to_string(s) + ".png");

            if (!exist) {
                  PATH = path + "screenshot_" + std::to_string(s) + ".png";
                  break;
            } else { s++; }
      }
      TakeScreenshot(PATH.c_str());
}

struct Game
{
      std::string state; bool game_running;

      ModLoader *modloader;
      TextureManager *texturemanager;
      ItemManager *itemmanager;

      World *world;
      Player *player;
      game::font *Gfont;
      Gui *gui;

      Game() {
            game_running = true;
            state = "main_menu";

            InitWindow(SCREEN_WIDTH, SCREEN_WIDTH, "raylib [core] example - basic window");
            
            ToggleFullscreen();
            LoadGame();

            modloader = new ModLoader();
            texturemanager = new TextureManager(modloader);

            itemmanager = new ItemManager();
            itemmanager->LoadFromMod(modloader->mods["base"]->ItemData);

            world = new World(texturemanager, modloader, "earth");
            player = new Player(texturemanager, 0, 0);
            player->SetUpHand(new Hand(world, modloader)); 
            player->SetUpNEU(itemmanager);

            Gfont = new game::font("data/assets/fonts/font.ttf");

            gui = new Gui();
            
            PlayerInventory *window = new PlayerInventory(player, {100, 100}, Gfont);
            window->SetUpItemManager(itemmanager);
            gui->addElement(window, {100, 100});

            Hotbar *hotbar = new Hotbar(player, 6);
            hotbar->SetUpTextureManager(texturemanager);
            gui->addElement(hotbar, {0, 0});
      }

      void CloseGame() {
            game_running = false;
            CloseWindow();
            
      }
      void LoadGame() {
            //modloader = new ModLoader();
      }

      void GameLoop() {
            if (IsKeyDown(KEY_F2)) { ScreenShot(); }
            
            BeginDrawing();

            ClearBackground(RAYWHITE);

            world->Render(player->x , player->y);
            player->Update();
            gui->Update();

            texturemanager->UpdateAnimations();

            player->Render();

            DrawFPS(0, 0); 
            gui->Render();
  
            EndDrawing();
            timer.Update();
      }

      void GameMenuLoop() {

            BeginDrawing();
            ClearBackground(RAYWHITE);
      
            player->Render();

            EndDrawing();

      }

      void MainLoop() {
            while(game_running) {
                  GameLoop();
            }
            CloseGame();
      }
};

#endif