#include <libhtml/html_node.hxx>
#include <format>

auto Test_HtmlNode_Encode(int, char**) -> int {
    HtmlNode node {"span"};

    node.prop("prop-1", "value-1").prop("prop-2", "value-2");
    node.addChild("content ").addChild(HtmlNode {"b"}.addChild("bold"));

    {
        // indent 0
        const auto expected {
            R"(<span prop-2="value-2" prop-1="value-1">content <b>bold</b></span>)"};

        if (const auto encoded {node.encode(0)}; encoded != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected encoded node:\n"
                            "{}\n"
                            "got encoded node:\n"
                            "{}",
                            __FILE__, __LINE__, expected, encoded));
    }

    {
        // indent 4
        const auto expected {R"(<span prop-2="value-2" prop-1="value-1">
    content 
    <b>
        bold
    </b>
</span>)"};

        if (const auto encoded {node.encode()}; encoded != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected encoded node:\n"
                            "{}\n"
                            "got encoded node:\n"
                            "{}",
                            __FILE__, __LINE__, expected, encoded));
    }

    return 0;
}
