env = Environment(
	CC = 'clang',
	CFLAGS = ['-g', '-fcolor-diagnostics', '-Wall', '-I.']
)

obj_aiparse = env.Object(['aiparse.c', 'table.c'])

test_aiparse = env.Program("test_aiparse", ['aiparse_test.c', obj_aiparse])
