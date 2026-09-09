#pragma once
#ifndef H_HTML_DOC
#define H_HTML_DOC

#include <istream>

class HtmlDoc final {
   public:
    // ------------------------------------------------------------------------
    // Ctors
    // ------------------------------------------------------------------------
    HtmlDoc(void) noexcept = default;

    [[nodiscard]] static auto decode(std::istream& is) -> HtmlDoc;

    [[nodiscard]] static auto decode(std::string_view raw) -> HtmlDoc;

    // ------------------------------------------------------------------------
    // Copy
    // ------------------------------------------------------------------------
    HtmlDoc(const HtmlDoc&) noexcept                     = default;
    auto operator =(const HtmlDoc&) noexcept -> HtmlDoc& = default;

    // ------------------------------------------------------------------------
    // Move
    // ------------------------------------------------------------------------
    HtmlDoc(HtmlDoc&&) noexcept                     = default;
    auto operator =(HtmlDoc&&) noexcept -> HtmlDoc& = default;

    // ------------------------------------------------------------------------
    // Dtor
    // ------------------------------------------------------------------------
    ~HtmlDoc(void) noexcept = default;
};

#endif
