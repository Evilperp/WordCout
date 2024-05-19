#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 函数声明
void count_chars_words(const char *filename, int count_chars, int count_words, long *char_count, int *word_count);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c|-w] [input_file_name]\n", argv[0]);
        return 1;
    }

    char *filename = argv[2];
    int count_chars = (strcmp(argv[1], "-c") == 0);
    int count_words = (strcmp(argv[1], "-w") == 0);

    if (!count_chars && !count_words) {
        printf("Invalid parameter. Use -c for character count or -w for word count.\n");
        return 1;
    }

    long char_count = 0;
    int word_count = 0;

    count_chars_words(filename, count_chars, count_words, &char_count, &word_count);

    if (count_chars) {
        printf("字符数：%ld\n", char_count);
    }
    if (count_words) {
        printf("单词数：%d\n", word_count);
    }

    return 0;
}

void count_chars_words(const char *filename, int count_chars, int count_words, long *char_count, int *word_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int in_word = 0; // 标记是否在单词内

    while (!feof(file)) {
        char ch = fgetc(file);
        if (feof(file)) break;

        if (count_chars) {
            (*char_count)++;
        }

        if (isspace(ch) || ch == ',') { // 空格、制表符、换行符或逗号
            in_word = 0;
        } else if (!in_word) { // 新单词的开始
            in_word = 1;
            if (count_words) {
                (*word_count)++;
            }
        }
    }

    fclose(file);
}
