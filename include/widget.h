#pragma once
#include "cglm/vec2.h"
#include "texture.h"
typedef struct {
	vec2 position;
	vec2 scale;
	Model* model;
}Widget;


void create_widget(Widget* widget, vec2 position, vec2 scale, Model* model);

void create_model_for_widget(Model* model, Texture* texture, const char* texture_file);

void is_mouse_over(Widget* widget, GLFWwindow* window);

