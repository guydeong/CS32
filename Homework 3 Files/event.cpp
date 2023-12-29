//Requirements:
// 1) You must not declare any struct or class other than Event, BasketballGame, Concert, and HockeyGame
// 2) The Event class must not have a default constructor. The only constructor you may declare for Event must have exactly one parameter. That parameter must be of type string, and it must be a useful parameter.
// 3) Although the expression new Concert("BLACKPINK", "K-pop") is fine, the expression new Event("Sparks vs. Mercury") must produce a compilation error. 
// (A client can create a particular kind of event object, like a concert, but is not allowed to create an object that is just a plain Event.
// 4) Other than constructors and destructors (which can't be const), all members must be const member functions
// 5) No two functions with non-empty bodies may have the same implementation, or implementations that have the same effect for a caller.
// 6) No implementation of a name() function may explicitly call any other function.
// 7) No class may have a data member whose value is identical for every object of a particular class type.
// 8) All data members must be declared private, You may declare member functions public or private. Your solution must not declare any protected members (which we're not covering in this class). Your solution must not contain the word friend
//Your declarations and implementations would go here

//Base Class: Event Class
class Event {
    public:
        Event(string name):m_name(name) {}; //constructor with one parameter
        string name() const { return m_name; } //getter for name
        virtual bool isSport() const { return true; } //virtual function
        virtual string need() const = 0; //pure-virtual function
        virtual ~Event() {}; //virtual destructor

    private:
        //Every event has a name
        string m_name;
        //Every type of event has a signficant need (e.g. hoops for a basketball game or a stage for a concert)
        //Most types of events are sporting events, but a few are not.
};


//Derived Class 1: Basketball Game Class
class BasketballGame: public Event {
public:
    BasketballGame(string name) : Event(name) {}
    virtual string need() const { return "hoops"; }
    virtual ~BasketballGame() {
        cout << "Destroying the " << this->name() << " basketball game" << endl;
    }

};

//Derived Class 2: Concert
class Concert: public Event {
public:
    Concert(string name, string genre) :Event(name) {
        m_genre = genre;
    }
    bool isSport() const { return false; }
    virtual string need() const { return "a stage"; }
    virtual ~Concert() {
        cout << "Destroying the " << this->name() << " " << m_genre << " concert" << endl;
    }
private:
    string m_genre;
};

//Derived Class 3: HockeyGame
class HockeyGame: public Event {
public:
    HockeyGame(string name) :Event(name) {};
    virtual string need() const { return "ice"; }
    virtual ~HockeyGame() {
        cout << "Destroying the " << this->name() << " hockey game" << endl;
    }
};
