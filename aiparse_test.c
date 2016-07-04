#include <stdio.h>
#include <aiparse.h>

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
