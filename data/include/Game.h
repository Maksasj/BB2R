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
      Window *window;
            
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

            window = new Window({450, 600}, {100, 100});
            window->setDraggable({450, 15});
            window->setTitle("Inventory", Gfont);
            window->color = {180, 180, 180, 150};
            window->addElement(new Hotbar(player, 6), {0, 0});
            window->addElement(new InventoryList(player, {150, 580}, {100, 100}, Gfont), {5, 17});
            window->addElement(new Text("Test Item", Gfont, 30, {100, 100}), {155, 25});
            window->addElement(new Text("Lorem ipsum dolor sit amet, consectetur \n adipiscing elit. Aliquam consequat arcu \n lacus, at tincidunt mi molestie a. Aliquam\n interdum ex in libero faucibus rhoncus. \n Integer pharetra leo vitae ex ultricies \n pharetra. Suspendisse vitae maximus felis. \n In euismod erat a leo fermentum, ut \n euismod tellus malesuada.", Gfont, 16, {100, 100}), {155, 80});
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
            if (IsKeyPressed(KEY_E)) { if(window->visible == false) { window->visible = true; } else { window->visible = false; }}

            BeginDrawing();
            ClearBackground(RAYWHITE);

            world->Render(player->x , player->y);
            player->Update();
            window->Update();

            texturemanager->UpdateAnimations();

            player->Render();

            DrawFPS(0, 0); 
            window->Render();

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