#pragma once

#if defined(_MSC_VER)

#include <FatWin32.hpp>

// some secret messages
#define WM_UAHDESTROYWINDOW 0x0090
#define WM_UAHDRAWMENU 0x0091
#define WM_UAHDRAWMENUITEM 0x0092
#define WM_UAHINITMENU 0x0093
#define WM_UAHMEASUREMENUITEM 0x0094
#define WM_UAHNCPAINTMENUPOPUP 0x0095

#define WIDEN(x) WIDEN2(x)
#define WIDEN2(x) (L ## x)

#define REGISTER_MESSAGE(msg) { static_cast<DWORD>(msg), WIDEN(#msg) }

#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>

namespace fatpound::win32
{
    class MessageMap final
    {
    public:
        explicit MessageMap()
            :
            m_map_({
                REGISTER_MESSAGE(WM_ACTIVATE),
                REGISTER_MESSAGE(WM_ACTIVATEAPP),
                REGISTER_MESSAGE(WM_ASKCBFORMATNAME),
                REGISTER_MESSAGE(WM_CANCELMODE),
                REGISTER_MESSAGE(WM_CAPTURECHANGED),
                REGISTER_MESSAGE(WM_CHANGECBCHAIN),
                REGISTER_MESSAGE(WM_CHAR),
                REGISTER_MESSAGE(WM_CHARTOITEM),
                REGISTER_MESSAGE(WM_CHILDACTIVATE),
                REGISTER_MESSAGE(WM_CLEAR),
                REGISTER_MESSAGE(WM_CLOSE),
                REGISTER_MESSAGE(WM_COMMAND),
                REGISTER_MESSAGE(WM_COMPACTING),
                REGISTER_MESSAGE(WM_COMPAREITEM),
                REGISTER_MESSAGE(WM_CONTEXTMENU),
                REGISTER_MESSAGE(WM_COPY),
                REGISTER_MESSAGE(WM_COPYDATA),
                REGISTER_MESSAGE(WM_CREATE),
                REGISTER_MESSAGE(WM_CTLCOLORBTN),
                REGISTER_MESSAGE(WM_CTLCOLORDLG),
                REGISTER_MESSAGE(WM_CTLCOLOREDIT),
                REGISTER_MESSAGE(WM_CTLCOLORLISTBOX),
                REGISTER_MESSAGE(WM_CTLCOLORMSGBOX),
                REGISTER_MESSAGE(WM_CTLCOLORSCROLLBAR),
                REGISTER_MESSAGE(WM_CTLCOLORSTATIC),
                REGISTER_MESSAGE(WM_CUT),
                REGISTER_MESSAGE(WM_DEADCHAR),
                REGISTER_MESSAGE(WM_DELETEITEM),
                REGISTER_MESSAGE(WM_DESTROY),
                REGISTER_MESSAGE(WM_DESTROYCLIPBOARD),
                REGISTER_MESSAGE(WM_DEVICECHANGE),
                REGISTER_MESSAGE(WM_DEVMODECHANGE),
                REGISTER_MESSAGE(WM_DISPLAYCHANGE),
                REGISTER_MESSAGE(WM_DRAWCLIPBOARD),
                REGISTER_MESSAGE(WM_DRAWITEM),
                REGISTER_MESSAGE(WM_DROPFILES),
                REGISTER_MESSAGE(WM_DWMNCRENDERINGCHANGED),
                REGISTER_MESSAGE(WM_ENABLE),
                REGISTER_MESSAGE(WM_ENDSESSION),
                REGISTER_MESSAGE(WM_ENTERIDLE),
                REGISTER_MESSAGE(WM_ENTERMENULOOP),
                REGISTER_MESSAGE(WM_ENTERSIZEMOVE),
                REGISTER_MESSAGE(WM_ERASEBKGND),
                REGISTER_MESSAGE(WM_EXITMENULOOP),
                REGISTER_MESSAGE(WM_EXITSIZEMOVE),
                REGISTER_MESSAGE(WM_FONTCHANGE),
                REGISTER_MESSAGE(WM_GETDLGCODE),
                REGISTER_MESSAGE(WM_GETFONT),
                REGISTER_MESSAGE(WM_GETICON),
                REGISTER_MESSAGE(WM_GETICON),
                REGISTER_MESSAGE(WM_GETMINMAXINFO),
                REGISTER_MESSAGE(WM_GETTEXT),
                REGISTER_MESSAGE(WM_GETTEXTLENGTH),
                REGISTER_MESSAGE(WM_HELP),
                REGISTER_MESSAGE(WM_HOTKEY),
                REGISTER_MESSAGE(WM_HSCROLL),
                REGISTER_MESSAGE(WM_HSCROLLCLIPBOARD),
                REGISTER_MESSAGE(WM_ICONERASEBKGND),
                REGISTER_MESSAGE(WM_IME_NOTIFY),
                REGISTER_MESSAGE(WM_IME_SETCONTEXT),
                REGISTER_MESSAGE(WM_INITDIALOG),
                REGISTER_MESSAGE(WM_INITMENU),
                REGISTER_MESSAGE(WM_INITMENUPOPUP),
                REGISTER_MESSAGE(WM_KEYDOWN),
                REGISTER_MESSAGE(WM_KEYLAST),
                REGISTER_MESSAGE(WM_KEYUP),
                REGISTER_MESSAGE(WM_KILLFOCUS),
                REGISTER_MESSAGE(WM_LBUTTONDBLCLK),
                REGISTER_MESSAGE(WM_LBUTTONDOWN),
                REGISTER_MESSAGE(WM_LBUTTONUP),
                REGISTER_MESSAGE(WM_MBUTTONDBLCLK),
                REGISTER_MESSAGE(WM_MBUTTONDOWN),
                REGISTER_MESSAGE(WM_MBUTTONUP),
                REGISTER_MESSAGE(WM_MDIACTIVATE),
                REGISTER_MESSAGE(WM_MDICASCADE),
                REGISTER_MESSAGE(WM_MDICREATE),
                REGISTER_MESSAGE(WM_MDIDESTROY),
                REGISTER_MESSAGE(WM_MDIGETACTIVE),
                REGISTER_MESSAGE(WM_MDIICONARRANGE),
                REGISTER_MESSAGE(WM_MDIMAXIMIZE),
                REGISTER_MESSAGE(WM_MDINEXT),
                REGISTER_MESSAGE(WM_MDIREFRESHMENU),
                REGISTER_MESSAGE(WM_MDIRESTORE),
                REGISTER_MESSAGE(WM_MDISETMENU),
                REGISTER_MESSAGE(WM_MDITILE),
                REGISTER_MESSAGE(WM_MEASUREITEM),
                REGISTER_MESSAGE(WM_MENUCHAR),
                REGISTER_MESSAGE(WM_MENUSELECT),
                REGISTER_MESSAGE(WM_MOUSEACTIVATE),
                REGISTER_MESSAGE(WM_MOUSEMOVE),
                REGISTER_MESSAGE(WM_MOUSEWHEEL),
                REGISTER_MESSAGE(WM_MOVE),
                REGISTER_MESSAGE(WM_MOVING),
                REGISTER_MESSAGE(WM_MOVING),
                REGISTER_MESSAGE(WM_NCACTIVATE),
                REGISTER_MESSAGE(WM_NCCALCSIZE),
                REGISTER_MESSAGE(WM_NCCREATE),
                REGISTER_MESSAGE(WM_NCDESTROY),
                REGISTER_MESSAGE(WM_NCHITTEST),
                REGISTER_MESSAGE(WM_NCLBUTTONDBLCLK),
                REGISTER_MESSAGE(WM_NCLBUTTONDOWN),
                REGISTER_MESSAGE(WM_NCLBUTTONUP),
                REGISTER_MESSAGE(WM_NCMBUTTONDBLCLK),
                REGISTER_MESSAGE(WM_NCMBUTTONDOWN),
                REGISTER_MESSAGE(WM_NCMBUTTONUP),
                REGISTER_MESSAGE(WM_NCMOUSELEAVE),
                REGISTER_MESSAGE(WM_NCMOUSEMOVE),
                REGISTER_MESSAGE(WM_NCPAINT),
                REGISTER_MESSAGE(WM_NCRBUTTONDBLCLK),
                REGISTER_MESSAGE(WM_NCRBUTTONDOWN),
                REGISTER_MESSAGE(WM_NCRBUTTONUP),
                REGISTER_MESSAGE(WM_NEXTDLGCTL),
                REGISTER_MESSAGE(WM_NOTIFY),
                REGISTER_MESSAGE(WM_PAINT),
                REGISTER_MESSAGE(WM_PAINTCLIPBOARD),
                REGISTER_MESSAGE(WM_PALETTECHANGED),
                REGISTER_MESSAGE(WM_PALETTEISCHANGING),
                REGISTER_MESSAGE(WM_PARENTNOTIFY),
                REGISTER_MESSAGE(WM_PASTE),
                REGISTER_MESSAGE(WM_POWER),
                REGISTER_MESSAGE(WM_POWERBROADCAST),
                REGISTER_MESSAGE(WM_PRINT),
                REGISTER_MESSAGE(WM_PRINT),
                REGISTER_MESSAGE(WM_PRINTCLIENT),
                REGISTER_MESSAGE(WM_PRINTCLIENT),
                REGISTER_MESSAGE(WM_QUERYDRAGICON),
                REGISTER_MESSAGE(WM_QUERYENDSESSION),
                REGISTER_MESSAGE(WM_QUERYNEWPALETTE),
                REGISTER_MESSAGE(WM_QUERYOPEN),
                REGISTER_MESSAGE(WM_QUEUESYNC),
                REGISTER_MESSAGE(WM_QUIT),
                REGISTER_MESSAGE(WM_RBUTTONDBLCLK),
                REGISTER_MESSAGE(WM_RBUTTONDOWN),
                REGISTER_MESSAGE(WM_RBUTTONUP),
                REGISTER_MESSAGE(WM_RENDERALLFORMATS),
                REGISTER_MESSAGE(WM_RENDERFORMAT),
                REGISTER_MESSAGE(WM_SETCURSOR),
                REGISTER_MESSAGE(WM_SETFOCUS),
                REGISTER_MESSAGE(WM_SETFONT),
                REGISTER_MESSAGE(WM_SETHOTKEY),
                REGISTER_MESSAGE(WM_SETICON),
                REGISTER_MESSAGE(WM_SETREDRAW),
                REGISTER_MESSAGE(WM_SETTEXT),
                REGISTER_MESSAGE(WM_SETTINGCHANGE),
                REGISTER_MESSAGE(WM_SHOWWINDOW),
                REGISTER_MESSAGE(WM_SIZE),
                REGISTER_MESSAGE(WM_SIZECLIPBOARD),
                REGISTER_MESSAGE(WM_SIZING),
                REGISTER_MESSAGE(WM_SIZING),
                REGISTER_MESSAGE(WM_SPOOLERSTATUS),
                REGISTER_MESSAGE(WM_STYLECHANGED),
                REGISTER_MESSAGE(WM_STYLECHANGED),
                REGISTER_MESSAGE(WM_STYLECHANGING),
                REGISTER_MESSAGE(WM_STYLECHANGING),
                REGISTER_MESSAGE(WM_SYSCHAR),
                REGISTER_MESSAGE(WM_SYSCOLORCHANGE),
                REGISTER_MESSAGE(WM_SYSCOMMAND),
                REGISTER_MESSAGE(WM_SYSDEADCHAR),
                REGISTER_MESSAGE(WM_SYSKEYDOWN),
                REGISTER_MESSAGE(WM_SYSKEYUP),
                REGISTER_MESSAGE(WM_TCARD),
                REGISTER_MESSAGE(WM_TIMECHANGE),
                REGISTER_MESSAGE(WM_TIMER),
                REGISTER_MESSAGE(WM_UAHDESTROYWINDOW),
                REGISTER_MESSAGE(WM_UNDO),
                REGISTER_MESSAGE(WM_VKEYTOITEM),
                REGISTER_MESSAGE(WM_VSCROLL),
                REGISTER_MESSAGE(WM_VSCROLLCLIPBOARD),
                REGISTER_MESSAGE(WM_WINDOWPOSCHANGED),
                REGISTER_MESSAGE(WM_WINDOWPOSCHANGING),
                REGISTER_MESSAGE(WM_WININICHANGE)
                })
        {

        }
        explicit MessageMap(const MessageMap&)     = delete;
        explicit MessageMap(MessageMap&&) noexcept = delete;

        auto operator = (const MessageMap&)     -> MessageMap& = delete;
        auto operator = (MessageMap&&) noexcept -> MessageMap& = delete;
        ~MessageMap() noexcept                                 = default;


    public:
        auto operator () (const DWORD msg, const WPARAM wp, const LPARAM lp) const -> std::wstring
        {
            constexpr int firstColWidth = 25;
            const auto i = m_map_.find(msg);

            std::wostringstream woss;

            if (i not_eq m_map_.end())
            {
                woss << std::left << std::setw(firstColWidth) << i->second << std::right;
            }
            else
            {
                std::wostringstream wpadss;

                wpadss << L"Unknown message: 0x" << std::hex << msg;
                woss << std::left << std::setw(firstColWidth) << wpadss.str() << std::right;
            }

            woss << L"   WP: 0x" << std::hex << std::setfill(L'0') << std::setw(8) << wp;
            woss << L"   LP: 0x" << std::hex << std::setfill(L'0') << std::setw(8) << lp << std::endl;

            return woss.str();
        }


    protected:


    private:
        std::unordered_map<DWORD, std::wstring> m_map_;
    };
}

#endif
