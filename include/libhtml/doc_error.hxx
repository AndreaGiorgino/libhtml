#pragma once
#ifndef H_DOCUMENT_ERROR
#define H_DOCUMENT_ERROR

#include <format>

/**
 * @class DocError
 * @brief Represents a parsing error
 *
 */
class DocError final : public std::runtime_error {
   public:
    // ------------------------------------------------------------------------
    // Ctors
    // ------------------------------------------------------------------------

    template <typename... Args>
    DocError(std::format_string<Args...> fmt, Args&&... args) noexcept
        : std::runtime_error("") {
        _message = "doc_error: "
                   + std::vformat(fmt.get(), std::make_format_args(args...));
    }

    // ------------------------------------------------------------------------
    // Copy
    // ------------------------------------------------------------------------
    DocError(const DocError&) noexcept                     = default;
    auto operator =(const DocError&) noexcept -> DocError& = default;

    // ------------------------------------------------------------------------
    // Move
    // ------------------------------------------------------------------------
    DocError(DocError&&) noexcept                     = default;
    auto operator =(DocError&&) noexcept -> DocError& = default;

    // ------------------------------------------------------------------------
    // Dtor
    // ------------------------------------------------------------------------
    ~DocError(void) noexcept = default;

   public:
    // ------------------------------------------------------------------------
    // Lookup
    // ------------------------------------------------------------------------

    [[nodiscard]] auto what(void) const noexcept -> const char* override;

   private:
    std::string _message {};
};

#endif
