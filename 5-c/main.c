#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

const int OUTER_ARRAYS = 7;
const int INNER_ARRAYS_LIMIT = 30;

struct InputData {
    long long* seeds;
    long long*** maps;
};

char* read_file(char* file_name) {
    FILE* fptr = fopen(file_name, "r");

    if (fptr == NULL) {
        printf("ERROR: File not found\n");
        exit(1);
    }

    fseek(fptr, 0, SEEK_END);
    long fileSize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    char* file_content = (char*)malloc(fileSize + 1);

    fread(file_content, sizeof(char), fileSize, fptr);
    file_content[fileSize] = '\0';

    fclose(fptr);

    return file_content;
}

struct InputData parse_input(char* input) {
    char* output = (char*)malloc(strlen(input) + 1);
    strcpy(output, input);

    long long*** array_3d = (long long***)malloc(OUTER_ARRAYS * sizeof(long long**));

    for (int i = 0; i < 7; i++) {
        array_3d[i] = (long long**)malloc(INNER_ARRAYS_LIMIT * sizeof(long long*));
    }

    char* token = strtok(output, "\n");
    char* seeds_line = token;
    token = strtok(NULL, "\n");

    int array_3d_idx = -1;
    int inner_array_idx = 0;
    while (token != NULL) {
        if (isdigit(token[0])) {
            long long a, b, c;
            sscanf(token, "%lld %lld %lld", &a, &b, &c);         

            array_3d[array_3d_idx][inner_array_idx] = (long long*)malloc(3 * sizeof(long long));
            array_3d[array_3d_idx][inner_array_idx][0] = a;
            array_3d[array_3d_idx][inner_array_idx][1] = b;
            array_3d[array_3d_idx][inner_array_idx][2] = c;
            array_3d[array_3d_idx][inner_array_idx + 1] = NULL;

            inner_array_idx++;
        } else {
            // is a map name, push to next array, starting at index 0
            array_3d_idx++;
            inner_array_idx = 0;
        }

        token = strtok(NULL, "\n");
    }

    long long* seeds = (long long*)malloc(30 * sizeof(long long*));

    char* seed_token = strtok(seeds_line + 7, " ");
    int idx = 0;
    while (seed_token != NULL) {
        long long seed;
        sscanf(seed_token, "%lld", &seed);
        seeds[idx] = seed;
        idx++;
        seed_token = strtok(NULL, " ");
    }

    struct InputData input_data = {
        .seeds = seeds,
        .maps = array_3d
    };

    return input_data;
}

long long get_dest(long long seed, long long** map) {
    for (int i = 0; map[i] != NULL; i++) {
        long long des_range_start = map[i][0];
        long long src_range_start = map[i][1];
        long long range_len       = map[i][2];

        if (seed >= src_range_start && seed < src_range_start + range_len) {
            long long result = seed - src_range_start + des_range_start;
            return result;
        }
    }

    return seed;
}

int main() {
    char* file_content = read_file("input.txt");
    struct InputData input_data = parse_input(file_content);
    
    long long*** array_3d = input_data.maps; 
    long long* seeds = input_data.seeds;

    long long part_1_lowest = LONG_MAX;

    for (int i = 0; seeds[i] != 0; i++) {
        long long seed = seeds[i];

        for (int j = 0; j < OUTER_ARRAYS; j++) {
            seed = get_dest(seed, array_3d[j]);
        }

        if (seed < part_1_lowest) {
            part_1_lowest = seed;
        }
    }

    printf("Part 1: %lld\n", part_1_lowest);

    return 0;
}