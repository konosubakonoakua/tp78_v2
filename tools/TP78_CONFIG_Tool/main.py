# Copyright (c) 2023 ChnMasterOG
# SPDX-License-Identifier: GPL-3.0

import pygame
import os
import sys
from dragfiles import Dragfiles
import tp78_keyboard
from tp78_keyboard import Keyboard
from kbm_detection import listen_key_nblock

tp78_keyboard.workpwd = os.getcwd()

# 资源文件目录访问
def source_path(relative_path):
    # 是否Bundle Resource
    if getattr(sys, 'frozen', False):
        base_path = sys._MEIPASS
    else:
        base_path = os.path.abspath(".")
    return os.path.join(base_path, relative_path)

# 修改当前工作目录，使得资源文件可以被正确访问
cd = source_path('')
os.chdir(cd) 

pygame.init()

pygame.display.set_caption('TP78 Keyboard Config Tool')
pygame_icon = pygame.image.load('./res/icon.png')
pygame.display.set_icon(pygame_icon)
window = pygame.display.set_mode((1280,768))
window.fill((0, 0, 0))
bg = pygame.image.load("./res/bg.png")
# my_switch = Switch()
# my_button = Button()
my_dragfiles = Dragfiles(window)
my_keyboard = Keyboard()

listen_key_nblock()

# first show
my_keyboard.show(window)

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            sys.exit()
        # 鼠标事件
        if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
            mouse = pygame.mouse.get_pos()
            my_keyboard.clicked_detection(mouse)
        if event.type == pygame.MOUSEMOTION:
            mouse = pygame.mouse.get_pos()
            my_keyboard.move_detection(mouse)
        if event.type == pygame.USEREVENT + 1:
            my_keyboard.hide_log()

    window.blit(bg, (0, 0))
    my_keyboard.show(window)

    pygame.display.update()
    #pygame.time.delay(5)
