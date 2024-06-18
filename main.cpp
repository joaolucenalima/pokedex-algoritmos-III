#include <iostream>
#include <list>
#include <climits>

using namespace std;

struct Pokemon
{
	int numero;
	string nome;
	string tipo;
	int x;
	int y;
};

struct TreeNode
{
	Pokemon pokemon;
	struct TreeNode *left;
	struct TreeNode *right;
};
typedef TreeNode *treenodeptr;

struct Edge
{
	int dest;
	int weight;
};

struct Cidade
{
	int codigo;
	string nome;
	bool centro_pkm;
	list<Edge> cidades_adj;
};

Cidade cidades[10];
int qtd_cidades = 0;

void mostrarMenu()
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

void cadastrarCidade()
{
	Edge a;
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
	list<Edge>::iterator it;

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

void mostrarCidades()
{
	list<Edge>::iterator p;
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

Pokemon cadastro()
{
	Pokemon pokemon;
	cout << "Qual o numero do pokemon?" << endl;
	cin >> pokemon.numero;
	cout << "Qual o nome do pokemon?" << endl;
	getline(cin >> ws, pokemon.nome);
	cout << "Qual o tipo do pokemon" << endl;
	getline(cin >> ws, pokemon.tipo);
	cout << "Qual a localizacao do pokemon? (x|y)" << endl;
	cin >> pokemon.x >> pokemon.y;
	return pokemon;
}

void inserirPokemon(treenodeptr &root, Pokemon value)
{
	if (root == NULL)
	{
		root = new TreeNode;
		root->pokemon = value;
		root->left = NULL;
		root->right = NULL;

		return;
	}

	if (value.nome < root->pokemon.nome)
		inserirPokemon(root->left, value);
	else if (value.nome > root->pokemon.nome)
		inserirPokemon(root->right, value);
}

void inserirPokemonPorTipo(treenodeptr root, Pokemon pokemon)
{
	if (root == NULL)
	{
		root = new TreeNode;
		root->pokemon = pokemon;
		root->left = NULL;
		root->right = NULL;

		return;
	}

	if (pokemon.tipo > root->pokemon.tipo)
		inserirPokemon(root->right, pokemon);
	else
		inserirPokemon(root->left, pokemon);
}

void ordenarPorTipo(treenodeptr root, treenodeptr &root_tipos)
{
	if (root == NULL)
		return;

	ordenarPorTipo(root->left, root_tipos);
	inserirPokemonPorTipo(root_tipos, root->pokemon);
	ordenarPorTipo(root->right, root_tipos);
}

void imprimirPokemonEmOrdem(treenodeptr root)
{
	if (root == NULL)
		return;

	imprimirPokemonEmOrdem(root->left);
	cout << "Nome: " << root->pokemon.nome << " | Tipo: " << root->pokemon.tipo << endl;
	imprimirPokemonEmOrdem(root->right);
}

treenodeptr pesquisarPokemon(treenodeptr root, string nome)
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

	if (nome < p->pokemon.nome)
		return removerPokemon(p->left, nome);

	return removerPokemon(p->right, nome);
}

int main()
{
	int x;
	Pokemon pokemon;
	treenodeptr root = NULL;
	treenodeptr root_tipos = NULL;
	treenodeptr pokemonPesquisado = NULL;
	string nome;

	do
	{
		mostrarMenu();
		cin >> x;

		switch (x)
		{
		case 0:
			cout << "Desligando Pokedex..." << endl;
			break;

		case 1: // cadastrar pokemon
			pokemon = cadastro();
			inserirPokemon(root, pokemon);
			break;

		case 2: // listar pokemon em ordem alfabetica dos nomes
			imprimirPokemonEmOrdem(root);
			fflush(stdin);
			getchar();
			break;

		case 3: // ordenar e listar pokemon em ordem alfabetica dos tipos
			ordenarPorTipo(root, root_tipos);
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
			cadastrarCidade();
			qtd_cidades++;
			break;

		case 6: // procurar pokecentro
			cout << "De qual cidade vai partir?" << endl;
			int c;
			cin >> c;
			if (cidades[c].centro_pkm)
				cout << "Existe um centro pokemon na cidade: " << c << endl;
			else
				cout << "Cidade mais proxima com centro pokemon: " << dijkstra(c) << endl;
			fflush(stdin);
			getchar();
			break;

		case 7: // contar tipos
			break;

		case 8: // procurar pokemons por perto
			break;

		case 9:
			mostrarCidades();
			break;

		case 10: // remover um pokemon
			cout << "Escreva o nome do pokemon a ser removido" << endl;
			cin >> nome;
			if (removerPokemon(root, nome))
				cout << "O pokemon foi removido" << endl;
			else
				cout << "Pokemon nao encontrado" << endl;
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