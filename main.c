#include "raylib.h"
#include <math.h>

#define GRID_SIZE 80
#define HALF_GRID (GRID_SIZE / 2)

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Black Hole Simulation");
    SetTargetFPS(120);

    Camera3D camera = {0};
    camera.position = (Vector3){ 60.0f, 50.0f, 60.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 grid[GRID_SIZE][GRID_SIZE];

    // Initialize grid positions
    for (int x = 0; x < GRID_SIZE; x++)
    {
        for (int z = 0; z < GRID_SIZE; z++)
        {
            grid[x][z] = (Vector3){ x - HALF_GRID, 0.0f, z - HALF_GRID };
        }
    }

    Vector3 blackHolePos = { 0.0f, 0.0f, 0.0f };
    float blackHoleMass = 50.0f;
    float radius = 2.5f;

    while (!WindowShouldClose())
    {
        UpdateCamera(&camera, CAMERA_FREE);

        float time = GetTime();

        // Apply deformation for curvature
        for (int x = 0; x < GRID_SIZE; x++)
        {
            for (int z = 0; z < GRID_SIZE; z++)
            {
                float dx = grid[x][z].x - blackHolePos.x;
                float dz = grid[x][z].z - blackHolePos.z;
                float dist = sqrtf(dx*dx + dz*dz);

                float well = -blackHoleMass / (dist + radius);
                float wave = sinf(time * 2.5f + dist * 0.5f) * 0.4f;

                grid[x][z].y = well + wave;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);

        // Wireframe grid lines
        for (int x = 0; x < GRID_SIZE; x++)
        {
            for (int z = 0; z < GRID_SIZE - 1; z++)
            {
                DrawLine3D(grid[x][z], grid[x][z+1], WHITE);
            }
        }

        for (int z = 0; z < GRID_SIZE; z++)
        {
            for (int x = 0; x < GRID_SIZE - 1; x++)
            {
                DrawLine3D(grid[x][z], grid[x+1][z], GRAY);
            }
        }

        // Draw black hole representation
        DrawSphere(blackHolePos, 3.0f, BLACK);

        EndMode3D();

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
