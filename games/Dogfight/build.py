
import os
import sys


def buildWeb():
    print("building...")
    res = os.system("dockcross-web-wasm bash -c 'make web'")

    if(res != 0):
        print("build failed with exitcode: " + str(res))
    else:
        print("build successfully")

def clean():
    print("cleaning...")
    res = os.system("dockcross-web-wasm bash -c 'make clean'")

    if(res != 0):
        print("clean failed with exitcode: " + str(res))
    else:
        print("clean successfully")

if(__name__ == "__main__"):
    try:
        if(sys.argv[1] == "web"):
            buildWeb()
        elif(sys.argv[1] == "clean"):
            clean()
        else:
            print("no known action specified")
    except IndexError:
        print("pleas specifie a valid action")