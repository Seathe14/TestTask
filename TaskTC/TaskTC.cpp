#include <iostream>
#include <vector>
#include <map>
#include <iomanip>
#include <thread>
#include <chrono>
class TestTask
{
public:
    TestTask() = default;
    TestTask(int size)
    {
        fillContainers(size);
    }
    void fillContainers(int size)
    {
        vec.clear();
        mmap.clear();
        std::cout << "Filling containers\n";
        for (int i = 0; i < size; i++)
        {
            vec.push_back(rand() % 10);      
            mmap.insert({i, rand() % 10});
        }
    }
    void removeRand()
    {
        if (vec.size() == 0 && mmap.size() == 0)
            return;
        std::cout << "After removing random amount of elements \n";
        int toRemove = rand() % 15 + 1;                               // randomizing amount of elements to remove
        if (vec.size() > 1 && mmap.size() > 1)                        // if there's more than 1 element in the containers, then we can remove at least 1 item.
        {
            while (toRemove >= vec.size() && toRemove >= mmap.size()) // randomizing amount of elements to remove according to our containers size
            {                                                         // toRemove has to be less than size
                toRemove = rand() % 15 + 1;
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
        std::cout << "Amount of items to remove: " << toRemove << "\n";
        for (int i = 0; i < toRemove; i++)
        {
            vec.pop_back();
            mmap.erase(mmap.erase(i));
        }
    }
    void printContainers()
    {
        if (vec.size() == 0 && mmap.size() == 0)  // if containers are empty
        {
            std::cout << "There's no items in the containers" << std::endl;
            return;
        }
        else
        {
            std::cout << "map:" << std::setw(5);
            for (auto i : mmap)
            {
                std::cout << i.second << " ";
            }
            std::cout << "\nvector: ";
            for (int i = 0; i < vec.size(); i++)
            {
                std::cout << vec[i] << " ";
            }
            std::cout << "\n\n";
        }

    }
    void eraseDistinct()
    {
        if (vec.size() == 0 && mmap.size() == 0)
            return;
        std::cout << "After erasing distinct: \n";
        for (auto mIt = mmap.begin(); mIt != mmap.end();)  // looping through the map, erasing items from the map that are not found in the vector
        {
            auto it = find(vec.begin(), vec.end(), mIt->second);
            if (it == vec.end())
                mmap.erase(mIt++);
            else
                mIt++;
        }
        auto it = vec.begin();
        while (it != vec.end())         // looping through the vector
        {
            auto mIt = mmap.begin();
            while (mIt != mmap.end())
            {
                if (mIt->second == *it) // if the value is found then break, so that our iterator doesn't become end
                    break;
                mIt++;
            }
            if (mIt == mmap.end())      // if the value is not found in the map, then erase it from the vector
                it = vec.erase(it);
            else                        // if not found then increment iterator
                it++;
        }
    }

private:
    std::vector<int> vec;
    std::map<int, int> mmap;
};

int main()
{
    srand(time(0));
    TestTask t(15);
    t.printContainers();
    t.removeRand();
    t.printContainers();
    t.eraseDistinct();
    t.printContainers();
}