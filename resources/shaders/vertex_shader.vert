#version 400 core
in vec2 position;
//in vec2 textureCoord;

uniform mat4 transformation;

out vec2 outTextureCoord;
void main() {
    gl_Position = transformation * vec4(position, 0, 1);
    outTextureCoord = vec2((position.x+1.0)/2.0, 1.0 - (position.y+1.0)/2.0);
    
}