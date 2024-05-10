// Trabalho da disciplina de Algoritmos 3, ministrada pelo professor Jonas Lopes de Vilas Boas
// Alunos: Andre Augusto Coelho Silva, Henrique Oliveira Campello, Lucas  Ynoguti e Joao Vitor de Lucena

#include <iostream>
#include <algorithm> //transform
#include <string>
// #include <windows.h> //system
#include <list>
#include <climits>

using namespace std;

struct Pokemon
{
	int numero;
	string name;
	string tipo1;
	string tipo2;
	int x;
	int y;
};

struct edge
{
	int dest;
	int weight;
};

struct cidade
{
	int codigo;
	string nome;
	bool centro_pkm;
	list<edge> cidades_adj;
};

cidade cidades[10];
int qtd_cidades = 0;

Pokemon cadastro()
{
	Pokemon pokemon;
	cout << "Qual o numero do pokemon?" << endl;
	cin >> pokemon.numero;
	cout << "Qual o nome do pokemon?" << endl;
	getline(cin >> ws, pokemon.nome);
	cout << "Qual o tipo do pokemon" << endl;
	getline(cin >> ws, pokemon.tipo);
	cout << "Qual a localização do pokemon? (x|y)" << endl;
	cin >> x >> y;
	return pokemon;
}


void mostra_menu()
{
	system("cls");
	cout << "[Digite 0 para Desligar Pokedex!]" << endl;
	cout << "[Digite 1 para cadastrar um pokemon!]" << endl;
	cout << "[Digite 2 para listar os pokemons cadastrados!]" << endl;
	cout << "[Digite 3 para listar os pokemons cadastrados em ordem alfabetica dos tipos!]" << endl;
	cout << "[Digite 4 para pesquisar um Pokemon!]" << endl;
	cout << "[Digite 5 para cadastrar cidade!]" << endl;
	cout << "[Digite 6 para Pokecentro mais perto!]" << endl;
	cout << "[Digite 7 para contar quantos pokemons tem de determinado tipo!]" << endl;
	cout << "[Digite 8 para mostrar quantos pokemons pode ser encontrados em um raio de 100 metros!]" << endl;
	cout << "[Digite 9 para mostrar todas as cidades.]" << endl;
	return;
}

void cadastrocidade()
{
	edge a;
	char aux;

	cout << "Digite o nome da cidade que deseja cadastrar: " << endl;
	getline(cin >> ws, cidades[qtd_cidades].nome);
	cout << "Digite o codigo da cidade: " << endl;
	cin >> cidades[qtd_cidades].codigo;
	cout << "Existe um centro pokemon nessa cidade? (s/n)" << endl;
	cin >> aux;
	while (aux != 's' && aux != 'n')
	{
		cout << "Entrada invalida, digite (s/n)" << endl;
		cin >> aux;
	}

	if (aux == 's')
		cidades[qtd_cidades].centro_pkm = true;
	else
		cidades[qtd_cidades].centro_pkm = false;

	cout << "Escreva a lista de cidades adjacentes a cidade e seus pesos. Digite -1 quando terminar." << endl;
	cin >> a.dest >> a.weight;
	while (a.dest != -1 && a.weight != -1)
	{
		cidades[qtd_cidades].cidades_adj.push_back(a);
		a.dest = qtd_cidades;
		cidades[a.dest].cidades_adj.push_back(a);
		cin >> a.dest >> a.weight;
	}
}

int dijkstra(int start)
{
	bool intree[qtd_cidades];
	int distance[qtd_cidades];
	int parent[qtd_cidades];

	for (int u = 0; u < qtd_cidades; u++)
	{
		intree[u] = false;
		distance[u] = INT_MAX;
		parent[u] = -1;
	}

	distance[start] = 0;
	int v = start;
	int dest, weight;
	list<edge>::iterator it;

	while (intree[v] == false)
	{
		intree[v] = true;
		for (it = cidades[v].cidades_adj.begin(); it != cidades[v].cidades_adj.end(); it++)
		{
			dest = it->dest;
			weight = it->weight;
			if (distance[dest] > distance[v] + weight)
			{
				distance[dest] = distance[v] + weight;
				parent[dest] = v;
			}
		}
		v = 0;
		int dist = INT_MAX;
		for (int u = 0; u < qtd_cidades; u++)
		{
			if (intree[u] == false && dist > distance[u])
			{
				dist = distance[u];
				v = u;
			}
		}
	}
	int cidade_mais_proxima = start;
	distance[start] = INT_MAX;
	for (int i = 0; i < qtd_cidades; i++)
	{
		if (distance[i] < distance[cidade_mais_proxima] && cidades[i].centro_pkm)
			cidade_mais_proxima = i;
	}
	return cidade_mais_proxima;
}

void mostrar_cidades()
{
	list<edge>::iterator p;
	for (int i = 0; i < qtd_cidades; i++)
	{
		cout << "Nome da cidade: " << cidades[i].nome << endl;
		cout << "Codigo da cidade: " << cidades[i].codigo << endl;
		if (cidades[i].centro_pkm)
			cout << "Existe um centro pokemon na cidade." << endl;
		else
			cout << "Nao existe um centro pokemon na cidade." << endl;

		cout << "Cidades adjacentes:";
		for (p = cidades[i].cidades_adj.begin(); p != cidades[i].cidades_adj.end(); p++)
			cout << " " << p->dest;
		cout << endl;
	}
	fflush(stdin);
	getchar();
}

int main()
{
	int x;
	Pokemon pokemon;
	do
	{
		mostra_menu();
		cin >> x;
		switch (x)
		{
		case 1: // cadastrar pokemon
			pokemon = cadastro();
			return;
			break;
		case 2: // listar pokemon em ordem alfabetica dos nomes
			break;
		case 3: // listar pokemon em ordem alfabetica dos tipos
			break;
		case 4: // pesquisar pokemons
			break;
		case 5: // cadastrar cidade
			cadastrocidade();
			qtd_cidades++;
			break;
		case 6: // procurar pokecentro
			cout << "De qual cidade vai partir?" << endl;
			int c;
			cin >> c;
			if (cidades[c].centro_pkm)
				cout << "Existe um centro pokemon na cidade: " << c << endl;
			else
				cout << "Cidade mais prÃ³xima com centro pokemon: " << dijkstra(c) << endl;
			fflush(stdin);
			getchar();
			break;
		case 7: // contar tipos
			break;
		case 8: // procurar pokemons por perto
			break;
		case 9:
			mostrar_cidades();
			break;
		default:
			break;
		}
	}
	while (x != 0);
	return 0;
}
