# TODO
import cs50

def coleman(l,w,s):
    c_var = 0.0588 * (l/w*100) - 0.296 * (s/w*100) - 15.8
    if (c_var <1):
        return print("Before Grade 1")
    elif (c_var >16):
        return print("Grade 16+")
    print(f"Grade {round(c_var)}")


def main():
    letters =0
    words=1
    sentences=0

    text1 = cs50.get_string("Text:")
    for element in text1:
        if (element.isalpha()):
            letters +=1
        if (element.isspace()):
            words +=1
        if ((element == '!') or (element == '?') or (element == '.')):
            sentences +=1
    coleman(letters,words,sentences)


if __name__ == "__main__":
    main()