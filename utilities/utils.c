#include "utils.h"

/// @brief Checks whether a string `needle` exists in a `haystack` of size `hay_size`
/// @attention Recommendation: the function exits early if a `needle` is found, so arranging
/// `haystack` so that the most likely values of `needle` come first would give a microsecond boost!
/// @param needle The string that is searched for
/// @param haystack The collection of strings that may or may not have an occurence of `needle`
/// @param hay_size Size of `haystack` in elements
/// @return If a string `needle` is found in a `haystack`, `true` is returned, otherwise, `false`.
bool strExists(const char* needle, const char *const *haystack, size_t hay_size)
{
	for(; hay_size!=0; hay_size--, haystack++) {
		if(!strcmp(*haystack, needle)) {
			return(true);
		}
	} return(false);
}

bool iswhitespace(char ch) {
    return (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r');
}

bool isfloat(const char text[]) {
    int len = strlen(text);
    bool has_dot = 0;

    if (len == 0) return 0;

    if (!isdigit((unsigned char)text[0])) return 0;

    for (int i = 0; i < len; i++) {
        if (text[i] == '.') {
            if (has_dot) {
                return 0;
            }
            has_dot = 1;
        } else if (!isdigit((unsigned char)text[i])) {
            return 0;
        }
    }

    return has_dot;
}
