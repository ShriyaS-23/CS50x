import csv
import sys

if len(sys.argv) < 3 or len(sys.argv) > 3:
    print('USAGE: python dna.py <database>.csv <sequence>.csv')
    sys.exit(1)

data = []

with open(sys.argv[1],'r') as database:
    dataReader = csv.DictReader(database)
    for row in dataReader:
        data.append(row)

with open(sys.argv[2], 'r') as sequence:
    seqReader = csv.reader(sequence)
    for row in seqReader:
        seq = row[0]


dnaSTR = set()

for item in data:
    for key in item.keys():
        if key != 'name':
            dnaSTR.add(key)

seqAns = {'name':0}


for STR in dnaSTR:
    STRname = ''
    STRcount = 0
    i = 0
    while i < len(seq):
        maxSTR = 0
        if STR == seq[i:(i+len(STR))]:
            STRname = STR
            STRcount += 1
        if maxSTR < STRcount:
            maxSTR = STRcount
        i += 1
    seqAns.update({STR: maxSTR})

for item in data:
    count = 0
    for DNA,key in zip(seqAns,item):
        if item[DNA] == str(seqAns[DNA]):
            count += 1
    if count == len(seqAns)-1:
        print(item['name'])
        sys.exit(0)

print('No Match')
sys.exit(0)