#version 330 core
layout(location=0) in vec3 position;
layout(location=1) in vec2 uv;
layout(location=2) in vec3 normal;

out vec2 fragUV;
out vec4 fragNormal;

uniform mat4 MVP;

void main(){
    vec4 v = vec4(position,1);
    gl_Position = MVP * v;
	fragUV = uv;
	fragNormal = vec4(normal,0);
}
