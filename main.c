#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

const int HEIGHT = 800;
const int WIDTH = 1200;

Shader gridShader;

int main(void) {
    InitWindow(WIDTH, HEIGHT, "CLow");
    SetTargetFPS(60);

    gridShader = LoadShader("grid_vs.glsl", "grid_fs.glsl");

    const float GRID_SPACING = 1.0f;
    const float GRID_WIDTH = 0.02f;
    const float QUAD_SIZE = 1000.0f;

    int spacingLoc = GetShaderLocation(gridShader, "gridSpacing");
    int widthLoc = GetShaderLocation(gridShader, "gridWidth");
    int lineColorLoc = GetShaderLocation(gridShader, "lineColor");

    Vector4 lineColor = { 0.5f, 0.5f, 0.5f, 1.0f }; // Dark Gray
    SetShaderValue(gridShader, spacingLoc, &GRID_SPACING, SHADER_UNIFORM_FLOAT);
    SetShaderValue(gridShader, widthLoc, &GRID_WIDTH, SHADER_UNIFORM_FLOAT);
    SetShaderValue(gridShader, lineColorLoc, &lineColor, SHADER_UNIFORM_VEC4);

    Model gridModel = LoadModelFromMesh(GenMeshPlane(QUAD_SIZE, QUAD_SIZE, 1, 1));
    gridModel.materials[0].shader = gridShader;


    Camera3D camera = { 0 };
    camera.position = (Vector3){ 4.0f, 4.0f, 4.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);
        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode3D(camera);

        DrawModel(gridModel, (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);

        DrawSphere((Vector3){0.0f, 1.0f, 0.0f}, 1.0f, BLACK);

        EndMode3D();
        EndDrawing();
    }
    UnloadModel(gridModel);
    UnloadShader(gridShader);
    CloseWindow();
    return 0;
}