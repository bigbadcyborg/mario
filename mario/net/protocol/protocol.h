#ifndef MARIO_NET_PROTOCOL_PROTOCOL_H
#define MARIO_NET_PROTOCOL_PROTOCOL_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace mario {
namespace net {
namespace protocol {

struct Version {
    std::uint16_t major;
    std::uint16_t minor;

    bool isCompatibleWith(const Version& other) const;
    std::string toString() const;
    static bool tryParse(const std::string& text, Version& outVersion);
};

enum class MessageType {
    Join,
    InputCommand,
    Snapshot,
    Ack
};

struct MessageHeader {
    Version version;
    MessageType type;
    std::uint32_t sequence;
};

struct Join {
    MessageHeader header;
    std::uint32_t playerId;
    std::string playerName;
};

struct InputCommand {
    MessageHeader header;
    std::uint32_t playerId;
    std::uint32_t tick;
    int moveX;
    int moveY;
    bool jump;
};

struct PlayerState {
    std::uint32_t playerId;
    float x;
    float y;
};

struct Snapshot {
    MessageHeader header;
    std::uint32_t tick;
    std::vector<PlayerState> players;
    std::uint32_t score;
};

struct Ack {
    MessageHeader header;
    std::uint32_t playerId;
    std::uint32_t ackedSequence;
};

extern const Version kJoinVersion;
extern const Version kInputCommandVersion;
extern const Version kSnapshotVersion;
extern const Version kAckVersion;

std::string serializeJoin(const Join& message);
bool tryDeserializeJoin(const std::string& payload, Join& outMessage);

std::string serializeInputCommand(const InputCommand& message);
bool tryDeserializeInputCommand(const std::string& payload, InputCommand& outMessage);

std::string serializeSnapshot(const Snapshot& message);
bool tryDeserializeSnapshot(const std::string& payload, Snapshot& outMessage);

std::string serializeAck(const Ack& message);
bool tryDeserializeAck(const std::string& payload, Ack& outMessage);

}  // namespace protocol
}  // namespace net
}  // namespace mario

#endif
