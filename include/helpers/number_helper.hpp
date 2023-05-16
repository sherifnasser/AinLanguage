#pragma once
#include <iostream>
#include <functional>
#define wstring std::wstring

/*
FIXME: can't differentiate between ints and doubles
*/

bool tryconvert(std::function<void()> convertfun);

bool isint(wstring s);

bool isfloat(wstring s);

bool isdouble(wstring s);

bool islong(wstring s);

bool isnum(wstring s);
