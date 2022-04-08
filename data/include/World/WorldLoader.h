#ifndef WORLDLOADER_CLASS_H
#define WORLDLOADER_CLASS_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <json.h>
#include <sys/stat.h>
#include <stdio.h>

#include "Chunk.h"
#include "../Defines.h"
#include "../Texture/TextureManager.h"
#include "../Utilities/explode.h"

inline bool exists (const std::string& filename) {
  struct stat buffer;   
  return (stat (filename.c_str(), &buffer) == 0); 
}

struct WorldLoader
{   
    std::string path;
    TextureManager *texturemanager;
    nlohmann::json jsWorld;

    WorldLoader(std::string _path, TextureManager *_texturemanager) {

        std::ifstream ifs(_path);
        jsWorld = nlohmann::json::parse(ifs);
        ifs.close();

        texturemanager = _texturemanager;
        path = _path;
    }

    bool CheckChunk(int X, int Y) {
        std::string chunk_c_str = std::to_string(X) + "x" + std::to_string(Y);
        if (jsWorld["chunks"].contains(chunk_c_str)) {
            return false;
        } else { return true; }
    }

    Chunk* LoadChunk(int X, int Y) {
        std::string chunk_c_str = std::to_string(X) + "x" + std::to_string(Y);
        
        Chunk* tmp_chunk;
        tmp_chunk = new Chunk(X, Y);

        for(int x = 0; x < 16; x++) {   
            for(int y = 0; y < 16; y++) { 
                std::string tile_c_str = std::to_string(x*TILE_SIZE + X * CHUNK_SIZE) + "x" + std::to_string(y*TILE_SIZE + Y * CHUNK_SIZE);
                std::string EntityID = jsWorld["chunks"][chunk_c_str]["tiles"][tile_c_str]["EntityID"];
                tmp_chunk->tiles[x][y] = CreateTile(texturemanager, EntityID, CHUNK_SIZE*X + x*TILE_SIZE, CHUNK_SIZE*Y + y*TILE_SIZE);
                
                if(jsWorld["chunks"][chunk_c_str]["blocks"].contains(tile_c_str)) {
                    std::string EntityID_BLOCK = jsWorld["chunks"][chunk_c_str]["blocks"][tile_c_str]["EntityID"];
                    tmp_chunk->blocks[x][y] = CreateBlock(texturemanager, EntityID_BLOCK, CHUNK_SIZE*X + x*TILE_SIZE, CHUNK_SIZE*Y + y*TILE_SIZE);   
                }
            }
        }
        std::cout << "Succefully Loaded Chunk! " << chunk_c_str << std::endl;

        //tmp_chunk->blocks[0][0] = CreateBlock(texturemanager, CHUNK_SIZE*X + 0*TILE_SIZE, CHUNK_SIZE*Y + 0*TILE_SIZE);

        return tmp_chunk;
    }

    void LoadWorld(std::map<std::pair<int, int> , Chunk*> &world) {
        for (auto chunk = jsWorld["chunks"].begin(); chunk != jsWorld["chunks"].end(); ++chunk) {
            std::string cord_string = chunk.key();
            auto v = explode(cord_string, 'x');
            int X = atoi(v[0].c_str()); int Y = atoi(v[1].c_str());
            world[{X, Y}] = LoadChunk(X, Y);
        }
        
        std::cout << "Finished Loading World !" << std::endl;
    }

    /*
    void SaveWorld(Player player, std::map<std::pair<int, int> , Chunk*> world, std::string path) {

        std::string PATH;
        PATH = path;

        int s = 0;
        while(true) {
           
            bool exist = exists(path + "autosave" + std::to_string(s) + ".json");

            if (!exist) {
                PATH = path + "autosave" + std::to_string(s) + ".json";
                break;
            } else { s++; }
        }
        
        std::cout << PATH << std::endl;

        nlohmann::json JWorld;

        JWorld["player"] = {};
        JWorld["player"]["pos"] = {};
        JWorld["player"]["pos"]["x"] = player.x;
        JWorld["player"]["pos"]["y"] = player.y;

        JWorld["player"]["EntityState"] = player.EntityState;

        JWorld["chunks"] = {};

        for(std::pair<std::pair<int, int>, Chunk*> chunk_sheet : world) { 
            std::string chunk_cords_code = std::to_string(chunk_sheet.first.first) + "x" + std::to_string(chunk_sheet.first.second);
            
            JWorld["chunks"][chunk_cords_code] = {};
            JWorld["chunks"][chunk_cords_code]["tiles"] = {};
            JWorld["chunks"][chunk_cords_code]["blocks"] = {};
            
            for (int x = 0; x < CHUNK_TILE_WIDTH; x++) {
                for (int y = 0; y < CHUNK_TILE_WIDTH; y++) {
                    
                    if (chunk_sheet.second->tiles[x][y]) {
                        std::string tile_cords_code = std::to_string((int)(chunk_sheet.second->tiles[x][y]->x) ) + "x" + std::to_string( (int)(chunk_sheet.second->tiles[x][y]->y) );
                        
                        //Tile
                        JWorld["chunks"][chunk_cords_code]["tiles"][tile_cords_code] = {};
                        JWorld["chunks"][chunk_cords_code]["tiles"][tile_cords_code]["EntityID"] = chunk_sheet.second->tiles[x][y]->EntityID;
                        JWorld["chunks"][chunk_cords_code]["tiles"][tile_cords_code]["EntityState"] = chunk_sheet.second->tiles[x][y]->EntityState;
                    }

                    
                    if (chunk_sheet.second->blocks[x][y]) {
                        std::string tile_cords_code = std::to_string((int)(chunk_sheet.second->blocks[x][y]->x) ) + "x" + std::to_string( (int)(chunk_sheet.second->blocks[x][y]->y) );
                        
                        //Tile
                        JWorld["chunks"][chunk_cords_code]["blocks"][tile_cords_code] = {};
                        JWorld["chunks"][chunk_cords_code]["blocks"][tile_cords_code]["EntityID"] = chunk_sheet.second->blocks[x][y]->EntityID;
                        JWorld["chunks"][chunk_cords_code]["blocks"][tile_cords_code]["EntityState"] = chunk_sheet.second->blocks[x][y]->EntityState;
                    }
                    
                }
            }
        }

        std::ofstream file(PATH);
        file << JWorld;
        file.close();
    }

    */
};


#endif