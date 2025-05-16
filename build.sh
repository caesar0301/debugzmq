#!/bin/bash
gcc -std=c99 server.c -o server
gcc -std=c99 client.c -o client

gcc -std=c99 zserver.c -o zserver -lzmq
gcc -std=c99 zclient.c -o zclient -lzmq
