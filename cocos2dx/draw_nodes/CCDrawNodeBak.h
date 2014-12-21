#include <stdbool.h>

class  CCDrawNode
{
public:
    static CCDrawNode* create();
    virtual ~CCDrawNode();
    
    virtual bool init();
    virtual void draw();
    /** Clear the geometry in the node's buffer. */
    void clear();
};
