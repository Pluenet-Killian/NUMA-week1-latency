
#include "main.h"

void free_names(char **dir_names)
{
    for (int i = 0; dir_names[i] != NULL; ++i)
        free(dir_names[i]);
    free(dir_names);
}

int main(int argc, char *argv[])
{
    struct dirent *pDirent;
    DIR *pDir;
    char **dir_names = malloc(sizeof(char *) * 1024);

    pDir = opendir("/sys/devices/system/node/");
    if (pDir == NULL) {
        printf("Command open dir");
        return 1;
    }
    int i = 0;
    while ((pDirent = readdir(pDir)) != NULL) {
        dir_names[i] = malloc(sizeof(char) * strlen(pDirent->d_name) + 1);
        // dir_names[i] = pDirent->d_name;
        strcpy(dir_names[i], pDirent->d_name);
        i++;
    }
    closedir(pDir);
    dir_names[i] = NULL;
    nodes(dir_names);
    latency(0, 0);
    latency(1, 0);
    latency(0, 2);
    latency(1, 2);
    free_names(dir_names);
    return 0;
}
