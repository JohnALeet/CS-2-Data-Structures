template <class T1> //Arrays let you access the content 
class Template
{
private:
    unsigned int _size;
    const static int _arrSize = 10;
    T1 _arr[_arrSize];
    int _beg, _end;
    public:
    Queue() {_size =0;}

    void enqueue(T1 Data)
    {
        if (full())
        {
            std::cerr << "Queue full!" << std::endl;
            return;
        }
        _end++;
        _end = _end % _arrSize;
        _arr[_end] = data;
        // _arr[++_end] = data;
        _size++;
        if(_beg == -1) _beg = _end;
    }
    bool full() //We need to make sure the distance between beginning and end is 10.
    {
        return ((_end > _beg && _beg == 0 && _end == _arrSize -1)|| (_end - _beg == -1));
    }
    bool empty()
    {
        return (_beg == -1)
    }
    T1 dequeue()
    {
        if(empty())
    {
        std::cerr << "Queue empty" << std::endl;
    }
    T1 toBeReturned = _arr[_beg];
    if (_beg == _end)
    {
        _beg = -1;
        _end = -1;
    }
    else
    {
    _beg++;
    _beg = _beg % _arrSize;
    }
    _size--;
    return toBeReturned;
    }

};

arrQue::arrQue(/* args */)
{
}

arrQue::~arrQue()
{
}
