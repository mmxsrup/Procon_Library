import os

for f in os.listdir("."):
  if f == "library.cpp":
    continue
  if (".cpp" or ".h") not in f:
    continue
  print("#"*50)
  l = (50-len(f)-2)//2
  r = (50-len(f)-2)-l
  print("#"*l+" "+f+" "+"#"*r)
  print("#"*50)
  print("")
  with open(f) as f:
    print(f.read())
  print("")
