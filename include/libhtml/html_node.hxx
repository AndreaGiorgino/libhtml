#pragma once
#ifndef H_HTML_NODE
#define H_HTML_NODE

#include <istream>
#include <unordered_map>
#include <variant>
#include <vector>

class HtmlNode {
   public:
    // ------------------------------------------------------------------------
    // Ctors
    // ------------------------------------------------------------------------
    HtmlNode(std::string_view tagName = "div") noexcept;

    /**
     * @brief Decode an html node from stream
     *
     * @param is The input stream
     *
     * @throws libhtml::ParseError When any parsing error has occured
     */
    [[nodiscard]] static auto decode(std::istream& is) -> HtmlNode;

    /**
     * @brief Decode an html node from string
     *
     * @param raw The input string
     *
     * @throws libhtml::ParseError When any parsing error has occured
     */
    [[nodiscard]] static auto decode(std::string_view raw) -> HtmlNode;

    // ------------------------------------------------------------------------
    // Copy
    // ------------------------------------------------------------------------
    HtmlNode(const HtmlNode&) noexcept                     = default;
    auto operator =(const HtmlNode&) noexcept -> HtmlNode& = default;

    // ------------------------------------------------------------------------
    // Move
    // ------------------------------------------------------------------------
    HtmlNode(HtmlNode&&) noexcept                     = default;
    auto operator =(HtmlNode&&) noexcept -> HtmlNode& = default;

    // ------------------------------------------------------------------------
    // Dtor
    // ------------------------------------------------------------------------
    ~HtmlNode(void) noexcept = default;

   public:
    // ------------------------------------------------------------------------
    // Capacity
    // ------------------------------------------------------------------------

    /**
     * @brief Get the properties map size
     */
    [[nodiscard]] auto propsSize(void) const noexcept -> std::size_t;

    /**
     * @brief Get the children collection size
     */
    [[nodiscard]] auto childrenSize(void) const noexcept -> std::size_t;

    // ------------------------------------------------------------------------
    // Lookup
    // ------------------------------------------------------------------------

    /**
     * @brief Get the tag name
     */
    [[nodiscard]] auto tagName(void) const noexcept -> std::string;

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
     * @brief Get the child node at index
     *
     * @param index The index of the child node
     *
     * @throw std::out_of_range When accessing an invalid index
     */
    [[nodiscard]] auto child(std::size_t index) const
        -> std::variant<std::string, HtmlNode>;

    /**
     * @brief Get the children collection
     */
    [[nodiscard]] auto children(void) const noexcept
        -> std::vector<std::variant<std::string, HtmlNode>>;

    // ------------------------------------------------------------------------
    // Modifiers
    // ------------------------------------------------------------------------

    /**
     * @brief Set the tag name
     *
     * @param name The tag name
     */
    auto tagName(std::string_view name) noexcept -> void;

    /**
     * @brief Set a property value and return self
     *
     * @param name The property name
     * @param value The property value
     */
    auto prop(std::string_view name, std::string_view value) noexcept
        -> HtmlNode&;

    /**
     * @brief Clear the properties map
     */
    auto clearProps(void) noexcept -> void;

    /**
     * @brief Add a node to the children collection
     *
     * @param node The node to add
     */
    auto addChild(std::variant<std::string, HtmlNode> node) noexcept
        -> HtmlNode&;

    /**
     * @brief Clear the children collection
     */
    auto clearChildren(void) noexcept -> void;

    // ------------------------------------------------------------------------
    // Print
    // ------------------------------------------------------------------------

    /**
     * @brief Encode the node
     *
     * @param indent The indentation to apply
     */
    [[nodiscard]] auto encode(std::size_t indent = 4) const noexcept
        -> std::string;

   private:
    /**
     * @brief Encode the node recursively
     *
     * @param node The node to encode
     * @param indent The indentation to apply
     * @param depth The depth level
     */
    friend auto _encodeRecursive(const HtmlNode& node, std::size_t indent,
                                 std::size_t depth) noexcept -> std::string;

   private:
    std::string _tagName {};
    std::unordered_map<std::string, std::string> _props {};
    std::vector<std::variant<std::string, HtmlNode>> _children {};
};

#endif
