#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
//#include <io.h>
#include <stdbool.h>

#define MAX_SIZE 1000000

struct ppm_header {
    unsigned char format[2];
    unsigned char width;
    unsigned char heigth;
    unsigned char RBG;
};

bool is_correct_type(FILE *, int32_t *, int32_t *);
bool has_acceptable_size(char * image);
void print_string_char_by_char(char *);
bool load_ppm(FILE *, struct ppm_header *);
void print_ppm_header(struct ppm_header *);

void print_string_char_by_char(char * string) {
    int32_t i=0;
    for (i=0;i< (int32_t) strlen(string);i++) {
        printf("%d ", string[i]);
    }
}

void print_ppm_header(struct ppm_header * header) {
    printf("format : %c%c (code : %d%d)\n"
    "size : %d %d\n"
    "rbg size : %d\n", header->format[0], header->format[1], (int32_t) header->format[0], (int32_t) header->format[1], (int32_t) header->width, (int32_t) header->heigth, (int32_t) header->RBG);
}

bool load_ppm(FILE * image, struct ppm_header * header) {
    char tmpwidth[100] = "";
    char tmpheight[100] = "";
    char tmpRGB[100] = "";
    fscanf(image, "%c%c %s %s %s", &(header->format[0]), &(header->format[1]), tmpwidth, tmpheight, tmpRGB);
    header->width = (unsigned char) strtol(tmpwidth, NULL, 10);
    header->heigth = (unsigned char) strtol(tmpheight, NULL, 10);
    header->RBG = (unsigned char) strtol(tmpRGB, NULL, 10);
    print_ppm_header(header);
    return 1;
}
/*
int32_t get_size(FILE *);

int32_t get_size(FILE * image) {
    fseek(image, 0, SEEK_SET);

}
*/
bool is_correct_type(FILE * image, int32_t * x, int32_t * y) {
    char line[1024] = "";
    //char delimiter = ' ';
    fgets(line, 1024, image);
    if (strstr(line, "P6") != NULL) {
        fgets(line, 1024, image);
        printf("line : %s\n", line);
        print_string_char_by_char(line);

        /* * x = (int32_t) strtol(strtok(line, &delimiter));
        * y = (int32_t) strtol(strtok(NULL, &delimiter), NULL, 10);
        if (strtok(NULL, &delimiter) != NULL) {
            printf("ERROR : 3rd VALUE FOUND IN IMAGE DIMENSIONS !\n");
            return 0;
        }*/
        *x = *x;
        *y = *y;
        printf("%s", line);
        fgets(line, 1024, image);
        printf("%s", line);
        return 1;
    }
    else return 0;
}


/*
fgets(line, 1024, image);
printf("%s", line);
*/
bool has_acceptable_size(char * image) {
    struct stat * buf;
    buf = malloc(sizeof(struct stat));
    stat(image, buf);
    if (buf->st_size < MAX_SIZE) {
        free(buf);
        return 1;
    }
    else {
        free(buf);
        return 0;
    }
}

int32_t main(int argc, char ** argv) {
    FILE * image;
    struct ppm_header image_header = {};
    if (argc != 2) { // if no param is put, exit and print usage specification
        printf("USAGE : %s <file_name>\nThe file must be in the same directory as the executable !\n", argv[1]);
        exit(1);
    }

    image = fopen(argv[1], "r");  // on ouvre le fichier en mode lecture
    if (!image) {
        printf("ERROR : FILE NOT FOUND\n");
        exit(1);
    }
    else {
        printf("OPENING FILE : %s\n", argv[1]);
    }

    if (!load_ppm(image, &image_header)) {
        printf("ERROR : WRONG FILE FORMAT\n");
        exit(1);
    }
    else {
        printf("FILE HAS VALID FORMAT\n");
    }

    if (!has_acceptable_size(argv[1])) {
        printf("FILE IS TOO LARGE !\n");
    }
    else {
        printf("FILE HAS VALID SIZE\n");
    }

}