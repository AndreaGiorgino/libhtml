#include <libhtml/html_doc.hxx>
#include <print>

auto main(int, char**) -> int {
    HtmlDoc doc {
        HtmlNode {"head"}
            .addChild(HtmlNode {"meta"}.prop("charset", "UTF-8"))
            .addChild(
                HtmlNode {"meta"}
                    .prop("name", "viewport")
                    .prop("content", "width=device-width, initial-scale=1.0"))
            .addChild(HtmlNode {"link"}
                          .prop("rel", "stylesheet")
                          .prop("href", "style.css")),
        HtmlNode {"body"}
            .addChild(HtmlNode {"header"}.addChild(
                HtmlNode {"h1"}.addChild("Heading")))
            .addChild(
                HtmlNode {"main"}
                    .addChild(HtmlNode {"p"}.addChild("Some content"))
                    .addChild(HtmlNode {"hr"})
                    .addChild(HtmlNode {"p"}.addChild("Some other content"))),
    };

    doc.prop("lang", "en-US");

    std::println("{}", doc.encode());

    return 0;
}
