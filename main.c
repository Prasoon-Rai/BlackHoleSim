#include <stdio.h>
#include <raylib.h>

const int HEIGHT = 800;
const int WIDTH = 1200;

int main(void) {
    InitWindow(WIDTH, HEIGHT, "CLow");
    SetTargetFPS(60);

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

        DrawSphere((Vector3){ 0.0f, 1.0f, 0.0f }, 3.0f, BLACK);

        DrawGrid(50, 1.0f);

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}