#include <libhtml/html_doc.hxx>
#include <format>

auto Test_HtmlDoc_Ctor(int, char**) -> int {
    const HtmlDoc doc {};

    {
        // test head
        const auto head {doc.head()};

        if (const auto expected {"head"}; head.tagName() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected tag name '{}' (got '{}')",
                            __FILE__, __LINE__, expected, head.tagName()));
        else if (const auto expected {0}; head.propsSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} properties (got '{}')",
                            __FILE__, __LINE__, expected, head.propsSize()));
        else if (const auto expected {0}; head.childrenSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} children (got '{}')", __FILE__,
                            __LINE__, expected, head.childrenSize()));
    }

    {
        // test body
        const auto body {doc.body()};

        if (const auto expected {"body"}; body.tagName() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected tag name '{}' (got '{}')",
                            __FILE__, __LINE__, expected, body.tagName()));
        else if (const auto expected {0}; body.propsSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} properties (got '{}')",
                            __FILE__, __LINE__, expected, body.propsSize()));
        else if (const auto expected {0}; body.childrenSize() != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected {} children (got '{}')", __FILE__,
                            __LINE__, expected, body.childrenSize()));
    }

    return 0;
}
