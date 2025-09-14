#include <time.h>

#include "expansion/expansion.h"
#include "io/io.h"
#include "main_loop.h"
#include "utils/hash_map_funcdec/hash_map_funcdec.h"

extern struct hash_map_funcdec *hash_map_funcdec;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    FILE *stream_fd = get_input_stream(argc, argv);
    if (!stream_fd)
    {
        return 2;
    }

    init_expansion();
    set_specials_variables();

    struct lexer *lexer = new_lexer(stream_fd);

    int return_value = parse_execute_loop(lexer);

    free_lexer(lexer);
    fclose(stream_fd);
    free_expansion();
    hash_map_funcdec_free(hash_map_funcdec);

    return return_value;
}
