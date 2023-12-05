#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Maps {
    int length;
    int (*rows)[3];
};

struct Maps createMaps(int rows) {
    struct Maps maps;
    maps.length = rows;
    maps.rows = (int(*)[3])malloc(rows * sizeof(int[3]));
    return maps;
}

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

void parse_input(char* input) {
    char* output = (char*)malloc(strlen(input) + 1);
    strcpy(output, input);

    const int OUTER_ARRAYS = 7;
    const int INNER_ARRAYS_LIMIT = 30;

    int*** array_3d = (int***)malloc(OUTER_ARRAYS * sizeof(int**));

    for (int i = 0; i < 7; i++) {
        array_3d[i] = (int**)malloc(INNER_ARRAYS_LIMIT * sizeof(int*));
    }

    char* token = strtok(output, "\n");
    char* seeds_line = token;
    token = strtok(NULL, "\n");

    int array_3d_idx = -1;
    int inner_array_idx = 0;
    while (token != NULL) {
        if (isdigit(token[0])) {
            int a, b, c;
            sscanf(token, "%d %d %d", &a, &b, &c);            

            array_3d[array_3d_idx][inner_array_idx] = (int*)malloc(3 * sizeof(int));
            array_3d[array_3d_idx][inner_array_idx][0] = a;
            array_3d[array_3d_idx][inner_array_idx][1] = b;
            array_3d[array_3d_idx][inner_array_idx][2] = c;

            inner_array_idx++;
        } else {
            // is a map name, push to next array, starting at index 0
            array_3d_idx++;
            inner_array_idx = 0;
        }

        token = strtok(NULL, "\n");
    }
    
    for (int i = 0; i < 7; i++) {
        printf("--------\n");
        for (int j = 0; array_3d[i][j] != NULL; j++) {
            int a = array_3d[i][j][0];
            int b = array_3d[i][j][1];
            int c = array_3d[i][j][2];
            printf("[%d, %d, %d]\n", a, b, c);
        }
        printf("\n");
    }
}

int get_dest(int seed, struct Maps maps) {
    for (int i = 0; i < maps.length; i++) {
        int* map = maps.rows[i];
        int des_range_start = map[0];
        int src_range_start = map[1];
        int range_len       = map[2];

        if (seed >= src_range_start && seed < src_range_start + 2) {
            return seed - des_range_start + range_len;
        }
    }

    return seed;
}

int main() {
    char* file_content = read_file("example.txt");
    parse_input(file_content);

    // Repeat for every seed
    struct Maps soil_maps = createMaps(2);
    soil_maps.rows[0][0] = 50;
    soil_maps.rows[0][1] = 98;
    soil_maps.rows[0][2] = 2;

    soil_maps.rows[1][0] = 52;
    soil_maps.rows[1][1] = 50;
    soil_maps.rows[1][2] = 48;

    // int soil = get_dest(98, soil_maps);
    // printf("%d\n", soil);

    // Repeat for other stages
    // int fertilizer = get_dest(soil, (int[][3]){{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    // int water = get_dest(fertilizer, (int[][3]){{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    // int light = get_dest(water, (int[][3]){{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    // int temperature = get_dest(light, (int[][3]){{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    // int humidity = get_dest(temperature, (int[][3]){{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
    // int location = get_dest(humidity, (int[][3]){{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

    // printf("%d\n", location);

    // Find lowest location 

    return 0;
}
