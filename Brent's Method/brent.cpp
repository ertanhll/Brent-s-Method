
// Halil Ertan 20220702109

#include "brent.h"
#include <iostream>

using namespace std;

Brent::Brent(int table_size) {
    data_vec.resize(table_size);
}

int Brent::hash(int key) const {
    return key % data_vec.size();
}

int Brent::hash2(int key) const {
    return int(key / data_vec.size()) % data_vec.size();
}

vector<int> Brent::calculateLQ(int index, int step) {
    vector<int> temp;
    temp.push_back(index);
    while (data_vec[index].valid == true) {
        // Collision: Linear quotient
        index = (index + step) % data_vec.size();
        temp.push_back(index);
    }

    return temp;
}



void Brent::insert(int key) {
    int index = hash(key);
    int step = hash2(key);
    
    if (!data_vec[index].valid) {
       
        data_vec[index].data = key;
        data_vec[index].valid = true;
        return;
    }
    
    vector<int> key_path = calculateLQ(index, step);
    long s = key_path.size();
    
    if (!key_path.empty()) {
        key_path.pop_back();
    }
    
    cout << "key_path: ";
    for (int path_element : key_path) {
        cout << path_element << " ";
    }
    cout << endl;
    unordered_map<int, vector<int>> second_table;
    
   
    for (int j = 0; j < key_path.size(); j++) {
        int current_key = data_vec[key_path[j]].data;
        
        
        cout << "currentkey = " << current_key  <<endl;
    }
    
    cout << "second_table [" << key << "]: ";
    for (int value : second_table[key]) {
        cout << value << " ";
    }
    cout << endl;
   
    for (int j = 0; j < key_path.size(); j++) {
        int current_key = data_vec[key_path[j]].data;
        int hash1_value = hash(current_key);
        int hash2_value = hash2(current_key);
        
        int i_value = 0;
        
        
        while (data_vec[(key_path[j]+ i_value * hash2_value) % data_vec.size()].valid) {
            i_value++;
            cout << "i = " << i_value << ", j = " << j+1 << endl;
            cout << "currentkey = " << current_key  <<endl;
            
        }
        
    
        second_table[key].push_back(i_value + j+1);
    }
    
    
    
    
    int min_ij = std::numeric_limits<int>::max();
    
    for (int ij : second_table[key]) {
        min_ij = std::min(min_ij, ij);
        cout << "min_ij= " <<min_ij   <<endl;
        cout << "S = " << s <<endl;
    }
    
    if (s > min_ij) {
        int min_ij_index = -1;
        for (int i = 0; i < key_path.size(); i++) {
            if (min_ij ==  second_table[key][i]) {
                min_ij_index ++;
                cout << "index = " << min_ij_index << endl;
                if (min_ij_index != -1) {
                    int current_key = data_vec[key_path[min_ij_index]].data;
                    cout << "Current key min index: " << current_key << endl;
                }
                break;
            }
            
        }
        
        int current_key = data_vec[key_path[min_ij_index]].data;
        int old_index = -1;
        
      
        for (int i = 0; i < data_vec.size(); i++) {
            if (data_vec[i].valid && data_vec[i].data == current_key) {
                old_index = i;
                cout << "oldindex = " << old_index << endl;

                break;
            }
        }
        
        data_vec[old_index].valid = false;
        data_vec[old_index].data = key;
        data_vec[old_index].valid = true;
        
        vector<int> new_probe_path = calculateLQ(old_index, hash2(current_key));
        int new_index = new_probe_path.back();

        data_vec[new_index].data = current_key;
        data_vec[new_index].valid = true;
        
        
    }
     else {

    int index = hash(key);
    int step = hash2(key);

  
    while (data_vec[index].valid) {
        index = (index + step) % data_vec.size();
    }

   
    data_vec[index].data = key;
    data_vec[index].valid = true;
}
}

    
int Brent::find_num_probes(int key) const {
    int index = hash(key);
    int step = hash2(key);
    int count = 1;

   
    while (data_vec[index].data != key) {
        index = (index + step) % data_vec.size();
        count++;
    }

    return count;
    
}

double Brent::find_average_num_probes() const {
    double total_probes = 0;
    int valid_entries = 0;

    for (const entry& e : data_vec) {
        if (e.valid) {
            total_probes += find_num_probes(e.data);
            valid_entries++;
        }
    }

    return (valid_entries > 0) ? total_probes / valid_entries : 0.0;
}



