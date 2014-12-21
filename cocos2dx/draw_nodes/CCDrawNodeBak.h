#ifdef ANDROID
typedef int beta;
#endif

int gLandable = 0;
static int sStaticLand;

enum {
	AAAA,
	BBBB,
	CCCC
} kCCNumberLike;

void globalbbb(float b) {

}

static void globalaaa(int b) {

}

extern void globalccc(std::string c);

class  CCDrawNode : public CCNode
{
public:
    static CCDrawNode* create();
    virtual ~CCDrawNode() {}  

    //virtual bool init();
	virtual void draw(int (*pf)(void*)) = 0;

    /** Clear the geometry in the node's buffer. */

    void clear();

    bool runWithScene(CCScene *pScene) {

    }

    std::string m_cancellable;

protected:
	void drawNode() { 
		#ifdef DEBUG
		CCLOG("test");
		#endif
		int i = 0; if (i == 9) printf("haha"); 
	} ; 

    CC_SYNTHESIZE_BOOL(m_cancellable, Cancellable);

    int m_villan;
};