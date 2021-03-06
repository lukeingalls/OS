#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVICE "/dev/pa2_character_driver"
#define BUFFER_SIZE 1024

void menu(char*);

int main() {
	char iterate = 1;
	char input;
	int length, whence, offset;
	char *buffer;	
	int check;
	int file = open(DEVICE, O_RDWR);
	if (file < 0) {
		printf("File did not open! Make sure mknod and insmod have both been done!\n");
		exit(0);
	}
	while (iterate) {
		menu(&input);
		switch(input) {
			case 'R':
			case 'r':
				printf("Enter the number of bytes you want to read: ");
				scanf(" %d", &length);
				buffer = (char*) malloc(length);
				memset(buffer, 0, length);
				check = read(file, buffer, length);
				if (check < length) {
					printf("Bytes exceed the buffer size. Nothing read.");
				}
				printf("Data read from the device:\n%s\n", buffer);
				free(buffer);
				break;
			case 'W':
			case 'w':
				printf("Enter data you want to write to the device: ");
				buffer = (char*) malloc(BUFFER_SIZE);
				memset(buffer, 0, BUFFER_SIZE);
				scanf(" %s", buffer);
				check = write(file, buffer, strlen(buffer));
				if (check < length) {
					printf("Bytes exceed the buffer size. Nothing read.");
				}
				free(buffer);
				break;
			case 'S':
			case 's':
				printf("Enter an offset value: ");
				scanf(" %d", &offset);
				printf("Enter a value for whence. The options are\n SEEK SET (0) Which will assign the offset to the value given.\n SEEK CUR (1) Which will add the given offset to the location of the current offset.\n SEEK END (2) Which will subtract the offset from the end of the buffer. Choice: ");
				scanf(" %d", &whence);
				check = lseek(file, offset, whence);
				if (check < 0) {
					printf("The cursor position specified was out of range! No change.\n");
				} else {
					printf("The cursor is now at position %d\n", check);
				}
				break;
			case 'E':
			case 'e':
				iterate = 0;
				break;
		}
	}
	close(file);
	return 0;
}

void menu(char *input) {
	printf("Please select one of the following commands:\n");
	printf("\t1. Press r to read from the device\n");
	printf("\t2. Press w to write to the device\n");
	printf("\t3. Press s to seek into the device\n");
	printf("\t4. Press e to exit from the device\n");
	printf("\t5. Press anything else to keep reading or writing from the device\n");
	printf("Enter Command:\t");
	scanf(" %c", input);
}

