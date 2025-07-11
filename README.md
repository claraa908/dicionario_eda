# dicionario_eda

O parâmetro de linha de comando usado no terminal

`./main [structure] [input].txt [output].txt`

structure:
- map_avl: Dicionário implementado com uma Árvore AVL;
- map_rbt: Dicionário implementado com uma Árvore Rubro-Negra;
- map_cht: Dicionário implementado com uma Tabela Hash com Encadeamento Exterior;
- map_oht: Dicionário implementado com uma Tabela Hash com Endereçamento Aberto;


### Descrição:
Este projeto tem como objetivo desenvolver uma aplicação em C++ capaz de ler um arquivo no formato `.txt` e gerar um novo arquivo contendo uma tabela das palavras encontradas, junto com sua frequência de aparições, ordenadas em ordem alfabética, o programa também deve realizar o devido tratamento das strings, desconsiderando pontuações, acentos e distinções entre letra maiúsculas e minúsculas. 

Para armazenar as palavras e suas respectivas frequências, será necessário implementar dicionários, com quatro estruturas de dados distintas: árvore AVL, árvore Rubro-Negra, Tabela Hash com tratamento de colisões por encadeamento exterior e Tabela Hash com tratamento de colisões por endereçamento aberto. Cada uma delas deve ser desenvolvida de forma genéricas, por meio de templates e seguindo os princípios da programação orientada a objetos, com o uso de classes, métodos públicos e privados. 

Tanto os dicionários quanto suas respectivas estruturas implementam  funções fundamentais, como criação, inserção, atualização, acesso, remoção, verificação de existência, obtenção do tamanho e limpeza, além das funções específicas de cada uma que garantem seu funcionamento interno. 

A única exceção que foge à regra da generalidade, são as métricas de contagem, como os contadores de comparação de chave, rotações, colisões, dentre outro específicos que possuem o objetivo de comparar e analisar o desempenho entre as estruturas.
