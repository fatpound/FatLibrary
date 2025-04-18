#pragma once

#include <zmq.hpp>

#pragma comment(lib, "iphlpapi")

#include <string>

namespace fatx::zeromq
{
    class Subscriber final
    {
    public:
        Subscriber(const std::string& address = "tcp://localhost:5555")
            :
            m_context_(1),
            m_subscriber_(m_context_, ::zmq::socket_type::sub)
        {
            m_subscriber_.connect(address);
            m_subscriber_.set(::zmq::sockopt::subscribe, "");
        }

        Subscriber(const Subscriber&)     = delete;
        Subscriber(Subscriber&&) noexcept = delete;

        auto operator = (const Subscriber&)     -> Subscriber& = delete;
        auto operator = (Subscriber&&) noexcept -> Subscriber& = delete;
        ~Subscriber() noexcept                                 = default;


    public:
        auto Receive() -> std::string
        {
            ::zmq::message_t message;

            {
                [[maybe_unused]]
                const auto& retval = m_subscriber_.recv(message, ::zmq::recv_flags::none);
            }

            return message.to_string();
        }


    protected:


    private:
        ::zmq::context_t m_context_;
        ::zmq::socket_t  m_subscriber_;
    };
}
