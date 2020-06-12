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

