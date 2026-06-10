#include <argparse.h>
#include <stddef.h>
#include <stdio.h>

#include "config.h"

static const char *const usages[] = {
    PROJECT_NAME " [options]\n",
    nullptr,
};

static int version_callback(struct argparse *argparse, const struct argparse_option *options);
static int parse_arguments(int argc, char **argv, struct xsh_config *config);


int
main(int argc, char **argv)
{
    struct xsh_config cfg;

    argc = parse_arguments(argc, argv, &cfg);

    /* The commands are passed in from the command line. */
    if (argv[0] != nullptr)
    {
        /* Run commands, and then exit. */
        return 0;
    }

    return 0;
}


int
version_callback(struct argparse * /* unused */, const struct argparse_option * /* unused */)
{
    /* clang-format off */
    fputs(
        PROJECT_NAME " - " PROJECT_VERSION "\n\n"
        "Copyright (C) 2026 quantumvoid0, and the contributors of " PROJECT_NAME ".\n\n"
        "This program is free software: you can redistribute it and/or modify\n"
        "it under the terms of the GNU General Public License as published by\n"
        "the Free Software Foundation, either version 3 of the License, or (at\n"
        "your option) any later version.\n", stderr);
    /* clang-format on */
    return 0;
}


int
parse_arguments(int argc, char **argv, struct xsh_config *config)
{
    /* clang-format off */
    struct argparse_option options[] = {
OPT_GROUP("General:"),
    OPT_HELP(),
    OPT_BOOLEAN('V', "version", nullptr, "Print the version information", version_callback, 0, OPT_NONEG),
OPT_GROUP("Shell behaviour:"),
    OPT_STRING ('c', "command", &config->command, "Set the command to run by the shell", nullptr, 0, 0),
    OPT_BOOLEAN('v', "verbose", &config->verbose, nullptr,                               nullptr, 0, OPT_NONEG),
OPT_END()
        };
    /* clang-format on */

    struct argparse argparse;

    argparse_init(&argparse, options, usages, 0);
    argparse_describe(&argparse, "A terminal-centric command-line shell made in C23.", nullptr);

    return argparse_parse(&argparse, argc, (const char **)argv);
}
