class unf{
public:
    int size;
    vector<int> sz;
    vector<int> id;
    int numberofcomponents;
    unf(int size){
        unf::size = size;
        size = numberofcomponents;

        for(int i=0;i<size;i++){
            id.push_back(i);
            sz.push_back(1);
        }
    }
    int find(int p){
        int root = p;
        while(root!=id[root]) root = id[root];

        while(p!=root){
            int next = id[p];
            id[p] = root;
            p = next;
        }
        return root;
    }
    bool connected(int p, int q){
        return find(p)==find(q);
    }
    int componentsize(int p){
        return sz[find(p)];
    }
    int sizeunf(){
        return size;
    }
    int components(){
        return numberofcomponents;
    }
    void unify(int a, int b){
        int roota = find(a);
        int rootb = find(b);
        int sza = componentsize(roota);
        int szb = componentsize(rootb);
        if(sza > szb){
            id[rootb] = roota;
            sz[roota] +=sz[rootb];
            sz[roota] = 0;

        } else {
            id[roota] = rootb;
            sz[rootb] +=sz[roota];
            sz[rootb] = 0;
        }
        numberofcomponents--;
    }

    
};
