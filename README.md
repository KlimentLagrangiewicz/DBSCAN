# DBSCAN
Implementation of DBSCAN clustering algorithm in C (standard C89/C90).  
## About DBSCAN  
DBSCAN (Density-based spatial clustering of applications with noise) is a density-based clustering non-parametric algorithm proposed by Martin Ester, Hans-Peter Kriegel, Jörg Sander and Xiaowei Xu in 1996.  
The main idea of the algorithm is to assign neighboring closely located points to the same cluster.  
#### Input data:
  +  $X=\mathrm{x}_{i=1,j=1}^{n,m}$ — description of objects, where n — number of objects, m — number of attributes;  
  +  $minPts \in ℕ$ — minimum number of points required to form a dense region;
  +  $\epsilon > 0$ — concentration radius.  
#### Output data:   
  +  $Y=\left\\{y_i|y_i\in ℕ,i\in\overline{\left(1,n\right)}\right\\}$ — cluster labels.  
#### Advantages of DBSCAN:
  +  Easy to implement;  
  +  Low algorithmic complexity;  
  +  The ability to allocate clusters of complex shape;  
  +  DBSCAN can find noise;
  +  The presence of many modifications.  
#### Disadvantages of DBSCAN:   
  +  DBSCAN works badly with clusters with different density;  
  +  DBSCAN does not work well on clusters that have a small intersection with each other. For example, the points of two touching circles DBSCAN will refer to the same cluster;  
  +  DBSCAN can't processing big data;  
  +  Accuracy of clustering with DBSCAN strongly depends on value $\epsilon$.  
#### Definitions
Def.1. A point p is a core point if at least minPts points are within distance $\epsilon$ of it (including p).  
Def.2. A point q is directly reachable from p if point q is within distance ε from point p: $\rho\left(q,p\right)\leqslant\epsilon$.  
Def.3. A point q is reachable from p if there is a path $p_1,\ldots,p_n$ with $p_1 = p$ and $p_n = q$, where each $p_{i+1}$ is directly reachable from $p_i$.  
### Steps of DBSCAN
Step 1. Data preparing (autoscaling): $x_{i,j}=\frac{x_{i,j}-\mathrm{E_{X^{j}}}}{\sigma_{X^{j}}}$;  
Step 2. Mark all points as unselected;  
Step 3. Select point from unselected core points;  
Step 4. Mark that point and points, which reachable from her;  
Step 5. Repeat steps 3, 4 until all core points have been marker;  
Step 6. Mark the unmarked points as noise.  
## Example of usage
```
git clone https://github.com/KlimentLagrangiewicz/DBSCAN
cd DBSCAN/  
cmake .  
cmake --build .  
./DBSCAN ./examplesDataSets/iris/test150 150 4 5 1.5 ./examplesDataSets/iris/result
 ```
