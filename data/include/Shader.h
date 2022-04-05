#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <iostream>
#include <raylib.h>
#include <map>

struct Shader
{   
    ShadeRaylib shader;
    std::map<std::string, int> ShaderUnifroms;

    void LoadFragmentShader() {
        shader = LoadShader(0, TextFormat("data/assets/shaders/base.fs", 330));
    }

    void LocateUniform(std::string _id) {
        int loc = GetShaderLocation(shader, _id.c_str());
        if (loc != -1) { ShaderUnifroms[_id] = loc;  }
    }

    void SetUniform(std::string _id, const void *value, int uniformType) {
        SetShaderValue(shader, ShaderUnifroms[_id], value, uniformType);
    }   

    void SetUniformArray(std::string _id, const void *value, int uniformType, int size) {
        SetShaderValueV(shader, ShaderUnifroms[_id], value, uniformType, size);
    }   

    void Activate() {
        BeginShaderMode(shader);
    }
    void Deactivate() {
        EndShaderMode(); 
    }
};

#endif