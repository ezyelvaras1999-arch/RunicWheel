# Compilar o diagnóstico do callsite v0.26 no GitHub

1. Cria um repositório no GitHub e envia para a raiz todos os ficheiros desta pasta, incluindo a pasta oculta `.github`.
2. Faz commit/push para `main` ou `master`. O workflow também pode ser iniciado manualmente em **Actions → Build Runic Wheel LE v0.26 callsite diagnostic → Run workflow**.
3. Abre a execução em **Actions**. Se terminar com sucesso, descarrega `RunicWheelLE-v026-callsite-diagnostic` na secção **Artifacts**.
4. Extrai o artifact. Ele contém `RunicWheelLE.dll`, `RunicWheelLE.ini` e as quatro texturas `.rwtx`; instala-os como mod separado no MO2.

O workflow prepara o compilador MSVC x86 no runner Windows e descarrega a fonte SKSE LE 1.7.3 do site oficial do SKSE para satisfazer as dependências de build.

O workflow só compila e publica o artifact. Não executa Skyrim nem valida o modelo renderizado no jogo. Esta build serve para registar os bytes reais do callsite do InventoryMenu; segue `PREVIEW-PROBE.md` para instalar e enviar os dois logs de diagnóstico.
