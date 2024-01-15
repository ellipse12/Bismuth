#include "widget.h"
#include <stdio.h>

static const float positions[] = { -1, 1, -1, -1,1, 1, 1, -1 };

void create_widget(Widget *widget, vec2 position, vec2 scale, Model* model) {
	glm_vec2_copy(position, widget->position);
	glm_vec2_copy(scale, widget->scale);
	widget->model = model;
}

void create_model_for_widget(Model* model, Texture* texture, const char* texture_file) {
	load_texture_data(texture_file, texture);
	model->texture = texture;
	load_to_vao(positions, sizeof(positions), texture, model);
	
}