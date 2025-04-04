#include <string>
using namespace std; 

struct EmergencyNode {
    int id;
    string description;
    int severity;
    string unitType;
    int assignedUnitId;
    string status;
    EmergencyNode* left;
    EmergencyNode* right;

    EmergencyNode(int i, string d, int s, string u, int unitID)
        : id(i), description(d), severity(s), unitType(u), left(nullptr), right(nullptr), status("Active"), assignedUnitId(unitID) {}
};

class EmergencyTree {
private:
    EmergencyNode* root = nullptr;

    EmergencyNode* insert(int id, string description, int severity, string unitType, int assignedUnitId);
    EmergencyNode* insertRec(EmergencyNode* node, int id, string description, int severity, string unitType, int assignedUnitId);
    void inorder(EmergencyNode* node);

public:
    void addLog(int id, string description, int severity, string unitType, int assignedUnitId);
    bool resolveEmergencyById(int id);
    void displayLog();
};
