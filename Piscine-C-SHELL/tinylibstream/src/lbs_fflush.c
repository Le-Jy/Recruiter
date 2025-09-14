#include <stdio.h>
#include <stdlib.h>

#include "../include/libstream.h"

int lbs_fflush(struct stream *stream)
{
    if (!stream)
    {
        stream->error = 1;
        return LBS_EOF;
    }
    ssize_t w = 0;
    size_t r = 0;
    int fd = stream->fd;
    if (stream->io_operation == STREAM_WRITING)
    {
        while (r < stream->buffered_size
               && (w = write(fd, stream->buffer, stream->buffered_size)) > 0)
            r += w;
        if (w == -1)
        {
            stream->error = 1;
            return LBS_EOF;
        }
        stream->buffered_size = 0;
    }
    else
    {
        lseek(stream->fd, -stream_remaining_buffered(stream), SEEK_CUR);
    }
    stream->buffered_size = 0;
    stream->already_read = 0;

    return 0;
}

int lbs_fclose(struct stream *file)
{
    int res = lbs_fflush(file);
    int res_c = close(file->fd);
    free(file);
    if (res < 0 || res_c < 0)
        return LBS_EOF;
    return res;
}

int lbs_fputc(int c, struct stream *stream)
{
    if (!stream_writable(stream))
    {
        stream->error = 1;
        return LBS_EOF;
    }
    if (stream->io_operation == STREAM_READING)
        lbs_fflush(stream);
    stream->io_operation = STREAM_WRITING;
    if (stream->buffered_size == LBS_BUFFER_SIZE)
    {
        if (lbs_fflush(stream) == -1)
        {
            stream->error = 1;
            return LBS_EOF;
        }
    }
    if (stream->buffering_mode == STREAM_UNBUFFERED)
    {
        stream->buffer[0] = c;
        stream->buffered_size++;

        if (lbs_fflush(stream) == -1)
        {
            stream->error = 1;
            return LBS_EOF;
        }

        return c;
    }
    else if (stream->buffering_mode == STREAM_LINE_BUFFERED)
    {
        if (c == '\n')
        {
            if (lbs_fflush(stream) == -1)
            {
                stream->error = 1;
                return LBS_EOF;
            }
        }
    }
    stream->buffer[stream->buffered_size] = c;
    stream->buffered_size++;

    return c;
}

int lbs_fgetc(struct stream *stream)
{
    if (!stream_readable(stream))
    {
        stream->error = 1;
        return LBS_EOF;
    }
    if (stream->io_operation == STREAM_WRITING)
        lbs_fflush(stream);
    stream->io_operation = STREAM_READING;
    if (!stream_remaining_buffered(stream))
    {
        lbs_fflush(stream);
    }
    if (!stream->buffered_size)
    {
        stream->already_read = 0;
        stream->buffered_size =
            read(stream->fd, stream->buffer, LBS_BUFFER_SIZE);
    }
    if (stream->buffered_size == 0)
        return LBS_EOF;
    unsigned char c = stream->buffer[stream->already_read];
    stream->already_read++;
    return c;
}
