#include <Win32_/IWindow.hpp>

#include <Win32_/Common.hpp>

#include <stdexcept>

namespace fatpound::win32
{
    IWindow::ClassEx::ClassEx(const WNDCLASSEX& wcx)
        :
        m_hInstance_(wcx.hInstance),
        m_atom_(::RegisterClassEx(&wcx))
    {
        if (m_atom_ == 0)
        {
            throw std::runtime_error{ "ATOM could not be created!\n" "Consider checking WNDCLASSEX::lpszClassName" };
        }
    }
    IWindow::ClassEx::ClassEx(const std::wstring& wstr)
        :
        ClassEx(wstr.c_str())
    {

    }
    IWindow::ClassEx::ClassEx(const wchar_t* const clsName)
        :
        ClassEx(CreateDefaultWNDCLASSEX_<>(ModuleHandleOf(nullptr), clsName))
    {

    }
    IWindow::ClassEx::~ClassEx() noexcept
    {
        [[maybe_unused]]
        const auto&& retval = ::UnregisterClass(MAKEINTATOM(m_atom_), m_hInstance_);
    }


    auto IWindow::ClassEx::GetAtom() const noexcept -> ATOM
    {
        return m_atom_;
    }
    auto IWindow::ClassEx::GetInstance() const noexcept -> HINSTANCE
    {
        return m_hInstance_;
    }

    auto IWindow::ClassEx::ForwardMsg_(IWindow* const pWnd, const HWND hWnd, const UINT msg, const WPARAM wParam, const LPARAM lParam) -> LRESULT
    {
        return pWnd->HandleMsg_(hWnd, msg, wParam, lParam);
    }
}
