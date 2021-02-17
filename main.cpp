#include <iostream>
#include <string>

using namespace std;

class No{
private:
    string v;
    No* proximo;
public:
    No(string v){//CONSTRUTOR
        this -> v = v;
        this -> proximo = NULL;
    }
    string obterValor(){
        return v;
    }
    No* obterProximo(){
        return proximo;
    }
    void setProximo(No* p){
        proximo = p;
    }
};

class Lista{
private:
    No* cabeca;
    No* cauda;
public:
    Lista(){//CONSTRUTOR SEM PARAMETRO
        cabeca = NULL;
        cauda = NULL;
    }
    Lista(string v){//CONSTRUTOR COM PARAMETRO
        cabeca = new No(v);
        cauda = cabeca;     
    }
    virtual ~Lista(){//DESTRUTOR
        delete cabeca;
    }
    void mostrar(){
        cout<<"/n imprimindo todos os elementos..."<<endl;
        No* c = cabeca;
        if (vazia()){
            cout<<"a lisa nao possui elementos"<<endl;    
        }
        else{
            while(c){
                cout << c->obterValor() << endl;
                c = c->obterProximo();
            }
            cout << endl;
        }

    }

    bool vazia(){
        return (cabeca == NULL);
    }

    void inserir_inicio(string v){
        No* novo_no = new No(v);
        if(vazia()){
            cabeca = novo_no;
            cauda = novo_no;
        }else{
            novo_no->setProximo(cabeca); 
            cabeca = novo_no;
        }
    }

    void inserir_final(string v){
        No* novo_no = new No(v);
        if(vazia()){
            cabeca = novo_no;
            cauda = novo_no;
        }
        else{
            cauda -> setProximo(novo_no);
            cauda = novo_no;
        }
    }

    int tamanho(){
        if(vazia()){
            return 0;
        }
        No* c = cabeca;
        int tam = 0;
        do{
            c = c->obterProximo();
            tam++;

        }while(c != NULL);
    }

    bool existe(string v){
        No* c = cabeca;
        while (c){
            if(c->obterValor() == v){
                return true;
            }
            c = c-> obterProximo();
        }
    }

    void remover(){//REMOCAO NO FINAL
        if(!vazia()){
            if(cabeca -> obterProximo() == NULL){
                cabeca = NULL;
            }
            else if (cabeca ->obterProximo() -> obterProximo() == NULL){
                cabeca -> setProximo(NULL);
            }
            else{
                No* ant_ant = cabeca;
                No* ant = cabeca ->obterProximo();
                No* corrente = cabeca->obterProximo() ->obterProximo();

                while(corrente){
                    No* aux = ant;
                    ant = corrente;
                    ant_ant = aux;
                    corrente = corrente ->obterProximo();
                }
                delete ant_ant ->obterProximo();
                ant_ant -> setProximo(NULL);
                cauda = ant_ant;
            }

        }
    }

};


int main(){


    cout<<"##########################################"<<endl;
    cout<<"#                 MENU                   #"<<endl;
    cout<<"##########################################"<<endl;
    cout<<"#   1                Adicionar musica    #"<<endl;
    cout<<"#----------------------------------------#"<<endl;
    cout<<"#   2                  Remover musica    #"<<endl;
    cout<<"#----------------------------------------#"<<endl;
    cout<<"#   3                Mostrar playlist    #"<<endl;
    cout<<"#----------------------------------------#"<<endl;
    cout<<"##########################################"<<endl;



    Lista l;
    if(l.vazia()){
        cout<<"LISTA VAZIA"<<endl;
    }
    else{
        cout <<"LISTA NAO VAZIA!" <<endl;
    }
    
    l.inserir_inicio("Nothing else matters");
    l.inserir_final("Sicko Mode");
    l.inserir_final("Black Eyed Peas");
    l.mostrar();
    


    return 0;
}