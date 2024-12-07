#version 450
layout(location = 0) out vec4 outColor;
layout(set = 0, binding = 0) uniform vec2 grid;

void main() {
    vec2 c = gl_FragCoord.xy / grid;
    outColor = vec4(c, 1.0 - c.x, 1.0);
}
