/****************************************************************************
 Author: Luma (stubma@gmail.com)
 
 https://github.com/stubma/cocos2dx-classical
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#ifndef __CCTMXLayer_h__
#define __CCTMXLayer_h__

#include "base_nodes/CCNode.h"
#include "ccTypes.h"
#include "ccMacros.h"
#include "sprite_nodes/CCSprite.h"

using namespace std;

NS_CC_BEGIN

class CCTMXMapInfo;
class CCTMXLayerInfo;
class CCTMXTileSetInfo;
class CCSpriteBatchNode;

/**
 * A layer in a TMX map. It supports multiple tilesets for one layer, which cocos2d-x doesn't.
 * The tile coordinate is relative to top-left and grows right in x axis and down in y axis
 *
 * \note
 * This is a re-implementation for TMX map. Cocos2d-x TMX support is defective, so I write my own.
 * To avoid name conflict, I use CB prefix which stands for cocos2dx-classical
 */
class CC_DLL CCTMXLayer : public CCNodeRGBA {
private:
	typedef struct {
		int atlasIndex;
		int tilesetIndex;
	} TileSetAtlasInfo;
	
private:
	/// gid array
	int* m_tiles;
	
	/// reused
	CCSprite* m_reusedTile;
	
private:
	/**
	 * decrease when index is larger than given value
	 *
     * @param tilesetIndex tileset index, must be matched
	 * @param index index threshold
	 */
	void decreaseIndexIfMoreThan(int tilesetIndex, int index);
	
	/**
	 * increase when index is not less than given value
	 *
     * @param tilesetIndex tileset index, must be matched
	 * @param index index threshold
	 */
	void increaseIndexIfEqualOrMoreThan(int tilesetIndex, int index);
	
	/// add sprite to tile
	void setupTileSprite(CCSprite* sprite, ccPosition pos, int gid);
	
	/// return reused tile
	CCSprite* reusedTile(CCRect rect, CCSpriteBatchNode* bn);
	
protected:
	/**
	 * Static constructor
	 *
	 * @param layerIndex index of layer, start from zero
	 * @param mapInfo info of whole map
	 */
	CCTMXLayer(int layerIndex, CCTMXMapInfo* mapInfo);
	
	/**
	 * get left-bottom pixel position of tile in a othrogonal map
	 *
	 * @param posX tile x
	 * @param posY tile y
	 * @return left-bottom pixel position of tile
	 */
	CCPoint getPositionForOrthoAt(int posX, int posY);
	
	/**
	 * get left-bottom pixel position of tile in a isometric map
	 *
	 * @param posX tile x
	 * @param posY tile y
	 * @return left-bottom pixel position of tile
	 */
	CCPoint getPositionForIsoAt(int posX, int posY);
	
	/**
	 * get left-bottom pixel position of tile in a hexagonal map
	 *
	 * @param posX tile x
	 * @param posY tile y
	 * @return left-bottom pixel position of tile
	 */
	CCPoint getPositionForHexAt(int posX, int posY);
	
	/**
	 * get vertex z value of a tile
	 *
	 * @param x tile x
	 * @param y tile y
	 * @return tile vertex z value
	 */
	float getVertexZAt(int x, int y);
    
    /**
     * get vertex z value of a tile
     *
     * @param loc tile location
     * @return tile vertex z value
     */
    float getVertexZAt(CCPoint loc);
	
	/**
	 * append a tile
	 *
     * @param tilesetIndex tileset index in which the tile image is
	 * @param gid tile id
	 * @param x tile x
	 * @param y tile y
	 */
	void appendTileForGid(int tilesetIndex, int gid, int x, int y);
    
    /**
     * Set a tile, internal called
     *
     * @param tilesetIndex index of tileset
     * @param gid tile id
     * @param x tile x position
     * @param y tile y position
     * @param z atlas info position
     */
    void setTileAt(int tilesetIndex, int gid, int x, int y, int z);
	
	/// parse internal properties
	void parseInternalProperties();
	
	/**
	 * calculate pixel offset of layer, by given tile coordinates
	 *
	 * @param x tile x
	 * @param y tile y
	 */
	CCPoint calculateLayerOffset(float x, float y);
	
	/// init gid array
	void setupTiles();
	
public:
	virtual ~CCTMXLayer();
	
	/**
	 * Static constructor
	 *
	 * @param layerIndex index of layer, start from zero
	 * @param mapInfo info of whole map
	 */
	static CCTMXLayer* create(int layerIndex, CCTMXMapInfo* mapInfo);
    
    /// set anti alias for all layer textures
    void setAntiAliasTexParameters();
	
	/// get layer property
	string getProperty(const string& key);
	
	/**
	 * By given a pixel offset in layer, return the tile coordinates
	 *
	 * @param x pixel x
	 * @param y pixel y
	 * @return tile coordinate, or (-1, -1) if not found
	 */
	ccPosition getTileCoordinateAt(float x, float y);
	
	/**
	 * returns the tile (CCSprite) at a given a tile coordinate.
	 * The returned CCSprite will be already added to the CCTMXLayer. Don't add it again.
	 * The CCSprite can be treated like any other CCSprite: rotated, scaled, translated, opacity, color, etc.
	 * You can remove either by calling:
	 * 		layer->removeChild(sprite, true);
	 * 	 or layer->removeTileAt(x, y);
	 *
	 * Tag of returned sprite is set to x + y * layerWidth, don't modify it.
	 */
	CCSprite* tileAt(int x, int y);
    
    /**
     * returns the tile (CCSprite) at a given a tile coordinate.
     * The returned CCSprite will be already added to the CCTMXLayer. Don't add it again.
     * The CCSprite can be treated like any other CCSprite: rotated, scaled, translated, opacity, color, etc.
     * You can remove either by calling:
     * 		layer->removeChild(sprite, true);
     * 	 or layer->removeTileAt(x, y);
     *
     * Tag of returned sprite is set to x + y * layerWidth, don't modify it.
     */
    CCSprite* tileAt(CCPoint loc);
	
	/**
	 * Remove a tile from a sprite which is got from \c tileAt method. If the sprite
	 * is not a tile sprite, do nothing
	 *
	 * @param sprite sprite which is got from \c tileAt
	 */
	void removeTile(CCSprite* sprite);
	
	/**
	 * get gid from tile coordinates
	 *
	 * @param x tile x
	 * @param y tile y
	 * @return tile id
	 */
	int getGidAt(int x, int y);
    
    /**
     * get gid from tile coordinates
     *
     * @param loc tile location
     * @return tile id
     */
    int getGidAt(CCPoint loc);
	
	/**
	 * get a reference of gid array, the array length is layerWidth * layerHeight
	 */
	const int* getGids();
	
	/**
	 * make a copy of gid array, the array length is layerWidth * layerHeight
	 * caller must release returned pointer
	 */
	const int* copyGids();
	
	/**
	 * remove tile at tile coordinates
	 *
	 * @param x tile x
	 * @param y tile y
	 */
	void removeTileAt(int x, int y);
    
    /**
     * remove tile at tile coordinates
     *
     * @param loc tile location
     */
    void removeTileAt(CCPoint loc);
	
	/**
	 * set a tile at tile coordinate, if tile is existent, it is same as updateTileAt
	 *
	 * @param gid tile id
	 * @param x tile x
	 * @param y tile y
	 */
	void setTileAt(int gid, int x, int y);
    
    /**
     * set a tile at tile coordinate, if tile is existent, it is same as updateTileAt
     *
     * @param gid tile id
     * @param loc tile location
     */
    void setTileAt(int gid, CCPoint loc);
	
	/**
	 * update tile at tile coordinate, if no tile, it will add a tile
	 *
	 * @param gid tile id
	 * @param x tile x
	 * @param y tile y
	 */
	void updateTileAt(int gid, int x, int y);
    
    /**
     * update tile at tile coordinate, if no tile, it will add a tile
     *
     * @param gid tile id
     * @param loc tile location
     */
    void updateTileAt(int gid, CCPoint loc);
	
	/**
	 * get left-bottom pixel position of tile, relative to layer left-bottom
	 *
	 * @param x tile x
	 * @param y tile y
	 * @return left-bottom pixel position
	 */
	CCPoint getPositionAt(int x, int y);
    
    /**
     * get left-bottom pixel position of tile, relative to layer left-bottom
     *
     * @param loc tile location
     * @return left-bottom pixel position
     */
    CCPoint getPositionAt(CCPoint loc);
	
	/// change color of a tile
	void setTileColorAt(ccColor4B c, int x, int y);
    
    /// change color of a tile
    void setTileColorAt(ccColor4B c, CCPoint loc);
    
    /// get layer size in tile
    CCSize getLayerSize() { return CCSizeMake(m_layerWidth, m_layerHeight); }
	
	/// layer tiles in x axis
	CC_SYNTHESIZE(int, m_layerWidth, LayerWidth);
	
	/// layer tiles in y axis
	CC_SYNTHESIZE(int, m_layerHeight, LayerHeight);
	
	/// tile width in pixels
	CC_SYNTHESIZE(int, m_tileWidth, TileWidth);
	
	/// tile height in pixels
	CC_SYNTHESIZE(int, m_tileHeight, TileHeight);
	
	/// min gid
	CC_SYNTHESIZE(int, m_minGid, MinGid);
	
	/// max gid
	CC_SYNTHESIZE(int, m_maxGid, MaxGid);
    
    /// map info
	CC_SYNTHESIZE(CCTMXMapInfo*, m_mapInfo, MapInfo);
	
    /// layer info
	CC_SYNTHESIZE(CCTMXLayerInfo*, m_layerInfo, LayerInfo);
	
	/// info of atlas
	CC_SYNTHESIZE(TileSetAtlasInfo*, m_atlasInfos, AtlasInfos);
    
    /// sprite batch node array
	CC_SYNTHESIZE(CCSpriteBatchNode**, m_batchNodes, BatchNodes);
	
	/// automatic vertex Z
	CC_SYNTHESIZE_BOOL(m_useAutomaticVertexZ, UseAutomaticVertexZ);
	
	/// fixed vertex z
	CC_SYNTHESIZE(float, m_vertexZ, VertexZ);
	
	/// alpha func value
	CC_SYNTHESIZE(float, m_alphaFuncValue, AlphaFuncValue);
};

NS_CC_END

#endif // __CCTMXLayer_h__
