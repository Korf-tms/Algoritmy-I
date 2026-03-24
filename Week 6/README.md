## Bruteforce

Řešení úplným prohledáváním.
Stavový prostor obchodního cestujícího identifikován jako prostor permutací a prozkoumán skrze `std::next_permutation`.
Stavový prostor batohu identifikován jako množina všech podmnožin a prozkoumán skrze jejich poctivé vygenerování.
Stojí za rozmyšlení, jak tenhle problém řešit reorganizací na průchod šikovně zvoleného grafu.