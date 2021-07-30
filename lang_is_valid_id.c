// TODO Convert error messages to use err_exit()
// TODO Write unit tests
// TODO Find an efficient algorithm? Is it worth it for the 26 possible
// languages?

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LANG_MIN_LEN 4
#define LANG_CODES "deensvisrurofritskptnlhufilaesbghrnocsdatrpleosrelbs"
#define LANG_CODES_LEN 52

bool is_lang_valid(const char * lang)
{
    // Parameter check
    if (lang == NULL)
    {
        fprintf(stderr, "Bad pointer passed to %s\n", __func__);
        return false;
    }
    else if (strlen(lang) != LANG_MIN_LEN)
    {
        fprintf(stderr, "language code is not the correct length\n");
        return false;
    }

    bool lang_1 = false;

    // Check first language code
    for (int i = 0; i < LANG_CODES_LEN; i += 2)
    {
        if ((lang[0] == LANG_CODES[i]) &&
            (lang[1] == LANG_CODES[i + 1]))
        {
            lang_1 = true;
            break;
        }
    }

    // Exit if not found
    if (lang_1 == false)
    {
        fprintf(stderr, "First language code not supported\n");
        return false;
    }

    // Check for second language code
    for (int i = 0; i < LANG_CODES_LEN; i += 2)
    {
        if ((lang[2] == LANG_CODES[i]) &&
            (lang[3] == LANG_CODES[i + 1]))
        {
            return true;
        }
    }

    fprintf(stderr, "Second language code not supported\n");
    return false;
}

int main(void)
{
    // Checking parameter checks
    fprintf(stderr, "0: %d\n", is_lang_valid(NULL));
    fprintf(stderr, "1: %d\n", is_lang_valid("dee"));
    fprintf(stderr, "2: %d\n", is_lang_valid("deenf"));

    // Check first and second language are valid
    fprintf(stderr, "3: %d\n", is_lang_valid("eebs"));
    fprintf(stderr, "4: %d\n", is_lang_valid("deee"));
    fprintf(stderr, "5: %d\n", is_lang_valid("fibs"));

	return 0;
}
