#version 330 core

out vec4 outCol;
uniform vec4 color;

void main()
{
	outCol = vec4(color); 
}