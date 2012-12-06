#ifndef NNISEARCH_H
#define NNISEARCH_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
	tree* tr;
	nodeptr p;
	int nniType;
	double z[NUM_BRANCHES]; // optimize branch lengths
	double z0[NUM_BRANCHES]; // unoptimized branch lengths
	double likelihood;
	double deltaLH;
} nniMove;

/*
 *  Find the best NNI move for the current branch
 *  Return NULL if no positive NNI is found
 *  Otherwise return the best positive NNI move found
 *
 *  @param tr the current tree data structure
 *  @param p the node representing the current branch
 *  @param curLH the curren log-likelihood of the tree
 *  @return the best NNI move found for this branch or nothing
 */
nniMove getBestNNIForBran(tree* tr, nodeptr p, double curLH);

/*
 * 	do 1round of fast NNI
 *  return new tree log-likelihood if found improving NNI otherwise 0.0
 *
 *  @param tr: the tree data strucutre
 *  @param nni_count: pointer to the number of NNI that has been apply (OUT parameter)
 *  @param deltaNNI: pointer to the average improvement made by one NNI (OUT parameters)
 */
double doNNISearch(tree* tr, int* nni_count, double* deltaNNI);

double doOneNNI(tree * tr, nodeptr p, int swap, int optBran);

/*
 *  Go through all 2(n-3) internal branches of the tree and
 *  evaluate all possible NNI moves
 */
void evalAllNNI(tree* tr);

/*
 *  cnt: number of internal branches that have been visited
 *  cnt_nni: number of positive NNI found
 */
void evalNNIForSubtree(tree* tr, nodeptr p, nniMove* nniList, int* cnt_bran, int* cnt_nni, double curLH);
/*
 *  Save the likelihood vector of p and q to the 2 pointer p_lhsave and
 *  q_lhsave.
 *  Should I use memcpy or just copy the pointer ?
 */
//void saveLHVector(nodeptr p, nodeptr q, double* p_lhsave, double* q_lhsave);


#ifdef __cplusplus
}
#endif

#endif

