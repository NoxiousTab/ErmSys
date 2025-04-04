#include "../include/EmergencyTree.hpp"
#include <bits/stdc++.h>

using namespace std;

EmergencyNode* EmergencyTree::insert(int id, string description, int severity, string unitType, int assignedUnitId) {
        root = insertRec(root, id, description, severity, unitType, assignedUnitId);
        return root;
}

EmergencyNode* EmergencyTree::insertRec(EmergencyNode* node, int id, string description, int severity, string unitType, int assignedUnitId) {
    if (!node) return new EmergencyNode(id, description, severity, unitType, assignedUnitId);
    if (id < node->id)
        node->left = insertRec(node->left, id, description, severity, unitType, assignedUnitId);
    else
        node->right = insertRec(node->right, id, description, severity, unitType, assignedUnitId);
    return node;
}


void EmergencyTree::inorder(EmergencyNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << "ID: " << node->id << " | " << node->description << " | Severity: "
             << node->severity << " | Unit: " << node->unitType << " | Status: " << node->status << endl;
        inorder(node->right);
}

void EmergencyTree::addLog(int id, string description, int severity, string unitType, int assignedUnitId) {
        EmergencyNode* newNode = new EmergencyNode(id, description, severity, unitType, assignedUnitId);
        root = insert(id, description, severity, unitType, assignedUnitId);
}

bool EmergencyTree::resolveEmergencyById(int id) {
    EmergencyNode* node = root;
    while (node) {
        if (id == node->id) {
            node->status = "Resolved";
            return true;
        } else if (id < node->id) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return false; // Not found
}


void EmergencyTree::displayLog() {
        cout << "\n--- Emergency Log (In-order) ---\n";
        inorder(root);
}
