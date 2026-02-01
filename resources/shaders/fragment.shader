#version 330 core
layout(location = 0) out vec4 color;
uniform float u_Alpha;
void main() {
	color = vec4(0.1*u_Alpha, 0.8*u_Alpha, 0.5*u_Alpha, 1.0);
};