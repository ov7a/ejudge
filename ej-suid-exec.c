#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

#define EXEC_USER "ejexec"
#define EXEC_GROUP "ejexec"

extern char **environ;

static void
safe_chown(const char *full, int to_user_id, int to_group_id, int from_user_id)
{
    int fd = open(full, O_RDONLY | O_NOFOLLOW | O_NONBLOCK, 0);
    if (fd < 0) return;
    struct stat stb;
    if (fstat(fd, &stb) < 0) {
        close(fd);
        return;
    }
    if (S_ISDIR(stb.st_mode)) {
        if (stb.st_uid == from_user_id) {
            fchown(fd, to_user_id, to_group_id);
            //fchmod(fd, (stb.st_mode & 0777) | 0700);
        }
    } else {
        if (stb.st_uid == from_user_id) {
            fchown(fd, to_user_id, to_group_id);
        }
    }
    close(fd);
}

static void
chown_rec(const char *path, int user_id, int group_id, int from_user_id)
{
    DIR *d = opendir(path);
    if (!d) return;
    struct dirent *dd;
    int names_a = 32, names_u = 0;
    char **names_s = malloc(names_a * sizeof(names_s[0]));
    while ((dd = readdir(d))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) continue;
        if (names_u == names_a) {
            names_s = realloc(names_s, (names_a *= 2) * sizeof(names_s[0]));
        }
        names_s[names_u++] = strdup(dd->d_name);
    }
    closedir(d); d = NULL;
    for (int i = 0; i < names_u; ++i) {
        char full[PATH_MAX];
        snprintf(full, sizeof(full), "%s/%s", path, names_s[i]);
        struct stat stb;
        if (lstat(full, &stb) < 0) continue;
        if (S_ISDIR(stb.st_mode)) {
            chown_rec(full, user_id, group_id, from_user_id);
        }
        safe_chown(full, user_id, group_id, from_user_id);
    }
    for (int i = 0; i < names_u; ++i)
        free(names_s[i]);
    free(names_s);
}

int
main(int argc, char **argv)
{
    int chown_flag = 0;
    int start_ind = 1;
    if (argc <= 1) {
        fprintf(stderr, "%s: wrong number of arguments\n", argv[0]);
        abort();
    }
    if (argv[1][0] == '-') {
        if (argc <= 2) {
            fprintf(stderr, "%s: wrong number of arguments\n", argv[0]);
            abort();
        }
        start_ind = 2;
        const char *s = argv[1] + 1;
        for (; *s; ++s) {
            if (*s == 'd') {
                chown_flag = 1;
            }
        }
    }


    struct passwd *pwd = getpwnam(EXEC_USER);
    struct group *grp = getgrnam(EXEC_GROUP);
    endpwent();
    endgrent();
    if (!pwd) {
        fprintf(stderr, "%s: user '%s' does not exist\n", argv[0], EXEC_USER);
        abort();
    }
    if (pwd->pw_uid <= 0) {
        fprintf(stderr, "%s: user '%s' has uid %d\n", argv[0], EXEC_USER, pwd->pw_uid);
        abort();
    }
    if (!grp) {
        fprintf(stderr, "%s: group '%s' does not exist\n", argv[0], EXEC_GROUP);
        abort();
    }
    if (grp->gr_gid <= 0) {
        fprintf(stderr, "%s: group '%s' has gid %d\n", argv[0], EXEC_GROUP, grp->gr_gid);
        abort();
    }
    int my_uid = getuid();
    if (chown_flag) {
        safe_chown(".", pwd->pw_uid, grp->gr_gid, my_uid);
        chown_rec(".", pwd->pw_uid, grp->gr_gid, my_uid);
    }
    if (setgid(grp->gr_gid) < 0) {
        fprintf(stderr, "%s: setgid failed\n", argv[0]);
        abort();
    }
    if (setuid(pwd->pw_uid) < 0) {
        fprintf(stderr, "%s: setuid failed\n", argv[0]);
        abort();
    }
    execve(argv[start_ind], argv + start_ind, environ);
    fprintf(stderr, "%s: execve '%s' failed\n", argv[0], argv[start_ind]);
    abort();
}

/*
 * Local variables:
 *  c-basic-offset: 4
 * End:
 */
