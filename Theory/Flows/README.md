# Flows 
1)  **Offline Paging/Caching**: Storage capacity is $k$ (i.e. at a time-frame atmost $k$ variable can be loaded into memory), you have $n$ job requests (each request require a variable to be processed) in sequencing. Required to do $i$-th job in $i$-th timeframe (so required variable should be in memory). Initially storage is empty. Loading $i$-th variable in memory cost $c[i]$ (when storage is full you need to replace it with something). Find best (min-cost) variable loading scheduling.
> Note: Can be modified to have more than one variable per job and preloaded storage.

<details>
<summary>Solution</summary>

Consider for each of $k$ memory slots its history over the whole process this will be our flow path from source $s$ to sink $t$. For each request make two node $a_i$ (denoting situation before job started) and $b_i$ (denoting situation after job ended).
Graph: 
*	```Fresh loading```: $s$ to $a_i$ with cost $c_i$ and flow $1$
*	```Processing the job```: $a_i$ to $b_i$  with cost $-inf$ and flow $1$
*	```Replacement```: for each $j>i$:  $b_i$ to $a_j$ with flow $1$ and
	*  cost $a_j$ if $var(i)!=var(j)$  
	* otherwise cost $0$  
*	```Ending```: $b_i$ to $t$ cost $0$ and flow $1$

Min-cost flow on this graph will try to include all processing the job edges so basically a flow of 1 through them meaning they are to be present in one of the $k$ path from $s$ to $t$ so job could be done. The problem is to max-flow on this graph will try to fill all slots of memory which may not be required (and infact sometimes could increasing cost) so we can move on steps of 1 increasing the flow untill the increased cost in postive.
</details>


2) **MaxFlow on regular-DAG**: Consider a DAG with $n$ nodes (lets say topological ordered $1..n$ i.e only for $i<j$ edge from $i$ to $j$ can be present) , a source $s = n+1$ and $t = n+2$. For each node there is a edge $s$ to $i$ with capacity $I[i]$, edge $t$ to $i$ with capacity $O[i]$ and $c[i][j] = c$(uniform) denote capacity of edge between node $i$ to $j$ ($i$ < $j$). Find max-flow $s$ to $t$.
> Note: generally $c[i][j]$ is of special form with $n$ large such that normal maxflow algorithm won't work in such cases a DP solution is intended. Solution could be modified to get actual flow on each capcity.
 
 <details>
<summary>Solution</summary>

Max-flow is same as min-cut so lets calculate value of min-cut $C$ ($s \in C$) using dp. Let $A$ denote a cut $C\setminus \{s\}$ and $B = \{1,..,n\} \setminus A$. 
$$ mincut = \sum_{i\in A} O[i] + \sum_{j\in B} I[j]+\sum_{i\in A,j\in B,i<j}c[i][j]$$
Let $dp[i][j]$ be min-value of right sum if only node $1..i$ is taken and $size(A)=j$. DP follows a simple recurrence based on case of node $i$ taken or not.
$$dp[i][j] = min(dp[i-1][j-1]+O[i],dp[i-1][j]+I[i]+j*c)$$
Our final answer is $min_jdp[n][j]$. Two layer Memory optimization also possible.
</details>
