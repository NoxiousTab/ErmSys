#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <map>
#include <algorithm>
#include "../include/EmergencyTree.hpp"

using namespace std;

struct Emergency {
    int severity;
    string description;
    string unitType;
    int assignedUnitId;
    int id; // unique ID for ordering same severity
    Emergency(int sev, string desc, string unit, int i)
        : severity(sev), description(desc), unitType(unit), id(i), assignedUnitId(1) {}
};

// Custom comparator for priority queue: higher severity = higher priority
struct CompareEmergency {
    bool operator()(Emergency* const& e1, Emergency* const& e2) {
        if (e1->severity == e2->severity)
            return e1->id > e2->id; // FIFO if same severity
        return e1->severity < e2->severity;
    }
};

class EmergencyResponseSystem {
private:
    int emergencyCount = 0;
    map<string, int> availableUnits; // unitType -> count
    map<string, priority_queue<Emergency*, vector<Emergency*>, CompareEmergency>> pendingEmergencies;
    EmergencyTree emergencyLog;

public:
    EmergencyResponseSystem() {
        availableUnits["Fire Truck"] = 2;
        availableUnits["Ambulance"] = 2;
        availableUnits["Police Car"] = 2;
    }

    void reportEmergency(int choice) {
        string description, unitType;
        int severity;

        switch (choice) {
            case 1:
                description = "Industrial Fire";
                severity = 3;
                unitType = "Fire Truck";
                break;
            case 2:
                description = "Domestic Fire";
                severity = 2;
                unitType = "Fire Truck";
                break;
            case 3:
                description = "Life-or-death Medical Emergency";
                severity = 3;
                unitType = "Ambulance";
                break;
            case 4:
                description = "Minor Injury";
                severity = 1;
                unitType = "Ambulance";
                break;
            case 5:
                description = "Robbery";
                severity = 2;
                unitType = "Police Car";
                break;
            case 6:
                description = "Other Criminal Incident";
                severity = 1;
                unitType = "Police Car";
                break;
            case 7:
                cin.ignore();
                cout << "Enter emergency description: ";
                getline(cin, description);
                cout << "Enter severity (1-3): ";
                cin >> severity;
                cin.ignore();
                cout << "Enter unit type required (Fire Truck / Ambulance / Police Car): ";
                getline(cin, unitType);
                break;
            default:
                cout << "Invalid choice!\n";
                return;
        }

        emergencyCount++;
        Emergency* newEmergency = new Emergency(severity, description, unitType, emergencyCount);

        if (availableUnits[unitType] > 0) {
            availableUnits[unitType]--;
            cout << "Emergency: " << description << " [Severity " << severity
                 << "] assigned to " << unitType << " immediately.\n";
            delete newEmergency; // simulate dispatch
        } else {
            pendingEmergencies[unitType].push(newEmergency);
            cout << "All units busy. Emergency queued.\n";
        }
        emergencyLog.addLog(emergencyCount, description, severity, unitType, emergencyCount);
    }

    void markUnitAvailable(string unitType) {
        availableUnits[unitType]++;
        cout << unitType << " marked as available.\n";
        assignUnits(unitType);
    }

    void assignUnits(string unitType) {
        auto& queue = pendingEmergencies[unitType];
        while (!queue.empty() && availableUnits[unitType] > 0) {
            Emergency* top = queue.top();
            queue.pop();
            availableUnits[unitType]--;
            cout << "Queued emergency dispatched: " << top->description
                 << " [Severity " << top->severity << "] assigned to " << unitType << ".\n";
            delete top;
        }
    }

    void viewPendingEmergencies() {
        cout << "\n--- Pending Emergencies ---\n";
        for (auto& [unitType, queue] : pendingEmergencies) {
            priority_queue<Emergency*, vector<Emergency*>, CompareEmergency> tempQueue = queue;
            cout << unitType << ":\n";
            if (tempQueue.empty()) {
                cout << "  None\n";
                continue;
            }
            while (!tempQueue.empty()) {
                Emergency* e = tempQueue.top();
                tempQueue.pop();
                cout << "  " << e->description << " (Severity " << e->severity << ")\n";
            }
        }
    }

    void viewAvailableUnits() {
        cout << "\n--- Available Units ---\n";
        for (auto& [unit, count] : availableUnits) {
            cout << unit << ": " << count << endl;
        }
    }

    bool resolveEmergency(int id) {
        return emergencyLog.resolveEmergencyById(id);
    }


    void menu() {
        int choice;
        do {
            cout << "\n--- Emergency Response Menu ---\n";
            cout << "1. Report Industrial Fire\n";
            cout << "2. Report Domestic Fire\n";
            cout << "3. Report Life-or-death Medical Emergency\n";
            cout << "4. Report Minor Injury\n";
            cout << "5. Report Robbery\n";
            cout << "6. Report Other Criminal Incident\n";
            cout << "7. Report Other Emergency\n";
            cout << "8. Mark Unit as Available\n";
            cout << "9. View Pending Emergencies\n";
            cout << "10. View Available Units\n";
            cout << "11. View Emergency Log (Binary Tree)\n";
            cout << "12. Mark Emergency as Resolved\n";
            cout << "13. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1 ... 7:
                    reportEmergency(choice);
                    break;
                case 8: {
                    cin.ignore();
                    string unitType;
                    cout << "Enter unit type to mark available: ";
                    getline(cin, unitType);
                    markUnitAvailable(unitType);
                    break;
                }
                case 9:
                    viewPendingEmergencies();
                    break;
                case 10:
                    viewAvailableUnits();
                    break;
                case 13:
                    cout << "Exiting...\n";
                    break;
                case 11:
                    emergencyLog.displayLog();
                    break;

                case 12: {
                    int id;
                    cout << "Enter Emergency ID to resolve: ";
                    cin >> id;
                    if (resolveEmergency(id)) {
                        cout << "Emergency ID " << id << " marked as resolved.\n";
                    } else {
                        cout << "Emergency ID not found in log.\n";
                    }
                    break;
                }


                default:
                    cout << "Invalid option!\n";
            }

        } while (choice != 13);
    }
};

int main() {
    EmergencyResponseSystem system;
    system.menu();
    return 0;
}
