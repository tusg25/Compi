// Linear Sieve and multiplication func example(currently mu)
const int rLIM=1e6;
int f[rLIM],is_com[rLIM];
vector<int> pr;
void sieve(){
    f[1]=1; // Assign f[1]
    for(int i=2;i<rLIM;++i){
        if(!is_com[i]) pr.push_back(i),f[i]=-1;
        for(auto &it: pr){
            if(it*i>=rLIM) break;
            is_com[i*it]=1;
            if(i%it==0){
                f[i*it]=0; // f[i*it] based on it power
                break;
            }else{
                f[i*it]=f[i]*f[it]; // multiplicative property
            }
        }
    }
}
//Erasthosthenes sieve
const int rLIM=1e6;
int lpd[rLIM]; //largest prime divsor
vector<int> pr;
void sieve(){
    lpd[1]=1;
    for(int i=2;i<rLIM;++i){
        if(!lpd[i]){
            pr.push_back(i);
            for(int j=i;j<rLIM;j+=i){
                lpd[j]=i; 
            }
        }
    }
}
