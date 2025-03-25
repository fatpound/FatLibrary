#pragma once

#include <zmq.hpp>

#pragma comment(lib, "iphlpapi")

#include <string>

namespace fatx::zeromq
{
    class Subscriber final
    {
    public:
        Subscriber(const std::string& address = "tcp://localhost:5555");

        Subscriber(const Subscriber&)     = delete;
        Subscriber(Subscriber&&) noexcept = delete;

        auto operator = (const Subscriber&)     -> Subscriber& = delete;
        auto operator = (Subscriber&&) noexcept -> Subscriber& = delete;
        ~Subscriber() noexcept                                 = default;


    public:
        auto Receive() -> std::string;


    protected:


    private:
        ::zmq::context_t m_context_;
        ::zmq::socket_t  m_subscriber_;
    };
}
