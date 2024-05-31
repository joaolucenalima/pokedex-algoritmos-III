// Trabalho da disciplina de Algoritmos 3, ministrada pelo professor Jonas Lopes de Vilas Boas
// Alunos: Andre Augusto Coelho Silva, Henrique Oliveira Campello, Lucas Nolasco Ynoguti e Joao Vitor de Lucena

#include <iostream>
#include <algorithm> //transform
#include <string>
#include <list>
#include <climits>
#include <stdio.h>

using namespace std;

struct Pokemon
{
	int numero;
	string nome;
	string tipo;
	int x;
	int y;
};

struct treenode
{
	Pokemon pokemon;
	struct treenode *left;
	struct treenode *right;
};

typedef treenode *treenodeptr;

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
	cout << "Qual a localizaÃ§Ã£o do pokemon? (x|y)" << endl;
	cin >> pokemon.x >> pokemon.y;
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
	cout << "[Digite 10 remover um pokemon.]" << endl;
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

void insertPokemon(treenodeptr &root, Pokemon value)
{
	if (root == NULL)
	{
		root = new treenode;
		root->pokemon = value;
		root->left = NULL;
		root->right = NULL;
	}
	else if (value.nome < root->pokemon.nome)
	{
		insertPokemon(root->left, value);
	}
	else
	{
		insertPokemon(root->right, value);
	}
}

void insertPokemonTipo(treenodeptr &root, Pokemon value)
{
	if (root == NULL)
	{
		root = new treenode;
		root->pokemon = value;
		root->left = NULL;
		root->right = NULL;
	}
	else if (value.tipo < root->pokemon.tipo)
	{
		insertPokemon(root->left, value);
	}
	else if (value.tipo < root->pokemon.tipo)
	{
		insertPokemon(root->right, value);
	}
	else
	{
		if (value.nome < root->pokemon.nome)
			insertPokemon(root->left, value);
		else if (value.nome > root->pokemon.nome)
			insertPokemon(root->left, value);
	}
}

void imprimirPokemonEmOrdem(treenodeptr root)
{
	if (root == NULL)
	{
		return;
	}
	imprimirPokemonEmOrdem(root->left);
	cout << "Nome: " << root->pokemon.nome << " Tipo: " << root->pokemon.tipo << endl;
	imprimirPokemonEmOrdem(root->right);
}

treenode *pesquisarPokemon(treenodeptr root, string nome)
{
	if (root == NULL)
		return NULL;

	if (root->pokemon.nome == nome)
		return root;

	if (nome < root->pokemon.nome)
		return pesquisarPokemon(root->left, nome);

	return pesquisarPokemon(root->right, nome);
}

treenodeptr encontrarMenorPokemon(treenodeptr &p)
{
	if (p->left == NULL)
		return p;

	return encontrarMenorPokemon(p->left);
}

bool removerPokemon(treenodeptr &p, string nome)
{
	treenodeptr t;
	if (p == NULL)
		return false;
	if (nome == p->pokemon.nome)
	{
		t = p;
		if (p->left == NULL)
			p = p->right;
		else if (p->right == NULL)
			p = p->left;
		else
		{
			t = encontrarMenorPokemon(p->right);
			p->pokemon = t->pokemon;
		}
		delete t;
		return true;
	}
	else if (nome < p->pokemon.nome)
		return removerPokemon(p->left, nome);
	else
		return removerPokemon(p->right, nome);
}

bool removerPokemonTipo(treenodeptr &p, string tipo, string nome)
{
	treenodeptr t;
	if (p == NULL)
		return false;
	if (nome == p->pokemon.nome)
	{
		t = p;
		if (p->left == NULL)
			p = p->right;
		else if (p->right == NULL)
			p = p->left;
		else
		{
			t = encontrarMenorPokemon(p->right);
			p->pokemon = t->pokemon;
		}
		delete t;
		return true;
	}
	else if (tipo < p->pokemon.tipo)
		return removerPokemonTipo(p->left, tipo, nome);
	else if (tipo < p->pokemon.tipo)
		return removerPokemonTipo(p->right, tipo, nome);
	else
	{
		if (nome < p->pokemon.nome)
			return removerPokemonTipo(p->left, tipo, nome);
		else if (nome > p->pokemon.nome)
			return removerPokemonTipo(p->right, tipo, nome);
	}
}

int main()
{
	int x;
	Pokemon pokemon;
	treenodeptr root = NULL;
	treenodeptr root_tipos = NULL;
	treenode *pokemonPesquisado;
	string nome, tipo;

	do
	{
		mostra_menu();
		cin >> x;

		switch (x)
		{
		case 1: // cadastrar pokemon
			pokemon = cadastro();
			insertPokemon(root, pokemon);
			insertPokemonTipo(root_tipos, pokemon);
			break;
		case 2: // listar pokemon em ordem alfabetica dos nomes
			imprimirPokemonEmOrdem(root);
			fflush(stdin);
			getchar();
			break;
		case 3: // listar pokemon em ordem alfabetica dos tipos
			imprimirPokemonEmOrdem(root_tipos);
			fflush(stdin);
			getchar();
			break;
		case 4: // pesquisar pokemons
			cout << "Digite o nome do pokemon que deseja pesquisar: " << endl;
			getline(cin >> ws, nome);
			pokemonPesquisado = pesquisarPokemon(root, nome);

			if (pokemonPesquisado == NULL)
				cout << "Pokemon nao encontrado!" << endl;
			else
				cout << "Pokemon encontrado: " << pokemonPesquisado->pokemon.nome << endl;

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
		case 10: // remover um pokemon
			cout << "Escreva o nome e o tipo do pokemon a ser removido" << endl;
			cin >> nome >> tipo;
			if (removerPokemon(root, nome) && removerPokemonTipo(root, tipo, nome))
				cout << "O pokemon foi removido" << endl;
			else
				cout << "Erro!" << endl;
			fflush(stdin);
			getchar();
			break;
		default:
			cout << "Opcao invalida!" << endl;
			break;
		}
	} while (x != 0);
	return 0;
}