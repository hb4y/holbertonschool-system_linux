#!/usr/bin/python3
"""
Write in the heap of a current process
"""

import sys

if len(sys.argv) != 4:
    print("Usage: read_write_heap.py <pid> <search_string> <replace_string>")
    sys.exit(1)

pid = int(sys.argv[1])
search_string = str(sys.argv[2])
replace_string = str(sys.argv[3])

if (pid <= 0) or (search_string == "") or (replace_string == ""):
    print("Error: bad argument format")
    sys.exit(1)

try:
    men_map = open('/proc/{}/maps'.format(pid), 'r')
except:
    print("Error: cannot open map")
    exit(1)

try:
    mem_file = open("/proc/{}/mem".format(pid), 'rb+')
except:
    print("Error: Can not open men file")
    men_map.close()
    exit(1)

for line in men_map:
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
        mem_file.write(bytes(sys.argv[3], "ASCII"))
        break

men_map.close()
mem_file.close()
