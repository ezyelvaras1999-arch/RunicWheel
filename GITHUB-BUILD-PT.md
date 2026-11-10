# Compilar o build v0.26 FormID memory preview no GitHub

1. Envia para a raiz do repositório os ficheiros do projeto, incluindo a pasta oculta `.github`.
2. Faz commit/push para `main` ou `master`, ou inicia manualmente **Build Runic Wheel LE v0.26 FormID memory preview** em Actions.
3. Quando o workflow terminar, descarrega `RunicWheelLE-v026-formid-memory-preview` em **Artifacts**.
4. Extrai o artifact e instala a DLL, INI e quatro texturas `.rwtx` como mod separado no MO2.

O workflow prepara MSVC x86 no runner Windows e descarrega a fonte SKSE LE 1.7.3 do site oficial para satisfazer as dependências de build. Ele não executa Skyrim nem valida o desenho no jogo. Segue `PREVIEW-PROBE.md` para o teste visual.

Para esta atualização, substitui apenas os ficheiros listados no patch fornecido; mantém os restantes ficheiros do repositório.
