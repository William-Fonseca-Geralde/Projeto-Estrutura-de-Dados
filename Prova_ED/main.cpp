#include <iostream>
#include <cstring>
#include "urna.h"
using namespace std;

int main() {

  string nome;
  char resp;
  bool err;
  long long int titu;
  int valor, opcao;

  do {
    system("cls");
    cout << "****************A FESTA DA DEMOCRACIA****************\n" << '\n';
    cout << "\t1 - Cadastro de Candidatos;\n";
    cout << "\t2 - Cadastro de Eleitores;\n";
    cout << "\t3 - Registro de Voto;\n";
    cout << "\t4 - Gerar Relatorio Geral;\n";
    cout << "\t5 - Sair do Programa.\n";
    cout << "\nDigite uma das opcoes: ";
    cin >> opcao;

    system("cls");
    switch (opcao) {
    case 1:
      do {
        system("cls");
        cout << "Digite o nome desse candidato: ";
        getline(cin >> ws, nome);
        cout << "Digite o seu numero: ";
        cin >> valor;

        inserirCandidato(valor, nome);

        cout << "\nDeseja adicionar mais um candidato? (s / n) ";
        cin >> resp;
      } while (resp == 's' || resp == 'S');
      system("cls");
      
      cout << "Deseja remover algum candidato? (s / n) ";
      cin >> resp;

      while (resp == 's' || resp == 'S') {
        system("cls");
        cout << "Digite o numero do candidato que quer ser removido: ";
        cin >> valor;
        err = removerCandidato(valor);
        if (err == true) {
          resp = 's';
          cout << "Nao encontrado\n";
          cout << "Deseja remover outro candidato? (s / n) ";
          cin >> resp;
        } else {
          cout << "Removido\n";
          cout << "Deseja remover mais algum candidato? (s / n) ";
          cin >> resp;
        }
      }

      arq.open("ListaCandidatos.txt");
      mostrarCandidatos();
      arq.close();
      
    break;
    case 2:
      do {
        system("cls");
        cout << "Digite o nome do eleitor: ";
        getline(cin >> ws, nome);
        cout << "E o seu titulo de eleitor: ";
        cin >> titu;

        inserirEleitor(titu, nome);

        cout << "\nDeseja adicionar mais eleitores? (s / n) ";
        cin >> resp;
      } while (resp == 's' || resp == 'S');
      system("cls");
      
      arq.open("ListaEleitoresAptos.txt");
      mostrarEleitores();
      arq.close();
    break;
    case 3:
      system("cls");
      if (estaVazioCandidato()) {
        cout << "Nao existe candidatos nessa eleicao\n";
        cout << "Por favor, cadastrar mais candidatos\n";
        system("Pause");
      } else if (umCandidato()) {
        cout << "Existe apenas um unico candidato nessa eleicao\n";
        cout << "Por favor, cadastrar, pelo menos, mais um candidatos\n";
        system("Pause");
      } else if (estaVazioEleitor()) {
        cout << "Nao exite eleitor nessa sala\n";
        system("Pause");
      } else if (verificarQuantEleitor()){
        cout << "Nao tem eleitores o suficiente para essa sala\n";
        cout << "Por motivos de prevenir faltas dos mesmo, por favor, cadastrar mais eleitores\n";
        system("Pause");
      } else {
        do {
          system("cls");
          cout << "Digite o titulo do eleitor para verificar se esta apto ou nao\n";
          cin >> titu;

          err = verificaApto(titu);
          if (err == true) {
            cout << "O eleitor nao esta apto\n";
            cout << "\nExistem eleitores na fila? (s / n) ";
            cin >> resp;
          } else {
            do {
              cout << "Para qual candidato ele votou? (apenas o numero dele) ";
              cin >> valor;

              err = inserirVoto(valor);

              if (err == true){
                cout << "Candidato nao encontrado\n";
                system("Pause");
                valor = 0;
              } else {
                cout << "Voto inserido...\n";
                cout << "Existem mais eleitores na fila? (s / n) ";
                cin >> resp;
              }
            } while (valor == 0);
          }
        } while (resp == 's' || resp == 'S');
      }
    break;
    case 4:
      system("cls");
      cout << "Arquivo gerado\n";
      arq.open("RelatorioEleicao.txt");
      mostrarVencedor();
      arq.close();
      system("Pause");
    break;
    case 5:
      system("cls");
      cout << "Saindo do Programa...";
    break;
    default:
      break;
    }
  } while (opcao != 4);

  return 0;
}