import sys
import os
from pathlib import Path

new_pro_name_without_extension = sys.argv[1]

for file in os.listdir():
    if '.sln' in file:
        old_pro_name  = file

old_pro_name_without_extension = os.path.splitext(old_pro_name)[0]


def chage_inside_files():
    old_vcxproj_path = ('./%s/%s.vcxproj'%(old_pro_name_without_extension,old_pro_name_without_extension))
    old_filters_path = ('./%s/%s.vcxproj.filters'%(old_pro_name_without_extension,old_pro_name_without_extension))

    new_vcxproj_path = ('./%s/%s.vcxproj'%(old_pro_name_without_extension,new_pro_name_without_extension))
    new_filters_path = ('./%s/%s.vcxproj.filters'%(old_pro_name_without_extension,new_pro_name_without_extension))

    if os.path.exists(old_vcxproj_path):
        os.rename(old_vcxproj_path,new_vcxproj_path)
    if os.path.exists(old_filters_path):
        os.rename(old_filters_path,new_filters_path)
    if os.path.exists(old_pro_name_without_extension):
        os.rename(old_pro_name_without_extension,new_pro_name_without_extension)
    return
    
def change_outside_files():
    sln_file_str = open(old_pro_name,'r',encoding='UTF-8')
    lines = sln_file_str.readlines()
    for i in range(len(lines)):
        if 'Project(' in lines[i]:
            lines[i] =  lines[i].replace(old_pro_name_without_extension,new_pro_name_without_extension)
            break
    sln_file_str.close()
    sln_file_str = open(old_pro_name,'w',encoding='UTF-8')
    sln_file_str.writelines(lines)
    sln_file_str.close()
    os.rename(old_pro_name,('%s.sln'%new_pro_name_without_extension))
    
    
if __name__ == "__main__":
    chage_inside_files()
    change_outside_files()
