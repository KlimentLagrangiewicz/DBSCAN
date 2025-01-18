# DBSCAN
Implementation of DBSCAN clustering algorithm in C programming language (standard C89/C90)
## About DBSCAN  
DBSCAN (Density-based spatial clustering of applications with noise) is a density-based clustering non-parametric algorithm proposed by Martin Ester, Hans-Peter Kriegel, Jörg Sander and Xiaowei Xu in 1996.  
The main idea of the algorithm is to assign neighboring closely located points to the same cluster.  
#### Input data:
  +  $X=\mathrm{x}_{i=1,j=1}^{n,m}$ — description of objects, where $n$ is number of objects, $m$ is number of attributes;  
  +  $minPts \in ℕ$ — minimum number of points required to form a dense region;  
  +  $\epsilon > 0$ — concentration radius.
#### Output data:   
  +  $Y=\left\\{y_i|y_i\in ℤ,i=\overline{\left(1,n\right)}\right\\}$ — cluster labels and noise markers.
#### Advantages of DBSCAN:
  +  Easy to implement;  
  +  Low algorithmic complexity;  
  +  The possibility of identifying clusters of complex shapes;  
  +  DBSCAN can find noise;
  +  Presence of many modifications.  
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
Step 4. Mark that point and points, which reachable from it;  
Step 5. Repeat steps 3, 4 until all core points have been marking;  
Step 6. Mark the unmarked points as noise.
## Example of usage
Cloning project and changing current directory:
```
git clone https://github.com/KlimentLagrangiewicz/DBSCAN
cd DBSCAN
```
Building from source (Linux):
```
make
```
Building from source (Windows):
```
make windows
```
If building was successfully, you can find executable file in `bin` subdirectory
```
./bin/dbscan ./datasets/iris/data.txt 150 4 3 1.1 ./datasets/iris/new_result.txt
```
