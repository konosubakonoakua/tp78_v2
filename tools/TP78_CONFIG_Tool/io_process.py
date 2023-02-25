# Copyright (c) 2023 ChnMasterOG
# SPDX-License-Identifier: GPL-3.0

from tp78_keyboard import *
from keyboard_cfg import *

processing_output = 0

def read_keyboard_cfg(fp):
    f = open(fp, 'r')
    x = 0
    y = 0
    try:
        while True:
            s = f.readline().strip()
            if s == "":
                break
            s = s.split(' ')
            for n in s:
                keyboard_matrix[x][y] = int(n)
                y += 1
                if y == keyboard_col_size:
                    y = 0
                    x += 1
    except:
        pass
    f.close()

def write_keyboard_cfg(fp):
    global processing_output
    f = open(fp, 'w')
    x = 0
    y = 0
    try:
        for x in range(keyboard_row_size):
            for y in range(keyboard_col_size):
                if y != keyboard_col_size - 1:
                    f.write(str(keyboard_matrix[x][y]) + ' ')
                else:
                    f.write(str(keyboard_matrix[x][y]) + '\n')
        processing_output = 2
    except:
        pass
    f.close()
