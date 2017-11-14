// NReinas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <queue>
using namespace std;

// =============================================================================
// ALUMNOS =====================================================================
// =============================================================================

char* NomAlumne1 = "Nil";
char* CognomsAlumne1 = "Domene Esteban";
char* NIAAlumne1 = "1425988"; // NIA alumno1

							  // No replenar en cas de grup de un alumne
char* NomAlumne2 = "Diego";
char* CognomsAlumne2 = "Velazquez Dorta";
char* NIAAlumne2 = "1429086"; // NIA alumne2

char* NIAS[] = {
	"1335167","1428136","1397750","1390855","1424739","1424670","1423739",
	"1423177","1427371","1423725","1448752","1423210","1391968","1424454",
	"1338429","1425988","1424818","1421980","1368533","1365501","1423802",
	"1175542","1264719","1424801","1423710","1390452","1424116","1391795",
	"1395085","1391630","1424310","1423234","1425968","1307828","1395062",
	"1426532","1391627","1366098","1425082","1325835","1425067","1424350",
	"1424035","1391544","1391634","1426771","1424698","1358835","1362219",
	"1425785","1424114","1424408","1362389","1428260","1391808","1425084",
	"1366706","1391632","1425109","1424032","1430970","1430896","1428176",
	"1390536","1429086","1423588","1195650","1424671","1306347"
};

bool CheckNIA(char* nia)
{
	for (const char *pNIA : NIAS) {
		if (strcmp(nia, pNIA) == 0) return true;
	}
	return false;
}

// =============================================================================
// PROBLEMA ====================================================================
// =============================================================================

// Clock =======================================================================

double Clock()
{
	LARGE_INTEGER cnt;
	LARGE_INTEGER fre;

	if (QueryPerformanceFrequency(&fre) && QueryPerformanceCounter(&cnt)) {
		return (double)cnt.QuadPart / (double)fre.QuadPart;
	}
	else return (double)clock() / (double)CLOCKS_PER_SEC;
}
//new class defined
class Solution {
public:
    int n;
    int total;
    // check feasibility incrementally
    // C: new pos 
    // solution[0] ~ solution[C-1] is feasible
    // check feasiblity after add solution[C]
    inline bool is_feasible_incr(const vector<int> &solution, const int &C) {
        for (int c = 0; c < C; ++c)
            if(solution[c]==solution[C] || abs(solution[C]-solution[c])==C-c)
                return false;
        return true;
    }
    // without & : 52ms use copies of `solution `
    // with &    : 16ms no copy, inplace
    void solve(vector<int> &solution, int C) {
        // solution[C] : not checked
        if(C==n) {
            total++;
            return;
        }
        else { // branch
            for (int r = 0; r < n; ++r) {
                solution[C]=r;
                if(is_feasible_incr(solution, C))
                    solve(solution, C+1);
            }
            return;
        }
    }
    int totalNQueens(int n) {
        total = 0;
        this->n=n;
        vector<int> solution(n);
        solve(solution,0);
        return total;
    }
};

// main ========================================================================

int main(int argc, char *argv[])
{
	if (!CheckNIA(NIAAlumne1) || !(*NIAAlumne2 == '\0' || CheckNIA(NIAAlumne2))) {
		puts("Indentificacio dels alumnes incorrecte");
		return 1;
	}
	printf("NIA1: %s\n", NIAAlumne1);
	printf("NOM1: %s\n", NomAlumne1);
	printf("COGNOMS1: %s\n", CognomsAlumne1);
	printf("NIA2: %s\n", NIAAlumne2);
	printf("NOM2: %s\n", NomAlumne2);
	printf("COGNOMS2: %s\n", CognomsAlumne2);
	if (argc != 2) {
		puts("Us: NReinas N\n");
		return 1;
	}
	int n = atoi(argv[1]);
	printf_s("PARAMETRE N=%d\n", n);
	printf_s("Col.locar %d reines en un taulell de %dx%d\n", n, n, n);
	bool **pTablero = new bool*[n];
	for (int i = 0; i < n; ++i) {
		bool *pFila = new bool[n];
		for (int j = 0; j < n; ++j) pFila[j] = false;
		pTablero[i] = pFila;
	}
	double t0 = Clock();
	// -------------------------------------------------------------------------
	// Afegir aquí el codi que soluciona NReines o crida a funció
	// Posar a true les posicions de les reines a pTablero[i][j]
	Solution s; 
    cout<<s.totalNQueens(n)<<endl;

	// -------------------------------------------------------------------------
	double t1 = Clock();
	printf("TEMPS: %lf\n", t1 - t0);
	puts("SOLUCIO:");

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) if (pTablero[i][j]) putchar('X'); else putchar('.');
		putchar('\n');
		delete[] pTablero[i];
	}
	delete[] pTablero;
	return 0;
}