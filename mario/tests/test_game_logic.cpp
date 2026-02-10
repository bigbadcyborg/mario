#include "../game_logic.h"

#include <cassert>
#include <iostream>
#include <vector>

using logic::EnemyCollisionType;
using logic::GameState;
using logic::Platform;
using logic::Rect;

void testBoundingBoxCollisionEdgeCases() {
  const Rect left{0, 0, 10, 10};
  const Rect touchingEdge{10, 0, 10, 10};
  const Rect overlap{9, 0, 10, 10};

  assert(logic::intersectsInclusive(left, touchingEdge));
  assert(!logic::intersectsExclusive(left, touchingEdge));
  assert(logic::intersectsExclusive(left, overlap));
}

void testPlayerEnemyStompVsSideCollision() {
  const Rect enemy{20, 20, 10, 10};
  const Rect stompingPlayer{20, 10, 10, 10};
  const Rect sidePlayer{10, 22, 10, 10};

  assert(logic::classifyPlayerEnemyCollision(stompingPlayer, enemy) ==
         EnemyCollisionType::stomp);
  assert(logic::classifyPlayerEnemyCollision(sidePlayer, enemy) ==
         EnemyCollisionType::side);
}

void testGravityAndPlatformLandingBehavior() {
  const Rect actor{5, 0, 10, 10};
  const std::vector<Platform> platforms{{Rect{0, 20, 40, 5}}};

  const logic::GravityResult result =
      logic::applyGravity(actor, 15, 100, platforms);
  assert(result.landed);
  assert(result.newY == 10);
}

void testLevelProgressionAndLivesScoreUpdates() {
  GameState state{0, 3, {1, 4, 0}};

  logic::onCoinCollected(state);
  logic::onEnemyStomp(state);
  assert(state.score == 2);
  assert(state.level.deadEnemies == 1);

  logic::onPlayerHit(state);
  assert(state.lives == 2);

  logic::onLevelCleared(state);
  assert(state.level.level == 2);
  assert(state.level.enemiesToSpawn == 6);
  assert(state.level.deadEnemies == 0);
}

int main() {
  testBoundingBoxCollisionEdgeCases();
  testPlayerEnemyStompVsSideCollision();
  testGravityAndPlatformLandingBehavior();
  testLevelProgressionAndLivesScoreUpdates();

  std::cout << "All game logic tests passed.\n";
  return 0;
}
