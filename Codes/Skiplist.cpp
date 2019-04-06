// Skiplist just like Leftist Trees having find_by_order and order_of_key in O(log n)
struct skip_list{
    struct node{
        int num;
        vector<node*> nxt;
        vector<node*> prv;
        vector<int> nxt_len;
        vector<int> prv_len;
        node(int x):num(x){}
    } *begin,*end;

    int size;

    skip_list(){
        size=0;
        begin=new node(-INF);
        end  =new node(+INF);
        begin->nxt={  end};
        end  ->prv={begin};
        begin->nxt_len=end->prv_len={1};
    }

    node *find(int x){
        node *cur=begin;
        int cl=begin->nxt.size();
        while(cl>=0){
            while(cl<cur->nxt.size() && cur->nxt[cl]->num<x)
            	cur=cur->nxt[cl];
            cl--;
        }
        return cur->nxt[0];
    }

    node *find_by_order(int x){
        node *cur=begin;
        int cl=begin->nxt.size();
        int cx=-1;
        while(cl>=0){
            while(cl<cur->nxt.size() && cx+cur->nxt_len[cl]<x){
                cx+=cur->nxt_len[cl];
                cur=cur->nxt[cl];
            }
            cl--;
        }
        return cur->nxt[0];
    }

    int order_of_key(int x){
    	node *cur=begin;
        int cl=begin->nxt.size();
        int cx=0;
        while(cl>=0){
            while(cl<cur->nxt.size() && cur->nxt[cl]->num<x){
                cx+=cur->nxt_len[cl];
                cur=cur->nxt[cl];
            }
            cl--;
        }
        return cx;
    }

    void insert(node *r,int x){
        node *it=new node(x);
        int cl=0;
        int c_len=1;
        do{
            if(cl==begin->nxt.size()){
                begin->nxt.push_back(end);
                end  ->prv.push_back(begin);
                begin->nxt_len.push_back(size+1);
                end  ->prv_len.push_back(size+1);
            }
            while(cl==r->prv.size()){
                c_len+=r->nxt_len[cl-1];
                r=r->nxt[cl-1];
            }
            it->nxt.push_back(r);
            it->prv.push_back(r->prv[cl]);
            it->nxt_len.push_back(c_len);
            it->prv_len.push_back(r->prv_len[cl]-c_len+1);
            r->prv[cl]->nxt[cl]=it;
            r->prv[cl]->nxt_len[cl]=it->prv_len[cl];
            r->prv[cl]=it;
            r->prv_len[cl]=c_len;
            cl++;
        }while(rand()&1);

        while(cl<begin->nxt.size()){
            while(cl==r->prv.size()) r=r->nxt[cl-1];
            r->prv_len[cl]++;
            r->prv[cl]->nxt_len[cl]++;
            cl++;
        }
        size++;
    }

    void insert(int x){
    	insert(find(x),x);
    }

    void erase(node *it){
        int cl=0;
        for(;cl<it->nxt.size();cl++){
            it->nxt[cl]->prv_len[cl]=it->prv[cl]->nxt_len[cl]=it->prv_len[cl]+it->nxt_len[cl]-1;
            it->nxt[cl]->prv[cl]=it->prv[cl];
            it->prv[cl]->nxt[cl]=it->nxt[cl];
        }
        node *r=it->nxt[cl-1];
        for(;cl<begin->nxt.size();cl++){
            while(cl==r->prv.size()) r=r->nxt[cl-1];
            r->prv[cl]->nxt_len[cl]--;
            r->prv_len[cl]--;
        }
        delete it;
        size--;
    }

    void erase(int x){
        erase(find(x));
    }
    void erase_by_order(int x){
        erase(find_by_order(x));
    }

    int &at(int x){
        return find_by_order(x)->num;
    }
    int &operator [](int x){
        return at(x);
    }
};
