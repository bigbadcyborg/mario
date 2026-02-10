#include "LevelLoader.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace {

std::string trim(const std::string& value) {
    std::string::size_type start = 0;
    while (start < value.size() && std::isspace(static_cast<unsigned char>(value[start]))) {
        start++;
    }

    std::string::size_type end = value.size();
    while (end > start && std::isspace(static_cast<unsigned char>(value[end - 1]))) {
        end--;
    }

    return value.substr(start, end - start);
}

std::string stripQuotes(const std::string& value) {
    std::string cleaned = trim(value);
    if (cleaned.size() >= 2 && cleaned.front() == '"' && cleaned.back() == '"') {
        return cleaned.substr(1, cleaned.size() - 2);
    }
    return cleaned;
}

int parseInteger(const std::string& value) {
    return std::atoi(trim(value).c_str());
}

bool startsWith(const std::string& value, const std::string& prefix) {
    return value.size() >= prefix.size() && value.substr(0, prefix.size()) == prefix;
}

void parseJsonObject(const std::string& objectText, EntityRecord& entity) {
    std::stringstream stream(objectText);
    std::string pair;
    while (std::getline(stream, pair, ',')) {
        std::string::size_type separator = pair.find(':');
        if (separator == std::string::npos) {
            continue;
        }

        std::string key = stripQuotes(pair.substr(0, separator));
        std::string value = stripQuotes(pair.substr(separator + 1));

        if (key == "type") {
            entity.type = value;
        }
        else if (key == "x") {
            entity.x = parseInteger(value);
        }
        else if (key == "y") {
            entity.y = parseInteger(value);
        }
        else if (key == "width") {
            entity.width = parseInteger(value);
        }
        else if (key == "height") {
            entity.height = parseInteger(value);
        }
        else if (startsWith(key, "behavior.")) {
            entity.behaviorParams[key.substr(9)] = parseInteger(value);
        }
    }
}

void parseProgressionLine(const std::string& key, const std::string& value, LevelProgression& progression) {
    if (key == "startLevel") {
        progression.startLevel = parseInteger(value);
    }
    else if (key == "initialEnemyCount") {
        progression.initialEnemyCount = parseInteger(value);
    }
    else if (key == "initialCoinCount") {
        progression.initialCoinCount = parseInteger(value);
    }
    else if (key == "enemyIncrementPerLevel") {
        progression.enemyIncrementPerLevel = parseInteger(value);
    }
    else if (key == "maxLevel") {
        progression.maxLevel = parseInteger(value);
    }
}

} // namespace

LevelEntity::LevelEntity(const EntityRecord& record) : entityRecord(record) {}

const EntityRecord& LevelEntity::getRecord() const {
    return entityRecord;
}

EnemyEntity::EnemyEntity(const EntityRecord& record) : LevelEntity(record) {}
std::string EnemyEntity::category() const { return "enemy"; }

CoinEntity::CoinEntity(const EntityRecord& record) : LevelEntity(record) {}
std::string CoinEntity::category() const { return "coin"; }

ObstacleEntity::ObstacleEntity(const EntityRecord& record) : LevelEntity(record) {}
std::string ObstacleEntity::category() const { return "platform"; }

TubeEntity::TubeEntity(const EntityRecord& record) : LevelEntity(record) {}
std::string TubeEntity::category() const { return "tube"; }

PowEntity::PowEntity(const EntityRecord& record) : LevelEntity(record) {}
std::string PowEntity::category() const { return "pow"; }

std::vector<EntityRecord> LevelData::recordsByType(const std::string& entityType) const {
    std::vector<EntityRecord> records;
    for (std::size_t i = 0; i < entities.size(); i++) {
        if (entities[i]->category() == entityType) {
            records.push_back(entities[i]->getRecord());
        }
    }
    return records;
}

LevelData LevelLoader::load(const std::string& levelPath) const {
    const std::string extension = getExtension(levelPath);
    const std::string levelText = readFile(levelPath);

    if (extension == "json") {
        return parseJson(levelText);
    }
    if (extension == "yaml" || extension == "yml") {
        return parseYaml(levelText);
    }
    if (extension == "toml") {
        return parseToml(levelText);
    }

    throw std::runtime_error("Unsupported level file extension: " + extension);
}

LevelData LevelLoader::parseJson(const std::string& inputText) const {
    LevelData data;
    data.progression.startLevel = 1;
    data.progression.initialEnemyCount = 4;
    data.progression.initialCoinCount = 1;
    data.progression.enemyIncrementPerLevel = 2;
    data.progression.maxLevel = 6;

    std::stringstream stream(inputText);
    std::string line;
    bool inEntities = false;
    bool inProgression = false;
    while (std::getline(stream, line)) {
        std::string text = trim(line);
        if (text.find("\"entities\"") != std::string::npos) {
            inEntities = true;
            inProgression = false;
            continue;
        }
        if (text.find("\"progression\"") != std::string::npos) {
            inProgression = true;
            inEntities = false;
            continue;
        }

        if (inEntities && text.find('{') != std::string::npos) {
            EntityRecord entity;
            entity.x = 0;
            entity.y = 0;
            entity.width = 0;
            entity.height = 0;

            std::string objectText = text;
            while (objectText.find('}') == std::string::npos && std::getline(stream, line)) {
                objectText += trim(line);
            }
            parseJsonObject(objectText, entity);
            data.entities.push_back(createEntity(entity));
        }

        if (inProgression && text.find(':') != std::string::npos) {
            std::string cleaned = text;
            if (cleaned[cleaned.size() - 1] == ',') {
                cleaned = cleaned.substr(0, cleaned.size() - 1);
            }
            std::string::size_type separator = cleaned.find(':');
            const std::string key = stripQuotes(cleaned.substr(0, separator));
            const std::string value = stripQuotes(cleaned.substr(separator + 1));
            parseProgressionLine(key, value, data.progression);
        }
    }

    return data;
}

LevelData LevelLoader::parseYaml(const std::string& inputText) const {
    LevelData data;
    data.progression.startLevel = 1;
    data.progression.initialEnemyCount = 4;
    data.progression.initialCoinCount = 1;
    data.progression.enemyIncrementPerLevel = 2;
    data.progression.maxLevel = 6;

    std::stringstream stream(inputText);
    std::string line;
    EntityRecord current;
    bool activeEntity = false;
    bool inProgression = false;

    while (std::getline(stream, line)) {
        std::string text = trim(line);
        if (text.empty() || text[0] == '#') {
            continue;
        }

        if (text == "entities:") {
            inProgression = false;
            continue;
        }
        if (text == "progression:") {
            inProgression = true;
            if (activeEntity) {
                data.entities.push_back(createEntity(current));
                activeEntity = false;
            }
            continue;
        }

        if (startsWith(text, "- ")) {
            if (activeEntity) {
                data.entities.push_back(createEntity(current));
            }
            activeEntity = true;
            current.type = "";
            current.x = 0;
            current.y = 0;
            current.width = 0;
            current.height = 0;
            current.behaviorParams.clear();
            text = trim(text.substr(2));
        }

        std::string::size_type separator = text.find(':');
        if (separator == std::string::npos) {
            continue;
        }
        std::string key = trim(text.substr(0, separator));
        std::string value = trim(text.substr(separator + 1));

        if (inProgression) {
            parseProgressionLine(key, value, data.progression);
            continue;
        }

        if (key == "type") {
            current.type = stripQuotes(value);
        }
        else if (key == "x") {
            current.x = parseInteger(value);
        }
        else if (key == "y") {
            current.y = parseInteger(value);
        }
        else if (key == "width") {
            current.width = parseInteger(value);
        }
        else if (key == "height") {
            current.height = parseInteger(value);
        }
        else if (startsWith(key, "behavior.")) {
            current.behaviorParams[key.substr(9)] = parseInteger(value);
        }
    }

    if (activeEntity) {
        data.entities.push_back(createEntity(current));
    }

    return data;
}

LevelData LevelLoader::parseToml(const std::string& inputText) const {
    LevelData data;
    data.progression.startLevel = 1;
    data.progression.initialEnemyCount = 4;
    data.progression.initialCoinCount = 1;
    data.progression.enemyIncrementPerLevel = 2;
    data.progression.maxLevel = 6;

    std::stringstream stream(inputText);
    std::string line;
    EntityRecord current;
    bool inEntity = false;
    bool inProgression = false;

    while (std::getline(stream, line)) {
        std::string text = trim(line);
        if (text.empty() || text[0] == '#') {
            continue;
        }

        if (text == "[[entities]]") {
            if (inEntity) {
                data.entities.push_back(createEntity(current));
            }
            inEntity = true;
            inProgression = false;
            current.type = "";
            current.x = 0;
            current.y = 0;
            current.width = 0;
            current.height = 0;
            current.behaviorParams.clear();
            continue;
        }

        if (text == "[progression]") {
            if (inEntity) {
                data.entities.push_back(createEntity(current));
                inEntity = false;
            }
            inProgression = true;
            continue;
        }

        std::string::size_type separator = text.find('=');
        if (separator == std::string::npos) {
            continue;
        }

        std::string key = trim(text.substr(0, separator));
        std::string value = stripQuotes(trim(text.substr(separator + 1)));

        if (inProgression) {
            parseProgressionLine(key, value, data.progression);
            continue;
        }

        if (key == "type") {
            current.type = value;
        }
        else if (key == "x") {
            current.x = parseInteger(value);
        }
        else if (key == "y") {
            current.y = parseInteger(value);
        }
        else if (key == "width") {
            current.width = parseInteger(value);
        }
        else if (key == "height") {
            current.height = parseInteger(value);
        }
        else if (startsWith(key, "behavior.")) {
            current.behaviorParams[key.substr(9)] = parseInteger(value);
        }
    }

    if (inEntity) {
        data.entities.push_back(createEntity(current));
    }

    return data;
}

std::string LevelLoader::readFile(const std::string& levelPath) const {
    std::ifstream infile(levelPath.c_str());
    if (!infile) {
        throw std::runtime_error("Could not open level file: " + levelPath);
    }

    std::stringstream buffer;
    buffer << infile.rdbuf();
    return buffer.str();
}

std::string LevelLoader::getExtension(const std::string& levelPath) const {
    std::string::size_type dotPosition = levelPath.find_last_of('.');
    if (dotPosition == std::string::npos) {
        return "";
    }
    std::string extension = levelPath.substr(dotPosition + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    return extension;
}

std::unique_ptr<LevelEntity> LevelLoader::createEntity(const EntityRecord& record) const {
    if (record.type == "enemy") {
        return std::unique_ptr<LevelEntity>(new EnemyEntity(record));
    }
    if (record.type == "coin") {
        return std::unique_ptr<LevelEntity>(new CoinEntity(record));
    }
    if (record.type == "platform") {
        return std::unique_ptr<LevelEntity>(new ObstacleEntity(record));
    }
    if (record.type == "tube") {
        return std::unique_ptr<LevelEntity>(new TubeEntity(record));
    }
    if (record.type == "pow") {
        return std::unique_ptr<LevelEntity>(new PowEntity(record));
    }
    return std::unique_ptr<LevelEntity>(new ObstacleEntity(record));
}
