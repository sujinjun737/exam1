#!/bin/bash


start() {
    echo "输入目录地址"
    read d 
    echo "输入文件名"
    read f
    ./program_a -d "$d" -f "$f" & 
    ./program_b &
    }


stop() {
    pkill -f program_a
    pkill -f program_b
    rm -f /tmp/pipe
    }

case "$1" in
    start)
        start
        ;;
    stop)
        stop
        ;;
    restart)
        stop
        start
        ;;
    *)
        echo "Usage: $0 {start|stop|restart}"
        exit 1
esac
exit 0
