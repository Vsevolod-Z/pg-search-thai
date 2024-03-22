/*-------------------------------------------------------------------------
 *
 * tokenizer.c
 *		  Thai text search parser
 *
 * IDENTIFICATION
 *		thai_parser/src/tokenizer.c
 *
 * Copyright (c) 2014, Di Warachet (zdk)
 * License: http://www.gnu.org/licenses/gpl.html GPL version 2 or higher
 *-------------------------------------------------------------------------
 */

#include </usr/local/include/thai/thbrk.h>
#include "thai_parser.h"
#include "converter.h"
#include "tokenizer.h"
#include <stdio.h>
#include <stdbool.h>

void print_parser_ctx(const parser_ctx_t* ctx) {
    fprintf(stderr,"text:%s    ", ctx->text);
    fprintf(stderr,"text_len: %d    ", ctx->text_len);
    fprintf(stderr,"buf:%s ", ctx->buf);
    fprintf(stderr,"buf_len: %d ", ctx->buf_len);
    fprintf(stderr,"pos: %p ", (void*)ctx->pos);
    fprintf(stderr,"num: %d ", ctx->num);
    fprintf(stderr,"cur_id: %d\n", ctx->cur_id);
}

int th_ubrk(char* text, int* pos, int text_len)
{
    
    int num = 0;
    ThBrk* _th_brk = th_brk_new(NULL);
    char* tis_text = calloc(text_len, sizeof(char));
    memset(tis_text,0,text_len);
    perror("conv");
    conv_code("utf-8", "tis620", text, text_len, tis_text, text_len);
    
    num = th_brk_find_breaks(_th_brk, (const thchar_t*)tis_text, pos, text_len);
    trans_pos(tis_text, pos, num);

    free(tis_text);
    th_brk_delete(_th_brk);
    return num;
}

int get_convert_char_to_unsigned_char_int(int char_num){
    if (char_num < 0){
        return char_num + 128 + 128;
    }
    return char_num;
}

int get_char_bytes_num(int firstByte){
    if (firstByte >= 0xF0) {
        fprintf(stderr, "firstByte >= 0xF0: %d\n", firstByte);
        // Символ занимает 4 байта (не обрабатываем в этом примере)
        return 4;
    } else if (firstByte >= 0xE0  ){
        fprintf(stderr, "firstByte >= 0xE0: %d\n", firstByte);
        // Символ занимает 3 байта
        return 3;
    } else if (firstByte >= 0xC0) {
        fprintf(stderr, "firstByte >= 0xC0: %d\n", firstByte);
        // Символ занимает 2 байта
        return 2;
    } else {
        fprintf(stderr, "Символ занимает 1 байт: %d\n", firstByte);
        // Символ занимает 1 байт
        return 1;
    }
}

int get_thai_word(parser_ctx_t* ctx, char** token, int *token_len)
{
    int cell_num = 0;
    if (ctx->cur_id == -1) {
        ctx->buf_len = 0;
        ctx->buf     = ctx->text;
        for (int i = 0; i < ctx->text_len; i++) {
            fprintf(stderr, "for: %d , text:%s, i: %d\n", get_convert_char_to_unsigned_char_int((int)*(ctx->buf + ctx->buf_len)), ctx->buf + ctx->buf_len, i);
            if(get_char_bytes_num(get_convert_char_to_unsigned_char_int((int)*(ctx->buf + ctx->buf_len))) == 3 && get_convert_char_to_unsigned_char_int((int)*(ctx->buf + ctx->buf_len)) == 224){
                ctx->buf_len+=3;
                i+=3;
            } else {
                fprintf(stderr, "break: %d , text:%s\n", get_convert_char_to_unsigned_char_int((int)*(ctx->buf + ctx->buf_len)), ctx->buf + ctx->buf_len);
                break;
            }
        }

        if (ctx->buf_len <= 0)
            return 0;

        // Allocate position array. Use maximum length
        cell_num = ctx->buf_len / sizeof(wchar_t) + 1;
        ctx->pos = (int*)calloc(sizeof(int), cell_num);

        // word break for utf-8 text
        ctx->num    = th_ubrk(ctx->buf, ctx->pos, ctx->buf_len);
        ctx->cur_id = 0;
    }

    if (ctx->cur_id > ctx->num) {
        // no word
        *token_len     = 0;
        ctx->cur_id    = -1;
        ctx->text     += ctx->buf_len;
        ctx->text_len -= ctx->buf_len;
        free(ctx->pos);
        return 0;
    } else if (ctx->cur_id == 0) {
        // the first word
        *token_len = ctx->pos[0];
        *token     = ctx->buf;
    } else if (ctx->cur_id == ctx->num) {
        // the last word
        *token_len = ctx->buf_len - ctx->pos[ctx->cur_id - 1];
        *token     = ctx->buf + ctx->pos[ctx->cur_id - 1];
    } else {
        // And those middle words
        *token_len = ctx->pos[ctx->cur_id] - ctx->pos[ctx->cur_id - 1];
        *token     = ctx->buf + ctx->pos[ctx->cur_id - 1];
    }
    // move to next word
    ctx->cur_id++;
    return 'a';
}

int get_non_thai_word(parser_ctx_t* ctx, char** token, int *token_len)
{
    int ret = 0;
    int len = 0;
    if (ctx->text_len <= 0)
        return 0;

    fprintf(stderr, "get_non_thai_word_num: %d\n", (int)*(ctx->text + len));
    while (isspace(*(ctx->text + len))) {
        len++;
        perror("isspace len++");
    }

    fprintf(stderr, "len: %d\n", len);
    if (len == 0 ) {
        while (isalnum(*(ctx->text + len)) || ispunct(*(ctx->text + len))) {
            len++;
        }
        if (len == 0) {
            len += get_char_bytes_num(get_convert_char_to_unsigned_char_int((int)*(ctx->text + len)));
            ret = 'd';
            perror("ret d many bytes");
        }else{
            ret = 'b';
            perror("ret b");
        }
    } else{
        ret = 'c';
        perror("ret c");
    }

    if (len > 0) {
        *token         = ctx->text;
        *token_len     = len;
        ctx->text     += len;
        ctx->text_len -= len;
        return ret;
    } else {
        return 0;
    }
}