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

	int result = pedalog_read_data(&devices[0], &data);

	if (result == PEDALOG_OK) {
		printf("volt: %f, iOut: %f, pO: %f, eO: %f, pMax: %f, pAve: %f, time: %ld\n", data.volt, data.iOut, data.pO, data.eO, data.pMax, data.pAve, data.time);
		return 0;	
	} else {
		return display_error(result);
	}
}
