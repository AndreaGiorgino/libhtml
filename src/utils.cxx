#include <cstring>
#include <lib/utils.hxx>
#include <libhtml/parse_error.hxx>

namespace utils {
auto trim(std::string_view str) noexcept -> std::string {
    if (str.empty())
        return {};

    return {
        std::find_if(str.begin(), str.end(),
                     [](char ch) { return !isspace(ch); }),
        std::find_if(str.rbegin(), str.rend(),
                     [](char ch) { return !isspace(ch); })
            .base(),
    };
}

auto skipws(std::istream& is) noexcept -> void {
    while (isspace(is.peek()))
        is.ignore();
}

auto skipwsAndComments(std::istream& is) -> void {
    while (!is.eof()) {
        if (isspace(is.peek())) {
            // handle whitespace
            is.ignore();
        } else if (is.peek() == '<') {
            // handle comment
            static constexpr auto prefix {"<!--"};

            const auto start {is.tellg()};

            // check whether prefix matches
            for (size i {}; i < strlen(prefix) && !is.eof(); i++)
                if (is.get() != prefix[i]) {
                    is.seekg(start);
                    break;
                }

            if (is.tellg() == start)
                break;

            auto end {start};

            while (!is.eof())
                if (is.get() == '-' && is.get() == '-') {
                    throwWhenNot(is, '>');

                    end = is.tellg();
                    is.ignore();
                    break;
                }

            if (end == start)
                throw ParseError("unclosed comment opened at position {}",
                                 (int)start);
        } else
            break;
    }
}

auto throwWhenEof(std::istream& is) -> void {
    if (!is.eof())
        return;

    throw ParseError("unexpected end of file");
}

auto throwWhenNot(std::istream& is, char ch) -> void {
    throwWhenEof(is);

    if (is.peek() == ch)
        return;

    throw ParseError("expected character '{}' at position '{}' (got '{}')", ch,
                     (int)is.tellg(), (char)is.peek());
}

auto getUntil(std::istream& is, std::function<bool(char)> predicate) noexcept
    -> std::string {
    std::string buffer {};

    while (!is.eof()) {
        if (predicate(is.peek()))
            break;

        buffer += is.get();
    }

    return buffer;
}

auto indent(std::ostream& os, size indent) noexcept -> void {
    os << std::string(indent, ' ');
}
} // namespace utils
