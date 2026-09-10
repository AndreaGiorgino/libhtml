#include <libhtml/html_node.hxx>

auto Test_HtmlNode_Ctor(int, char**) -> int {
    if (const auto tagName {HtmlNode {}.tagName()}; tagName != "div")
        throw std::runtime_error(
            std::format("{}:{}: expected tag name 'div' (got '{}')", __FILE__,
                        __LINE__, tagName));
    else if (const auto tagName {HtmlNode {"span"}.tagName()}; tagName != "span")
        throw std::runtime_error(
            std::format("{}:{}: expected tag name 'span' (got '{}')", __FILE__,
                        __LINE__, tagName));

    return 0;
}
