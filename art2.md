# Resolver ou Verificar? Uma pergunta que vale um milhão de dólares
O artigo usa problemas de **teoria dos grafos** para mostrar a diferença entre **encontrar uma solução** e **verificar uma solução**.

O exemplo dado é o problema do vacinador: encontrar um circuito que passe por cada cidade exatamente uma vez e volte para a cidade inicial (lembra o problema do caixeiro viajante ein), isso corresponde ao **ciclo hamiltoniano**

Já o problema do pavimentador pede um circuito que percorra cada aresta/rodovia exatamente uma vez, esse é o **ciclo euleriano**

Ta mas, qual a diferença?

o problema do pavimentador tem uma caracteristica: um grafo possui um circuito euleriano <-> todos os seus vertices possuem grau par. Então bastaria verificar o grau de cada vértice, em vez de testar em força bruta todas as rotas possíveis, gostei que isso mostra a importância de encontrar uma propriedade matemática **necessária e suficiente**, em vez de buscar diretamente a solução entre uma quantidade gigante de possibilidades, é mais esperto verificar uma propriedade que diz se a solução existe

No problema do vacinador, a gente não conhece uma propriedade desse tipo que permita resolver o problema de forma eficaz, podemos tentar até a força bruta, mas como existem `n!` possibilidades, a busca é impraticável em tempo polinomial, entretanto, se alguém aparecer magicamente e entregar um possível circuito hamiltoniano, é fácil de verificar se ele realmente visita cada cidade uma única vez e se as cidades consecutivas tem uma estrada ligando-as

Isso dá a ideia de **solução difícil, verificação fácil**.

## Definições
- **Grafo:** estrutura formada por vértices e arestas que representam objetos e as conexões entre eles.
- **Vértice:** representa um elemento do problema, como uma cidade.
- **Aresta:** representa uma conexão entre dois vértices, como uma rodovia.
- **Grau:** quantidade de arestas que incidem sobre um vértice.
- **Ciclo hamiltoniano:** ciclo que visita cada vértice exatamente uma vez e retorna ao vértice inicial.
- **Ciclo euleriano:** ciclo que percorre cada aresta exatamente uma vez e retorna ao ponto inicial.
- **Condição necessária:** algo que precisa ser verdadeiro para que uma solução exista, mas que sozinho pode não ser suficiente para garantir a solução.
- **Condição suficiente:** algo que, se for verdadeiro, garante que a solução existe, mas que pode não ser necessário.
- **Condição necessária e suficiente:** uma propriedade que caracteriza exatamente quando uma solução existe.
- **Força bruta:** testar sistematicamente as possibilidades de solução. Pode ser inviável quando o número de possibilidades cresce muito rapidamente.
- **NP-completo:** problemas que estão em NP e são, informalmente, tão difíceis quanto qualquer problema de NP. Se um problema NP-completo puder ser resolvido em tempo polinomial, então P = NP.
- **P:** problemas que podem ser resolvidos em tempo polinomial.
- **NP:** problemas cujas soluções podem ser verificadas em tempo polinomial.

## Coisas que achei interessantes

O contraste entre os dois circuitos é muito bom, Euler conseguiu transformar um problema que parecia exigir procurar entre possibilidades em uma simples verificação de uma propriedade matemática. No caso do pavimentador, não precisamos descobrir o circuito para saber se ele existe, bastando verificar se todos os vértices possuem grau par.

Já no vacinador, podemos verificar rapidamente uma solução que alguém nos entrega, mas encontrar essa solução parece ser muito mais difícil.
O número de possibilidades também é absurdo, para `n` cidades, podemos ter aproximadamente `n!` possíveis circuitos. Para 92 cidades, `92!` já possui 143 algarismos.

Isso me lembra bastante a ideia do artigo anterior sobre crescimento exponencial, só que aqui aparece um crescimento fatorial, que é ainda mais brutal que o anterior.

E tem uma conexão que eu acho importante: um algoritmo eficiente não necessariamente precisa "procurar melhor", às vezes precisamos encontrar uma propriedade matemática que elimine quase todo o espaço de busca.
Para encontrar um ótimo global, às vezes precisamos explorar um espaço enorme de possibilidades. E uma solução local pode ser encontrada bemm mais rapidamente, mas sem garantia de que seja a melhor possível