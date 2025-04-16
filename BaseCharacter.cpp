#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{
}

void BaseCharacter::undoMovement()
{
    worldPos = worldLastFrame;
}

Rectangle BaseCharacter::getCollisionRec()
{
    return Rectangle{
        screenPos.x,
        screenPos.y,
        width * scale,
        height * scale};
}

void BaseCharacter::tick(float deltaTime)
{
    worldLastFrame = worldPos;

    // update animation frame
    runningTimne += deltaTime;
    if (runningTimne >= updateTime)
    {
        frame++;
        runningTimne = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        // set worldPos = worldPois + direction
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }
    velocity = {};

    // Draw the Character
    Rectangle source{frame * width, 0.f, rightLeft * width, height};
    Rectangle dest{screenPos.x, screenPos.y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}