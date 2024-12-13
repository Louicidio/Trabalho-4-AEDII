#include <iostream>
#include <string>
using namespace std;

// livro que vai ser armazenado no nó
class Livro {
public:
    int isbn;
    string titulo;
    string autor;

    Livro(int isbn, string titulo, string autor) {
        this->isbn = isbn;
        this->titulo = titulo;
        this->autor = autor;
    }
};

// no da arvore
struct NodoAVL {
    Livro* livro;
    NodoAVL *esquerda, *direita;
    int altura;

    NodoAVL(Livro* livro) {
        this->livro = livro;
        esquerda = direita = nullptr;
        altura = 1;
    }
};

// arvore avl
class AVL {
private:
    NodoAVL* raiz;

    int altura(NodoAVL* nodo) {
        return nodo ? nodo->altura : 0;
    }

    int fatorBalanceamento(NodoAVL* nodo) {
        return nodo ? altura(nodo->esquerda) - altura(nodo->direita) : 0;
    }

    NodoAVL* rotacionarDireita(NodoAVL* y) {
        NodoAVL* x = y->esquerda;
        NodoAVL* T2 = x->direita;
        x->direita = y;
        y->esquerda = T2;
        y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
        x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
        return x;
    }

    NodoAVL* rotacionarEsquerda(NodoAVL* x) {
        NodoAVL* y = x->direita;
        NodoAVL* T2 = y->esquerda;
        y->esquerda = x;
        x->direita = T2;
        x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
        y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
        return y;
    }

    NodoAVL* inserir(NodoAVL* nodo, Livro* livro) {
        if (!nodo) return new NodoAVL(livro);
        if (livro->isbn < nodo->livro->isbn)
            nodo->esquerda = inserir(nodo->esquerda, livro);
        else if (livro->isbn > nodo->livro->isbn)
            nodo->direita = inserir(nodo->direita, livro);
        else
            return nodo;

        nodo->altura = 1 + max(altura(nodo->esquerda), altura(nodo->direita));

        int balanceamento = fatorBalanceamento(nodo);

        if (balanceamento > 1 && livro->isbn < nodo->esquerda->livro->isbn)
            return rotacionarDireita(nodo);

        if (balanceamento < -1 && livro->isbn > nodo->direita->livro->isbn)
            return rotacionarEsquerda(nodo);

        if (balanceamento > 1 && livro->isbn > nodo->esquerda->livro->isbn) {
            nodo->esquerda = rotacionarEsquerda(nodo->esquerda);
            return rotacionarDireita(nodo);
        }

        if (balanceamento < -1 && livro->isbn < nodo->direita->livro->isbn) {
            nodo->direita = rotacionarDireita(nodo->direita);
            return rotacionarEsquerda(nodo);
        }

        return nodo;
    }

    void inOrder(NodoAVL* raiz) {
        if (raiz) {
            inOrder(raiz->esquerda);
            cout << raiz->livro->isbn << " (" << raiz->livro->titulo << ", " << raiz->livro->autor << ") ";
            inOrder(raiz->direita);
        }
    }

public:
    AVL() {
        raiz = nullptr;
    }

    void inserir(Livro* livro) {
        raiz = inserir(raiz, livro);
    }

    void exibirLivros() {
        inOrder(raiz);
        cout << endl;
    }
};

// gerencia a biblioteca (adiciona e exibe)
class Biblioteca {
private:
    AVL arvore;

public:
    void adicionarLivro(int isbn, string titulo, string autor) {
        Livro* novoLivro = new Livro(isbn, titulo, autor);
        arvore.inserir(novoLivro);
        cout << "Livro adicionado: " << titulo << endl;
    }

    void exibirLivros() {
        cout << "Livros na Biblioteca: ";
        arvore.exibirLivros();
    }
};

// main
int main() {
    Biblioteca biblioteca;
    biblioteca.adicionarLivro(12345, "O Senhor dos Anéis", "J.R.R. Tolkien");
    biblioteca.adicionarLivro(67890, "O Hobbit", "J.R.R. Tolkien");
    biblioteca.adicionarLivro(11121, "Dom Quixote", "Miguel de Cervantes");
    biblioteca.adicionarLivro(31415, "1984", "George Orwell");

    biblioteca.exibirLivros();

    return 0;
}
