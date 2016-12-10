import numpy as np
import csv
import os
import random

def randomTileClass(bias):					#FUNCTION TO DETERMINE IF A BLOCK SHOULD BE TILED, OR NOT
	r = random.uniform(0, 1)				#bias IS THE PROBABILITY OF A TILE OCCURING IN A BLOCK
	#print r
	if (r <= bias):
		return 0
		
	else:
		return 1
	
#####################################

	
def findLeftNeighbour(current_row, current_col):
	global NEW_MAP
	global ROWS_LIMIT
	global COLUMNS_LIMIT
	leftNeighbour = -1
	
	if (current_col-1) >= 0:
		leftNeighbour = (current_row, current_col-1)
		
	return leftNeighbour
#####################################
MAPS_PATH = './Maps/'						#PATH TO MAPS DIRECTORY
MAPS = os.listdir(MAPS_PATH)				#LIST CONTAINING NAMES OF EACH MAP
NUMBER_OF_MAPS = len(MAPS)					#FINDING THE NUMBER OF MAPS, TO EVALUATE THE PROBABILITY OF THE OCCURANCE OF A FLOOR TILE ON EACH BLOCK
START_I = 0									#i-INDEX FROM WHICH MAP GENERATION, AFTER THE PLACEMENT OF THE FIRST TILE BEGINS
START_J = 0									#j-INDEX FROM WHICH MAP GENERATION, AFTER THE PLACEMENT OF THE FIRST TILE BEGINS
ROWS_LIMIT = 8
COLUMNS_LIMIT = 8
#####################################

ACCUMULATOR = []							#MATRIX TO STORE THE PROBABILITIES OF THE OCCURANCE OF A FLOOR TILE ON EACH BLOCK
NEW_MAP = []								#MATRIX TO STORE STATS OF THE GENERATED MAP

#INITIALIZING ACCUMULATOR AND NEW_MAP
print 'INITIALIZING NEW MAP______'

for i in range(0, ROWS_LIMIT):
	temp1 = []
	temp2 = []
	for j in range(0, COLUMNS_LIMIT):
		temp1.append(0.)
		temp2.append(999)
	ACCUMULATOR.append(temp1)
	NEW_MAP.append(temp2)
	
ACCUMULATOR = np.matrix(ACCUMULATOR)
NEW_MAP = np.matrix(NEW_MAP)

#####################################

print 'ANALYZING MAPS______'
for val in MAPS:

	current_map = MAPS_PATH+val				#PATH TO CURRENT MAP
	CURRENT_MAP_MATRIX = []					#TO STORE STATS OF THE CURRENT MAP: WHETHER A FLOOR TILE OCCURS ON A BLOCK, OR NOT
	
	#READING THE CURRENT MAP FILE
	with open(current_map,'rb') as csvfile:
		reader = csv.reader(csvfile,delimiter='	')
		temp = []
		for row in reader:
			for val in row:
				temp.append(float(val))
			
			CURRENT_MAP_MATRIX.append(temp)
			temp = []
	
	CURRENT_MAP_MATRIX = np.matrix(CURRENT_MAP_MATRIX)
	CURRENT_MAP_MATRIX = CURRENT_MAP_MATRIX[1:-1,1:-1]

	#UPDATING THE ACCUMULATOR
	for i in range (0, ROWS_LIMIT):
		for j in range(0, COLUMNS_LIMIT):
			if (CURRENT_MAP_MATRIX[i, j] > 6):
				ACCUMULATOR[i, j] += 1

ACCUMULATOR/=NUMBER_OF_MAPS					#FINDING THE PROBABILITY OF A FLOOR TILE ON EACH BLOCK

#print(ACCUMULATOR)
print 'ACCUMULATED OBJECT DISTRIBUTION STATS______'

i = 0
j = 0
while not (0 in NEW_MAP):
	#print('Hi')
	NEW_MAP[i, j] = randomTileClass(ACCUMULATOR[i, j])
	
	if NEW_MAP[i, j] != 0:
		if (i == ROWS_LIMIT - 1) and (j == COLUMNS_LIMIT - 1):
			print('MAP FAILURE______')
			break
			
		elif (i < ROWS_LIMIT) and (j < COLUMNS_LIMIT):
			
			if i == ROWS_LIMIT:
				i = 0
				j += 1
			
			else:
				i += 1
	else:
		START_I = i
		START_J = j
	#print (i, j)

#print(START_I, START_J)

for j in range(0, ROWS_LIMIT):
	for i in range(0, ROWS_LIMIT - 1):
		
		currentBlockValue = NEW_MAP[i, j]
		#print('LALALA')
		#print(currentBlockValue)

		leftNeighbour = (findLeftNeighbour(i,j))
		leftNeighbourValue = -1
		neighbourValues = []
		
		"""
		print('rows limit')
		print(ROWS_LIMIT)
		print('i')
		print(i)
		print('j')
		print(j)
		print('this value')
		print(currentBlockValue)
		print(i,j)
		"""
		
		if leftNeighbour != -1:
			a,b = leftNeighbour
			leftNeighbourValue = NEW_MAP[a, b]
		
		while True:
			if (i < ROWS_LIMIT - 1):
				downNeighbourValue = randomTileClass(ACCUMULATOR[i, j])
			else:
				downNeighbourValue = -1
			
			
			if (j < COLUMNS_LIMIT - 1):
				rightNeighbourValue = randomTileClass(ACCUMULATOR[i, j])
			else:
				rightNeighbourValue = -1
			
			
			if currentBlockValue == 0:
				if (leftNeighbourValue == 0) or (downNeighbourValue == 0):
					#print('REACHED')
					break
			
			break
		
		if (rightNeighbourValue != -1):
			NEW_MAP[i, j+1] = rightNeighbourValue
		
		
		if (downNeighbourValue != -1):
			NEW_MAP[i+1, j] = downNeighbourValue
		"""
		print('THIS')
		print(i, j)
		print(neighbourValues)
		"""
#print(NEW_MAP)

#####################################

print 'SAVING MAP METADATA______'
np.savetxt("NEW_MAP.map", NEW_MAP, delimiter = '	')


#print(MAP_OUT)
