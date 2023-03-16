# Copyright (c) 2023 ChnMasterOG
# SPDX-License-Identifier: GPL-3.0

keyboard_page = (
    "Resv", "ErrorRollOver", "POSTFail", "ErrorUndefined",  # 0~3
    "A a", "B b", "C c", "D d", "E e", "F f", "G g",        # 4~10
    "H h", "I i", "J j", "K k", "L l", "M m", "N n",        # 11~17
    "O o", "P p", "Q q", "R r", "S s", "T t", "U u",        # 18~24
    "V v", "W w", "X x", "Y y", "Z z", "1 !", "2 @",        # 25~31
    "3 #", "4 $", "5 %", "6 ^", "7 &", "8 *", "9 (",        # 32~38
    "0 )", "Enter", "Esc", "Back", "Tab", "Space",          # 39~44
    "- _", "= +", "[ {", "] }", "Non-US #", "\\ |",         # 45~50
    "; :", "' \"", "` ~", ", <", ". >", "/ ?", "Caps",      # 51~57
    "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8",         # 58~65
    "F9", "F10", "F11", "F12", "PtrSc", "Scro",             # 66~71
    "Pause", "Insert", "Home", "PgUp", "Del",               # 72~76
    "End", "PgDn", "→", "←", "↓", "↑", "Num",               # 77~83
    "/", "*", "-", "+", "Enter", "1", "2", "3", "4",        # 84~92
    "5", "6", "7", "8", "9", "0", ".", "Non-US \\",         # 93~100
    "Application", "Power", "=", "F13", "F14", "F15",       # 101~106
    "F16", "F17", "F18", "F19", "F20", "F21", "F22",        # 107~113
    "F23", "F24", "Execute", "Help", "Menu", "Select",      # 114~119
    "Stop", "Again", "Undo", "Cut", "Copy", "Paste",        # 120~125
    "Find", "Mute", "Vol Up", "Vol Down",                   # 126~129
    "Locking Caps Lock", "Locking Num Lock",                # 130~131
    "Locking Scroll Lock", "Comma", "Equal Sign",           # 132~134
    "International1", "International2",                     # 135~136
    "International3", "International4",                     # 137~138
    "International5", "International6",                     # 139~140
    "International7", "International8",                     # 141~142
    "International9", "LANG1", "LANG2", "LANG3",            # 143~146
    "LANG4", "LANG5", "LANG6", "LANG7", "LANG8",            # 147~151
    "LANG9", "Alternate Erase", "SysReq", "Cancel",         # 152~156
    "Clear", "Prior", "Return", "Separator", "Out",         # 157~160
    "Oper", "Again", "CrSel", "ExSel",                      # 161~164
    "Resv", "Resv", "Resv", "Resv",                         # 165~168
    "Resv", "Resv", "Resv", "Resv",                         # 169~172
    "Resv", "Resv", "Resv", "00",                           # 173~176
    "000", "Thousands Separator", "Decimal Separator",      # 177~179
    "Currency Unit", "Currency Sub-unit", "(",              # 180~182
    ")", "{", "}", "[Tab]", "[Backspace]", "A",             # 183~188
    "B", "C", "D", "E", "F", "XOR", "^", "%", "<",          # 189~197
    ">", "&", "&&", "|", "||", ":", "#", "Space",           # 198~205
    "@", "!", "Mem Store", "Mem Recall", "Mem Clear",       # 206~210
    "Mem Add", "Mem Subtract", "Mem Multiply",              # 211~213
    "Mem Divide", "+/-", "[Clear]", "Clear Entry",          # 214~217
    "Bin", "Oct", "Dec", "Hex",                             # 218~221
    "Resv", "Resv", "Ctrl", "Shift",                        # 222~225
    "Alt", "GUI", "Ctrl", "Shift",                          # 226~229
    "Alt", "GUI", "Resv", "Resv",                           # 230~233
    "Resv", "Resv", "Resv", "Resv",                         # 234~237
    "Resv", "Resv", "Resv", "Resv",                         # 238~241
    "Resv", "SP_1", "SP_2", "SP_3",                         # 242~245
    "SP_4", "SP_5", "SP_6", "SP_7",                         # 246~249
    "Resv", "Resv", "Resv", "Resv",                         # 250~253
    "Resv", "Fn"                                            # 254~255
)

keyboard_pynput_to_index = {
    "'a'": 4, "'b'": 5, "'c'": 6, "'d'": 7, "'e'": 8, "'f'": 9, "'g'": 10, "'h'": 11,
    "'i'": 12, "'j'": 13, "'k'": 14, "'l'": 15, "'m'": 16, "'n'": 17, "'o'": 18, "'p'": 19,
    "'q'": 20, "'r'": 21, "'s'": 22, "'t'": 23, "'u'": 24, "'v'": 25, "'w'": 26, "'x'": 27,
    "'y'": 28, "'z'": 29, "'1'": 30, "'2'": 31, "'3'": 32, "'4'": 33, "'5'": 34, "'6'": 35,
    "'7'": 36, "'8'": 37, "'9'": 38, "'0'": 39, "']'": 48, "'-'": 45, "'='": 46, "'`'": 53,
    "'\\\\'": 50, "','": 54, "'.'": 55, "'/'": 56, "';'": 51, "\"'\"": 52, "'['": 47,
    "Key.f1": 58, "Key.f2": 59, "Key.f3": 60, "Key.f4": 61, "Key.f5": 62, "Key.f6": 63,
    "Key.f7": 64, "Key.f8": 65, "Key.f9": 66, "Key.f10": 67, "Key.f11": 68, "Key.f12": 69,
    "Key.delete": 76, "Key.esc": 41, "Key.caps_lock": 57,
    "Key.backspace": 42, "Key.tab": 43, "Key.enter": 40, "Key.space": 44, 
    "Key.page_up": 75, "Key.page_down": 78, "Key.home": 74, "Key.end": 77,
    "Key.right": 79, "Key.left": 80, "Key.down": 81, "Key.up": 82, 
    "Key.ctrl_l": 224, "Key.ctrl_r": 228, "Key.alt_l": 226, "Key.alt_gr": 230, 
    "Key.cmd": 227, "Key.cmd_r": 231, "Key.shift": 225, "Key.shift_r": 229, 
    "Key.print_screen": 70, "Key.num_lock": 83, "Key.scroll_lock": 71,
}

keyboard_page_desc = {
    225: "左Shift",
    229: "右Shift",
    224: "左Ctrl", 
    228: "右Ctrl", 
    227: "左GUI - windows键",
    231: "右GUI - windows键",
    226: "左Alt",
    230: "右Alt",
    243: "TP78 SP_1键，无法捕捉",
    244: "TP78 SP_2键，无法捕捉",
    245: "TP78 SP_3键，无法捕捉",
    246: "TP78 SP_4键，无法捕捉",
    247: "TP78 SP_5键，无法捕捉",
    248: "TP78 SP_6键，无法捕捉",
    249: "TP78 SP_7键，无法捕捉",
    255: "TP78功能键Fn，无法捕捉",
}

keyboard_default_matrix = (
[41, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 76],
[53, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 45, 46, 42],
[43, 20, 26, 8, 21, 23, 28, 24, 12, 18, 19, 47, 48, 50],
[57, 4, 22, 7, 9, 10, 11, 13, 14, 15, 51, 52, 40, 75],
[225, 0, 29, 27, 6, 25, 5, 17, 16, 54, 55, 56, 229, 78],
[224, 227, 226, 44, 44, 230, 255, 228, 80, 81, 79, 82, 77, 74]
)

keyboard_default_ext_matrix = (
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 42, 82, 40, 75, 0, 0, 0, 0, 0, 70, 0, 0, 0],
[0, 80, 81, 79, 78, 0, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 74, 77, 0, 0, 0, 0, 0, 0, 0, 0],
[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
)

keyboard_row_size = 6
keyboard_col_size = 14
keyboard_core_xy_base = (190, 85)

keyboard_core_xy = (
    (
    # row 0
    (keyboard_core_xy_base[0]-3, keyboard_core_xy_base[1]),         # col0
    (keyboard_core_xy_base[0]+70, keyboard_core_xy_base[1]),        # col1
    (keyboard_core_xy_base[0]+126, keyboard_core_xy_base[1]),       # col2
    (keyboard_core_xy_base[0]+183, keyboard_core_xy_base[1]),       # col3
    (keyboard_core_xy_base[0]+239, keyboard_core_xy_base[1]),       # col4
    (keyboard_core_xy_base[0]+310, keyboard_core_xy_base[1]),       # col5
    (keyboard_core_xy_base[0]+366, keyboard_core_xy_base[1]),       # col6
    (keyboard_core_xy_base[0]+422, keyboard_core_xy_base[1]),       # col7
    (keyboard_core_xy_base[0]+479, keyboard_core_xy_base[1]),       # col8
    (keyboard_core_xy_base[0]+550, keyboard_core_xy_base[1]),       # col9
    (keyboard_core_xy_base[0]+606, keyboard_core_xy_base[1]),       # col10
    (keyboard_core_xy_base[0]+662, keyboard_core_xy_base[1]),       # col11
    (keyboard_core_xy_base[0]+718, keyboard_core_xy_base[1]),       # col12
    (keyboard_core_xy_base[0]+788, keyboard_core_xy_base[1]),       # col13
    ), (
    # row 1
    (keyboard_core_xy_base[0]+0, keyboard_core_xy_base[1]+72),      # col0
    (keyboard_core_xy_base[0]+56, keyboard_core_xy_base[1]+72),     # col1
    (keyboard_core_xy_base[0]+112, keyboard_core_xy_base[1]+72),    # col2
    (keyboard_core_xy_base[0]+168, keyboard_core_xy_base[1]+72),    # col3
    (keyboard_core_xy_base[0]+224, keyboard_core_xy_base[1]+72),    # col4
    (keyboard_core_xy_base[0]+280, keyboard_core_xy_base[1]+72),    # col5
    (keyboard_core_xy_base[0]+336, keyboard_core_xy_base[1]+72),    # col6
    (keyboard_core_xy_base[0]+393, keyboard_core_xy_base[1]+72),    # col7
    (keyboard_core_xy_base[0]+450, keyboard_core_xy_base[1]+72),    # col8
    (keyboard_core_xy_base[0]+506, keyboard_core_xy_base[1]+72),    # col9
    (keyboard_core_xy_base[0]+563, keyboard_core_xy_base[1]+72),    # col10
    (keyboard_core_xy_base[0]+618, keyboard_core_xy_base[1]+72),    # col11
    (keyboard_core_xy_base[0]+674, keyboard_core_xy_base[1]+72),    # col12
    (keyboard_core_xy_base[0]+757, keyboard_core_xy_base[1]+72),    # col13
    ), (
    # row 2
    (keyboard_core_xy_base[0]+14, keyboard_core_xy_base[1]+128),    # col0
    (keyboard_core_xy_base[0]+85, keyboard_core_xy_base[1]+128),    # col1
    (keyboard_core_xy_base[0]+141, keyboard_core_xy_base[1]+128),   # col2
    (keyboard_core_xy_base[0]+197, keyboard_core_xy_base[1]+128),   # col3
    (keyboard_core_xy_base[0]+253, keyboard_core_xy_base[1]+128),   # col4
    (keyboard_core_xy_base[0]+309, keyboard_core_xy_base[1]+128),   # col5
    (keyboard_core_xy_base[0]+365, keyboard_core_xy_base[1]+128),   # col6
    (keyboard_core_xy_base[0]+421, keyboard_core_xy_base[1]+128),   # col7
    (keyboard_core_xy_base[0]+477, keyboard_core_xy_base[1]+128),   # col8
    (keyboard_core_xy_base[0]+533, keyboard_core_xy_base[1]+128),   # col9
    (keyboard_core_xy_base[0]+590, keyboard_core_xy_base[1]+128),   # col10
    (keyboard_core_xy_base[0]+646, keyboard_core_xy_base[1]+128),   # col11
    (keyboard_core_xy_base[0]+703, keyboard_core_xy_base[1]+128),   # col12
    (keyboard_core_xy_base[0]+775, keyboard_core_xy_base[1]+128),   # col13
    ), (
    # row 3
    (keyboard_core_xy_base[0]+15, keyboard_core_xy_base[1]+184),    # col0
    (keyboard_core_xy_base[0]+95, keyboard_core_xy_base[1]+184),    # col1
    (keyboard_core_xy_base[0]+151, keyboard_core_xy_base[1]+184),   # col2
    (keyboard_core_xy_base[0]+207, keyboard_core_xy_base[1]+184),   # col3
    (keyboard_core_xy_base[0]+264, keyboard_core_xy_base[1]+184),   # col4
    (keyboard_core_xy_base[0]+320, keyboard_core_xy_base[1]+184),   # col5
    (keyboard_core_xy_base[0]+377, keyboard_core_xy_base[1]+184),   # col6
    (keyboard_core_xy_base[0]+433, keyboard_core_xy_base[1]+184),   # col7
    (keyboard_core_xy_base[0]+488, keyboard_core_xy_base[1]+184),   # col8
    (keyboard_core_xy_base[0]+546, keyboard_core_xy_base[1]+184),   # col9
    (keyboard_core_xy_base[0]+602, keyboard_core_xy_base[1]+184),   # col10
    (keyboard_core_xy_base[0]+659, keyboard_core_xy_base[1]+184),   # col11
    (keyboard_core_xy_base[0]+748, keyboard_core_xy_base[1]+184),   # col12
    (keyboard_core_xy_base[0]+867, keyboard_core_xy_base[1]+72),    # col13
    ), (
    # row 4
    (keyboard_core_xy_base[0]+30, keyboard_core_xy_base[1]+240),    # col0
    (keyboard_core_xy_base[0]-999, keyboard_core_xy_base[1]-999),   # col1 - no used
    (keyboard_core_xy_base[0]+125, keyboard_core_xy_base[1]+240),   # col2
    (keyboard_core_xy_base[0]+181, keyboard_core_xy_base[1]+240),   # col3
    (keyboard_core_xy_base[0]+237, keyboard_core_xy_base[1]+240),   # col4
    (keyboard_core_xy_base[0]+293, keyboard_core_xy_base[1]+240),   # col5
    (keyboard_core_xy_base[0]+349, keyboard_core_xy_base[1]+240),   # col6
    (keyboard_core_xy_base[0]+405, keyboard_core_xy_base[1]+240),   # col7
    (keyboard_core_xy_base[0]+462, keyboard_core_xy_base[1]+240),   # col8
    (keyboard_core_xy_base[0]+518, keyboard_core_xy_base[1]+240),   # col9
    (keyboard_core_xy_base[0]+574, keyboard_core_xy_base[1]+240),   # col10
    (keyboard_core_xy_base[0]+630, keyboard_core_xy_base[1]+240),   # col11
    (keyboard_core_xy_base[0]+708, keyboard_core_xy_base[1]+240),   # col12
    (keyboard_core_xy_base[0]+867, keyboard_core_xy_base[1]+128),   # col13
    ), (
    # row 5
    (keyboard_core_xy_base[0]+5, keyboard_core_xy_base[1]+296),     # col0
    (keyboard_core_xy_base[0]+74, keyboard_core_xy_base[1]+296),    # col1
    (keyboard_core_xy_base[0]+145, keyboard_core_xy_base[1]+296),   # col2
    (keyboard_core_xy_base[0]+237, keyboard_core_xy_base[1]+296),   # col3
    (keyboard_core_xy_base[0]+463, keyboard_core_xy_base[1]+296),   # col4
    (keyboard_core_xy_base[0]+562, keyboard_core_xy_base[1]+296),   # col5
    (keyboard_core_xy_base[0]+618, keyboard_core_xy_base[1]+296),   # col6
    (keyboard_core_xy_base[0]+675, keyboard_core_xy_base[1]+296),   # col7
    (keyboard_core_xy_base[0]+745, keyboard_core_xy_base[1]+310),   # col8
    (keyboard_core_xy_base[0]+802, keyboard_core_xy_base[1]+310),   # col9
    (keyboard_core_xy_base[0]+858, keyboard_core_xy_base[1]+310),   # col10
    (keyboard_core_xy_base[0]+802, keyboard_core_xy_base[1]+254),   # col11
    (keyboard_core_xy_base[0]+867, keyboard_core_xy_base[1]+184),   # col12
    (keyboard_core_xy_base[0]+867, keyboard_core_xy_base[1]+240),   # col13
    )
)
