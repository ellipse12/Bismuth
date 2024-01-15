#pragma once
#include "defines.h"
typedef struct {
	ui32 program_id;
	ui32 vertex_id;
	ui32 fragment_id;

}Shader;

void init_shader(Shader* shader, const char* vertex_file, const char* fragment_file);


void shader_bind(Shader* shader);
void shader_release();
void shader_cleanup(Shader* shader);

void bind_attribute(Shader* shader, ui32 attribute, const char* var);

ui32 load_shader_data(const char* file, GLenum type);

ui32 get_uniform_location(Shader* shader, const char* name);