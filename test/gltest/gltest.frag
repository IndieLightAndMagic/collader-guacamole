#version 330 core
// It was expressed that some drivers required this next line to function properly
precision highp float;

in  vec3 ex_Color;
out vec4 v4_FragColor;

void main(void) {
    // Pass through our original color with full opacity.
    v4_FragColor = vec4(ex_Color,1.0);
}