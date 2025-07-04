# dicionario_eda

Resumo:
Neste trabalho será desenvolvido um contêiner associativo do tipo dicionário (map), implementado de quatro formas distintas com o uso de diferentes estruturas de dados genéricas: Árvores Binárias AVL e Rubro-Negra, e Tabelas Hash com tratamento de colisões por encadeamento exterior e endereçamento aberto. A aplicação lê um arquivo .txt, processa todas as palavras e constrói uma tabela de frequência ordenada em um novo arquivo para análise. Além disso, métricas como número de comparações, quantidade de rotações e colisões também são coletadas para a avaliação do desempenho das estruturas.

Descrição:
Este projeto tem como objetivo desenvolver uma aplicação em C++ capaz de ler um arquivo no formato '.txt' e gerar um novo arquivo contendo uma tabela das palavras encontradas, junto com sua frequência de aparições, ordenadas em ordem alfabética, o programa também deve realizar o devido tratamento das strings, desconsiderando pontuações, acentos e distinções entre letra maiúsculas e minúsculas. 

Para armazenar as palavras e suas respectivas frequências, será necessário implementar dicionários, com quatro estruturas de dados distintas: árvore AVL, árvore Rubro-Negra, Tabela Hash com tratamento de colisões por encadeamento exterior e Tabela Hash com tratamento de colisões por endereçamento aberto. Cada uma delas deve ser desenvolvida de forma genéricas, por meio de templates e seguindo os princípios da programação orientada a objetos, com o uso de classes, métodos públicos e privados. 

Tanto os dicionários quanto suas respectivas estruturas implementam  funções fundamentais, como criação, inserção, atualização, acesso, remoção, verificação de existência, obtenção do tamanho e limpeza, além das funções específicas de cada uma que garantem seu funcionamento interno. 

A única exceção que foge à regra da generalidade, são as métricas de contagem, como os contadores de comparação de chave, rotações, colisões, dentre outro específicos que possuem o objetivo de comparar e analisar o desempenho entre as estruturas.
