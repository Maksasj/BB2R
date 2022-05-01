#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <iostream>
#include <vector>
#include <raylib.h>
#include <stdio.h>

#include "../Renderer/Shader.h"
#include "../Prototype/Tile.h"
#include "../Prototype/Block.h"
#include "../Prototype/MobEntity.h"
#include "../Prototype/ItemEntity.h"

#include "../Defines.h"
#include "../PerlinNoise/FastNoiseLite.h"
#include "BiomeManager.h"

struct Chunk
{
    Tile* tiles[16][16]; Block* blocks[16][16];
    std::vector<MobEntity*>  mobs;
    std::vector<ItemEntity*> items;

    bool block_exist[16][16]; bool tile_exist[16][16];
    int X, Y;

    Chunk(int x, int y) {
        for(int Xr = 0; Xr < 16; Xr++) {   
            for(int Yr = 0; Yr < 16; Yr++) {
                block_exist[Xr][Yr] = false; tile_exist[Xr][Yr] = false;
            }
        }
        X = x; Y = y;  
    }
    
    void Update() {
        for(int x = 0; x < 16; x++) {   
            for(int y = 0; y < 16; y++) {
                if (block_exist[x][y] == true) {
                    blocks[x][y]->Update();    
                }
            }
        }
    }
    
    void GetLight(LightSystem *lightsystem) {
        for(int x = 0; x < 16; x++) {   
            for(int y = 0; y < 16; y++) {
                if (block_exist[x][y] == true) {
                    blocks[x][y]->GetLight(lightsystem); 
                }
            }
        }
    }

    std::string GetTile(BiomeManager *biomemanager, FastNoiseLite *noise , int x, int y) {
        double hight =  noise->GetNoise((float)(x + X*CHUNK_TILE_WIDTH)*biomemanager->noise_size, (float)(y + Y*CHUNK_TILE_WIDTH)*biomemanager->noise_size) +                   noise->GetNoise((float)(5*x + 5*X*CHUNK_TILE_WIDTH)*biomemanager->noise_size, (float)(5*y + 5*Y*CHUNK_TILE_WIDTH)*biomemanager->noise_size) * 0.5;
        double temp  =  noise->GetNoise((float)(x + X*CHUNK_TILE_WIDTH + 816516)*biomemanager->noise_size , (float)(y + Y*CHUNK_TILE_WIDTH + 1161)*biomemanager->noise_size) +  noise->GetNoise((float)(5*x + 5*X*CHUNK_TILE_WIDTH + 98146)*biomemanager->noise_size , (float)(5*y + 5*Y*CHUNK_TILE_WIDTH)*biomemanager->noise_size) * 0.5;
        double derv  =  noise->GetNoise((float)(x + X*CHUNK_TILE_WIDTH + 1165)*biomemanager->noise_size, (float)(y + Y*CHUNK_TILE_WIDTH + 7191)*biomemanager->noise_size) +     noise->GetNoise((float)(5*x + 5*X*CHUNK_TILE_WIDTH + 41894)*biomemanager->noise_size , (float)(5*y + 5*Y*CHUNK_TILE_WIDTH)*biomemanager->noise_size) * 0.5;
      
        for(auto biome : biomemanager->Biomes) {                    
            if (biome->CheckForReq(temp, derv, hight)) {
                return biome->tile;
            }
        }

        for (auto biome : biomemanager->Biomes) {
            if (biome->name == biomemanager->fill_biome) { return biome->tile; }
        }

        return "water_tile";
    }
    
    void ReloadConnections(BiomeManager *biomemanager, FastNoiseLite *noise) {
        for(int x = 0; x < 16; x++) {   
            for(int y = 0; y < 16; y++) {
                
                std::string x_yp1 = GetTile(biomemanager, noise, x, y + 1); //Down
                std::string x_ym1 = GetTile(biomemanager, noise, x, y - 1); //Up
                std::string xp1_y = GetTile(biomemanager, noise, x + 1, y); //Right
                std::string xm1_y = GetTile(biomemanager, noise, x - 1, y); //Left

                std::string c = tiles[x][y]->EntityID;

                if(biomemanager->modloader->mods["base"]->TileData[c]["texture"].contains("transition_animations")) {
                    for (std::string w : biomemanager->modloader->mods["base"]->TileData[c]["texture"]["transition_animations"]) {
                        if (xp1_y == w) { tiles[x][y]->EntityState = c+"_"+w+"_right"; }
                        if ( xm1_y == w) { tiles[x][y]->EntityState = c+"_"+w+"_left"; }
                        if (x_yp1 == w) { tiles[x][y]->EntityState = c+"_"+w+"_down"; }
                        if (x_yp1 == w && xm1_y == w) { tiles[x][y]->EntityState = c+"_"+w+"_left_down"; }
                        if (x_yp1 == w && xp1_y == w) { tiles[x][y]->EntityState = c+"_"+w+"_right_down"; }
                        if (x_ym1 == w) { tiles[x][y]->EntityState = c+"_"+w+"_up"; }
                        if (x_ym1 == w && xm1_y == w) { tiles[x][y]->EntityState = c+"_"+w+"_left_up"; }
                        if (x_ym1 == w && xp1_y == w) { tiles[x][y]->EntityState = c+"_"+w+"_right_up"; }
                    }
                }
            }
        }
    }

    void GenerateChunk(TextureManager *texturemanager, BiomeManager *biomemanager, FastNoiseLite *noise , int x, int y) {
        double start_time = GetTime(); 
        
        for(int x = 0; x < 16; x++) {   
            for(int y = 0; y < 16; y++) {
                tiles[x][y] = CreateTile(texturemanager, "clear_grass_tile", CHUNK_SIZE*X + x*TILE_SIZE, CHUNK_SIZE*Y + y*TILE_SIZE); 
                
                tiles[x][y]->subgroup = "farmable_soil";
                
                tile_exist[x][y] = true;
            }
        }

        /*
        for(int x = 0; x < 16; x++) {   
            for(int y = 0; y < 16; y++) {

                //Noises
                double hight =  noise->GetNoise((float)(x + X*CHUNK_TILE_WIDTH)*biomemanager->noise_size, (float)(y + Y*CHUNK_TILE_WIDTH)*biomemanager->noise_size) +                   noise->GetNoise((float)(5*x + 5*X*CHUNK_TILE_WIDTH)*biomemanager->noise_size, (float)(5*y + 5*Y*CHUNK_TILE_WIDTH)*biomemanager->noise_size) * 0.5;
                double temp  =  noise->GetNoise((float)(x + X*CHUNK_TILE_WIDTH + 816516)*biomemanager->noise_size , (float)(y + Y*CHUNK_TILE_WIDTH + 1161)*biomemanager->noise_size) +  noise->GetNoise((float)(5*x + 5*X*CHUNK_TILE_WIDTH + 98146)*biomemanager->noise_size , (float)(5*y + 5*Y*CHUNK_TILE_WIDTH)*biomemanager->noise_size) * 0.5;
                double derv  =  noise->GetNoise((float)(x + X*CHUNK_TILE_WIDTH + 1165)*biomemanager->noise_size, (float)(y + Y*CHUNK_TILE_WIDTH + 7191)*biomemanager->noise_size) +     noise->GetNoise((float)(5*x + 5*X*CHUNK_TILE_WIDTH + 41894)*biomemanager->noise_size , (float)(5*y + 5*Y*CHUNK_TILE_WIDTH)*biomemanager->noise_size) * 0.5;
      
                //Create tile according to biome
                for(auto biome : biomemanager->Biomes) {                    
                    if (tile_exist[x][y] == false && biome->CheckForReq(temp, derv, hight)) {
                        //Placing Tile
                        tiles[x][y] = CreateTile(texturemanager, biome->tile, CHUNK_SIZE*X + x*TILE_SIZE, CHUNK_SIZE*Y + y*TILE_SIZE); tile_exist[x][y] = true;

                        //Placing Block
                        for (auto block : biome->blocks) {
                            float bchance = rand() % 100 / 100.0;
                            if (block.second > bchance && block_exist[x][y] == false) { block_exist[x][y] = true; blocks[x][y] = CreateBlock(texturemanager, block.first, CHUNK_SIZE*X + x*TILE_SIZE, CHUNK_SIZE*Y + y*TILE_SIZE); break; }
                        } break;
                    }
                }

                //Fill free space
                if (tile_exist[x][y] == false) {
                    for (auto biome : biomemanager->Biomes) {
                        if (biome->name == biomemanager->fill_biome) {
                            //Placing Tile
                            tiles[x][y] = CreateTile(texturemanager, biome->tile, CHUNK_SIZE*X + x*TILE_SIZE, CHUNK_SIZE*Y + y*TILE_SIZE);  tile_exist[x][y] = true; 
                            
                            //Placing Block
                            for (auto block : biome->blocks) {
                                float bchance = rand() % 100 / 100.0;
                                if (block.second > bchance) { block_exist[x][y] = true; blocks[x][y] = CreateBlock(texturemanager, block.first, CHUNK_SIZE*X + x*TILE_SIZE, CHUNK_SIZE*Y + y*TILE_SIZE); break; }
                            } break;
                        }
                    }
                    
                }
            }
        }
        */

        //ReloadConnections(biomemanager, noise);
        std::cout << "Generated Chunk , time eclipsed: " << GetTime() - start_time << " seconds \n";
    }

    void Render(Shader shader) {
        for(int x = 0; x < 16; x++) {
            for(int y = 0; y < 16; y++) {
                if (tile_exist[x][y])  {    tiles[x][y]->Render(shader);  }
            }
        }

        for(int x = 0; x < 16; x++) {
            for(int y = 0; y < 16; y++) {
                if (block_exist[x][y]) {    blocks[x][y]->Render(shader); }
            }
        }

        for(auto item : items) {
            item->Render(shader);
        }
    }
};


#endif