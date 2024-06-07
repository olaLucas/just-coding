from os import sys, listdir, mkdir, chdir, rmdir 


def rm_dir(target_dir):
    if '/' in target_dir:
        target_split = target_dir.split('/')
        if len(target_split) > 1:
            path_dir = target_split[0] # taking an directory before to check if it exists
            for i in range(1, len(target_split) - 1):
                path_dir = path_dir + '/' + target_split[i]

            if target_split[-1] in listdir(path_dir): # see if the directory exists
                try:
                    chdir(path_dir)
                    rmdir(path_dir + '/' + target_split[-1])
                    # rmdir(target_split[-1])
                except:
                    print(listdir(path_dir))
                    print(f'error while trying to remove {target_dir}')
            else:
                print(listdir(path_dir))
                print(f'{target_dir} not found.')

    else:
        if target_dir in listdir():
            try:
                rmdir(target_dir)
            except:
                print(f'error while trying to remove {target_dir}')
        else:
            print(f'{target_dir} not found.')


def scan_dir(path):
        entries = listdir(path)
        if len(entries) > 0:
            for entry in entries:
                print(path + entry)
                try:
                    if path[-1] != '/':
                        scan_dir(path + '/'  + entry)
                    else:
                        scan_dir(path + entry)
                except:
                    pass


def make_dir(target_dir):
    if '/' in target_dir:
        pathname = target_dir.split('/')
        if len(pathname) > 1:
            if  pathname[0] not in listdir(): # checking if the folder already exist
                for directory in pathname: # creating recursive
                    try:
                        mkdir(directory) # is there a better way to do that?
                        chdir(directory)
                    except:
                        print(f'error while trying to create: {directory}')
    
    elif ' ' in target_dir:
        print('oops not implemented yet')

    else:
        if target_dir not in listdir():
            mkdir(target_dir)
                

# TODO: -mk various files simultaniously
def terminal_args():
    args = (( '-l',  '--list' ), 
            ( '-mk', '--mkdir'),
            ( '-rm', '--rm   '))

    if len(sys.argv) > 1:
        for i in range(1, len(sys.argv)):
            if sys.argv[i] in args[0]:
                scan_dir(sys.argv[i + 1])
                i += 1

            elif sys.argv[i] in args[1]:
                make_dir(sys.argv[i + 1])
                i += 1

            elif sys.argv[i] in args[2]:
                rm_dir(sys.argv[i + 1])
                i += 1

            elif '--' in sys.argv[i] or '-' in sys.argv[i]:
                if sys.argv[i] not in args:
                    print(f'Unknown argument: {sys.argv[i]}')


terminal_args()
