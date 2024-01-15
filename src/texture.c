#include "texture.h"
#include "lodepng.h"
#include <stdio.h>
#include <string.h>
#include "GL/glew.h"
#include <stdlib.h>


void load_texture_data(const char* filename, Texture* texture) {
	ui32 error;
	unsigned char* image = 0;
	ui32 width, height;
	error = lodepng_decode32_file(&image, &width, &height, filename);
	if (error != 0) {
		fprintf(stderr, "Could not find file %s", filename);
		exit(-1);
	}
	texture->filename = filename;
	texture->image_data = image;
	texture->texture_id = -1;
	texture->width = width;
	texture->height = height;
	texture->size = 4;
	texture->size *= width;
	texture->size *= height;
}

void gl_create_texture(Texture* texture) {
	ui32 texture_id;
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->image_data);
	glGenerateMipmap(GL_TEXTURE_2D);
	texture->texture_id = texture_id;
	store_in_attrib_list(1, 2, (f32*)texture->image_data, texture->size);
	
}




ui32 create_vao() {
	ui32 arrays;
	glGenVertexArrays(1, &arrays);
	glBindVertexArray(arrays);
	return arrays;
}

void store_in_attrib_list(ui32 number, ui32 coord_size, f32* data, isize data_size) {
	ui32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_STATIC_DRAW);
	glVertexAttribPointer(number, coord_size, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}


void load_to_vao(f32* positions, isize positions_length, Texture* texture, Model* model) {
	ui32 vaoID = create_vao();
	store_in_attrib_list(0, 2, positions, positions_length);
	glBindVertexArray(0);
	gl_create_texture(texture);
	model->texture = texture;
	model->vao_id = vaoID;
	model->vertex_count = positions_length / 2;

	
}