#ifndef BIOME_CLASS_H
#define BIOME_CLASS_H

#include <iostream>
#include <string>
#include <vector>

struct Biome
{   
      std::string name; std::string tile;
      std::vector<std::pair<std::string, float>> blocks;

      float temp_max; float temp_min; 
      float humi_max; float humi_min;
      float hight_max; float hight_min;
      
      Biome(std::string _name, float _temp_max, float _temp_min, float _humi_max, float _humi_min, float _hight_max, float _hight_min, std::string _tile) {
            temp_max = _temp_max; temp_min = _temp_min;
            humi_max = _humi_max; humi_min = _humi_min;
            hight_max = _hight_max; hight_min = _hight_min;
            tile = _tile; name = _name;
      }

      bool CheckForReq(float temp, float derv, float hight) {
            if (temp < temp_max && temp > temp_min && derv < humi_max && derv > humi_min && hight < hight_max && hight > hight_min) { return true; } return false;
      }
};

#endif