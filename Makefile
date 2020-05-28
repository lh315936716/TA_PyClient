all::
	cc -g  _insertPy.c  -I/usr/include/python3.6m/  
	-L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu -lpython3.6m
