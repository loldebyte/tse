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
    unsigned char height;
    unsigned char RBG;
};

typedef struct ppm {
    uint8_t width;
    uint8_t height;
    uint8_t pixels[];
}ppm;

void fill_pixel_array(FILE * image_file, ppm * pixel_array);
ppm * pixel_array_init(uint8_t, uint8_t);
bool is_correct_type(FILE *, int32_t *, int32_t *);
bool has_acceptable_size(char * image);
void print_string_char_by_char(char *);
ppm * load_ppm(FILE *, struct ppm_header *);
void print_ppm_header(struct ppm_header *);
void destroy_pixel_array(ppm *);

void print_string_char_by_char(char * string) {
    int32_t i=0;
    for (i=0;i< (int32_t) strlen(string);i++) {
        printf("%d ", string[i]);
    }
}

void print_ppm_header(struct ppm_header * header) {
    printf("format : %c%c (code : %d%d)\n"
    "size : %d %d\n"
    "rbg size : %d\n", header->format[0], header->format[1], (int32_t) header->format[0], (int32_t) header->format[1], (int32_t) header->width, (int32_t) header->height, (int32_t) header->RBG);
}

void destroy_pixel_array(ppm * pixel_array) {
    free(pixel_array);
}

ppm * pixel_array_init(uint8_t width, uint8_t height) {
    ppm * pixels = malloc(sizeof(ppm)+width*height*sizeof(uint8_t)*3);
    if (!pixels) {
        printf("ERROR : COULD NOT ALLOCATE SPACE FOR PIXEL ARRAY !\n");
        exit(EXIT_FAILURE);
    }
    pixels->width = width;
    pixels->height = height;
    for (uint32_t i=0; i<(uint32_t) width*height*3; i++) {
        pixels->pixels[i] = 0;
    }
    return pixels;
}

ppm * load_ppm(FILE * image, struct ppm_header * header) {
    char tmpwidth[100] = "";
    char tmpheight[100] = "";
    char tmpRGB[100] = "";
    ppm * pixel_array;
    fscanf(image, "%c%c %s %s %s", &(header->format[0]), &(header->format[1]), tmpwidth, tmpheight, tmpRGB);
    if (header->format[0] != 'P') {
        printf("ERROR : WRONG FILE FORMAT !");
        exit(EXIT_FAILURE);
    }
    if (strtol(tmpwidth, NULL, 10) > 255) {
        printf("ERROR : WIDTH IS GREATER THAN 255");
        exit(EXIT_FAILURE);
    }
    if (strtol(tmpheight, NULL, 10) > 255) {
        printf("ERROR : HEIGHT IS GREATER THAN 255");
        exit(EXIT_FAILURE);
    }
    if (strtol(tmpRGB, NULL, 10) > 255) {
        printf("ERROR : RGB IS GREATER THAN 255");
        exit(EXIT_FAILURE);
    }
    header->width = (unsigned char) strtol(tmpwidth, NULL, 10);
    header->height = (unsigned char) strtol(tmpheight, NULL, 10);
    header->RBG = (unsigned char) strtol(tmpRGB, NULL, 10);
    print_ppm_header(header);
    pixel_array = pixel_array_init(header->width, header->height);
    for (uint32_t i=0; i < (uint32_t) pixel_array->width*pixel_array->height; i++) {
        fread(pixel_array->pixels+i, sizeof(uint8_t), 1, image);
        fseek(image, 1, SEEK_CUR);
        fread(pixel_array->pixels+i+1, sizeof(uint8_t), 1, image);
        fseek(image, 1, SEEK_CUR);
        fread(pixel_array->pixels+i+2, sizeof(uint8_t), 1, image);
        fseek(image, 1, SEEK_CUR);
    }
    return pixel_array;
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
    ppm * pixel_array;
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

    pixel_array = load_ppm(image, &image_header);
    destroy_pixel_array(pixel_array);
/*
    if (!has_acceptable_size(argv[1])) {
        printf("FILE IS TOO LARGE !\n");
    }
    else {
        printf("FILE HAS VALID SIZE\n");
    }
*/
}