#ifndef EXTENDEDGETLINE_H
#define EXTENDEDGETLINE_H

#define BUF_SIZE 4096

struct line
{
    int fd;
    unsigned start;
    int datasize;
    char data[BUF_SIZE];
};

char *exgetline(struct line *buf);
void exgetline_end(struct line *buf, int closefd);
struct line *exgetline_start(int fd);

#endif
