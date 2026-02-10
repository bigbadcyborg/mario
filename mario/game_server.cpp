#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <vector>

#include "net/protocol/protocol.h"

namespace {

using mario::net::protocol::Ack;
using mario::net::protocol::InputCommand;
using mario::net::protocol::Join;
using mario::net::protocol::MessageHeader;
using mario::net::protocol::MessageType;
using mario::net::protocol::PlayerState;
using mario::net::protocol::Snapshot;
using mario::net::protocol::kAckVersion;
using mario::net::protocol::kInputCommandVersion;
using mario::net::protocol::kJoinVersion;
using mario::net::protocol::kSnapshotVersion;

struct ServerPlayer {
    std::uint32_t id;
    float x;
    float y;
};

struct GameState {
    std::map<std::uint32_t, ServerPlayer> players;
    std::uint32_t score;
    std::uint32_t tick;
    float coinX;
    float coinY;

    GameState() : score(0), tick(0), coinX(3.0f), coinY(3.0f) {}
};

class GameServer {
public:
    GameServer() : nextSequence_(1), previousSnapshot_(createSnapshot()) {}

    void processJoin(const Join& join) {
        ServerPlayer player = {join.playerId, 0.0f, 0.0f};
        state_.players[join.playerId] = player;
    }

    void processInputs(const std::vector<InputCommand>& inputs) {
        for (std::size_t index = 0; index < inputs.size(); ++index) {
            const InputCommand& input = inputs[index];
            std::map<std::uint32_t, ServerPlayer>::iterator playerIt = state_.players.find(input.playerId);
            if (playerIt == state_.players.end()) {
                continue;
            }

            ServerPlayer& player = playerIt->second;
            player.x += static_cast<float>(input.moveX);
            player.y += static_cast<float>(input.moveY);
            if (input.jump) {
                player.y -= 0.5f;
            }

            resolveWorldBounds(player);
            resolveCoinCollision(player);
        }
    }

    Snapshot tick() {
        ++state_.tick;
        Snapshot current = createSnapshot();
        broadcastSnapshotDelta(previousSnapshot_, current);
        previousSnapshot_ = current;
        return current;
    }

    Ack buildAck(std::uint32_t playerId, std::uint32_t ackedSequence) {
        Ack ack;
        ack.header = makeHeader(MessageType::Ack, kAckVersion);
        ack.playerId = playerId;
        ack.ackedSequence = ackedSequence;
        return ack;
    }

private:
    MessageHeader makeHeader(MessageType type, const mario::net::protocol::Version& version) {
        MessageHeader header;
        header.version = version;
        header.type = type;
        header.sequence = nextSequence_++;
        return header;
    }

    Snapshot createSnapshot() {
        Snapshot snapshot;
        snapshot.header = makeHeader(MessageType::Snapshot, kSnapshotVersion);
        snapshot.tick = state_.tick;
        snapshot.score = state_.score;

        for (std::map<std::uint32_t, ServerPlayer>::const_iterator it = state_.players.begin(); it != state_.players.end(); ++it) {
            PlayerState player;
            player.playerId = it->second.id;
            player.x = it->second.x;
            player.y = it->second.y;
            snapshot.players.push_back(player);
        }

        return snapshot;
    }

    void resolveWorldBounds(ServerPlayer& player) {
        player.x = std::max(0.0f, std::min(player.x, 10.0f));
        player.y = std::max(0.0f, std::min(player.y, 10.0f));
    }

    void resolveCoinCollision(ServerPlayer& player) {
        if (std::abs(player.x - state_.coinX) < 0.25f && std::abs(player.y - state_.coinY) < 0.25f) {
            ++state_.score;
            state_.coinX = (state_.coinX >= 8.0f) ? 2.0f : state_.coinX + 2.0f;
            state_.coinY = (state_.coinY >= 8.0f) ? 2.0f : state_.coinY + 1.0f;
        }
    }

    void broadcastSnapshotDelta(const Snapshot& previous, const Snapshot& current) {
        std::cout << "tick=" << current.tick << " score=" << current.score;

        for (std::size_t index = 0; index < current.players.size(); ++index) {
            const PlayerState& player = current.players[index];
            const PlayerState* oldPlayer = findPlayer(previous, player.playerId);
            if (oldPlayer == NULL || oldPlayer->x != player.x || oldPlayer->y != player.y) {
                std::cout << " | delta player=" << player.playerId << " x=" << player.x << " y=" << player.y;
            }
        }

        std::cout << std::endl;
    }

    const PlayerState* findPlayer(const Snapshot& snapshot, std::uint32_t playerId) const {
        for (std::size_t index = 0; index < snapshot.players.size(); ++index) {
            if (snapshot.players[index].playerId == playerId) {
                return &snapshot.players[index];
            }
        }

        return NULL;
    }

    GameState state_;
    std::uint32_t nextSequence_;
    Snapshot previousSnapshot_;
};

}  // namespace

int main() {
    GameServer server;

    Join join;
    join.header = {kJoinVersion, MessageType::Join, 1};
    join.playerId = 7;
    join.playerName = "player-seven";
    server.processJoin(join);

    for (std::uint32_t tick = 0; tick < 5; ++tick) {
        InputCommand input;
        input.header = {kInputCommandVersion, MessageType::InputCommand, tick + 2};
        input.playerId = 7;
        input.tick = tick;
        input.moveX = 1;
        input.moveY = (tick % 2 == 0) ? 1 : 0;
        input.jump = (tick == 3);

        std::vector<InputCommand> inputs;
        inputs.push_back(input);
        server.processInputs(inputs);

        Snapshot snapshot = server.tick();
        Ack ack = server.buildAck(join.playerId, snapshot.header.sequence);
        std::cout << mario::net::protocol::serializeAck(ack) << std::endl;
    }

    return 0;
}
