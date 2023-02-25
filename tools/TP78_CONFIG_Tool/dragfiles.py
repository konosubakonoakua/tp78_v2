# Copyright (c) 2023 ChnMasterOG
# SPDX-License-Identifier: GPL-3.0

import pygame
import windnd
from io_process import read_keyboard_cfg

class Dragfiles():
    def __init__(self, screen) -> None:
        self.screen = screen
        self.display_w = self.screen.get_width()
        self.display_h = self.screen.get_height()
        hwnd = pygame.display.get_wm_info()['window']  # 获取句柄
        windnd.hook_dropfiles(
            hwnd, func=self.dragg)
 
    def dragg(self, files):
        for item in files:
            read_keyboard_cfg(item.decode('gbk'))
 