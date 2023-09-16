#include "./utils/dirtylist.h"
#include "./utils/logging.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SWAP(t, a, b) {t __hold = *a; *a = *b; *b = __hold;}
void permutes(char *chars, int starting_index, int len_chars, DirtyList *dl) {
    if (starting_index == (len_chars - 1)) {
        char *str = malloc( sizeof( chars ) );
        memcpy( str, chars, sizeof( chars ) );
        dl->add(dl, (void*)str);
    }
    for (int i = starting_index; i < len_chars; i++) {
        SWAP(char, (chars + starting_index), (chars + i))
        permutes(chars, starting_index + 1, len_chars, dl);
        SWAP(char, (chars + starting_index), (chars + i))
    }
}

int count(char* chars, int len, char count) {
    int c = 0;
    char *ptr = chars;
    for (int i = 0; i < len; i++) {
        if (*chars++ == count) {
             c++;
        }
    }
    return c;
}

int count_chars = 0;

bool filter_bbs(char*chars) {
    for (int i = 1; i < count_chars; i++) {
        if (
            count(
                chars + i,
                count_chars - i,
                '1'
            ) < count(
                chars + i,
                count_chars - i,
                '0'
            )
        ) return 0;
    }
    return 1;
}
void print(char* chars) {
    for (int i = 1; i < count_chars; i++) {
        printf("%c", *(chars + i));
    }
    printf("\n");
}

void ppermutes(int *arr, int i, int n) {
    if (!i<n) {
        for (int j = 0; j < n; j++) {
            printf("%d", arr[j]);
        }
        printf("\n");
    }
    return;

    int t;
    for (int j = i; j < n; j++) {
        t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}




int main() {
    DirtyList *dl = new_dirtylist(1, sizeof( char* ));

    printf("Enter n for \"Print all the balanced binary sequences of length n\"> ");
    int num = 0;
    scanf("%d", &num);
    if (num & 1) {
        printf("Cannot use odd number, exiting...\n");
        exit(1);
    } else {
        num = num / 2;
    }
    // DEBUG("allocating chars...")
    char *chars = malloc(sizeof(char) * num * 2);
    for (int i = 0; i < num; i++) {
        chars[i] = '0';
        chars[i+num] = '1';
    }
    // DEBUG("allocated chars")


    permutes(chars, 0, num*2, dl);
    count_chars = num * 2;

    int old_count = dl->count;
    // DEBUG("deduplicate_unsafe...")
    int dedup = dl->deduplicate_unsafe(dl, sizeof( char ) * count_chars );
    // DEBUG("filter_bbs...")
    int removed = dl->filter(dl, filter_bbs);
    dl->for_each(dl, print);
    // printf("dl->count -> %d\n", old_count);
    // printf("dl->filter(dl->deduplicate_unsafe(dl, sizeof( char ) * count_chars )) -> %d\n", dedup);
    // printf("dl->filter(dl, filter_bbs) -> %d\n", removed);
    // printf("dl->count -> %d\n", dl->count);


    printf("Enter n for \"Print all permutations from 1, 2, ..., n in which every odd number appears before every even number\"> ");
    int n = 0;
    scanf("%d", &n);

}