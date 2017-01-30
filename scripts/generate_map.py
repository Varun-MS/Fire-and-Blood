import numpy as np
import csv
from random import randint

CURRENT_MAP_MATRIX = []

with open('./generated_map/NEW_MAP.map','rb') as csvfile:
	reader = csv.reader(csvfile,delimiter='	')
	temp = []
	for row in reader:
		for val in row:
			number = float(val)
			temp.append(int(number))
			
		CURRENT_MAP_MATRIX.append(temp)
		temp = []

MAP_OUT = [[13,11,11,11,11,11,11,11,11,12]]
for i in range(0, 8):
	temp = []
	temp.append(17)
	for j in range(0, 8):
		temp.append(CURRENT_MAP_MATRIX[i][j])
	temp.append(10)
	MAP_OUT.append(temp)
MAP_OUT.append([16,14,14,14,14,14,14,14,14,15])

#SUBSTITUTING 0s AND 1s WITH APPROPRIATE TILE VALUES

for i in range (0, 10):
	for j in range (0, 10):
		if MAP_OUT[i][j] == 0:
			MAP_OUT[i][j] = randint(0, 8)
			
		elif MAP_OUT[i][j] == 1:
			MAP_OUT[i][j] = 9

print MAP_OUT
print ''
print 'GENERATED COMPLETE MAP______'
print 'DELETING MAP METADATA______'
print 'SAVING MAP______'

w = csv.writer(open('./generated_map/NEW_MAP.map', 'w'), delimiter = '	')
for row in MAP_OUT:
	w.writerow(row)
print 'MAP SAVED______'
