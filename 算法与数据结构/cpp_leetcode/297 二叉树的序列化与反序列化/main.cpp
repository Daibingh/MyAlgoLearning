#include <bits/stdc++.h>
#include "utils.hpp"

using namespace std;


/*
思路：先序遍历存成字符串，保留末尾的空节点，递归实现
此外，还可以采用层次遍历的方式

采用递归函数引用传参，否则超时
*/


class Codec {
public:

    void helper(TreeNode* root, string& str) {
        if (!root) {
            str+="X,";
            return;
        }
        str += to_string(root->val);
        str += ",";
        helper(root->left, str);
        helper(root->right, str);
    }

    string serialize(TreeNode* root) {
        string str="";
        helper(root, str);
        return str;
    }

    // TreeNode* deserialize(string data) {
    //     int pos = 0;
    //     return parse(data, pos);
    // }

    // TreeNode* parse(string& data, int& pos) {
    //     if (pos>=data.size()) return nullptr;
    //     if (data[pos]=='X') {
    //         pos+=2;
    //         return nullptr;
    //     }
    //     int val = 0;
    //     int sig = 1;
    //     if (data[pos]=='-') {
    //         sig = -1;
    //         ++pos;
    //     }
    //     while (data[pos]!=',')
    //     {
    //         val = 10*val + data[pos]-'0';
    //         ++pos;
    //     }
    //     ++pos;
    //     TreeNode* root = new TreeNode(sig*val);
    //     root->left = parse(data, pos);
    //     root->right = parse(data, pos);
    //     return root;
    // }

    TreeNode* deserialize(string data) {
        vector<string> a;
        while (!data.empty())  {
            int p = data.find(',');
            a.push_back(data.substr(0, p));
            data = data.substr(p+1);
        }
        print_vec(a);
        int pos = 0;
        TreeNode* root = build(a, pos);

        return root;
    }

    TreeNode* build(vector<string>& a, int& pos) {
        if (pos==a.size()) return nullptr;
        if (a[pos]=="X") {
            ++pos;
            return nullptr;
        }
        TreeNode* root = new TreeNode(atoi(a[pos++].c_str()));
        root->left = build(a, pos);
        root->right = build(a, pos);
        return root;
    }

};


// 字符空格分割读取 stringstream 方便

class Codec2 {

private:
    void serialize(TreeNode* root, ostringstream& out) {
        if (!root) {
            out<< "# ";  // "#" 表示空的叶子节点
            return;
        }
        out<<root->val<<" ";  // 以空格最为分割，便于 stringstream 读取
        serialize(root->left, out);
        serialize(root->right, out);
    }

    TreeNode* deserialize(istringstream& in) {
        string val;
        in>>val;
        if (val == "#") return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }
};



int main() {
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(6);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(7);

    Codec c;
    auto str = c.serialize(root);
    cout<<str<<endl;
    auto r = c.deserialize(str);

    cout<<c.serialize(r)<<endl;
}