	#ifndef HEDER_UTILS_H
#define HEDER_UTILS_H

#include <stdbool.h>

#include <stddef.h>
#include <string.h>
/// @brief Checks whether a string `needle` exists in a `haystack` of size `hay_size`
/// @attention Recommendation: the function exits early if a `needle` is found, so arranging
/// `haystack` so that the most likely values of `needle` come first would give a microsecond boost!
/// @param needle The string that is searched for
/// @param haystack The collection of strings that may or may not have an occurence of `needle`
/// @param hay_size Size of `haystack` in elements
/// @return If a string `needle` is found in a `haystack`, `true` is returned, otherwise, `false`.
bool strExists(const char* needle, const char *const *haystack, size_t hay_size);

bool iswhitespace(char ch);
bool isfloat(const char text[]);

	#endif
