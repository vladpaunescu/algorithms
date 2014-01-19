Problema cerea determinarea numarului de drumuri de la un punct 
(start_x, start_y) dintr-o matrice pana la un punct (end_x, end_y) 
din aceeasi matrice, drum care sa aiba cel mult K pasi. 
Problema se rezolva usor folosind metoda programarii dinamice.
Vom folosi o matrice tridimensionala unde num_waysi,j,k are semnificatia:
numarul de drumuri ce incep in (start_x, start_y), 
se termina in (i, j) si au fix k pasi.
 Solutia se va afla in num_waysend_x,end_y,0 + num_waysend_x,end_y,1 + ... + 
num_waysend_x,end_y,K. 
Formula de recurenta pentru problema este usor de determinat:
num_waysi,j,k = num_waysi+1,j,k-1 + num_waysi-1,j,k-1 +
 num_waysi,j-1,k-1 + num_waysi,j+1,k-1.
 Se observa ca pentru a determina valorile corespunzatoare lui k 
avem nevoie doar de valorile corespunzatoare lui k - 1, deci putem folosi doua matrici
 bidimensionale in loc de una tridimensionala. 
Complexitatea solutiei ca si timp este O(N * M * K) 
iar ca si spatiu este O(N * M).