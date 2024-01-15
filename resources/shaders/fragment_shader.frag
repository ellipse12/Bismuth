#version 400 core
in vec2 outTextureCoord;
uniform sampler2D texture_sampler;
out vec4 color;
void main(){
   color = texture(texture_sampler, outTextureCoord);
}