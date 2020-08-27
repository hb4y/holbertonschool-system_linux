#!/usr/bin/python3
"""
Write in the heap of a current process
"""
import sys


def write_heap():
    """
    Script that over write the heap
    """
    if len(sys.argv) != 4:
        e = "Usage: read_write_heap.py pid search_string replace_string"
        print(e)
        exit(1)

    pid = sys.argv[1]
    search_string = str(sys.argv[2])
    replace_string = str(sys.argv[3])

    try:
        men_map = open('/proc/{}/maps'.format(pid), 'r')
    except Exception as e:
        print(e)
        exit(1)

    try:
        mem_file = open("/proc/{}/mem".format(pid), 'rb+')
    except Exception as e:
        print(e)
        men_map.close()
        exit(1)

    for line in men_map.readlines():
        info = line.split()
        if "[heap]" in info:
            addr = info[0].split("-")
            addr_start = int(addr[0], 16)
            addr_end = int(addr[1], 16)
            mem_file.seek(addr_start)
            heap = mem_file.read(addr_end - addr_start)
            i = heap.find(str.encode(search_string))

            if i == -1:
                break

            mem_file.seek(addr_start + i)
            mem_file.write(str.encode(sys.argv[3]) + b'\x00')
            break

    men_map.close()
    mem_file.close()

if __name__ == '__main__':
    write_heap()
