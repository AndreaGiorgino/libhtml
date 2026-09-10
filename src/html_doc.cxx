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
    return {}; // FIXME: parse data
}

auto HtmlDoc::decode(std::string_view raw) -> HtmlDoc {
    std::stringstream ss {};
    ss << raw;

    return HtmlDoc::decode(ss);
}

auto HtmlDoc::head(void) const noexcept -> HtmlNode {
    return _head;
}

auto HtmlDoc::body(void) const noexcept -> HtmlNode {
    return _body;
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
