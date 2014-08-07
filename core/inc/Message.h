// TODO: Licensing

#pragma once

#include <memory>

#include "DhtCommon.h"

namespace Iso { namespace Dht {

    // The base-class that all network messages inherit from. It provides the basic
    // fields requires for ANY DHT message.
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
        const UniqueId& GetSourceUniqueId() const { return m_UniqueId; }

        virtual std::unique_ptr<uint8_t[]> Serialize() const = 0;
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
    };

    class FindValueMessage
        : public FindBaseMessage
    {
    public:
        FindValueMessage(UniqueId sourceNode, UniqueId lookupId, UniqueId randomId)
            : FindBaseMessage(sourceNode, lookupId, randomId)
        {}

        MessageType GetMessageType() const override { return MessageType::FindValue; }
    };

    class NodeReplyMessage
        : public Message
    {

    };

    class ValueReplyMessage
        : public Message
    {

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

} }