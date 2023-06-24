#include <iostream>
#include <fstream>
using namespace std;

ofstream arq;

typedef struct noCand {
  int num;
  string nome;
  struct noCand *prox, *ante;
} *listaCand;


static listaCand cabecaC = NULL;
static listaCand raboC = NULL;
static listaCand tempC = NULL;

typedef struct noVoto {
  int numCand, quantVotos = 0;
  string nomeCand;
  struct noVoto *prox, *ante;
} *listaVoto;


static listaVoto cabecaV = NULL;
static listaVoto raboV = NULL;
static listaVoto tempV = NULL;

typedef struct noEleit {
  long long int titulo;
  string nome;
  struct noEleit *prox, *ante;
} *listaEleit;


static listaEleit cabecaE = NULL;
static listaEleit raboE = NULL;
static listaEleit tempE = NULL;

/*Candidatos*/
bool estaVazioCandidato();
bool umCandidato();
void inserirCandidato(int numero, string nome);
bool removerCandidato(int numero);
void mostrarCandidatos();

/*Eleitores*/
bool estaVazioEleitor();
void inserirEleitor(long long int titu, string nome);
bool verificaApto(long long int titu);
void mostrarEleitores();
bool verificarQuantEleitor();

/*Votos*/
bool inserirVoto(int numero);
void mostrarVencedor();

bool estaVazioCandidato(){
  if (cabecaC == NULL)
    return true;
  else
    return false;
}

bool umCandidato(){
  if (cabecaC == raboC)
    return true;
  else
    return false;
}

void inserirCandidato(int numero, string nome){
  tempC = new noCand;

  tempC->nome = nome;
  tempC->num = numero;

  tempC->prox = NULL;
  tempC->ante = NULL;
  if (cabecaC == NULL) {
    cabecaC = tempC;
  } else {
    raboC->prox = tempC;
    tempC->ante = raboC;
  }
  raboC = tempC;
  tempC = NULL;

  delete tempC;
}

bool removerCandidato(int numero){
  bool erro;
  noCand *removC = cabecaC;

  while (removC->prox != NULL && removC->num != numero) {
    removC = removC->prox;
  }

  if (removC->num != numero) {
    erro = true;
  } else if (removC->num == numero) {
    if (removC != cabecaC && removC != raboC) {
      removC->prox->ante = removC->ante;
      removC->ante->prox = removC->prox;
    } else if (removC == cabecaC) {
      cabecaC = removC->prox;
      removC->prox->ante = NULL;
    } else if (removC == raboC) {
      raboC = removC->ante;
      removC->ante->prox = NULL;
    }

    removC->ante = NULL;
    removC->prox = NULL;
    
    erro = false;
  }

  delete removC;

  return erro;
}

void mostrarCandidatos(){
  arq << "***************LISTA DE CANDIDATOS***************\n";
  arq << endl;

  for (tempC = cabecaC; tempC != NULL; tempC = tempC->prox) {
    arq << "Nome: " << tempC->nome << '\n';
    arq << "Numero dele: " << tempC->num << '\n';
    arq << '\n';
  }
  tempC = NULL;
  delete tempC;
}


bool estaVazioEleitor(){
  if (cabecaE == NULL)
    return true;
  else
    return false;
}

void inserirEleitor(long long int titu, string nome){
  tempE = new noEleit;

  tempE->nome = nome;
  tempE->titulo = titu;

  tempE->prox = NULL;
  tempE->ante = NULL;
  if (cabecaE == NULL) {
    cabecaE = tempE;
  } else {
    raboE->prox = tempE;
    tempE->ante = raboE;
  }
  raboE = tempE;
  tempE = NULL;

  delete tempE;
}

bool verificaApto(long long int titu){
  bool apto;

  for (tempE = cabecaE; tempE != NULL; tempE = tempE->prox) {
    if (titu != tempE->titulo && tempE->prox == NULL) {
      apto = true;
      break;
    } else if (titu == tempE->titulo) {
      apto = false;
      break;
    }
  }
  tempE = NULL;
  delete tempE;

  return apto;
}

void mostrarEleitores(){
  arq << "***************LISTA DE ELEITORES***************\n";
  arq << endl;

  for (tempE = cabecaE; tempE != NULL; tempE = tempE->prox) {
    arq << "Nome: " << tempE->nome << '\n';
    arq << "Titulo: " << tempE->titulo << '\n';
    arq << '\n';
  }
  tempE = NULL;
  delete tempE;
}

bool verificarQuantEleitor(){
  int numTotalCandidatos = 0, numTotalEleit = 0;

  for (tempC = cabecaC; tempC != NULL; tempC = tempC->prox) {
    numTotalCandidatos++;
  }

  for (tempE = cabecaE; tempE != NULL; tempE = tempE->prox) {
    numTotalEleit++;
  }

  if (numTotalCandidatos >= numTotalEleit/2)
    return true;
  else
    return false;
}


bool inserirVoto(int numero){
  bool encontr;

  for (tempC = cabecaC; tempC != NULL; tempC = tempC->prox) {
    if (tempC->num == numero) {
      encontr = false;

      if (cabecaV == NULL) {
        tempV = new noVoto;

        cabecaV = tempV;

        tempV->nomeCand = tempC->nome;
        tempV->numCand = tempC->num;
        tempV->quantVotos++;

        tempV->prox = NULL;
        tempV->ante = NULL;
      } else {
        for (tempV = cabecaV; tempV != NULL; tempV = tempV->prox) {
          if (tempV->numCand == numero) {
            tempV->quantVotos++;
            /*
            if (tempV != cabecaV) {
              tempV->prox->ante = tempV->prox;
              tempV->ante->prox = tempV->ante;
              tempV->prox = cabecaV;
              tempV->ante = NULL;
              cabecaV = tempV;
            } else if (tempV == raboV && tempV != cabecaV) {
              tempV->ante->prox = NULL;
              raboV = tempV->ante;
              tempV->ante = NULL;
              tempV->prox = cabecaV;
            }
            */
            break;
          } else if (tempV->numCand != numero && tempV->prox == NULL) {
            tempV = new noVoto;

            tempV->nomeCand = tempC->nome;
            tempV->numCand = tempC->num;
            tempV->quantVotos++;

            raboV->prox = tempV;
            tempV->ante = raboV;
            break;
          }
        }
      }
      raboV = tempV;

      tempV = NULL;
      delete tempV;

      break;
    } else if (tempC->num != numero && tempC->prox == NULL) {
      encontr = true;
      break;
    }
  }
  tempC = NULL;
  delete tempC;
  
  return encontr;
}

void mostrarVencedor(){
  int numTotalEleit = 0, numTotalVotos = 0;

  arq << "***************RELATORIO DA ELEICAO***************\n";
  arq << endl;

  for (tempV = cabecaV; tempV->prox != NULL; tempV = tempV->prox) {
    arq << "Nome do Candidato: " << tempV->nomeCand << "\tNumero: " << tempV->numCand << '\n';
    arq << "Quantidade de Votos: " << tempV->quantVotos << '\n';
    arq << '\n';
    numTotalVotos++;
  }

  for (tempE = cabecaE; tempE->prox != NULL; tempE = tempE->prox) {
    numTotalEleit++;
  }

  arq << endl << endl;
  arq << "Quantidade de votos: " << numTotalVotos << '\n';
  if (numTotalEleit != numTotalVotos) {
    arq << "Faltaram " << numTotalEleit - numTotalVotos << " Eleitores nessa eleicao" << '\n';
  } else {
    arq << "Todos os Eleitores compareceram nessa eleicao";
  }

  tempV = NULL;
  delete tempV;
}
