    #include "tools/KDTree.h"
    int Point::idx = 0;
    KDTree::KDTree() {
        _data.reserve(N * 4);
        _flag.reserve(N * 4);//TODO init
    }

    KDTree::~KDTree() {}

    int KDTree::read_in(vector<Point> inputPoints) {
        int len=inputPoints.size();
        //cout<<len<<endl;
        //_find_nth.reserve(N * 4);
        //_find_nth.assign
        //cout<<2<<endl;
        for (int i = 0; i < inputPoints.size(); ++i) {
            //cout<<i<<endl;
            //Point tmp(ary_x[i], ary_y[i]);
            _find_nth.push_back(inputPoints[i]);
        }
        for (int i = 0; i < N * 4; ++i) {
            Point tmp;
            _data.push_back(tmp);
            _flag.push_back(0);
        }
        build(0, len - 1, 1, 0);
        return 0;
    }

    void KDTree::clean() {
        _find_nth.clear();
        _data.clear();
        _flag.clear();
    }

    //建立kd-tree
    void KDTree::build(int l, int r, int rt, int dept) {
        if (l > r) return;
        _flag[rt] = 1;                  //表示标号为rt的节点存在
        _flag[lson] = _flag[rson] = -1; //当前节点的孩子暂时标记不存在 
        int mid = (l + r + 1) >> 1;
        Point::idx = dept % k;           //按照编号为idx的属性进行划分
        std::nth_element(_find_nth.begin() + l, _find_nth.begin() + mid, _find_nth.begin() + r + 1);
        _data[rt] = _find_nth[mid];
        build(l, mid - 1, lson, dept + 1); //递归左子树
        build(mid + 1, r, rson, dept + 1);
    }

    int KDTree::find_nearest_point(double x, double y, Point &res, double& dist) {
        Point p(x, y);
        query(p, res, dist, 1, 0);
        return 0;
    }

    //查找kd-tree距离p最近的点
    void KDTree::query(const Point& p, Point& res, double& dist, int rt, int dept) {
        //cout<<1<<endl;
        if (_flag[rt] == -1) {
          // cout<<"不存在"<<endl;
            return;
        }//不存在的节点不遍历
        //cout<<1<<endl;
        double tmp_dist = distance(_data[rt], p);
        bool fg = false; //用于标记是否需要遍历右子树
        int dim = dept % k; //和建树一样, 保证相同节点的dim值不变
        int x = lson;
        int y = rson;
        if(dim==0){
           if (p.x >= _data[rt].x) {
            std::swap(x, y);  //数据p的第dim个特征值大于等于当前的数据，则需要进入右子树
          }
        }
        if(dim==1){
           if (p.y >= _data[rt].y) {
            std::swap(x, y);  //数据p的第dim个特征值大于等于当前的数据，则需要进入右子树
           }
        }
        
        if (~_flag[x]) {
           // cout<<2<<endl;
            query(p, res, dist, x, dept + 1); //节点x存在, 则进入子树继续遍历
        }
        //cout<<3<<endl;
        if (tmp_dist < dist) { //如果找到更小的距离, 则替换目前的结果dist
            res = _data[rt];
            dist = tmp_dist;
           // cout<<"dis min "<<dist<<endl;
        }
        if(dim==0)
        tmp_dist = (p.x - _data[rt].x) * (p.x - _data[rt].x);
        if(dim==1)
        tmp_dist = (p.y - _data[rt].y) * (p.y - _data[rt].y);
        if (tmp_dist < dist) { //还需要继续回溯
            fg = true;
        }
        if (~_flag[y] && fg) {
            query(p, res, dist, y, dept + 1);
        }
    }

    //计算两点间的距离的平方
    double KDTree::distance(const Point& x, const Point& y) {
        double re = 0;
        re=(x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y);
        return re;
    }
