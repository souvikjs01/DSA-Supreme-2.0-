#include<iostream>
#include<queue>

using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;

    Node(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};
Node* insertIntoBST(Node* root, int data){
    if(root == NULL){
        root = new Node(data);
        return root;
    }
    
    if(data < root->data){
        root->left = insertIntoBST(root->left, data);
    }
    else{
        root->right = insertIntoBST(root->right, data);
    }
    return root;
}
void createBST(Node* &root){
    int data;
    cout << "enter data: " << endl;
    cin >> data;

    while(data != -1){
        root = insertIntoBST(root, data);
        cin >> data;
    }
}
void levelorderTraversal(Node* root){
    queue<Node*> q;
    q.push(root);
    q.push(NULL);
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        if(temp == NULL){
            cout << endl;
            if(!q.empty()){
                q.push(NULL);
            }
        }
        else{
            cout << temp->data << " ";
            if(temp->left != NULL){
                q.push(temp->left);
            }
            if(temp->right != NULL){
                q.push(temp->right);
            }
        }
    }
}
void inorder(Node* root){
    if(!root){
        return ;
    }
    // LNR
    
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
void preOrder(Node* root){
    if(!root) return;

    // NLR
    preOrder(root->left);
    cout << root->data << " ";
    preOrder(root->right);
}
void postOrder(Node* root){
    if(!root) return ;

    // LRN
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}
Node* minValue(Node* root){
    if(root == NULL){
        return NULL;
    }
    Node* temp = root;
    while(temp->left != NULL){
        temp = temp->left;
    }
    return temp;
}
Node* maxValue(Node* root){
    if(root == NULL) {
        return NULL;
    }
    Node* temp = root;
    while(temp->right != NULL){
        temp = temp->right;
    }
    return temp;
}
bool searchBST(Node* root, int target){
    if(!root) return false;

    if(root->data == target) return true;

    if(target < root->data){
        searchBST(root->left, target);
    }else{
        searchBST(root->right, target);
    }
}
Node* deleteNodeOfBST(Node* root, int target){
    if(root == NULL) return NULL;

    if(root->data == target){
        // 4 cases
        // for leaf node
        if(root->left == NULL && root->right == NULL){
            delete root;
            return NULL;
        }
        else if(root->left != NULL && root->right == NULL){
            Node* childNode = root->left;
            delete root;
            return childNode;
        }
        else if(root->left == NULL && root->right != NULL){
            Node* childNode = root->right;
            delete root;
            return childNode;
        }
        else{
            Node* temp = maxValue(root->left);
            root->data = temp->data;
            root->left = deleteNodeOfBST(root->left, temp->data);
            return root;
        }
    }

    // recursion calls
    if(target < root->data){
        root->left = deleteNodeOfBST(root->left, target);
    }
    else{
        root->right = deleteNodeOfBST(root->right,target);
    }
    return root;
}

int main(){
    Node* root = NULL;
    createBST(root);

    levelorderTraversal(root);

    cout << endl;
    cout << "inorder: " << endl;
    inorder(root);
    cout << endl << "preorder: " << endl;
    preOrder(root);
    cout << endl << "postOrder: "<< endl;
    postOrder(root);
    cout << endl;

    Node* ans = minValue(root);
    if(ans){
        cout << "minimum value of the BST: " << ans->data << endl;
    }else{
        cout << "no minimum value exist" << endl;
    }

    Node* ans2 = maxValue(root);
    if(ans2){
        cout << "maximum value of the BST is: " << ans2->data << endl;
    }else{
        cout << "no maximum element exist " << endl;
    }
    
    // int target;
    // cout << "enter the targeted element " << endl;
    // cin >> target;
    // bool ans3 = searchBST(root, target);
    // if(ans3 == true){
    //     cout << "the element is present in the BST" << endl;
    // }else{
    //     cout << "the element isn't present in the BST" << endl;
    // }

    int target;
    cout << "enter target value to be deleted " << endl;
    cin >> target;
    while(target != -1){
        deleteNodeOfBST(root, target);
        cout << "printing level order traversal of BST "<<endl;
        levelorderTraversal(root);
        cout << "enter target value to be deleted " << endl;
        cin >> target;
    }

    return 0;
}