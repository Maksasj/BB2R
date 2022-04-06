#ifndef PARTICLEGENERATOR_CLASS_H
#define PARTICLEGENERATOR_CLASS_H

#include <iostream>
#include <raylib.h>

#include "../Shader.h"
#include "../Timer.h"
#include "../World.h"
#include "../TextureManager.h"
#include "../utilities/vector.h"

typedef struct {
      vec2 pos;
      vec2 vel;

      int live;
} Particle;

struct ParticleGenerator
{    
      std::vector<Particle> Particles;
      game::Texture *tex;
      vec2 pos;

      int MAX_PARTICLE_COUNT;

      ParticleGenerator(vec2 _pos, int _max_p) {
            MAX_PARTICLE_COUNT = _max_p;
            pos = _pos;

            for(int x = 0; x < _max_p; x++) {
                  Particle tmp_particle;
                  tmp_particle.live = GetRandomValue(0, 120);
                  tmp_particle.pos = _pos;

                  float velX = ((float)GetRandomValue(-30, 30))/100.0; 
                  float velY = ((float)GetRandomValue(-100, 10))/100.0; 
                  
                  tmp_particle.vel = {velX, velY};
                  Particles.push_back(tmp_particle);
            }
      }

      void Update() {
            for (auto &particle : Particles) {
                  if (particle.live <= 120) {
                        particle.live++;
                        particle.pos.x += particle.vel.x;
                        particle.pos.y += particle.vel.y;
                  } else {
                        particle.live = 0;
                        particle.pos = pos;
                  }
            }
      }
      void Render() {
            for (auto particle : Particles) {
                  tex->Render("fire_particle_idle", particle.pos.x - camera.x, particle.pos.y - camera.y);
            }
      }
};


#endif