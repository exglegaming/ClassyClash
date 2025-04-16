#include "raylib.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 getWorldPos() { return worldPos; }
    void undoMovement();
    Rectangle getCollisionRec();
    virtual void tick(float deltaTime);
    bool getAlive() { return alive; }
    void setAlive(bool isAlive) { alive = isAlive; }
protected:
    Texture2D texture{LoadTexture("../characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("../characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("../characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldLastFrame{};
    // 1: Facing right, -1: Facing Left
    float rightLeft{1.f};
    // animation variables
    float runningTimne{};
    int frame{};
    const int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};
private:
    bool alive{true};
};

#endif