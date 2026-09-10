#include <libhtml/html_doc.hxx>
#include <format>

auto Test_HtmlDoc_Copy(int, char**) -> int {
    HtmlDoc doc {};

    doc.head(HtmlNode {"head"}.prop("prop", "value"));
    doc.body(HtmlNode {"body"}.prop("prop", "value"));

    {
        // copy ctor
        const auto val {doc};

        {
            /// test head
            const auto head {val.head()};

            if (const auto expected {"head"}; head.tagName() != expected)
                throw std::runtime_error(
                    std::format("{}:{}: expected tag name '{}' (got '{}')",
                                __FILE__, __LINE__, expected, head.tagName()));
            else if (const auto expected {1}; head.propsSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} properties (got '{}')", __FILE__,
                    __LINE__, expected, head.propsSize()));
            else if (const auto expected {0}; head.childrenSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} children (got '{}')", __FILE__,
                    __LINE__, expected, head.childrenSize()));

            //// test properties
            if (const auto name {"prop"}, expected {"value"};
                head.prop(name) != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                    __FILE__, __LINE__, name, expected, head.prop(name)));
        }

        {
            /// test body
            const auto body {val.body()};

            if (const auto expected {"body"}; body.tagName() != expected)
                throw std::runtime_error(
                    std::format("{}:{}: expected tag name '{}' (got '{}')",
                                __FILE__, __LINE__, expected, body.tagName()));
            else if (const auto expected {1}; body.propsSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} properties (got '{}')", __FILE__,
                    __LINE__, expected, body.propsSize()));
            else if (const auto expected {0}; body.childrenSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} children (got '{}')", __FILE__,
                    __LINE__, expected, body.childrenSize()));

            //// test properties
            if (const auto name {"prop"}, expected {"value"};
                body.prop(name) != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                    __FILE__, __LINE__, name, expected, body.prop(name)));
        }
    }

    {
        // copy operator
        const auto val = doc;

        {
            /// test head
            const auto head {val.head()};

            if (const auto expected {"head"}; head.tagName() != expected)
                throw std::runtime_error(
                    std::format("{}:{}: expected tag name '{}' (got '{}')",
                                __FILE__, __LINE__, expected, head.tagName()));
            else if (const auto expected {1}; head.propsSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} properties (got '{}')", __FILE__,
                    __LINE__, expected, head.propsSize()));
            else if (const auto expected {0}; head.childrenSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} children (got '{}')", __FILE__,
                    __LINE__, expected, head.childrenSize()));

            //// test properties
            if (const auto name {"prop"}, expected {"value"};
                head.prop(name) != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                    __FILE__, __LINE__, name, expected, head.prop(name)));
        }

        {
            /// test body
            const auto body {val.body()};

            if (const auto expected {"body"}; body.tagName() != expected)
                throw std::runtime_error(
                    std::format("{}:{}: expected tag name '{}' (got '{}')",
                                __FILE__, __LINE__, expected, body.tagName()));
            else if (const auto expected {1}; body.propsSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} properties (got '{}')", __FILE__,
                    __LINE__, expected, body.propsSize()));
            else if (const auto expected {0}; body.childrenSize() != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected {} children (got '{}')", __FILE__,
                    __LINE__, expected, body.childrenSize()));

            //// test properties
            if (const auto name {"prop"}, expected {"value"};
                body.prop(name) != expected)
                throw std::runtime_error(std::format(
                    "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                    __FILE__, __LINE__, name, expected, body.prop(name)));
        }
    }

    return 0;
}
