#include <iostream>
#include <string>
#include "regex.cpp"
#include "nfa.cpp"
#include <getopt.h>

int main(int argc, char *argv[])
{
    int opt;
    std::string regex_str;
    char *output_file = NULL;
    int mode = 0;

    while ((opt = getopt(argc, argv, "rto:")) != -1)
    {
        switch (opt)
        {
            case 'r':
                if (mode != 0)
                {
                    fprintf(stderr, "Error: Solo puedes usar una opcion de modo entre -r, -t o -o.\n");
                    return 1;
                }
                mode = 'r';
                break;
            case 't':
                if (mode != 0)
                {
                    fprintf(stderr, "Error: Solo puedes usar una opcion de modo entre -r, -t o -o.\n");
                    return 1;
                }
                mode = 't';
                break;
            case 'o':
                if (mode != 0)
                {
                    fprintf(stderr, "Error: Solo puedes usar una opcion de modo entre -r, -t o -o.\n");
                    return 1;
                }
                mode = 'o';
                output_file = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -r | -t | -o <archivo.nfa>\n", argv[0]);
                return 1;
        }
    }

    if (mode == 0)
    {
        fprintf(stderr, "Usage: %s -r | -t | -o <archivo.nfa>\n", argv[0]);
        return 1;
    }

    std::getline(std::cin, regex_str); 

    if (mode == 'r')
    {
        std::cout << sufija(explicita(regex_str)) << std::endl;
        return 0;
    }

    if (mode == 't')
    {
        //test_strings_stdin(regex_str);
        return 0;
    }

    return 0;
}