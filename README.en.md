# AdbCommandWidgetSample
Sample EditorUtilityWidget plug-in to execute adb command from the editor
![0](https://raw.githubusercontent.com/pafuhana1213/Screenshot/master/AdbCommandSample0.png)

[Japanese](https://github.com/pafuhana1213/AdbCommandWidgetSample/blob/master/README.md)

# Overview
It is a tool that can execute the adb command used in Android development from the UE4 editor.Since it was troublesome to open tools other than UE4 (command prompt etc.) just to use the adb command, I created it for myself using the Editor Utility Widget function input from UE4.22.

You can choose which command to use from the list of adb commands provided in advance. Then you can select the target terminal to execute the command or send command to all connected devices. You can also check the execution result of the command from the bottom of the tool. And, because it is implemented in the Editor Utility Widget, it can be (almost) customized by BP alone.

Development was done at UE 4.2 2.0.  
In addition, since I have only tested in the environment at hand, I do NOT guarantee the operation. In addition, function requests are NOT accepted. I hope you understand.

# 用意しているコマンド
- Get list of connected devices (adb devices)
- Run Console Command (adb shell "am broadcast -a android.intent.action.RUN -e cmd　'XXXX')
- Get Saved folder (adb pull /mnt/sdcard/UE4Game/XXX/XXX/Saved D:/XXX/XXX/Adb/XXX)
- Send UE4CommandLine.txt (adb push D:/XXX/XXX/Adb/UE4CommandLine.txt /mnt/sdcard/UE4Game/XXX/UE4CommandLine.txt)
- Start package (adb shell am start -n com.XXX.XXX/com.epicgames.ue4.SplashActivity  )
- Install package (adb install -r )
- Uninstall package (adb uninstall com.XXX.XXX )
- Setup to connect (adb tcpip 5555)
- Connect using Wifi (adb connect)
- Disconnect (adb disconnect)
- free writing for adb command (adb)
- free writing for shell command (adb shell)
 
# 使用方法
1. Plugins/AdbCommandEditorWidget を プロジェクトの Pluginsフォルダに移動
1. エディタのPluginsからAdbCommandEditorWidgetを有効に
1. コンテンツブラウザのView OptionsのShow Plugin Contentを有効に
1. /AdbCommandEditorWidget/AdbCommandWidgetSample を開く

## 作者
[@pafuhana1213](https://twitter.com/pafuhana1213)

## License
[MIT](https://github.com/pafuhana1213/AdbCommandWidgetSample/blob/master/LICENSE)
