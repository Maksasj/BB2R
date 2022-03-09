#ifndef GUI_CLASS_H
#define GUI_CLASS_H

#include <iostream>
#include <vector>
#include <memory>

#include "Font.h"
#include "Text.h"
#include "Field.h"
#include "Window.h"
#include "GuiElement.h"

struct Gui
{   
      std::vector<std::unique_ptr<GuiElement>> GuiElements;

      Gui() {
      }

      void addElement(GuiElement *element, vec2 _offset) { 
            element->offset = {0, 0}; element->pos = _offset;
            GuiElements.emplace_back(element); 
      }

      void Update() {
            for(auto& element : GuiElements) { element->Update(); }
      }

      void Render() {
            for(auto& element : GuiElements) { element->Render(); }
      }
};

#endif