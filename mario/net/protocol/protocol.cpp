#include "protocol.h"

#include <cstdlib>
#include <sstream>

namespace mario {
namespace net {
namespace protocol {

const Version kJoinVersion = {1, 0};
const Version kInputCommandVersion = {1, 0};
const Version kSnapshotVersion = {1, 0};
const Version kAckVersion = {1, 0};

namespace {

std::string messageTypeToString(MessageType type) {
    switch (type) {
        case MessageType::Join:
            return "Join";
        case MessageType::InputCommand:
            return "InputCommand";
        case MessageType::Snapshot:
            return "Snapshot";
        case MessageType::Ack:
            return "Ack";
    }
    return "Unknown";
}

bool tryParseMessageType(const std::string& text, MessageType& outType) {
    if (text == "Join") {
        outType = MessageType::Join;
        return true;
    }
    if (text == "InputCommand") {
        outType = MessageType::InputCommand;
        return true;
    }
    if (text == "Snapshot") {
        outType = MessageType::Snapshot;
        return true;
    }
    if (text == "Ack") {
        outType = MessageType::Ack;
        return true;
    }
    return false;
}

std::map<std::string, std::string> parseFields(const std::string& payload) {
    std::map<std::string, std::string> fields;
    std::stringstream stream(payload);
    std::string item;

    while (std::getline(stream, item, ';')) {
        if (item.empty()) {
            continue;
        }

        std::size_t separator = item.find('=');
        if (separator == std::string::npos) {
            continue;
        }

        fields[item.substr(0, separator)] = item.substr(separator + 1);
    }

    return fields;
}

std::string serializeHeader(const MessageHeader& header) {
    std::stringstream stream;
    stream << "type=" << messageTypeToString(header.type) << ';';
    stream << "version=" << header.version.toString() << ';';
    stream << "sequence=" << header.sequence << ';';
    return stream.str();
}

bool tryDeserializeHeader(
    const std::map<std::string, std::string>& fields,
    const Version& expectedVersion,
    MessageType expectedType,
    MessageHeader& outHeader
) {
    std::map<std::string, std::string>::const_iterator typeIt = fields.find("type");
    std::map<std::string, std::string>::const_iterator versionIt = fields.find("version");
    std::map<std::string, std::string>::const_iterator sequenceIt = fields.find("sequence");

    if (typeIt == fields.end() || versionIt == fields.end() || sequenceIt == fields.end()) {
        return false;
    }

    MessageType actualType;
    if (!tryParseMessageType(typeIt->second, actualType) || actualType != expectedType) {
        return false;
    }

    Version parsedVersion;
    if (!Version::tryParse(versionIt->second, parsedVersion)) {
        return false;
    }

    if (!parsedVersion.isCompatibleWith(expectedVersion)) {
        return false;
    }

    outHeader.version = parsedVersion;
    outHeader.type = actualType;
    outHeader.sequence = static_cast<std::uint32_t>(std::strtoul(sequenceIt->second.c_str(), NULL, 10));

    return true;
}

}  // namespace

bool Version::isCompatibleWith(const Version& other) const {
    return major == other.major;
}

std::string Version::toString() const {
    std::stringstream stream;
    stream << major << '.' << minor;
    return stream.str();
}

bool Version::tryParse(const std::string& text, Version& outVersion) {
    std::size_t dot = text.find('.');
    if (dot == std::string::npos) {
        return false;
    }

    outVersion.major = static_cast<std::uint16_t>(std::strtoul(text.substr(0, dot).c_str(), NULL, 10));
    outVersion.minor = static_cast<std::uint16_t>(std::strtoul(text.substr(dot + 1).c_str(), NULL, 10));
    return true;
}

std::string serializeJoin(const Join& message) {
    std::stringstream stream;
    stream << serializeHeader(message.header);
    stream << "playerId=" << message.playerId << ';';
    stream << "playerName=" << message.playerName << ';';
    return stream.str();
}

bool tryDeserializeJoin(const std::string& payload, Join& outMessage) {
    std::map<std::string, std::string> fields = parseFields(payload);
    if (!tryDeserializeHeader(fields, kJoinVersion, MessageType::Join, outMessage.header)) {
        return false;
    }

    outMessage.playerId = static_cast<std::uint32_t>(std::strtoul(fields["playerId"].c_str(), NULL, 10));
    outMessage.playerName = fields["playerName"];
    return true;
}

std::string serializeInputCommand(const InputCommand& message) {
    std::stringstream stream;
    stream << serializeHeader(message.header);
    stream << "playerId=" << message.playerId << ';';
    stream << "tick=" << message.tick << ';';
    stream << "moveX=" << message.moveX << ';';
    stream << "moveY=" << message.moveY << ';';
    stream << "jump=" << static_cast<int>(message.jump) << ';';
    return stream.str();
}

bool tryDeserializeInputCommand(const std::string& payload, InputCommand& outMessage) {
    std::map<std::string, std::string> fields = parseFields(payload);
    if (!tryDeserializeHeader(fields, kInputCommandVersion, MessageType::InputCommand, outMessage.header)) {
        return false;
    }

    outMessage.playerId = static_cast<std::uint32_t>(std::strtoul(fields["playerId"].c_str(), NULL, 10));
    outMessage.tick = static_cast<std::uint32_t>(std::strtoul(fields["tick"].c_str(), NULL, 10));
    outMessage.moveX = std::atoi(fields["moveX"].c_str());
    outMessage.moveY = std::atoi(fields["moveY"].c_str());
    outMessage.jump = std::atoi(fields["jump"].c_str()) != 0;
    return true;
}

std::string serializeSnapshot(const Snapshot& message) {
    std::stringstream stream;
    stream << serializeHeader(message.header);
    stream << "tick=" << message.tick << ';';
    stream << "score=" << message.score << ';';
    stream << "playerCount=" << message.players.size() << ';';

    for (std::size_t index = 0; index < message.players.size(); ++index) {
        const PlayerState& player = message.players[index];
        stream << "player" << index << "="
               << player.playerId << ',' << player.x << ',' << player.y << ';';
    }

    return stream.str();
}

bool tryDeserializeSnapshot(const std::string& payload, Snapshot& outMessage) {
    std::map<std::string, std::string> fields = parseFields(payload);
    if (!tryDeserializeHeader(fields, kSnapshotVersion, MessageType::Snapshot, outMessage.header)) {
        return false;
    }

    outMessage.tick = static_cast<std::uint32_t>(std::strtoul(fields["tick"].c_str(), NULL, 10));
    outMessage.score = static_cast<std::uint32_t>(std::strtoul(fields["score"].c_str(), NULL, 10));

    std::size_t playerCount = static_cast<std::size_t>(std::strtoul(fields["playerCount"].c_str(), NULL, 10));
    outMessage.players.clear();

    for (std::size_t index = 0; index < playerCount; ++index) {
        std::stringstream key;
        key << "player" << index;
        std::map<std::string, std::string>::iterator playerFieldIt = fields.find(key.str());
        if (playerFieldIt == fields.end()) {
            return false;
        }

        std::stringstream valueStream(playerFieldIt->second);
        std::string component;
        PlayerState playerState = {0, 0.0f, 0.0f};

        if (!std::getline(valueStream, component, ',')) {
            return false;
        }
        playerState.playerId = static_cast<std::uint32_t>(std::strtoul(component.c_str(), NULL, 10));

        if (!std::getline(valueStream, component, ',')) {
            return false;
        }
        playerState.x = static_cast<float>(std::atof(component.c_str()));

        if (!std::getline(valueStream, component, ',')) {
            return false;
        }
        playerState.y = static_cast<float>(std::atof(component.c_str()));

        outMessage.players.push_back(playerState);
    }

    return true;
}

std::string serializeAck(const Ack& message) {
    std::stringstream stream;
    stream << serializeHeader(message.header);
    stream << "playerId=" << message.playerId << ';';
    stream << "ackedSequence=" << message.ackedSequence << ';';
    return stream.str();
}

bool tryDeserializeAck(const std::string& payload, Ack& outMessage) {
    std::map<std::string, std::string> fields = parseFields(payload);
    if (!tryDeserializeHeader(fields, kAckVersion, MessageType::Ack, outMessage.header)) {
        return false;
    }

    outMessage.playerId = static_cast<std::uint32_t>(std::strtoul(fields["playerId"].c_str(), NULL, 10));
    outMessage.ackedSequence = static_cast<std::uint32_t>(std::strtoul(fields["ackedSequence"].c_str(), NULL, 10));
    return true;
}

}  // namespace protocol
}  // namespace net
}  // namespace mario
