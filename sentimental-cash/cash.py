# TODO
import cs50
import csv
import sys


def main():
    cash_in =-1.0
    count=0
    change=0
    denominations = [.25,.10,.05,.01]

    while (cash_in<0):
        cash_in = cs50.get_float("Change owed:")

    for i in denominations:
        count += int(round(cash_in/i,2))
        cash_in = cash_in - int(round(cash_in/i,2))*i

    print(f"{count}")


if __name__ == "__main__":
    main()


