# AdbCommandWidgetSample
adbコマンドをエディタ上から実行するEditorUtilityWidgetのプラグイン・サンプル  
![0](https://raw.githubusercontent.com/pafuhana1213/Screenshot/master/AdbCommandSample0.png)

English

# 概要
Android開発で使うadbコマンドをUE4エディタから実行できるツールです。adbコマンドを使うためだけにUE4以外のツール（コマンドプロンプトなど）を開くことが面倒だったので、UE4.22から入ったEditor Utility Widget機能を使って自分用に作成しました。

事前に用意されたadbコマンドのリストからどのコマンドを使用するか選択可能です。そして、コマンドを実行する対象の端末を選択、または接続中の全デバイスにadbコマンドを送る事が可能です。また、コマンドの実行結果をツール下部から確認することも可能です。そして、Editor Utility Widgetで実装しているため、BPだけで（ほぼ）カスタマイズ可能です。

開発はUE4.22.0で行いました。  
なお、手元の環境でしかテストをしていないため、動作保証はしていません。また、機能要望は受け付けていません。ご理解いただけますと幸いです。

# 用意されているコマンド
- 接続中のデバイスのリスト取得 (adb devices)
- 実機にConsole Commandを送信 (adb shell "am broadcast -a android.intent.action.RUN -e cmd　'XXXX')
- 実機からSavedフォルダを取得 (adb pull /mnt/sdcard/UE4Game/XXX/XXX/Saved D:/XXX/XXX/Adb/XXX)
- 
 
