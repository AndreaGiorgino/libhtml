#include <libhtml/html_node.hxx>
#include <print>

auto main(int, char**) -> int {
    static constexpr auto raw {
        R"(<div id="container" data-active><span>Content</span></div>)"};

    std::println("Parsing node:");
    std::println("{}\n", raw);

    const auto node {HtmlNode::decode(raw)};

    std::println("Encoded:");
    std::println("{}\n", node.encode());

    return 0;
}
