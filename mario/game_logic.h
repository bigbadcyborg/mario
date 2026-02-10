#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>

namespace logic {

struct Rect {
  int x;
  int y;
  int width;
  int height;
};

struct Platform {
  Rect bounds;
};

enum class EnemyCollisionType { none, stomp, side };

struct GravityResult {
  int newY;
  bool landed;
};

struct LevelProgress {
  int level;
  int enemiesToSpawn;
  int deadEnemies;
};

struct GameState {
  int score;
  int lives;
  LevelProgress level;
};

bool intersectsInclusive(const Rect &left, const Rect &right);
bool intersectsExclusive(const Rect &left, const Rect &right);

EnemyCollisionType classifyPlayerEnemyCollision(const Rect &player,
                                                const Rect &enemy,
                                                int stompTolerance = 0);

GravityResult applyGravity(const Rect &actor, int velocity, int worldFloorY,
                           const std::vector<Platform> &platforms);

void onEnemyStomp(GameState &state);
void onCoinCollected(GameState &state);
void onPlayerHit(GameState &state);
void onLevelCleared(GameState &state);

} // namespace logic

#endif
