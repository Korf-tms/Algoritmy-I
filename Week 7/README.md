## Průchod grafem do šířky a do hloubky

Implementace nejjednodušších průchodů grafem do šířky a do hloubky, pouze pro vypsání dosažitelných vrcholů a určení počtu komponent.
Srovnejte s obecnějším přístupem prezentovaným na přednášce, obvzláště okamžiky, kdy vrcholy grafu odcházejí ze stacku/fronty.

Zvolená implementace grafu je ta nejjednodušší, neuvažujeme přidávání nebo odebíraní vrcholů ani hran.
Vrcholy jsou reprezentované čísly, obecně bychom asi potřebovali `struct Node` a pointery na jednotlivé nody.
Uvažované grafy jsou dokonce číslované od `0` do `|V|-1`, tím je vše ještě jednodušší.

![Testovací graf ze `main.cpp` — dvě komponenty](graph.png)

