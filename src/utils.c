
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libintl.h>


#define COPYRIGHT_YEAR "2014"
#define COPYRIGHT_OWNER "seti volkylany"
#define COPYRIGHT_EMAIL "setivolkylany@gmail.com"


char *
join_paths(const char path1[], const char path2[])
{
    char *buffer;
    buffer = calloc(strlen(path1) + strlen(path2) + 1, sizeof(char));

    strcpy(buffer, path1);
    strcat(buffer, "/");
    strcat(buffer, path2);

    return buffer;
}


char *
str_replace(char str[], char old[], char new[])
{
    char *rest_str, *buffer;
    size_t len;
    size_t new_len = strlen(new);
    size_t old_len = strlen(old);
    size_t buffer_len;

    if (old_len == 0) {
        if (new_len == 0)
            return str;

        len = strlen(str) * (new_len + 1) + new_len;
        buffer = calloc(len, sizeof(char));

        while (*str != '\0') {
            strcat(buffer, new);

            buffer_len = strlen(buffer);

            buffer[buffer_len] = *str;
            buffer[buffer_len + 1] = '\0';

            ++str;
        }

        strcat(buffer, new);

    } else {

        buffer = malloc(sizeof(char));

        while ((rest_str = strstr(str, old)) != NULL) {

            len = strlen(str) - strlen(rest_str);
            buffer = realloc(buffer, strlen(buffer) + len + new_len);

            strncat(buffer, str, len);
            strcat(buffer, new);

            str += (len + old_len);
        }
        if (str != NULL) {
            len = strlen(buffer) + strlen(str);
            if (len == 0)
                ++len;
            buffer = realloc(buffer, len);
            strcat(buffer, str);
        }
    }

    return buffer;
}


int
copy_file_with_copyright(char path1[], char path2[], char file_to_copyright[])
{
    char chr, buffer[255], *p_buffer;
    FILE *stream_for_write, *stream_for_read, *stream_copyright;

    if ((stream_for_write = fopen(path1, "w")) == NULL) {
        fprintf(
            stderr, "%s: %s\n",
            gettext("Impossible to create a file"), path1
        );
        return -1;
    }

    if ((stream_for_read = fopen(path2, "r")) == NULL) {
        fprintf(
            stderr, "%s: %s\n",
            gettext("Impossible to read a file"), path2
        );
        return -1;
    }

    if (file_to_copyright != NULL) {
        stream_copyright = fopen(file_to_copyright, "r");

        fputs("/**\n", stream_for_write);
        while (fgets(buffer, sizeof(buffer), stream_copyright) != NULL) {

            p_buffer = str_replace(buffer, "{year}", COPYRIGHT_YEAR);
            p_buffer = str_replace(p_buffer, "{owner}", COPYRIGHT_OWNER);
            p_buffer = str_replace(p_buffer, "{email}", COPYRIGHT_EMAIL);

            fputs(" * ", stream_for_write);
            fputs(p_buffer, stream_for_write);
        }
        fputs(" */\n\n", stream_for_write);

        fclose(stream_copyright);
    }

    while ((chr = fgetc(stream_for_read)) != EOF) {
        fputc(chr, stream_for_write);
    }

    fclose(stream_for_write);
    fclose(stream_for_read);

    return 0;
}

#endif // __UTILS_H__
