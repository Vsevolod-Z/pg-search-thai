/*-------------------------------------------------------------------------
 *
 * converter.c
 *		  Thai text search parser
 *
 * IDENTIFICATION
 *		thai_parser/src/converter.c
 *
 * Copyright (c) 2014, Di Warachet (zdk)
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *-------------------------------------------------------------------------
 */

#include "thai_parser.h"
#include "converter.h"
#include <stdio.h>
#include </usr/local/include/iconv.h>
#include <string.h>
#include <stdbool.h>
// void printedtext(const char* label, int value) {
//     printf("%s: %d\n", label, value);
//     fflush(stdout);
// }
// void printedtextCHAR(const char* label, const char* value) {
//     printf("%s: %s\n", label, value);
//     fflush(stdout);
// }

int conv_code(char* from, char* to, char* in, size_t in_len, char* out, size_t out_len) {
    
    iconv_t conv;
    char* pin = in;
    char* pout = out;
    size_t in_bytes_left = in_len;
    size_t out_bytes_left = out_len;
    perror(from);
    print_perror_p("in", in);
    memset(out, 0, out_len);
    conv = iconv_open(to, from);
    if (conv == (iconv_t)-1) {
        perror("iconv_open");
        return -1;
    }
   
    if (iconv(conv, &pin, &in_bytes_left, &pout, &out_bytes_left) == (size_t)-1) {
        perror("iconv");
        if (errno == EILSEQ) {
        fprintf(stderr, "iconv: Invalid multibyte sequence\n");
        fflush(stdout);
        } else if (errno == EINVAL) {
        fprintf(stderr, "iconv: Incomplete multibyte sequence\n");
        fflush(stdout);
        } else if (errno == E2BIG) {
        fprintf(stderr, "iconv: Argument list too long\n");
        perror("pin");
        perror(pin);
        fflush(stdout);
       
        } else {
        perror("iconv");
    }
        iconv_close(conv);
        return -1;
    }

    iconv_close(conv);

    if(strcmp(to, "utf-8") == 0 && !is_utf8(out,out_len)){
        print_perror_hex("NOT UTF8",out);
        return -1;
    }
    print_perror_p(out, in);
    return 0;
}

void trans_pos(char* msg, int *pos, int pos_len)
{
    // the length of current tis 620 string
    int len = 0;
    // a tempory buffer that is used for utf-8 position calculation.
    char tmp[12800];
    // the last word break postion of tis-620 string
    int last_pos = 0;
    int i = 0;

    memset(tmp,0,sizeof(tmp));
    while (i <= pos_len) {
        if (i == 0) {
            len = pos[0];
            perror("4");
        } else if (i == pos_len) {
            len = strlen(msg);
            perror("5");
        } else {
            len += pos[i] - last_pos;
            perror("6");
        }
        last_pos = pos[i];
        perror("7");

        // convert current tis 620 string to utf-8 to get the corresponding utf-8 length
        perror("!!!!!!!!!!!!!!TIS -> UTF!!!!!!!!!!!!!!!");
        conv_code("tis620", "utf-8", msg, len, tmp, sizeof(tmp) - 1);
        pos[i] = strlen(tmp); //rewrite with utf-8 position
        i++;
    }
}

void print_perror_hex(const char* message, const char* variable) {
    char error_message[256];
    snprintf(error_message, sizeof(error_message), "%s: %s ", message, variable);
    perror(error_message);
}
void print_perror_p(const char* variable,const char* variable2) {
    char error_message[256];
    snprintf(error_message, sizeof(error_message), "Output: %s , IN: %s", variable,variable2);
    perror(error_message);
}

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