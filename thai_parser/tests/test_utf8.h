#ifndef TEST_UTF8_H
#define TEST_UTF8_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

_Bool is_utf8(const char* str, size_t len);
void test_is_utf8(const char* str, size_t len, _Bool expected_result, FILE* file);

#endif