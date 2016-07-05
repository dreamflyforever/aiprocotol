env = Environment(
	CC = 'clang',
	CFLAGS = ['-g', '-fcolor-diagnostics', '-Wall', '-I.', '-I socket']
)

obj_aiparse = env.Object(['aiparse.c', 'table.c'])

test_aiparse = env.Program("test_aiparse", ['aiparse_test.c', obj_aiparse])

obj_aiprotocol = env.Object(['aiprotocol.c'])

obj_client = env.Object(['socket/client.c'])
test_airpotcol = env.Program("test_aiprotocol_client", ['aiprotocol_test_client.c', obj_aiprotocol, obj_client])

obj_server = env.Object(['socket/server.c'])
test_airpotcol = env.Program("test_aiprotocol_server", ['aiprotocol_test_server.c', obj_aiprotocol, obj_server])
