#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 50;
const int genN = 300;
const int k = 7;
const int muteRate = 5;
const int limit = 500000;
int pool[genN][N];
int newPool[genN][N];
int val[N][N];

int res[limit + 10];
mt19937 eng((unsigned int)time(NULL));
uniform_int_distribution<int> dist(0,N);
auto gene = bind(dist, eng);
void init() {
    //ifstream myFile("Data.txt");
    int i, j;
    for(i=0;i<N;i++) {
        for(j=0;j<N;j++) {
            //myFile >> val[i][j];
            val[i][j] = rand();
        }
    }
    //myFile.close();
    for(i=0;i<genN;i++) {
        vector<int> V;
        for(int j = 0; j < N; j++) V.push_back(j);
        random_shuffle(V.begin(),V.end());
        for(int j = 0; j < N; j++) pool[i][j] = V[j];
        //set<int> S;
        //for(int j= 0 ;j <N; j++) S.insert(pool[i][j]);
        //assert(S.size()==N);
    }
}

int cost(int gen){
	int ret = 0;
	for(int i = 0; i < N; i++) {
        ret += val[i][pool[gen][i]];
	}
	return ret;
}

void mutation(int gen){
    vector<int> shuffle_list;
    vector<int> shuffle_index;
    /*set<int>S;
    for(int i= 0; i < N;i ++) {
        S.insert(newPool[gen][i]);
    }
    if(S.size()!=N) {
        cout << "Wrong Mutation Start\n";
        cout << gen << '\n';
        for(int i = 0; i < N; i++) {
            cout << newPool[gen][i] << ' ';
        }
        cout << '\n';
    }*/
	for(int i=0; i<N; i++){
		int bias = rand()%100;
		if(bias < muteRate) {
            shuffle_list.push_back(newPool[gen][i]);
            shuffle_index.push_back(i);
		}
	}
	random_shuffle(shuffle_list.begin(),shuffle_list.end());
	for(int i = 0; i <shuffle_list.size();i++) {
        newPool[gen][shuffle_index[i]] = shuffle_list[i];
	}
}

void localOptimize(int gen){
	int loop = 10;
	while(loop--) {
        int v = gene()%N;
        for(int i = 0; i < N; i++) {
            if(i==v) continue;
            int c1 = newPool[gen][v];
            int c2 = newPool[gen][i];
            if(val[v][c1]+val[i][c2]<val[v][c2]+val[i][c1]) {
                swap(newPool[gen][v],newPool[gen][i]);
                break;
            }
        }
	}
}

int bestCost(){
	int ret = 0;
	for(int i=0; i<genN; i++){
		ret = max(ret, cost(i));
	}
	return ret;
}

void copyArr(int a, int b){
	for(int i=0; i<N; i++){
		newPool[a][i] = pool[b][i];
	}
}

int nextGen(){
    int i, j;
	int idx = 0;
	//cout << "gen start\n";
	for(i=0; i<genN; i+=2){
		if(cost(i) > cost(i+1)) copyArr(idx, i);
		else copyArr(idx, i+1);
		idx++;
	}
	//cout << "step 1\n";
	for(i=0; i<genN/2; i++){
		vector<int> del_index;
		vector<int> del_val;
		/*set<int> S3;
		for(int j = 0; j <N;j++) S3.insert(newPool[i][j]);
		if(S3.size()!=N) {
            cout << "Wrong S3\n";
            cout << i << '\n';
		}*/
		for(j=0; j<N; j++){
			int rnd = rand()&255;
			if(rnd&128) {
                newPool[idx][j] = newPool[i][j];
			}
			else {
                del_index.push_back(j);
                del_val.push_back(newPool[i][j]);
			}
		}
		for(int j = 0 ;j < N; j++) newPool[idx][j] = newPool[i][j];
		random_shuffle(del_index.begin(),del_index.end());
		for(int i = 0; i < del_val.size();i++) {
            newPool[idx][del_index[i]] = del_val[i];
		}
		/*set<int> S;
		for(int j= 0; j <N; j++) S.insert(newPool[idx][j]);
		if(S.size()!=N) {
            cout << i << '\n';
            exit(1);
		}*/
		idx++;
	}
	//cout << "step 2\n";
	for(i=0; i<genN; i++){
		mutation(i);
		localOptimize(i);
	}
	//cout << "step 3\n";
	vector<int> V;
	for(int j = 0; j < N; j++) V.push_back(j);
	random_shuffle(V.begin(),V.end());
	for(int j = 0; j < N; j++) {
        for(int i = 0; i <N; i++) {
            pool[V[j]][i] = newPool[j][i];
        }
	}
	return bestCost();
}


signed main(){
	init();

    cout << "init done\n";
	int i;
	int now;
	int ma = 0;
	for(i=1; i<=limit; i++){
		now = nextGen();
		ma = max(ma, now);
		if(i%1000 == 0) cout << i << ' ' << now << '\n';
		res[i] = now;
	}
	for(i=limit-10;i<=limit;i++) {
        cout << i << " : " << res[i] << '\n';
	}
	cout << "total maximum : " << ma;
}
