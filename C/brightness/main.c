#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SYS_FILE_PATH "/sys/class/backlight/amdgpu_bl1/brightness"
#define HOME_FILE_PATH "/home/dio/.config/i3status_brightness/brightness"


int
read_term_arg(int argv, char * argc[], void ** return_arg);

void
invalid_term_arg(int argv, char * argc[]);

int
read_file(const char * PATH);

int
write_file(const char * PATH, const int new_brightness_value);


typedef struct Arg {
	char * short_name;
	char * long_name;
	int arg_code;
	bool return_value;
} Arg;

// ACCEPT ONLY ONE ARGUMENT THESE
// -i or --info: return the current brightness value
// -s or --set: set an new brightness value
#define INFO 0
#define SET 1
Arg args_arr[] = {
	{	"-i", 	"--info", INFO, false	},
	{	"-s", 	"--set", 	SET, 	true	}
};

const int ARG_ARR_SIZE = sizeof(args_arr) / sizeof(Arg);


int
read_term_arg(int argv, char * argc[], void ** return_arg) {
	for (int i = 1; i < argv; i++) {
		for (int j = 0; j < ARG_ARR_SIZE; j++) {
				if (!strcmp(argc[i], args_arr[j].short_name) || !strcmp(argc[i], args_arr[j].long_name)) {
					if (args_arr[j].return_value == true) {
					*return_arg = argc[i + 1];
				}

				return args_arr[j].arg_code;
			}
		}
	}

	return -1;
}

void
invalid_term_arg(int argv, char * argc[]) {
	int j = 0;
	for (int i = 1; i < argv; i++) {
		while (true) {
			if (j == ARG_ARR_SIZE	) {
				fprintf(stderr, "invalid argument: %s\n", argc[i]);
				break;
			} else if (!strcmp(argc[i], args_arr[j].short_name) || !strcmp(argc[i], args_arr[j].long_name)) {
				break;
			} else {
				j++;
			}
		}

		j = 0;
	}
}

int
read_file(const char * PATH) {
	FILE * sys_file = fopen(PATH, "r");
	if (!sys_file) {
		fprintf(stderr, "error while opening %s file in read mode.", PATH);
		return -1;
	} else {
		int current_value = 0;
		fscanf(sys_file, "%d", &current_value);
		fclose(sys_file);
		return current_value;
	}
}

int
write_file(const char * PATH, const int new_value) {
	FILE * sys_file = fopen(PATH, "w+"); // do not create the file
	if (!sys_file) {
		 fprintf(stderr, "error while opening %s file in read mode.\n", PATH);
		 return 0;
	} else {
		fprintf(stdout, "%d", new_value);
		fclose(sys_file);
		return new_value;
	}
}

int
main(int argv, char * argc[]) {

	void * arg = NULL;
	switch (read_term_arg(argv, argc, &arg)) {
		case INFO:
			printf("current brightness: %d\n", read_file(SYS_FILE_PATH));
			break;

		case SET:
			if (write_file(SYS_FILE_PATH, atol((char *)arg)))
				write_file(HOME_FILE_PATH, atol((char *)arg));
			break;

		default:
			invalid_term_arg(argv, argc);
			break;
	}

	return 0;
}
