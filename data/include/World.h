#ifndef WORLD_CLASS_H
#define WORLD_CLASS_H

#include <iostream>
#include <raylib.h>
#include <stdio.h>
#include <map>
#include <cmath>

#include "Chunk.h"
#include "Defines.h"
#include "TextureManager.h"
#include "ModLoader.h"

#include "WorldGenerator.h"
#include "WorldLoader.h"
#include "BiomeManager.h"

struct World
{
    std::map<std::pair<int, int> , Chunk*> _World;
    std::map<std::pair<int, int> , Chunk*> Chunks;

    WorldGenerator* worldgenerator;
    WorldLoader* worldloader;
    BiomeManager* biomemanager;

    std::string ptype;

    World(TextureManager *texturemanager, ModLoader *_modloader, std::string _ptype) {
        ptype = _ptype;

        std::cout << "Biome loading.. \n";
        biomemanager = new BiomeManager;
        biomemanager->LoadBiomes(_modloader, ptype);
        std::cout << "Succefully loaded biomes \n";

        worldgenerator = new WorldGenerator(texturemanager, biomemanager, 237);
        worldloader = new WorldLoader("saves/autosave69.json", texturemanager);
        worldloader->LoadWorld(_World);
        std::cout << _World.size() << std::endl;
    }

    /*
    void Save(Player player) {
        std::cout << _World.size() << std::endl;
        worldloader->SaveWorld(player, _World , "saves/");
    }
    */

    void LoadChunk(int x, int y) {
        if (worldloader->CheckChunk(x, y)) {
            _World[{x, y}] =  worldgenerator->GenerateChunk(x, y);
            Chunks[{x, y}] = _World[{x, y}]; 
        } else {
            std::cout << "Loading Chunk !" << std::endl;
            _World[{x, y}] = worldloader->LoadChunk(x, y);
            Chunks[{x, y}] = _World[{x, y}];
        }
    }

    bool checkBlock(int x, int y) {
        int X = floor(x / 1024); if (x < 0) { X--; }
        int Y = floor(y / 1024); if (y < 0) { Y--; }
        int px = abs(X*1024 - x)/64;
        int py = abs(Y*1024 - y)/64;
        return _World[{X, Y}]->block_exist[px][py];
    }

    Block* getBlock(int x, int y) {
        int X = floor(x / 1024); if (x < 0) { X--; }
        int Y = floor(y / 1024); if (y < 0) { Y--; }
        int px = abs(X*1024 - x)/64;
        int py = abs(Y*1024 - y)/64;
        return _World[{X, Y}]->blocks[px][py];
    }

    void Update(float x, float y) {
        int X = floor(x / CHUNK_SIZE);
        int Y = floor(y / CHUNK_SIZE);

        //conveyorsystemmanager.Update();


        Chunks[{X,Y}]->Update();
        Chunks[{X + 1, Y}]->Update();
        Chunks[{X + 1, Y +1}]->Update();
        Chunks[{X - 1,Y}]->Update();
        Chunks[{X - 1,Y - 1}]->Update();
        Chunks[{X + 1,Y - 1}]->Update();
        Chunks[{X - 1,Y + 1}]->Update();
        Chunks[{X,Y + 1}]->Update();
        Chunks[{X,Y - 1}]->Update();
    }

    void Render(float x, float y) {
        int X = floor(x / CHUNK_SIZE);
        int Y = floor(y / CHUNK_SIZE);

        if(Chunks[{X,Y}]) {
            Chunks[{X,Y}]->Render();
        } else { LoadChunk(X, Y); } 
        if(Chunks[{X + 1,Y}]) {
            Chunks[{X + 1, Y}]->Render();
        } else { LoadChunk(X + 1, Y); }
        if(Chunks[{X + 1,Y + 1}]) {
            Chunks[{X + 1, Y +1}]->Render();
        } else { LoadChunk(X + 1, Y + 1); }
        if(Chunks[{X - 1,Y}]) {
            Chunks[{X - 1,Y}]->Render();
        } else { LoadChunk(X - 1, Y); }
        if(Chunks[{X - 1,Y - 1}]) {
            Chunks[{X - 1,Y - 1}]->Render();
        } else { LoadChunk(X - 1, Y - 1); }
        if(Chunks[{X + 1,Y - 1}]) {
            Chunks[{X + 1,Y - 1}]->Render();
        } else { LoadChunk(X + 1, Y - 1);  }
        if(Chunks[{X - 1,Y + 1}]) {
            Chunks[{X - 1,Y + 1}]->Render();
        } else { LoadChunk(X - 1, Y + 1); }
        if(Chunks[{X,Y + 1}]) {
            Chunks[{X,Y + 1}]->Render();
        } else { LoadChunk(X, Y + 1); }
        if(Chunks[{X,Y - 1}]) {
            Chunks[{X,Y - 1}]->Render();
        } else { LoadChunk(X, Y - 1); }
    }
};

#endif