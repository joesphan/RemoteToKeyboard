# RemoteToKeyboard
Converting old remote controls to keyboards for use on mediacenter/kodi/the lazy

# Req
-Arduino Pro micro/leonardo
-IR receiver, 3 legged boi: ![image](https://user-images.githubusercontent.com/38387138/115137890-84d3e480-9fdd-11eb-9ddd-50c88684d3c4.png)

# hookup
https://create.arduino.cc/projecthub/electropeak/use-an-ir-remote-transmitter-and-receiver-with-arduino-1e6bc8

Uses NicoHood's HID library, key code macros found in improvedkeylayouts.h, consumerapi.h, keyboard.h
for any consumerapi keycodes use consumer.write(byte keycode)
otherwise use bootkeyboard.write(byte keycode)
