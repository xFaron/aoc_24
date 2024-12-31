import os

i = int(input("Enter day: "))
clear = input("Clear data[Type 'Yes']: ")

try:
    try:
        os.mkdir(f"Day{i}")
        print(f"Created Day{i} directory")
    except:
        print(f"Directory already exist | Day{i}")
    
    for j in range(2):
        path = f"./Day{i}/q{j+1}.cpp"

        if not os.path.exists(path) or clear == "Yes":
            with open(path, "w") as f:
                print(f"> Created file {path}")
                f.write("#include <iostream>\n\nint main() {\n\n\treturn 0;\n}")
        else:
            print(f"> File {path} already exists")
    
    for j in range(2):
        path = f"./Day{i}/input{j+1}.txt"

        if not os.path.exists(path) or clear == "Yes":
            with open(path, "w") as f:
                print(f"> Created file {path}")
        else:
            print(f"> File {path} already exists")

    print("Created files")
except Exception as e:
    print(f"Error for iteration {i}: {e}")