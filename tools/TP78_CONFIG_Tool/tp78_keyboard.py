# Copyright (c) 2023 ChnMasterOG
# SPDX-License-Identifier: GPL-3.0

import pygame
import copy
import os
import kbm_detection
import io_process
import _thread
from keyboard_cfg import *

workpwd = ""
keyboard_matrix = copy.deepcopy(keyboard_default_matrix)

WHITE = (255, 255, 255)
BLUE = (0, 0, 255)
LIGHT_BLUE = (50, 50, 255)
CYAN = (153, 217, 234)
RED = (255, 0, 0)
GREEN = (0, 255, 0)

KEY_TITLE0_POS = (keyboard_core_xy_base[0]-10, keyboard_core_xy_base[1]-60)
KEY_TITLE1_POS = (keyboard_core_xy_base[0]-10, keyboard_core_xy_base[1]+381)
KEY_TITLE2_POS = (keyboard_core_xy_base[0]-10, keyboard_core_xy_base[1]+461)
KEY_TITLE3_POS = (keyboard_core_xy_base[0]-10, keyboard_core_xy_base[1]+541)
KEY_TITLE4_POS = (keyboard_core_xy_base[0]+300, keyboard_core_xy_base[1]+381)
KEY_TITLE5_POS = (keyboard_core_xy_base[0]+300, keyboard_core_xy_base[1]+541)
KEY_OUTPUT_POS = (keyboard_core_xy_base[0]+300, keyboard_core_xy_base[1]+461)
KEY_SWITCH_MODE_POS = (keyboard_core_xy_base[0]+300, keyboard_core_xy_base[1]+498)
KEY_DESCRIPTION1_POS = (keyboard_core_xy_base[0]-10, keyboard_core_xy_base[1]+425)
KEY_DESCRIPTION2_POS = (keyboard_core_xy_base[0]-10, keyboard_core_xy_base[1]+505)
KEY_DESCRIPTION3_POS = (keyboard_core_xy_base[0]-10, keyboard_core_xy_base[1]+585)
KEY_LOG_POS = (keyboard_core_xy_base[0]+300, keyboard_core_xy_base[1]+585)
KEY_LOGO_POS = (keyboard_core_xy_base[0]+700, keyboard_core_xy_base[1]+400)
KEY_USERDIFINED_TEXT_POS = (keyboard_core_xy_base[0]+310, keyboard_core_xy_base[1]+425)
KEY_USERDIFINED_RECT_POS = (keyboard_core_xy_base[0]+300, keyboard_core_xy_base[1]+418, 250, 30)

class Keyboard(pygame.sprite.Sprite):
    def __init__(self):
        super().__init__()
        self.img = pygame.image.load("./res/keyboard.png").convert_alpha()
        self.core = (1280/2, keyboard_core_xy_base[1]+175)
        self.key_front = pygame.font.SysFont('arial', 16)
        self.title_front = pygame.font.Font('./res/font2.ttf', 24)
        self.desc_front = pygame.font.Font('./res/font1.ttf', 16)
        self.color = [[WHITE for i in range(keyboard_col_size)] for j in range(keyboard_row_size)]
        self.rect = [[0 for i in range(keyboard_col_size)] for j in range(keyboard_row_size)]
        self.input_rect = pygame.Rect(*KEY_USERDIFINED_RECT_POS)
        self.output_rect = self.title_front.render("导出布局到当前目录", True, WHITE).get_rect(topleft = KEY_OUTPUT_POS)
        self.switch_mode_rect = self.title_front.render("切换到键盘测试", True, WHITE).get_rect(topleft = KEY_SWITCH_MODE_POS)
        self.now_key_x = 0
        self.now_key_y = 0
        self.color[0][0] = RED
        self.input_text_color = WHITE
        self.output_text_color = WHITE
        self.switch_mode_color = WHITE
        self.log_color = WHITE
        self.log_text = ""
        self.userdefkey = 0
        self.mode = 0
    
    def show(self, screen):
        screen.blit(self.img, self.img.get_rect(center=tuple(self.core)))
        if io_process.processing_output == 1:
            text = self.title_front.render("正在导出", True, self.output_text_color)
            screen.blit(text, text.get_rect(topleft = KEY_OUTPUT_POS))
        else:
            if io_process.processing_output == 2:
                io_process.processing_output = 0
                self.show_log("导出完成！", GREEN)
            text = self.title_front.render("导出布局到当前目录", True, self.output_text_color)
            screen.blit(text, text.get_rect(topleft = KEY_OUTPUT_POS))
        if self.mode == 0:
            text = self.title_front.render("切换到键盘测试", True, self.switch_mode_color)
            screen.blit(text, text.get_rect(topleft = KEY_SWITCH_MODE_POS))
        else:
            text = self.title_front.render("切换到改键配置", True, self.switch_mode_color)
            screen.blit(text, text.get_rect(topleft = KEY_SWITCH_MODE_POS))
        if kbm_detection.keycode_update == True:
            kbm_detection.keycode_update = False
            if self.mode == 0:  # 模式0
                if self.input_text_color == WHITE:   # 选择按键
                    keyboard_matrix[self.now_key_x][self.now_key_y] = kbm_detection.keycode
                else:   # 自定义改键
                    if kbm_detection.keycode >= 30 and kbm_detection.keycode <= 38:
                        self.userdefkey *= 10
                        self.userdefkey += kbm_detection.keycode - 29
                    elif kbm_detection.keycode == 39:
                        self.userdefkey *= 10
                    elif kbm_detection.keycode == 42:
                        self.userdefkey = int(self.userdefkey / 10)
                    elif kbm_detection.keycode == 40:
                        keyboard_matrix[self.now_key_x][self.now_key_y] = self.userdefkey
                    # 上下限约束
                    if self.userdefkey < 0:
                        self.userdefkey = 0
                    elif self.userdefkey > 255:
                        self.userdefkey = 255
            else:   # 模式1
                for x in range(keyboard_row_size):
                    for y in range(keyboard_col_size):
                        if keyboard_matrix[x][y] == kbm_detection.keycode:
                            self.color[x][y] = RED
        for x in range(keyboard_row_size):
            for y in range(keyboard_col_size):
                text = self.key_front.render(keyboard_page[int(keyboard_matrix[x][y])], True, self.color[x][y])
                self.rect[x][y] = text.get_rect(topleft = keyboard_core_xy[x][y])
                screen.blit(text, self.rect[x][y])
        text = self.title_front.render("拖入布局以导入 ", True, WHITE)
        screen.blit(text, text.get_rect(topleft = KEY_TITLE0_POS))
        text = self.title_front.render("键码信息: ", True, WHITE)
        screen.blit(text, text.get_rect(topleft = KEY_TITLE1_POS))
        text = self.desc_front.render("Dec: %d Hex: %x" % (keyboard_matrix[self.now_key_x][self.now_key_y], keyboard_matrix[self.now_key_x][self.now_key_y]), True, WHITE)
        screen.blit(text, text.get_rect(topleft = KEY_DESCRIPTION1_POS))
        text = self.title_front.render("描述: ", True, WHITE)
        screen.blit(text, text.get_rect(topleft = KEY_TITLE2_POS))
        text = self.title_front.render("典型案例: ", True, WHITE)
        screen.blit(text, text.get_rect(topleft = KEY_TITLE3_POS))
        text = self.title_front.render("自定义Key, Enter生效: ", True, WHITE)
        screen.blit(text, text.get_rect(topleft = KEY_TITLE4_POS))
        text = self.title_front.render("LOG信息: ", True, WHITE)
        screen.blit(text, text.get_rect(topleft = KEY_TITLE5_POS))
        text = self.desc_front.render(self.log_text, True, self.log_color)
        screen.blit(text, text.get_rect(topleft = KEY_LOG_POS))
        text = self.desc_front.render(str(self.userdefkey), True, self.input_text_color)
        screen.blit(text, text.get_rect(topleft = KEY_USERDIFINED_TEXT_POS))
        logo_img = pygame.image.load("./res/logo.png").convert_alpha()
        screen.blit(logo_img, logo_img.get_rect(topleft = KEY_LOGO_POS))
        pygame.draw.rect(screen, CYAN, self.input_rect, 2)
        if int(keyboard_matrix[self.now_key_x][self.now_key_y]) in keyboard_page_desc:
            text = self.desc_front.render(keyboard_page_desc[keyboard_matrix[self.now_key_x][self.now_key_y]], True, WHITE)
            screen.blit(text, text.get_rect(topleft = KEY_DESCRIPTION2_POS))
        if os.path.exists("./res/%d.png" % (keyboard_matrix[self.now_key_x][self.now_key_y])):
            img = pygame.image.load("./res/%d.png" % (keyboard_matrix[self.now_key_x][self.now_key_y])).convert_alpha()
            screen.blit(img, img.get_rect(topleft = KEY_DESCRIPTION3_POS))
        else:
            img = pygame.image.load("./res/default.png").convert_alpha()
            screen.blit(img, img.get_rect(topleft = KEY_DESCRIPTION3_POS))

    def clicked_detection(self, pos):
        # 自定义Key
        if self.input_rect.collidepoint(pos):
            self.input_text_color = RED
        else:
            self.input_text_color = WHITE
        # 切换模式
        if self.switch_mode_rect.collidepoint(pos):
            if self.mode == 0:
                self.mode = 1
                self.color[self.now_key_x][self.now_key_y] = WHITE
            else:
                self.mode = 0
                for x in range(keyboard_row_size):
                    for y in range(keyboard_col_size):
                        self.color[x][y] = WHITE
                self.color[self.now_key_x][self.now_key_y] = RED
        # 保存布局
        if self.output_rect.collidepoint(pos) and io_process.processing_output == 0:
            io_process.processing_output = 1
            _thread.start_new_thread(io_process.write_keyboard_cfg, (os.path.join(workpwd, "keyboard_mat.txt"),))
        # 点击对应key
        for x in range(keyboard_row_size):
            for y in range(keyboard_col_size):
                if self.rect[x][y].collidepoint(pos):
                    if self.mode == 0:
                        self.color[x][y] = RED
                        self.color[self.now_key_x][self.now_key_y] = WHITE
                    else:
                        self.color[x][y] = WHITE
                    self.now_key_x = x
                    self.now_key_y = y

    def move_detection(self, pos):
        if self.output_rect.collidepoint(pos):
            self.output_text_color = RED
        else:
            self.output_text_color = WHITE
        if self.switch_mode_rect.collidepoint(pos):
            self.switch_mode_color = RED
        else:
            self.switch_mode_color = WHITE
    
    def show_log(self, logtext, color, delayms = 3000):
        self.log_color = color
        self.log_text = logtext
        pygame.time.set_timer(pygame.USEREVENT + 1, delayms)

    def hide_log(self):
        self.log_text = ""
