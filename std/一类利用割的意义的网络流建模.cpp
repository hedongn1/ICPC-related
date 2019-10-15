这几天在BZOJ漫无目的的闲逛。
今天逛到了第12页，那一群没写Source的题基本都是2011的命题答辩。
我顿时心花怒放，终于又见到有题解的题了。

膜拜了十几题下来，加上前不久见到的，就有看起来类似的网络流三发了...
稍微写一写吧。

先来看这么一个题。
给出一个无向图G=(V,E)，并有定义在V上的权a和b，以及定义在E上的权w。
（这里提及的所有权都默认为非负整数。）
选出一个点集S，最大化∑(x属于S)a[x]+∑(x不属于S)b[x]+∑(x和y同时属于或不同时属于S)w(x,y)。
这是一个可以直接用最小割解决的问题。
添加源S和汇T，对于每个x，连边(S,x,a[x])和(x,T,b[x])，而w(x,y)直接变为对应边的容量。
考察这个图的割的意义不难得出最终的答案=∑a[x]+∑b[x]+∑w(x,y)-最小割。

好..我们来改一改。
现在我们需要最大的化的式子变成了这样。
∑(x属于S)a[x]+∑(x不属于S)b[x]+∑(x属于S且y不属于S)w(x,y)。
....很可惜似乎直接做是不可行的，如果有靠谱的做法请不吝赐教。
我们需要一个重要的条件：图G是二分图。
对于X中的每个点x，连边(S,x,a[x])和(x,T,b[x])；
对于Y中的每个点y，连边(S,y,b[y])和(y,T,a[y])。
而边权w(x,y)仍然直接变为对应边的容量。

下面来看另外一种改法。
新增一个定义在E上的权r。
最大化∑(x属于S)a[x]+∑(x不属于S)b[x]+∑(x和y都属于S)w(x,y)+∑(x和y都不属于S)r(x,y)。
（请留意，二分图的条件已经吃粑粑去了。）
回顾前面的解题过程，在考虑使用割的意义建图的时候，我们的割边实际上是“损失”。
在这一题中点权似乎仍然是老样子，但是边权有些麻烦了。
1. 当x和y同时属于S的时候，我们损失了r(x,y)。
2. 当x和y同时不属于S的时候，我们损失了w(x,y)。
3. 当x属于S和y属于S的真假性不同的时候，我们损失了w(x,y)以及r(x,y)。
正确的表达这些损失要用到的技巧是权值的重新分配。

首先，添加源S和汇T，对于每个x，连边(S,x,a[x])和(x,T,b[x])

考虑第1条，可以视为，当x属于S的时候，损失r(x,y)/2，y同理；
此时即要将x，y向T连各连一条r(x,y)/2的边，因为割的边代表损失的利益，而S连向x，y的边保留代表取此种方案。

第2条类似。 

而在第3条描述的情形下，根据前面已经做出的调整（根据前两条，已经割了S向x的边，y向T的边（或是S到y，x到T）），我们就会计算出(r(x,y)+w(x,y))/2的损失；
然而真正的损失是w(x,y)+r(x,y)，因此我们对x到y，y到x分别连上一条容量(r(x,y)+w(x,y))/2的边来补上这个损失。
这样一来所有的损失都被正确的计算了。

再来看一道有点像的题。
给定无重边无自环的无向图G=(V,E)，定义在V上的权a，E上的权w，求一个点集S，最大化：
2*∑(x,y属于S)w(x,y)-∑(x属于S且y不属于S)w(x,y)-∑(x属于S)a[x]。
（为什么要乘2呢...∑枚举的x,y是无序的，但是根据题意w(x,y)和w(y,x)都要算进去）
令b[x]=∑(y)w(x,y)，则∑(x属于S且y不属于S)w(x,y)=∑(x属于S)b[x]-2*∑(x,y属于S)w(x,y)，
进而要最大化的式子变为 ∑(x,y属于S)4*w(x,y) - ∑(x属于S)(a[x]+b[x])。
很经典的最大权闭合图，这里略去。
但是这样搞总觉得有点脱离主题，于是我们再来看一个做法。
据∑w(x,y)=∑(x,y属于S)w(x,y)+∑(x,y不属于S)w(x,y)+∑(x属于S且y不属于S)w(x,y)，将目标式化为
2*∑w(x,y) - 3*∑(x属于S且y不属于S)w(x,y)  - ∑(x属于S)a[x]。
从而只需要最小化 3*∑(x属于S且y不属于S)w(x,y) + 2*∑(x,y不属于S)w(x,y) + ∑(x属于S)a[x]。
而这个东西等于 ∑(y不属于S)w(x,y) + 2*∑(x属于S且y不属于S)w(x,y) + ∑(x属于S)a[x]。
（恩，2*∑(x,y不属于S)w(x,y)+∑(x属于S且y不属于S)w(x,y)=∑(y不属于S)w(x,y)看起来挺纠结的。）
不管怎么说弄成这样了以后就可以利用割的意义来构造了：
∑w(x,y)就是把y割出S的损失，a[x]就是把x割进S的损失，将x,y分开的损失则是2*w(x,y)。
于是直接最小割就完了。
