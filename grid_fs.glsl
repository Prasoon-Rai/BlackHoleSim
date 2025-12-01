#version 330

// Input from vertex shader (interpolated world position)
in vec3 fragPosition;

// Output color
out vec4 fragColor;

// Uniforms for grid customization (set from the C code)
uniform float gridSpacing; // e.g., 1.0
uniform float gridWidth;   // e.g., 0.02
uniform vec4 lineColor;   // e.g., Dark Gray

void main() {
    // We only care about the X and Z coordinates (the horizontal plane)
    float x = fragPosition.x;
    float z = fragPosition.z;

    // Use absolute value to mirror the grid pattern across the axes
    float fx = abs(x);
    float fz = abs(z);

    // --- Grid Line Calculation ---

    // 1. Calculate the position within the current grid cell (remainder after division)
    // lineX will range from 0 to gridSpacing
    float lineX = mod(fx, gridSpacing);
    float lineZ = mod(fz, gridSpacing);

    // 2. Check if the line position is close to the start of the cell (0)
    bool isLineX = lineX < gridWidth;
    bool isLineZ = lineZ < gridWidth;

    // --- Center Axis (Optional: Thicker center lines) ---
    /*
    // Check if X or Z is very close to 0 (the world origin)
    bool isCenterAxis = (fx < gridWidth * 2.0) || (fz < gridWidth * 2.0);

    if (isLineX || isLineZ || isCenterAxis) {
        // ... set color based on line type ...
    }
    */

    // --- Final Color Output ---
    if (isLineX || isLineZ) {
        fragColor = lineColor;
    } else {
        // DISCARD the fragment (make it fully transparent).
        // This is what allows you to see the background/other objects.
        discard;
    }
}