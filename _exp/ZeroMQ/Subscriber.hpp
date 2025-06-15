#pragma once

#include <_macros/Compiler.hpp>

#pragma warning (push)
#pragma warning (disable : FATLIB_EXTERNAL_WARNINGS)
#include <zmq.hpp>
#pragma warning (pop)

#pragma comment(lib, "iphlpapi")

#include <string>

namespace fatx
{
    namespace zeromq
    {
        class Subscriber final
        {
        public:
            Subscriber(const std::string& address)
                :
                m_context_(1),
                m_subscriber_(m_context_, zmq::socket_type::sub)
            {
                m_subscriber_.connect(address);
                m_subscriber_.set(zmq::sockopt::subscribe, "");
            }

            Subscriber(const Subscriber&)     = delete;
            Subscriber(Subscriber&&) noexcept = delete;

            auto operator = (const Subscriber&)     -> Subscriber& = delete;
            auto operator = (Subscriber&&) noexcept -> Subscriber& = delete;
            ~Subscriber() noexcept                                 = default;


        public:
            auto Receive() -> std::string
            {
                zmq::message_t message;

                static_cast<void>(m_subscriber_.recv(message, zmq::recv_flags::none));

                return message.to_string();
            }

            void SetReceiveTimeout(const int milliseconds)
            {
                m_subscriber_.set(zmq::sockopt::rcvtimeo, milliseconds);
            }


        protected:


        private:
            zmq::context_t m_context_;
            zmq::socket_t  m_subscriber_;
        };
    }
}