#ifndef GOLD_H
#define GOLD_H

template <typename T>
class Gold {
    private:
    T gold;

   public:
    Gold(T gold);
    void displayGold() const;
    void setGold(T gold);
    T getGold() const;


};

#endif 
