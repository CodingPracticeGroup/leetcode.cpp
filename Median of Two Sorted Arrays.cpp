class Solution {
public:
    double findMedianSortedArrays(int A[], int m_, int B[], int n_) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (0 == m_)
            return m(B, 0, n_);
        if (0 == n_)
            return m(A, 0, m_);
        if (m_ <= n_) {
            return prune(A, B, 0, m_, 0, n_);
        } else {
            return prune(B, A, 0, n_, 0, m_);
        }
    }

    double m(int A[], int Abegin, int Aend) {
        int len = Aend-Abegin;
        if (len%2 == 0) {
            int half = len/2;
            return (A[Abegin+half-1]+A[Abegin+half])/2.0;
        } else {
            return A[Abegin+len/2];
        }
    }

    int min(int a, int b) {
        return a<b ? a : b;
    }
    int max(int a, int b) {
        return a>b ? a : b;
    }

    double prune1(int a, int B[], int Bbegin, int Bend) {
        double mB = m(B, Bbegin, Bend);
        if (Bend-Bbegin == 1)
            return (a+B[Bbegin])/2.0;
        if ((1+(Bend-Bbegin))%2 == 0) {
            if (mB < a)
                return (mB+min(a, B[Bbegin+(Bend-Bbegin)/2+1]))/2;
            else if (mB > a)
                return (mB+max(a, B[Bbegin+(Bend-Bbegin)/2-1]))/2;
        } else {
            if (B[Bbegin+(Bend-Bbegin)/2-1]<=a && a<=B[Bbegin+(Bend-Bbegin)/2])
                return a;
            else if (B[Bbegin+(Bend-Bbegin)/2-1] > a)
                return B[Bbegin+(Bend-Bbegin)/2-1];
            else if (a > B[Bbegin+(Bend-Bbegin)/2])
                return B[Bbegin+(Bend-Bbegin)/2];
        }
    }

    double makeAndSortLeft(int a0, int a1, int B_[], int B_begin, int B_end) {
        vector<int> ret;
        ret.push_back(a0);
        ret.push_back(a1);
        for (int i=B_begin; i<B_end; i++)
            ret.push_back(B_[i]);
        sort (ret.begin(), ret.end());
        return (ret[ret.size()-2]+ret[ret.size()-1])/2.0;
    }
    double makeAndSortRight(int a0, int a1, int B_[], int B_begin, int B_end) {
        vector<int> ret;
        ret.push_back(a0);
        ret.push_back(a1);
        for (int i=B_begin; i<B_end; i++)
            ret.push_back(B_[i]);
        sort (ret.begin(), ret.end());
        return (ret[0]+ret[1])/2.0;
    }

    double prune2(int a0, int a1, int B[], int Bbegin, int Bend) {
        double mB = m(B, Bbegin, Bend);
        if ((2+(Bend-Bbegin))%2 == 0) {
            if (a0<=mB && mB<=a1)
                return (min(B[Bbegin+(Bend-Bbegin)/2], a1)+max(B[Bbegin+(Bend-Bbegin)/2-1], a0))/2.0;
            else if (mB < a0) {
                return makeAndSortRight(a0, a1, B, Bbegin+(Bend-Bbegin)/2, min(Bbegin+(Bend-Bbegin)/2+2, Bend));
            } else if (a1 < mB) {
                return makeAndSortLeft(a0, a1, B, max(Bbegin, Bbegin+(Bend-Bbegin)/2-2), Bbegin+(Bend-Bbegin)/2);
            }
        } else {
            if (a0<=mB && mB<=a1)
                return mB;
            else if (mB<a0)
                return min(B[Bbegin+(Bend-Bbegin)/2+1], a0);
            else if (a1<mB)
                return max(B[Bbegin+(Bend-Bbegin)/2-1], a1);
        }
    }

    // A is shorter than B
    double prune(int A[], int B[], int Abegin, int Aend, int Bbegin, int Bend) {
        double mA = m(A, Abegin, Aend);
        double mB = m(B, Bbegin, Bend);
        if (mA == mB) {
            return mA;
        }
        int lenA = Aend-Abegin;
        if (lenA == 1) {
            return prune1(A[Abegin], B, Bbegin, Bend);
        } else if (lenA == 2) {
            return prune2(A[Abegin], A[Abegin+1], B, Bbegin, Bend);
        } else {
            int pruneLen = lenA-1;
            if (mA > mB) {
                return prune(A, B, Abegin, Aend-pruneLen/2, Bbegin+pruneLen/2, Bend);
            } else {
                return prune(A, B, Abegin+pruneLen/2, Aend, Bbegin, Bend-pruneLen/2);
            }
        }
    }
};