# dicionario_eda

### Compilação do projeto:
O projeto já possui um 'Makefile' configurado para compilação funciona tanto em Windows como em Linux. Para compilar no terminal, basta estar na raiz do projeto, onde o makefile se encontra, e executar o comando `make all` que irá gerar um executável `./freq` para uso do programa.

NOTA: O makefile possui mais dois comandos o `make teste` que irá gerar e executar o teste dos dicionários que se encontra na pasta `tests_dictionary` e o comando `make clean` que apaga todos os executáveis gerados.

### Comando de Execução no Terminal:
Para executar o programa após a compilação basta usar o seguinte padrão no terminal:

`./freq [structure] [input].txt [output].txt`

#### structure:
- map_avl: Dicionário implementado com uma Árvore AVL;
- map_rbt: Dicionário implementado com uma Árvore Rubro-Negra;
- map_cht: Dicionário implementado com uma Tabela Hash com Encadeamento Exterior;
- map_oht: Dicionário implementado com uma Tabela Hash com Endereçamento Aberto;

Os arquivos de input se encontram na pasta `texts`, caso queira adicionar mais arquivos .txt para teste adicione nesta pasta. Já referente ao arquivo de output, após a execução do programa no terminal o arquivo contendo as tabelas estará na pasta `tables_texts`.

### Descrição:
Este projeto tem como objetivo desenvolver uma aplicação em C++ capaz de ler um arquivo no formato `.txt` e gerar um novo arquivo contendo uma tabela das palavras encontradas, junto com sua frequência de aparições, ordenadas em ordem alfabética, o programa também deve realizar o devido tratamento das strings, desconsiderando pontuações, acentos e distinções entre letra maiúsculas e minúsculas. 

Para armazenar as palavras e suas respectivas frequências, será necessário implementar dicionários, com quatro estruturas de dados distintas: árvore AVL, árvore Rubro-Negra, Tabela Hash com tratamento de colisões por encadeamento exterior e Tabela Hash com tratamento de colisões por endereçamento aberto. Cada uma delas deve ser desenvolvida de forma genéricas, por meio de templates e seguindo os princípios da programação orientada a objetos, com o uso de classes, métodos públicos e privados. 

Tanto os dicionários quanto suas respectivas estruturas implementam  funções fundamentais, como criação, inserção, atualização, acesso, remoção, verificação de existência, obtenção do tamanho e limpeza, além das funções específicas de cada uma que garantem seu funcionamento interno. 

A única exceção que foge à regra da generalidade, são as métricas de contagem, como os contadores de comparação de chave, rotações, colisões, dentre outro específicos que possuem o objetivo de comparar e analisar o desempenho entre as estruturas.
