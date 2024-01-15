#pragma once
#include "defines.h"



GLFWwindow* create_window(const char* title, ui32 width, ui32 height);

void render(GLFWwindow* window);

void render_init();
