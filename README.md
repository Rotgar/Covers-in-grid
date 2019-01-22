# Covers-in-grid

**Analiza algorytmów**

**Zad. 12 Stacje BTS** - problem polega na tym, że na wejściu dostajemy tablicę dwuwymiarową wypełnioną * oraz o, w której należy pokryć wszystkie *, gdzie możemy to zrobić za pomocą "prostokątów wielkości 1x2", czyli dwie kolejne komórki tablicy pionowo lub poziomo, albo zaznaczać * pojedynczo. Należy znaleźć najmniejszą liczbę takich pokryć, aby każda * nalezała do co najmniej jednego pokrycia.

Program możemy skompilować poleceniem make, a następnie uruchomić za pomocą ./cover w następujacych trybach:

1. Dajemy na wejście dane z pliku .txt, w którym znajduje sie tablica jak w treści zadania wypełniona, np. w następujący sposób:
   
   3 4  
   \* o * o  
   o * * o  
   \* * * o  

   gdzie 3 oznacza liczbę wierszy, a 4 liczbę kolumn. Wszystkie elementy muszą być oddzielone spacjami.
   Uruchamiamy go wtedy jako:
   
   **./cover -m1 < dane.txt**            - wyświetli rozwiązanie na w terminalu, lub można podać je do pliku, np.  
   **./cover -m1 < dane.txt > out.txt**  - zapisze wynik w pliku out.txt


2. Tablica zostaje w*ygenerowana losowo. Jako argumenty programu podajemy kolejno właściwe flagi a po nich liczbę wierszy, kolumn tablicy, a jako ostatni pokrycie jakie ma posiadać ta tablica. Flagi -n, -m, -k odzielone spacją od wartości:
 
  **./cover -m2 -n n -m m -c cov**
    
   , np.  
   **./cover -m2 -n 10 -m 10 -c 7**    - wygeneruje losowo tablicę 10x10, w której pokrycie wynosi 7. Wygenerowana tablica zostanie pokazana na wyjściu, a poniżej rozwiązanie uzyskane przeprowadzonym na niej algorytmem. Powinno zwrócić wartość 4 argumentu, czyli 7.


3. Trzecia opcja generuje losowo tablice i wykonuje na nich cały algorytm w celach pomiarowych. Na końcu wyświetlona tabelka jak w wymaganiach.
 
   **./cover -m3 -n n -m m -c cov -k k -step step -r r**  
    gdzie 
	n - wiersze, m - kolumny
	cov - pokrycie jakie mają posiadać generowane tablice	
	k - liczba iteracji
	step - krok o jaki zwiekszamy n oraz m, w kolejnych iteracjach
	r - liczba powtórzeń dla konkretnych n oraz m

  Przykładowo: **./cover -m3 -n 300 -m 300 -c 400 -k 10 -step 100 -r 10** - tworzy tablice zaczynająć od 300x300(r=10 razy), zwiększając je o step=100 w   	 każdej iteracji od 0 do k=10.
  Najlepiej ograniczyć rozmiary tworzonych tablic tak, by nie wykraczały w kolejnym iteracjach powyżej 4000( m oraz n w kolejnych krokach).
  Podawać cov tak by nie wykraczał poza n*m/2, gdyż nie da się zrobić większej liczby rozwiązań. W dodatku wartości w okolicach n*m/2 sprawią, że      	 program zadziała z pesymistyczną złożonością, co dla dużych tablic moze zająć bardzo długo. Najlepiej podawać cov tak by był w okolicach 
  <1/4, 3/4>*n*m.  
  

Rozwiązanie polega na przedstawieniu danych tablicy w postaci grafu dwudzielnego. Następnie wyliczany zostaje max-matching stworzonego grafu, który pomoże obliczyć liczbę pokryć, a będzie ona równa V - Max, gdzie V to liczba wierzchołków, a Max - max matching wyliczony za pomocą algorytmu.

Max matching wyliczony zostaje za pomocą zaimplementowanego algorytmu Hopcroft-Karp. W implementacji wykorzystane zostają funkcje BFS(breadth-first search) oraz DFS(depth-first search). Graf reprezentowany jest za pomocą jednokierunkowej listy dynamicznej, której kolejne komórki też są listami i przechowują odpowiednio informacje o wierzchołkach, które są połączone krawędzią. Poza tym wykorzystany został pomocniczo kontener query. Inne informacje i dane w plikach przechowywane są w dynamicznie alokowanych tablicach, jedno lub dwu wymiarowych.

Dekompozycja:
Program składa się z następujących plików składowych:
main.cpp - plik główny, zawiera wczytywanie z pliku, uruchamianie odpowiednich trybów, itp.

cover.h, cover.cpp - plik nagłówkowy i źródłowy, zawierają funkcje tworzące graf oraz uruchamiające algorytm i wyliczające wynik programu 

graph.h, graph.cpp - plik nagłówkowy i źródłowy, w którym zaimplementowana została klasa grafu Graph, posiadająca metodę będącą zaimplementowanym algorytmem Hopcorfta-Karpa o nazwie matching(),

generator.h, generator.cpp - plik nagłówkowy i źródłowy, z zaimplementowanym generatorem. Tworzony jest za pomocą funkcji generate(), która przyjmuje jako argumenty n - liczba wierszy, m - liczba kolumn, k - minimalne pokrycie w tworzonej tablicy, l - długość pojedynczego pokrycia, równe 2 

timer.h - plik nagłówkowy zawierający implementację timera mierzącego czas wykonania algorytmu

