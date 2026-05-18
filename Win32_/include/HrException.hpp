#pragma once

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <Win32_/include/FatWin.hpp>

#include <stdexcept>
#include <string>
#include <source_location>

namespace fatpound::win32
{
    class HrException : public std::runtime_error
    {
    public:
        HrException(const HRESULT& hr, const std::string& note, const std::source_location& loc = std::source_location::current());


    public:
        [[nodiscard]]
        virtual auto what() const noexcept -> const char* override;


    public:
        [[nodiscard]]
        auto GetErrorCode() const noexcept -> HRESULT;


    protected:
        std::string   m_message_;
        HRESULT       m_hr_;

        
    private:
    };
}

#endif
