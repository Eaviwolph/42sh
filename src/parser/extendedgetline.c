#include "extendedgetline.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/macro.h"

#define safe_strlen(s) ((s) == NULL ? 0 : strlen(s))

static void append_str(char **source, char *add, int length)
{
    int source_length = safe_strlen(*source);
    safe_realloc(*source, *source, (source_length + length + 1) * sizeof(char));
    for (int i = source_length; i < source_length + length; i++)
        (*source)[i] = add[i - source_length];
    (*source)[source_length + length] = 0;
}

struct line *exgetline_start(int fd)
{
    struct line *new_buf = malloc(sizeof(struct line));
    if (!new_buf)
        exit(ERROR_ONMALLOC);
    new_buf->fd = fd;
    new_buf->datasize = 0;
    new_buf->start = 0;
    return new_buf;
}

void exgetline_end(struct line *buffer, int closefd)
{
    if (closefd < 3)
        close(buffer->fd);
    free(buffer);
}

char *getbufferdata(struct line *buffer)
{
    if (!buffer)
        return NULL;
    return buffer->data + buffer->start;
}

char *exgetline(struct line *buffer)
{
    char *final = NULL;
    // for all the buffer, read each group of char
    do
    {
        for (int i = buffer->start; i < buffer->datasize; i++)
        {
            if (buffer->data[i] == '\n') // each \n append the line to "string"
            {
                append_str(&final, getbufferdata(buffer),
                           i - buffer->start + 1);
                buffer->start = i + 1; // skip to next not read group of char
                return final;
            }
        }
        if (buffer->datasize - buffer->start > 0)
            append_str(&final, getbufferdata(buffer),
                       buffer->datasize - buffer->start);
        buffer->start = 0;
        buffer->datasize = read(buffer->fd, buffer->data, BUF_SIZE);
        if (buffer->datasize < 0)
            buffer->datasize = 0;
    } while (buffer->datasize > 0);
    return final;
}
