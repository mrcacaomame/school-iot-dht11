# liboptions

## 概要
```
ソフトウェアを実行したときのオプション情報を簡単に操作できるようにするためのライブラリである
```

## 目次
1. [利用方法](#利用方法)
2. [利用例 (引数のオプションを取得する)](#利用例-引数のオプションを取得する)
3. [利用例 (実行ファイルパスの絶対パスを取得する)](#利用例-実行ファイルパスの絶対パスを取得する)

## 利用方法
**オプション情報を設定する**

```cpp
void Options::set(const int argc, char *argv[]) noexcept;
```
|引数|引数タイプ|指定してほしい値|
|:--|:--|:--|
|1|const int argc|オプションの配列の長さを指定する|
|2|char *argv[]|オプション情報を入れる|

<br>

**オプション情報を取得する (引数なし)**

```cpp
bool Options::getFlag (const uint8_t bar, const std::string &key) const noexcept;
```
|引数|引数タイプ|指定してほしい値|
|:--|:--|:--|
|1|const uint8_t|オプションの [-] の長さ|
|2|const std::string&|オプションのキーの情報|

|戻り値|説明|
|:--|:--|
|true|処理が正常に終了しました|
|false|指定されたオプションの長さとキーの長さに一致するものを見つけることができませんでした|

<br>

**オプション情報を取得する (引数あり)**

```cpp
bool Options::getValues (const uint8_t bar, const std::string &key, Options::Values &values) const noexcept;
```

|引数|引数タイプ|指定してほしい値|
|:--|:--|:--|
|1|const uint8_t|オプションの [-] の長さ|
|2|const std::string&|オプションのキーの情報|
|3|Options::Values&|指定したキーの引数の情報を取得する|

|戻り値|説明|
|:--|:--|
|true|処理が正常に終了しました|
|false|指定されたオプションの長さとキーの長さに一致するものを見つけることができませんでした|

<br>

**オプションに指定されていたファイルの現状パスから絶対パスを求める**

```cpp
bool Options::getAbsFilePath (std::string &file_path)const noexcept;
```

|引数|引数タイプ|指定してほしい値|
|:--|:--|:--|
|1|std::string&|取得したファイルパスを入れる変数|

|戻り値|説明|
|:--|:--|
|true|処理が正常に終了しました|
|false|オプションが設定されていないため取得することができませんでした|

<br>

**オプションに指定されていたファイルの現状パスからディレクトリパスを求める**

```cpp
bool Options::getAbsDirPath (std::string &directory_path)const noexcept;
```

|引数|引数タイプ|指定してほしい値|
|:--|:--|:--|
|1|std::string&|取得したディレクトリパスを入れる変数|

|戻り値|説明|
|:--|:--|
|true|処理が正常に終了しました|
|false|オプションが設定されていないため取得することができませんでした|

<br>

**情報をクリアする**

```cpp
void Options::clear (void) noexcept;
```
<br>

## 利用例 (引数のオプションを取得する)

```cpp
#include <liboptions/options.h>

int main (int argc, char *argv[]){
    bool flag;
    Options opt;
    Options::Values values;

    // オプション情報を入れる
    opt.set (argc, argv);

    // -h, --help のオプションがあるか確かめる
    flag = (opt.getFlag (1, "h") || opt.getFlag (2, "help"));
    if (flag){
        // オプションが含まれています
    }else{
        // オプションが含まれていません
    }

    // -f, --file のオプションがあるか確かめ、引数が指定されているかを確かめる
    flag = (opt.getValues (1, "f", values) || opt.getValues (2, "file", values));
    if (flag){
        // オプションが含まれています
        for (const Options::Value &value : values){
            // 引数をvalueで取得することができる

        }
    }

    return 0;
}
```

## 利用例 (実行ファイルパスの絶対パスを取得する)

```cpp
#include <liboptions/options.h>

int main (int argc, char *argv[]){
    bool flag;
    Options opt;
    Options::Values values;
    std::string abs_file_path;
    std::string abs_dir_path;

    // オプション情報を入れる
    opt.set (argc, argv);

    // 実行可能ファイルパスの絶対パスを取得する
    flag = opt.getAbsFilePath (abs_file_path);

    if (flag){
        // 取得に成功しました
    }else{
        // 取得に失敗しました
    }

    // 実行可能ファイルパスのディレクトリの絶対パスを取得する
    flag = opt.getAbsDirPath (abs_dir_path);

    if (flag){
        // 取得に成功しました
    }else{
        // 取得に失敗しました
    }

    return 0;
}
```