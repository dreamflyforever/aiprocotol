src = ['main.c', 'table.c']
Program('main',
	src,
        LIBPATH = ['.'], 
        CCFLAGS = '-DHELLOSCONS',
	CFLAGS = ['-g', '-fcolor-diagnostics', '-Os', '-Wall'],
	CC = 'clang')
