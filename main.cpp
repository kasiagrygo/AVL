#include <bits/stdc++.h>

using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
};

// Funkcja do obliczania wysokosci wezla
int height(Node* n) {
    if (n == nullptr)
        return 0;
    return n->height;
}

// Funkcja do aktualizowania wysokosci wezla
void updateHeight(Node* n) {
    int leftHeight = height(n->left);
    int rightHeight = height(n->right);
    n->height = 1 + max(leftHeight, rightHeight);
}

// Funkcja do obliczania roznicy wysokosci pomiedzy lewym i prawym poddrzewem
int getBalance(Node* n) {
    if (n == nullptr)
        return 0;
    return height(n->left) - height(n->right);
}

// Funkcja do obrotu w prawo
Node* rotateRight(Node* n) {
    Node* left = n->left;
    Node* leftRight = left->right;

    left->right = n;
    n->left = leftRight;

    updateHeight(n);
    updateHeight(left);

    return left;
}

// Funkcja do obrotu w lewo
Node* rotateLeft(Node* n) {
    Node* right = n->right;
    Node* rightLeft = right->left;

    right->left = n;
    n->right = rightLeft;

    updateHeight(n);
    updateHeight(right);

    return right;
}

// Funkcja do wstawiania nowego wezla
Node* insert(Node* n, int key) {
    if (n == nullptr) {
        Node* newNode = new Node();
        newNode->key = key;
        newNode->height = 1;
        return newNode;
    }

    if (key < n->key)
        n->left = insert(n->left, key);
    else if (key > n->key)
        n->right = insert(n->right, key);
    else
        return n;

    updateHeight(n);

    int balance = getBalance(n);

    if (balance > 1 && key < n->left->key)
        return rotateRight(n);
    if (balance < -1 && key > n->right->key)
        return rotateLeft(n);
    if (balance > 1 && key > n->left->key) {
        n->left = rotateLeft
            (n->left);
    return rotateRight(n);
}
if (balance < -1 && key < n->right->key) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

return n;
}

// Funkcja do usuwania wezla
Node* remove(Node* n, int key) {
    if (n == nullptr)
        return n;

    if (key < n->key)
        n->left = remove(n->left, key);
    else if (key > n->key)
        n->right = remove(n->right, key);
    else {
        if ((n->left == nullptr) || (n->right == nullptr)) {
            Node* temp = n->left ? n->left : n->right;
            if (temp == nullptr) {
                temp = n;
                n = nullptr;
            } else
                *n = *temp;
            delete temp;
        } else {
            Node* temp = n->right;
            while (temp->left != nullptr)
                temp = temp->left;
            n->key = temp->key;
            n->right = remove(n->right, temp->key);
        }
    }

    if (n == nullptr)
        return n;

    updateHeight(n);

    int balance = getBalance(n);

    if (balance > 1 && getBalance(n->left) >= 0)
        return rotateRight(n);
    if (balance > 1 && getBalance(n->left) < 0) {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    if (balance < -1 && getBalance(n->right) <= 0)
        return rotateLeft(n);
    if (balance < -1 && getBalance(n->right) > 0) {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }

    return n;
}

// Funkcja do wyszukiwania wezla
Node* search(Node* n, int key) {
    if (n == nullptr || n->key == key)
        return n;

    if (n->key < key)
        return search(n->right, key);

    return search(n->left, key);
}

void KLP(Node* n) {
    if (n == nullptr)
        return;
    cout << n->key << " ";
    KLP(n->left);
    KLP(n->right);
}

void treeLevelOrder(Node* root) {
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        cout << curr->key << " ";
        if (curr->left != nullptr)
            q.push(curr->left);
        if (curr->right != nullptr)
            q.push(curr->right);
    }
}


void weightAndLevel(Node* root, int key, int level) {
    if (root == nullptr) {
        cout << "Element nie znajduje się w drzewie." << endl;
        return;
    }
    if (root->key == key) {
        cout << "Waga elementu: " << height(root) << endl;
        cout << "Poziom elementu: " << level << endl;
    } else if (key < root->key) {
        weightAndLevel(root->left, key, level+1);
    } else {
        weightAndLevel(root->right, key, level+1);
    }
}


ifstream in;
ofstream out;

int main()
{
    in.open("InTest1.txt");
    out.open("OutTest2.txt");

    Node* root = nullptr;

    int a;

    srand(time(NULL));

    /*while (in >> a) {
        root = insert(root, a);
    }*/

    int t[50];
    for(int i=0;i<20;i++){
        t[i]=rand()%99+1;
        root = insert(root, t[i]);
        cout<<t[i]<<" ";
    }

    cout<<endl;
    cout<<"MENU"<<endl;
    cout<<"1. Wypisywanie w kolejnosci KLP"<<endl;
    cout<<"2. Dodaj element"<<endl;
    cout<<"3. Usun element"<<endl;
    cout<<"4. Wypisz elementy poziomami"<<endl;
    cout<<"5. Waga i poziom"<<endl;
    cout<<"6. Koniec";
    cout<<endl;

    int l1, l2;
    while(1==1){
        cout<<"Co chcesz zrobic?: ";
        cin>>l1;
        cout<<endl;
        if(l1==1){
            KLP(root);
        }
        if(l1==2){
            cout<<"Podaj liczbe do wstawienia: ";
            cin>>l2;
            insert(root, l2);
            cout<<endl;
        }
        if(l1==3){
            cout<<"Podaj liczbe do usuniecia: ";
            cin>>l2;
            remove(root, l2);
            cout<<endl;
        }
        if(l1==4){
            treeLevelOrder(root);
        }
        if(l1==5){
            cout<<"Podaj liczbe: ";
            cin>>l2;
            weightAndLevel(root, l2, 0);
        }
        if(l1==6){
            break;
        }
    }


    in.close();
    out.close();
    return 0;
}


