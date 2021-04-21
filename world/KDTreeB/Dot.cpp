#include "Dot.h"

#include "KDTreeB/Nodes.h"
#include "KDTreeB/KDTree.h"
#include "Triangle.h"

namespace KDTreeB
{
    void addNode(std::ostream &ostream, UNode const *node);
    void addLink(std::ostream &ostream, UNode const *node);
    void addTriangle(std::ostream &ostream, Triangle const*);
    void printTriangles(std::ostream &ostream, const KDTree &tree);
    void printNodes(std::ostream &ostream, const KDTree &tree);
    void linkNodes(std::ostream &ostream, const KDTree &tree);

    void printKDTree(std::ostream &ostream, const KDTree &tree)
    {
        ostream << "digraph G {\n";
        printTriangles(ostream, tree);
        printNodes(ostream, tree);
        linkNodes(ostream, tree);
        ostream << "}";
    }

    inline std::string node2Label(unsigned idx)
    {
        return std::string("n").append(std::to_string(idx));
    }

    inline std::string triangle2Label(Triangle const*ptr)
    {
        return std::string("t").append(std::to_string(ptr->id));
    }

    inline char plane2char(Plane p)
    {
        static char c[] = {'x', 'y', 'z'};
        return c[p];
    }

//    void addNode(std::ostream &ostream, const KDTree& tree)
//    {
//        if (node->isNode()) {
//            ostream << toLabel(node) << "[label=\"" << plane2char(node->node.type()) << ": "
//                    << (node->node.split) << "\"]\n";
//
//        } else {
//            ostream << toLabel(node) << "[shape=square]\n";
//        }
//    }

//    void addLink(std::ostream &ostream, UNode const*node)
//    {
//        if (node->isNode())
//            ostream << toLabel(node) << "->" << toLabel(((UNode *) node)->lChild) << "\n";
//            ostream << toLabel(node) << "->" << toLabel(((UNode *) node)->rChild) << "\n";
//        else {
//            for (int i = 0; i < ((UNode *) node)->triangles.size(); ++i) {
//                ostream << toLabel(node) << "->" << t_toLabel((((UNode *) node)->triangles[i])) << "\n";
//            }
//        }
//    }

    void printTriangles(std::ostream &ostream, const KDTree &tree)
    {
        for(unsigned i = 0; i < tree.triangles.size(); ++i)
            ostream << triangle2Label(&(tree.triangles.at(i))) << "[shape=triangle]\n";
    }

    void printNodes(std::ostream &ostream, const KDTree &tree)
    {
        ostream << "root[label=\"root size:" << tree.nodes.size() << "\",shape=pentagon]\n";

        UNode const* un;
        for (unsigned idx = 0; idx < tree.nodes.size(); ++idx) {
            un = &tree.nodes.at(idx);
            ostream << node2Label(idx);
            if(un->isNode()) {
                ostream << "[label=\"" << plane2char(un->node.type()) << ": "
                        << (un->node.split) << "\"]\n";
            }
            else {
                ostream << "[label=\"" << un->leaf.first << "|" << un->leaf.children() << "\" ,shape=square]\n";
            }
        }
    }

    void linkNodes(std::ostream &ostream, const KDTree &tree)
    {
        ostream << "root->" << node2Label(0) << "\n";
        UNode const* un;
        for (unsigned idx = 0; idx < tree.nodes.size(); ++idx) {
            un = &tree.nodes.at(idx);
            if(un->isNode()) {
                ostream << node2Label(idx) << "->" << node2Label(idx+un->node.first()) << "\n";
                ostream << node2Label(idx) << "->" << node2Label(idx+un->node.first()+1) << "\n";
            }
            else {
                for(unsigned tidx = un->leaf.first; tidx < un->leaf.first+un->leaf.children(); tidx++) {
                    ostream << node2Label(idx) << "->" << triangle2Label(&(tree.triangles.at(tidx))) << "\n";
                }
            }
        }
    }
}