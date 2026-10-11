#define _DEFAULT_SOURCE
/*
 * OS Assignment 02 - Version 1.1.0
 * Based on the instructor's starter directory-listing program.
 * Adds the -l option for long listing.
 */

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <inttypes.h>

static int had_error = 0;

/* Convert file type and permission bits into text. */
static void permissions(mode_t mode, char text[11])
{
    strcpy(text, "----------");

    if (S_ISDIR(mode)) text[0] = 'd';
    else if (S_ISLNK(mode)) text[0] = 'l';
    else if (S_ISCHR(mode)) text[0] = 'c';
    else if (S_ISBLK(mode)) text[0] = 'b';
    else if (S_ISFIFO(mode)) text[0] = 'p';
    else if (S_ISSOCK(mode)) text[0] = 's';

    if (mode & S_IRUSR) text[1] = 'r';
    if (mode & S_IWUSR) text[2] = 'w';
    if (mode & S_IXUSR) text[3] = 'x';
    if (mode & S_IRGRP) text[4] = 'r';
    if (mode & S_IWGRP) text[5] = 'w';
    if (mode & S_IXGRP) text[6] = 'x';
    if (mode & S_IROTH) text[7] = 'r';
    if (mode & S_IWOTH) text[8] = 'w';
    if (mode & S_IXOTH) text[9] = 'x';

    if (mode & S_ISUID)
        text[3] = (mode & S_IXUSR) ? 's' : 'S';
    if (mode & S_ISGID)
        text[6] = (mode & S_IXGRP) ? 's' : 'S';
    if (mode & S_ISVTX)
        text[9] = (mode & S_IXOTH) ? 't' : 'T';
}

/* Display a symbolic link's destination. */
static void link_target(const char *path)
{
    size_t capacity = 128;

    for (;;) {
        char *buffer = malloc(capacity + 1);
        if (buffer == NULL) {
            perror("malloc");
            had_error = 1;
            return;
        }

        ssize_t length = readlink(path, buffer, capacity);
        if (length < 0) {
            perror(path);
            free(buffer);
            had_error = 1;
            return;
        }

        if ((size_t)length < capacity) {
            buffer[length] = '\0';
            printf(" -> %s", buffer);
            free(buffer);
            return;
        }

        free(buffer);
        if (capacity > SIZE_MAX / 2 - 1) {
            fprintf(stderr, "Link target is too long: %s\n", path);
            had_error = 1;
            return;
        }
        capacity *= 2;
    }
}

/* Print metadata for one directory entry. */
static void long_entry(const char *directory, const char *name)
{
    size_t length = strlen(directory) + strlen(name) + 2;
    char *path = malloc(length);

    if (path == NULL) {
        perror("malloc");
        had_error = 1;
        return;
    }

    snprintf(path, length, "%s/%s", directory, name);

    struct stat info;
    if (lstat(path, &info) == -1) {
        perror(path);
        free(path);
        had_error = 1;
        return;
    }

    char mode[11];
    char date[64] = "?";
    char uid[32];
    char gid[32];

    permissions(info.st_mode, mode);

    snprintf(uid, sizeof(uid), "%ju", (uintmax_t)info.st_uid);
    snprintf(gid, sizeof(gid), "%ju", (uintmax_t)info.st_gid);

    struct passwd *owner = getpwuid(info.st_uid);
    struct group *group = getgrgid(info.st_gid);
    const char *modified = ctime(&info.st_mtime);
    if (modified != NULL)
        snprintf(date, sizeof(date), "%.12s", modified + 4);

    printf("%s %3ju %-12s %-12s %10jd %s %s",
           mode,
           (uintmax_t)info.st_nlink,
           owner != NULL ? owner->pw_name : uid,
           group != NULL ? group->gr_name : gid,
           (intmax_t)info.st_size,
           date,
           name);

    if (S_ISLNK(info.st_mode))
        link_target(path);

    putchar('\n');
    free(path);
}

/* Read a directory and skip hidden entries. */
static void do_ls(const char *directory, int long_format)
{
    DIR *dp = opendir(directory);
    if (dp == NULL) {
        perror(directory);
        had_error = 1;
        return;
    }

    for (;;) {
        errno = 0;
        struct dirent *entry = readdir(dp);

        if (entry == NULL) {
            if (errno != 0) {
                perror("readdir");
                had_error = 1;
            }
            break;
        }

        if (entry->d_name[0] == '.')
            continue;

        if (long_format)
            long_entry(directory, entry->d_name);
        else
            printf("%s\n", entry->d_name);
    }

    if (closedir(dp) == -1) {
        perror("closedir");
        had_error = 1;
    }
}

int main(int argc, char *argv[])
{
    int long_format = 0;
    int option;

    while ((option = getopt(argc, argv, "l")) != -1) {
        if (option == 'l')
            long_format = 1;
        else {
            fprintf(stderr, "Usage: %s [-l] [directory ...]\n",
                    argv[0]);
            return EXIT_FAILURE;
        }
    }

    if (optind == argc) {
        do_ls(".", long_format);
    } else {
        for (int i = optind; i < argc; i++) {
            if (argc - optind > 1)
                printf("%s:\n", argv[i]);

            do_ls(argv[i], long_format);

            if (i + 1 < argc)
                putchar('\n');
        }
    }

    return had_error ? EXIT_FAILURE : EXIT_SUCCESS;
}
