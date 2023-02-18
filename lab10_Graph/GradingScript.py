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
    stu_file = "g++ -std=c++11 "+str(stu_cpp_file)+" -o Stu_Lab10 >/dev/null 2>&1"
    out_path = "./"+stu_output_name+"/stu_result"
    flag = os.system(stu_file)
    if flag ==0 :
        for k in range(10):
            cmd_cpp_2 = "./Stu_Lab10 "+folder_path+str(k)+" > "+ out_path+str(k)
            os.system(cmd_cpp_2)
        return True
    else:
        print("The program can not compile")
        sys.exit()
        return False



if __name__ == '__main__':
    foldername = sys.argv[2]
    headername = sys.argv[1]
    outputname = sys.argv[3]
    if((foldername)=="" or (headername)=="" or outputname==""):
        print("please input parameters")
    else:
        if(os.path.exists(headername)):
            stu_cases_path = "mkdir stu_result >/dev/null 2>&1"
            os.system(stu_cases_path)
            folder_path = "./"+str(foldername)+"/data"
            header_rename = "cp " +(headername)+ " myGraph.h >/dev/null 2>&1"
            os.system(header_rename)
            stu_cases_path = "stu_result"
            flag = compileStudentCpp("MainTest.cpp",stu_cases_path,foldername)
            outfolder_path = "./"+outputname+"/right_result"
            if flag:
                outputfoler_name = "cp -r sample_output "+str(outputname)+" >/dev/null 2>&1"
                os.system(outputfoler_name)
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
            else:
                print("Please input your lab header")
                sys.exit()
        else:
            print("Your Lab header does not exist")

   
