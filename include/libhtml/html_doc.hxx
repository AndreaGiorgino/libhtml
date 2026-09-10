#pragma once
#ifndef H_HTML_DOC
#define H_HTML_DOC

#include <istream>
#include <libhtml/html_node.hxx>

/**
 * @class HtmlDoc
 * @brief Represents an html document
 *
 */
class HtmlDoc final {
   public:
    // ------------------------------------------------------------------------
    // Ctors
    // ------------------------------------------------------------------------
    HtmlDoc(HtmlNode head = {"head"}, HtmlNode body = {"body"});

    /**
     * @brief Decode an html document from stream
     *
     * @param is The input stream
     *
     * @throws libhtml::ParseError When any parsing error has occured
     */
    [[nodiscard]] static auto decode(std::istream& is) -> HtmlDoc;

    /**
     * @brief Decode an html document from string
     *
     * @param raw The input string
     *
     * @throws libhtml::ParseError When any parsing error has occured
     */
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

   public:
    // ------------------------------------------------------------------------
    // Capacity
    // ------------------------------------------------------------------------

    /**
     * @brief Get the properties map size
     */
    [[nodiscard]] auto propsSize(void) const noexcept -> std::size_t;

    // ------------------------------------------------------------------------
    // Lookup
    // ------------------------------------------------------------------------

    /**
     * @brief Get the property value
     *
     * @param name The property name
     */
    [[nodiscard]] auto prop(std::string_view name) const noexcept
        -> std::string;

    /**
     * @brief Get the properties map
     */
    [[nodiscard]] auto props(void) const noexcept
        -> std::unordered_map<std::string, std::string>;

    /**
     * @brief Get the document head
     */
    [[nodiscard]] auto head(void) const noexcept -> HtmlNode;

    /**
     * @brief Get the document body
     */
    [[nodiscard]] auto body(void) const noexcept -> HtmlNode;

    // ------------------------------------------------------------------------
    // Modifiers
    // ------------------------------------------------------------------------

    /**
     * @brief Set a property value and return self
     *
     * @param name The property name
     * @param value The property value
     */
    auto prop(std::string_view name, std::string_view value) noexcept
        -> HtmlDoc&;

    /**
     * @brief Get the document head
     */
    auto head(HtmlNode head) -> void;

    /**
     * @brief Get the document body
     */
    auto body(HtmlNode head) -> void;

    // ------------------------------------------------------------------------
    // Print
    // ------------------------------------------------------------------------

    [[nodiscard]] auto encode(std::size_t indent = 4) const noexcept
        -> std::string;

   private:
    std::unordered_map<std::string, std::string> _props {};
    HtmlNode _head {};
    HtmlNode _body {};
};

#endif
