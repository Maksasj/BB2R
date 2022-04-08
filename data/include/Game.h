#ifndef GAME_CLASS_H
#define GAME_CLASS_H

#include <raylib.h>
#include <string>

#include "Defines.h"
#include "Timer.h"

#include "Texture/TextureManager.h"
#include "Mod/ModLoader.h"
#include "Mod/ItemManager.h"
#include "World/World.h"
#include "World/Planet.h"
#include "Player/Player.h"
#include "Player/Hand.h"

#include "Renderer/Shader.h"
#include "Renderer/LightSystem.h"
#include "Gui/Hotbar.h"
#include "Gui/Font.h"
#include "Gui/Text.h"
#include "Gui/Field.h"
#include "Gui/Window.h"
#include "Gui/GuiElement.h"
#include "Gui/Gui.h"
#include "Gui/InventoryList.h"
#include "Gui/PlayerInventory.h"

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

      Planet *planet;
      Player *player;
      game::font *Gfont;
      Gui *gui;

      Shader shader;
      //LightSystem *lightsystem;

      Game() {
            game_running = true;
            state = "main_menu";

            InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "BB2R");
            
            ToggleFullscreen();
            LoadGame();

            //shader.LoadFragmentShader();
            //shader.LocateUniform("ambient_light");
            //shader.LocateUniform("light_count");
            /*

            shader.LocateUniform("light_count");
            shader.LocateUniform("light_pos_x");
            shader.LocateUniform("light_pos_y");
            */
            //lightsystem = new LightSystem(shader);

            modloader = new ModLoader();
            texturemanager = new TextureManager(modloader);

            itemmanager = new ItemManager();
            itemmanager->LoadFromMod(modloader->mods["base"]->ItemData);


            planet = new Planet(texturemanager, modloader);

            player = new Player(texturemanager, 0, 0);
            player->SetUpHand(new Hand(planet->world, modloader)); 
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
            if (IsKeyPressed(KEY_P)) { planet->day_lenght *= 1.05; }
            if (IsKeyPressed(KEY_M)) { planet->day_lenght *= 0.95; }
            
            //float ambient_light = planet->ambient_light;
            //shader.SetUniform("ambient_light", &ambient_light, SHADER_UNIFORM_FLOAT);
            
            planet->Update(player);
            //planet->GetLight(lightsystem, player);

            player->Update();
            gui->Update();
            
            //lightsystem->SetPlayerPos({player->x, player->y});
            //lightsystem->SetLightUniforms(shader);

            BeginDrawing();
            ClearBackground(BLACK);

            texturemanager->UpdateAnimations();
            
            //Game world
                  planet->Render(shader, player);
                  player->Render(shader);

            //Light Overlay
            /*
            shader.Activate();
                  DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACK);
            shader.Deactivate();
            */

            //lightsystem->UnloadLight();

            DrawFPS(0, 0); 

            gui->Render();
  
            EndDrawing();
            timer.Update();
      }

      void GameMenuLoop() {

            BeginDrawing();
            ClearBackground(RAYWHITE);
      
            player->Render(shader);

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