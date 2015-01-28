README

Fisiere incluse:

christmas.c
README
Makefile

Toate fisierele sunt comprimate intr-o arhiva ZIP, care cuprinde fisierele sursa, acest README si un makefile cu doua reguli (build si clean), cu ajutorul carora se vor compila fisierele sursa rezultate, intr-un executabil (allocator) si se va sterge, la apel, fisierul executabil.

In implementarea problemei, am creat doua structuri, una pentru sacul lui Mos Craciun si cealalta pentru harta Laponiei, iar sacul va fi alocat dinamic, conform mentiunilor, acceptand pe rand 4 orase, apoi 8 s.a.m.d. Apoi am creat o functie numita "travel", care va parcurge harta Laponiei conform numarului de pasi dat la intrare si conform indicatiilor prezente in cadrul fiecarei regiuni. Astfel, cu ajutorul acestei functii, se vor inmagazina in sacul Mosului cadouri, inregistrate, de fapt, sub forma coordonatelor acestora in matrice (linie si coloana, adica), pana la terminarea numarului de pasi.

Pe langa functia travel, mai exista alte doua functii care vor rula in cadrul functiei travel (sortapparition si sort_apparition_type) si care vor sorta coordonatele din sacul Mosului in functie de ordinea lexicografica a oraselor, numarul de aparitii al cadourilor etc. Astfel, in sacul Mosului va exista o secventa, ale carei componente vor indica catre orasele "BUCHAREST BUCHAREST BUCHAREST", ceea ce semnifica faptul ca sania Mosului va trebui sa livreze 3 cadouri in orasul Bucuresti. Functia sortcity se va ocupa cu aranjarea lexicografica a oraselor corespunzatoare coordonatelor din sac, ca mai apoi functia sortapparition sa fie apelata pentru a determina secventele similare cu cea de mai sus, iar, in final, functia sort_apparition_type va fi apelata pentru fiecare secventa succesiva de tipul celei de mai sus, pentru a ordona in functie de numarul de aparitii si, respectiv, lexicografic dupa tipul cadourilor.

In ceea ce priveste problemele tehnice, am evitat apelarea functiilor amintite mai sus pentru cazuri speciale, precum acela in care numarul cadourilor este nul, folosind o variabila "wehavegifts", care va determina prezenta cadourilor in cadrul unui ciclu "for". O alta problema esentiala a aparut in cadrul unei conditii if: 	if (contor + 1 <= nrstep && strcmp (a[bag[contor].l][bag[contor].c].city, a[bag[contor + 1].l][bag[contor + 1].c].city) == 0). In acest caz, ordinea este cea corecta, dar, initial, conditia a doua era evaluata prima si, ca atare, contor +1 depasea valoarea variabilei nrstep, rezultat intr-o eroare de tipul "Segmentation fault".
