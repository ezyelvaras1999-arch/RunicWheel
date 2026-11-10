# Runic Wheel LE — miniatura temporária associada ao FormID

M3, com o Inventário aberto e o cursor sobre um item, solicita uma miniatura do render 3D que o próprio inventário está a mostrar. O plugin associa uma miniatura de 128×128 ao FormID e mantém até 24 miniaturas apenas em memória (cerca de 1,5 MB de textura no máximo). Não grava BMPs nem mantém capturas completas no disco. M1 continua a guardar o item/FormID no slot selecionado; quando um slot contém o FormID em cache, o wheel desenha a miniatura sobre o ícone. M2 remove o item do slot.

A miniatura vem do limite verificado entre o render Scaleform do inventário e o `Inventory3DManager::Render` do Skyrim LE. O bridge preserva o frame, limpa temporariamente o backbuffer, deixa o jogo renderizar o modelo 3D, lê os pixels em memória, recorta o modelo pelo fundo magenta temporário, restaura o frame original e cria a textura pequena. A extração e a textura são transitórias; nenhum ficheiro de imagem é escrito.

Se o modelo não aparecer no render naquela chamada, o plugin tenta novamente por alguns frames e não cria uma miniatura vazia. Um FormID sem miniatura continua a mostrar o ícone normal. O hook depende das verificações de vtable, bytes e destino de salto específicas do Skyrim LE 1.9.32.0.8; se alguma falhar, só a função de miniatura é desativada.

## Procedimento no jogo

1. Instala este build como mod separado no MO2 e desativa outras cópias da DLL Runic Wheel.
2. Usa um save descartável, abre o Inventário e aponta para uma arma ou armadura com modelo visível.
3. Pressiona M3 para abrir o wheel. Aguarda um instante para o render do inventário ser associado ao FormID.
4. Escolhe um slot e pressiona M1 para o guardar. A miniatura deve aparecer nesse slot. Pressiona M2 para remover o item e M3 para fechar o wheel.
5. Se não aparecer, envia `RunicWheelLE.log` e `RunicWheelLE-diagnostic.log`. Não é preciso enviar imagens BMP.

O workflow compila e publica o plugin; não executa Skyrim. A validação visual desta versão é feita no jogo pelo utilizador.
