#include <format>
#include <libhtml/doc_error.hxx>
#include <libhtml/html_doc.hxx>

auto Test_HtmlDoc_Encode(int, char**) -> int {
    HtmlDoc doc {
        HtmlNode {"head"}
            .prop("prop", "value")
            .addChild(HtmlNode {"meta"}.prop("charset", "UTF-8")),
        HtmlNode {"body"}
            .prop("prop", "value")
            .addChild(HtmlNode {"p"}.addChild("Some content")),
    };

    doc.prop("lang", "en-US");

    {
        // indent 0
        const auto expected {
            R"(<!doctype html><html lang="en-US"><head prop="value"><meta charset="UTF-8" /></head><body prop="value"><p>Some content</p></body></html>)"};

        if (const auto encoded {doc.encode(0)}; encoded != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected encoded doc:\n"
                            "{}\n"
                            "got encoded doc:\n"
                            "{}",
                            __FILE__, __LINE__, expected, encoded));
    }

    {
        // indent 4
        const auto expected {
            R"(<!doctype html>
<html lang="en-US">
    <head prop="value">
        <meta charset="UTF-8" />
    </head>
    <body prop="value">
        <p>
            Some content
        </p>
    </body>
</html>)"};

        if (const auto encoded {doc.encode()}; encoded != expected)
            throw std::runtime_error(
                std::format("{}:{}: expected encoded doc:\n"
                            "{}\n"
                            "got encoded doc:\n"
                            "{}",
                            __FILE__, __LINE__, expected, encoded));
    }

    return 0;
}
