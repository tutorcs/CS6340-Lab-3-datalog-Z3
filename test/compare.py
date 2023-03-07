https://tutorcs.com
WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
import sys


if len(sys.argv) != 3:
    print("Usage: compare.py <first_file> <second_file>")
    exit(1)
f1 = sys.argv[1]
f2 = sys.argv[2]
fp1 = open(f1, "r")
fp2 = open(f2, "r")
i=0
type_1_errors = 0
type_2_errors = 0
for line1, line2 in zip(fp1, fp2):
    i += 1
    if(line1 == line2):
        continue
    nl1 = " " + line1.strip("[]\n")
    nl2 = " " + line2.strip("[]\n")
    x1 = set(nl1.split(";"))
    x2 = set(nl2.split(";"))
    if x1 != x2:
        print("Line difference in line {}:".format(i))
        diff_set1 = x1.difference(x2)
        diff_set2 = x2.difference(x1)
        if bool(diff_set1):
            print("Values missing from second file:", diff_set1)
            type_2_errors += len(diff_set1)
        if bool(diff_set2):
            print("Values missing from first file:", diff_set2)
            type_1_errors += len(diff_set2)
        print("Type 1 errors: %d; Type 2 errors: %d; Total: %d)" %
            (type_1_errors, type_2_errors, type_1_errors + type_2_errors))
        print("#########################")
