# Compilar a prova v0.26 no GitHub

1. Cria um repositório no GitHub e envia para a raiz todos os ficheiros desta pasta, incluindo a pasta oculta `.github`.
2. Faz commit/push para `main` ou `master`. O workflow também pode ser iniciado manualmente em **Actions → Build Runic Wheel LE v0.26 preview → Run workflow**.
3. Abre a execução em **Actions**. Se terminar com sucesso, descarrega `RunicWheelLE-v026-preview` na secção **Artifacts**.
4. Extrai o ZIP do artifact. Ele contém `RunicWheelLE.dll` e `RunicWheelLE.ini`; instala-os como mod separado no MO2 para o teste.

O workflow prepara o compilador MSVC x86 no runner Windows e descarrega o arquivo de fonte SKSE LE 1.7.3 do site oficial do SKSE para satisfazer as dependências do script `build-v026.bat`. A opção `[Debug] CaptureInventoryPreview=1` grava a captura de diagnóstico; o procedimento está em `PREVIEW-PROBE.md`.

O workflow só compila e publica o artifact. Não executa Skyrim nem valida a captura dentro do jogo.
