#include <format>
#include <libhtml/html_node.hxx>

auto Test_HtmlNode_Copy(int, char**) -> int {
    HtmlNode node {"span"};

    node.prop("prop-1", "value-1").prop("prop-2", "value-2");
    node.addChild("content ").addChild(HtmlNode {"b"}.addChild("bold"));

    {
        // copy ctor
        const auto val {node};

        if (const auto expected {"span"}; val.tagName() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected tag name '{}' (got '{}')",
                            __FILE__, __LINE__, expected, val.tagName()));
        else if (const auto expected {2}; val.propsSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} properties (got '{}')",
                            __FILE__, __LINE__, expected, val.propsSize()));
        else if (const auto expected {2}; val.childrenSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} children (got '{}')", __FILE__,
                            __LINE__, expected, val.childrenSize()));

        //// test properties
        if (const auto name {"prop-1"}, expected {"value-1"};
            val.prop(name) != expected)
            throw std::runtime_error(std::format(
                "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                __FILE__, __LINE__, name, expected, val.prop(name)));
        else if (const auto name {"prop-2"}, expected {"value-2"};
                 val.prop(name) != expected)
            throw std::runtime_error(std::format(
                "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                __FILE__, __LINE__, name, expected, val.prop(name)));

        {
            /// test nested string content
            const auto nestedContent {std::get<std::string>(val.child(0))};

            if (const auto expected {"content "}; nestedContent != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected string content '{}' (got '{}')", __FILE__,
                    __LINE__, expected, nestedContent));
        }

        {
            /// test child <b>
            const auto child {std::get<HtmlNode>(val.child(1))};

            if (const auto expected {"b"}; child.tagName() != expected)
                throw std::runtime_error(
                    std::format("{}:{}: expected tag name '{}' (got '{}')",
                                __FILE__, __LINE__, expected, child.tagName()));
            else if (const auto expected {0}; child.propsSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} properties (got '{}')", __FILE__,
                    __LINE__, expected, child.propsSize()));
            else if (const auto expected {1}; child.childrenSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} children (got '{}')", __FILE__,
                    __LINE__, expected, child.childrenSize()));

            {
                //// test nested string content
                const auto nestedContent {
                    std::get<std::string>(child.child(0))};

                if (const auto expected {"bold"}; nestedContent != expected)
                    throw std::runtime_error(std::format(
                        "{}:{}: expected string content '{}' (got '{}')",
                        __FILE__, __LINE__, expected, nestedContent));
            }
        }
    }

    {
        // copy operator
        const auto val = node;

        if (const auto expected {"span"}; val.tagName() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected tag name '{}' (got '{}')",
                            __FILE__, __LINE__, expected, val.tagName()));
        else if (const auto expected {2}; val.propsSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} properties (got '{}')",
                            __FILE__, __LINE__, expected, val.propsSize()));
        else if (const auto expected {2}; val.childrenSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} children (got '{}')", __FILE__,
                            __LINE__, expected, val.childrenSize()));

        //// test properties
        if (const auto name {"prop-1"}, expected {"value-1"};
            val.prop(name) != expected)
            throw std::runtime_error(std::format(
                "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                __FILE__, __LINE__, name, expected, val.prop(name)));
        else if (const auto name {"prop-2"}, expected {"value-2"};
                 val.prop(name) != expected)
            throw std::runtime_error(std::format(
                "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                __FILE__, __LINE__, name, expected, val.prop(name)));

        {
            /// test nested string content
            const auto nestedContent {std::get<std::string>(val.child(0))};

            if (const auto expected {"content "}; nestedContent != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected string content '{}' (got '{}')", __FILE__,
                    __LINE__, expected, nestedContent));
        }

        {
            /// test child <b>
            const auto child {std::get<HtmlNode>(val.child(1))};

            if (const auto expected {"b"}; child.tagName() != expected)
                throw std::runtime_error(
                    std::format("{}:{}: expected tag name '{}' (got '{}')",
                                __FILE__, __LINE__, expected, child.tagName()));
            else if (const auto expected {0}; child.propsSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} properties (got '{}')", __FILE__,
                    __LINE__, expected, child.propsSize()));
            else if (const auto expected {1}; child.childrenSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} children (got '{}')", __FILE__,
                    __LINE__, expected, child.childrenSize()));

            {
                //// test nested string content
                const auto nestedContent {
                    std::get<std::string>(child.child(0))};

                if (const auto expected {"bold"}; nestedContent != expected)
                    throw std::runtime_error(std::format(
                        "{}:{}: expected string content '{}' (got '{}')",
                        __FILE__, __LINE__, expected, nestedContent));
            }
        }
    }

    return 0;
}
