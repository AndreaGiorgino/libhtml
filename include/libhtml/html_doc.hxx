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
    // Lookup
    // ------------------------------------------------------------------------

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
     * @brief Get the document head
     */
    auto head(HtmlNode head) -> void;

    /**
     * @brief Get the document body
     */
    auto body(HtmlNode head) -> void;

   private:
    HtmlNode _head {};
    HtmlNode _body {};
};

#endif
