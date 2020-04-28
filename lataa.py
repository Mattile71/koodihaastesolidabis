import json
f = open("reittiopas.json","r")
d = json.load(f)
print ("moi")
for a in d:
    print(a)
f.close()


f= open("ulos.txt","w+")
pitpysakit = len(d['pysakit'])
f.write("%d\n" % pitpysakit)
for i in d['pysakit']:
    f.write(i+"\n")

pittiet = len(d['tiet'])
f.write("%d\n" % pittiet)
for i in d['tiet']:
    f.write(i['mista']+"\n")
    f.write(i['mihin']+"\n")
    f.write("%d"%i['kesto']+"\n")
    
pitlinjastot = len(d['linjastot'])
f.write("%d\n" % pitlinjastot)
for i in d['linjastot']:
    pit = len(d['linjastot'][i])
    f.write("%d"%pit+"\n")
    f.write(i+"\n")
    
    for a in d['linjastot'][i]:
        f.write(a+"\n")
        
f.close()
