#include <iostream>
#include <algorithm>
#include <set>

#include <time.h>

#include "graph.h"

using namespace std;

int main() {
    Graph h("graph6.txt", Graph::TYPE_ADJACENCY_LIST);
    h.print(true);       

    cout << endl << "A minimum feedback vertex set : ";
    vector<int> mfvs = h.minimumFeedbackVertexSet(true);
    for (vector<int>::iterator it = mfvs.begin(); it != mfvs.end(); ++it)
        cout << *it << " ";
    cout << endl;
    cout << "Is it really a feedback vertex set ? ";
    if (h.isFeedbackVertexSet(mfvs)) cout << "yes";
    else cout << "no";
		cout << endl;
}
