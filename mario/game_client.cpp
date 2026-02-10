#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "net/protocol/protocol.h"

namespace {

using mario::net::protocol::InputCommand;
using mario::net::protocol::MessageType;
using mario::net::protocol::PlayerState;
using mario::net::protocol::Snapshot;
using mario::net::protocol::kInputCommandVersion;

struct SnapshotHistory {
    Snapshot previous;
    Snapshot latest;
    bool hasPrevious;

    SnapshotHistory() : hasPrevious(false) {}
};

class GameClient {
public:
    GameClient(std::uint32_t playerId) : playerId_(playerId), nextSequence_(1) {}

    InputCommand captureLocalInput(std::uint32_t tick, const std::string& userInput) {
        InputCommand command;
        command.header.version = kInputCommandVersion;
        command.header.type = MessageType::InputCommand;
        command.header.sequence = nextSequence_++;
        command.playerId = playerId_;
        command.tick = tick;
        command.moveX = 0;
        command.moveY = 0;
        command.jump = false;

        for (std::size_t index = 0; index < userInput.size(); ++index) {
            switch (userInput[index]) {
                case 'a':
                    command.moveX = -1;
                    break;
                case 'd':
                    command.moveX = 1;
                    break;
                case 'w':
                    command.moveY = -1;
                    break;
                case 's':
                    command.moveY = 1;
                    break;
                case ' ':
                    command.jump = true;
                    break;
                default:
                    break;
            }
        }

        return command;
    }

    void receiveSnapshot(const Snapshot& snapshot) {
        if (!history_.hasPrevious) {
            history_.previous = snapshot;
            history_.latest = snapshot;
            history_.hasPrevious = true;
            return;
        }

        history_.previous = history_.latest;
        history_.latest = snapshot;
    }

    void render(float alpha) const {
        if (!history_.hasPrevious) {
            std::cout << "No state replicated yet." << std::endl;
            return;
        }

        std::cout << "render score=" << history_.latest.score << std::endl;
        for (std::size_t index = 0; index < history_.latest.players.size(); ++index) {
            const PlayerState& latest = history_.latest.players[index];
            const PlayerState* previous = findPlayer(history_.previous, latest.playerId);
            PlayerState visual = interpolateOrExtrapolate(latest, previous, alpha);

            std::cout << "player=" << visual.playerId
                      << " x=" << visual.x
                      << " y=" << visual.y
                      << std::endl;
        }
    }

private:
    PlayerState interpolateOrExtrapolate(
        const PlayerState& latest,
        const PlayerState* previous,
        float alpha
    ) const {
        if (previous == NULL) {
            return latest;
        }

        PlayerState smooth = latest;
        float deltaX = latest.x - previous->x;
        float deltaY = latest.y - previous->y;

        if (alpha <= 1.0f) {
            smooth.x = previous->x + (deltaX * alpha);
            smooth.y = previous->y + (deltaY * alpha);
        } else {
            float extra = alpha - 1.0f;
            smooth.x = latest.x + (deltaX * extra);
            smooth.y = latest.y + (deltaY * extra);
        }

        return smooth;
    }

    const PlayerState* findPlayer(const Snapshot& snapshot, std::uint32_t playerId) const {
        for (std::size_t index = 0; index < snapshot.players.size(); ++index) {
            if (snapshot.players[index].playerId == playerId) {
                return &snapshot.players[index];
            }
        }

        return NULL;
    }

    std::uint32_t playerId_;
    std::uint32_t nextSequence_;
    SnapshotHistory history_;
};

Snapshot makeDemoSnapshot(std::uint32_t tick, float x, float y, std::uint32_t score) {
    Snapshot snapshot;
    snapshot.header.version = mario::net::protocol::kSnapshotVersion;
    snapshot.header.type = MessageType::Snapshot;
    snapshot.header.sequence = tick + 10;
    snapshot.tick = tick;
    snapshot.score = score;

    PlayerState player;
    player.playerId = 7;
    player.x = x;
    player.y = y;
    snapshot.players.push_back(player);

    return snapshot;
}

}  // namespace

int main() {
    GameClient client(7);

    std::vector<std::string> localInputs;
    localInputs.push_back("d");
    localInputs.push_back("ds");
    localInputs.push_back("d ");

    for (std::size_t tick = 0; tick < localInputs.size(); ++tick) {
        InputCommand command = client.captureLocalInput(static_cast<std::uint32_t>(tick), localInputs[tick]);
        std::cout << "send " << mario::net::protocol::serializeInputCommand(command) << std::endl;

        Snapshot snapshot = makeDemoSnapshot(
            static_cast<std::uint32_t>(tick),
            1.0f + static_cast<float>(tick),
            2.0f + static_cast<float>(tick),
            static_cast<std::uint32_t>(tick)
        );
        client.receiveSnapshot(snapshot);
        client.render(0.5f);
        client.render(1.25f);
    }

    return 0;
}
