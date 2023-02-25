# Copyright (c) 2023 ChnMasterOG
# SPDX-License-Identifier: GPL-3.0

from pynput import keyboard
from pynput import mouse
from keyboard_cfg import keyboard_pynput_to_index

keycode = 0
keycode_update = False

def on_press(key):
    # try:
    #     print(f'{key.char} down')
    #     print(keyboard_page.index(key.char.upper()+" "+key.char))
    # except AttributeError:
    #     print(f'{key} down')
    # except:
    #     pass
    pass

def on_release(key):
    global keycode, keycode_update
    if str(key) in keyboard_pynput_to_index:
        keycode = keyboard_pynput_to_index[str(key)]
        keycode_update = True
    #print(f'{key} up')
  
def on_move(x,y):
    print('move to',x,y)
 
def on_click(x,y,button,pressed):
    print('click at',x,y,button,pressed)
 
def on_scroll(x,y,dx,dy):
    print('scroll at',x,y,'by',dx,dy)
 
def listen_key_nblock():
    listener = keyboard.Listener(
        on_press=on_press, on_release=on_release
    )
    listener.start()  # 启动线程
  
def listen_mouse_nblock():
    listener = mouse.Listener(
        on_move=None,
        on_click=on_click,
        on_scroll=on_scroll
    )
    listener.start()
 