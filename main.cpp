#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main()
{
    // Create window dimensions
    int windowDimensions[2]{384, 384};
    InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash");

    // Load map into program
    Texture2D map = LoadTexture("../nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.0f};

    Character knight{windowDimensions[0], windowDimensions[1]};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("../nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("../nature_tileset/Log.png")}};

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("../characters/goblin_idle_spritesheet.png"),
        LoadTexture("../characters/goblin_run_spritesheet.png")};

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("../characters/slime_idle_spritesheet.png"),
        LoadTexture("../characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    goblin.setTarget(&knight);

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // Start Drawing
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // Draw the map
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        // Draw the props
        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive()) // character is not alive
        {
            DrawText("Game OVER!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // character is alive
        {
            std::string knightsHealth = "Health: ";
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowDimensions[0] > map.width * mapScale ||
            knight.getWorldPos().y + windowDimensions[1] > map.height * mapScale)
        {
            knight.undoMovement();
        }

        // check prop collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        // Stop Drawing
        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}