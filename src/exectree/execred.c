#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../tools/tools.h"
#include "exectree.h"

int file_exists(char *name)
{
    FILE *file;

    if ((file = fopen(name, "r")))
    {
        fclose(file);
        return 1;
    }
    fclose(file);
    return 0;
}

// clobber is an option
int io(struct node_red n, struct shell *s, int clobber, int append)
{
    int ret;

    char *name = varstrrep(mystrdup(n.word[0]), s->var);
    if (clobber && file_exists(name) == 0)
    {
        warn("Can't override existing file");
        return 1;
    }

    int mode = append == 0 ? O_TRUNC : O_APPEND;
    ret = open(name, O_WRONLY | mode | O_CREAT,
               S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

    if (ret == -1)
    {
        warn("Error open");
        close(ret);
        return 1;
    }

    int r = dup2(ret, *n.fd);
    if (r == -1)
    {
        warn("%d", ret);
        close(ret);
        return 1;
    }
    exectree(n.mhs, s);

    close(ret);
    return 0;
}

int io_and(struct node_red n, struct shell *s)
{
    int d = atoi(varstrrep(mystrdup(n.word[0]), s->var));
    int r = dup2(d, *n.fd);
    if (r == -1)
    {
        warn("%d", d);
        return 1;
    }
    exectree(n.mhs, s);
    close(d);

    return 0;
}

void execred(struct node_red n, struct shell *s)
{
    int save = dup(*n.fd);
    if (!n.word)
        errx(2, "Parsing Error");
    switch (*n.type)
    {
    case R_LESS:; // <
        io(n, s, 0, 0);
        break;
    case R_LESSAND:; // <&
        io_and(n, s);
        break;
    case R_GREAT:; // >
        io(n, s, 0, 0);
        break;
    case R_GREATAND:; // >&
        io_and(n, s);
        break;
    case R_DGREAT:; // >>
        io(n, s, 0, 1);
        break;
    case R_LESSGREAT:; // <>
        io(n, s, 0, 0);
        break;
    case R_CLOBBER:; // >|
        io(n, s, 0, 0);
        break;
    case R_DLESS:; // <<
        warn("Here-document (<<) isn't implemented as said by the subject.");
        break;
    case R_DLESSDASH:; // <<-
        warn("Here-document (<<-) isn't implemented as said by the subject.");
        break;
    }
    dup2(save, *n.fd);
}