
#ifndef __UTILS_H__
#define __UTILS_H__


char* join_paths(const char path1[], const char path2[]);
char* str_replace(char str[], char old[], char new[]);
int copy_file_with_copyright(char path1[], char path2[], char file_to_copyright[]);


#endif // __UTILS_H__
