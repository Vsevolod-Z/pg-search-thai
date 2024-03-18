#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include </usr/local/include/thai/thbrk.h>
#include "test_utf8.h"
#include "../src/thai_parser.h"
#include "../src/tokenizer.h"
#include "../src/converter.h"


void assert_equal(const char* expected, const char* actual, const char* message) {
    if (strcmp(expected, actual) == 0) {
        printf("[PASS] %s\n", message);
    } else {
        printf("[FAIL] %s\n", message);
        printf("Expected: %s\n", expected);
        printf("Actual: %s\n", actual);
    }
    fflush(stdout);
}

void test_conv() {
    char from[] = "utf-8//TRANSLIT";
    char to[] = "tis620//TRANSLIT";
    // char from[] = "tis620";
    // char to[] = "utf-8";
    // char in[] = "Hello, world!";
    char in[] = "CHINA:โกลด์แมน แซคส์ปรับเพิ่มคาดการณ์จีดีพีจีนขึ้นเป็น 6 ในปีนี้";
    size_t in_len = strlen(in);
    while ((in + in_len) != NULL && ((int)*(in + in_len) & 0x80) != 0) {
        in_len++;
    }
    char* tis_text = calloc(in_len, sizeof(char));

    int result = conv_code(from, to, in, in_len, tis_text, in_len);
    perror(tis_text);
    // assert_equal("CHINA:�Ŵ���� ᫤���Ѻ�����Ҵ��ó�մվըչ����� 6 㹻չ��", tis_text, "Output matches expected");
    // assert_equal("[PASS]", result == 0 ? "[PASS]" : "[FAIL]", "Conversion succeeded");

    char from_bk[] = "tis620//TRANSLIT";
    char to_bk[] = "utf-8//TRANSLIT";
    char in_bk[] = "CHINA:โกลด์แมน แซคส์ปรับเพิ่มคาดการณ์จีดีพีจีนขึ้นเป็น 6 ในปีนี้";
    size_t in_len_bk = strlen(in);
    while ((in_bk + in_len_bk) != NULL && ((int)*(in_bk + in_len_bk) & 0x80) != 0) {
        in_len_bk++;
    }
    char* tis_text_bk = calloc(in_len_bk, sizeof(char));

    int result_bk = conv_code(from_bk, to_bk, in_bk, in_len_bk, tis_text_bk, in_len_bk);
    perror(tis_text);
    assert_equal("CHINA:โกลด์แมน แซคส์ปรับเพิ่มคาดการณ์จีดีพีจีนขึ้นเป็น 6 ในปีนี้", tis_text_bk, "Output matches expected");
    assert_equal("[PASS]", result_bk == 0 ? "[PASS]" : "[FAIL]", "Conversion succeeded");

}


int main(int argc, char* argv[])
{
    test_conv();
    // parser_ctx_t ctx;
    // ctx.text = "\"ทดสอบการสร้างรายการคำไทย hello 123 test test testtest 80%\"";
    // if (argc > 1)
    //     ctx.text = argv[1];
    // ctx.text_len = strlen(ctx.text);
    // ctx.cur_id   = -1;
    // char* t = NULL;
    // int len = 0;
    // char buf[1024];
    // int num = 0;
    // int cell_num = 0;
    // int* pos = (int*)calloc(sizeof(int), cell_num);

    // ThBrk* _th_brk = th_brk_new(NULL);
    // char* tis_text = calloc(ctx.text_len, sizeof(char));
    // conv_code("utf-8", "tis620", ctx.text, ctx.text_len, tis_text, text_len);
    // num = th_brk_find_breaks(_th_brk, (const thchar_t*)tis_text, pos, text_len);
    // trans_pos(tis_text, pos, num);
    // free(tis_text);
    // th_brk_delete(_th_brk);
    // conv_code("utf-8", "tis620", text, text_len, tis_text, text_len);
    // conv_code("tis620", "utf-8", msg, len, tmp, sizeof(tmp) - 1);
    // return num;
    return 0;
}




_Bool test_conv_code_thai_to_utf8(){

    return true;
}

_Bool test_conv_code_utf8_to_thai(){

    return true;
}