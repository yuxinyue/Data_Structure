/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim] == second[curDim]) return first < second;
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double sumCur = 0;
    double sumPot = 0;
    for(int i = 0; i < Dim; i++){
        sumCur += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
        sumPot += (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    if(sumCur == sumPot) return potential < currentBest;
    return sumPot < sumCur;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    if(newPoints.size() == 0) return;
    points = newPoints;
    KDTree_helper(0, (int)points.size() - 1, 0);

}

template <int Dim>
void KDTree<Dim>::KDTree_helper(int left, int right, int dim){
    if(left >= right) return;
    //cout<< "before select"<<endl;
    select(left, right, (left + right)/2, dim);
    //cout<<"help"<<left<<right<<(left + right)/2<<dim<<endl;
    KDTree_helper(left, (left + right)/2 - 1, (dim + 1) % Dim);
    KDTree_helper((left + right)/2 + 1, right, (dim + 1) % Dim);
}

template<int Dim>
int KDTree<Dim>::partition(int left, int right, int pivotIndex, int dim){
    Point<Dim> temp = points[pivotIndex];
    points[pivotIndex] = points[right];
    points[right] = temp;
    int storeIndex = left;
    for(int i = left; i < right; i++){
        if( smallerDimVal(points[i], points[right], dim)){
            temp = points[i];
            points[i] = points[storeIndex];
            points[storeIndex] = temp;
            storeIndex++;
        }
    }
    temp = points[right];
    points[right] = points[storeIndex];
    points[storeIndex] = temp;

    return storeIndex;
}


template<int Dim>
void KDTree<Dim>::select(int left, int right, int n, int dim){
    //cout<<"select"<<n<<endl;
    if (left >= right) 
        return; 
    int pivotIndex = (left + right)/2;
    //cout<< "select 1"<<endl;
    pivotIndex = partition(left, right, pivotIndex, dim);
    //cout<<"select 2"<<endl;
    if(n == pivotIndex)
        return; 
    else if(n < pivotIndex)
        return select(left, pivotIndex - 1, n, dim);
    else
        return select(pivotIndex + 1, right, n, dim);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    int nearestNeighbor = -1;
    findNearestNeighbor_helper(0, points.size() - 1, 0, nearestNeighbor,query);
    return points[nearestNeighbor];
}

template <int Dim>
void KDTree<Dim>::findNearestNeighbor_helper(int left, int right, int dim, int & currentBestIdx, const Point<Dim>& query) const{
    if (left>right) return;
    if(left == right) {
        if(currentBestIdx == -1)
            currentBestIdx = left;
        else if(shouldReplace(query, points[currentBestIdx], points[left])){
            currentBestIdx = left;
        }
    return;
    }
    int node = (left + right)/2;
    if(smallerDimVal(query, points[node], dim)){
        if (node==left) findNearestNeighbor_helper(left, node , (dim + 1) % Dim, currentBestIdx, query);//added by someone special
        else findNearestNeighbor_helper(left, node - 1, (dim + 1) % Dim, currentBestIdx, query);
        if(shouldReplace(query, points[currentBestIdx], points[node])){
            currentBestIdx = node;
        }
        if ((points[node][dim] - query[dim]) * (points[node][dim] - query[dim]) <=radius2(currentBestIdx, query)){
            findNearestNeighbor_helper(node + 1, right, (dim + 1) % Dim, currentBestIdx, query);
        }
    }  
    else{
        findNearestNeighbor_helper(node + 1, right, (dim + 1) % Dim, currentBestIdx, query);
        if(shouldReplace(query, points[currentBestIdx], points[node])){
            currentBestIdx = node;
        }
        if ((points[node][dim] - query[dim]) * (points[node][dim] - query[dim]) <= radius2(currentBestIdx, query)){
            findNearestNeighbor_helper(left, node - 1, (dim + 1) % Dim, currentBestIdx, query);
        }
    }
}

template <int Dim>
double KDTree<Dim>::radius2(int first, const Point<Dim>& query) const{
    double radiusSquare = 0;
    for(int i = 0; i < Dim; i++){
        radiusSquare += (points[first][i] - query[i]) * (points[first][i] - query[i]);
    }
    return radiusSquare;
}   
