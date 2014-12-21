#ifdef ANDROID
typedef int beta;
#endif

void globalaaa(int b) {

}

class  CCDrawNode : public CCNode
{
public:
    static CCDrawNode* create();
    virtual ~CCDrawNode() {}  ;

    //virtual bool init();
	virtual void draw(int (*pf)(void*)) = 0;

    /** Clear the geometry in the node's buffer. */

    void clear();

    bool runWithScene(CCScene *pScene) {

    }

protected:
	void drawNode() { 
		#ifdef DEBUG
		CCLOG("test");
		#endif
		int i = 0; if (i == 9) printf("haha"); 
	} ; 

    CC_SYNTHESIZE_BOOL(m_cancellable, Cancellable);
};