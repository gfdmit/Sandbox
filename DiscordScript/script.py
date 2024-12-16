import pyautogui

pyautogui.click(50, 350, duration=1)

number = 35
while(number != 88):
    pyautogui.click(365, 725, duration=3)
    pyautogui.click(500, 250, duration=1)
    pyautogui.click(500, 375, duration=1)
    pyautogui.moveTo(675, 375, duration=1)
    pyautogui.dragRel(0, 200, duration=1)
    pyautogui.click(550, 925,duration=1)
    pyautogui.click(900, 630, duration=1)
    pyautogui.typewrite(str(number))
    pyautogui.click(1100, 700, duration=1)
    number += 1