#version 330

// Input vertex attributes (from mesh)
in vec3 vertexPosition;

// Input uniform values (from raylib)
uniform mat4 mvp; // Model-view-projection matrix
uniform mat4 matModel; // Model matrix (for world position)

// Output to fragment shader
out vec3 fragPosition;

void main() {
    // Calculate world position and pass it to the fragment shader
    vec4 worldPos = matModel * vec4(vertexPosition, 1.0);
    fragPosition = worldPos.xyz;

    // Calculate final position
    gl_Position = mvp * vec4(vertexPosition, 1.0);
}