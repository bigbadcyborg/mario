#include "game_logic.h"

#include <algorithm>

namespace logic {

namespace {

int bottom(const Rect &rect) { return rect.y + rect.height; }

int right(const Rect &rect) { return rect.x + rect.width; }

} // namespace

bool intersectsInclusive(const Rect &left, const Rect &rightRect) {
  return !(right(left) < rightRect.x || bottom(left) < rightRect.y ||
           left.x > right(rightRect) || left.y > bottom(rightRect));
}

bool intersectsExclusive(const Rect &left, const Rect &rightRect) {
  return !(right(left) <= rightRect.x || bottom(left) <= rightRect.y ||
           left.x >= right(rightRect) || left.y >= bottom(rightRect));
}

EnemyCollisionType classifyPlayerEnemyCollision(const Rect &player,
                                                const Rect &enemy,
                                                int stompTolerance) {
  if (!intersectsInclusive(player, enemy)) {
    return EnemyCollisionType::none;
  }

  const int playerBottom = bottom(player);
  const int enemyTop = enemy.y;
  const bool horizontallyOverlapping =
      right(player) > enemy.x && player.x < right(enemy);

  if (horizontallyOverlapping && playerBottom <= enemyTop + stompTolerance) {
    return EnemyCollisionType::stomp;
  }

  return EnemyCollisionType::side;
}

GravityResult applyGravity(const Rect &actor, int velocity, int worldFloorY,
                           const std::vector<Platform> &platforms) {
  const int maxY = worldFloorY - actor.height;
  int nextY = std::min(actor.y + velocity, maxY);
  bool landed = false;

  for (const Platform &platform : platforms) {
    const bool isAbovePlatform = actor.y + actor.height <= platform.bounds.y;
    const bool crossesTop = actor.y + actor.height <= platform.bounds.y &&
                            nextY + actor.height >= platform.bounds.y;
    const bool horizontallyOverlapping =
        right(actor) > platform.bounds.x && actor.x < right(platform.bounds);

    if (isAbovePlatform && crossesTop && horizontallyOverlapping) {
      nextY = std::min(nextY, platform.bounds.y - actor.height);
      landed = true;
    }
  }

  landed = landed || nextY == maxY;
  return GravityResult{nextY, landed};
}

void onEnemyStomp(GameState &state) {
  state.score += 1;
  state.level.deadEnemies += 1;
}

void onCoinCollected(GameState &state) { state.score += 1; }

void onPlayerHit(GameState &state) {
  state.lives = std::max(0, state.lives - 1);
}

void onLevelCleared(GameState &state) {
  state.level.level += 1;
  state.level.deadEnemies = 0;
  state.level.enemiesToSpawn += 2;
}

} // namespace logic
