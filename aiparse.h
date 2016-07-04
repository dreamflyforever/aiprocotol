struct output_data {
	int len;
	int data[10];
};
int asr_output(char *input, struct output_data *od);

extern char value[][100];
#define CMD_NUM 200
