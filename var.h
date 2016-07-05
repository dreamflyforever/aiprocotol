/*AIprotoco version*/
#define VERSION "1.0.0"

/*if ASR_NUM > 2000, function may be stackoverflow*/
#define ASR_NUM 1000

/*number of user callback*/
#define CMD_NUM 0xf

/*user's number parameter, for example one number kitchen two nunber led
parse: "num0": "1", "num1":"2", max: 10*/
#define PARA_NUM 5

/*number of user callback parameter, attention: PARA_NUM <= USER_ARGC*/
#define USER_ARGC 4

#define OUT
#define IN
#define u8 unsigned char
#define u32 unsigned int
