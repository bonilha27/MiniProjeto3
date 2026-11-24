# MiniProjeto3
Sistema de Gerenciamento de Estoque

Projeto desenvolvido em linguagem C, com o objetivo de realizar o gerenciamento de produtos e o controle de estoque por meio de menus interativos no terminal.

O programa possui três módulos principais:

Gerenciamento de estoque: permite cadastrar, editar, remover e listar produtos, identificar o produto mais caro e o mais barato, buscar produtos pelo nome, ordenar por preço, verificar produtos com estoque baixo, consultar o total de unidades e identificar produtos sem estoque.

Entrada e saída de produtos: permite registrar o recebimento e a retirada de mercadorias, atualizando automaticamente as quantidades disponíveis e impedindo saídas superiores ao estoque existente.

Histórico de movimentações: registra as entradas e saídas realizadas, permite consultar o histórico completo, gerar relatórios separados por tipo de movimentação e limpar os registros.

Cada produto possui nome, quantidade, valor unitário, código de identificação e estoque mínimo. Os códigos são gerados automaticamente pelo sistema.

Os dados são armazenados em arquivos .txt, permitindo preservar as informações do estoque e o histórico de movimentações entre diferentes execuções do programa.

Tecnologias utilizadas:

Linguagem C;

Biblioteca stdio.h;

Biblioteca stdlib.h;

Biblioteca string.h;

Biblioteca time.h;

Manipulação de arquivos;

Estruturas (struct);

Alocação dinâmica de memória.

O projeto foi desenvolvido com o propósito de praticar conceitos fundamentais da programação em C, aplicando estruturas de dados, funções, ponteiros, alocação dinâmica, manipulação de arquivos e organização de programas em módulos.
