import os



def fild_all_files(directory):
    for root, dirs, files in os.walk(directory):
        yield root
        for file in files:
            yield os.path.join(root, file)

for f in fild_all_files('./'):

    filename = os.path.basename(f)
    path, ext = os.path.splitext(f)

    if ext != ".cpp" and ext != ".h" and ext != ".hpp":
        continue
    if filename == "library.cpp":
        continue

    #print filename

    print("#"*50)
    l = (50-len(f)-2)//2
    r = (50-len(f)-2)-l
    print("#"*l+" "+f+" "+"#"*r)
    print("#"*50)
    print("")
    with open(f) as f:
        print(f.read())
    print("")
