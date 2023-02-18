import os
import sys

def cmp_file(f1, f2):
    st1 = os.stat(f1)
    st2 = os.stat(f2)
    if st1.st_size != st2.st_size:
        return False
    bufsize = 8*1024*8
    with open(f1, 'rb') as fp1, open(f2, 'rb') as fp2:
        while True:
            b1 = fp1.read(bufsize)  # 
            b2 = fp2.read(bufsize)
            if b1 != b2:
                return False
            if not b1:
                return True

def compileStudentCpp(stu_cpp_file,stu_output_name,inputfoler_name):
    folder_path = "./"+str(inputfoler_name)+"/data"
    stu_file = "g++ "+str(stu_cpp_file)+" -o Stu_Lab1"
    out_path = "./"+stu_output_name+"/stu_result"
    os.system(stu_file)
    for k in range(10):
        cmd_cpp_2 = "./Stu_Lab1 "+folder_path+str(k)+" > "+ out_path+str(k)
        os.system(cmd_cpp_2)


if __name__ == '__main__':
    foldername = sys.argv[2]
    headername = sys.argv[1]
    outputname = sys.argv[3]
    #create folder
    if((foldername)=="" or (headername)=="" or outputname==""):
        print("please input parameters")
    else:
        outputfoler_name = "mkdir "+str(outputname)
        os.system(outputfoler_name)
        stu_cases_path = "mkdir stu_result"
        os.system(stu_cases_path)
        # os.system("g++ MainTest.cpp -o Lab1")
        folder_path = "./"+str(foldername)+"/data"

    #correct results
        for k in range(10):
            cmd_cpp_1 = "./Lab1 "+folder_path+str(k)+" > "+ "./"+outputname+"/right_result"+str(k)
            os.system(cmd_cpp_1)
    
        header_rename = "mv " +(headername)+ " myVector.h"
        os.system(header_rename)

    #students' main cpp file to compile
        stu_cases_path = "stu_result"
        compileStudentCpp("MainTest.cpp",stu_cases_path,foldername)
        outfolder_path = "./"+outputname+"/right_result"
        score = 0
        for k in range(10):
            f1 = "./"+stu_cases_path+"/stu_result"+str(k)
            f2 = outfolder_path+str(k)
            if(cmp_file(f1,f2)):
                score = score + 10
            else:
                score = score + 0
            print("student result"+" "+str(k)+" is "+str(cmp_file(f1,f2)))
        print("Total point = "+str(score))
