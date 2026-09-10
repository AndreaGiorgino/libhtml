#include <libhtml/html_node.hxx>

auto Test_HtmlNode_Capacity(int, char**) -> int {
    HtmlNode node {"span"};

    node.prop("prop-1", "value-1").prop("prop-2", "value-2");
    node.addChild("content ").addChild(HtmlNode {"b"}.addChild("bold"));

    if (const auto expected {2}; node.propsSize() != expected)
        throw std::runtime_error(
            std::format("{}:{}: expected {} properties (got '{}')", __FILE__,
                        __LINE__, expected, node.propsSize()));
    else if (const auto expected {2}; node.childrenSize() != expected)
        throw std::runtime_error(
            std::format("{}:{}: expected {} children (got '{}')", __FILE__,
                        __LINE__, expected, node.childrenSize()));

    return 0;
}
