## Průchod do šířky jako bruteforce

Ilustrace průchodu do šířky jako bruteforce algoritmu pro procházení stavového prostoru hlavolamu, v tomto případě [8/15-puzzle](https://en.wikipedia.org/wiki/15_puzzle).
Každý uzel představuje stav hlavolamu, a hrany grafu popisujicího stavový prostor představují možné tahy.
Průchod do šířky prohledává všechny uzly na stejné vzdálenosti od startovního stavu, než přejde k uzlům v další vzdálenosti.
Algoritmus zaručuje nalezení nejkratší cesty k řešení, ale může být velmi náročný na paměť, protože musí uchovávat všechny navštívené uzly v paměti.

K dispozici jsou dvě implementace `Puzzle`, jednou jako vektor vektorů a druhou jako jediný vektor, který reprezentuje stav řádek po řádku.
Rozhraní je plus mínus stejné, chtělo by to ještě vyladit konstruktory.

K držení informace o navštívených stavech se používá buď `unordered_set` nebo `set`.
`unordered_set` je interně implementavaná jako hashovací tabulka, pro kterou je potřeba definovat hashovací funkci pro `Puzzle`, zatímco `set` je implementován jako binární vyhledávací strom, který vyžaduje definici operátoru `<`.
Složitost operací vložení a hledání v `unordered_set` je průměrně O(1), zatímco v `set` je O(log n), stojí za to si vykoušet a porovnat obě implementace pro 15-puzzle.