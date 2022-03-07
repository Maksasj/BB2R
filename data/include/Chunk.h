#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <iostream>
#include <raylib.h>
#include <stdio.h>

#include "Tile.h"
#include "Block.h"
#include "Defines.h"
#include "PerlinNoise/FastNoiseLite.h"
#include "BiomeManager.h"

struct Chunk
{
    Tile* tiles[16][16]; Block* blocks[16][16];
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

    void GenerateChunk(TextureManager *texturemanager, BiomeManager *biomemanager, FastNoiseLite *noise , int x, int y) {
        for(int x = 0; x < 16; x++) {   
            for(int y = 0; y < 16; y++) {

                
                if( (X == 0) && (Y == 0) && (x == 0) && (y == 0) ) {
                    std::cout << "Creating Marker \n";
                    block_exist[x][y] = true; 
                    blocks[x][y] = CreateBlock(texturemanager, "stone_wall", CHUNK_SIZE*X + x*TILE_SIZE, CHUNK_SIZE*Y + y*TILE_SIZE);
                }

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
    }

    void Render() {
        for(int x = 0; x < 16; x++) {
            for(int y = 0; y < 16; y++) {
                if (tile_exist[x][y])  {    tiles[x][y]->Render();  }
                if (block_exist[x][y]) {    blocks[x][y]->Render(); }
            }
        }
    }

};


#endif