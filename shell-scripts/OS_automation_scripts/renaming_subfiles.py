import os


def print_all_sub_names(folder_path):
    for path, subdirs, files in os.walk(folder_path):
        for name in files:
            print(name)


def replace_names_substring(folder_path, unwanted_substring, replacement_substring):
    for path, subdirs, files in os.walk(folder_path):
        for name in subdirs:  # change this to files if you want to change file names not dir names
            if(unwanted_substring.lower() in name.lower()):
                file_path = os.path.join(path, name)
                new_name = os.path.join(
                    path, name.lower().replace(unwanted_substring.lower(), replacement_substring))
                print(name)
                print(new_name)
                print("----------")
                os.rename(file_path, new_name)


cwd = os.getcwd()
folder_path = cwd + '/node-app-aws'

replace_names_substring(
    folder_path, "BUILDING-MODERN-NODE-APPLICATIONS-ON-AWS_", "")
