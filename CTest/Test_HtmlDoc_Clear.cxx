#include <libhtml/html_doc.hxx>

auto Test_HtmlDoc_Clear(int, char**) -> int {
    HtmlDoc doc {};

    doc.prop("lang", "en-US");

    if (const auto expected {1}; doc.propsSize() != expected)
        throw std::runtime_error(
            std::format("{}:{}: expected {} properties (got '{}')", __FILE__,
                        __LINE__, expected, doc.propsSize()));

    doc.clearProps();

    if (const auto expected {0}; doc.propsSize() != expected)
        throw std::runtime_error(
            std::format("{}:{}: expected {} properties (got '{}')", __FILE__,
                        __LINE__, expected, doc.propsSize()));

    return 0;
}
