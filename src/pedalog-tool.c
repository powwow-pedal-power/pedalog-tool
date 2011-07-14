/*
 * pedalog-tool.c
 *
 * Copyright (c) 2011 Dan Haughey (http://www.powwow-pedal-power.org.uk)
 *
 * This file is part of pedalog-tool.
 *
 * pedalog-tool is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * pedalog-tool is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pedalog-tool.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <pedalog.h>
#include <argp.h>

const char *argp_program_version = "pedalog-tool 0.1";
const char *argp_program_bug_address = "<dan@powwow-pedal-power.org.uk>";

static char doc[] = "Pedalog Tool - a simple program for reading data from Pedalog devices";

/* The options we understand. */
static struct argp_option options[] = {
    {"comma",  'c', 0,      0,  "Produce comma-separated output" },
    {"serial",   's', "SERIAL", 0,
        "Read data from a Pedalog device with a specific serial number" },
    { 0 }
};

/* A description of the arguments we accept. */
static char args_doc[] = "";

/* Used by main to communicate with parse_opt. */
struct arguments
{
    int comma;
    int serial;
};

/* Parse a single option. */
static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
    /* Get the input argument from argp_parse, which we
       know is a pointer to our arguments structure. */
    struct arguments *arguments = state->input;

    switch (key)
    {
        case 'c':
            arguments->comma = 1;
            break;
        case 's':
            arguments->serial = atoi(arg);
            if (arguments->serial < 1) {
                argp_error(state, "option 'serial', if specified, must be a positive integer");
                return EINVAL;
            }

            break;

        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

int display_error(int error)
{
    char message[PEDALOG_MAX_ERROR_MESSAGE];
    pedalog_get_error_message(error, message);

    fprintf(stderr, "%s\n", message);
    return error;
}

int main(int argc, char **argv)
{
    struct arguments arguments;

    /* Default values. */
    arguments.comma = 0;
    arguments.serial = 0;

    /* Parse our arguments; every option seen by parse_opt will
       be reflected in arguments. */
    argp_parse (&argp, argc, argv, 0, 0, &arguments);

    pedalog_init();

    pedalog_data data;
    pedalog_device devices[PEDALOG_MAX_DEVICES];

    int device_count = pedalog_find_devices(devices);

    int i;
    for (i = 0; i < device_count; ++i) {
        if (arguments.serial == 0 || arguments.serial == devices[i].serial) {
            int result = pedalog_read_data(&devices[i], &data);

            if (result == PEDALOG_OK) {
                if (arguments.comma) {
                    printf("%d,%f,%f,%f,%f,%f,%f,%d\n",
                        devices[i].serial, data.voltage, data.current, data.power, data.energy, data.max_power, data.avg_power, data.time);
                } else {
                    printf("Serial: %d, voltage: %f, current: %f, power: %f, energy: %f, max_power: %f, avg_power: %f, time: %d\n",
                        devices[i].serial, data.voltage, data.current, data.power, data.energy, data.max_power, data.avg_power, data.time);
                }
                return 0;	
            } else {
                return display_error(result);
            }
        }
    }

    return display_error(PEDALOG_ERROR_NO_DEVICE_FOUND);
}
