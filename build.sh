#!/bin/bash
gcc server.c -o server
gcc client.c -o client

gcc zserver.c -o zserver -lzmq
gcc zclient.c -o zclient -lzmq