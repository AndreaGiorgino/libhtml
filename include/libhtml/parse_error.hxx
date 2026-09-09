#pragma once
#ifndef H_PARSE_ERROR
#define H_PARSE_ERROR

#include <format>

/**
 * @class ParseError
 * @brief Represents a parsing error
 *
 */
class ParseError final : public std::runtime_error {
   public:
    // ------------------------------------------------------------------------
    // Ctors
    // ------------------------------------------------------------------------

    template <typename... Args>
    ParseError(std::format_string<Args...> fmt, Args&&... args) noexcept
        : std::runtime_error("") {
        _message = "parse_error: "
                   + std::vformat(fmt.get(), std::make_format_args(args...));
    }

    // ------------------------------------------------------------------------
    // Copy
    // ------------------------------------------------------------------------
    ParseError(const ParseError&) noexcept                     = default;
    auto operator =(const ParseError&) noexcept -> ParseError& = default;

    // ------------------------------------------------------------------------
    // Move
    // ------------------------------------------------------------------------
    ParseError(ParseError&&) noexcept                     = default;
    auto operator =(ParseError&&) noexcept -> ParseError& = default;

    // ------------------------------------------------------------------------
    // Dtor
    // ------------------------------------------------------------------------
    ~ParseError(void) noexcept = default;

   public:
    // ------------------------------------------------------------------------
    // Lookup
    // ------------------------------------------------------------------------

    [[nodiscard]] auto what(void) const noexcept -> const char* override;

   private:
    std::string _message {};
};

#endif
