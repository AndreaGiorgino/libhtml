#include <libhtml/html_doc.hxx>
#include <sstream>

auto Test_HtmlDoc_Decode(int, char**) -> int {
    {
        // valid
        std::stringstream ss {};

        ss << R"(
            <!-- comment -->

            <!doctype html>
            <html lang="en-US">
                <!-- comment -->

                <head prop="value"></head>
                <body prop="value"></body>
            </html>
        )";

        const auto doc {HtmlDoc::decode(ss)};

        /// test properties
        if (const auto name {"lang"}, expected {"en-US"};
            doc.prop(name) != expected)
            throw std::runtime_error(std::format(
                "{}:{}: expected attribute '{}' to be '{}' (got '{}')",
                __FILE__, __LINE__, name, expected, doc.prop(name)));

        {
            /// test head
            const auto head {doc.head()};

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
            const auto body {doc.body()};

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
