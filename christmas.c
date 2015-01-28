#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Laponia{
int gift;
char type[20], city[20], dir;
};

struct sack{
int l,c;
};

typedef struct Laponia Lap;
typedef struct sack s;

Lap **a;
s *bag;

int n, m;

void sortcity (int nrstep)
{
//functia sortcity va sorta in ordine lexicografica dupa orase
	int k1, k2;
	for (k1 = 0; k1 <= nrstep - 1; k1++)
	{
		for (k2 = k1 + 1; k2 <= nrstep; k2++)
			if (strcmp (a[bag[k1].l][bag[k1].c].city, 
			a[bag[k2].l][bag[k2].c].city) > 0)
			{
				bag[k2].l ^= bag[k1].l;
				bag[k1].l ^= bag[k2].l;
				bag[k2].l ^= bag[k1].l;
				bag[k1].c ^= bag[k2].c;
				bag[k2].c ^= bag[k1].c;
				bag[k1].c ^= bag[k2].c;
			}
	}
}
void sort_apparition_type (int start, int contor)
{
//functia va sorta dupa nr de aparitii, iar apoi in ordine lexicografica
//dupa tipul de cadou
	int countertype = start, k, app, pos, max, i, k1, k2; 
	int subst1, subst2, wehavegifts;
	Lap **b;
	//creeaza o copie dupa matrice, pentru a o putea modifica in momentul
	//in care se vor numara numarul de aparitii ale cadourilor
	b = (Lap**)malloc (n * sizeof (Lap*));
	for (k = 0; k < n; k++)
		b[k] = (Lap*)malloc (m * sizeof(Lap)); 
	wehavegifts = 0;
	for (k = start; k <= contor; k++)
		if(a[bag[k].l][bag[k].c].gift != 0) 
		{	
			wehavegifts = 1;
			break;
		}
	//procesul va continua doar in cazul in care avem cadouri
	if (wehavegifts == 1)
	{
		printf ("%s:\n", a[bag[countertype].l][bag[countertype].c].city);
		while (countertype <= contor)
		{
			for (i = 0; i < n; i++)
				for (k = 0; k < m; k++)
				{
					b[i][k].gift = a[i][k].gift;
					strcpy (b[i][k].type, a[i][k].type);
				}
			max = -1;
			for (k1 = countertype; k1 <= contor; k1++)
			{
				app = 0;
				for (k2 = countertype; k2 <= contor; k2++)
				if (strcmp (b[bag[k1].l][bag[k1].c].type, 
				b[bag[k2].l][bag[k2].c].type) == 0 && 
				b[bag[k2].l][bag[k2].c].gift > 0)
				{
					app++;
					b[bag[k2].l][bag[k2].c].gift--;
				}
				if (max < app)
				{
				//memoreaza numarul maxim de aparitii
					max = app;
					pos = k1;
				}
				else if (max == app)
				{
					if (strcmp (b[bag[pos].l][bag[pos].c].type, 
					b[bag[k1].l][bag[k1].c].type) > 0)
					{
						pos = k1;
					}
				}
				

			}
			i = 1;
			//face interschimbarile, grupand cadourile de acelasi 
			//tip la inceputul secventei
			if (countertype != contor)
			{
				k1 = countertype;
				i = 0;
				subst1 = bag[pos].l;
				subst2 = bag[pos].c;
				while (k1 <= contor && countertype + i <= contor)
				{
					if (strcmp (b[bag[countertype + i].l]
					[bag[countertype + i].c].type, 
					b[subst1][subst2].type) == 0)
						i++;
					else
					{
						if (strcmp (b[bag[k1].l][bag[k1].c].type,
						b[subst1][subst2].type) == 0 
						&& (k1 > countertype+ i))
						{
							bag[k1].l ^= bag[countertype + i].l;
							bag[countertype + i].l ^= bag[k1].l;
							bag[k1].l ^= bag[countertype + i].l;
							bag[k1].c ^= bag[countertype + i].c;
							bag[countertype + i].c ^= bag[k1].c;
							bag[k1].c ^= bag[countertype + i].c;
							i++;
						}
						k1++;
					}
				}
			}
			if (max)
				printf ("  %d %s\n", max, 
				b[bag[countertype].l][bag[countertype].c].type);
			countertype += i; 
		}
	}
	for (i = 0; i < n; i++)
		free(b[i]);
	free(b);
}

void sortapparition (int nrstep) 
{
	int contor = 0, start = 0, ok = 1;
	while (contor <= nrstep )
	{
		if (ok == 0) 
		{
			start = contor;
		}
		
		if (contor + 1 <= nrstep && strcmp (a[bag[contor].l][bag[contor].c].city, 
		a[bag[contor + 1].l][bag[contor + 1].c].city) == 0)
		{
			contor++;
			ok = 1;
			continue;
		}
		//sortare dupa nr de aparitii, 
		//in ordine lexicografica in caz de egalitate
		sort_apparition_type (start, contor);
		if (nrstep == 0) break;
		ok = 0;
		contor++;
	}
}

void travel (int step, int lin, int col, int N, int M)
{
	int k, nrstep = 0, k1, nrgift = 0, i, doubleit = 2;
	char next;
	s* newbag;
	Lap **b;
	while (nrstep <= step)
	{
		//se expandeaza sacul, daca e nevoie
		if (nrstep % doubleit == 0 && nrstep > 0)
			 {
			 	doubleit *= 2;
			 	newbag =  (s*)realloc (bag, doubleit * sizeof(s));
			 	if (newbag != NULL)
			 		bag = newbag;
			 	else exit (1);
			 }
		bag[nrstep].l = lin;
		bag[nrstep].c = col;
		next = a[lin][col].dir;
		if (next == 'U') lin--;
		if (next == 'D') lin++;
		if (next == 'L') col--;
		if (next == 'R') col++;
		if (lin > N-1 || lin < 0 || col > M - 1 || col < 0)
			break;
		else nrstep ++;
	}
	if (nrstep > step) nrstep--;
	if (nrstep < step) printf ("TOO MUCH SNOW !\n");
	//facem o copie dupa matrice, pentru a numara numarul total de
	//cadouri
	b = (Lap**)malloc (n * sizeof (Lap*));
	for (k = 0; k < n; k++)
		b[k] = (Lap*)malloc (m * sizeof(Lap));
	for (i = 0; i < n; i++)
		for (k = 0; k < m; k++)
		{
			b[i][k].gift = a[i][k].gift;
		}
	for (k1 = 0; k1 <= nrstep; k1++)
		if (b[bag[k1].l][bag[k1].c].gift != 0) 
		{
			nrgift++;
			b[bag[k1].l][bag[k1].c].gift--;
		}
	for (i = 0; i < n; i++)
		free(b[i]);
	free(b);	
	printf ("%d\n%d\n", nrstep, nrgift);
	sortcity (nrstep);
	sortapparition (nrstep);	
}
		
int main()
{
	int x, y, pas, i, j;
	scanf ("%d%d", &n, &m);
	scanf ("%d%d", &x, &y);
	scanf ("%d", &pas);
	bag = (s*)malloc (2 * sizeof(s));
	a = (Lap**)malloc (n * sizeof(Lap*));
	for (i = 0; i < n; i++)
		*(a + i) = (Lap*) malloc (m * sizeof(Lap));
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
		{
			scanf("%s%s%d %c", a[i][j].city, a[i][j].type, &a[i][j].gift, &a[i][j].dir);
		}
	travel (pas, x, y, n, m);
	free(bag);
	free(a);
	return 0;
}			
