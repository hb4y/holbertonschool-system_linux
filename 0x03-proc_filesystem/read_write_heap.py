#!/usr/bin/env python3
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
	sys.exit(1)

for line in men_map:
	info = line.split(' ')
	if info[-1][:-1] == "[heap]":
		if (info[1][0] != 'r') or (info[1][1] != 'w'):
			print("read/write denied")
			men_map.close()
			exit(0)
		addr = info[0].split("-")
		if len(addr) != 2:
			print("Error: Invalid addr")
			men_map.close()
			exit(1)
		addr_start = int(addr[0], 16)
		addr_end = int(addr[1], 16)

		try:
			mem_file = open("/proc/{}/mem".format(pid), 'rb+')
		except:
			print("Error: Can not open men file")
			men_map.close()
			exit(1)
  
		mem_file.seek(addr_start)
		heap = mem_file.read(addr_end - addr_start)

		try:
			i = heap.index(bytes(search_string, "ASCII"))
		except Exception:
			print("Can't find the string in the heap")
			men_map.close()
			mem_file.close()
			exit(0)

		mem_file.seek(addr_start + i)
		mem_file.write(bytes(sys.argv[3], "ASCII"))

		men_map.close()
		mem_file.close()
		break
