#version 330 core
precision highp float;

in vec2 fragUV;
in vec4 fragNormal;

out vec4 gl_FragColor;

uniform sampler2D textureSampler;

void main(void) {

    vec2 newUV;
    newUV = vec2(fragUV.x, 1.0 - fragUV.y);
	gl_FragColor = texture(textureSampler, newUV);
}
