#include <stdio.h>
#include <stdbool.h>
#include <string.h>

_Bool is_utf8(const char* str, size_t len) {
    size_t i = 0;
    while (i < len) {
        unsigned char ch = (unsigned char)str[i];
        if (ch < 0x80) {
            // 1-byte UTF-8 sequence (0xxxxxxx)
            i++;
        } else if ((ch & 0xE0) == 0xC0) {
            // 2-byte UTF-8 sequence (110xxxxx 10xxxxxx)
            if (i + 1 >= len || (str[i + 1] & 0xC0) != 0x80) {
                return false;
            }
            i += 2;
        } else if ((ch & 0xF0) == 0xE0) {
            // 3-byte UTF-8 sequence (1110xxxx 10xxxxxx 10xxxxxx)
            if (i + 2 >= len || (str[i + 1] & 0xC0) != 0x80 || (str[i + 2] & 0xC0) != 0x80) {
                return false;
            }
            i += 3;
        } else if ((ch & 0xF8) == 0xF0) {
            // 4-byte UTF-8 sequence (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx)
            if (i + 3 >= len || (str[i + 1] & 0xC0) != 0x80 || (str[i + 2] & 0xC0) != 0x80 || (str[i + 3] & 0xC0) != 0x80) {
                return false;
            }
            i += 4;
        } else {
            // Invalid UTF-8 sequence
            return false;
        }
    }
    // Проверка, что строка не превышает заданную длину
    if (i != len) {
        return false;
    }
    return true;
}


void test_is_utf8(const char* str, size_t len, _Bool expected_result) {
    _Bool result = is_utf8(str, len);
    printf("Input: \"%.*s\"\n", (int)len, str);
    printf("Expected result: %s\n", expected_result ? "true" : "false");
    printf("Actual result: %s\n", result ? "true" : "false");
    printf("Test %s\n\n", result == expected_result ? "passed" : "failed");
}

int main() {
    // Valid UTF-8 strings
    test_is_utf8("Hello, world!", 13, true);
    test_is_utf8("Привет, мир!", 25, true);
    test_is_utf8("こんにちは、世界！", 27, true);
    test_is_utf8("你好，世界！", 15, true);

    // Invalid UTF-8 strings
    test_is_utf8("Hello\x80, world!", 15, false);
    test_is_utf8("Привет\xF0\x28\x8C\xBC, мир!", 31, false);
    test_is_utf8("こんにちは\xE3\x81\x82\xE3\x81\x84\xE3\x81\x86、世界！", 37, true);
    test_is_utf8("你好\xC3\x28\xC3\xA0\xC3\xA9，世界！", 21, false);
    printf("end");
    return 0;
}