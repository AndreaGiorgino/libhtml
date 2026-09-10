#include <libhtml/html_node.hxx>
#include <sstream>

auto Test_HtmlNode_Decode(int, char**) -> int {
    std::stringstream ss {};
    ss << R"(<main>
      <p>Paragraph with <strong>bold</strong> and <em>italic</em> text.</p>
      <hr />
      <img src="test.jpg" alt="Test image" data-boolean />
    </main>)";

    const auto node {HtmlNode::decode(ss)};

    // test <main>
    if (const auto expected {"main"}; node.tagName() != expected)
        throw std::runtime_error(
            std::format("{}:{}: expected tag name '{}' (got '{}')", __FILE__,
                        __LINE__, expected, node.tagName()));
    else if (const auto expected {0}; node.propsSize() != expected)
        throw std::runtime_error(
            std::format("{}:{}: expected {} properties (got '{}')", __FILE__,
                        __LINE__, expected, node.propsSize()));
    else if (const auto expected {3}; node.childrenSize() != expected)
        throw std::runtime_error(
            std::format("{}:{}: expected {} children (got '{}')", __FILE__,
                        __LINE__, expected, node.childrenSize()));

    {
        /// test child <p>
        const auto child {std::get<HtmlNode>(node.child(0))};

        if (const auto expected {"p"}; child.tagName() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected tag name '{}' (got '{}')",
                            __FILE__, __LINE__, expected, child.tagName()));
        else if (const auto expected {0}; child.propsSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} properties (got '{}')",
                            __FILE__, __LINE__, expected, child.propsSize()));
        else if (const auto expected {5}; child.childrenSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} children (got '{}')", __FILE__,
                            __LINE__, expected, child.childrenSize()));

        {
            //// test nested string content
            const auto nestedContent {std::get<std::string>(child.child(0))};

            if (const auto expected {"Paragraph with "};
                nestedContent != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected string content '{}' (got '{}')", __FILE__,
                    __LINE__, expected, nestedContent));
        }

        {
            //// test nested <b>
            const auto nested {std::get<HtmlNode>(child.child(1))};

            if (const auto expected {"strong"}; nested.tagName() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected tag name '{}' (got '{}')", __FILE__,
                    __LINE__, expected, nested.tagName()));
            else if (const auto expected {0}; nested.propsSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} properties (got '{}')", __FILE__,
                    __LINE__, expected, nested.propsSize()));
            else if (const auto expected {1}; nested.childrenSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} nestedren (got '{}')", __FILE__,
                    __LINE__, expected, nested.childrenSize()));

            {
                ///// test nested string content
                const auto nestedContent {
                    std::get<std::string>(nested.child(0))};

                if (const auto expected {"bold"}; nestedContent != expected)
                    throw std::runtime_error(std::format(
                        "{}:{}: expected string content '{}' (got '{}')",
                        __FILE__, __LINE__, expected, nestedContent));
            }
        }

        {
            //// test nested string content
            const auto nestedContent {std::get<std::string>(child.child(2))};

            if (const auto expected {" and "}; nestedContent != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected string content '{}' (got '{}')", __FILE__,
                    __LINE__, expected, nestedContent));
        }

        {
            //// test nested <em>
            const auto nested {std::get<HtmlNode>(child.child(3))};

            if (const auto expected {"em"}; nested.tagName() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected tag name '{}' (got '{}')", __FILE__,
                    __LINE__, expected, nested.tagName()));
            else if (const auto expected {0}; nested.propsSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} properties (got '{}')", __FILE__,
                    __LINE__, expected, nested.propsSize()));
            else if (const auto expected {1}; nested.childrenSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} nestedren (got '{}')", __FILE__,
                    __LINE__, expected, nested.childrenSize()));

            {
                ///// test nested string content
                const auto nestedContent {
                    std::get<std::string>(nested.child(0))};

                if (const auto expected {"italic"}; nestedContent != expected)
                    throw std::runtime_error(std::format(
                        "{}:{}: expected string content '{}' (got '{}')",
                        __FILE__, __LINE__, expected, nestedContent));
            }
        }

        {
            //// test nested string content
            const auto nestedContent {std::get<std::string>(child.child(4))};

            if (const auto expected {" text."}; nestedContent != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected string content '{}' (got '{}')", __FILE__,
                    __LINE__, expected, nestedContent));
        }
    }

    {
        /// test child <hr>
        const auto child {std::get<HtmlNode>(node.child(1))};

        if (const auto expected {"hr"}; child.tagName() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected tag name '{}' (got '{}')",
                            __FILE__, __LINE__, expected, child.tagName()));
        else if (const auto expected {0}; child.propsSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} properties (got '{}')",
                            __FILE__, __LINE__, expected, child.propsSize()));
        else if (const auto expected {0}; child.childrenSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} children (got '{}')", __FILE__,
                            __LINE__, expected, child.childrenSize()));
    }

    {
        /// test child <img>
        const auto child {std::get<HtmlNode>(node.child(2))};

        if (const auto expected {"img"}; child.tagName() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected tag name '{}' (got '{}')",
                            __FILE__, __LINE__, expected, child.tagName()));
        else if (const auto expected {3}; child.propsSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} properties (got '{}')",
                            __FILE__, __LINE__, expected, child.propsSize()));
        else if (const auto expected {0}; child.childrenSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} children (got '{}')", __FILE__,
                            __LINE__, expected, child.childrenSize()));

        //// test properties
        const auto props {child.props()};

        if (const auto name {"src"}, expected {"test.jpg"};
            child.prop(name) != expected)
            throw std::runtime_error(std::format(
                "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                __FILE__, __LINE__, name, expected, child.prop(name)));
        else if (const auto name {"alt"}, expected {"Test image"};
                 child.prop(name) != expected)
            throw std::runtime_error(std::format(
                "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                __FILE__, __LINE__, name, expected, child.prop(name)));
        else if (const auto name {"data-boolean"}, expected {"data-boolean"};
                 child.prop(name) != expected)
            throw std::runtime_error(std::format(
                "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                __FILE__, __LINE__, name, expected, child.prop(name)));
    }

    return 0;
}
