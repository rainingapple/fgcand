#include "LKH.h"
#include "Genetic.h"
#include "BIT.h"

/*
 * This file contains the main function of the program.
 */

int main(int argc, char* argv[])
{
    GainType Cost, OldOptimum;
    double Time, LastTime;
    Node *N;
    int i;
    static char candstr[1000000];
    memset(candstr, '\0', sizeof(candstr));

    /* Read the specification of the problem */
    ParameterFileName = argv[1];
    ReadParameters();
    StartTime = LastTime = GetTime();
    MaxMatrixDimension = 20000;
    MergeWithTour = Recombination == IPT ? MergeWithTourIPT :
        MergeWithTourGPX2;
    ReadProblem();
    if (SubproblemSize > 0) {
        if (DelaunayPartitioning)
            SolveDelaunaySubproblems();
        else if (KarpPartitioning)
            SolveKarpSubproblems();
        else if (KCenterPartitioning)
            SolveKCenterSubproblems();
        else if (KMeansPartitioning)
            SolveKMeansSubproblems();
        else if (RohePartitioning)
            SolveRoheSubproblems();
        else if (MoorePartitioning || SierpinskiPartitioning)
            SolveSFCSubproblems();
        else
            SolveTourSegmentSubproblems();
        return EXIT_SUCCESS;
    }
    AllocateStructures();
    if (ProblemType == TSPTW)
        TSPTW_Reduce();
    if (ProblemType == VRPB || ProblemType == VRPBTW)
        VRPB_Reduce();
    if (ProblemType == PDPTW)
        PDPTW_Reduce();
    CreateCandidateSet();
    InitializeStatistics();
    Candidate* NN;
    N = FirstNode;
    /*do {
        sprintf(candstr, "%s%d ", candstr, N->Id);
        if (N->CandidateSet)
            for (NN = N->CandidateSet; NN->To; NN++) {
                sprintf(candstr, "%s%d %lf ", candstr, NN->To->Id, (double)NN->Alpha / exmaxalpha);
            }
        sprintf(candstr, "%s\n", candstr);
    } while ((N = N->Suc) != FirstNode);*/
    do {
        printf("%d ", N->Id);
        if (N->CandidateSet)
            for (NN = N->CandidateSet; NN->To; NN++) {
                printf("%d %lf ",NN->To->Id, (double)NN->Alpha / exmaxalpha);
            }
        printf("\n");
    } while ((N = N->Suc) != FirstNode);
    return 0;
}

