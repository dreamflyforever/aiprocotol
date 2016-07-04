#include <stdio.h>
#include <string.h>
#include <aiparse.h>

int asr_output(char *input, struct output_data *od)
{
	void *ret;
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
	return 0;
}
