#include <libhtml/parse_error.hxx>

auto ParseError::what(void) const noexcept -> const char* {
    return _message.c_str();
}
