import json
import requests

host = "http://202.38.93.241:10024"

base=['cos'];
zero=['1/x','exp','sqrt','log','1/x']
one=['sqrt','asinh','1/x','exp','sqrt','log','1/x','cosh']
div=['1/x','exp','x^2','log','1/x']

def dec2bin(x):
    x -= int(x)
    bins = []
    while x:
        x *= 2
        bins.append(1 if x>=1. else 0)
        x -= int(x)
    return bins

def int2bin(x):
    bins=[]
    while x:
        bins.append(int(x%2))
        x//=2
    bins.reverse()
    return bins
def solve(x):
    alllen=dec2bin(x)[:17]
    intlen=int2bin(x//1)

    base=['cos']
    for i in intlen[1:]:
        if i==0:
            base+=zero
        else: base+=one
    for i in alllen:
        if i==0:
            base+=zero
        else: base+=one
    
    for i in range(len(alllen)):
        base+=div
    print(base)
    return (','.join(base))

def fuck():
    with requests.session() as sess:
        r = sess.get(host + '/challenges')
        X = json.loads(r.text)["msg"]
        print(X)
        
        data = {
            "a1": solve(X[0]),
            "a2": solve(X[1]),
            "a3": solve(X[2])
        }
        r = sess.post(host + "/submit", data=data)
        resp = json.loads(r.text)
        print(resp["msg"])

fuck()