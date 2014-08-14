#pragma once

#include <memory>
#include <vector>

#include <Dht\UniqueId.h>

namespace IsoPeer { namespace Substrate { namespace Dht {

    // Tempoary until we figure out what the low-level networking library is going
    // to look like.
    struct NetworkAddress {
        uint8_t IpAddress[4];
        uint16_t Port;
    };

    // A base class representing all possible DHT messages. It provides the basic
    // contract used by the system for serialization and deserialization. 
    class Message
    {
    public:
        enum class MessageType : uint8_t
        {
            PingRequest,
            PingReply,
            PingRepReq,
            FindNode,
            FindValue,
            ReplyNode,
            ReplyValue,
            StoreValue,
        };

        virtual MessageType GetMessageType() const = 0;
        const UniqueId& GetSourceId() const { return m_UniqueId; }
        virtual std::string ToString() const = 0;

        virtual std::vector<uint8_t> Serialize() const = 0;
        static std::unique_ptr<Message> Deserialize(uint8_t buffer[]);

        virtual ~Message() {}

    protected:
        Message(UniqueId sourceNode);

    private:
        UniqueId m_UniqueId;
    };

    class PingRequestMessage
        : public Message
    {
    public:
        PingRequestMessage(UniqueId sourceNode, UniqueId randomId)
            : m_randomId(randomId)
            , Message(sourceNode)
        {}

        MessageType GetMessageType() const override { return MessageType::PingRequest; }
        const UniqueId& GetRequestId() const { return m_randomId; }
        std::string ToString() const override;
        std::vector<uint8_t> Serialize() const override;

    private:
        UniqueId m_randomId;
    };

    class PingReplyMessage
        : public Message
    {
    public:
        PingReplyMessage(UniqueId sourceNode, UniqueId randomId)
            : m_randomId(randomId)
            , Message(sourceNode)
        {}

        MessageType GetMessageType() const override { return MessageType::PingReply; }
        const UniqueId& GetReplyId() const { return m_randomId; }
        std::string ToString() const override;
        std::vector<uint8_t> Serialize() const override;

    private:
        UniqueId m_randomId;
    };

    class PingRepReqMessage
        : public Message
    {
    public:
        PingRepReqMessage(UniqueId sourceNode, UniqueId requestId, UniqueId replyId)
            : m_requestId(requestId)
            , m_replyId(replyId)
            , Message(sourceNode)
        {}

        MessageType GetMessageType() const override { return MessageType::PingRepReq; }
        const UniqueId& GetRequestId() const { return m_requestId; }
        const UniqueId& GetReplyId() const { return m_replyId; }
        std::string ToString() const override;
        std::vector<uint8_t> Serialize() const override;

    private:
        UniqueId m_requestId;
        UniqueId m_replyId;
    };

    class FindBaseMessage
        : public Message
    {
    public:
        const UniqueId& GetRandomId() const { return m_randomId; }
        const UniqueId& GetLookupId() const { return m_lookupId; }
        std::vector<uint8_t> Serialize() const override;

    protected:
        FindBaseMessage(UniqueId sourceNode, UniqueId lookupId, UniqueId randomId)
            : m_lookupId(lookupId)
            , m_randomId(randomId)
            , Message(sourceNode)
        {}

    private:
        UniqueId m_lookupId;
        UniqueId m_randomId;
    };

    class FindNodeMessage
        : public FindBaseMessage
    {
    public:
        FindNodeMessage(UniqueId sourceNode, UniqueId lookupId, UniqueId randomId)
            : FindBaseMessage(sourceNode, lookupId, randomId)
        {}

        MessageType GetMessageType() const override { return MessageType::FindNode; }
        std::string ToString() const override;
    };

    class FindValueMessage
        : public FindBaseMessage
    {
    public:
        FindValueMessage(UniqueId sourceNode, UniqueId lookupId, UniqueId randomId)
            : FindBaseMessage(sourceNode, lookupId, randomId)
        {}

        MessageType GetMessageType() const override { return MessageType::FindValue; }
        std::string ToString() const override;
    };

    class NodeReplyMessage
        : public Message
    {
    public:
        NodeReplyMessage(UniqueId sourceNode, UniqueId requestId, std::vector<NetworkAddress> contactInfo, UniqueId replyId)
            : m_requestId(requestId)
            , m_contactInfo(std::move(contactInfo))
            , m_replyId(replyId)
            , Message(sourceNode)
        {}

        MessageType GetMessageType() const override { return MessageType::ReplyNode; }
        const UniqueId& GetRequestId() const { return m_requestId; }
        const UniqueId& GetReplyId() const { return m_replyId; }
        const std::vector<NetworkAddress>& GetContactInfo() const { return m_contactInfo; }
        std::string ToString() const override;
        std::vector<uint8_t> Serialize() const override;

    private:
        UniqueId m_requestId;
        std::vector<NetworkAddress> m_contactInfo;
        UniqueId m_replyId;
    };

    class ValueReplyMessage
        : public Message
    {
        ValueReplyMessage(UniqueId sourceNode, UniqueId requestId, std::vector<uint8_t> payload, UniqueId replyId)
            : m_requestId(requestId)
            , m_payload(std::move(payload))
            , m_replyId(replyId)
            , Message(sourceNode)
        {}

        MessageType GetMessageType() const override { return MessageType::ReplyNode; }
        const UniqueId& GetRequestId() const { return m_requestId; }
        const UniqueId& GetReplyId() const { return m_replyId; }
        const std::vector<uint8_t>& GetPayload() const { return m_payload; }
        std::string ToString() const override;
        std::vector<uint8_t> Serialize() const override;

    private:
        UniqueId m_requestId;
        std::vector<uint8_t> m_payload;
        UniqueId m_replyId;
    };

    class StoreValueMessage
        : public Message
    {
    public:
        StoreValueMessage(UniqueId sourceNode, std::vector<uint8_t> payload, UniqueId randomId)
            : m_payload(std::move(payload))
            , m_randomId(randomId)
            , Message(sourceNode)
        {}

        const UniqueId& GetRandomId() const { return m_randomId; }
        const std::vector<uint8_t>& GetPayload() const { return m_payload; }

    private:
        std::vector<uint8_t> m_payload;
        UniqueId m_randomId;
    };

} } }