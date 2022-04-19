#!/usr/bin/python


""" Creates an m3u playlist with relative paths inside.
    Playlist is created inside the dir supplied.
    All media files inside the root dir are sorted using 'natural' sort.
"""
# Example usage: replace the
# python generate_playlist.py -d "<course root directory>" -p my_playlist.m3u

# to install the code globally ... move it to a path dir and change its excution permission

import argparse
from os import walk
from os import path
from natsort import natsorted

import subprocess

def get_length(filename):
    result = subprocess.run(["ffprobe", "-v", "error", "-show_entries",
                             "format=duration", "-of",
                             "default=noprint_wrappers=1:nokey=1", filename],
    stdout=subprocess.PIPE,
    stderr=subprocess.STDOUT)
    print(result.stdout)
    return float(result.stdout)


def get_file_list(root_dir_path):
    media_files = []
    for (dirpath, _dirnames, filenames) in walk(root_dir_path):
        for file in filenames:
            extension = path.splitext(file)[1]
            if extension in ['.mp4', '.mp3', '.mkv', '.aac','.avi' , '.mov']:
                media_files.append(path.join(dirpath, file))
                # print(root_dir_path+'/'+ file)
    return media_files


def create_playlist(playlist_path, files):
    with open(playlist_path, 'w', encoding='utf-8') as p:
        for f in files:
            print(f, file=p)

def generate_durations(playlist_path, files):
    print(*files, sep='\n')
    with open('./000-durations.txt', 'w', encoding='utf-8') as p:
        for file in files:
            try:
                duration = round(get_length(file) / 60, 2) 
            except:
                duration = 0
            print(f'{file}\t{duration}', file=p)




def parse_arguments():
    """ Parses the arguments
        directory is required argument
        playlist name defaults to playlist.m3u
        sort_by_files defaults to False"""
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-p", "--play-list", default='000-playlist.m3u', help="playlist name")
    parser.add_argument(
        "-d", "--directory", required=True, default=' .', help="root directory")
    parser.add_argument(
        '--sort-by-files',
        dest='sort_by_files',
        action='store_true',
        help='sorts list by file name')
    parser.add_argument(
        '--no-sort-by-files',
        dest='sort_by_files',
        action='store_false',
        help='disables file name based sort')
    parser.set_defaults(sort_by_files=False)
    return parser.parse_args()


def main():
    """ Entry point function """
    args = parse_arguments()
    file_list = get_file_list(args.directory)
    if args.sort_by_files:
        file_list = natsorted(file_list, path.basename)
    else:
        file_list = natsorted(file_list)
    relative_paths = [path.relpath(p, args.directory) for p in file_list]
    # print(*relative_paths, sep='\n')
    create_playlist(path.join(args.directory, args.play_list), relative_paths)
    generate_durations(path.join(args.directory, args.play_list),file_list)



if __name__ == '__main__':
    main()
# 