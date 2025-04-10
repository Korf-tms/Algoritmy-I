# Procházení do šířky jako bruteforce stavového prostoru

Dvě implementace řešení 8 puzzle, menší varianty [15 puzzle.](https://en.wikipedia.org/wiki/15_puzzle)
Řešení se hledá průchodem do šířky, sousední vrcholy stavového grafu jsou dané možnými pohyby v tabulce.

Jedna implementace reprezentuje stav jako vektor, druhá tabulku nejprve obalí speciální hodnotou `-1` a do vektoru převede až výsledek.
Tohle vede k rozdílné implementaci funkce, která generuje sousední stavy.
