#ifndef WORLDGENERATOR_CLASS_H
#define WORLDGENERATOR_CLASS_H

#include <iostream>
#include <stdio.h>

#include "Chunk.h"
#include "../Texture/TextureManager.h"
#include "../Mod/ModLoader.h"
#include "BiomeManager.h"

struct WorldGenerator
{   
    unsigned int seed;

    FastNoiseLite* noise;
    TextureManager *texturemanager;
    BiomeManager *biomemanager;

    WorldGenerator (TextureManager *_texturemanager, BiomeManager *_biomemanager, int SEED) {
        texturemanager = _texturemanager;
        biomemanager = _biomemanager;
        seed = SEED;

        noise = new FastNoiseLite;
        noise->SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    }

    Chunk* GenerateChunk(int x, int y) {
        Chunk* tmp_chunk;
        tmp_chunk = new Chunk(x, y);
        tmp_chunk->GenerateChunk(texturemanager, biomemanager, noise, x, y);
        return tmp_chunk;
    }
};

#endif