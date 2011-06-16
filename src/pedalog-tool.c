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
 *( at your option) any later version.
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

int display_error(int error)
{
    char message[PEDALOG_MAX_ERROR_MESSAGE];
    pedalog_get_error_message(error, message);

    printf("%s\n", message);
	return error;
}

int main()
{
	pedalog_init();

	pedalog_data data;
	pedalog_device devices[PEDALOG_MAX_DEVICES];

	int device_count = pedalog_find_devices(devices);
	if (device_count < 1) {
		return display_error(PEDALOG_ERROR_NO_DEVICE_FOUND);
	}

    while (1) {
	int result = pedalog_read_data(&devices[0], &data);

	if (result == PEDALOG_OK) {
		printf("voltage: %f, current: %f, power: %f, energy: %f, max_power: %f, avg_power: %f, time: %ld\n",
            data.voltage, data.current, data.power, data.energy, data.max_power, data.avg_power, data.time);
	//	return 0;	
	} else {
		return display_error(result);
	}
    }
}
