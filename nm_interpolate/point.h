#ifndef POINT
#define POINT

typedef double Real;

class Point {
    private: 
        Real x, y;
    public:
        Point(Real x, Real y);
        static int compare(const void *arg1, const void *arg2);
        Real get_X();
        Real get_Y();
};

#endif //POINT
