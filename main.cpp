#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
ifstream f("in.txt");
//ofstream o("out.txt");
//ofstream
int n,p,tip_op,len,x,keys[100],nrkeys,ola,ok,pp,xx,ooo;
char s[20];
//nod-ul din arbore
struct Treep
{
    int key; //data
    int priority; // prioritatea
    Treep *left,*right;
    Treep(int key) //constructor
    {this->key=key;
    this->priority=rand() %100; //val random de la 0 la 100
    this->left=nullptr;// nu e legat de nimic
    this->right=nullptr; //nu e legat de nimic
    }
};
void rotateS(Treep* &root) //rotesc dreapta
{
    Treep* a =root->right;
    Treep* b =root->right->left;

    //
    a->left=root;
    root->right=b;
    root=a;
}
void rotateD(Treep* &root)
{
    Treep* d = root->left;
    Treep* c = root->left->right;
    d->right=root;
    root->left=c;
    root=d;
}
void inserare(Treep *&root,int key)
{
    if(root== nullptr)
    {
        root=new Treep(key);
        return;
    }
    if(key < root->key) //daca ce vreu sa inserez e mai mica decat valoare radacinii inserez in stanga
    {
        inserare(root->left,key);
        //rotesc arborele dreapta daca prop de prioritate e incalcata
        if(root->left !=nullptr && root->left->priority > root->priority)
            rotateD(root);
    }
    else
    {
        inserare(root->right,key);
        //rotesc arborele stanga daca prop de prio e incalcata
        if(root->right != nullptr && root->right->priority > root->priority)
            rotateS(root);
    }
}
//cauta o valoare
bool searchVal(Treep *root,int val)
{
    if(root == nullptr)
        return false;
    if(root->key == val)
        return true;
    if (val < root->key)
        return searchVal(root->left,val);
    else return searchVal(root->right,val);

}
void deleteval(Treep* &root,int val)
{
    if(root == nullptr) // nu exista arbore
        return;
    if ( val < root->key)  //daca val e mai mica merg in stanga
        deleteval(root->left,val);
    else if (val >root->key) // daca val e mai mare merg in dreapta
        deleteval(root->right,val);
        else
        {
            //Avem 3 cazuri aici
            // I nodul pe care il stergem nu are copii
            if(root -> left == nullptr && root->right == nullptr)
            {
                delete root;
                root=nullptr;
            }
            //are 2 copii
            else if (root->left && root->right)
            {
                if(root->left->priority < root->right->priority)
                {
                    rotateS(root);
                    deleteval(root->left,val);
                }
                else
                {
                    rotateD(root);
                    deleteval(root->right,val);

                }
            }
            // are doar un copil
            else
            {
                Treep* fiu = (root->left)? root->left:root->right;
                Treep* asta = root;
                root= fiu;
                delete asta;

            }

        }
}
void afis(Treep* root,int val1,int val2)
{
    if (root != nullptr)
    {
    afis(root->left,val1,val2);
    if(root->key > val1 && root->key <val2)
        cout<<root->key<<" ";
    afis(root->right,val1,val2);
    }

}
void succ(Treep *root,int val,int &mini)
{
    if(root != nullptr)
    {
        succ(root->left,val,mini);
        if(root->key >= val)
            {mini=root->key;
            return;
            }
        succ(root->right,val,mini);
    }
}
int main()
{
    f>>n;
    tip_op=0;
    int x=0;
    nrkeys=0;

    Treep* root = nullptr;
    // Citirea celor n operatii
    for(int i=1;i<=n+1;i++)
    {
        f.getline(s,256);
        tip_op=int(s[0])-48;
         //tip_op are tipul de operatie
        if (tip_op == 1)
        {
        p=0;
        len=strlen(s);
        for(int j=2;j<len;j++)
            {
                x=s[j]-48;
                p=p*10 + x;
            }
        inserare(root,p);

        }
        if(tip_op == 2)
        {
            p=0;
        len=strlen(s);
        for(int j=2;j<len;j++)
            {
                x=s[j]-48;
                p=p*10 + x;
            }
        while ( searchVal(root,p) == true)
                deleteval(root,p);


        }
        if(tip_op == 3)
        {
        p=0;
        len=strlen(s);
        for(int j=2;j<len;j++)
            {
                x=s[j]-48;
                p=p*10 + x;
            }
        if (searchVal(root,p)== true )
            cout<<"1"<<endl;
        else cout<<"0"<<endl;
        }
        if(tip_op == 4)
        {
            p=0;
        len=strlen(s);
        for(int j=2;j<len;j++)
            {
                x=s[j]-48;
                p=p*10 + x;
            }
        int mini=-1;
        succ(root,p,mini);
        cout<<mini<<endl;


        }
        if(tip_op == 5)
        {
        p=0;
        len=strlen(s);
        for(int j=2;j<len;j++)
            {
                x=s[j]-48;
                p=p*10 + x;
            }
        ok=0;
        for(int o=p;i>=1;o--)
        {
            if(searchVal(root,o)== true)
                {ok=1;
                ola=o;
                break;
                }
        }
        if(ok == 1)
            cout<< ola<<endl;
        else cout <<"-1"<<endl;

        }
        if(tip_op == 6)
        {
            p=0;
            len=strlen(s);
            pp=0;
            xx=0;
            for(int j=2;j<len;j++)
            {
                if (s[j]==' ')
                    {ooo=j;
                    break;

                    }
                x=s[j]-48;
                p=p*10 + x;
            }
            int j=ooo+1;
            while (j < len)
            {
                xx=s[j]-48;
                pp=pp*10 + xx;
                j=j+1;
            }
            afis(root,p,pp);
            cout<<endl;

        }

    }
    return 0;
}
