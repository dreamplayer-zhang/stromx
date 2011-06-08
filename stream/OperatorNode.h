#ifndef STREAM_OPERATORNODE_H
#define STREAM_OPERATORNODE_H

#include <boost/thread/mutex.hpp>
#include <map>

namespace stream
{
    class OperatorInterface;
    class InputNode;
    class OutputNode;
    
    class OperatorNode
    {
    public:
        OperatorNode(OperatorInterface* const op);
        ~OperatorNode();
        
        const std::string & name() const { return m_name; }
        void setName(const std::string & name) { m_name = name; }
        InputNode* const getInputNode(const unsigned int id);
        OutputNode* const getOutputNode(const unsigned int id);
        OperatorInterface* const op() { return m_operator; }
        
    private:
        std::string m_name;
        OperatorInterface* m_operator;
        std::map<unsigned int, OutputNode*> m_outputs;
        std::map<unsigned int, InputNode*> m_inputs;
    };
}

#endif // STREAM_OPERATORNODE_H