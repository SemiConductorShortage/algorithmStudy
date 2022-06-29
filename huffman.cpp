#include <iostream>//for output
#include <list>    //for list
#include <numeric> //for accumulate
#include <vector>
#include <map>
#include <string> //we'll be storing the binary codes in a string (very efficient!!!!!!!!!!!)

struct tree {
    int size = sizeof(struct tree);
    char character;
    tree *left, *right;
};
tree* createNode(char character){
    tree* node_n = new tree;
    node_n->left = NULL;
    node_n->right = NULL;
    node_n->character = character;
    return node_n;
};

std::map<char, std::string> encodeMap;


struct earlyTermination : std::exception {const char* what() const noexcept {return "No More Node Info, haven't reached a leaf yet!!\n";}};

typedef std::vector< std::pair<char,int> > vectorPair;


vectorPair huffmanWeightVec(std::string message){ //O(2n+n^2), not the best, but can be shortened with a better sorting algorithm for pairs
    std::map<char,int> huffman;
    for (char i : message){ //O(n)
        huffman[i]==0 ? huffman[i]=1 : huffman[i]+=1;
    }
    vectorPair vec;
    for (auto i : huffman){ //O(n), currently O(2n)
        vec.push_back(std::make_pair(i.first,i.second));
    }
    for (int i = 0; i < vec.size(); i++){ //nested loop for bubblesort, O(n^2), so total time complexity for calculating weight is O(2n+n^2), sorry(!)
        for (int j = 0; j < vec.size(); j++){
            if (vec[i].second < vec[j].second)std::swap(vec[i],vec[j]);
        }
    }
    return vec;
}

void store(tree* root, std::string str){
    if (root==NULL)
        return;
    
    if (root->right==NULL && root->left==NULL){
        encodeMap[root->character]= str;
    }
    store(root->left, str + "0");
    store(root->right, str + "1");
}



int main(){
    std::list<tree> treeList;
    std::string string = "hello stranger on the internet, this is my crappy implementation of huffman coding";
    vectorPair vec = huffmanWeightVec(string);
    for (auto i : vec){
        std::cout<<i.first<<" "<<i.second<<std::endl;
    } //debug stuff just to show the sorting of pairs
    tree* previousTree = (tree *)malloc(sizeof(struct tree)); //literally just "new tree"

    tree* _firstLeaves = new tree;
    _firstLeaves->right = createNode(vec[0].first);
    _firstLeaves->left = createNode(vec[1].first);

    previousTree = _firstLeaves;



    int i=2;
    while (i<vec.size()){
        std::cout<<"looping\n";
        tree* node = new tree;
        node->right = new tree;
        node->left = createNode(vec[i].first);
        node->right = previousTree;
        previousTree = node;

        i++;
    }

    std::cout<<"done\n\n";
    //now we check if the binary tree is made properly
    tree* root = previousTree; //syntax yummy
    store(root, "");


    std::cout<<"binary of compressed string : ";
    for (char i : string){
        std::cout << encodeMap[i];
    }

    
    std::cout<<'\n';
    


}