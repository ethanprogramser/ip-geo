depend: cjson, curl

compile : gcc -o e c.c `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` -lcurl -lcjson
