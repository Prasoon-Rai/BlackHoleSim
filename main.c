#include "raylib.h"
#include "raymath.h"

void DeformMesh(Mesh *mesh, Vector3 holePosition, float holeMass) {
    for (int i = 0; i < mesh->vertexCount; i++) {
        float x = mesh->vertices[i * 3 + 0];
        float z = mesh->vertices[i * 3 + 2];

        float distSq = pow(x - holePosition.x, 2) + pow(z - holePosition.z, 2);
        float dist = sqrt(distSq);

        if (dist < 0.1f) dist = 0.1f;

        float newY = -holeMass / dist;

        if (newY < -5.0f) newY = -5.0f;

        mesh->vertices[i * 3 + 1] = newY;
    }
    UpdateMeshBuffer(*mesh, 0, mesh->vertices, mesh->vertexCount * 3 * sizeof(float), 0);
}

int main(void) {
    const int screenWidth = 1920;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Black Hole Simulation");

    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Mesh gridMesh = GenMeshPlane(20, 20, 50, 50);
    Model gridModel = LoadModelFromMesh(gridMesh);

    Vector3 holePos = { 0.0f, 0.0f, 0.0f };
    float holeMass = 3.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {

        DeformMesh(&gridMesh, holePos, holeMass);

        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
            ClearBackground(BLACK);

            BeginMode3D(camera);

                DrawModelWires(gridModel, (Vector3){0,0,0}, 1.0f, RAYWHITE);
                DrawSphere(holePos, 0.5f, BLACK);

            EndMode3D();
        EndDrawing();
    }

    UnloadModel(gridModel);
    CloseWindow();

    return 0;
}