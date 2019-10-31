//k-d tree算法 k-d树（k-dimensional树的简称）.
//是一种分割k维数据空间的数据结构。 主要应用于多维空间关键数据的搜索（如：范围搜索和最近邻搜索）
/*****
 * 索引结构中相似性查询有两种基本的方式：一种是范围查询（range searches），另一种是K近邻查询（K-neighbor searches）。范围查询就是给定查询点和查询距离的阈值，从数据集中找出所有与查询点距离小于阈值的数据；K近邻查询是给定查询点及正整数K，从数据集中找到距离查询点最近的K个数据，当K=1时，就是最近邻查询（nearest neighbor searches）。
 * 
 * 需要定义两点间的距离
 */
/*
#include <algorithm>
using namespace std;
*/
struct Point {
	int d[XD];
};

long long Dist(Point const &a,Point const &b) {
	
}

struct KDTree {
	struct Node {
		Node *son[2];
		Point p,min,max;
	
		Node(Point p):p(p),min(p),max(p) {
			son[0]=son[1]=null;
		}

		Node(void*):min(),max() {
			son[0]=son[1]=0;
		}

		void Up() {
			for(int i=0;i<k;++i) {
				min.d[i]=std::min(p.d[i],std::min(son[0]->min.d[i],son[1]->min.d[i]));
				max.d[i]=std::max(p.d[i],std::max(son[0]->max.d[i],son[1]->max.d[i]));
			}
		}

		long long Dist(Point const &q) {
			
		}
	}*root;

	static Node *null;

	KDTree(Point p[],int n):root(Build(p,1,n,0)) {}
	
	Node *Build(Point p[],int L,int R,int d) {
		if(L>R)
			return null;
		else {
			struct Compare {
				int d;
				Compare(int d):d(d) {}

				bool operator ()(Point const &a,Point const &b) {
					return a.d[d]<b.d[d];
				}
			};
			int M=(L+R)/2;
			std::nth_element(p+L,p+M,p+R+1,Compare(d));
			Node *pos=new Node(p[M]);
			pos->son[0]=Build(p,L,M-1,(d+1)%k);
			pos->son[1]=Build(p,M+1,R,(d+1)%k);
			pos->Up();
			return pos;
		}
	}

	long long Query(Point p) {
		long long res;
		Query(root,p,res);
		return res;
	}

	void Query(Node *pos,Point p,long long &res) {
		if(pos==null)
			return;
		else {
			Reduce(res,Dist(pos->p,p));
			if(pos->son[0]->Dist(p)<res)
				Query(pos->son[0],p,res);
			if(pos->son[1]->Dist(p)<res)
				Query(pos->son[1],p,res);
		}
	}
};
KDTree::Node *KDTree::null=new KDTree::Node((void*)0);
