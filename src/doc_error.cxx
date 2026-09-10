#include <libhtml/doc_error.hxx>

auto DocError::what(void) const noexcept -> const char* {
    return _message.c_str();
}
