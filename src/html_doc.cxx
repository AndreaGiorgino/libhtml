#include <cstring>
#include <lib/utils.hxx>
#include <libhtml/doc_error.hxx>
#include <libhtml/html_doc.hxx>
#include <libhtml/parse_error.hxx>
#include <sstream>

HtmlDoc::HtmlDoc(HtmlNode head, HtmlNode body) : _head(head), _body(body) {
    if (head.tagName() != "head")
        throw DocError(
            "'html' first child must be an 'head' tag (got '{}' instead)",
            head.tagName());

    if (body.tagName() != "body")
        throw DocError(
            "'html' second child must be a 'body' tag (got '{}' instead)",
            body.tagName());
}

auto HtmlDoc::decode(std::istream& is) -> HtmlDoc {
    utils::ignorewsAndComments(is);

    // parse preamble
    static constexpr auto preamble {"<!doctype html>"};

    for (size i {}; i < strlen(preamble); i++) {
        utils::throwWhenEof(is);
        utils::throwWhenNot(is, tolower(preamble[i]));

        if (isspace(is.peek()))
            utils::ignorews(is);
        else
            is.ignore();
    }

    // parse top level node
    utils::ignorewsAndComments(is);

    const auto root {HtmlNode::decode(is)};

    if (root.tagName() != "html")
        throw DocError(
            "document root node must be an 'html' tag (got '{}' instead)",
            root.tagName());
    else if (root.childrenSize() != 2)
        throw DocError(
            "document root node must contain 2 children ('head' and 'body')");

    const auto head {std::get<HtmlNode>(root.child(0))};

    if (head.tagName() != "head")
        throw DocError(
            "'html' first child must be an 'head' tag (got '{}' instead)",
            head.tagName());

    const auto body {std::get<HtmlNode>(root.child(1))};

    if (body.tagName() != "body")
        throw DocError(
            "'html' second child must be a 'body' tag (got '{}' instead)",
            body.tagName());

    // handle remainder
    utils::ignorewsAndComments(is);

    if (!is.eof())
        throw DocError("unexpected trailing character(s) at position {}",
                       (int)is.tellg());

    HtmlDoc buffer {head, body};

    for (const auto& [k, v] : root.props())
        buffer.prop(k, v);

    return buffer;
}

auto HtmlDoc::decode(std::string_view raw) -> HtmlDoc {
    std::stringstream ss {};
    ss << raw;

    return HtmlDoc::decode(ss);
}

auto HtmlDoc::propsSize(void) const noexcept -> std::size_t {
    return _props.size();
}

auto HtmlDoc::prop(std::string_view name) const noexcept -> std::string {
    if (const auto it {_props.find(std::string {name})}; it != _props.end())
        return it->second;

    return {};
}
auto HtmlDoc::props(void) const noexcept
    -> std::unordered_map<std::string, std::string> {
    return _props;
}

auto HtmlDoc::head(void) const noexcept -> HtmlNode {
    return _head;
}

auto HtmlDoc::body(void) const noexcept -> HtmlNode {
    return _body;
}

auto HtmlDoc::prop(std::string_view name, std::string_view value) noexcept
    -> HtmlDoc& {
    _props[std::string {name}] = std::string {value};

    return *this;
}

auto HtmlDoc::head(HtmlNode head) -> void {
    if (head.tagName() != "head")
        throw DocError(
            "'html' first child must be an 'head' tag (got '{}' instead)",
            head.tagName());

    _head = head;
}

auto HtmlDoc::body(HtmlNode body) -> void {
    if (body.tagName() != "body")
        throw DocError(
            "'html' second child must be a 'body' tag (got '{}' instead)",
            body.tagName());

    _body = body;
}
