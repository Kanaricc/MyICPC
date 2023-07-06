import os

with open('in.txt','w') as f:
    f.write("1 500000\n")
    f.write('a'*500000)
    f.write('\n')