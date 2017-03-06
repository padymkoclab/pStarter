
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#include "cli.h"
// #include "c/main.h"
// #include "c++.h"
// #include "python.h"
// #include "java.h"
// #include "javascipt.h"


#define VERSION_FILE "./VERSION"
#define DEFAULT_VERSION "0.0.1"
#define TEMPLATE_DIR "templates"

#define KIND_PROJECT_NAME_MAX_LENGTH 30
#define KIND_PROJECT_NAME_ALLOW_EMPTY false
#define KIND_PROJECT_ALIAS_MAX_LENGTH 5
#define KIND_PROJECT_ALIAS_ALLOW_EMPTY false


struct KindProject {
    char* name;
    char alias[KIND_PROJECT_ALIAS_MAX_LENGTH];
    bool is_available;
    struct KindProject *next;
};


bool
_kind_project_validate_name(char name[])
{
    size_t name_len = strlen(name);

    if (KIND_PROJECT_NAME_ALLOW_EMPTY == false && name_len == 0) {
        fprintf(stderr, "%s\n", "Not allowed empty name");
        return false;
    }

    if (name_len > KIND_PROJECT_NAME_MAX_LENGTH) {
        fprintf(
            stderr, "%s %d): %s\n",
            "Too long name (max length", KIND_PROJECT_NAME_MAX_LENGTH, name
        );
        return false;
    }

    return true;
}


bool
_kind_project_validate_alias(char alias[])
{
    size_t alias_len = strlen(alias);

    if (KIND_PROJECT_ALIAS_ALLOW_EMPTY == false && alias_len == 0) {
        fprintf(stderr, "%s\n", "Not allowed empty alias");
        return false;
    }

    if (alias_len > KIND_PROJECT_ALIAS_MAX_LENGTH) {
        fprintf(
            stderr, "%s %d): %s\n",
            "Too long alias (max length", KIND_PROJECT_ALIAS_MAX_LENGTH, alias
        );
        return false;
    }
    return true;
}


struct KindProject *
_kind_project_check_unique_and_return_tail(struct KindProject *kind_project_head, char name[], char alias[])
{
    struct KindProject *tail;

    tail = NULL;

    while (kind_project_head != NULL) {
        tail = kind_project_head;
        if (strcmp(kind_project_head->name, name) == 0) {
            fprintf(stderr, "%s: %s\n", "Dublication name", name);
            return NULL;
        }
        if (strcmp(kind_project_head->alias, alias) == 0) {
            fprintf(stderr, "%s: %s\n", "Dublication alias", alias);
            return NULL;
        }
        kind_project_head = kind_project_head->next;
    }

    return tail;
}


struct KindProject *
kind_project_add(struct KindProject *kind_project_head, char name[], char alias[], const bool is_available)
{
    if (!_kind_project_validate_name(name))
        return NULL;

    if (!_kind_project_validate_alias(alias))
        return NULL;

    struct KindProject *new_kind_project, *tail;

    new_kind_project = malloc(sizeof(struct KindProject));

    if (new_kind_project == NULL) {
        fprintf(stderr,
            "%s(name=\"%s\", alias=\"%s\")\n", "Can`t create a new struct KindProject",
            name, alias);
        return NULL;
    }

    new_kind_project->name = name;
    strcpy(new_kind_project->alias, alias);
    new_kind_project->is_available = is_available;
    new_kind_project->next = NULL;

    if (kind_project_head != NULL) {
        if (!(tail = _kind_project_check_unique_and_return_tail(kind_project_head, name, alias)))
            return NULL;
        tail->next = new_kind_project;
    }

    return new_kind_project;
}


void
kind_project_print(struct KindProject *kind_project_head)
{
    char *line = "---------------------------------------------";
    int count_availabled = 0, count_no_availabled = 0;
    char *status_msg;

    puts(line);

    while (kind_project_head != NULL) {
        if (kind_project_head->is_available == true) {
            status_msg = "available";
            ++count_availabled;
        } else {
            status_msg = "not available";
            ++count_no_availabled;
        }

        printf("%-20s | %-5s | %s\n",
            kind_project_head->name, kind_project_head->alias, status_msg);

        kind_project_head = kind_project_head->next;
    }

    puts(line);
    printf("Total count availabled: %d\nTotal count no availabled: %d\n",
        count_availabled, count_no_availabled);
}


void
kind_project_free(struct KindProject *kind_project)
{
    if (kind_project != NULL) {
        struct KindProject *tail, *next;

        next = kind_project;
        while (next != NULL) {
            tail = next;
            free(tail);
            next = tail->next;
        }
    }
}


char *
get_current_version()
{
    FILE *stream;

    if ((stream = fopen(VERSION_FILE, "r")) == NULL) {
        fprintf(stderr, "%s: %s\n", strerror(errno), VERSION_FILE);
        return NULL;
    }

    char buffer[255];
    fread()

    return "";
}


int
main(const int argc, const char *argv[])
{
    struct KindProject *kind_project_head;

    kind_project_head = kind_project_add(NULL, "C", "c", true);
    kind_project_add(kind_project_head, "C header", ".h", false);
    kind_project_add(kind_project_head, "C++", "c++", false);
    kind_project_add(kind_project_head, "C++ header", ".hpp", false);
    kind_project_add(kind_project_head, "Python", "py", false);
    kind_project_add(kind_project_head, "Python module", ".py", false);
    kind_project_add(kind_project_head, "JavaScript", "js", false);
    kind_project_add(kind_project_head, "Java", "java", false);

    // kind_project_print(kind_project_head);

    if (argc == 1) {
        puts("Loading ...");
    } else {
        printf("Processing args: ");
        int i = 0;
        while (i < argc) {
            if (i + 1 == argc)
                printf("%s\n", argv[i]);
            else
                printf("%s ", argv[i]);
            ++i;
        }
    }

    char *version;
    if ((version = get_current_version()) == NULL)
        version = "undefined";

    puts(version);

    kind_project_free(kind_project_head);

    return EXIT_SUCCESS;
}
