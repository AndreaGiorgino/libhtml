#include <lib/utils.hxx>
#include <libhtml/html_node.hxx>
#include <libhtml/parse_error.hxx>
#include <sstream>

HtmlNode::HtmlNode(std::string_view tagName) noexcept : _tagName(tagName) {};

auto HtmlNode::decode(std::istream& is) -> HtmlNode {
    utils::throwWhenNot(is, '<');

    const auto start {is.tellg()};

    is.ignore();
    utils::ignorews(is);

    if (is.peek() == '/') {
        // self closing, unnamed tag
        is.ignore();
        utils::throwWhenNot(is, '>');
        is.ignore();

        return {};
    }

    const auto tagName {
        utils::getUntil(is, [](char ch) { return !isalnum(ch) && ch != '-'; })};

    HtmlNode node {tagName};

    while (!is.eof()) {
        utils::ignorews(is);

        if (!isalnum(is.peek()))
            break;

        // parse property name
        const auto propName {utils::getUntil(
            is, [](char ch) { return !isalnum(ch) && ch != '-'; })};

        utils::ignorews(is);

        if (is.peek() != '=') {
            node.prop(propName, propName);
            continue;
        }

        // parse property value
        is.ignore();
        utils::ignorews(is);
        utils::throwWhenNot(is, '"');
        is.ignore();

        const auto propValue {
            utils::getUntil(is, [](char ch) { return ch == '"'; })};

        utils::throwWhenNot(is, '"');
        is.ignore();

        node.prop(propName, propValue);
    }

    if (is.peek() == '>') {
        // parse contents
        is.ignore();

        while (!is.eof()) {
            utils::ignorewsAndComments(is);

            if (is.eof())
                throw ParseError("unclosed tag '{}' opened at position {}",
                                 tagName, (int)start);

            if (is.peek() == '<') {
                is.ignore();

                if (is.peek() == '/') {
                    // parse close tag
                    is.ignore();
                    utils::ignorews(is);

                    for (size i {}; i < tagName.size(); i++) {
                        if (is.get() != tagName[i])
                            throw ParseError(
                                "unclosed tag '{}' opened at position {}",
                                tagName, (int)start);
                    }

                    utils::ignorews(is);
                    utils::throwWhenNot(is, '>');
                    is.ignore();

                    break;
                }

                // parse child node
                is.seekg((int)is.tellg() - 1);
                node.addChild(HtmlNode::decode(is));
            } else {
                // parse text content
                node.addChild(utils::trim(
                    utils::getUntil(is, [](auto ch) { return ch == '<'; })));
            }
        }
    } else if (is.peek() == '/') {
        is.ignore();
        utils::throwWhenNot(is, '>');
        is.ignore();
    } else
        throw ParseError("unexpected character '{}' at position {}",
                         (char)is.peek(), (int)is.tellg());

    return node;
}

auto HtmlNode::decode(std::string_view raw) -> HtmlNode {
    std::stringstream ss {};
    ss << raw;

    return HtmlNode::decode(ss);
}

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

auto _encodeRecursive(const HtmlNode& node, size indent, size depth) noexcept
    -> std::string {
    std::stringstream ss {};

    utils::indent(ss, indent * depth);
    ss << "<" << node._tagName << " ";

    for (const auto& [k, v] : node._props)
        ss << k << "=\"" << v << "\" ";

    // pop trailing space
    ss.seekp((int)ss.tellp() - 1);
    ss << ">";

    if (indent != 0)
        ss << std::endl;

    for (const auto& child : node._children)
        std::visit(
            [&](const auto& child) {
                using base = std::remove_cvref_t<decltype(child)>;

                if constexpr (std::is_same_v<base, std::string>) {
                    // encode string content
                    utils::indent(ss, indent * (depth + 1));
                    ss << child;

                    if (indent != 0)
                        ss << std::endl;
                } else {
                    // encode child node
                    ss << _encodeRecursive(child, indent, depth + 1);

                    if (indent != 0)
                        ss << std::endl;
                }
            },
            child);

    utils::indent(ss, indent * depth);
    ss << "</" << node._tagName << ">";

    return ss.str();
}
