/* Test driver for a text context in thai parser */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/thai_parser.h"
#include "../src/tokenizer.h"
#include "../src/converter.h"

int main(int argc, char* argv[])
{
    parser_ctx_t ctx;
    ctx.text = "สวัสดีครับ";
    if (argc > 1)
        ctx.text = argv[1];
    ctx.text_len = strlen(ctx.text);
    ctx.cur_id   = -1;
    char* t = NULL;
    int len = 0;
    char buf[1024];
    int i = 0;
    while (ctx.text_len > 0) {
        memset(buf, 0, 1024);
        if (get_thai_word(&ctx, &t, &len) == 0) {

            get_non_thai_word(&ctx, &t, &len);
        }

        if (len > 0) {
            memmove(buf, t, len);
            printf("%s:%d| " , buf,ctx.cur_id );
        }
        if (i>1){
        // return 0;
        }
        i++;
    }
    printf("\n");

    return 0;
}
