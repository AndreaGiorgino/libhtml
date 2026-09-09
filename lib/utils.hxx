#pragma once
#ifndef H_UTILS
#define H_UTILS

#include <functional>
#include <istream>

using size = std::size_t;

namespace utils {
/**
 * @brief Trim a string
 *
 * @param str The input string
 */
[[nodiscard]] auto trim(std::string_view str) noexcept -> std::string;

/**
 * @brief Skip whitespaces in stream
 *
 * @param is The input stream
 */
auto skipws(std::istream& is) noexcept -> void;

/**
 * @brief Skip whitespaces and comments in stream
 *
 * @param is The input stream
 *
 * @throws libhtml::ParseError When an unclosed comment is found
 */
auto skipwsAndComments(std::istream& is) -> void;

/**
 * @brief Throws when the stream has reached EOF
 *
 * @param is The input stream
 *
 * @throws libhtml::ParseError When the stream has reached EOF
 */
auto throwWhenEof(std::istream& is) -> void;

/**
 * @brief Throws when the next character is not the expected one
 *
 * @param is The input stream
 * @param ch The expected character
 *
 * @throws libhtml::ParseError When the next character is not the expected one
 */
auto throwWhenNot(std::istream& is, char ch) -> void;

[[nodiscard]] auto getUntil(std::istream& is,
                            std::function<bool(char)> predicate) noexcept
    -> std::string;

/**
 * @brief Add indentation to stream
 *
 * @param os The output stream
 * @param indent The indentation to add
 */
auto indent(std::ostream& os, size indent) noexcept -> void;

} // namespace utils

#endif
