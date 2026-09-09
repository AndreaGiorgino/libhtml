#include <libhtml/html_doc.hxx>
#include <sstream>

auto HtmlDoc::decode(std::istream& is) -> HtmlDoc {
    return {}; // FIXME: parse data
}

auto HtmlDoc::decode(std::string_view raw) -> HtmlDoc {
    std::stringstream ss {};
    ss << raw;

    return HtmlDoc::decode(ss);
}
