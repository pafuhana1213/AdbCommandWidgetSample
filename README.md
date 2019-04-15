# AdbCommandWidgetSample
adbコマンドをエディタ上から実行するEditorUtilityWidgetのプラグイン・サンプル  
  
![0](https://raw.githubusercontent.com/pafuhana1213/Screenshot/master/AdbCommandSample0.png)

[English](https://github.com/pafuhana1213/AdbCommandWidgetSample/blob/master/README.en.md)

# 概要
Android開発で使うadbコマンドをUE4エディタから実行できるツールです。adbコマンドを使うためだけにUE4以外のツール（コマンドプロンプトなど）を開くことが面倒だったので、UE4.22から入ったEditor Utility Widget機能を使って自分用に作成しました。

- 事前に用意されたadbコマンドのリストからどのコマンドを使用するか選択可能です
- コマンドを実行する対象の端末を選択、または接続中の全デバイスにadbコマンドを送る事が可能です
- コマンドの実行結果をツール下部から確認することも可能です
- コマンドの実行は非同期に行うため、コマンドが完了するまで作業を待つ必要はありません
- Editor Utility Widgetで実装しているため、BPだけで（ほぼ）カスタマイズ可能です。

開発はUE4.22.0で行いました。  
なお、手元の環境でしかテストをしていないため、動作保証はしていません。また、機能要望は受け付けていません。ご理解いただけますと幸いです。

# 用意しているコマンド
- 接続中のデバイスのリスト取得 (adb devices)
- 実機にConsole Commandを送信 (adb shell "am broadcast -a android.intent.action.RUN -e cmd　'XXXX')
- 実機からSavedフォルダを取得 (adb pull /mnt/sdcard/UE4Game/XXX/XXX/Saved D:/XXX/XXX/Adb/XXX)
- UE4CommandLine.txtを実機に送信 (adb push D:/XXX/XXX/Adb/UE4CommandLine.txt /mnt/sdcard/UE4Game/XXX/UE4CommandLine.txt)
- アプリ起動 (adb shell am start -n com.XXX.XXX/com.epicgames.ue4.SplashActivity  )
- パッケージインストール (adb install -r )
- パッケージアンインストール (adb uninstall com.XXX.XXX )
- Wifi接続準備 (adb tcpip 5555)
- Wifi接続開始 (adb connect)
- Wifi接続終了 (adb disconnect)
- adbコマンド 自由記述 (adb)
- shellコマンド 自由記述 (adb shell)
 
# 使用方法
1. Plugins/AdbCommandEditorWidget を プロジェクトの Pluginsフォルダに移動
1. エディタのPluginsからAdbCommandEditorWidgetを有効に
1. コンテンツブラウザのView OptionsのShow Plugin Contentを有効に
1. /AdbCommandEditorWidget/AdbCommandWidgetSample を開く

## 作者
[@pafuhana1213](https://twitter.com/pafuhana1213)

## License
[MIT](https://github.com/pafuhana1213/AdbCommandWidgetSample/blob/master/LICENSE)
