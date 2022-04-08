#ifndef LIGHTSYSTEM_CLASS_H
#define LIGHTSYSTEM_CLASS_H

#include <raylib.h>
#include "../Defines.h"
#include "../Renderer/Shader.h"
#include "../Utilities/vector.h"

typedef struct {
    vec2 pos;
    float inner;
    float radius;

    unsigned int posLoc;
    unsigned int innerLoc;
    unsigned int radiusLoc;
} Spot;

struct LightSystem
{    
      const int MAX_LIGHT = 50;
      Spot spots[50];
      int light_count;

      float x, y;

      LightSystem(Shader shader) {
            light_count = 0;
            x = y = 0;

            for (int i = 0; i < MAX_LIGHT; i++)
            {
                  std::string pos_Name = "spots[" + std::to_string(i) + "].pos\0";
                  std::string inner_Name = "spots[" + std::to_string(i) + "].inner\0";
                  std::string radius_Name = "spots[" + std::to_string(i) + "].radius\0";

                  spots[i].posLoc = GetShaderLocation(shader.shader, pos_Name.c_str());
                  spots[i].innerLoc = GetShaderLocation(shader.shader, inner_Name.c_str());
                  spots[i].radiusLoc = GetShaderLocation(shader.shader, radius_Name.c_str());
                  
                  spots[i].pos = {1, 0};

                  spots[i].inner = 28.0f * (i + 1);
                  spots[i].radius = 48.0f * (i + 1);

                  SetShaderValue(shader.shader, spots[i].posLoc, &spots[i].pos.x, SHADER_UNIFORM_VEC2);
                  SetShaderValue(shader.shader, spots[i].innerLoc, &spots[i].inner, SHADER_UNIFORM_FLOAT);
                  SetShaderValue(shader.shader, spots[i].radiusLoc, &spots[i].radius, SHADER_UNIFORM_FLOAT);

            }
      }

      void SetPlayerPos(vec2 pos) {
            x = pos.x; y = pos.y;
      }

      void LoadLight(vec2 pos, vec3 color) {
            if (light_count < MAX_LIGHT) {
                  float X_c = ((pos.x - x)/HALF_SCREEN_WIDTH)*0.90;
                  float Y_c = -((pos.y - y)/SCREEN_HEIGHT);

                  spots[light_count].pos = { X_c, Y_c };
                  light_count++;
            }

      }

      void UnloadLight() {
            for(int x = 0; x < MAX_LIGHT; x++) { spots[x].pos = {0, 0}; }
            light_count = 0;
      }

      void SetLightUniforms(Shader shader) {
            shader.SetUniform("light_count", &light_count, SHADER_UNIFORM_INT);
            for (int i = 0; i < MAX_LIGHT; i++){
                  SetShaderValue(shader.shader, spots[i].posLoc, &spots[i].pos.x, SHADER_UNIFORM_VEC2);
            }
      }
};

#endif