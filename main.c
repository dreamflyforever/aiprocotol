#include <stdio.h>
#include <string.h>

struct output_data {
	int len;
	int data[10];
};

extern char value[][100];
#define CMD_NUM 200
int asr_output(char *input, struct output_data *od);

int main()
{
	struct output_data od = {0};
	char *input = "sdf sfdf s fsdf close  sdfsf open  1 air_condition";
	asr_output(input, &od);

	while (od.len >= 0) {
		printf("od->data[%d]: %d\n", od.len, od.data[od.len]);
		od.len--;
	}
	return 0;
}

int asr_output(char *input, struct output_data *od)
{
	void *ret;
	int retval;
	od->len = 0;
	int i;
	for (i = 0; i < CMD_NUM; i++) {
		if (value[i] == NULL) {
			printf("i: %d return \n", i);
		}
		ret = strstr(input, value[i]);
		if (ret != NULL) {
			if (strlen(value[i]) == 0) {
				/*null string*/
			} else {
				printf("i:%d, %s\n", i, value[i]);
				od->data[od->len] = i;
				/*when end the while,
				it's len will add one*/
				od->len++;
			}
		}
	}
	od->len--;
	return retval;
}
