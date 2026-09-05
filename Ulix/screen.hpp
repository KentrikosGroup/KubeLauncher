#pragma once

#include <winfunc.hpp>
#include <rect.hpp>
#include <types.hpp>

namespace ulx {
    class screen {
        public:
            inline static auto get_rect() -> ulx::rect {
                return ulx::rect(0, 0,
                    ulx::wfun::logical_cast(GetSystemMetricsForDpi(SM_CXSCREEN, ulx::wfun::system_dpi)),
                    ulx::wfun::logical_cast(GetSystemMetricsForDpi(SM_CYSCREEN, ulx::wfun::system_dpi)));
            }
            
            inline static auto get_dpi() -> ulx::u32 {
                return ulx::wfun::system_dpi;
            }
    };
}
