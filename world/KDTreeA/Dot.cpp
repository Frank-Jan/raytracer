#include "Dot.h"
#include "world/KDTreeA/LNode.h"
#include "world/KDTreeA/INode.h"
#include "Triangle.h"


namespace KDTreeA
{

    void addNode(std::ostream &ostream, Node *node);

    void addLink(std::ostream &ostream, INode *node);

    void addTriangle(std::ostream &ostream, Triangle *);

    void printNodes(std::ostream &ostream, const KDTree &tree);

    void linkNodes(std::ostream &ostream, const KDTree &tree);

    void printKDTree(std::ostream &ostream, const KDTree &tree)
    {
        ostream << "digraph G {\n";
        printNodes(ostream, tree);
        linkNodes(ostream, tree);
        ostream << "}";
    }

    inline std::string toLabel(void *ptr)
    {
        return std::to_string((int) ptr);
    }

    inline std::string triangle2Label(const Triangle *ptr)
    {
        return std::string("t").append(std::to_string(ptr->id));
    }

    inline char plane2char(Plane p)
    {
        static char c[] = {'x', 'y', 'z'};
        return c[p];
    }

    void addNode(std::ostream &ostream, Node *node)
    {
        if (node->isLeaf) {
            ostream << toLabel(node) << "[label=\"" << ((LNode*)node)->triangles.size() << "\"shape=square]\n";
            for (int i = 0; i < ((LNode *) node)->triangles.size(); ++i) {
                ostream << triangle2Label((((LNode *) node)->triangles[i])) << "[shape=triangle]\n";
            }
        } else {
            ostream << toLabel(node) << "[label=\"" << plane2char(((INode *) node)->tsplit) << ": "
                    << ((INode *) node)->txyz << "\"]\n";
        }
    }

    void addLink(std::ostream &ostream, Node *node)
    {
        if (node->isLeaf) {
            for (int i = 0; i < ((LNode *) node)->triangles.size(); ++i) {
                ostream << toLabel(node) << "->" << triangle2Label((((LNode *) node)->triangles[i])) << "\n";
            }
        }
        else {
            ostream << toLabel(node) << "->" << toLabel(((INode *) node)->lChild) << "\n";
            ostream << toLabel(node) << "->" << toLabel(((INode *) node)->rChild) << "\n";
        }
    }

    void printNodes(std::ostream &ostream, const KDTree &tree)
    {
        ostream << "root[label=\"root size:" << tree.nodes.size() << "\",shape=pentagon]\n";

        for (Node *n : tree.nodes) {
            addNode(ostream, n);
        }
    }

    void linkNodes(std::ostream &ostream, const KDTree &tree)
    {
        ostream << "root->" << toLabel(tree.root) << "\n";
        for (Node *n : tree.nodes) {
            addLink(ostream, n);
        }
    }

}