#coding=utf-8

import re

f = open('test.cl', 'r')
start_from = "main"

for line in f.readlines():
	if re.match("#START_FROM_", line):
		start_from = line.split("_")[2]
		start_from = start_from.replace('\n', '')
		print start_from
	if line == "\n":
		continue
	if re.match(start_from, line):
		print line
