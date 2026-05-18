#include "HrException.hpp"

#ifdef FATLIB_BUILDING_WITH_MSVC

#include <format>
#include <system_error>

namespace fatpound::win32
{
    HrException::HrException(const HRESULT& hr, const std::string& note, const std::source_location& loc)
        :
        std::runtime_error("WinAPI Exception!"),
        m_hr_(hr)
    {
        m_message_ = std::format<>(
            "WinAPI Exception!\n"
            "Error Code: {:#010x}\n"
            "Description: {}\n"
            "Note: {}\n"
            "File: {}\n"
            "Line: {}\n"
            "Function: {}",
            static_cast<unsigned int>(m_hr_),
            std::system_category().message(hr),
            note,
            loc.file_name(),
            loc.line(),
            loc.function_name()
        );
    }


    [[nodiscard]]
    auto HrException::what() const noexcept -> const char*
    {
        return m_message_.c_str();
    }

    [[nodiscard]]
    auto HrException::GetErrorCode() const noexcept -> HRESULT
    {
        return m_hr_;
    }
}

#endif
