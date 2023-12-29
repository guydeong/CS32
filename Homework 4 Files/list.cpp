void listAll(const MenuItem* m, string path) // two-parameter overload
{
    string s;
    const MenuItem* curr = m;
    string curr_name = curr->name();
    if (path == "") {
        s = curr_name;
    }
    else {
        s = path + "/" + curr_name;
    }

    if (curr_name != "")
        cout << s << endl;
    if (curr->menuItems() != 0) {

        for (int i = 0; i < curr->menuItems()->size(); i++)
            listAll(curr->menuItems()->at(i), s);
    }
            
}