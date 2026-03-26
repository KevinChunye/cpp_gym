#include <iostream>
#include <vector>
using namespace std;


class HotelRoom {
public:
    // Constructor: initializer list sets private members directly (efficient)
    HotelRoom(int bedrooms, int bathrooms)
        : bedrooms_(bedrooms), bathrooms_(bathrooms) {}

    // BUG FIX: must be 'virtual' so that when called through a base pointer,
    // the correct subclass version runs (polymorphism).
    //
    // ROOT CAUSE OF ORIGINAL BUG:
    // Without 'virtual', C++ uses the POINTER TYPE (always HotelRoom*) to
    // decide which get_price() to call -- not the actual object underneath.
    // So even when the real object is HotelApartment, it always calls
    // HotelRoom::get_price(), silently losing the +100 surcharge.

    // Without 'virtual' = static dispatch  (pointer type decides)
    // With    'virtual' = dynamic dispatch (actual object type decides)
    virtual int get_price() {
        return 50 * bedrooms_ + 100 * bathrooms_;
    }

private:
    int bedrooms_;
    int bathrooms_;  // trailing _ is a common convention for private members
};

// DERIVED CLASS
class HotelApartment : public HotelRoom {
public:
    // Delegates construction up to HotelRoom via initializer list
    HotelApartment(int bedrooms, int bathrooms)
        : HotelRoom(bedrooms, bathrooms) {}

    // 'override': compiler error if base has no matching virtual
    int get_price() override {
        return HotelRoom::get_price() + 100; 
    }
};

int main() {
    int n;
    cin >> n;  

    // Single vector holds raw pointers to heap-allocated objects.
    // Works correctly now because get_price() is virtual -- the actual
    // object type is used at runtime, not the pointer type.
    vector<HotelRoom*> rooms;

    for (int i = 0; i < n; ++i) {
        string room_type;
        int bedrooms, bathrooms;
        cin >> room_type >> bedrooms >> bathrooms;

        if (room_type == "standard") {
            rooms.push_back(new HotelRoom(bedrooms, bathrooms));
        } else {
            rooms.push_back(new HotelApartment(bedrooms, bathrooms));
        }
        // 'new' allocates on the heap; we manually delete below to avoid leaks
    }

    int total_profit = 0;
    for (auto room : rooms) {
        total_profit += room->get_price();
    }
    cout << total_profit << endl;

    // CLEANUP (manual memory management)
    // Every 'new' must be paired with a 'delete' to free heap memory
    for (auto room : rooms) { delete room; }
    rooms.clear();

    return 0;
}