# ATSPaco – Ant Colony Optimization for Asymmetric TSP

Projekt rozwiązuje rozszerzoną wersję problemu komiwojażera – **Asymmetric Traveling Salesman Problem (ATSP)** z uwzględnieniem **współrzędnych trójwymiarowych** oraz **zużycia paliwa** zależnego od różnicy wysokości między miastami.

---

## 📘 Opis

Rozszerzony problem ATSP uwzględnia:

- **Współrzędne 3D**: każde miasto ma wartości `(x, y, z)`, gdzie `z` oznacza wysokość nad poziomem morza,
- **Zużycie paliwa**: podróż "pod górę" kosztuje więcej, niż zjazd w dół,
- **Asymetria trasy**: trasa A → B niekoniecznie zużywa tyle samo paliwa co B → A.

🎯 **Cel**: Znalezienie najoptymalniejszej (najmniej paliwożernej) trasy między wszystkimi miastami.

---

## Algorytmy zaimplementowane

- **Greedy Algorithm** – wybiera kolejne miasta na podstawie minimalnego kosztu paliwa.
- **Brute-Force Algorithm** – sprawdza wszystkie możliwe permutacje tras (ekstremalnie kosztowny obliczeniowo).
- **Ant Colony Optimization (ACO)** – metaheurystyka inspirowana zachowaniem mrówek, poszukujących najkrótszej ścieżki do pożywienia.

---

## Generator danych

Projekt zawiera moduł generujący dane testowe:

- Konfigurowalna liczba miast,
- Zakres wartości współrzędnych `x`, `y`, `z`,
- Losowanie różnic wysokości między miastami.

Umożliwia szybkie tworzenie niestandardowych instancji problemu.

---

## 📊 Wizualizacja wyników

- Trasy przedstawiane w **3D** z wykorzystaniem bibliotek:
  - `matplotlib`
  - `mpl_toolkits.mplot3d`
- Kolorowe wizualizacje ułatwiają zrozumienie trasy oraz topografii.

---

## Dokładna dokumentacja
 - Dokładną dokumentację wraz z wynikami znaleźć można w pliku dokumentacja_sprawozdanie_pl.odt
