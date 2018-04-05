#include "timsort.h"
#include <algorithm>

void TimSort::sort(vector<CatInfo *> &mas)
{
    int n = mas.size();

    vector<CatInfo *> tmp(n);
    vector<segment> seg;

    int minSize = getMainSize(n);
    int size = minSize;

    seg.reserve((n-1)/minSize + 1);

    for(auto ii = 0; ii < n; ii += minSize)
    {
        size = min(minSize, n-ii);
        selectionSort(mas, ii, ii+size);
        seg.push_back(segment(ii, size));
        try_merge(mas, seg, tmp);
    }

    while(seg.size() != 1)
        try_merge(mas, seg, tmp, true);
}

void TimSort::selectionSort(vector<CatInfo *> &mas, int beg, int last)
{
    for(auto ii = beg; ii < last; ii++)
    {
        auto minPos = ii;
        for(auto jj = ii + 1; jj < last; jj++)
        {
            CatInfo *p1 = mas.at(jj);
            CatInfo *p2 = mas.at(minPos);

            switch(_sortType)
            {
                case cat::CatSortNumber:
                case cat::CatSortAge:
                    if(p1->getIntProperty(_sortType) < p2->getIntProperty(_sortType))
                        minPos = jj;
                    break;
                case cat::CatSortName:
                case cat::CatSortBreed:
                case cat::CatSortFood:
                    if(p1->getStrProperty(_sortType) < p2->getStrProperty(_sortType))
                        minPos = jj;
                    break;
            }
        }

        swap(mas[ii], mas[minPos]);
    }
}

void TimSort::merge(vector<CatInfo *> &mas, vector<segment> &seg, bool isXY, vector<CatInfo *> &tmp)
{
    segment f = seg[seg.size() - dY];
    segment s = isXY ? seg[seg.size() - dX] : seg[seg.size() - dZ];

    if(f.beg > s.beg)
        swap(f, s);

    int posF = 0, posS = s.beg, pos = f.beg - 1;
    int lstF = f.len, lstS = s.beg + s.len;

    copy(mas.begin() + f.beg + posF, mas.begin() + f.beg + lstF, tmp.begin());

    int fAmount = 0, sAmount = 0;
    while(posF < lstF && posS < lstS)
    {
        CatInfo *p1 = tmp.at(posF);
        CatInfo *p2 = mas.at(posS);
        bool flag = false;

        switch(_sortType)
        {
            case cat::CatSortNumber:
            case cat::CatSortAge:
                if(p1->getIntProperty(_sortType) < p2->getIntProperty(_sortType))
                    flag = true;
                break;
            case cat::CatSortName:
            case cat::CatSortBreed:
            case cat::CatSortFood:
                if(p1->getStrProperty(_sortType) < p2->getStrProperty(_sortType))
                    flag = true;
                break;
        }

        if(flag)
        {
            mas[++pos] = tmp[posF];
            ++fAmount;
            sAmount = 0;
            if(fAmount == 7)
            {
                //vector<CatInfo *>::iterator it = (vector<CatInfo *>::iterator)upper_bound(tmp.begin() + posF, tmp.begin() + lstF, mas[pos]);
                vector<CatInfo *>::iterator it = great(tmp.begin() + posF, tmp.begin() + lstF, mas[pos]);
                copy(tmp.begin() + posF, it, mas.begin() + pos + 1);
                pos += (it - (tmp.begin() + posF));
                posF += (it - (tmp.begin() + posF));
            }
        }
        else
        {
            mas[++pos] = mas[posS++];
            fAmount = 0;
            ++sAmount;
            if(sAmount == 7)
            {
                //vector<CatInfo *>::iterator it = (vector<CatInfo *>::iterator)upper_bound(mas.begin() + posS, mas.begin() + lstS, tmp[posF]);
                vector<CatInfo *>::iterator it = great(mas.begin() + posS, mas.begin() + lstS, tmp[posF]);
                copy(mas.begin() + posS, it, mas.begin() + pos + 1);
                pos += (it - (mas.begin() + posS));
                posS += (it - (mas.begin() + posS));
            }
        }
    }

    copy(tmp.begin() + posF, tmp.begin() + lstF, mas.begin() + pos + 1);
}

void TimSort::try_merge(vector<CatInfo *> &mas, vector<segment> &seg, vector<CatInfo *> &tmp, bool is_merge)
{
    while(seg.size() > 1)
    {
        auto x = seg[seg.size() - dX].len;
        auto y = seg.size() < 2 ? 0 : seg[seg.size() - dY].len;
        auto z = seg.size() < 3 ? 0 : seg[seg.size() - dZ].len;

        if(seg.size() >= 3 && z <= x + y)
        {
            if(z < x)
            {
                merge(mas, seg, false, tmp);
                seg[seg.size() - dZ].len += seg[seg.size() - dY].len;
                seg[seg.size() - dY] = seg[seg.size() - dX];
                goto POP_BACK;
            }
            else
            {
                merge(mas, seg, true, tmp);
                seg[seg.size() - dY].len += seg[seg.size() - dX].len;
                goto POP_BACK;
            }
        }
        else if(is_merge || y <= x)
        {
            merge(mas, seg, true, tmp);
            seg[seg.size() - dY].len += seg[seg.size() - dX].len;
            goto POP_BACK;
        }
        else
            break;

    POP_BACK:
        seg.pop_back();
    }
}

vector<CatInfo *>::iterator TimSort::great(vector<CatInfo *>::iterator first, vector<CatInfo *>::iterator last, CatInfo *value)
{
    vector<CatInfo *>::iterator it;
    auto count = std::distance(first, last);
    auto step = count;
    while(count > 0)
    {
        it = first;
        step = count / 2;
        advance(it, step);
        bool flag = false;

        switch(_sortType)
        {
            case cat::CatSortNumber:
            case cat::CatSortAge:
                if(value->getIntProperty(_sortType) < (*it)->getIntProperty(_sortType))
                    flag = true;
                break;
            case cat::CatSortName:
            case cat::CatSortBreed:
            case cat::CatSortFood:
                if(value->getStrProperty(_sortType) < (*it)->getStrProperty(_sortType))
                    flag = true;
                break;
        }

        if(!flag)
        {
            first = ++it;
            count -= (step + 1);
        }
        else
            count = step;
    }

    return first;
}
