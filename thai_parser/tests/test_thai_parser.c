/* Test driver for a text context in thai parser */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_utf8.h"
#include "../src/thai_parser.h"
#include "../src/tokenizer.h"
#include "../src/converter.h"


int main(int argc, char* argv[])
{
    parser_ctx_t ctx;
    ctx.text = "\"ทดสอบการสร้างรายการคำไทย hello 123 test test testtest 80%\"";
    if (argc > 1)
        ctx.text = argv[1];
    // printf(">>%s<< ", ctx.text);
    ctx.text_len = strlen(ctx.text);
    ctx.cur_id   = -1;
    char* t = NULL;
    int len = 0;
    char buf[1024];
    while (ctx.text_len > 0) {
        memset(buf, 0, 1024);
        if (get_thai_word(&ctx, &t, &len) == 0) {

            get_non_thai_word(&ctx, &t, &len);
        }

        if (len > 0) {
            memcpy(buf, t, len);
        // perror("t");
        // perror(t);
            if(!is_utf8(buf,len))
            {
                print_perror_hex("NOT UTF8 TEXT!!",buf);
                return -1;
            }

            printf("%s:%d| ", buf,ctx.cur_id );
        }
    }
    printf("\n");
    
    return 0;
}
