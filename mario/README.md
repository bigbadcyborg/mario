# Mario Level Data

Levels are loaded from `mario/assets/levels/` by `LevelLoader`.

## Entity schema

Each level file may define entity records with:
- `type` (enemy, coin, platform, tube, pow)
- `x`
- `y`
- `width`
- `height`
- optional behavior params prefixed as `behavior.*` (example: `behavior.direction`)

## Progression schema

- `startLevel`
- `initialEnemyCount`
- `initialCoinCount`
- `enemyIncrementPerLevel`
- `maxLevel`

Supported level file formats: JSON, YAML, and TOML.
