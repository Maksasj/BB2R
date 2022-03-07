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

      void addElement(GuiElement *element, float of_x, float of_y) {
            element->offset.x = of_x; element->offset.y = of_y;
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