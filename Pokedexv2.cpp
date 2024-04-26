// Trabalho da disciplina de Algoritmos 3, ministrada pelo professor Jonas Lopes de Vilas Boas
// Alunos: Andre Augusto Coelho Silva, Henrique Oliveira Campello, Lucas  Ynoguti e Joao Vitor de Lucena
// Segunda Entrega nas linhas: 31 (Grafo), 317 (Cadastrar uma cidade e suas cidades adjcentes), 387 (mostrar as cidades)

#include <iostream>
#include <algorithm> //transform
#include <string>
#include <cctype>  // tolower
#include <fstream> //arquivos
#include <sstream> // parse do arquivo csv
// #include <windows.h> //system
#include <list>
#include <climits>

using namespace std;

struct info
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

string tipagem[18] = {"agua", "dragao", "eletrico", "fada", "fantasma", "fogo", "gelo", "grama", "inseto", "lutador", "metal", "normal", "psiquico", "rocha", "sombrio", "terra", "venenoso", "voador"};
int qtd_tipagem[18];

int qtd_pokemon = 0;
info pokedex[1015];

cidade cidades[10];
int qtd_cidades = 0;

int compara_nome(const void *a, const void *b)
{
	info *pkmA = (info *)a;
	info *pkmB = (info *)b;
	if (pkmA->name < pkmB->name)
		return -1;
	else if (pkmA->name > pkmB->name)
		return 1;
	else
		return 0;
}

int compara_tipo(const void *a, const void *b)
{
	info *pkmA = (info *)a;
	info *pkmB = (info *)b;
	if ((pkmA->tipo1 + pkmA->tipo2) < (pkmB->tipo1 + pkmB->tipo2))
		return -1;
	else if ((pkmA->tipo1 + pkmA->tipo2) > (pkmB->tipo1 + pkmB->tipo2))
		return 1;
	else
		return 0;
}

// busca binaria
// qual = 1: acha o nome;  qual = 2: acha o tipo
int binaria(string txt, int tamanho, int qual)
{
	bool achou;			   // var aux p/ busca
	int baixo, meio, alto; // var aux
	string txt2;
	baixo = 0;
	alto = tamanho - 1;
	achou = false;
	while ((baixo <= alto) && (achou == false))
	{
		meio = (baixo + alto) / 2;

		if (qual == 2)
			txt2 = tipagem[meio];
		else
		{
			txt2 = pokedex[meio].name;
		}

		if (txt < txt2)
			alto = meio - 1;
		else if (txt > txt2)
			baixo = meio + 1;
		else
			achou = true;
	}
	if (achou)
		return meio;
	else
		return -1;
}

void ler_arquivo()
{
	ifstream input_file;
	input_file.open("pokemons.csv");
	string line = "";
	while (getline(input_file, line))
	{
		string temp_string;

		stringstream input_string(line);

		getline(input_string, temp_string, ',');
		pokedex[qtd_pokemon].numero = atoi(temp_string.c_str());

		getline(input_string, pokedex[qtd_pokemon].name, ',');

		getline(input_string, pokedex[qtd_pokemon].tipo1, ',');
		qtd_tipagem[binaria(pokedex[qtd_pokemon].tipo1, 18, 2)]++;

		getline(input_string, pokedex[qtd_pokemon].tipo2, ',');
		qtd_tipagem[binaria(pokedex[qtd_pokemon].tipo2, 18, 2)]++;

		getline(input_string, temp_string, ',');
		pokedex[qtd_pokemon].x = atoi(temp_string.c_str());

		getline(input_string, temp_string, ',');
		pokedex[qtd_pokemon].y = atoi(temp_string.c_str());

		line = "";
		qtd_pokemon++;
	}
	qsort(pokedex, qtd_pokemon, sizeof(info), compara_nome);
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

// Funcao de cadastro de pokemon na pokedex (FEITO)
info cadastro_pokemon()
{
	info novo;
	int resultado;
	string txt;
	cout << "[Qual nome do pokemon que deseja cadastrar?]" << endl;
	getline(cin >> ws, novo.name);

	cout << "[Qual numero do pokemon que deseja cadastrar?]" << endl;
	cin >> novo.numero;

	// leitura do tipo1 do pokemon, com verificacao para saber se ele existe
	do
	{
		cout << "[Qual o primeiro tipo do pokemon que deseja cadastrar?]" << endl;
		cout << "[Fogo, Agua, Grama, Eletrico, Rocha, Terra, Metal, Voador, Dragao, Fada, Sombrio, Fantasma, Psiquico, Lutador, Inseto, Venenoso, Normal, Gelo]" << endl;
		cin >> txt;
		transform(txt.begin(), txt.end(), txt.begin(), ::tolower);
		resultado = binaria(txt, 18, 2);
	} while (resultado == -1);
	novo.tipo1 = txt;
	qtd_tipagem[resultado]++;

	// leitura do tipo2 do pokemon, com verificacao para saber se ele existe
	do
	{
		cout << "[Qual o segundo tipo do pokemon que deseja cadastrar? (digite 'vazio' caso n�o possua)]" << endl;
		cin >> txt;
		if (txt == "vazio")
			break;
		transform(txt.begin(), txt.end(), txt.begin(), ::tolower);
		resultado = binaria(txt, 18, 2);
	} while (resultado == -1);
	novo.tipo2 = txt;
	if (txt != "vazio")
		qtd_tipagem[resultado]++;

	cout << "[Qual a localizacao do Pokemon no mapa?]" << endl;

	cout << "[X?]" << endl;
	cin >> novo.x;

	cout << "[Y?]" << endl;
	cin >> novo.y;
	return novo;
}

// Funcao para listar os pokemons cadastrados
void lista_pokemon()
{
	int j;
	qsort(pokedex, qtd_pokemon, sizeof(info), compara_nome);
	for (j = 0; j < qtd_pokemon; j++)
	{
		cout << "Pokemon " << pokedex[j].numero << " nome: " << pokedex[j].name << endl;
		cout << "Pokemon " << pokedex[j].numero << " tipo1: " << pokedex[j].tipo1 << endl;
		cout << "Pokemon " << pokedex[j].numero << " tipo2: " << pokedex[j].tipo2 << endl;
		cout << "Pokemon " << pokedex[j].numero << " X: " << pokedex[j].x << endl;
		cout << "Pokemon " << pokedex[j].numero << " Y: " << pokedex[j].y << endl;
	}

	fflush(stdin);
	getchar();
}

// Funcao para pesquisar os pokemons cadastrados
void pesquisa()
{
	int x;
	string nome;
	int numero, resultado;
	cout << "[Como deseja pesquisar o Pokemon? (1 - Nome) (2 - Numero))]" << endl;
	cin >> x;
	while (x > 2 || x < 1)
	{
		cout << "[Como deseja pesquisar o Pokemon? (1 - Nome) (2 - Numero))]" << endl;
		cin >> x;
	}

	if (x == 1)
	{
		cout << "[Nome do pokemon que deseja pesquisar:]" << endl;
		cin >> nome;
		resultado = binaria(nome, qtd_pokemon, 1);
		if (resultado != -1)
		{
			cout << "[Pokemon Encontrado!:]" << endl;
			cout << "Nome: " << pokedex[resultado].name << endl;
			cout << "Numero: " << pokedex[resultado].numero << endl;
			cout << "Tipagem 1: " << pokedex[resultado].tipo1 << endl;
			cout << "Tipagem 2: " << pokedex[resultado].tipo2 << endl;
			cout << "X: " << pokedex[resultado].x << " Y: " << pokedex[resultado].y << endl;
			fflush(stdin);
			getchar();
			return;
		}
		else
		{
			cout << "Esse pokemon nao foi encontrado." << endl;
			fflush(stdin);
			getchar();
			return;
		}
	}
	else
	{
		int j;
		cout << "[Numero do pokemon que deseja pesquisar:]" << endl;
		cin >> numero;
		for (j = 0; j < qtd_pokemon; j++)
		{
			if (numero == pokedex[j].numero)
			{
				cout << "[Pokemon Encontrado!:]" << endl;
				cout << "Nome: " << pokedex[j].name << endl;
				cout << "Numero: " << pokedex[j].numero << endl;
				cout << "Tipagem 1: " << pokedex[j].tipo1 << endl;
				cout << "Tipagem 2: " << pokedex[j].tipo2 << endl;
				cout << "X: " << pokedex[j].x << "Y: " << pokedex[j].y << endl;
				fflush(stdin);
				getchar();
				return;
			}
		}
	}
	return;
}

// Funcao para listar tipo (FALTA LISTAR EM ORDEM ALFABETICA)
void listartipo()
{
	int j;
	qsort(pokedex, qtd_pokemon, sizeof(info), compara_tipo);
	for (j = 0; j < qtd_pokemon; j++)
	{
		cout << "Pokemon " << pokedex[j].numero << ": " << pokedex[j].name << " Tipo 1: " << pokedex[j].tipo1 << " Tipo 2: " << pokedex[j].tipo2 << endl;
	}

	cin.ignore();
	getchar();
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

// Funcao para imprimir quantos pokemons de determinado tipo (FEITO)
void imprimirtipo()
{
	qsort(pokedex, qtd_pokemon, sizeof(info), compara_nome);
	for (int i = 0; i < 18; i++)
		cout << "Qtd do tipo " << tipagem[i] << ":" << qtd_tipagem[i] << endl;
}

void contar_tipos()
{
	string txt;
	int indice_tipo;
	do
	{
		cout << "Qual tipo deseja saber a quantidade de pokemons?" << endl;
		cin >> txt;
		transform(txt.begin(), txt.end(), txt.begin(), ::tolower);
		indice_tipo = binaria(txt, 18, 2);
		if (indice_tipo != -1)
			cout << "A quantidade de pokemons do tipo " << txt << " eh de: " << qtd_tipagem[indice_tipo] << endl;
		else
			cout << "Esse tipo nao existe." << endl;
		fflush(stdin);
		getchar();
	} while (indice_tipo == -1);
}

// Funcao para procurar pokemons em um raio de 100 metros
void pokemonsporperto()
{
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
	for (int i = 0; i < 18; i++)
		qtd_tipagem[i] = 0;

	int x;

	ler_arquivo();

	do
	{
		mostra_menu();
		cin >> x;
		switch (x)
		{
		case 1: // cadastrar pokemon
			pokedex[qtd_pokemon] = cadastro_pokemon();
			qtd_pokemon++;
			break;
		case 2: // listar pokemon em ordem alfabetica dos nomes
			lista_pokemon();
			break;
		case 3: // listar pokemon em ordem alfabetica dos tipos
			listartipo();
			break;
		case 4: // pesquisar pokemons
			pesquisa();
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
				cout << "Cidade mais próxima com centro pokemon: " << dijkstra(c) << endl;
			fflush(stdin);
			getchar();
			break;
		case 7: // contar tipos
			contar_tipos();
			break;
		case 8: // procurar pokemons por perto
			pokemonsporperto();
			break;
		case 9:
			mostrar_cidades();
			break;
		default:
			break;
		}
	} while (x != 0);
	return 0;
}
