#version 400 core

in vec3 color;
in vec2 pass_textureCoords;

out vec4 out_Color;

uniform sampler2D modelTexture;


void main(void) {
  out_Color = texture(modelTexture, pass_textureCoords);
}