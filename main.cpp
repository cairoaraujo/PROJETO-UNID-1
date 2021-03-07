#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "musica.hpp"
#include "node.hpp"
#include "lista.hpp"
#include "playlist.hpp"

using namespace std;

#define MAX_PL 20


int main(int argc, char const *argv[]){

    // Variável para uma flag de condicao
    bool flag = false;

    // Variáveis para guardar opcões que o usuário escolheu
    int op1 = 0, op2 = 0, op3 = 0, op4 = 0;

    // Variável para quardar a quantidade de playlists cadastradas
    int qtd_pl = 0;

    // Variável para receber a posicao da playlist escolhida pelo usuário
    int posicao_pl;

    // Variável para armazenar as posicões digitadas pelo usuário
    int posicao1, posicao2;

    // Variáveis para armazenar os nomes das musicas, artistas e playlists
    string nome_musica, nome_artista, nome_playlist;

    // Variável para reber a string das opcões do usuário nos menus
    string s_op;

    // Variável para montar uma musica ou receber retorno de alguma funcao
    Musica musica;
    
    // Variável para receber o ponteiro da próxima musica a ser tocada
    Musica *prox_musica;

    // Lista de todas as musicas do sistema
    Lista *musicas_sistema = new Lista;

    // Array de todas as playlists
    Playlist *playlists = new Playlist[MAX_PL];

    system("clear || cls");

    // Apresentacao do menu principal do programa
    do{

        cout << "+---------------------------+" << endl;
        cout << "|      MENU PRINCIPAL       |" << endl;
        cout << "+---------------------------+" << endl;
        cout << "| 1 - Musicas do sistema    |" << endl;
        cout << "| 2 - Playlists             |" << endl;
		cout << "| 3 - Sair                  |" << endl;
        cout << "+---------------------------+" << endl;

        cout << "Digite uma opcao: ";

		// Lê a string da opcao e converte para inteiro
		getline(cin, s_op);
        stringstream op(s_op);
        op >> op1;

        system("clear || cls");

        switch (op1){

            case 1: // Menu de musicas do sistema
                
                do{

					cout << "+--------------------------------+" << endl;
					cout << "|       MuSICAS DO SISTEMA       |" << endl;
                    cout << "+--------------------------------+" << endl;
                    cout << "| 1 - Adicionar musica           |" << endl;
                    cout << "| 2 - Remover musica             |" << endl;
                    cout << "| 3 - Exibir musicas cadastradas |" << endl;
					cout << "| 4 - Voltar                     |" << endl;
                    cout << "+--------------------------------+" << endl;

                    cout << "Digite uma opcao: ";

                    // Lê a string da opcao e converte para inteiro
                    getline(cin, s_op); 
                    stringstream op(s_op);
                    op >> op2;

					system("clear || cls");

                    switch(op2){

                        case 1: // Adicionar musica

							fflush(stdin); // Limpa o buffer
							cout << "Digite o nome da musica: ";
							getline(cin, nome_musica);

							fflush(stdin); // Limpa o buffer
							cout << "\nDigite o nome do artista: ";
							getline(cin, nome_artista);

							// Monta a musica
                            musica.setNome(nome_musica);
                            musica.setArtista(nome_artista);

                            cout << "\nDeseja incluir em alguma posicao especifica? Nao(1) ou Sim(2): ";
                            cin >> op3;
                            cin.ignore();

                            if(op3 == 2){ // Verifica se o usuário deseja inserir em uma posicao especifica

                                system("clear || cls");

                                musicas_sistema->imprime(); // Imprime a lista de musicas do sistema

                                cout << "\nDigite a posicao: ";
                                cin >> posicao1;
                                cin.ignore();

                                if(posicao1 > musicas_sistema->getTamanho() + 1){ // Verifica se a posicao é válida
                                    cout << "\nPosicao inválida!" << endl;

                                }else{
                                    if(musicas_sistema->inserePos(posicao1, musica)){ // Chama a funcao e verifica se a insercao foi bem sucedida
                                        cout << "\nmusica cadastrada no sistema com sucesso!" << endl;

                                    }else{
                                        cout << "\nErro ao cadastrar musica no sistema!" << endl;
                                    }
                                }

                            }else{
                                if(op3 == 1){ // Verifica se o usuário nao quer inserir em uma posicao especifica
                                    if(musicas_sistema->insereFim(musica)){ // Verifica se a insercao foi bem sucedida
                                        cout << "\nmusica cadastrada no sistema com sucesso!" << endl;

                                    }else{
                                        cout << "\nErro ao cadastrar musica no sistema!" << endl;
                                    }

                                }else{
                                    cout << "\nopcao inválida!" << endl;
                                }
                            }

                            cout << "Pressione ENTER para continuar..." << endl;
                            getchar();
                            system("clear || cls");

							break;
                        
                        case 2: // Remover musica

                            if(musicas_sistema->getTamanho() > 0){ // Verifica se há musicas cadastradas
                                
                                musicas_sistema->imprime(); // Imprime a lista de musicas para o usuário
                                
                                cout << "\nDigite o número da musica que deseja remover do sistema: ";
                                cin >> posicao1;
                                cin.ignore();

                                if(posicao1 >= 1 && posicao1 <= musicas_sistema->getTamanho()){ // Verifica se a posicao digitada é válida

                                    musica = *(musicas_sistema->buscaMusicaPos(posicao1 - 1)); // Recebe a musica da posicao especificada

                                    for(int i = 0; i < qtd_pl; i++){ // Laco para percorrer o array de playlists procurando por playlists com a musica a ser apagada
                                        if(playlists[i].getLista()->buscaMusica(musica) != nullptr){
                                            for(int j = 0; j < playlists[i].getLista()->getTamanho(); j++){ // Percorre os elementos da playlist para achar a posicao da musica a ser apagada
                                                if(playlists[i].getLista()->buscaMusicaPos(j)->getNome() == musica.getNome() && playlists[i].getLista()->buscaMusicaPos(j)->getArtista() == musica.getArtista()){
                                                    cout << "\nA musica " << playlists[i].getLista()->buscaMusicaPos(j)->getNome() << " de " << playlists[i].getLista()->buscaMusicaPos(j)->getArtista() << " estava na posicao " << j+1 <<  " da playlist " << playlists[i].getNome() << " e foi removida!";
                                                    playlists[i].removeMusicaPos(j + 1); // Apaga a musica da playlist
                                                }
                                            }
                                        }
                                    }

                                    musicas_sistema->removePos(posicao1); // Remove a musica do sistema
                                    
                                    cout << "\nmusica removida do sistema com sucesso!" << endl;

                                }else{
                                    cout << "\nPosicao inválida!" << endl;
                                }

                            }else{
                                cout << "Nao há musicas cadastradas no sistema!" << endl << endl;
                            }
                            
                            cout << "Pressione ENTER para continuar..." << endl;
                            getchar();
                            system("clear || cls");

                            break;

                        case 3: // Exibir musicas cadastradas

                            if(musicas_sistema->getTamanho() > 0){ // Verifica se há musicas cadastradas
                                musicas_sistema->imprime(); // Imprime a lista de musicas para o usuário
                                cout << endl;

                            }else{
                                cout << "Nao há musicas cadastradas no sistema!" << endl << endl;
                            }

                            cout << "Pressione ENTER para continuar..." << endl;
                            getchar();
                            system("clear || cls");

                            break;
                        
                        case 4: break; // Sair

                        default: // opcao inválida
                            cout << "opcao inválida!" << endl;
                            cout << "Pressione ENTER para continuar..." << endl;
                            getchar();
                            system("clear || cls");
                            break;
                    }

                }while (op2 != 4);

                break;

            case 2: // Menu de playlists
                                
                do{

                    cout << "+------------------------+" << endl;
                    cout << "|       PLAYLISTS        |" << endl;
                    cout << "+------------------------+" << endl;
                    cout << "| 1 - Adicionar playlist |" << endl;
                    cout << "| 2 - Remover playlist   |" << endl;
                    cout << "| 3 - Exibir playlists   |" << endl;
					cout << "| 4 - Abrir uma playlist |" << endl;
					cout << "| 5 - Voltar             |" << endl;
                    cout << "+------------------------+" << endl;

                    cout << "Digite uma opcao: ";

                    // Lê a string da opcao e converte para inteiro
                    getline(cin, s_op); 
                    stringstream op(s_op); 
                    op >> op2;

                    system("clear || cls");

                    switch(op2){
                        case 1: // Adicionar playlist

                            if(qtd_pl < MAX_PL){ // Verifica se o número máximo de playlists permitidas já foi atingido
                                
								fflush(stdin); // Limpa o buffer
                                cout << "Digite o nome da playlist que deseja inserir: ";
                                getline(cin, nome_playlist);
                                
                                flag = false;
                                for(int i = 0; i < qtd_pl; i++){ // Verifica se há uma playlist com o mesmo nome
                                    if(nome_playlist == playlists[i].getNome()){
                                        flag = true;
                                    }
                                }

                                if(!flag){
                                    // A playlist nao existe e pode ser adicionada
                                    playlists[qtd_pl].setNome(nome_playlist);
                                    cout << "\nPlaylist " << playlists[qtd_pl].getNome() << " adicionada com sucesso!" << endl;
                                    qtd_pl++;

                                }else{
                                    cout << "\nEsta playlist já existe!" << endl;
                                }

                            }else{
                                cout << "Você já atingiu o limite de playlists!" << endl << endl;
                            }

                            cout << "Pressione ENTER para continuar..." << endl;
                            getchar();
                            system("clear || cls");

                            break;
                        
                        case 2: // Remover playlist

                            if(qtd_pl > 0){ // Verifica se há playlists cadastradas

                                for(int i = 0; i < qtd_pl; i++){ // Exibe as playlists cadastradas
                                    cout << i+1 << ". " << playlists[i].getNome() << endl;
                                }

                                cout << "\nDigite o número da playlist que deseja remover: ";
                                cin >> posicao1;
                                cin.ignore();

                                if(posicao1 >= 1 && posicao1 <= qtd_pl){ // Verifica se a posicao é válida

                                    posicao1--; // Ajusta a posicao para a faixa de valores dos indices (0 -> n-1)
                                    for(int i = posicao1; i < qtd_pl - 1; i++){ // Percorre o array realocando as posicões
                                        playlists[i].setNome(playlists[i + 1].getNome());
                                        playlists[i].setLista(playlists[i + 1].getLista());
                                    }

                                    playlists[qtd_pl - 1].setNome("");
                                    playlists[qtd_pl - 1].setLista(nullptr);

                                    qtd_pl--; // Atualiza o tamanho da playlist

                                    cout << "\nPlaylist removida com sucesso!" << endl;

                                }else{
                                    cout << "\nPosicao inválida!" << endl;
                                }

                            }else{
                                cout << "Nao há nenhuma playlist cadastrada!" << endl << endl;
                            }

                            cout << "Pressione ENTER para continuar..." << endl;
                            getchar();
                            system("clear || cls");

                            break;

                        case 3: // Exibe as playlists cadastradas

                            if(qtd_pl > 0){
                                for(int i = 0; i < qtd_pl; i++){ // Imprime o nome das playlists
                                    cout << i+1 << ". " << playlists[i].getNome() << endl;
                                }
                                cout << endl;

                            }else{
                                cout << "Nao há nenhuma playlist cadastrada!" << endl << endl;
                            }

                            cout << "Pressione ENTER para continuar..." << endl;
                            getchar();
                            system("clear || cls");

                            break;
                        
                        case 4: // Abrir uma playlist

							if(qtd_pl > 0){ // Verifica se há playlists cadastradas

								for(int i = 0; i < qtd_pl; i++){ // Imprime o nome das playlists
									cout << i+1 << ". " << playlists[i].getNome() << endl;
								}

								do{
									cout << "\nDigite o número da playlist que deseja abrir: ";
									cin >> posicao_pl;
									cin.ignore();
									if(posicao_pl < 1 || posicao_pl > qtd_pl){
										cout << "Playlist inválida! Escolha novamente!" << endl;
									}
								}while(posicao_pl < 1 || posicao_pl > qtd_pl);

								posicao_pl--; // Adequa a variável à faixa de números de indices (0 -> n-1)

								system("clear || cls");

								do{

									cout << "+--------------------------------+" << endl;
									cout << "|      MUSICAS DA PLAYLIST       |" << endl;
									cout << "+--------------------------------+" << endl;
									cout << "| 1 - Adicionar musica           |" << endl;
									cout << "| 2 - Remover musica             |" << endl;
									cout << "| 3 - Mover musica               |" << endl;
									cout << "| 4 - Exibir musicas da playlist |" << endl;
									cout << "| 5 - Reproduzir playlist        |" << endl;
									cout << "| 6 - Voltar                     |" << endl;
									cout << "+--------------------------------+" << endl;

									cout << "Digite uma opcao: ";

									// Lê a string da opcao e converte para inteiro
									getline(cin, s_op);
									stringstream op(s_op);
									op >> op3;

									system("clear || cls");

									switch(op3){

										case 1: // Adicionar musica

											if(musicas_sistema->getTamanho() > 0){ // Verfica se há musicas no sistema

												// Imprime as musicas do sistema
												musicas_sistema->imprime();

												cout << "\nDigite a posicao da musica que deseja adicionar em " << playlists[posicao_pl].getNome() << ": ";
												cin >> posicao1;
												cin.ignore();

												if(posicao1 > 0 && posicao1 <= musicas_sistema->getTamanho()){ // Verifica se a posicao é válida

													musica = *musicas_sistema->buscaMusicaPos(posicao1 - 1);

													if(playlists[posicao_pl].getLista()->buscaMusica(musica) == nullptr){ // Verifica se a musica já existe na playlist

														cout << "\nDeseja adicionar esta musica em uma posicao especifica de " << playlists[posicao_pl].getNome() << "? Nao(1) ou Sim(2): ";
														cin >> op4;
														cin.ignore();

														if(op4 == 1){
															// Insere no final
															if(playlists[posicao_pl].adicionaMusicaFim(musica)){ // Verifica se a insercao foi bem sucedida
																cout << "\nmusica adicionada na playlist com sucesso!" << endl;

															}else{
																cout << "\nErro ao adicionar musica na playlist!" << endl;
															}

														}else{
															// Insere em uma posicao especifica
															system("clear || cls");
															
															playlists[posicao_pl].imprime(playlists[posicao_pl].getLista()->buscaPos(0), 1); // Imprime as musicas da playlist

															cout << "\nDigite a posicao em que deseja inserir a musica: ";
															cin >> posicao2;
															cin.ignore();

															if(posicao2 > 0 && posicao2 <= playlists[posicao_pl].getLista()->getTamanho()){ // Verifica se a posicao é válida
																if(playlists[posicao_pl].adicionaMusicaPos(posicao2, musica)){ // Verifica se a insercao foi bem sucedida
																	cout << "\nmusica adicionada na playlist com sucesso!" << endl;
																
																}else{
																	cout << "\nErro ao adicionar musica na playlist!" << endl;
																}

															}else{
																cout << "\nPosicao inválida!" << endl;
															}
														}

													}else{
														cout << "\nEsta musica já está na playlist!" << endl;
													}

												}else{
													cout << "\nPosicao inválida!" << endl;
												}

											}else{
												cout << "Nao há musicas cadastradas no sistema!" << endl << endl;
											}

											cout << "Pressione ENTER para continuar..." << endl;
											getchar();
											system("clear || cls");

											break;
										
										case 2: // Remover musica
											
											if(playlists[posicao_pl].getLista()->getTamanho() > 0){ // Verifica se há musicas cadastradas

												playlists[posicao_pl].imprime(playlists[posicao_pl].getLista()->buscaPos(0), 1); // Imprime a lista de musicas da playlist para o usuário
												
												cout << "\nDigite o número da musica que deseja remover da playlist: ";
												cin >> posicao1;
												cin.ignore();

												if(posicao1 >= 1 && posicao1 <= playlists[posicao_pl].getLista()->getTamanho()){ // Verifica se a posicao digitada é válida
													playlists[posicao_pl].removeMusicaPos(posicao1); // Remove musica da playlist
													cout << "\nmusica removida com sucesso!" << endl;

												}else{
													cout << "\nPosicao inválida!" << endl;
												}

											}else{
												cout << "Nao há musicas para remover!" << endl << endl;
											}

											cout << "Pressione ENTER para continuar..." << endl;
											getchar();
											system("clear || cls");

											break;

										case 3: // Mover musica

											if(playlists[posicao_pl].getLista()->getTamanho() > 0){ // Verifica se há musica na playlist

												if(playlists[posicao_pl].getLista()->getTamanho() > 1){ // Verifica se é possivel mover musicas de lugar

													playlists[posicao_pl].imprime(playlists[posicao_pl].getLista()->buscaPos(0), 1);
													cout << endl;

													cout << "Digite a posicao atual da musica que deseja mover: ";
													cin >> posicao1;
													cin.ignore();

													if(posicao1 > 0 && posicao1 <= playlists[posicao_pl].getLista()->getTamanho()){ // Verifica se a posicao é válida
														cout << "Digite a posicao para qual deseja mover: ";
														cin >> posicao2;
														cin.ignore();

														if(posicao2 > 0 && posicao2 <= playlists[posicao_pl].getLista()->getTamanho()){ // Verifica se a posicao é válida

															playlists[posicao_pl].moveMusica(posicao1, posicao2); // Move a musica de lugar

															system("clear || cls");

															cout << "musica movida com sucesso!" << endl << endl;

															playlists[posicao_pl].imprime(playlists[posicao_pl].getLista()->buscaPos(0), 1); // Imprime nova organizacao das musicas
															cout << endl;

														}else{
															cout << "\nPosicao inválida!" << endl;
														}

													}else{
														cout << "\nPosicao inválida!" << endl;
													}

												}else{
													cout << "Nao há como mover musicas de lugar pois a playlist só tem uma musica!" << endl << endl;
												}

											}else{
												cout << "Nao há musicas nessa playlist!" << endl << endl;
											}

											cout << "Pressione ENTER para continuar..." << endl;
											getchar();
											system("clear || cls");

											break;
										
										case 4: // Exibir musicas da playlist

											if(playlists[posicao_pl].getLista()->getTamanho() > 0){ // Verifica se há musicas na playlist
												playlists[posicao_pl].imprime(playlists[posicao_pl].getLista()->buscaPos(0), 1); // Imprime as musicas da playlist
												cout << endl;

											}else{
												cout << "Nao há nenhuma musica nessa playlist!" << endl << endl;
											}

											cout << "Pressione ENTER para continuar..." << endl;
											getchar();
											system("clear || cls");

											break;

										case 5: // Tocar musica

											if(playlists[posicao_pl].getLista()->getTamanho() > 0){ // Verifica se a playlist tem musicas cadastradas

												system("clear || cls");

												prox_musica = playlists[posicao_pl].proxMusica(); // Chama a funcao e recebe o ponteiro de musica

												if(prox_musica != nullptr){ // Verifica se a reproducao das musicas já chegou ao fim
													cout << "Tocando " << prox_musica->getNome() << " - " << prox_musica->getArtista() << " da playlist " << playlists[posicao_pl].getNome() << "!" << endl << endl;

												}else{
													cout << "Você terminou de escutar essa playlist!" << endl << endl;
												}

											}else{
												cout << "Nao há nenhuma musica nessa playlist para tocar!" << endl << endl;
											}

											cout << "Pressione ENTER para continuar..." << endl;
											getchar();
											system("clear || cls");

											break;

										case 6: break; // Sair

										default:
											cout << "opcao inválida!" << endl;
											cout << "Pressione ENTER para continuar..." << endl;
											getchar();
											system("clear || cls");
											break;
									}

								}while (op3 != 6);

							}else{
								cout << "Nenhuma playlist cadastrada!\nAdicione uma playlist em \"Playlists\" no Menu Principal!" << endl << endl;
								cout << "Pressione ENTER para continuar..." << endl;
								getchar();
								system("clear || cls");
							}

							break;

						case 5: break; // Sair

                        default:
                            cout << "opcao inválida!" << endl;
                            cout << "Pressione ENTER para continuar..." << endl;
                            getchar();
                            system("clear || cls");
                            break;
                    }

                }while (op2 != 5);

                break;

            case 3: break; // Sair

            default: // opcao inválida
                cout << "opcao inválida!" << endl;
                cout << "Pressione ENTER para continuar..." << endl;
                getchar();
                system("clear || cls");
                break;
        }

    }while(op1 != 3);

    cout << "Programa encerrado!" << endl << endl;

    // Libera os espacos de memória alocados dinamicamente para as musicas do sistema e para as playlists
    delete musicas_sistema;
    delete[] playlists;

    return 0;
}