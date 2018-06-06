0. 動作環境
  OS            : RHEL6.6
  CarbonGnuTools: Gcc422
  SoCDesigner   : 7.12.2

1. ディレクトリ構成
  trunk/
   |-- 01_Model/
   |    |-- DummyGraphicsMacroModel/ ........................  ダミー画像マクロモデル格納ディレクトリ
   |    |-- DummyGraphicsMacroModelWrapper/ .................  ダミー画像マクロモデルSoCDラッパー基本クラス格納ディレクトリ
   |    `-- BufferlessModel/ ................................  BufferlessModelモデル格納ディレクトリ
   |         |-- src/
   |         |    |-- BufferlessModel.cpp ...................  BufferlessModelモデルラッパーソースファイル
   |         |    |-- BufferlessModel_AXI_Master_Port.cpp ...  BufferlessModelモデル用AXIv2トランザクタソースファイル
   |         |    |-- BufferlessModel_wrapperbase.cpp .......  BufferlessModelモデルラッパーベースクラスソースファイル
   |         |    `-- BufferlessModel_Scenario.cpp ..........  BufferlessModelモデルシナリオソースファイル
   |         `-- include/
   |              |-- BufferlessModel.h .....................  BufferlessModelモデルラッパーヘッダファイル
   |              |-- BufferlessModel_AXI_Master_Port.h .....  BufferlessModelモデル用AXIv2トランザクタヘッダファイル
   |              |-- BufferlessModel_wrapperbase.h .........  BufferlessModelモデルラッパーベースクラスヘッダファイル
   |              `-- BufferlessModel_Scenario.h ............  BufferlessModelモデルシナリオヘッダファイル
   |
   `-- 10_Build/
        `-- UnitTest/
             `-- BufferlessModel/ ................................  BufferlessModelモデル単体テスト環境格納ディレクトリ
                  `-- Developpers/
                       |-- BufferlessModel_buffer_parameter.csv ..  内部バッファパラメータファイル
                       |-- Makefile ..............................  単体テスト環境Makefile
                       |-- Project.mxp ...........................  SoCDプロジェクトファイル
                       |-- README.txt ............................ 本テキスト
                       |-- maxlib.conf ...........................  BufferlessModelモデルライブラリコンフィグファイル
                       |-- run_sdsim.sh ..........................  単体テスト実行スクリプト
                       |-- setup.sh ..............................  環境設定ファイル
                       |-- axi_slave/ ............................  対向スレーブモデルビルド環境
                       `-- script/ ...............................  SoCDスクリプト格納ディレクトリ


2. モデル構成
                             model_id : 0
                              AXI I/F : 1
                            interrupt : 4
                               output : 4
                  input_buffer_number : 0
  input_internal_buffer_number[0]~[7] : 0
                 output_buffer_number : 0
                          fifo_number : 1

3. 実行手順
  3.1. 環境設定
    以下のコマンドを実行します。
       $ source ${CARBON_GNU_TOOLS_INST_DIR}/Gcc422/etc/setup.sh
       $ cd trunk/10_Build/UnitTest/BufferlessModel/Developpers
       $ source setup.sh

  3.2. ビルド
    以下のコマンドを実行します。
      $ make

    ビルドが完了すると、以下のライブラリファイルが生成されます。
      libBufferlessModel.so

  3.3 axi_slaveのビルド
    3.3.1 axi_slaveディレクトリに移動します
      $ cd axi_slave

    3.3.2 コンパイルします
      $ ./cbuild.sh

    3.3.3 必要ファイルを準備します
      $ ./build_socd.sh

    3.3.4 ModelStudioでコンパイルします
      $ modelstudio Project2/Project2.carbon
        ([Compile]ボタン押下->コンパイル終了後->File->Exit)

  3.3. 実行
    以下のコマンドを実行します。
      $ run_sdsim.sh

    実行が完了すると、以下のファイルが生成されます。
      BufferlessModel.vcd .................. SoCD波形ファイル


  memo
    axi_slaveのwreadyは、sdsimでシミュレーション停止中に、
    モデルのwready_outパラメタをfalse, trueに変更することで制御できます。
    スクリプトで実行する場合、script/sdsim.mxscrのsetParameterのfalse, trueを
    変更することで制御可能です。

