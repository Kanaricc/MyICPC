fline=input()
ilen=int(fline.split(' ')[0])

isum=int(fline.split(' ')[1])
inp=[]
for i in range(0,ilen):
    li=input();
    name=li.split(' ')[0]
    pri=int(li.split(' ')[1])
    inp.append((pri,name))
inp.sort()
temp=ilen-1
ok=False
ans=[]
for i in range(1,ilen+1):
    if isum-inp[ilen-i][0]<0:
        #print("jump",ilen-i)
        continue
    isum-=inp[ilen-i][0]
    ans.append(inp[ilen-i][1])
    temp-=1
    if isum==0:
        ok=True
        break
if(ok):
    print(len(ans))
    for i in ans:
        print(i)
else:
    print(0)
