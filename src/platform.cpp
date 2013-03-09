#include <platform.h>

Platform::Platform()
{
}

std::string const & Platform::name()
{
    return _name;
}

void Platform::name(std::string const & name)
{
    _name = name;
}

View const & Platform::view()
{
    return _view;
}

