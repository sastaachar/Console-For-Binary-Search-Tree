#include<bits/stdc++.h>
#include<windows.h>
#define fr(a,i) for(int i=0;i<a;i++)
using namespace std;

class BsT {

  protected:
    struct node {
        int data;
        node *right;
        node *left;
    };

    node *mainHead;

  public:
    node * newNode(int x) {
        node *temp = new node;
        temp->data = x;
        temp->right = NULL;
        temp->left = NULL;
        return temp;
    }

    node *getParent(node *head,int x) {
        if( x > head->data ) {
            if(head->right)
                return getParent(head->right,x);
        }
        else {
            if(head->left)
                return getParent(head->left,x);
        }
        return head;
    }

    void insertNode(node *head,int x) {
        node *temp = newNode(x);
        if(head == NULL) {
            mainHead = temp;
            return;
        }
        head = getParent(head,x);
        if( x > head->data )
            head->right = temp;
        else
            head->left = temp;
        return;
    }

    void preOrderTraversal(node *head) {
        if(head) {
            cout<<head->data<<" ";
            preOrderTraversal(head->left);
            preOrderTraversal(head->right);
        }
        return ;
    }

    void inOrderTraversal(node *head) {
        if(head) {
            inOrderTraversal(head->left);
            cout<<head->data<<" ";
            inOrderTraversal(head->right);
        }
        return ;
    }

    void postOrderTraversal(node *head) {
        if(head) {
            postOrderTraversal(head->left);
            postOrderTraversal(head->right);
            cout<<head->data<<" ";
        }
        return ;
    }

    void levelOrderTraversal(node *head) {
        queue< node* > nodes;
        nodes.push(head);
        do {
            head = nodes.front();
            nodes.pop();
            cout<<head->data<<" ";
            if(head->left)
                nodes.push(head->left);
            if(head->right)
                nodes.push(head->right);

        } while(!nodes.empty());
    }

    void bstPrint(node *head) {
        queue< node* > nodes;
        nodes.push(head);
        do {
            head = nodes.front();
            nodes.pop();
            cout<<head->data<<" ";
            if(head->left)
                nodes.push(head->left);
            else
                nodes.push(NULL);
            if(head->right)
                nodes.push(head->right);
            else
                nodes.push(NULL);

        } while(!nodes.empty());
    }

    node* findMin(node* root) {
        if(root->left)
            return findMin(root->left);
        return root;
    }

    bool found;
    node* deleteNode(node* root, int x) {
        //first we find the node
        found = false;
        if(root == NULL)
            return root;
        if(root->data > x)
            root->left = deleteNode(root->left, x);
        else if(root->data < x)
            root->right = deleteNode(root->right, x);
        else {
            found = true;
            if(root->right == NULL && root->left == NULL) {
                delete root;
                root = NULL;
            } else if(root->right == NULL) {
                node* temp = root->left;
                delete root;
                root = temp;
            } else if(root->left == NULL) {
                node* temp = root->right;
                delete root;
                root = temp;
            }  else {
                node* temp = findMin(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
            return root;
        }
    }

    bool deleteNode(int x) {
        mainHead = deleteNode(mainHead, x);
        return found;
    }

    node *getHead() {
        return mainHead;
    }

    BsT() {
        mainHead = NULL;
    }

};

class BsT_Console {
    //use the bst class
    BsT tree;
    //the argument to be passed
    vector<int> args;
    string cmnd;
  public:
    int argsPharse(string s, int pos1, int pos2) {
        bool neg = false;
        if( s[pos1+1] == '-' ) {
            neg = true;
            ++pos1;
        }
        int num = 0;
        for(int i=pos1+1; i<pos2; i++) {
            num *= 10;
            num += s[i]-48;
        }
        if(neg)
            num *= -1;
        return num;
    }
    void start_console() {
        this->startAnim();
        while(true) {
            cout<<"-->";
            getline(cin, cmnd);
            args = commandDecoder(cmnd);
            bool noExit = actionPerformed(args);
            if(!noExit)
                break;
        }

    }
    void startAnim() {
        //just fancy stuff
        for(int i=0;i<=50;i++) {
            cout<<"Starting Console......\n";
            cout<<"|";
                for(int j=0;j<=50;j++) {
                    if(j <= i) {
                        cout<<"#";
                        Sleep(0.5);
                    } else {
                        cout<<" ";
                    }
                }
            cout<<"|";
            system("cls");
        }
    }
    vector<int> commandDecoder(string s) {
        vector<int> args;
        //can use size_t and npos , but i wont
        if(s.find("insert") < s.length()) {
            args.push_back(1);
            int pos1 = s.find("(");
            int pos2 = s.find(")");
            int arg1 = argsPharse(s, pos1, pos2);
            args.push_back(arg1);
        } else if(s.find("delete") < s.length()) {
            args.push_back(2);
            int pos1 = s.find("(");
            int pos2 = s.find(")");
            int arg1 = argsPharse(s, pos1, pos2);
            args.push_back(arg1);
        } else if(s.find("preOrder") < s.length()) {
           args.push_back(3);
        } else if(s.find("inOrder") < s.length()) {
            args.push_back(4);
        } else if(s.find("postOrder") < s.length()) {
            args.push_back(5);
        } else if(s.find("levelOrder") < s.length()) {
            args.push_back(6);
        } else if(s.find("random") < s.length()) {
            args.push_back(7);
            int pos1 = s.find("(");
            int pos2 = s.find(")");
            int arg1 = argsPharse(s, pos1, pos2);
            args.push_back(arg1);
        } else if(s.find("printBst") < s.length()) {
            args.push_back(8);
        } else if(s.find("exit") < s.length()) {
            args.push_back(9);
        } else if(s.find("help") < s.length()) {
            args.push_back(10);
        } else if(s.find("clear") < s.length()) {
            args.push_back(11);
        }  else {
            args.push_back(-1);
        }
        return args;
    }
    bool actionPerformed(vector<int> args) {
        int ch = args[0];
        if(ch == 1) {
            //insert
            int x = args[1];
            tree.insertNode(tree.getHead(), x);
        }
        else if(ch == 2) {
            //delete
            int x = args[1];
            if(!tree.deleteNode(x))
                cout<<"is the value there in the BST ??????????????????\n";
        }
        else if(ch == 3) {
            //preOrder
            tree.preOrderTraversal(tree.getHead());
            cout<<"\n";
        }
        else if(ch == 4) {
            //inOrder
            tree.inOrderTraversal(tree.getHead());
            cout<<"\n";
        }
        else if(ch == 5) {
            //postOrder
            tree.postOrderTraversal(tree.getHead());
            cout<<"\n";
        }
        else if(ch == 6) {
            //postOrder
            tree.levelOrderTraversal(tree.getHead());
            cout<<"\n";
        }
        else if(ch == 7) {
            //random
            int x = args[1];
            fr(x,i)
                tree.insertNode(tree.getHead(),rand()%101);
        }
        else if(ch == 8) {
            //print
            tree.bstPrint(tree.getHead());
        }
        else if(ch == 9) {
            //exit
            cout<<"Bye!!\n";
            return false;
        }
        else if(ch == 10) {
            //call help function
            consoleHelp();
        }
        else if(ch == 11) {
            system("cls");
        }
        else {
            if(cmnd.length() != 0)
                cout<<"'"<<cmnd<<"' is not recognized as an internal or external command, operable program or batch file.\n";
        }
        return true;
    }

    void consoleHelp(int arg = -1) {
        //under development
        cout<<"insert\n"
            <<"delete\n"
            <<"preOrder\n"
            <<"inOrder\n"
            <<"postOrder\n"
            <<"random\n"
            <<"printBst\n"
            <<"clear\n"
            <<"exit\n";
    }

    BsT_Console() {
        cout<<"Start\n";
    }

};

int main() {
    (new BsT_Console)->start_console();
    return 0;
}



