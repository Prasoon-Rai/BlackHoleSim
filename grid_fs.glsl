#version 330
in vec3 fragPosition;
out vec4 fragColor;

uniform float gridSpacing; // e.g., 1.0
uniform float gridWidth;   // e.g., 0.02
uniform vec4 lineColor;   // e.g., Dark Gray

void main() {
    float x = fragPosition.x;
    float z = fragPosition.z;

    float fx = abs(x);
    float fz = abs(z);

    float lineX = mod(fx, gridSpacing);
    float lineZ = mod(fz, gridSpacing);

    bool isLineX = lineX < gridWidth;
    bool isLineZ = lineZ < gridWidth;

    if (isLineX || isLineZ) {
        fragColor = lineColor;
    } else {
        discard;
    }
}