#ifndef LEVEL_LOADER_H_INCLUDED
#define LEVEL_LOADER_H_INCLUDED

#include <map>
#include <memory>
#include <string>
#include <vector>

struct EntityRecord {
    std::string type;
    int x;
    int y;
    int width;
    int height;
    std::map<std::string, int> behaviorParams;
};

class LevelEntity {
public:
    explicit LevelEntity(const EntityRecord& record);
    virtual ~LevelEntity() {}
    virtual std::string category() const = 0;
    const EntityRecord& getRecord() const;

protected:
    EntityRecord entityRecord;
};

class EnemyEntity : public LevelEntity {
public:
    explicit EnemyEntity(const EntityRecord& record);
    std::string category() const;
};

class CoinEntity : public LevelEntity {
public:
    explicit CoinEntity(const EntityRecord& record);
    std::string category() const;
};

class ObstacleEntity : public LevelEntity {
public:
    explicit ObstacleEntity(const EntityRecord& record);
    std::string category() const;
};

class TubeEntity : public LevelEntity {
public:
    explicit TubeEntity(const EntityRecord& record);
    std::string category() const;
};

class PowEntity : public LevelEntity {
public:
    explicit PowEntity(const EntityRecord& record);
    std::string category() const;
};

struct LevelProgression {
    int startLevel;
    int initialEnemyCount;
    int initialCoinCount;
    int enemyIncrementPerLevel;
    int maxLevel;
};

struct LevelData {
    std::vector<std::unique_ptr<LevelEntity> > entities;
    LevelProgression progression;

    std::vector<EntityRecord> recordsByType(const std::string& entityType) const;
};

class LevelLoader {
public:
    LevelData load(const std::string& levelPath) const;

private:
    LevelData parseJson(const std::string& inputText) const;
    LevelData parseYaml(const std::string& inputText) const;
    LevelData parseToml(const std::string& inputText) const;
    std::string readFile(const std::string& levelPath) const;
    std::string getExtension(const std::string& levelPath) const;
    std::unique_ptr<LevelEntity> createEntity(const EntityRecord& record) const;
};

#endif
