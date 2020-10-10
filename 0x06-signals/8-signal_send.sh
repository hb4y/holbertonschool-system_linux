#!/bin/bash
# sends the signal SIGQUIT to a process
# Where <pid> is the PID of the process to send a signal to

if [ $# -ne 1 ]
then
  echo "Usage: $0 <pid>"
  exit 1
fi
kill -s SIGQUIT "$1"
