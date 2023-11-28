class quantities{
    public:
    int quantity;
    int price;
    int minmax;
    quantities(int minmax):minmax(minmax){
        quantity = 0;
        price = 0;
    }
    quantities(int price, int quantity, int minmax):price(price), quantity(quantity), minmax(minmax){}
    bool operator<(const quantities& q2) const{
        return this->price*minmax < q2.price*minmax;
    }
    bool operator>(const quantities& q2) const{
        return q2 < *this;
    }
};