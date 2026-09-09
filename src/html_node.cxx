#include <lib/utils.hxx>
#include <libhtml/html_node.hxx>
#include <libhtml/parse_error.hxx>
#include <sstream>

HtmlNode::HtmlNode(std::string_view tagName) noexcept : _tagName(tagName) {};

auto HtmlNode::propsSize(void) const noexcept -> std::size_t {
    return _props.size();
}

auto HtmlNode::childrenSize(void) const noexcept -> std::size_t {
    return _children.size();
}

auto HtmlNode::tagName(void) const noexcept -> std::string {
    return _tagName;
}

auto HtmlNode::prop(std::string_view name) const noexcept -> std::string {
    if (const auto it {_props.find(std::string {name})}; it != _props.end())
        return {it->second};

    return {};
}

auto HtmlNode::props(void) const noexcept
    -> std::unordered_map<std::string, std::string> {
    return _props;
}

auto HtmlNode::child(std::size_t index) const
    -> std::variant<std::string, HtmlNode> {
    return _children[index];
}

auto HtmlNode::children(void) const noexcept
    -> std::vector<std::variant<std::string, HtmlNode>> {
    return _children;
}

auto HtmlNode::tagName(std::string_view name) noexcept -> void {
    _tagName = name;
}

auto HtmlNode::prop(std::string_view name, std::string_view value) noexcept
    -> HtmlNode& {
    _props[std::string {name}] = std::string {value};

    return *this;
}

auto HtmlNode::clearProps(void) noexcept -> void {
    _props.clear();
}

auto HtmlNode::addChild(std::variant<std::string, HtmlNode> node) noexcept
    -> HtmlNode& {
    _children.push_back(node);

    return *this;
}

auto HtmlNode::clearChildren(void) noexcept -> void {
    _children.clear();
}

auto HtmlNode::encode(size indent) const noexcept -> std::string {
    return _encodeRecursive(*this, indent, 0);
}
