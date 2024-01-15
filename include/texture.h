#pragma once
#include "defines.h"
typedef struct {
	ui32 texture_id;
	const char* filename;
	unsigned char* image_data;
	isize width;
	isize height;
	isize size;
}Texture;

typedef struct {
	ui32 vao_id;
	isize vertex_count;
	Texture* texture;
}Model;

void gl_create_texture(Texture* texture);

void load_texture_data(const char* filename, Texture* texture);

void store_in_attrib_list(ui32 number, ui32 coord_size, f32* data, isize data_size);

ui32 create_vao();

void load_to_vao(f32* positions, isize positions_length, Texture* texture, Model* model);

