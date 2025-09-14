#include <stdlib.h>
#include <string.h>

#include "../include/libstream.h"

struct stream *lbs_fopen(const char *path, const char *mode)
{
    struct stream *res = malloc(sizeof(struct stream));
    if (!res)
        return NULL;
    if (!strcmp(mode, "r"))
        res->flags = O_RDONLY;
    else if (!strcmp(mode, "r+"))
        res->flags = O_RDWR;
    else if (!strcmp(mode, "w"))
        res->flags = O_WRONLY + O_CREAT + O_TRUNC;
    else if (!strcmp(mode, "w+"))
        res->flags = O_RDWR + O_CREAT + O_TRUNC;
    else
    {
        free(res);
        return NULL;
    }
    res->fd = open(path, res->flags);
    if (res->fd < 0)
    {
        free(res);
        return NULL;
    }
    res->io_operation = STREAM_WRITING;
    res->error = 0;
    if (isatty(res->fd))
        res->buffering_mode = STREAM_LINE_BUFFERED;
    else
        res->buffering_mode = STREAM_BUFFERED;
    res->buffered_size = 0;
    res->already_read = 0;
    return res;
}

struct stream *lbs_fdopen(int fd, const char *mode)
{
    if (fd < 0)
        return NULL;
    struct stream *res = malloc(sizeof(struct stream));
    if (!res)
        return NULL;
    if (!strcmp(mode, "r"))
        res->flags = O_RDONLY;
    else if (!strcmp(mode, "r+"))
        res->flags = O_RDWR;
    else if (!strcmp(mode, "w"))
        res->flags = O_WRONLY + O_CREAT + O_TRUNC;
    else if (!strcmp(mode, "w+"))
        res->flags = O_RDWR + O_CREAT + O_TRUNC;
    else
    {
        free(res);
        return NULL;
    }
    res->io_operation = STREAM_WRITING;
    res->fd = fd;
    res->error = 0;
    if (isatty(fd))
        res->buffering_mode = STREAM_LINE_BUFFERED;
    else
        res->buffering_mode = STREAM_BUFFERED;
    res->buffered_size = 0;
    res->already_read = 0;
    return res;
}
