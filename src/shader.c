#include "shader.h"
#include "GL/glew.h"
#define __STDC_WANT_LIB_EXT1__ 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bind_attributes(Shader* shader);


void init_shader(Shader* shader, const char* vertex_file, const char* fragment_file){
	shader->vertex_id = load_shader_data(vertex_file, GL_VERTEX_SHADER);
	shader->fragment_id = load_shader_data(fragment_file, GL_FRAGMENT_SHADER);
	shader->program_id = glCreateProgram();
	glAttachShader(shader->program_id, shader->vertex_id);
	glAttachShader(shader->program_id, shader->fragment_id);
	bind_attributes(shader);
	glLinkProgram(shader->program_id);
	glValidateProgram(shader->program_id);
	
}

ui32 get_uniform_location(Shader* shader, const char* name) {
	return glGetUniformLocation(shader->program_id, name);
}

void bind_attributes(Shader* shader) {
	bind_attribute(shader, 0, "position");
	bind_attribute(shader, 1, "textureCoord");
}



void shader_bind(Shader* shader){
	glUseProgram(shader->program_id);
}
void shader_release(){
	glUseProgram(0);
}

void cleanup(Shader* shader){
	shader_release();
	glDetachShader(shader->program_id, shader->vertex_id);
	glDetachShader(shader->program_id, shader->fragment_id);
	glDeleteShader(shader->vertex_id);
	glDeleteShader(shader->fragment_id);
	glDeleteProgram(shader->program_id);

}

void bind_attribute(Shader* shader, ui32 attribute, const char* var){
	glBindAttribLocation(shader->program_id, attribute, var);
}

ui32 load_shader_data(const char* file, GLenum type){
	FILE* f;
	errno_t error = fopen_s(&f, file, "r");
	if (error != 0) {
		fprintf(stdout, "could not open file %s", file);
		exit(-1);
	}
	fseek(f, 0, SEEK_END);
	ui32 length = ftell(f) + 1;
	fseek(f, 0, SEEK_SET);
	char* buffer = malloc(length*sizeof(char));
	if (buffer == NULL) { exit(-1); }
	size_t newLen = fread(buffer, 1, length - 1, f);
	if (ferror(f) != 0) {
		printf("Error Reading File");
	}
	else {
		buffer[newLen++] = '\0';
	}

	ui32 shader = glCreateShader(type);
	
	glShaderSource(shader, 1, &buffer, &length);
	glCompileShader(shader);
	ui32 exception = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &exception);
	if ( exception == GL_FALSE) {
		
		ui32 len = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		char* log = malloc(len);
		glGetShaderInfoLog(shader, len , &len, log);
		fprintf(stderr, "Failed to compile shader; %s; %s",file, log);
		exit(-1);
	}
	fclose(f);
	free(buffer);
	
	return shader;
}