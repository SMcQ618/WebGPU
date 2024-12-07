#version 450

// this is still a comment
layout(location = 0) out vec2 position;
layout(location = 1) in vec2 cell;

layout(set = 0, binding = 0) uniform vec2 grid;
layout(set = 0, binding = 1) buffer CellState {
    uint cellState[];
};

void main() {
    uint instance = gl_InstanceIndex;
    vec2 cell = vec2(float(instance) % grid.x, floor(float(instance) / grid.x));

    float state = float(cellState[instance]);

    vec2 cellOffset = cell / grid * 2.0;
    vec2 gridPos = (position * state + 1.0) / grid - 1.0 + cellOffset;

    gl_SamplePosition = vec4(gridPos, 0.0, 1.0);
}