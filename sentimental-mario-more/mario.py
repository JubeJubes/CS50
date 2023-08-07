# TODO
import cs50


def main():
    input1 = 0
    while (input1<1 or input1 >8):
        input1 = cs50.get_int("Height:")
    recurs_pyramid(input1,input1)


def recurs_pyramid(n,i):
    if (i>0):
        recurs_pyramid(n,i-1)
        print(" "*(n-i),end="")
        print("#"*(i),end="")
        print("  ",end="")
        print("#"*(i))


if __name__ == "__main__":
    main()



